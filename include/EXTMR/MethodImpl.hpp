
/******************************************************************************      
 *      Extended Mirror: MethodImpl.hpp                                       *
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

/* WARNING: This file has been autogenerated. do not modify it directly! */

#ifndef EXTMR_METHODIMPL_HPP
#define	EXTMR_METHODIMPL_HPP

#include <EXTMR/Exceptions/VariantCostnessException.hpp>

namespace extmr{


template
<
    class ClassT,
    typename RetT,
    typename ParamT0
>
class MethodImpl_1_Params : public Method
{
public: 
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type
        NqRetT;

    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT0>::Type>::Type
        NqParamT0;
    
    MethodImpl_1_Params(const std::string& name,
        RetT (ClassT::*method)
        (
            ParamT0
        ),
        bool constant = false) :
        Method(getClass<ClassT>(), name),
        method_(method),
        constant_(constant)
    {
        addParameter(*new Parameter(getType<ClassT>())); 
        addParameter(*new Parameter(getType<ParamT0>()));
    }

    
    Function::ReturnMode getReturnMode() const
    {
        if (IsReference<RetT>::value)
        {
            if (IsConst<RetT>::value)
                return ConstReference;
            else
                return Reference;
        }
        else
            return Value;
    }
    
    bool isConst() const
    {
        return constant_;
    }
    
    
    Variant callImpl
    (   
        const Variant& arg0,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7
        
    ) const
    {
        ClassT& objRef = arg0.as<ClassT>();
        
        // cannot call a non constant method of a constant instance
        if (arg0.isConst() && !constant_)
            throw VariantCostnessException(arg0.getType());
        
        const NqRetT& returnValue = (arg0.as<ClassT>().*method_)
        (
        );
        return Variant(const_cast<NqRetT&>(returnValue),
                ReturnVariantFlags<RetT>::flags);
        
    }

private:
    RetT (ClassT::*method_)
    (
        ParamT0
    );

    /// Whether the method is constant.
    bool constant_;
};


template
<
    class ClassT,
    typename ParamT0
>
class MethodImpl_1_Params
<
    ClassT,
    void,
    ParamT0
> : public Method
{
public: 
        typedef void RetT;

    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT0>::Type>::Type
        NqParamT0;
    
    MethodImpl_1_Params(const std::string& name,
        RetT (ClassT::*method)
        (
            ParamT0
        ),
        bool constant = false) :
        Method(getClass<ClassT>(), name),
        method_(method),
        constant_(constant)
    {
        addParameter(*new Parameter(getType<ClassT>())); 
        addParameter(*new Parameter(getType<ParamT0>()));
    }

    
    Function::ReturnMode getReturnMode() const
    {
        return None;
    }
    
    
    bool isConst() const
    {
        return constant_;
    }
    
    
    Variant callImpl
    (   
        const Variant& arg0,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7
        
    ) const
    {
        ClassT& objRef = arg0.as<ClassT>();
        
        // cannot call a non constant method of a constant instance
        if (arg0.isConst() && !constant_)
            throw VariantCostnessException(arg0.getType());
        
        (arg0.as<ClassT>().*method_)
        (
        );
        return Variant::Null;
        
    }

private:
    RetT (ClassT::*method_)
    (
        ParamT0
    );

    /// Whether the method is constant.
    bool constant_;
};


template
<
    class ClassT,
    typename RetT,
    typename ParamT0,
    typename ParamT1
>
class MethodImpl_2_Params : public Method
{
public: 
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type
        NqRetT;

    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT0>::Type>::Type
        NqParamT0;
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type
        NqParamT1;
    
    MethodImpl_2_Params(const std::string& name,
        RetT (ClassT::*method)
        (
            ParamT0,
            ParamT1
        ),
        bool constant = false) :
        Method(getClass<ClassT>(), name),
        method_(method),
        constant_(constant)
    {
        addParameter(*new Parameter(getType<ClassT>())); 
        addParameter(*new Parameter(getType<ParamT0>()));
        addParameter(*new Parameter(getType<ParamT1>()));
    }

    
    Function::ReturnMode getReturnMode() const
    {
        if (IsReference<RetT>::value)
        {
            if (IsConst<RetT>::value)
                return ConstReference;
            else
                return Reference;
        }
        else
            return Value;
    }
    
    bool isConst() const
    {
        return constant_;
    }
    
    
    Variant callImpl
    (   
        const Variant& arg0,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7
        
    ) const
    {
        ClassT& objRef = arg0.as<ClassT>();
        
        // cannot call a non constant method of a constant instance
        if (arg0.isConst() && !constant_)
            throw VariantCostnessException(arg0.getType());
        
        const NqRetT& returnValue = (arg0.as<ClassT>().*method_)
        (,
            arg1.as<NqParamT1>()
        );
        return Variant(const_cast<NqRetT&>(returnValue),
                ReturnVariantFlags<RetT>::flags);
        
    }

private:
    RetT (ClassT::*method_)
    (
        ParamT0,
        ParamT1
    );

    /// Whether the method is constant.
    bool constant_;
};


template
<
    class ClassT,
    typename ParamT0,
    typename ParamT1
>
class MethodImpl_2_Params
<
    ClassT,
    void,
    ParamT0,
    ParamT1
> : public Method
{
public: 
        typedef void RetT;

    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT0>::Type>::Type
        NqParamT0;
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type
        NqParamT1;
    
    MethodImpl_2_Params(const std::string& name,
        RetT (ClassT::*method)
        (
            ParamT0,
            ParamT1
        ),
        bool constant = false) :
        Method(getClass<ClassT>(), name),
        method_(method),
        constant_(constant)
    {
        addParameter(*new Parameter(getType<ClassT>())); 
        addParameter(*new Parameter(getType<ParamT0>()));
        addParameter(*new Parameter(getType<ParamT1>()));
    }

    
    Function::ReturnMode getReturnMode() const
    {
        return None;
    }
    
    
    bool isConst() const
    {
        return constant_;
    }
    
    
    Variant callImpl
    (   
        const Variant& arg0,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7
        
    ) const
    {
        ClassT& objRef = arg0.as<ClassT>();
        
        // cannot call a non constant method of a constant instance
        if (arg0.isConst() && !constant_)
            throw VariantCostnessException(arg0.getType());
        
        (arg0.as<ClassT>().*method_)
        (,
            arg1.as<NqParamT1>()
        );
        return Variant::Null;
        
    }

private:
    RetT (ClassT::*method_)
    (
        ParamT0,
        ParamT1
    );

    /// Whether the method is constant.
    bool constant_;
};


template
<
    class ClassT,
    typename RetT,
    typename ParamT0,
    typename ParamT1,
    typename ParamT2
>
class MethodImpl_3_Params : public Method
{
public: 
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type
        NqRetT;

    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT0>::Type>::Type
        NqParamT0;
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type
        NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type
        NqParamT2;
    
    MethodImpl_3_Params(const std::string& name,
        RetT (ClassT::*method)
        (
            ParamT0,
            ParamT1,
            ParamT2
        ),
        bool constant = false) :
        Method(getClass<ClassT>(), name),
        method_(method),
        constant_(constant)
    {
        addParameter(*new Parameter(getType<ClassT>())); 
        addParameter(*new Parameter(getType<ParamT0>()));
        addParameter(*new Parameter(getType<ParamT1>()));
        addParameter(*new Parameter(getType<ParamT2>()));
    }

    
    Function::ReturnMode getReturnMode() const
    {
        if (IsReference<RetT>::value)
        {
            if (IsConst<RetT>::value)
                return ConstReference;
            else
                return Reference;
        }
        else
            return Value;
    }
    
    bool isConst() const
    {
        return constant_;
    }
    
    
    Variant callImpl
    (   
        const Variant& arg0,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7
        
    ) const
    {
        ClassT& objRef = arg0.as<ClassT>();
        
        // cannot call a non constant method of a constant instance
        if (arg0.isConst() && !constant_)
            throw VariantCostnessException(arg0.getType());
        
        const NqRetT& returnValue = (arg0.as<ClassT>().*method_)
        (,
            arg1.as<NqParamT1>(),
            arg2.as<NqParamT2>()
        );
        return Variant(const_cast<NqRetT&>(returnValue),
                ReturnVariantFlags<RetT>::flags);
        
    }

private:
    RetT (ClassT::*method_)
    (
        ParamT0,
        ParamT1,
        ParamT2
    );

    /// Whether the method is constant.
    bool constant_;
};


template
<
    class ClassT,
    typename ParamT0,
    typename ParamT1,
    typename ParamT2
>
class MethodImpl_3_Params
<
    ClassT,
    void,
    ParamT0,
    ParamT1,
    ParamT2
> : public Method
{
public: 
        typedef void RetT;

    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT0>::Type>::Type
        NqParamT0;
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type
        NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type
        NqParamT2;
    
    MethodImpl_3_Params(const std::string& name,
        RetT (ClassT::*method)
        (
            ParamT0,
            ParamT1,
            ParamT2
        ),
        bool constant = false) :
        Method(getClass<ClassT>(), name),
        method_(method),
        constant_(constant)
    {
        addParameter(*new Parameter(getType<ClassT>())); 
        addParameter(*new Parameter(getType<ParamT0>()));
        addParameter(*new Parameter(getType<ParamT1>()));
        addParameter(*new Parameter(getType<ParamT2>()));
    }

    
    Function::ReturnMode getReturnMode() const
    {
        return None;
    }
    
    
    bool isConst() const
    {
        return constant_;
    }
    
    
    Variant callImpl
    (   
        const Variant& arg0,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7
        
    ) const
    {
        ClassT& objRef = arg0.as<ClassT>();
        
        // cannot call a non constant method of a constant instance
        if (arg0.isConst() && !constant_)
            throw VariantCostnessException(arg0.getType());
        
        (arg0.as<ClassT>().*method_)
        (,
            arg1.as<NqParamT1>(),
            arg2.as<NqParamT2>()
        );
        return Variant::Null;
        
    }

private:
    RetT (ClassT::*method_)
    (
        ParamT0,
        ParamT1,
        ParamT2
    );

    /// Whether the method is constant.
    bool constant_;
};


template
<
    class ClassT,
    typename RetT,
    typename ParamT0,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3
>
class MethodImpl_4_Params : public Method
{
public: 
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type
        NqRetT;

    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT0>::Type>::Type
        NqParamT0;
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type
        NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type
        NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type
        NqParamT3;
    
    MethodImpl_4_Params(const std::string& name,
        RetT (ClassT::*method)
        (
            ParamT0,
            ParamT1,
            ParamT2,
            ParamT3
        ),
        bool constant = false) :
        Method(getClass<ClassT>(), name),
        method_(method),
        constant_(constant)
    {
        addParameter(*new Parameter(getType<ClassT>())); 
        addParameter(*new Parameter(getType<ParamT0>()));
        addParameter(*new Parameter(getType<ParamT1>()));
        addParameter(*new Parameter(getType<ParamT2>()));
        addParameter(*new Parameter(getType<ParamT3>()));
    }

    
    Function::ReturnMode getReturnMode() const
    {
        if (IsReference<RetT>::value)
        {
            if (IsConst<RetT>::value)
                return ConstReference;
            else
                return Reference;
        }
        else
            return Value;
    }
    
    bool isConst() const
    {
        return constant_;
    }
    
    
    Variant callImpl
    (   
        const Variant& arg0,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7
        
    ) const
    {
        ClassT& objRef = arg0.as<ClassT>();
        
        // cannot call a non constant method of a constant instance
        if (arg0.isConst() && !constant_)
            throw VariantCostnessException(arg0.getType());
        
        const NqRetT& returnValue = (arg0.as<ClassT>().*method_)
        (,
            arg1.as<NqParamT1>(),
            arg2.as<NqParamT2>(),
            arg3.as<NqParamT3>()
        );
        return Variant(const_cast<NqRetT&>(returnValue),
                ReturnVariantFlags<RetT>::flags);
        
    }

private:
    RetT (ClassT::*method_)
    (
        ParamT0,
        ParamT1,
        ParamT2,
        ParamT3
    );

    /// Whether the method is constant.
    bool constant_;
};


template
<
    class ClassT,
    typename ParamT0,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3
>
class MethodImpl_4_Params
<
    ClassT,
    void,
    ParamT0,
    ParamT1,
    ParamT2,
    ParamT3
> : public Method
{
public: 
        typedef void RetT;

    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT0>::Type>::Type
        NqParamT0;
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type
        NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type
        NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type
        NqParamT3;
    
    MethodImpl_4_Params(const std::string& name,
        RetT (ClassT::*method)
        (
            ParamT0,
            ParamT1,
            ParamT2,
            ParamT3
        ),
        bool constant = false) :
        Method(getClass<ClassT>(), name),
        method_(method),
        constant_(constant)
    {
        addParameter(*new Parameter(getType<ClassT>())); 
        addParameter(*new Parameter(getType<ParamT0>()));
        addParameter(*new Parameter(getType<ParamT1>()));
        addParameter(*new Parameter(getType<ParamT2>()));
        addParameter(*new Parameter(getType<ParamT3>()));
    }

    
    Function::ReturnMode getReturnMode() const
    {
        return None;
    }
    
    
    bool isConst() const
    {
        return constant_;
    }
    
    
    Variant callImpl
    (   
        const Variant& arg0,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7
        
    ) const
    {
        ClassT& objRef = arg0.as<ClassT>();
        
        // cannot call a non constant method of a constant instance
        if (arg0.isConst() && !constant_)
            throw VariantCostnessException(arg0.getType());
        
        (arg0.as<ClassT>().*method_)
        (,
            arg1.as<NqParamT1>(),
            arg2.as<NqParamT2>(),
            arg3.as<NqParamT3>()
        );
        return Variant::Null;
        
    }

private:
    RetT (ClassT::*method_)
    (
        ParamT0,
        ParamT1,
        ParamT2,
        ParamT3
    );

    /// Whether the method is constant.
    bool constant_;
};


template
<
    class ClassT,
    typename RetT,
    typename ParamT0,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3,
    typename ParamT4
>
class MethodImpl_5_Params : public Method
{
public: 
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type
        NqRetT;

    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT0>::Type>::Type
        NqParamT0;
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type
        NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type
        NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type
        NqParamT3;
    typedef typename RemoveConst<typename RemoveReference<ParamT4>::Type>::Type
        NqParamT4;
    
    MethodImpl_5_Params(const std::string& name,
        RetT (ClassT::*method)
        (
            ParamT0,
            ParamT1,
            ParamT2,
            ParamT3,
            ParamT4
        ),
        bool constant = false) :
        Method(getClass<ClassT>(), name),
        method_(method),
        constant_(constant)
    {
        addParameter(*new Parameter(getType<ClassT>())); 
        addParameter(*new Parameter(getType<ParamT0>()));
        addParameter(*new Parameter(getType<ParamT1>()));
        addParameter(*new Parameter(getType<ParamT2>()));
        addParameter(*new Parameter(getType<ParamT3>()));
        addParameter(*new Parameter(getType<ParamT4>()));
    }

    
    Function::ReturnMode getReturnMode() const
    {
        if (IsReference<RetT>::value)
        {
            if (IsConst<RetT>::value)
                return ConstReference;
            else
                return Reference;
        }
        else
            return Value;
    }
    
    bool isConst() const
    {
        return constant_;
    }
    
    
    Variant callImpl
    (   
        const Variant& arg0,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7
        
    ) const
    {
        ClassT& objRef = arg0.as<ClassT>();
        
        // cannot call a non constant method of a constant instance
        if (arg0.isConst() && !constant_)
            throw VariantCostnessException(arg0.getType());
        
        const NqRetT& returnValue = (arg0.as<ClassT>().*method_)
        (,
            arg1.as<NqParamT1>(),
            arg2.as<NqParamT2>(),
            arg3.as<NqParamT3>(),
            arg4.as<NqParamT4>()
        );
        return Variant(const_cast<NqRetT&>(returnValue),
                ReturnVariantFlags<RetT>::flags);
        
    }

private:
    RetT (ClassT::*method_)
    (
        ParamT0,
        ParamT1,
        ParamT2,
        ParamT3,
        ParamT4
    );

    /// Whether the method is constant.
    bool constant_;
};


template
<
    class ClassT,
    typename ParamT0,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3,
    typename ParamT4
>
class MethodImpl_5_Params
<
    ClassT,
    void,
    ParamT0,
    ParamT1,
    ParamT2,
    ParamT3,
    ParamT4
> : public Method
{
public: 
        typedef void RetT;

    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT0>::Type>::Type
        NqParamT0;
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type
        NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type
        NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type
        NqParamT3;
    typedef typename RemoveConst<typename RemoveReference<ParamT4>::Type>::Type
        NqParamT4;
    
    MethodImpl_5_Params(const std::string& name,
        RetT (ClassT::*method)
        (
            ParamT0,
            ParamT1,
            ParamT2,
            ParamT3,
            ParamT4
        ),
        bool constant = false) :
        Method(getClass<ClassT>(), name),
        method_(method),
        constant_(constant)
    {
        addParameter(*new Parameter(getType<ClassT>())); 
        addParameter(*new Parameter(getType<ParamT0>()));
        addParameter(*new Parameter(getType<ParamT1>()));
        addParameter(*new Parameter(getType<ParamT2>()));
        addParameter(*new Parameter(getType<ParamT3>()));
        addParameter(*new Parameter(getType<ParamT4>()));
    }

    
    Function::ReturnMode getReturnMode() const
    {
        return None;
    }
    
    
    bool isConst() const
    {
        return constant_;
    }
    
    
    Variant callImpl
    (   
        const Variant& arg0,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7
        
    ) const
    {
        ClassT& objRef = arg0.as<ClassT>();
        
        // cannot call a non constant method of a constant instance
        if (arg0.isConst() && !constant_)
            throw VariantCostnessException(arg0.getType());
        
        (arg0.as<ClassT>().*method_)
        (,
            arg1.as<NqParamT1>(),
            arg2.as<NqParamT2>(),
            arg3.as<NqParamT3>(),
            arg4.as<NqParamT4>()
        );
        return Variant::Null;
        
    }

private:
    RetT (ClassT::*method_)
    (
        ParamT0,
        ParamT1,
        ParamT2,
        ParamT3,
        ParamT4
    );

    /// Whether the method is constant.
    bool constant_;
};


template
<
    class ClassT,
    typename RetT,
    typename ParamT0,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3,
    typename ParamT4,
    typename ParamT5
>
class MethodImpl_6_Params : public Method
{
public: 
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type
        NqRetT;

    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT0>::Type>::Type
        NqParamT0;
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type
        NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type
        NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type
        NqParamT3;
    typedef typename RemoveConst<typename RemoveReference<ParamT4>::Type>::Type
        NqParamT4;
    typedef typename RemoveConst<typename RemoveReference<ParamT5>::Type>::Type
        NqParamT5;
    
    MethodImpl_6_Params(const std::string& name,
        RetT (ClassT::*method)
        (
            ParamT0,
            ParamT1,
            ParamT2,
            ParamT3,
            ParamT4,
            ParamT5
        ),
        bool constant = false) :
        Method(getClass<ClassT>(), name),
        method_(method),
        constant_(constant)
    {
        addParameter(*new Parameter(getType<ClassT>())); 
        addParameter(*new Parameter(getType<ParamT0>()));
        addParameter(*new Parameter(getType<ParamT1>()));
        addParameter(*new Parameter(getType<ParamT2>()));
        addParameter(*new Parameter(getType<ParamT3>()));
        addParameter(*new Parameter(getType<ParamT4>()));
        addParameter(*new Parameter(getType<ParamT5>()));
    }

    
    Function::ReturnMode getReturnMode() const
    {
        if (IsReference<RetT>::value)
        {
            if (IsConst<RetT>::value)
                return ConstReference;
            else
                return Reference;
        }
        else
            return Value;
    }
    
    bool isConst() const
    {
        return constant_;
    }
    
    
    Variant callImpl
    (   
        const Variant& arg0,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7
        
    ) const
    {
        ClassT& objRef = arg0.as<ClassT>();
        
        // cannot call a non constant method of a constant instance
        if (arg0.isConst() && !constant_)
            throw VariantCostnessException(arg0.getType());
        
        const NqRetT& returnValue = (arg0.as<ClassT>().*method_)
        (,
            arg1.as<NqParamT1>(),
            arg2.as<NqParamT2>(),
            arg3.as<NqParamT3>(),
            arg4.as<NqParamT4>(),
            arg5.as<NqParamT5>()
        );
        return Variant(const_cast<NqRetT&>(returnValue),
                ReturnVariantFlags<RetT>::flags);
        
    }

private:
    RetT (ClassT::*method_)
    (
        ParamT0,
        ParamT1,
        ParamT2,
        ParamT3,
        ParamT4,
        ParamT5
    );

    /// Whether the method is constant.
    bool constant_;
};


template
<
    class ClassT,
    typename ParamT0,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3,
    typename ParamT4,
    typename ParamT5
>
class MethodImpl_6_Params
<
    ClassT,
    void,
    ParamT0,
    ParamT1,
    ParamT2,
    ParamT3,
    ParamT4,
    ParamT5
> : public Method
{
public: 
        typedef void RetT;

    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT0>::Type>::Type
        NqParamT0;
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type
        NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type
        NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type
        NqParamT3;
    typedef typename RemoveConst<typename RemoveReference<ParamT4>::Type>::Type
        NqParamT4;
    typedef typename RemoveConst<typename RemoveReference<ParamT5>::Type>::Type
        NqParamT5;
    
    MethodImpl_6_Params(const std::string& name,
        RetT (ClassT::*method)
        (
            ParamT0,
            ParamT1,
            ParamT2,
            ParamT3,
            ParamT4,
            ParamT5
        ),
        bool constant = false) :
        Method(getClass<ClassT>(), name),
        method_(method),
        constant_(constant)
    {
        addParameter(*new Parameter(getType<ClassT>())); 
        addParameter(*new Parameter(getType<ParamT0>()));
        addParameter(*new Parameter(getType<ParamT1>()));
        addParameter(*new Parameter(getType<ParamT2>()));
        addParameter(*new Parameter(getType<ParamT3>()));
        addParameter(*new Parameter(getType<ParamT4>()));
        addParameter(*new Parameter(getType<ParamT5>()));
    }

    
    Function::ReturnMode getReturnMode() const
    {
        return None;
    }
    
    
    bool isConst() const
    {
        return constant_;
    }
    
    
    Variant callImpl
    (   
        const Variant& arg0,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7
        
    ) const
    {
        ClassT& objRef = arg0.as<ClassT>();
        
        // cannot call a non constant method of a constant instance
        if (arg0.isConst() && !constant_)
            throw VariantCostnessException(arg0.getType());
        
        (arg0.as<ClassT>().*method_)
        (,
            arg1.as<NqParamT1>(),
            arg2.as<NqParamT2>(),
            arg3.as<NqParamT3>(),
            arg4.as<NqParamT4>(),
            arg5.as<NqParamT5>()
        );
        return Variant::Null;
        
    }

private:
    RetT (ClassT::*method_)
    (
        ParamT0,
        ParamT1,
        ParamT2,
        ParamT3,
        ParamT4,
        ParamT5
    );

    /// Whether the method is constant.
    bool constant_;
};


template
<
    class ClassT,
    typename RetT,
    typename ParamT0,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3,
    typename ParamT4,
    typename ParamT5,
    typename ParamT6
>
class MethodImpl_7_Params : public Method
{
public: 
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type
        NqRetT;

    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT0>::Type>::Type
        NqParamT0;
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type
        NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type
        NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type
        NqParamT3;
    typedef typename RemoveConst<typename RemoveReference<ParamT4>::Type>::Type
        NqParamT4;
    typedef typename RemoveConst<typename RemoveReference<ParamT5>::Type>::Type
        NqParamT5;
    typedef typename RemoveConst<typename RemoveReference<ParamT6>::Type>::Type
        NqParamT6;
    
    MethodImpl_7_Params(const std::string& name,
        RetT (ClassT::*method)
        (
            ParamT0,
            ParamT1,
            ParamT2,
            ParamT3,
            ParamT4,
            ParamT5,
            ParamT6
        ),
        bool constant = false) :
        Method(getClass<ClassT>(), name),
        method_(method),
        constant_(constant)
    {
        addParameter(*new Parameter(getType<ClassT>())); 
        addParameter(*new Parameter(getType<ParamT0>()));
        addParameter(*new Parameter(getType<ParamT1>()));
        addParameter(*new Parameter(getType<ParamT2>()));
        addParameter(*new Parameter(getType<ParamT3>()));
        addParameter(*new Parameter(getType<ParamT4>()));
        addParameter(*new Parameter(getType<ParamT5>()));
        addParameter(*new Parameter(getType<ParamT6>()));
    }

    
    Function::ReturnMode getReturnMode() const
    {
        if (IsReference<RetT>::value)
        {
            if (IsConst<RetT>::value)
                return ConstReference;
            else
                return Reference;
        }
        else
            return Value;
    }
    
    bool isConst() const
    {
        return constant_;
    }
    
    
    Variant callImpl
    (   
        const Variant& arg0,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7
        
    ) const
    {
        ClassT& objRef = arg0.as<ClassT>();
        
        // cannot call a non constant method of a constant instance
        if (arg0.isConst() && !constant_)
            throw VariantCostnessException(arg0.getType());
        
        const NqRetT& returnValue = (arg0.as<ClassT>().*method_)
        (,
            arg1.as<NqParamT1>(),
            arg2.as<NqParamT2>(),
            arg3.as<NqParamT3>(),
            arg4.as<NqParamT4>(),
            arg5.as<NqParamT5>(),
            arg6.as<NqParamT6>()
        );
        return Variant(const_cast<NqRetT&>(returnValue),
                ReturnVariantFlags<RetT>::flags);
        
    }

private:
    RetT (ClassT::*method_)
    (
        ParamT0,
        ParamT1,
        ParamT2,
        ParamT3,
        ParamT4,
        ParamT5,
        ParamT6
    );

    /// Whether the method is constant.
    bool constant_;
};


template
<
    class ClassT,
    typename ParamT0,
    typename ParamT1,
    typename ParamT2,
    typename ParamT3,
    typename ParamT4,
    typename ParamT5,
    typename ParamT6
>
class MethodImpl_7_Params
<
    ClassT,
    void,
    ParamT0,
    ParamT1,
    ParamT2,
    ParamT3,
    ParamT4,
    ParamT5,
    ParamT6
> : public Method
{
public: 
        typedef void RetT;

    /// type of the arguments without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<ParamT0>::Type>::Type
        NqParamT0;
    typedef typename RemoveConst<typename RemoveReference<ParamT1>::Type>::Type
        NqParamT1;
    typedef typename RemoveConst<typename RemoveReference<ParamT2>::Type>::Type
        NqParamT2;
    typedef typename RemoveConst<typename RemoveReference<ParamT3>::Type>::Type
        NqParamT3;
    typedef typename RemoveConst<typename RemoveReference<ParamT4>::Type>::Type
        NqParamT4;
    typedef typename RemoveConst<typename RemoveReference<ParamT5>::Type>::Type
        NqParamT5;
    typedef typename RemoveConst<typename RemoveReference<ParamT6>::Type>::Type
        NqParamT6;
    
    MethodImpl_7_Params(const std::string& name,
        RetT (ClassT::*method)
        (
            ParamT0,
            ParamT1,
            ParamT2,
            ParamT3,
            ParamT4,
            ParamT5,
            ParamT6
        ),
        bool constant = false) :
        Method(getClass<ClassT>(), name),
        method_(method),
        constant_(constant)
    {
        addParameter(*new Parameter(getType<ClassT>())); 
        addParameter(*new Parameter(getType<ParamT0>()));
        addParameter(*new Parameter(getType<ParamT1>()));
        addParameter(*new Parameter(getType<ParamT2>()));
        addParameter(*new Parameter(getType<ParamT3>()));
        addParameter(*new Parameter(getType<ParamT4>()));
        addParameter(*new Parameter(getType<ParamT5>()));
        addParameter(*new Parameter(getType<ParamT6>()));
    }

    
    Function::ReturnMode getReturnMode() const
    {
        return None;
    }
    
    
    bool isConst() const
    {
        return constant_;
    }
    
    
    Variant callImpl
    (   
        const Variant& arg0,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7
        
    ) const
    {
        ClassT& objRef = arg0.as<ClassT>();
        
        // cannot call a non constant method of a constant instance
        if (arg0.isConst() && !constant_)
            throw VariantCostnessException(arg0.getType());
        
        (arg0.as<ClassT>().*method_)
        (,
            arg1.as<NqParamT1>(),
            arg2.as<NqParamT2>(),
            arg3.as<NqParamT3>(),
            arg4.as<NqParamT4>(),
            arg5.as<NqParamT5>(),
            arg6.as<NqParamT6>()
        );
        return Variant::Null;
        
    }

private:
    RetT (ClassT::*method_)
    (
        ParamT0,
        ParamT1,
        ParamT2,
        ParamT3,
        ParamT4,
        ParamT5,
        ParamT6
    );

    /// Whether the method is constant.
    bool constant_;
};



} // namespace extmr

#endif /* EXTMR_METHODIMPL_HPP */