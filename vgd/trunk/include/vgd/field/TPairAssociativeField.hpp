// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_TPAIRASSOCIATIVEFIELD_H
#define _VGD_FIELD_TPAIRASSOCIATIVEFIELD_H

#include "vgd/vgd.hpp"

#include <map>

#include "vgd/field/AbstractField.hpp"



namespace vgd
{
	
namespace field
{



/**
 *
 * @brief Template class for pair associative field.
 * 
 * A pair associative field is a container where each element is a pair that has both a data value and a sort key. The value of the 
 * key is unique and is used to order the data automatically. All values must have the same type.
 * It's simply an encapsulated std::map from STL.
 *
 * @remarks \c Assignable, but \c Not \c DefaultConstructible.
 * 
 * @todo Check interface of this class to be a complete encapsulation of std::map interface (add insert()).
 * 
 * @todo Add documentation directly in this class.
 */
template< typename KeyType, typename ValueType >
struct TPairAssociativeField : public AbstractField
{
	/**
	 * @name Typedefs.
	 */
	//@{
	
	/**
	 * @brief Constant iterator for this container.
	 */
	typedef typename std::map<KeyType, ValueType>::const_iterator		const_iterator;

	/**
	 * @brief Iterator for this container.
	 */	
	typedef typename std::map<KeyType, ValueType>::iterator				iterator;
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

	const int32		size	( void ) const
	{
		assert( checkRO() );

		return ( static_cast<int32>(m_map.size()) );
	}



	const bool		empty	( void ) const
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
	ValueType& operator[]( const KeyType& key )
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
	int32 erase( const KeyType& key )
	{
		assert( checkRW() );
		
		return ( static_cast<int32>(m_map.erase( key )) );
	}


	void  clear( void )
	{
		assert( checkRW() );

		m_map.clear();
	}

	//@}



	/** 
	 * @name Swap.
	 */
	//@{
	
	void  swap   ( TPairAssociativeField< KeyType, ValueType > other )
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
	int32 count( const KeyType& key ) const
	{
		assert( checkRO() );
		
		return ( static_cast<int32>(m_map.count( key )) );
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
	std::map< KeyType, ValueType >		m_map;

	//@}
};



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_TPAIRASSOCIATIVEFIELD_H
