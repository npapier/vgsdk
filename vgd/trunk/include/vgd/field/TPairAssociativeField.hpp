// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_TPAIRASSOCIATIVEFIELD_H
#define _VGD_FIELD_TPAIRASSOCIATIVEFIELD_H

#include <map>

#include "vgd/vgd.hpp"
#include "vgd/field/AbstractField.hpp"



namespace vgd
{

namespace field
{



/**
 *
 * @brief Template class for pair associative field.
 * 
 * A pair associative field is a container where each element is a pair that has both a data value and a sort key. The 
 * value of the key is unique and is used to order the data automatically. All values must have the same type.
 * It's simply an encapsulated std::map from STL.
 *
 * @remarks \c Assignable, but \c Not \c DefaultConstructible.
 * 
 * @todo Check interface of this class to be a complete encapsulation of std::map interface (add insert()).
 * 
 * @todo Add documentation directly in this class.
 */
template< typename KeyType, typename DataType >
struct TPairAssociativeField : public AbstractField
{
	/**
	 * @name Typedefs.
	 */
	//@{
	
	/**
	 * @brief A type that describes the sort key object that constitutes each element of the map.
	 */
	typedef KeyType key_type;
	
	/**
	 * @brief A type that represents the data type stored in a map.
	 */
	typedef DataType mapped_type;

	/**
	 * @brief A type that represents the type of object stored as an element in a map.
	 */
	typedef std::pair< const KeyType, DataType > value_type;
	
	/**
	 * @brief Constant iterator for this container.
	 */
	typedef typename std::map<KeyType, DataType>::const_iterator		const_iterator;

	/**
	 * @brief Iterator for this container.
	 */	
	typedef typename std::map<KeyType, DataType>::iterator				iterator;
	//@}



	/**
	 * @name Constructor.
	 */
	//@{

    /**
     * @brief Default constructor.
     */
    TPairAssociativeField( const std::string strFieldName ) :
		AbstractField( strFieldName )
   {}

	//@}



	/** 
	 * @name Size methods.
	 */
	//@{

	const uint32		size	() const
	{
		assert( checkRO() );

		return ( static_cast<uint32>(m_map.size()) );
	}



	const bool		empty	() const
	{
		assert( checkRO() );

		return ( m_map.empty() );
	}
	
	//@}



	/**
	 * @name Accessor to one value.
	 */
	//@{
	
	/**
	 * @brief Inserts an element into a map with a specified key value.
	 * 
	 * @return A reference to the data value of the inserted or pre-existing element.
	 */
	DataType& operator[]( const KeyType& key )
	{
		assert( checkRW() );
		
		return ( m_map[key] );
	}

	//@}



	/**
	 * @name Iterators.
	 */
	//@{

	const_iterator begin() const
	{
		assert( checkRO() );

		return ( m_map.begin() );
	}
	
	iterator			begin()
	{
		assert( checkRW() );
		
		return ( m_map.begin() );
	}


	const_iterator end() const
	{
		assert( checkRO() );

		return ( m_map.end() );
	}
	
	iterator			end()
	{
		assert( checkRW() );
		
		return ( m_map.end() );
	}
	
	//@}

	
	
	/** 
	 * @name Erase.
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
		
		return ( static_cast<uint32>(m_map.erase( key )) );
	}


	void  clear()
	{
		assert( checkRW() );

		m_map.clear();
	}

	//@}



	/** 
	 * @name Swap.
	 */
	//@{
	
	void  swap   ( TPairAssociativeField< KeyType, DataType > other )
	{
		assert( checkRW() );
		assert( other.checkRW() );
		
		m_map.swap( other );
	}
	//@}



	/** 
	 * @name Find.
	 */
	//@{

	/**
	 * @brief Returns the number of elements whose key matches a parameter-specified key.
	 */
	uint32 count( const KeyType& key ) const
	{
		assert( checkRO() );
		
		return ( static_cast<uint32>(m_map.count( key )) );
	}
	
	iterator find ( const KeyType& key )
	{
		assert( checkRW() );
		
		return ( m_map.find( key ) );
	}
	
	const_iterator find( const KeyType& key ) const
	{
		assert( checkRO() );
		
		return ( m_map.find( key ) );
	}

	//@}



private:

	/**
	 * @name Data.
	 */
	//@{

	/**
	 * @brief Map that contains all (key,value) pairs for this field.
	 */
	std::map< KeyType, DataType >		m_map;

	//@}
};



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_TPAIRASSOCIATIVEFIELD_H
