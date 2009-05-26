// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_TOPTIONALFIELD_HPP
#define _VGD_FIELD_TOPTIONALFIELD_HPP

#include "vgd/field/AbstractField.hpp"
#include <boost/optional.hpp>



namespace vgd
{

namespace field
{


/**
 *
 * @brief Template class for all single-value optional fields.
 *
 * @remarks \c Assignable, but \c Not \c DefaultConstructible.
 * T must be Copy Constructible
 */
template < typename T >
struct TOptionalField : public AbstractField
{
	/**
	 * @name Typedefs
	 */
	//@{

	/**
	 * @brief A type that represents the data type stored in this class.
	 */
	typedef T value_type;

	//@}



	/**
	 * @name Constructor
	 */
	//@{

	/**
	 * @brief Default constructor
	 * 
	 * @param strFieldName	name of field.
	 * @post hasValue() == false
	 */
	TOptionalField( const std::string strFieldName )
	:	AbstractField(strFieldName)
	{}

	//@}



	/**
	 * @name Accessors
	 */
	//@{

	/**
	 * @brief Gets the value stored by this field.
	 *
	 * @param value	the value stored by this field only and only if it contains a value (see returned value).
	 *
	 * @return true if the value is initialized, else false
	 */
	const bool getValue( T& value ) const
	{
		assert( checkRO() );

		if ( m_item )
		{
			// m_item is initialized, so copies m_item in value
			value = *m_item;
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	 * @brief Sets the value stored by this field.
	 *
	 * @param rItem	the value to store
	 *
	 * @post hasValue()
	 */
	void setValue( const T& rItem )
	{
		assert( checkRW() );

		m_item.reset( rItem );

		assert( hasValue() );
	}


	/**
	 * @brief Erases the value stored by this field.
	 *
	 * @post hasValue() == false
	 */
	void eraseValue()
	{
		assert( checkRW() );

		m_item.reset();

		assert( hasValue() == false );
	}


	/**
	 * @brief Tests if this field stored a value
	 *
	 * @return true if the value is initialized, else false
	 */
	const bool hasValue() const
	{
		assert( checkRO() );

		return m_item.is_initialized();
	}

	//@}



private:

	boost::optional< T > m_item;		///< the value stored by this field
};



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_TOPTIONALFIELD_HPP
