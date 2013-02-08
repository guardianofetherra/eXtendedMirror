/* 
 * File:   TypeTraits.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 20 August 2012, 15.30
 */

#ifndef EXTMR_TYPETRAITS_HPP
#define	EXTMR_TYPETRAITS_HPP

#include <sstream>

namespace extmr{


/**
 * Checks whether or not a given type is constant.
 * The value field evaluate to true if so, to false otherwise.
 */
template<typename T>
struct IsConst
{
    static const bool value = false;
};

template<typename T>
struct IsConst<const T>
{
    static const bool value = true;
};

template<typename T>
struct IsConst<const T&>
{
    static const bool value = true;
};

/**
 * Checks whether or not a given type is a reference.
 * The value field evaluate to true if so, to false otherwise.
 */
template<typename T>
struct IsReference
{
    static const bool value = false;
};

template<typename T>
struct IsReference<T&>
{
    static const bool value = true;
};

/**
 * Checks whether or not a given type is a reference.
 * The value field evaluate to true if so, to false otherwise.
 */
template<typename T>
struct IsArray
{
    static const bool value = false;
};

template<typename T, std::size_t size>
struct IsArray<T[size]>
{
    static const bool value = true;
};

/**
 * Checks whether or not a given type is a non constant reference.
 */
template<typename T>
struct IsNonConstReference
{
    static const bool value = IsReference<T>::value && ! IsConst<T>::value;
};

/**
 * Remove constness from a type.
 */
template<typename T>
struct RemoveConst
{
    typedef T Type;
};

template<typename T>
struct RemoveConst<const T>
{
    typedef typename RemoveConst<T>::Type Type;
};

/**
 * Removes all the CV qualifiers that appears in the type name.
 */
template<typename T>
struct RemoveAllCVQualifiers
{
    typedef T Type;
};

template<typename T>
struct RemoveAllCVQualifiers<const T>
{
    typedef typename RemoveAllCVQualifiers<T>::Type Type;
};

template<typename T>
struct RemoveAllCVQualifiers<const T*>
{
    typedef typename RemoveAllCVQualifiers<T*>::Type Type;
};

template<typename T>
struct RemoveAllCVQualifiers<const T&>
{
    typedef typename RemoveAllCVQualifiers<T&>::Type Type;
};

/**
 * Remove the pointer from the type.
 */
template<typename T>
struct RemovePointer
{
    typedef T Type;
};

template<typename T>
struct RemovePointer<T*>
{
    typedef T Type;
};

/**
 * Remove the reference from the type.
 */
template<typename T>
struct RemoveReference
{
    typedef T Type;
};

template<typename T>
struct RemoveReference<T&>
{
    typedef T Type;
};

/**
 * If T is the type ElementType[size_1][size_2]...[size_n] then Type evaluate to
 * ElementType[size_2][size_3]...[size_n].
 * If T is not an array then Type evaluate to T.
 */
template<typename T>
struct RemoveExtent
{
    typedef T Type;
};

template<typename T, std::size_t size>
struct RemoveExtent<T[size]>
{
    typedef T Type;
};

/**
 * If T is the type ElementType[size_1][size_2]...[size_n] then Type evaluate to
 * ElementType.
 * If T is not an array then Type evaluate to T.
 */
template<typename T>
struct RemoveAllExtents
{
    typedef T Type;
};

template<typename T, std::size_t size>
struct RemoveAllExtents<T[size]>
{
    typedef typename RemoveAllExtents<T>::Type Type;
};

/**
 * The getSizeSignature method returns a string in the form [size_1][size_2]...[size_n]
 * if type T is an array in the form T[size_1][size_2]...[size_n],
 * an empty string if T is not an array.
 */
template<typename T>
struct ArraySizeSignature
{
    static std::string getSizeSignature()
    {
        return "";
    }
};

template<typename T, std::size_t size>
struct ArraySizeSignature<T[size]>
{
    static std::string getSizeSignature()
    {
        std::stringstream sstream;
        sstream << "[" << size << "]" << ArraySizeSignature<T>::getSizeSignature();
        return sstream.str();
    }
};

/**
 * Given the [size_1][size_2]...[size_n] array the size member
 * evaluate to size_1 or to zero if T is not an array.
 */
template<typename T>
struct ArraySize
{
    static const std::size_t size = 0;
};

template<typename T, std::size_t _size>
struct ArraySize<T[_size]>
{
    static const std::size_t size = _size;
};


/**
 * The inner type Type is the same of T if T is a numerical type, another numerical
 * type if T is not a numerical type.
 */
template<typename T>
struct ToNumerical
{
    typedef char Type;
};

#define EXTMR_TONUMERICAL_SPECIALIZE(type)\
template<>\
struct ToNumerical<type>\
{\
    typedef type Type;\
};

// Specialize the type recognizer for each primitive type
EXTMR_TONUMERICAL_SPECIALIZE(char);
EXTMR_TONUMERICAL_SPECIALIZE(wchar_t);
EXTMR_TONUMERICAL_SPECIALIZE(short);
EXTMR_TONUMERICAL_SPECIALIZE(int);
EXTMR_TONUMERICAL_SPECIALIZE(long);
EXTMR_TONUMERICAL_SPECIALIZE(float);
EXTMR_TONUMERICAL_SPECIALIZE(double);
EXTMR_TONUMERICAL_SPECIALIZE(uchar);
EXTMR_TONUMERICAL_SPECIALIZE(ushort);
EXTMR_TONUMERICAL_SPECIALIZE(uint);
EXTMR_TONUMERICAL_SPECIALIZE(ulong);

} // namespace extmr

#endif	/* EXTMR_TYPETRAITS_HPP */

