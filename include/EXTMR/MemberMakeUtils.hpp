/******************************************************************************      
 *      Extended Mirror: MemberMakeUtils.hpp                                  *
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


#ifndef EXTMR_MEMBERMAKEUTILS_HPP
#define	EXTMR_MEMBERMAKEUTILS_HPP

/*
 * Collection of functions to allow registration of properties and methods
 * through the parameter type deduction mechanism.
 */
namespace extmr{

//TODO: Consider using a bindProperty/bindMethod/bindBase method that does all
// the dirty work of binding things togheter, and remove the & operator,
// so the makeXXX methods.
// These method can be made part of the ClassBuild() functor to have access
// to the static type of the class being registered.

/*
 * Methods for property building through type deduction 
 */
template<class ClassT, typename FieldT>
Property& makeProperty(const std::string& name, FieldT ClassT::* field)
{
    // ensure that the type is registered
    registerType<FieldT>();
    
    // build the Property  and add it to the Class
    return *new PropertyField<ClassT, FieldT>(name, field);
}

template<class ClassT, typename FieldT, std::size_t size>
Property& makeProperty(const std::string& name,
        FieldT (ClassT::* field) [size])
{
    // ensure that the type is registered
    registerType<FieldT[size]>();
    
    // build the Property  and add it to the Class
    return *new PropertyArrayField<ClassT, FieldT[size]>(name, field);
}

template<class ClassT, typename RetT, typename ParamT>
Property& makeProperty(const std::string& name, RetT (ClassT::*getter)(),
        void (ClassT::*setter)(ParamT))
{   
    // ensure that the type is registered
    registerType<RetT>();
    
    // build the Property
    return *new PropertyGetterNSetter<ClassT, RetT, ParamT>(name, getter, false,
            setter);
}

template<class ClassT, typename RetT, typename ParamT>
Property& makeProperty(const std::string& name, RetT (ClassT::*getter)() const,
        void (ClassT::*setter)(ParamT))
{
    // ensure that the type is registered
    registerType<RetT>();
    
    // remove the constness from the getter method
    RetT (ClassT::*getter_nc)() = reinterpret_cast<RetT (ClassT::*)()>(getter);
    
    // build the Property
    return *new PropertyGetterNSetter<ClassT, RetT, ParamT>(name, getter_nc,
            true, setter);
}

template<class ClassT, typename RetT>
Property& makeProperty(const std::string& name, RetT (ClassT::*getter)())
{
    // ensure that the type is registered
    registerType<RetT>();
    
    // build the Property with a null setter pointer
    return *new PropertyGetterNSetter<ClassT, RetT, Empty>
            (
                name,
                getter,
                false,
                (void(ClassT::*)(Empty))(NULL)
            );
}

template<class ClassT, typename RetT>
Property& makeProperty(const std::string& name, RetT (ClassT::*getter)() const)
{
    // ensure that the type is registered
    registerType<RetT>();
    
    // remove the constness from the getter method
    RetT (ClassT::*getter_nc)() = reinterpret_cast<RetT (ClassT::*)()>(getter);
    
    // build the Property with a null setter pointer
    return *new PropertyGetterNSetter<ClassT, RetT, Empty>
            (
                name,
                getter_nc,
                true,
                (void(ClassT::*)(Empty))(NULL)
            );
}

template<class ClassT, typename RetT, typename ParamT, typename ExtrParamT>
Property& makeProperty
(
        const std::string& name,
        RetT (ClassT::*getter)(ExtrParamT),
        void (ClassT::*setter)(ParamT, ExtrParamT),
        ExtrParamT extrArg
)
{
    // ensure that the type is registered
    registerType<RetT>();
   
    // build the Property
    return *new PropertyGetterNSetter<ClassT, RetT, ParamT, ExtrParamT>
            (
                name,
                getter,
                false,
                setter,
                extrArg
            );
}
    
template<class ClassT, typename RetT, typename ParamT, typename ExtrParamT>
Property& makeProperty
(
        const std::string& name,
        RetT (ClassT::*getter)(ExtrParamT) const,
        void (ClassT::*setter)(ParamT, ExtrParamT),
        ExtrParamT extrArg
)
{ 
    // ensure that the type is registered
    registerType<RetT>();
    
    // remove the constness from the getter method
    RetT (ClassT::*getter_nc)(ExtrParamT) =
            reinterpret_cast<RetT (ClassT::*)(ExtrParamT)>(getter);
    
    // build the Property
    return *new PropertyGetterNSetter<ClassT, RetT, ParamT, ExtrParamT>
            (
                name,
                getter_nc,
                true,
                setter,
                extrArg
            );
}

template<class ClassT, typename RetT, typename ExtrParamT>
Property& makeProperty(const std::string& name,
        RetT (ClassT::*getter)(ExtrParamT), ExtrParamT extrArg)
{
    // ensure that the type is registered
    registerType<RetT>();
    
    // build the Property with a null setter pointer
    return *new PropertyGetterNSetter<ClassT, RetT, Empty, ExtrParamT>
            (
                name,
                getter,
                false,
                (void(ClassT::*)(Empty))(NULL),
                extrArg
            );
}

template<class ClassT, typename RetT, typename ExtrParamT>
Property& makeProperty(const std::string& name,
        RetT (ClassT::*getter)(ExtrParamT) const, ExtrParamT extrArg)
{
    // ensure that the type is registered
    registerType<RetT>();
    
    // remove the constness from the getter method
    RetT (ClassT::*getter_nc)(ExtrParamT) =
            reinterpret_cast<RetT (ClassT::*)(ExtrParamT)>(getter);
    
    // build the Property with a null setter pointer
    return *new PropertyGetterNSetter<ClassT, RetT, Empty, ExtrParamT>
            (
                name,
                getter_nc,
                true,
                (void(ClassT::*)(Empty))(NULL),
                extrArg
            );
}

template<class ClassT, typename RetT, typename ParamT, typename ExtrParamT1,
        typename ExtrParamT2>
Property& makeProperty
(
        const std::string& name,
        RetT (ClassT::*getter)(ExtrParamT1, ExtrParamT2),
        void (ClassT::*setter)(ParamT, ExtrParamT1, ExtrParamT2),
        ExtrParamT1 extrArg1,
        ExtrParamT2 extrArg2
)
{
    // ensure that the type is registered
    registerType<ParamT>();
    
    // build the Property
    return *new PropertyGetterNSetter<ClassT, RetT, ParamT, ExtrParamT1,
            ExtrParamT2>
            (
                name,
                getter,
                false,
                setter,
                extrArg1,
                extrArg2
            );
}

template<class ClassT, typename RetT, typename ParamT, typename ExtrParamT1,
        typename ExtrParamT2>
Property& makeProperty
(
        const std::string& name,
        RetT (ClassT::*getter)(ExtrParamT1, ExtrParamT2) const,
        void (ClassT::*setter)(ParamT, ExtrParamT1, ExtrParamT2),
        ExtrParamT1 extrArg1,
        ExtrParamT2 extrArg2
)
{
    // ensure that the type is registered
    registerType<RetT>();
    
    // remove the constness from the getter method
    RetT (ClassT::*getter_nc)(ExtrParamT1, ExtrParamT2) = 
            reinterpret_cast<RetT (ClassT::*)(ExtrParamT1,
            ExtrParamT2)>(getter);
    
    // build the Property
    return *new PropertyGetterNSetter<ClassT, RetT, ParamT, ExtrParamT1,
            ExtrParamT2>
            (
                name,
                getter_nc,
                true,
                setter,
                extrArg1,
                extrArg2
            );
}

template<class ClassT, typename RetT, typename ExtrParamT1,
        typename ExtrParamT2>
Property& makeProperty
(
        const std::string& name,
        RetT (ClassT::*getter)(ExtrParamT1, ExtrParamT2),
        ExtrParamT1 extrArg1,
        ExtrParamT2 extrArg2
)
{
    // ensure that the type is registered
    registerType<RetT>();
    
    // build the Property with a null setter pointer
    return *new PropertyGetterNSetter<ClassT, RetT, Empty, ExtrParamT1,
            ExtrParamT2>
            (
                name,
                getter,
                false,
                (void(ClassT::*)(Empty, ExtrParamT1, ExtrParamT2))(NULL),
                extrArg1,
                extrArg2
            );
}

template<class ClassT, typename RetT, typename ExtrParamT1,
        typename ExtrParamT2>
Property& makeProperty
(
        const std::string& name,
        RetT (ClassT::*getter)(ExtrParamT1, ExtrParamT2) const,
        ExtrParamT1 extrArg1,
        ExtrParamT2 extrArg2
)
{    
    // ensure that the type is registered
    registerType<RetT>();
    
    // remove the constness from the getter method
    RetT (ClassT::*getter_nc)(ExtrParamT1, ExtrParamT2) =
        reinterpret_cast<RetT (ClassT::*)(ExtrParamT1, ExtrParamT2)>(getter);
    
    // build the Property with a null setter pointer
    return *new PropertyGetterNSetter<ClassT, RetT, Empty, ExtrParamT1,
            ExtrParamT2>
            (
                name,
                getter_nc,
                true,
                (void(ClassT::*)(Empty, ExtrParamT1, ExtrParamT2))(NULL),
                extrArg1,
                extrArg2
            );
}

/*
 * Methods for methods building through type deduction 
 */

template<class ClassT, typename RetT>
Method& makeMethod(const std::string& name, RetT (ClassT::*method)())
{
    // ensure the RetT is registered
    registerType<RetT>();
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT>(name, method);
}

template<class ClassT, typename RetT>
Method& makeMethod(const std::string& name, RetT (ClassT::*method)() const)
{
    // ensure the RetT is registered
    registerType<RetT>();
    
    // remove the constness from the method
    RetT (ClassT::*method_nc)() = reinterpret_cast<RetT (ClassT::*)()>(method);
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT>(name, method_nc, true);
}
    
template<class ClassT, typename RetT, typename ParamT1>
Method& makeMethod(const std::string& name, RetT (ClassT::*method)(ParamT1))
{
    // ensure the types are registered
    registerType<RetT>();
    registerType<ParamT1>();
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT, ParamT1>(name, method);
}

template<class ClassT, typename RetT, typename ParamT1>
Method& makeMethod(const std::string& name,
        RetT (ClassT::*method)(ParamT1) const)
{
    // ensure the types are registered
    registerType<RetT>();
    registerType<ParamT1>();
    
    // remove the constness from the method
    RetT (ClassT::*method_nc)(ParamT1) =
            reinterpret_cast<RetT (ClassT::*)(ParamT1)>(method);
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT, ParamT1>(name, method_nc, true);
}
    
template<class ClassT, typename RetT, typename ParamT1, typename ParamT2>
Method& makeMethod(const std::string& name,
        RetT (ClassT::*method)(ParamT1, ParamT2))
{
    // ensure the types are registered
    registerType<RetT>();
    registerType<ParamT1>();
    registerType<ParamT2>();
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT, ParamT1, ParamT2>(name, method);   
}

template<class ClassT, typename RetT, typename ParamT1, typename ParamT2>
Method& makeMethod(const std::string& name,
        RetT (ClassT::*method)(ParamT1, ParamT2) const)
{
    // ensure the types are registered
    registerType<RetT>();
    registerType<ParamT1>();
    registerType<ParamT2>();
    
    // remove the constness from the method
    RetT (ClassT::*method_nc)(ParamT1, ParamT2) =
            reinterpret_cast<RetT (ClassT::*)(ParamT1, ParamT2)>(method);
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT, ParamT1, ParamT2>(name, method_nc,
            true);
}
    
template<class ClassT, typename RetT, typename ParamT1, typename ParamT2,
        typename ParamT3>
Method& makeMethod(const std::string& name,
        RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3))
{
    // ensure the types are registered
    registerType<RetT>();
    registerType<ParamT1>();
    registerType<ParamT2>();
    registerType<ParamT3>();
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT, ParamT1, ParamT2, ParamT3>(name,
            method);
}

template<class ClassT, typename RetT, typename ParamT1, typename ParamT2,
        typename ParamT3>
Method& makeMethod(const std::string& name,
        RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3) const)
{
    // ensure the types are registered
    registerType<RetT>();
    registerType<ParamT1>();
    registerType<ParamT2>();
    registerType<ParamT3>();
    
    // remove the constness from the method
    RetT (ClassT::*method_nc)(ParamT1, ParamT2, ParamT3) =
            reinterpret_cast<RetT (ClassT::*)(ParamT1, ParamT2,
            ParamT3)>(method);
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT, ParamT1, ParamT2, ParamT3>(name,
            method_nc, true);
}
    
template<class ClassT, typename RetT, typename ParamT1, typename ParamT2,
        typename ParamT3, typename ParamT4>
Method& makeMethod(const std::string& name,
        RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3, ParamT4))
{
    // ensure the types are registered
    registerType<RetT>();
    registerType<ParamT1>();
    registerType<ParamT2>();
    registerType<ParamT3>();
    registerType<ParamT4>();
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT, ParamT1, ParamT2, ParamT3,
            ParamT4>(name, method);
}

template<class ClassT, typename RetT, typename ParamT1, typename ParamT2,
        typename ParamT3, typename ParamT4>
Method& makeMethod(const std::string& name,
        RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3, ParamT4) const)
{
    // ensure the types are registered
    registerType<RetT>();
    registerType<ParamT1>();
    registerType<ParamT2>();
    registerType<ParamT3>();
    registerType<ParamT4>();
    
    // remove the constness from the method
    RetT (ClassT::*method_nc)(ParamT1, ParamT2, ParamT3, ParamT4) =
            reinterpret_cast<RetT (ClassT::*)(ParamT1, ParamT2, ParamT3,
            ParamT4)>(method);
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT, ParamT1, ParamT2, ParamT3,
            ParamT4>(name, method_nc, true);
}
    
template<class ClassT, typename RetT, typename ParamT1, typename ParamT2,
        typename ParamT3, typename ParamT4, typename ParamT5>
Method& makeMethod(const std::string& name,
        RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5))
{
    // ensure the types are registered
    registerType<RetT>();
    registerType<ParamT1>();
    registerType<ParamT2>();
    registerType<ParamT3>();
    registerType<ParamT4>();
    registerType<ParamT5>();
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT, ParamT1, ParamT2, ParamT3, ParamT4,
            ParamT5>(name, method);
}

template<class ClassT, typename RetT, typename ParamT1, typename ParamT2,
        typename ParamT3, typename ParamT4, typename ParamT5>
Method& makeMethod(const std::string& name,
        RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3, ParamT4,
        ParamT5) const)
{
    // ensure the types are registered
    registerType<RetT>();
    registerType<ParamT1>();
    registerType<ParamT2>();
    registerType<ParamT3>();
    registerType<ParamT4>();
    registerType<ParamT5>();
    
    // remove the constness from the method
    RetT (ClassT::*method_nc)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5) = 
            reinterpret_cast<RetT (ClassT::*)(ParamT1, ParamT2, ParamT3,
            ParamT4, ParamT5)>(method);
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT, ParamT1, ParamT2, ParamT3, ParamT4,
            ParamT5>(name, method_nc, true);
}

template<class ClassT, typename RetT, typename ParamT1, typename ParamT2,
        typename ParamT3, typename ParamT4, typename ParamT5, typename ParamT6>
Method& makeMethod(const std::string& name,
        RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5,
        ParamT6))
{
    // ensure the types are registered
    registerType<RetT>();
    registerType<ParamT1>();
    registerType<ParamT2>();
    registerType<ParamT3>();
    registerType<ParamT4>();
    registerType<ParamT5>();
    registerType<ParamT6>();
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT, ParamT1, ParamT2, ParamT3, ParamT4,
            ParamT5, ParamT6>(name, method);
}

template<class ClassT, typename RetT, typename ParamT1, typename ParamT2,
        typename ParamT3, typename ParamT4, typename ParamT5, typename ParamT6>
Method& makeMethod(const std::string& name,
        RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5,
        ParamT6) const)
{
    // ensure the types are registered
    registerType<RetT>();
    registerType<ParamT1>();
    registerType<ParamT2>();
    registerType<ParamT3>();
    registerType<ParamT4>();
    registerType<ParamT5>();
    registerType<ParamT6>();
    
    // remove the constness from the method
    RetT (ClassT::*method_nc)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5) = 
            reinterpret_cast<RetT (ClassT::*)(ParamT1, ParamT2, ParamT3,
            ParamT4, ParamT5, ParamT6)>(method);
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT, ParamT1, ParamT2, ParamT3, ParamT4,
            ParamT5, ParamT6>(name, method_nc, true);
}

template<class ClassT, typename RetT, typename ParamT1, typename ParamT2,
        typename ParamT3, typename ParamT4, typename ParamT5, typename ParamT6,
        typename ParamT7>
Method& makeMethod(const std::string& name,
        RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5,
        ParamT6, ParamT7))
{
    // ensure the types are registered
    registerType<RetT>();
    registerType<ParamT1>();
    registerType<ParamT2>();
    registerType<ParamT3>();
    registerType<ParamT4>();
    registerType<ParamT5>();
    registerType<ParamT6>();
    registerType<ParamT7>();
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT, ParamT1, ParamT2, ParamT3, ParamT4,
            ParamT5, ParamT6, ParamT7>(name, method);
}

template<class ClassT, typename RetT, typename ParamT1, typename ParamT2,
        typename ParamT3, typename ParamT4, typename ParamT5, typename ParamT6,
        typename ParamT7>
Method& makeMethod(const std::string& name,
        RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5,
        ParamT6, ParamT7) const)
{
    // ensure the types are registered
    registerType<RetT>();
    registerType<ParamT1>();
    registerType<ParamT2>();
    registerType<ParamT3>();
    registerType<ParamT4>();
    registerType<ParamT5>();
    registerType<ParamT6>();
    registerType<ParamT7>();
    
    // remove the constness from the method
    RetT (ClassT::*method_nc)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5) = 
            reinterpret_cast<RetT (ClassT::*)(ParamT1, ParamT2, ParamT3,
            ParamT4, ParamT5, ParamT6, ParamT7)>(method);
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT, ParamT1, ParamT2, ParamT3, ParamT4,
            ParamT5, ParamT6, ParamT7>(name, method_nc, true);
}

template<class ClassT, typename RetT, typename ParamT1, typename ParamT2,
        typename ParamT3, typename ParamT4, typename ParamT5, typename ParamT6,
        typename ParamT7, typename ParamT8>
Method& makeMethod(const std::string& name,
        RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5,
        ParamT6, ParamT7, ParamT8))
{   
    // ensure the types are registered
    registerType<RetT>();
    registerType<ParamT1>();
    registerType<ParamT2>();
    registerType<ParamT3>();
    registerType<ParamT4>();
    registerType<ParamT5>();
    registerType<ParamT6>();
    registerType<ParamT7>();
    registerType<ParamT8>();
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT, ParamT1, ParamT2, ParamT3, ParamT4,
            ParamT5, ParamT6, ParamT7, ParamT8>(name, method);
}

template<class ClassT, typename RetT, typename ParamT1, typename ParamT2,
        typename ParamT3, typename ParamT4, typename ParamT5, typename ParamT6,
        typename ParamT7, typename ParamT8>
Method& makeMethod(const std::string& name, RetT (ClassT::*method)(ParamT1,
        ParamT2, ParamT3, ParamT4, ParamT5, ParamT6, ParamT7, ParamT8) const)
{   
    // ensure the types are registered
    registerType<RetT>();
    registerType<ParamT1>();
    registerType<ParamT2>();
    registerType<ParamT3>();
    registerType<ParamT4>();
    registerType<ParamT5>();
    registerType<ParamT6>();
    registerType<ParamT7>();
    registerType<ParamT8>();
    
    // remove the constness from the method
    RetT (ClassT::*method_nc)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5) = 
            reinterpret_cast<RetT (ClassT::*)(ParamT1, ParamT2, ParamT3,
            ParamT4, ParamT5, ParamT6, ParamT7, ParamT8)>(method);
    
    // create the proper Method
    return *new MethodImpl<ClassT, RetT, ParamT1, ParamT2, ParamT3, ParamT4,
            ParamT5, ParamT6, ParamT7, ParamT8>(name, method_nc, true);
}

} // namespace extmr

#endif	/* EXTMR_MEMBERMAKEUTILS_HPP */

