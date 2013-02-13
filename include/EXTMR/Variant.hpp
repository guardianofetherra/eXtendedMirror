/* 
 * File:   Variant.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on September 3, 2012, 12.04
 */

#ifndef EXTMR_VARIANT_HPP
#define	EXTMR_VARIANT_HPP

namespace extmr{

class Type;

/**
 * This class can store data from each type that is registrable or already registered
 * within the type register.
 * For store we mean that data can be both copied and stored or just referenced. 
 * In the second case is up to the programmer to ensure the data will remain valid and to deallocate
 * this data after the variant object is destroyed.
 * The copy construct has in any case the effect to copy the content of the variant so that
 * changes on the data of the newly created variant never affect the original variant.
 */
class Variant
{
public:
    /**
     * Some variant flags.
     */
    enum Flags
    {
        /// The variant data is a reference to external data.
        Reference = 1,
        
        /// The variant holds constant data
        Const = 2,
        
        /// When this variant is copied into another one, data will be referenced.
        CopyByRef = 4
    };
    
    /**
     * Build an invalid variant.
     */
    Variant();
    
    /**
     * Construct a variant from the given object.
     * The object data is copied with its class copy constructor and the data is stored
     * internally.
     * 
     * @param data
     */
    template<typename T>
    Variant(const T& data);
    
    /**
     * Construct a variant from the given object.
     * By default the object is copied with its class copy constructor and the data is stored
     * internally.
     * If you want to change this behavior specify the second parameter.
     * 
     * @param data The object from which to take the data form.
     * @param flags The variant flags.
     */
    template<typename T>
    Variant(T& data, char flags);
    
    /**
     * Get the Type for the data.
     * 
     * @return The Type.
     */
    const Type& getType() const
    {
        return *type_;
    }
    
    /**
     * Check if the variant is a valid one.
     * 
     * @return True if the variant is valid, false otherwise.
     */
    bool isValid();
    
    /**
     * Ask if this variant data is a reference to an external data.
     * 
     * @return true if the variant data is a reference, false otherwise.
     */
    bool isReference() const
    {
        return flags & Reference;
    }
    
    /**
     * Ask if this variant holds constant data.
     * 
     * @return true if the variant holds constant data, false otherwise.
     */
    bool isConst() const
    {
        return flags & Const;
    }
    
    /**
     * Ask if this variant holds a pointer to constant data.
     * 
     * @return true if the variant holds a pointer to constant data, false otherwise.
     */
    bool isPointedConst() const
    {
        return flags & PointerToConst;
    }
    
    /**
     * Set the variant data to be constant, after a variant has been marked as constant,
     * the constness cannot be removed anymore.
     */
    void setConst()
    {
        flags |= Const;
    }
    
    /**
     * Set the variant data to be referenced when the variant is copied with the copy constructor.
     * 
     * @param value Whether data of the copied object should be a reference to this one.
     */
    void setCopyByRef(bool value = true)
    {
        if (value) flags |= CopyByRef;
        else flags &= ~CopyByRef;
    }
    
    /**
     * Cast operator, get the data of the variant by reference.
     * This method only works if the template parameter
     * is either the same of the contained data or, given that the
     * data is an object of a class or a pointer
     * to an object of a class, then the specified type
     * is respectively a base class of the that class or a pointer to
     * a base class of that class.
     * In other words this would only work if a reinterpret_cast<> from the pointer
     * to the contained data type to a pointer of the target type would lead to a meaningful result.
     * In all other cases a BadType exception arises.
     * 
     * @return The variant data.
     */
    template<typename T>
    operator T&() const;
    
    /**
     * This is just a shortcut to static_cast<T>(*this)
     * 
     * @return The variant data.
     */
    template<typename T>
    T& to() const;
    
    /**
     * Copy constructor. The data is copied through the copy constructor.
     * 
     * @param orig The variant to copy.
     */
    Variant(const Variant& orig);
    
#ifdef EXTMR_STDSTRING_FACILITY
    
    /**
     * Constructor facility for strings. A c string is converted
     * into an std::string.
     * 
     * @param str A c string.
     */
    Variant(const char* str) : Variant(string(str))
    {
    }
    
#endif
    
    /**
     * Operator for assignment.
     * The data is copied through the type assign operator.
     * If the data of the lvalue variant has not yet been allocated is then allocated
     * through the standard constructor. It types are different, then the lvalue variant
     * data is first deallocated, and then types are set the same.
     * 
     * @param other The other variant object.
     * @return The variant
     */
    const Variant& operator=(const Variant& other);
    
    /**
     * Operator for assignment.
     * The data of the rvalue is stored into the variant after it has been copied
     * through the assignment operator of the specified type.
     * If current type of the variant is different form that of the rvalue then
     * the previous data is deallocated with the destructor and a new object of the
     * new type is allocated with its default constructor.
     * The assignment is then performed.
     * 
     * @param rvalue The rvalue object
     * @return A reference to the rvalue
     */
    template<typename T>
    const T& operator=(const T& rvalue);
    
    /**
     * Destructor. The data is deallocated calling the destructor.
     */
    virtual ~Variant();
    
private:
    /**
     * Flags that don't have to passed to the constructor.
     */
    enum
    {
        /// The variant data is a pointer to a constant.
        PointerToConst = 8
    };
    
    /**
     * Determine if a reinterpret_cast from a reference to the original type
     * to a reference to the target type would lead to a meaningful result.
     * 
     * @param type The original type.
     * @param targettype The target type.
     * @return true if the types are compatible for reinterpret_cast.
     */
    static bool canReinterpret(const Type& type, const Type& targetType);
    
    /// Pointer to the data.
    void* data_;
    
    /// Pointer to the Type of the data.
    const Type* type_;
    
    /// This field store some variant flags.
    char flags;
    
    /// The actual construction of the object is delegated to this function object.
    template<typename T>
    friend class VariantInitializer;
};

} // namespace extmr

#endif	/* VARIANT_HPP */

