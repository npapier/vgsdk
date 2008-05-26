// VGSDK - Copyright (C) 2004, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_TSINGLEASSOCIATIVEFIELD_HPP
#define _VGD_FIELD_TSINGLEASSOCIATIVEFIELD_HPP

#include <set>

#include "vgd/field/AbstractField.hpp"



namespace vgd
{

namespace field
{



/**
 *
 * @brief Template class for single associative field.
 *
 * A single associative field is a container where the values of the elements contained are unique and serve as the key 
 * values according to which the data is automatically ordered. All values must have the same type.
 * It's simply an encapsulated std::set from STL.
 *
 * @remarks \c Assignable, but \c Not \c DefaultConstructible.
 * 
 * @todo Check interface of this class to be a complete encapsulation of std::set interface.
 * 
 * @todo Add documentation directly in this class.
 */
template< typename KeyType >
struct TSingleAssociativeField : public AbstractField
{
	/**
	 * @name Typedefs
	 */
	//@{

	/**
	 * @brief A type that describes an object stored as an element of a set in its capacity as sort key.
	 */
	typedef KeyType key_type;
	
	/**
	 * @brief A type that describes an object stored as an element of a set in its capacity as a value.
	 */
	typedef KeyType value_type;

	/**
	 * @brief Constant iterator for this container.
	 */
	typedef typename std::set<KeyType>::const_iterator		const_iterator;

	/**
	 * @brief Iterator for this container.
	 */	
	typedef typename std::set<KeyType>::iterator				iterator;

	//@}



	/**
	 * @name Constructor
	 */
	//@{

	/**
	 * @brief Default constructor
	 */
   TSingleAssociativeField( const std::string strFieldName ) :
		AbstractField( strFieldName )
   {}

	//@}



	/** 
	 * @name Size methods
	 */
	//@{

	const uint32	size() const
	{
		assert( checkRO() );

		return ( static_cast<uint32>(m_set.size()) );
	}



	const bool		empty	() const
	{
		assert( checkRO() );

		return ( m_set.empty() );
	}
	
	//@}



	/**
	 * @name Insert
	 */
	//@{

	bool	insert( const KeyType& val )
	{
		assert( checkRW() );
		
		return ( m_set.insert(val) );
	}

	//@}



	/**
	 * @name Iterators
	 */
	//@{

	const_iterator begin() const
	{
		assert( checkRO() );

		return ( m_set.begin() );
	}
	
	iterator			begin()
	{
		assert( checkRW() );
		
		return ( m_set.begin() );
	}


	const_iterator end() const
	{
		assert( checkRO() );

		return ( m_set.end() );
	}
	
	iterator			end()
	{
		assert( checkRW() );
		
		return ( m_set.end() );
	}
	
	//@}

	
	
	/** 
	 * @name Erase
	 */
	//@{
	
	/**
	 * @brief Erase an element that match the key.
	 * 
	 * @return the number of elements that have been removed.
	 */
	uint32 erase( const KeyType& key )
	{
		assert( checkRW() );
		
		return ( static_cast<uint32>(m_set.erase( key )) );
	}


	void  clear()
	{
		assert( checkRW() );

		m_set.clear();
	}

	//@}



	/** 
	 * @name Swap methods
	 */
	//@{
	
	void swap( TSingleAssociativeField< KeyType > other )
	{
		assert( checkRW() );
		assert( other.checkRW() );
		
		m_set.swap( other.m_set );
	}


	void swap( std::set< KeyType >& other )
	{
		assert( checkRW() );

		m_set.swap( other );
	}
	//@}



	/** 
	 * @name Find
	 */
	//@{

	/**
	 * @brief Returns the number of elements whose key matches a parameter-specified key.
	 */
	uint32 count( const KeyType& key ) const
	{
		assert( checkRO() );
		
		return ( static_cast<uint32>(m_set.count( key )) );
	}
	
	iterator find ( const KeyType& key )
	{
		assert( checkRW() );
		
		return ( m_set.find( key ) );
	}
	
	const_iterator find( const KeyType& key ) const
	{
		assert( checkRO() );
		
		return ( m_set.find( key ) );
	}

	//@}



private:

	/**
	 * @name Data
	 */
	//@{

	/**
	 * @brief a set container that contains all element for this field.
	 */
	std::set< KeyType >		m_set;

	//@}
};



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_TSINGLEASSOCIATIVEFIELD_HPP
