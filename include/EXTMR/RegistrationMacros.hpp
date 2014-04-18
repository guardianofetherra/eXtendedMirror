/******************************************************************************      
 *      Extended Mirror: RegistrationMacros.hpp                               *
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


#ifndef EXTMR_MACROS_HPP
#define	EXTMR_MACROS_HPP


/**
 * \def EXTMR_ENABLE_PRIMITIVE(_primitive_type_)
 * Specialize the GetTypeName class for the \a _primitive_type_
 */
#define EXTMR_ENABLE_PRIMITIVE(_primitive_type_)                               \
namespace extmr{                                                               \
                                                                               \
template<>                                                                     \
struct GetTypeName<_primitive_type_>                                           \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        return #_primitive_type_;                                              \
    }                                                                          \
};                                                                             \
                                                                               \
} // namespace extmr


/**
 * \def EXTMR_ENABLE_CLASS(_class_)
 * 
 * GetTypeName template struct is specialized in order to define the right
 * name and category for the type.
 * This information is used during the registration phase of this type.
 * 
 * Enables reflection for the class \a _class_.
 * Place this macro in the same header of the \a _class_ declaration,
 * after the class declaration.
 */
#define EXTMR_ENABLE_CLASS(_class_)                                            \
namespace extmr{                                                               \
                                                                               \
template<>                                                                     \
struct GetTypeName<_class_ >                                                   \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        return #_class_;                                                       \
    }                                                                          \
};                                                                             \
                                                                               \
template<>                                                                     \
struct BuildClass<_class_>                                                     \
{                                                                              \
    typedef _class_ ClassT;                                                    \
    void operator()();                                                         \
};                                                                             \
                                                                               \
template<>                                                                     \
struct CreateType<_class_>                                                     \
{                                                                              \
    Type* operator()()                                                         \
    {                                                                          \
        return createClass<_class_ >();                                        \
    }                                                                          \
};                                                                             \
                                                                               \
} // namespace extmr


#define EXTMR_ASSUME_NON_COPYABLE(_class_)                                     \
namespace extmr{                                                               \
                                                                               \
template<>                                                                     \
class CopyConstructorImpl<_class_ > : public CopyConstructor                   \
{                                                                              \
public:                                                                        \
    CopyConstructorImpl(const Class& owner) : CopyConstructor(owner) {};       \
};                                                                             \
                                                                               \
} //namespace extmr


#define EXTMR_ASSUME_NON_INSTANTIABLE(_class_)                                 \
namespace extmr{                                                               \
                                                                               \
template<>                                                                     \
class ConstructorImpl<_class_ > : public Constructor                           \
{                                                                              \
public:                                                                        \
    ConstructorImpl(const Class& owner) : Constructor(owner) {};               \
};                                                                             \
                                                                               \
} //namespace extmr


#define EXTMR_ASSUME_NON_ASSIGNABLE(_class_)                                   \
namespace extmr{                                                               \
                                                                               \
template<>                                                                     \
class AssignOperatorImpl<_class_ > : public AssignOperator                     \
{                                                                              \
public:                                                                        \
    AssignOperatorImpl(const Class& owner) : AssignOperator(owner) {};         \
};                                                                             \
                                                                               \
} //namespace extmr


#define EXTMR_ASSUME_NON_DESTRUCTIBLE(_class_)                                 \
namespace extmr{                                                               \
                                                                               \
template<>                                                                     \
class DestructorImpl<_class_ > : public Constructor                            \
{                                                                              \
public:                                                                        \
    DestructorImpl(const Class& owner) : DestructorImpl(owner) {};             \
};                                                                             \
                                                                               \
} //namespace extmr


#define EXTMR_ASSUME_ABSTRACT(_class_)                                         \
namespace extmr{                                                               \
                                                                               \
template<>                                                                     \
struct IsAbstract<_class_ > : public TrueType{};                               \
                                                                               \
} /*namespace extmr*/                                                          \
EXTMR_ASSUME_NON_INSTANTIABLE(_class_)                                         \
EXTMR_ASSUME_NON_ASSIGNABLE(_class_)                                           \
EXTMR_ASSUME_NON_COPYABLE(_class_)


#define EXTMR_BUILD_CLASS(...) void extmr::BuildClass<__VA_ARGS__>::operator()()


/**
 * \def EXTMR_AUTOREG(_class_)
 * 
 * Ensure the class will be registered at program startup, or when the shared
 * object is loaded dynamically, with no extra code.
 * \a relfected_class is the class to be registered.
 */
#define EXTMR_AUTOREG(_class_)                                                 \
template class extmr::AutoRegisterer<_class_ >;


#define EXTMR_TEMPLATE_PARAM_MAX 4

/**
 * \def EXTMR_ENABLE_TEMPLATE_1(_template_)
 * 
 * Use to enable instances of template class to be registered as such.
 * 
 * Works only with one type parameter template classes.
 * After this macro, specify the body of the building function.
 */
#define EXTMR_ENABLE_TEMPLATE_1(_template_)                                    \
namespace extmr{                                                               \
                                                                               \
template<typename T1>                                                          \
struct GetTypeName<_template_<T1> >                                            \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        std::string str = std::string(#_template_) + "<";                      \
        str += GetTypeName<T1>()();                                            \
        if (str[str.length() - 1] == '>')                                      \
        {                                                                      \
            str += " ";                                                        \
        }                                                                      \
        str += ">";                                                            \
        return str;                                                            \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1>                                                          \
struct GetTemplateName<_template_<T1> >                                        \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        return #_template_;                                                    \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1>                                                          \
struct GetTemplateArgs<_template_<T1> >                                        \
{                                                                              \
    Const_Type_Vector operator()()                                             \
    {                                                                          \
        Const_Type_Vector templateArgs;                                        \
        TypeRegister& typeReg = TypeRegister::getSingleton();                  \
        templateArgs.push_back(&typeReg.registerType<T1>());                   \
        return templateArgs;                                                   \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1>                                                          \
struct BuildClass<_template_<T1> >                                             \
{                                                                              \
    typedef _template_<T1> ClassT;                                             \
    void operator()();                                                         \
};                                                                             \
                                                                               \
template<typename T1>                                                          \
struct CreateType<_template_<T1> >                                             \
{                                                                              \
    Type* operator()()                                                         \
    {                                                                          \
        return createCompoundClass<_template_<T1> >();                         \
    }                                                                          \
};                                                                             \
                                                                               \
} // namespace extmr


/**
 * \def EXTMR_ENABLE_TEMPLATE_2(_template_)
 * 
 * Use to enable instances of template class to be registered as such.
 * 
 * Works only with two type parameters template classes.
 * After this macro, specify the body of the building function.
 */
#define EXTMR_ENABLE_TEMPLATE_2(_template_)                                    \
namespace extmr{                                                               \
                                                                               \
template<typename T1, typename T2>                                             \
struct GetTypeName<_template_<T1, T2> >                                        \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        std::string str = std::string(#_template_) + "<";                      \
        str += GetTypeName<T1>()();                                            \
        str += ", " + GetTypeName<T2>()();                                     \
        if (str[str.length() - 1] == '>')                                      \
        {                                                                      \
            str += " ";                                                        \
        }                                                                      \
        str += ">";                                                            \
        return str;                                                            \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1, typename T2>                                             \
struct GetTemplateName<_template_<T1, T2> >                                    \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        return #_template_;                                                    \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1, typename T2>                                             \
struct GetTemplateArgs<_template_<T1, T2> >                                    \
{                                                                              \
    Const_Type_Vector operator()()                                             \
    {                                                                          \
        Const_Type_Vector templateArgs;                                        \
        TypeRegister& typeReg = TypeRegister::getSingleton();                  \
        templateArgs.push_back(&typeReg.registerType<T1>());                   \
        templateArgs.push_back(&typeReg.registerType<T2>());                   \
        return templateArgs;                                                   \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1,  typename T2>                                            \
struct BuildClass<_template_<T1, T2> >                                         \
{                                                                              \
    typedef _template_<T1, T2> ClassT;                                         \
    void operator()();                                                         \
};                                                                             \
                                                                               \
template<typename T1, typename T2>                                             \
struct CreateType<_template_<T1, T2> >                                         \
{                                                                              \
    Type* operator()()                                                         \
    {                                                                          \
        return createCompoundClass<_template_<T1, T2> >();                     \
    }                                                                          \
};                                                                             \
                                                                               \
} // namespace extmr


/**
 * \def EXTMR_ENABLE_TEMPLATE_3(_template_)
 * 
 * Use to enable instances of template class to be registered as such.
 * 
 * Works only with three type parameters template classes.
 * After this macro, specify the body of the building function.
 */
#define EXTMR_ENABLE_TEMPLATE_3(_template_)                                    \
namespace extmr{                                                               \
                                                                               \
template<typename T1,  typename T2,  typename T3>                              \
struct GetTypeName<_template_<T1, T2, T3> >                                    \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        std::string str = std::string(#_template_) + "<";                      \
        str += GetTypeName<T1>()() + ", ";                                     \
        str += GetTypeName<T2>()() + ", ";                                     \
        str += GetTypeName<T3>()();                                            \
        if (str[str.length() - 1] == '>')                                      \
        {                                                                      \
            str += " ";                                                        \
        }                                                                      \
        str += ">";                                                            \
        return str;                                                            \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1, typename T2, typename T3>                                \
struct GetTemplateName<_template_<T1, T2, T3> >                                \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        return #_template_;                                                    \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1, typename T2, typename T3>                                \
struct GetTemplateArgs<_template_<T1, T2, T3> >                                \
{                                                                              \
    Const_Type_Vector operator()()                                             \
    {                                                                          \
        Const_Type_Vector templateArgs;                                        \
        TypeRegister& typeReg = TypeRegister::getSingleton();                  \
        templateArgs.push_back(&typeReg.registerType<T1>());                   \
        templateArgs.push_back(&typeReg.registerType<T2>());                   \
        templateArgs.push_back(&typeReg.registerType<T3>());                   \
        return templateArgs;                                                   \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1,  typename T2,  typename T3>                              \
struct BuildClass<_template_<T1, T2, T3> >                                     \
{                                                                              \
    typedef _template_<T1, T2, T3> ClassT;                                     \
    void operator()();                                                         \
};                                                                             \
                                                                               \
template<typename T1, typename T2, typename T3>                                \
struct CreateType<_template_<T1, T2, T3> >                                     \
{                                                                              \
    Type* operator()()                                                         \
    {                                                                          \
        return createCompoundClass<_template_<T1, T2, T3> >();                 \
    }                                                                          \
};                                                                             \
                                                                               \
                                                                               \
} // namespace extmr


/**
 * \def EXTMR_ENABLE_TEMPLATE_4(_template_)
 * 
 * Use to enable instances of template class to be registered as such.
 * 
 * Works only with four type parameters template classes.
 * After this macro, specify the body of the building function.
 */
#define EXTMR_ENABLE_TEMPLATE_4(_template_)                                    \
namespace extmr{                                                               \
                                                                               \
template<typename T1,  typename T2,  typename T3,  typename T4>                \
struct GetTypeName<_template_<T1, T2, T3, T4> >                                \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        std::string str = std::string(#_template_) + "<";                      \
        str += GetTypeName<T1>()() + ", ";                                     \
        str += GetTypeName<T2>()() + ", ";                                     \
        str += GetTypeName<T3>()() + ", ";                                     \
        str += GetTypeName<T4>()();                                            \
        if (str[str.length() - 1] == '>')                                      \
        {                                                                      \
            str += " ";                                                        \
        }                                                                      \
        str += ">";                                                            \
        return str;                                                            \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1, typename T2, typename T3, typename T4>                   \
struct GetTemplateName<_template_<T1, T2, T3, T4> >                            \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        return #_template_;                                                    \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1, typename T2, typename T3, typename T4>                   \
struct GetTemplateArgs<_template_<T1, T2, T3, T4> >                            \
{                                                                              \
    Const_Type_Vector operator()()                                             \
    {                                                                          \
        Const_Type_Vector templateArgs;                                        \
        TypeRegister& typeReg = TypeRegister::getSingleton();                  \
        templateArgs.push_back(&typeReg.registerType<T1>());                   \
        templateArgs.push_back(&typeReg.registerType<T2>());                   \
        templateArgs.push_back(&typeReg.registerType<T3>());                   \
        templateArgs.push_back(&typeReg.registerType<T4>());                   \
        return templateArgs;                                                   \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1,  typename T2,  typename T3,  typename T4>                \
struct BuildClass<_template_<T1, T2, T3, T4> >                                 \
{                                                                              \
    typedef _template_<T1, T2, T3, T4> ClassT;                                 \
    void operator()();                                                         \
};                                                                             \
                                                                               \
template<typename T1, typename T2, typename T3, typename T4>                   \
struct CreateType<_template_<T1, T2, T3, T4> >                                 \
{                                                                              \
    Type* operator()()                                                         \
    {                                                                          \
        return createCompoundClass<_template_<T1, T2, T3, T4> >();             \
    }                                                                          \
};                                                                             \
                                                                               \
} // namespace extmr


#endif	/* EXTMR_MACROS_HPP */

