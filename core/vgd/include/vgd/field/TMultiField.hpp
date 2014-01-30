// VGSDK - Copyright (C) 2004, 2006, 2008, 2013, 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_TMULTIFIELD_HPP
#define _VGD_FIELD_TMULTIFIELD_HPP

#include <vector>

#include "vgd/field/AbstractField.hpp"
#include "vgDebug/helpers.hpp"



namespace vgd
{

namespace field
{



/**
 * @brief Template class for all multiple-valued fields.
 *
 * The TMultiField class is a template class that provides a dynamic array similar to std::vector.
 * This is one of vgsdk generic container classes used by field.
 * Items are stored in adjacent memory locations. Index-based accesses are fast.
 *
 * @remarks \c Assignable, but \c Not \c DefaultConstructible.
 * 
 * @todo Checks compatibility and similarity with std::vector(at(). see stl::vector::at, pop_back, assign, insert).
 * @todo Uses video memory automatically.
 * @todo Resize() that could really decrease the size of the multi-field.
 * @todo Adds documentation directly in this class.
 */
template<typename T>
struct TMultiField : public AbstractField
{
	/**
	 * @name Typedefs
	 */
	//@{
	
	/**
	 * @brief A type that represents the data type stored in this container.
	 */
	typedef T value_type;

	/**
	 * @brief Constant iterator
	 *
	 * A random-access iterator that can read a const element.
	 */
	typedef typename std::vector<T>::const_iterator				const_iterator;

	/**
	 * @brief Iterator
	 *
	 * A random-access iterator that can read or modify any element.
	 */	
	typedef typename std::vector<T>::iterator					iterator;

	/**
	 * @brief Constant reverse iterator
	 *
	 * A random-access iterator that can read a const element.
	 */
	typedef typename std::vector<T>::const_reverse_iterator		const_reverse_iterator;

	/**
	 * @brief Reverse iterator
	 *
	 * A random-access iterator that can read or modify any element.
	 */	
	typedef typename std::vector<T>::reverse_iterator			reverse_iterator;
	
	//@}
	
	
	
	/**
	 * @name Constructor
	 */
	//@{

	/**
	 * @brief Default constructor
	 */
	TMultiField( const std::string strFieldName ) :
		AbstractField( strFieldName )
	{}

	//@}



	/** 
	 * @name Size methods
	 */
	//@{

	void reserve( const uint32 ui32Size )
	{
		vgAssert( checkRW() );

		m_vectorMF.reserve( ui32Size );
	}



	void resize( const uint32 ui32Size )
	{
		vgAssert( checkRW() );

		m_vectorMF.resize( ui32Size );
	}



	const uint32 size() const
	{
		vgAssert( checkRO() );

		return static_cast<uint32>(m_vectorMF.size());
	}



	const uint32 capacity() const
	{
		vgAssert( checkRO() );
				
		return static_cast<uint32>(m_vectorMF.capacity());
	}

	

	const bool empty() const
	{
		vgAssert( checkRO() );

		return ( size() == 0 );
	}
	//@}



	/**
	 * @name Accessor to one value
	 * 
	 * @todo at().
	 */
	//@{

	const T&	operator[] ( const uint32 index ) const
	{
		vgAssert( checkRO() );

		vgAssert( isIndexValid( index ) );

		return m_vectorMF[index];
	}



	T&			operator[] ( const uint32 index )
	{
		vgAssert( checkRW() );

		vgAssert( isIndexValid( index ) );

		return m_vectorMF[index];
	}



	const T& front() const
	{
		vgAssert( checkRO() );

		vgAssert( m_vectorMF.size() >= 1 );

		return m_vectorMF.front();
	}



	T& front()
	{
		vgAssert( checkRW() );

		vgAssert( m_vectorMF.size() >= 1 );

		return m_vectorMF.front();
	}



	const T& back() const
	{
		vgAssert( checkRO() );

		vgAssert( m_vectorMF.size() >= 1 );

		return m_vectorMF.back();
	}



	T& back()
	{
		vgAssert( checkRW() );

		vgAssert( m_vectorMF.size() >= 1 );

		return m_vectorMF.back();
	}



	const T * ptr() const
	{
		vgAssert( checkRO() );

		return m_vectorMF.empty() ? 0 : &m_vectorMF.front();
	}


	T * ptr()
	{
		vgAssert( checkRW() );

		return m_vectorMF.empty() ? 0 : &m_vectorMF.front();
	}
	//@}



	/**
	 * @name Iterators
	 *
	 * The following iterators are compatibles with stl iterators.
	 * So for example, any \c stl algorithms could be applied to a multi-field.
	 */
	//@{

	const_iterator begin() const
	{
		vgAssert( checkRO() );

		return m_vectorMF.begin();
	}
	
	iterator begin()
	{
		vgAssert( checkRW() );
		
		return m_vectorMF.begin();
	}


	const_iterator end() const
	{
		vgAssert( checkRO() );

		return m_vectorMF.end();
	}
	
	iterator end()
	{
		vgAssert( checkRW() );
		
		return m_vectorMF.end();
	}



	const_reverse_iterator rbegin() const
	{
		vgAssert( checkRO() );

		return m_vectorMF.rbegin();
	}
	
	reverse_iterator rbegin()
	{
		vgAssert( checkRW() );
		
		return m_vectorMF.rbegin();
	}


	const_reverse_iterator rend() const
	{
		vgAssert( checkRO() );

		return m_vectorMF.rend();
	}
	
	reverse_iterator rend()
	{
		vgAssert( checkRW() );
		
		return m_vectorMF.rend();
	}
	//@}
	
	
	
	/** 
	 * @name Inserts element at the end
	 */
	//@{

	/**
	 * @brief Adds an element to the end.
	 *
	 * @param rItem		element to add.
	 */
	void  push_back( const T& rItem )
	{
		vgAssert( checkRW() );

		m_vectorMF.push_back( rItem );
	}

	/**
	 * @brief Adds to the end of this container all element from a multifield.
	 *
	 * @param other	the multi-field containing all elements to add
	 */
	void push_back( const TMultiField<T>& other )
	{
		vgAssert( checkRW() );
		vgAssert( other.checkRO() );

		m_vectorMF.insert( m_vectorMF.end(), other.m_vectorMF.begin(), other.m_vectorMF.end() );
	}

	/**
	 * @brief Adds to the end of this container elements from range [begin,end[
	 *
	 * @param begin	the position of the first element in the range of elements to be copied.
	 * @param end	the position of the first element beyond the range of elements to be copied.
	 * 
	 * @remarks Given iterators could be standard \c STL iterator or TMultiField iterators.
	 */
	void push_back(	const typename std::vector<T>::const_iterator begin,
					const typename std::vector<T>::const_iterator end )
	{
		vgAssert( checkRW() );

		m_vectorMF.insert( m_vectorMF.end(), begin, end );
	}

	/**
	 * @brief Adds to the end of this container elements from range [begin,end[
	 *
	 * @param begin	the position of the first element in the range of elements to be copied.
	 * @param end	the position of the first element beyond the range of elements to be copied.
	 * 
	 * @remarks Given iterators could be standard \c STL iterator or TMultiField iterators.
	 */
	template< typename U >
	void push_back(	const typename std::vector<U>::const_iterator begin,
					const typename std::vector<U>::const_iterator end )
	{
		vgAssert( checkRW() );

		for(	typename std::vector< U >::const_iterator iter = begin;
				iter != end;
				++iter )
		{
			push_back( static_cast< const T >(*iter) );
		}
	}

	/**
	 * @brief Adds at the end of this container all elements of the given vector.
	 * 
	 * @param source	vector with element to push back.
	 */
	void push_back( const typename std::vector<T> source )
	{
		push_back( source.begin(), source.end() );
	}

	/**
	 * @brief Adds at the end of this container all elements of the given vector.
	 *
	 * @param source	vector with element to push back.
	 */
	template< typename U >
	void push_back( const typename std::vector<U> source )
	{
		push_back( source.begin(), source.end() );
	}
	//@}



	/**
	 * @name Inserts element(s)
	 * 
	 * @remarks Inserting or deleting elements in the middle of a vector requires linear time. Try to avoid them as possible.
	 */
	//@{

	/**
	 * @brief Inserts an element at a specified position.
	 *
	 * @param index		the zero-based position in the multi-field where the element is inserted
	 * @param item		the new element to insert
	 */
	void insert( const uint32 index, const T& item )
	{
		vgAssert( checkRW() );

		vgAssert( isIndexValid(index) || index == size() );

		typename std::vector<T>::iterator iter = m_vectorMF.begin() + index;

		m_vectorMF.insert( iter, item );
	}

	/**
	 * @brief Inserts an element at a specified position.
	 *
	 * @param where	the position in the multi-field where the element is inserted
	 * @param item		the new element to insert
	 */
	void insert( const const_iterator where, const T& item )
	{
		vgAssert( checkRW() );

		m_vectorMF.insert( where, item );
	}

	/**
	 * @brief Inserts a number of elements at a specified position.
	 *
	 * @param index		the zero-based position in the multi-field where the element is inserted
	 * @param count		the number of elements being inserted into the multi-field
	 * @param item		the new element to insert
	 */
	void insert( const uint32 index, const uint32 count, const T& item )
	{
		vgAssert( checkRW() );

		vgAssert( isIndexValid(index) || index == size() );

		typename std::vector<T>::iterator iter = m_vectorMF.begin() + index;

		m_vectorMF.insert( iter, count, item );
	}

	/**
	 * @brief Inserts an element at a specified position.
	 *
	 * @param where	the position in the multi-field where the element is inserted
	 * @param count		the number of elements being inserted into the multi-field
	 * @param item		the new element to insert
	 */
	void insert( const const_iterator where, const uint32 count, const T& item )
	{
		vgAssert( checkRW() );

		m_vectorMF.insert( where, count, item );
	}

	/**
	 * @brief Inserts a range of elements at a specified position.
	 *
	 * @param index		the zero-based position in the multi-field where the element is inserted
	 * @param begin		the position of the first element in the range of elements to be copied
	 * @param end		the position of the first element beyond the range of elements to be copied
	 *
	 * @remarks Given iterators could be standard \c STL iterator or TMultiField iterators.
	 */
	void insert(	const uint32 index,
					const typename std::vector<T>::const_iterator begin,
					const typename std::vector<T>::const_iterator end )
	{
		vgAssert( checkRW() );

		vgAssert( isIndexValid(index) || index == size() );

		typename std::vector<T>::iterator iter = m_vectorMF.begin() + index;

		m_vectorMF.insert( iter, begin, end );
	}

	/**
	 * @brief Inserts a range of elements at a specified position.
	 *
	 * @param where	the position in the multi-field where the element is inserted
	 * @param begin		the position of the first element in the range of elements to be copied
	 * @param end		the position of the first element beyond the range of elements to be copied
	 *
	 * @remarks Given iterators could be standard \c STL iterator or TMultiField iterators.
	 */
	void insert(	const const_iterator where,
					const typename std::vector<T>::const_iterator begin,
					const typename std::vector<T>::const_iterator end )
	{
		vgAssert( checkRW() );

		m_vectorMF.insert( where, begin, end );
	}
	//@}



	/**
	 * @name Erases element(s)
	 *
	 * @remarks Inserting or deleting elements in the middle of a vector requires linear time. Try to avoid them as possible.	 
	 */
	//@{

	/**
	 * @brief Removes an element.
	 *
	 * @param index		position of the element to be removed from the multi-field.
	 */
	void erase( const uint32 index )
	{
		vgAssert( checkRW() );

		vgAssert( m_vectorMF.size() >= 1 );
		vgAssert( isIndexValid( index ) );

		typename std::vector<T>::iterator iter = m_vectorMF.begin() + index;

		m_vectorMF.erase( iter );
	}

	/**
	 * @brief Removes an elements.
	 *
	 * @param where	position of the element to be removed from the multi-field.
	 */
	void erase( iterator where )
	{
		vgAssert( checkRW() );

		vgAssert( m_vectorMF.size() >= 1 );

		m_vectorMF.erase( where );
	}

	void pop_back()
	{
		vgAssert( checkRW() );

		vgAssert( m_vectorMF.size() >= 1 );
		
		m_vectorMF.pop_back();
	}



	/**
	 * @brief Removes an element or a range of elements from specified positions.
	 *
	 * @param indexStart	position of the first element removed from the multi-field.
	 * @param indexEnd	position just beyond the last element removed from the multi-field.
	 */
	void erase( const uint32 indexStart, const uint32 indexEnd )
	{
		vgAssert( checkRW() );

		vgAssert( isIndexValid( indexStart ) );
		vgAssert( isIndexValid( indexEnd ) || indexEnd == size() );
		vgAssert( indexStart < indexEnd );

		typename std::vector<T>::iterator iterStart = m_vectorMF.begin() + indexStart;
		typename std::vector<T>::iterator iterEnd   = m_vectorMF.begin() + indexEnd;

		m_vectorMF.erase( iterStart, iterEnd );
	}

	/**
	 * @brief Removes an element or a range of elements from specified positions.
	 *
	 * @param begin	position of the first element removed from the multi-field.
	 * @param end	position just beyond the last element removed from the multi-field.
	 */
	void erase( iterator begin, iterator end )
	{
		vgAssert( checkRW() );

		vgAssert( begin < end );

		m_vectorMF.erase( begin, end );
	}



	/**
	 * @brief Erases the elements of the multi-field.
	 */
	void clear()
	{
		vgAssert( checkRW() );

		m_vectorMF.clear();
	}

	//@}



	/** 
	 * @name Swapping methods
	 */
	//@{
	
	void swap( const uint32 indexItem1, const uint32 indexItem2 )
	{
		vgAssert( checkRW() );

		vgAssert( isIndexValid( indexItem1 ) );
		vgAssert( isIndexValid( indexItem2 ) );

		T *pTmp = m_vectorMF[indexItem1];

		m_vectorMF[indexItem1] = m_vectorMF[indexItem2];
		m_vectorMF[indexItem2] = pTmp;
	}

	void swap( TMultiField<T>& other )
	{
		vgAssert( checkRW() );
		vgAssert( other.checkRW() );
		    	
		m_vectorMF.swap( other.m_vectorMF );
	}

	void swap( std::vector<T>& other )
	{
		vgAssert( checkRW() );

		m_vectorMF.swap( other );
	}

	//@}



	/** 
	 * @name Searching
	 */
	//@{

	/**
	 * @brief Finds an item.
	 * 
	 * @param rItem	an item.
	 * @return zero-based index of item (0 to size()-1), or size() if not found.
	 */
	const uint32 find( const T& rItem ) const
	{
		vgAssert( checkRO() );

		uint32 index = 0;
		typename std::vector< T >::const_iterator vectorIter;
		for( vectorIter=m_vectorMF.begin(); (vectorIter != m_vectorMF.end()); ++vectorIter, ++index )
		{
			if ( (*vectorIter) == rItem )
			{
				return index;
			}
		}
		
		return size();
	}
	//@}



private:

	/**
	 * @name Data
	 */
	//@{

	/**
	 * @brief Vector that contains all values of this field.
	 */
	std::vector< T >	m_vectorMF;

	//@}



	/**
	 * @brief Tests if an index is valid ( >=0 and < size() ).
	 */
	const bool isIndexValid( const uint32 index ) const
	{
		vgAssert( checkRO() );

		return (	( 0 <= index		) &&
					( index < size()	)
				);
	}
};



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_TMULTIFIELD_HPP
