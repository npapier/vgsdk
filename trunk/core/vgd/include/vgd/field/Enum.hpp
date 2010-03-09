// VGSDK - Copyright (C) 2006, 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_ENUM_HPP
#define _VGD_FIELD_ENUM_HPP

#include <utility>
#include <vector>
#include "vgd/field/containers.hpp"



namespace vgd
{

namespace field
{

/**
 * @brief Definition of an enumeration type
 *
 * @todo virtual getValues(), getStrs() ...
 * @todo call isValid() in constructors
 * @todo getDefaultValue()
 */
struct VGD_API Enum
{
	/**
	 * @name Constructors/assign
	 */
	//@{

	/**
	 * @brief Default constructor
	 *
	 * @post isValid() == false
	 */
	Enum();

	/**
	 * @brief Constructor from an integer
	 *
	 * @remarks a c++ enum is an integer, so this constructor permits to use an element of an enum with this class smoothly.
	 */
	Enum( const int v );

	/**
	 * @brief Copy constructor
	 */
	Enum( const Enum& o );

	/**
	 * @brief Assign operator
	 */
	Enum& operator = ( const Enum& other );
	//@}



	/**
	 * @name Comparison operators
	 */
	//@{

	/**
	 * @brief Returns if value() is less than the value of the given object
	 *
	 * @remarks Used by std::map
	 */
	const bool operator < ( const Enum& other ) const;

	/**
	 * @brief Returns if value() is less than or equal to the value of the given object
	 */
	const bool operator <= ( const Enum& other ) const;

	/**
	 * @brief Returns if value() is greater than the value of the given object
	 */
	const bool operator > ( const Enum& other ) const;

	/**
	 * @brief Returns if value() is greater than or equal the value of the given object
	 */
	const bool operator >= ( const Enum& other ) const;

	/**
	 @brief Returns if value() is equal to the value of the given object
	 */
	const bool operator == ( const Enum& other ) const;

	/**
	 @brief Returns if value() is not equal to the value of the given object
	 */
	const bool operator != ( const Enum& other ) const;

	//@}


	/**
	 * @brief Returns the integer value used to construct this object.
	 *
	 * @return the integer value of this object.
	 */
	const int value() const;

	/**
	 * @brief Returns the literal representation of enumeration value.
	 *
	 * @return the string containing the literal representation of enumeration value
	 */
	const std::string str() const;


	/**
	 * @brief	Retrieves the enumeration value for the given string.
	 *
	 * @return	an enumeration for the given value, cab be invalid
	 */
	const Enum fromString( const std::string & str ) const;

	/**
	 * @brief Returns a vector containing all integer values (and theirs literal representation) allowed to construct this object.
	 */
	const std::vector< std::pair< int, std::string> > valuesAndStrings() const;

	/**
	 * @brief Returns a vector containing all integer values allowed to construct this object.
	 */
	virtual const std::vector< int > values() const;

	/**
	 * @brief Returns a vector containing literal representation of all integer values  allowed to construct this object.
	 */
	virtual const std::vector< std::string > strings() const;


	/**
	 * @brief Returns if this instance of enumeration is valid
	 *
	 * @return true if valid, false otherwise
	 *
	 * @todo checks if in values(), adds test in constructor
	 */
	const bool isValid() const;

private:
	int m_value;	//< the enumeration value
};

/**
 * @name Container definitions of enum type
 */
//@{

typedef TSingleField< Enum >					SFEnum;

typedef TOptionalField< Enum >					OFEnum;

typedef TMultiField< Enum >						MFEnum;

typedef TSingleAssociativeField< Enum >			SAFEnum;

typedef TPairAssociativeField< Enum, Enum >		PAFEnum;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_ENUM_HPP
