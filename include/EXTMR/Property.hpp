#ifndef EXTMR_PROPERTYDESC_HPP
#define EXTMR_PROPERTYDESC_HPP

namespace extmr{

class Type;
class Variant;

/**
 * Describes a property of a class. A property is an attribute that has been registered
 * through the reflection mechanism. Note that a Property is related to the class and not
 * to the object (instances).
 */
class Property
{
public:
    
    /// Some property flags.
    enum PropertyFlags
    {
        /// Whether the property is settable or not.
        Settable = 1,

        /// Whether the property interface should be considered part of the host class interface.
        Encapsulated = 2,

        /// Whether the encapsulated property is retrieved by pointer or reference.
        EncasulatedPtr = 4,

    };
    
    /**
     * Basic constructor for initialization.
     * 
     * @param name The property name.
     */
    Property(const std::string& name = "");
    
    /**
     * Get the name of the property.
     * 
     * @return The name of the property.
     */
    const std::string& getName() const;
    
    /**
     * Get the Type of the property type.
     * 
     * @return The Type.
     */
    const Type& getType() const;
    
    /**
     * Get the flags of this property.
     * 
     * @return The flags.
     */
    virtual char getFlags() const;
    
    /**
     * Set the property flags.
     * A reference to the Property is returned to allow a method chain call.
     * 
     * @param flags The flags.
     * @return This Property.
     */
    virtual Property& setFlags(char flags);
    
        /**
     * Ask for the property minimum allowed value.
     * NOTE: this method makes sense only if the property is of a numerical type.
     * 
     * @return the minimum value.
     */
    virtual double getMinValue() const;
    
    /**
     * Set the property minimum allowed value.
     * A reference to the Property is returned to allow a method chain call.
     * NOTE: this method makes sense only if the property is of a numerical type.
     * 
     * @param minValue the mininum allowe value.
     * @return This Property.
     */
    virtual Property& setMinValue(double minValue);
    /**
     * Ask for the property maximum allowed value.
     * NOTE: this method makes sense only if the property is of a numerical type.
     * 
     * @return the maximum value.
     */
    virtual double getMaxValue() const;
    
    /**
     * Set the property maximum allowed value.
     * A reference to the Property is returned to allow a method chain call.
     * NOTE: this method makes sense only if the property is of a numerical type.
     * 
     * @param maxValue the maximum allowed value.
     * @return This Property.
     */
    virtual Property& setMaxValue(double maxValue);
    
    /**
     * Ask whether the property data is retrived by a non const reference.
     * 
     * @return True if the property data is retrieved by a non const reference.
     */
    virtual bool getGetByNcRef();
    
    /**
     * Ask whether the property data is set by a non const reference.
     * 
     * @return True if the property data is set by reference.
     */
    virtual bool getSetByNcRef();
    
    /**
     * Get the data through variant objects.
     * 
     * @param objPtr Pointer to an object which type has this property. 
     * @return Variant containing the property data.
     */
    virtual Variant getData(const Variant& objPtr) const;
    
    /**
     * Set the data through variant objects.
     * 
     * @param objPtr Pointer to an object which type has this property. 
     * @param data Variant containing the data to be set.
     */
    virtual void setData(const Variant& objPtr, const Variant& data) const {};
    
    /// This function object is used to compare two pointers to this class by the name of the pointed objects.
    typedef ::PtrCmpByName<Property> PtrCmp;
    
protected:
    
    /// The property name.
    std::string name;
    
    /// The property Type.
    const Type* type;
    
    /// PtrCmpByName must be a friend of this class to access the name attribute.
    friend class ::PtrCmpByName<Property>;
    
    /// Property flags.
    char flags;
};

} // namespace extmr

#endif // EXTMR_PROPERTYDESC_HPP
