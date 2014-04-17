/******************************************************************************      
 *      Extended Mirror: Variant.inl                                         *
 ******************************************************************************
 *      Copyright (c) 2012-2014, Manuele Finocchiaro                          *
 *      All rights reserved.                                                  *
 ******************************************************************************
 * Redistribution and use in source and binary forms, with or without         *
 * modification, are permitted provided that the following conditions         *
 * are met:                                                                   *
 *                                                                            *
 *    1. Redistributions of source code must retain the above copyright       *
 *       notice, this list of conditions and the following disclaimer.        *
 *                                                                            *
 *    2. Redistributions in binary form must reproduce the above copyright    *
 *       notice, this list of conditions and the following disclaimer in      *
 *       the documentation and/or other materials provided with the           *
 *       distribution.                                                        *
 *                                                                            *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"* 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE  *
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE *
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE  *
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR        *
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF       *
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   *
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN    *
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)    *
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF     *
 * THE POSSIBILITY OF SUCH DAMAGE.                                            *
 *****************************************************************************/


#ifndef EXTMR_VARIANT_INL
#define	EXTMR_VARIANT_INL

#include <EXTMR/Exceptions/VariantTypeException.hpp>
#include <EXTMR/Exceptions/VariantCostnessException.hpp>
#include <EXTMR/Exceptions/NonCopyableException.hpp>
#include <EXTMR/Exceptions/NonAssignableException.hpp>
#include <EXTMR/Variant.hpp>

#include <cstring>


namespace extmr{
    

inline
const Type& Variant::getType() const
{
    return *type_;
}
    

inline
bool Variant::isReference() const
{
    return flags_ & Reference;
}
    

inline
bool Variant::isConst() const
{
    return flags_ & Const;
}
    

inline
bool Variant::isPointerToConst() const
{
    return flags_ & Ptr2Const;
}
    

inline
void Variant::setConst()
{
    flags_ |= Const;
}
    

template<typename T>    
Variant::Initialize<T>::Initialize(Variant& variant) : variant_(variant){};


template<typename T>
void Variant::Initialize<T>::operator()(T& data)
{
    // ensure type is registered.
    variant_.type_ = &registerType<T>();

    if (variant_.flags_ & Reference)
    {
        // store pointer to the data
        variant_.data_ = &data;
    }
    else
    {
        // allocate memory TODO: allow custom allocator
        variant_.data_ = ::operator new(sizeof(data));
        const Class* clazz = dynamic_cast<const Class*>(variant_.type_);
        
        if (clazz)
        {
            // copy data trough copy constructor
            try
            {
                clazz->getCopyConstructor().copy(variant_, RefVariant(data));
            }
            catch(NonCopyableException& e)
            {
                // deallocate memory if cannot copy
                ::operator delete(variant_.data_);
                throw e;
            }
        }
        else
        {
            // copy raw data
            std::memcpy(variant_.data_, &data, sizeof(data));
        }
    }

    // if the type is a pointer to a constant, set the proper flag.
    if (IsConst<typename RemovePointer<T>::Type>::value)
        variant_.flags_ |= Ptr2Const;
}


/**
 * If the type is an array, create an initializer
 * for a pointer to the element type, and pass it the address of the
 * first element.
 */
template<typename T, std::size_t size>
struct Variant::Initialize<T[size]>
{
    Initialize(Variant& variant) : variant_(variant){};
    
    void operator()(T data[size])
    {
        Initialize<T*> initializer(variant_);
        initializer(data);
    }
    
private:
    // A reference to the variant that is being initialized
    Variant& variant_;
};


template<typename T>
Variant::Variant(const T& data)
: flags_(0)
{
    // if the type is a constant array, then the type will be converted to a
    // pointer to constant
    if (IsArray<T>::value) flags_ |= Ptr2Const;
    
    // Call initializer functor
    Initialize<T>(*this)(const_cast<T&>(data));
}


template<typename T>
Variant::Variant(T& data, char flags)
: flags_(flags)
{
    typedef typename RemoveConst<T>::Type NonConstT;
    
    // if the type is a constant one, and a storing is performed by reference,
    // remember constness
    if ((flags & Reference) && IsConst<T>::value) flags_ |= Const;
    
    // if the type is a constant array, then the type will be converted to a
    // pointer to constant
    if (IsArray<T>::value && IsConst<T>::value) flags_ |= Ptr2Const;
    
    // Call initializer functor
    Initialize<NonConstT>(*this)(const_cast<NonConstT&>(data));
}


template<typename T>
Variant::operator T&() const
{
    // retrieve the type register
    TypeRegister& typeReg = TypeRegister::getSingleton();

    // ensure the type of the data is registered and retrieve it
    const Type& targetType = typeReg.registerType<T>();
    
    // check for constness correctness
    if (!IsConst<T>::value && flags_ & Const)
        throw VariantCostnessException(*type_);
    
    // check for pointed type's constness correctness
    if (flags_ & Ptr2Const &&
            !IsConst<typename RemovePointer<T>::Type>::value)
    {
        const Type& pointedType =
                dynamic_cast<const PointerType&>(*type_).getPointedType();
        throw VariantCostnessException(pointedType);
    }
    
    // check for type compatibility
    if (targetType == *type_)
    {
        // just reinterpret pointer
        return *reinterpret_cast<T*>(data_);
    }
    else
    {
        // check if objects
        if (!(targetType.getCategory() & Type::Class
            && type_->getCategory() & Type::Class))
            throw VariantTypeException(targetType, *type_);
        
        // cast to Class object
        const Class& clazz = dynamic_cast<const Class&>(*type_);
        
        // retrieve direct caster if any
        Const_RefCaster_Set casters = clazz.getRefCasters();
        const RefCaster* caster = 
                ptrSet::findByKey(casters, std::make_pair(type_, &targetType));
        
        // if caster found, cast this variant and return
        if (caster)
        {
            try
            {
                return caster->cast(*this).as<T>();
            }
            catch(std::bad_cast)
            {
                throw VariantTypeException(targetType, *type_);
            }
        }
        else
        {
            // for every ref caster, cast to that, then try to recast to T
            Const_RefCaster_Set::iterator ite = casters.begin();
            while(ite != casters.end())
            {
                try
                {
                    return (*ite)->cast(*this).as<T>();
                }
                catch (VariantTypeException)
                {}
                catch (std::bad_cast)
                {}
                ite ++;
            }
            throw VariantTypeException(targetType, *type_);
        }
    }
}


template<typename T>
inline T& Variant::as() const
{
    return *this;
}


template<>
Empty& Variant::as<Empty>() const;


template<typename T>
const T& Variant::operator=(const T& rvalue)
{       
    // get the Type
    const Type& rtype = extmr::getType<T>();
    const Class* clazz = dynamic_cast<const Class*>(type_);
    
    // check if types are the same
    if (!type_ || rtype != *type_)
    {
        // call destructor if class
        if (clazz)
        {
            const Destructor& destructor = clazz->getDestructor();
            destructor.destroy(*this);
        }
        
        // free memory
        ::operator delete(data_); // TODO: allow custom deallocator
        
        // set the new Type
        type_ = &rtype;
        
        // allocate new memory
        ::operator new(sizeof(T)); // TODO: allow custom allocator
        
        // call copy constructor if any
        clazz = dynamic_cast<const Class*>(type_);
        if (clazz)
        {
            const CopyConstructor& cpyC = clazz->getCopyConstructor();
            cpyC.copy(*this, RefVariant(rvalue));
        }
    }
    else
    {
        // call assign operator if class
        if (clazz)
        {
            const AssignOperator& assignOp = clazz->getAssignOperator();
            assignOp.assign(*this, RefVariant(rvalue));
        }
        else
        {
            // raw copy memory
            std::memcpy(data_, &rvalue, sizeof(T));
        }
    }
    
    // return the rvalue
    return rvalue;
}


} // namespace extmr

#endif	/* EXTMR_VARIANT_INL */

