// VGSDK - Copyright (C) 2006, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_ENUM_HPP
#define _VGD_FIELD_ENUM_HPP

#include "vgd/field/containers.hpp"



namespace vgd
{

namespace field
{

/**
 * @brief Definition of an enumeration type
 *
 * @todo virtual getValues(), getStrs() ...
 */
struct VGD_API Enum
{
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
	 * @brief Assign operator
	 */
	Enum& operator = ( const Enum& other );

	/**
	 * @brief Returns if value() is less than the value of the given object
	 *
	 * @remarks Used by std::map
	 */
	const bool operator < ( const Enum& other ) const;

	/**
	 @brief Returns if value() is equal to the value of the given object
	 */
	const bool operator == ( const Enum& other ) const;

	/**
	 * @brief Returns the integer value used to construct this object.
	 *
	 * @return the integer value of this object.
	 */
	const int value() const;

	/**
	 * @brief Returns the litteral representation of enumeration value.
	 *
	 * @return the string containing the litteral representation of enumeration value
	 */
	const std::string str() const;

	/**
	 * @brief Returns if this instance of enumeration is valid
	 *
	 * @return true if valid, false otherwise
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

typedef TMultiField< Enum >						MFEnum;

typedef TSingleAssociativeField< Enum >			SAFEnum;

typedef TPairAssociativeField< Enum, Enum >		PAFEnum;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_ENUM_HPP
