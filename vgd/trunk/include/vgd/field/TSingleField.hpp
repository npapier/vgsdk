// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_TSINGLEFIELD_HPP
#define _VGD_FIELD_TSINGLEFIELD_HPP

#include "vgd/vgd.hpp"
#include "vgd/field/AbstractField.hpp"



namespace vgd
{
	
namespace field
{

/**
 *
 * @brief Template class for all single-value fields.
 *
 * @remarks \c Assignable, but \c Not \c DefaultConstructible.
 */
template < typename T >
struct TSingleField : public AbstractField
{
	/**
	 * @name Typedefs.
	 */
	//@{
		
	/**
	 * @brief A type that represents the data type stored in this class.
	 */
	typedef T value_type;
	
	//@}



	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 * 
	 * @param strFieldName		: name of field.
	 */
	TSingleField( const std::string strFieldName ) :
		AbstractField(strFieldName)
	{}
	
	//@}



	/**
	 * @name Accessors.
	 */
	//@{
	void     setValue ( const T& rItem )
	{
		assert( checkRW() );

		m_item = rItem;
	}

	const T& getValue () const
	{
		assert( checkRO() );
    	
    	return ( m_item );
	}

	T&       getValue ()
	{
		assert( checkRW() );
    	
    	return ( m_item );
	}
	//@}



private:
 
    T m_item;
};



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_TSINGLEFIELD_HPP
