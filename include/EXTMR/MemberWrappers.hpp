/* 
 * File:   MethodWrapper.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on December 27, 2012, 11.27
 */

#ifndef EXTMR_METHODWRAPPER_HPP
#define	EXTMR_METHODWRAPPER_HPP

namespace extmr{

/**
 * Auxiliary function to provide an abstract signature to construct objects.
 * 
 * @param address If not NULL, the placement constructor will be called to this address.
 * @return A pointer to the new instance.
 */
template<typename T>
void* constructorWrapper(void* address)
{
    if (address)
    {
        // call the placement constructor to the provided address
        return new (reinterpret_cast<T*>(address)) T();
    }
    else
    {
        // call the constructor
        return new T();
    }
}

/**
 * Auxiliary function to provide an abstract signature to copy objects.
 * 
 * @param address If not NULL, the placement copy constructor will be called to this address.
 * @return A pointer to the new copied instance.
 */
template<typename T>
void* copyConstructorWrapper(const void* toBeCopiedPtr, void* address)
{
    if (address)
    {
        // call the placement copy constructor to the specified address
        return new (reinterpret_cast<T*>(address)) T(*reinterpret_cast<const T*>(toBeCopiedPtr));
    }
    else
    {
        // call the copy constructor
        return new T(*reinterpret_cast<const T*>(toBeCopiedPtr));
    }
}

/**
 * Auxiliary function to provide an abstract signature to destruct objects.
 * 
 * @param toBeDeletedPtr Pointer to the object to be destroyed.
 * @param deallocate If true, the delete operator is called, otherwise the destructor is called explicity
 */
template<typename T>
void destructorWrapper(void* toBeDeletedPtr, bool deallocate)
{
    if (deallocate)
    {
        delete reinterpret_cast<T*>(toBeDeletedPtr);
    }
    else
    {
        reinterpret_cast<T*>(toBeDeletedPtr)->~T();
    }
}

/**
 * Utility function to provide an abstract signature to assign objects.
 * 
 * @param lvaluePtr Pointer to the lvalue object.
 * @param rvaluePtr Pointer to the rvalue object.
 */
template<typename T>
void operatorAssignWrapper(void* lvaluePtr, const void* rvaluePtr)
{
    *reinterpret_cast<T*>(lvaluePtr) = *reinterpret_cast<const T*>(rvaluePtr);
}

/**
 * Utility template to get the right flags for the return variant of the method wrappers.
 */
template<typename T>
struct ReturnVariantFlags
{
    static const char flags = (IsReference<T>::value * (Variant::Reference + Variant::CopyByRef)) | (IsConst<T>::value * Variant::Const);
};

/**
 * This method wrapper template provide an abstraction to a class method. This is needed because
 * Method::call() needs to return a Variant regardless the method return value is void or not.
 * So we return a Variant containing the method return value when this is not void, an invalid variant otherwise.
 * To accomplish this, instead of partial specializing the whole MethodImpl class we can use such a wrapper.
 */
template
<
    class ClassT,
    typename RetT,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3,
    typename ParamT4,
    typename ParamT5,
    typename ParamT6,
    typename ParamT7,
    typename ParamT8
>
struct MethodWrapper
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef RetT (ClassT::*MethodType)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5, ParamT6, ParamT7, ParamT8);
    
    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type NqParamT3;
    typedef typename RemoveConst<typename RemoveReference<ParamT4>::Type>::Type NqParamT4;
    typedef typename RemoveConst<typename RemoveReference<ParamT5>::Type>::Type NqParamT5;
    typedef typename RemoveConst<typename RemoveReference<ParamT6>::Type>::Type NqParamT6;
    typedef typename RemoveConst<typename RemoveReference<ParamT7>::Type>::Type NqParamT7;
    typedef typename RemoveConst<typename RemoveReference<ParamT8>::Type>::Type NqParamT8;
    
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type NqRetT;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        /*
         * This method must work regardless the return type is a reference or a temporary.
         * In any case, assigning the return value to a constant reference is allowed.
         * Assigning to a reference is needed, in case the return value is a reference, to construct a reference
         * Variant referencing the original data. If the return value is not a reference we are minimizing the coping and
         * still keeping the code cleaner (otherwise using an auxiliary variable would result in adding a copy constructor call).
         * We are actually fooling the compiler because we will remove the constness with a
         * const_cast before the value is passed to the Variant constructor.
         * It's up to the Variant constructor copy the variable value or to reference it.
         * The ReturnVariantFlags<RetT>::flags evaluate to the right flags to manage the Variant
         * construction.
         */
        const NqRetT& returnValue = (objRef.*(method))
        (
            arg1.to<NqParamT1>(),
            arg2.to<NqParamT2>(),
            arg3.to<NqParamT3>(),
            arg4.to<NqParamT4>(),
            arg5.to<NqParamT5>(),
            arg6.to<NqParamT6>(),
            arg7.to<NqParamT7>(),
            arg8.to<NqParamT8>()
        );
        return Variant(const_cast<NqRetT&>(returnValue), ReturnVariantFlags<RetT>::flags);
    }
    
private:
    MethodType method;
};

template
<
    class ClassT,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3,
    typename ParamT4,
    typename ParamT5,
    typename ParamT6,
    typename ParamT7,
    typename ParamT8
>
struct MethodWrapper<ClassT, void, ParamT1, ParamT2, ParamT3, ParamT4, ParamT5, ParamT6, ParamT7, ParamT8>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef void (ClassT::*MethodType)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5, ParamT6, ParamT7, ParamT8);
    
    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type NqParamT3;
    typedef typename RemoveConst<typename RemoveReference<ParamT4>::Type>::Type NqParamT4;
    typedef typename RemoveConst<typename RemoveReference<ParamT5>::Type>::Type NqParamT5;
    typedef typename RemoveConst<typename RemoveReference<ParamT6>::Type>::Type NqParamT6;
    typedef typename RemoveConst<typename RemoveReference<ParamT7>::Type>::Type NqParamT7;
    typedef typename RemoveConst<typename RemoveReference<ParamT8>::Type>::Type NqParamT8;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        (objRef.*(method))
        (
            arg1.to<NqParamT1>(),
            arg2.to<NqParamT2>(),
            arg3.to<NqParamT3>(),
            arg4.to<NqParamT4>(),
            arg5.to<NqParamT5>(),
            arg6.to<NqParamT6>(),
            arg7.to<NqParamT7>(),
            arg8.to<NqParamT8>()
        );
        // return an invalid variant
        return Variant();
    }
    
private:
    MethodType method;
};

template
<
    class ClassT,
    typename RetT,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3,
    typename ParamT4,
    typename ParamT5,
    typename ParamT6,
    typename ParamT7
>
struct MethodWrapper<ClassT, RetT, ParamT1, ParamT2, ParamT3, ParamT4, ParamT5, ParamT6, ParamT7, Empty>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef RetT (ClassT::*MethodType)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5, ParamT6, ParamT7);
    
    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type NqParamT3;
    typedef typename RemoveConst<typename RemoveReference<ParamT4>::Type>::Type NqParamT4;
    typedef typename RemoveConst<typename RemoveReference<ParamT5>::Type>::Type NqParamT5;
    typedef typename RemoveConst<typename RemoveReference<ParamT6>::Type>::Type NqParamT6;
    typedef typename RemoveConst<typename RemoveReference<ParamT7>::Type>::Type NqParamT7;
    
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type NqRetT;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        const NqRetT& returnValue = (objRef.*(method))
        (
            arg1.to<NqParamT1>(),
            arg2.to<NqParamT2>(),
            arg3.to<NqParamT3>(),
            arg4.to<NqParamT4>(),
            arg5.to<NqParamT5>(),
            arg6.to<NqParamT6>(),
            arg7.to<NqParamT7>()
        );
        return Variant(const_cast<NqRetT&>(returnValue), ReturnVariantFlags<RetT>::flags);
    }
    
private:
    MethodType method;
};

template
<
    class ClassT,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3,
    typename ParamT4,
    typename ParamT5,
    typename ParamT6,
    typename ParamT7
>
struct MethodWrapper<ClassT, void, ParamT1, ParamT2, ParamT3, ParamT4, ParamT5, ParamT6, ParamT7, Empty>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef void (ClassT::*MethodType)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5, ParamT6, ParamT7);
    
    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type NqParamT3;
    typedef typename RemoveConst<typename RemoveReference<ParamT4>::Type>::Type NqParamT4;
    typedef typename RemoveConst<typename RemoveReference<ParamT5>::Type>::Type NqParamT5;
    typedef typename RemoveConst<typename RemoveReference<ParamT6>::Type>::Type NqParamT6;
    typedef typename RemoveConst<typename RemoveReference<ParamT7>::Type>::Type NqParamT7;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        (objRef.*(method))
        (
            arg1.to<NqParamT1>(),
            arg2.to<NqParamT2>(),
            arg3.to<NqParamT3>(),
            arg4.to<NqParamT4>(),
            arg5.to<NqParamT5>(),
            arg6.to<NqParamT6>(),
            arg7.to<NqParamT7>()
        );
        // return an invalid variant
        return Variant();
    }
    
private:
    MethodType method;
};


template
<
    class ClassT,
    typename RetT,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3,
    typename ParamT4,
    typename ParamT5,
    typename ParamT6
>
struct MethodWrapper<ClassT, RetT, ParamT1, ParamT2, ParamT3, ParamT4, ParamT5, ParamT6, Empty, Empty>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef RetT (ClassT::*MethodType)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5, ParamT6);
    
    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type NqParamT3;
    typedef typename RemoveConst<typename RemoveReference<ParamT4>::Type>::Type NqParamT4;
    typedef typename RemoveConst<typename RemoveReference<ParamT5>::Type>::Type NqParamT5;
    typedef typename RemoveConst<typename RemoveReference<ParamT6>::Type>::Type NqParamT6;
    
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type NqRetT;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        const NqRetT& returnValue = (objRef.*(method))
        (
            arg1.to<NqParamT1>(),
            arg2.to<NqParamT2>(),
            arg3.to<NqParamT3>(),
            arg4.to<NqParamT4>(),
            arg5.to<NqParamT5>(),
            arg6.to<NqParamT6>()
        );
        return Variant(const_cast<NqRetT&>(returnValue), ReturnVariantFlags<RetT>::flags);
    }
    
private:
    MethodType method;
};

template
<
    class ClassT,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3,
    typename ParamT4,
    typename ParamT5,
    typename ParamT6
>
struct MethodWrapper<ClassT, void, ParamT1, ParamT2, ParamT3, ParamT4, ParamT5, ParamT6, Empty, Empty>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef void (ClassT::*MethodType)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5, ParamT6);
    
    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type NqParamT3;
    typedef typename RemoveConst<typename RemoveReference<ParamT4>::Type>::Type NqParamT4;
    typedef typename RemoveConst<typename RemoveReference<ParamT5>::Type>::Type NqParamT5;
    typedef typename RemoveConst<typename RemoveReference<ParamT6>::Type>::Type NqParamT6;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        (objRef.*(method))
        (
            arg1.to<NqParamT1>(),
            arg2.to<NqParamT2>(),
            arg3.to<NqParamT3>(),
            arg4.to<NqParamT4>(),
            arg5.to<NqParamT5>(),
            arg6.to<NqParamT6>()
        );
        // return an invalid variant
        return Variant();
    }
    
private:
    MethodType method;
};


template
<
    class ClassT,
    typename RetT,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3,
    typename ParamT4,
    typename ParamT5
>
struct MethodWrapper<ClassT, RetT, ParamT1, ParamT2, ParamT3, ParamT4, ParamT5, Empty, Empty, Empty>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef RetT (ClassT::*MethodType)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5);
    
    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type NqParamT3;
    typedef typename RemoveConst<typename RemoveReference<ParamT4>::Type>::Type NqParamT4;
    typedef typename RemoveConst<typename RemoveReference<ParamT5>::Type>::Type NqParamT5;
    
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type NqRetT;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        const NqRetT& returnValue = (objRef.*(method))
        (
            arg1.to<NqParamT1>(),
            arg2.to<NqParamT2>(),
            arg3.to<NqParamT3>(),
            arg4.to<NqParamT4>(),
            arg5.to<NqParamT5>()
        );
        return Variant(const_cast<NqRetT&>(returnValue), ReturnVariantFlags<RetT>::flags);
    }
    
private:
    MethodType method;
};

template
<
    class ClassT,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3,
    typename ParamT4,
    typename ParamT5
>
struct MethodWrapper<ClassT, void, ParamT1, ParamT2, ParamT3, ParamT4, ParamT5, Empty, Empty, Empty>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef void (ClassT::*MethodType)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5);
    
    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type NqParamT3;
    typedef typename RemoveConst<typename RemoveReference<ParamT4>::Type>::Type NqParamT4;
    typedef typename RemoveConst<typename RemoveReference<ParamT5>::Type>::Type NqParamT5;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        (objRef.*(method))
        (
            arg1.to<NqParamT1>(),
            arg2.to<NqParamT2>(),
            arg3.to<NqParamT3>(),
            arg4.to<NqParamT4>(),
            arg5.to<NqParamT5>()
        );
        // return an invalid variant
        return Variant();
    }
    
private:
    MethodType method;
};

template
<
    class ClassT,
    typename RetT,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3,
    typename ParamT4
>
struct MethodWrapper<ClassT, RetT, ParamT1, ParamT2, ParamT3, ParamT4, Empty, Empty, Empty, Empty>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef RetT (ClassT::*MethodType)(ParamT1, ParamT2, ParamT3, ParamT4);
    
    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type NqParamT3;
    typedef typename RemoveConst<typename RemoveReference<ParamT4>::Type>::Type NqParamT4;
    
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type NqRetT;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        const NqRetT& returnValue = (objRef.*(method))
        (
            arg1.to<NqParamT1>(),
            arg2.to<NqParamT2>(),
            arg3.to<NqParamT3>(),
            arg4.to<NqParamT4>()
        );
        return Variant(const_cast<NqRetT&>(returnValue), ReturnVariantFlags<RetT>::flags);
    }
    
private:
    MethodType method;
};

template
<
    class ClassT,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3,
    typename ParamT4
>
struct MethodWrapper<ClassT, void, ParamT1, ParamT2, ParamT3, ParamT4, Empty, Empty, Empty, Empty>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef void (ClassT::*MethodType)(ParamT1, ParamT2, ParamT3, ParamT4);
    
    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type NqParamT3;
    typedef typename RemoveConst<typename RemoveReference<ParamT4>::Type>::Type NqParamT4;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        (objRef.*(method))
        (
            arg1.to<NqParamT1>(),
            arg2.to<NqParamT2>(),
            arg3.to<NqParamT3>(),
            arg4.to<NqParamT4>()
        );
        // return an invalid variant
        return Variant();
    }
    
private:
    MethodType method;
};

template
<
    class ClassT,
    typename RetT,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3
>
struct MethodWrapper<ClassT, RetT, ParamT1, ParamT2, ParamT3, Empty, Empty, Empty, Empty, Empty>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef RetT (ClassT::*MethodType)(ParamT1, ParamT2, ParamT3);
    
    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type NqParamT3;
    
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type NqRetT;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        const NqRetT& returnValue = (objRef.*(method))
        (
            arg1.to<NqParamT1>(),
            arg2.to<NqParamT2>(),
            arg3.to<NqParamT3>()
        );
        return Variant(const_cast<NqRetT&>(returnValue), ReturnVariantFlags<RetT>::flags);
    }
    
private:
    MethodType method;
};

template
<
    class ClassT,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3
>
struct MethodWrapper<ClassT, void, ParamT1, ParamT2, ParamT3, Empty, Empty, Empty, Empty, Empty>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef void (ClassT::*MethodType)(ParamT1, ParamT2, ParamT3);
    
    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type NqParamT3;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        (objRef.*(method))
        (
            arg1.to<NqParamT1>(),
            arg2.to<NqParamT2>(),
            arg3.to<NqParamT3>()
        );
        // return an invalid variant
        return Variant();
    }
    
private:
    MethodType method;
};

template
<
    class ClassT,
    typename RetT,
    typename ParamT1,
    typename ParamT2
>
struct MethodWrapper<ClassT, RetT, ParamT1, ParamT2, Empty, Empty, Empty, Empty, Empty, Empty>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef RetT (ClassT::*MethodType)(ParamT1, ParamT2);
    
    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type NqParamT2;
    
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type NqRetT;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        const NqRetT& returnValue = (objRef.*(method))
        (
            arg1.to<NqParamT1>(),
            arg2.to<NqParamT2>()
        );
        return Variant(const_cast<NqRetT&>(returnValue), ReturnVariantFlags<RetT>::flags);
    }
    
private:
    MethodType method;
};

template
<
    class ClassT,
    typename ParamT1,
    typename ParamT2
>
struct MethodWrapper<ClassT, void, ParamT1, ParamT2, Empty, Empty, Empty, Empty, Empty, Empty>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef void (ClassT::*MethodType)(ParamT1, ParamT2);
    
    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type NqParamT2;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        (objRef.*(method))
        (
            arg1.to<NqParamT1>(),
            arg2.to<NqParamT2>()
        );
        // return an invalid variant
        return Variant();
    }
    
private:
    MethodType method;
};

template
<
    class ClassT,
    typename RetT,
    typename ParamT1
>
struct MethodWrapper<ClassT, RetT, ParamT1, Empty, Empty, Empty, Empty, Empty, Empty, Empty>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef RetT (ClassT::*MethodType)(ParamT1);
    
    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type NqParamT1;
    
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type NqRetT;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        const NqRetT& returnValue = (objRef.*(method))
        (
            arg1.to<NqParamT1>()
        );
        return Variant(const_cast<NqRetT&>(returnValue), ReturnVariantFlags<RetT>::flags);
    }
    
private:
    MethodType method;
};

template
<
    class ClassT,
    typename ParamT1
>
struct MethodWrapper<ClassT, void, ParamT1, Empty, Empty, Empty, Empty, Empty, Empty, Empty>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef void (ClassT::*MethodType)(ParamT1);
    
    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type NqParamT1;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        (objRef.*(method))
        (
            arg1.to<NqParamT1>()
        );
        // return an invalid variant
        return Variant();
    }
    
private:
    MethodType method;
};

template
<
    class ClassT,
    typename RetT
>
struct MethodWrapper<ClassT, RetT, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef RetT (ClassT::*MethodType)();
    
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type NqRetT;
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        const NqRetT& returnValue = (objRef.*(method))();
        return Variant(const_cast<NqRetT&>(returnValue), ReturnVariantFlags<RetT>::flags);
    }
    
private:
    MethodType method;
};

template <class ClassT>
struct MethodWrapper<ClassT, void, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty>
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    /// type of a method belonging to ClassT
    typedef void (ClassT::*MethodType)();
    
    MethodWrapper(GeneralMethod method) : method(reinterpret_cast<MethodType>(method)){}
    
    Variant operator()
    (
        ClassT& objRef,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const
    {   
        (objRef.*(method))();
        // return an invalid variant
        return Variant();
    }
    
private:
    MethodType method;
};


/*
 * Getter wrappers to allow to call through a signature with same parameter number
 * within the PropertyGetterSetter template class.
 */
template<class ClassT, typename RetT, typename ExtrParamT1, typename ExtrParamT2>
struct GetterWrapper
{   
    typedef RetT (ClassT::*GetterType)(ExtrParamT1, ExtrParamT2);
    
    GetterWrapper(GetterType getter) : getter(getter)
    {
    }
    
    RetT operator()(ClassT& objRef, ExtrParamT1 extrArg1, ExtrParamT2 extrArg2) const
    {
        return (objRef.*getter) (extrArg1, extrArg2);
    }
    
    GetterType getter;
};

template<class ClassT, typename RetT>
struct GetterWrapper<ClassT, RetT, Empty, Empty>
{    
    typedef RetT (ClassT::*GetterType)();
    
    GetterWrapper(GetterType getter) : getter(getter)
    {
    }
    
    RetT operator()(ClassT& objRef, Empty extrArg1, Empty extrArg2) const
    {
        return (objRef.*getter) ();
    }
    
    GetterType getter;
};

template<class ClassT, typename RetT, typename ExtrParamT1>
struct GetterWrapper<ClassT, RetT, ExtrParamT1, Empty>
{   
    typedef RetT (ClassT::*GetterType)(ExtrParamT1);
    
    GetterWrapper(GetterType getter) : getter(getter)
    {
    }
    
    RetT operator()(ClassT& objRef, ExtrParamT1 extrArg1, Empty extrArg2) const
    {
        return (objRef.*getter) (extrArg1);
    }
    
    GetterType getter;
};

/*
 * Setter wrappers to allow to call through a signature with same parameter number
 * within the PropertyGetterSetter tempate class.
 */
template<class ClassT, typename ParamT, typename ExtrParamT1, typename ExtrParamT2>
struct SetterWrapper
{   
    typedef void (ClassT::*SetterType)(ParamT, ExtrParamT1, ExtrParamT2);
    
    SetterWrapper(SetterType setter) : setter(setter)
    {
    }
    
    void operator()(ClassT& objRef, ParamT value, ExtrParamT1 extrArg1, ExtrParamT2 extrArg2) const
    {
        return (objRef.*setter) (value, extrArg1, extrArg2);
    }

    SetterType setter;
};

template<class ClassT, typename ParamT>
struct SetterWrapper<ClassT, ParamT, Empty, Empty>
{   
    typedef void (ClassT::*SetterType)(ParamT);
    
    SetterWrapper(SetterType setter) : setter(setter)
    {
    }
    
    void operator()(ClassT& objRef, ParamT value, Empty extrArg1, Empty extrArg2) const
    {
        return (objRef.*setter) (value);
    }
    
    SetterType setter;
};

template<class ClassT, typename ParamT, typename ExtrParamT1>
struct SetterWrapper<ClassT, ParamT, ExtrParamT1, Empty>
{   
    typedef void (ClassT::*SetterType)(ParamT, ExtrParamT1);
    
    SetterWrapper(SetterType setter) : setter(setter)
    {
    }
    
    void operator()(ClassT& objRef, ParamT value, ExtrParamT1 extrArg1, Empty extrArg2) const
    {
        return (objRef.*setter) (value, extrArg1);
    }
    
    SetterType setter;
};

} // namespace extmr

#endif	/* EXTMR_METHODWRAPPER_HPP */

