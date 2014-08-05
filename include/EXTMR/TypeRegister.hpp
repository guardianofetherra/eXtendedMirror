/******************************************************************************      
 *      Extended Mirror: TypeRegister.hpp                                     *
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


#ifndef EXTMR_TYPEEXTMR_HPP
#define EXTMR_TYPEEXTMR_HPP

namespace extmr{


/**
 * Holds all the type descriptors of the registered types and provide
 * methods to access or manipulate them. This class is meant to be singleton
 * so there is no public constructor. Instead the instance can be safely
 * retrieved through the getTypeReg method in constructors of static objects
 * or you can simply use the global variable typeReg to access the type register
 * from any other point in your program.
 */
class TypeRegister
{
public:
    /**
     * Start the registration mechanism for the given type.
     * Registration macros will handle automatic type registration and call this
     * method for you.
     * 
     * @return The registered type.
     */
    template<typename T> const Type& registerType();
    
    /**
     * The same of registerType() except this is only valid for class types and
     * return a Class instead of a Type.
     * 
     * @return The registered type.
     */
    template<typename T> const Class& registerClass();
    
    /**
     * Remove a type from the register.
     * 
     * @param typeName The typeName.
     */
     void unregisterType(const std::string& typeName);
     
    /**
     * Remove a type from the register.
     * 
     * @param cppType The type_info struct of the type.
     */
     void unregisterType(const std::type_info& cppType);
    
    /**
     * Set a function that is called whenever a type is registered within the
     * type register and the registered type is passed to this function.
     * 
     * @param callBackFnc
     */
    void setRegCallBack(void (*callBackFnc)(const Type&));
    
    /**
     * Used to safely retrieve the type register singleton when the
     * program starts up (before the main function execution) preventing the
     * static initialization order fiasco.
     * 
     * @return The type register.
     */
    static TypeRegister& getSingleton();
    
private:

     /*
      * Singleton restrictions.
      */
    TypeRegister();
    
    TypeRegister(const TypeRegister&);
    TypeRegister& operator=(const TypeRegister&);
    
    ~ TypeRegister();
    
    /**
     * This method is called by registerType, after the type qualifiers are
     * removed from the type.
     * 
     * @return the registered type.
     */
    template<typename T> Type& registerType_();
    
    /**
     * Add a template to the template set.
     * 
     * @param tempjate The template to add.
     */
    void addTemplate(const Template& tempjate);
    
    /**
     * Return the function pointer of the callback function to call after each
     * type registration.
     * 
     * @return The callback function pointer.
     */
    static void (*getRegCallBack())(const Type&);

    // A set containing the pointers to all the registered type descriptors
    //sorted by type name.
    Type_Set_ByName typesByName_;
    
    // A set containing the pointers to all the registered type descriptors
    //sorted by type_info struct order.
    Type_SetById typesById_;
    
    // A set containing the pointers to all the registered class descriptors
    // sorted by type_info struct order.
    Class_SetById classesById_;
    
    // A set containing the template descriptors of all the instantiated
    //templates.
    Const_Template_Set templates_;
    
    // this function needs to add Templates to the register
    template<typename T>
    friend Type* createCompoundClass();
};

} // namespace extmr

#endif // TYPEEXTMR_HPP
