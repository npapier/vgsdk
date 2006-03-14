// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_TMULTIFIELD_H
#define _VGD_FIELD_TMULTIFIELD_H

#include <vector>

#include "vgd/vgd.hpp"
#include "vgd/field/AbstractField.hpp"



namespace vgd
{
	
namespace field
{



/**
 *
 * @brief Template class for all multiple-valued fields.
 * 
 * @remarks \c Assignable, but \c Not \c DefaultConstructible.
 * 
 * @todo Check if interface is compatible with std::vector => At(). see stl::vector::at, Pop_back, assign, insert see stl::vector.
 * 
 * @todo automatic usage of agp memory(for NVidia and ATI). See allocator in stl.
 * @todo Resize() that could really decrease the size of the multifield.
 * @todo Add documentation directly in this class.
 */
template<typename T>
struct TMultiField : public AbstractField
{
	/**
	 * @name Typedefs.
	 */
	//@{
	
	/**
	 * @brief A type that represents the data type stored in a vector.
	 */
	typedef T value_type;

	/**
	 * @brief Constant iterator for this container.
	 */
	typedef typename std::vector<T>::const_iterator				const_iterator;

	/**
	 * @brief Iterator for this container.
	 */	
	typedef typename std::vector<T>::iterator						iterator;
	
	//@}
	
	
	
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	TMultiField( const std::string strFieldName ) :
		AbstractField( strFieldName )
	{}

	//@}



	/** 
	 * @name Size methods.
	 */
	//@{

	void		reserve	( const uint32 ui32Size )
	{
		assert( checkRW() );

		m_vectorMF.reserve( ui32Size );
	}



	void		resize	( const uint32 ui32Size )
	{
		assert( checkRW() );

		m_vectorMF.resize( ui32Size );
	}



	const uint32		size	() const
	{
		assert( checkRO() );

		return ( static_cast<uint32>(m_vectorMF.size()) );
	}



	const uint32	capacity() const
	{
		assert( checkRO() );
				
		return ( static_cast<uint32>(m_vectorMF.capacity()) );
	}

	

	const bool		empty	() const
	{
		assert( checkRO() );

		return ( size() == 0 );
	}
	//@}



	/**
	 * @name Accessor to one value.
	 * 
	 * @todo at().
	 */
	//@{

	const T&	operator[] ( const uint32 index ) const
	{
		assert( checkRO() );

		assert( isIndexValid( index ) );

		return ( m_vectorMF[index] );
	}



	T&			operator[] ( const uint32 index )
	{
		assert( checkRW() );

		assert( isIndexValid( index ) );

		return ( m_vectorMF[index] );
	}



	const T&	front() const
	{
		assert( checkRO() );

		assert( m_vectorMF.size() >= 1 );
		
		return ( m_vectorMF.front() );
	}



	T&			front()
	{
		assert( checkRW() );

		assert( m_vectorMF.size() >= 1 );
		
		return ( m_vectorMF.front() );
	}



	const T&	back() const
	{
		assert( checkRO() );

		assert( m_vectorMF.size() >= 1 );
		
		return ( m_vectorMF.back() );
	}



	T&			back()
	{
		assert( checkRW() );

		assert( m_vectorMF.size() >= 1 );
		
		return ( m_vectorMF.back() );
	}

	//@}



	/**
	 * @name Iterators.
	 */
	//@{

	const_iterator begin() const
	{
		assert( checkRO() );

		return ( m_vectorMF.begin() );
	}
	
	iterator			begin()
	{
		assert( checkRW() );
		
		return ( m_vectorMF.begin() );
	}


	const_iterator end() const
	{
		assert( checkRO() );

		return ( m_vectorMF.end() );
	}
	
	iterator			end()
	{
		assert( checkRW() );
		
		return ( m_vectorMF.end() );
	}
	
	//@}
	
	
	
	/** 
	 * @name Accessor on multiple value.
	 * 
	 * @todo assign(), insert()
	 */
	//@{
	//@}



	/** 
	 * @name Inserts element at the end.
	 */
	//@{

	/**
	 * @brief Add an element to the end.
	 *
	 * @param rItem : element to add.
	 */
	void  push_back( const T& rItem )
	{
		assert( checkRW() );

		m_vectorMF.push_back( rItem );
	}



	/**
	 * @brief Add all element from a multifield to the end.
	 *
	 * @param rMFToAppend : multi field to add.
	 */
	void	push_back( const TMultiField<T>& rMFToAppend )
	{
		assert( checkRW() );		
		assert( !rMFToAppend.checkRW() );

		for(	typename std::vector< T >::const_iterator iter = rMFToAppend.begin();
				iter != rMFToAppend.end();
				++iter
			)
		{
			const T& rItem = *iter;
			m_vectorMF.push_back( rItem );
		}
	}

	/**
	 * @brief Add elements from range [begin,end[ of a vector.
	 *
	 * @param begin		position of the first element in the range of elements to be added.
	 * @param end		Position of the first element beyond the range of elements to be added. 
	 */
	void	push_back(	const typename std::vector<T>::const_iterator begin,
						const typename std::vector<T>::const_iterator end )
	{
		assert( checkRW() );

		for(	typename std::vector< T >::const_iterator iter = begin;
				iter != end;
				++iter )
		{
			push_back( *iter );
		}
	}

	/**
	 * @brief Add elements from range [begin,end[ of a vector.
	 *
	 * @param begin		position of the first element in the range of elements to be added.
	 * @param end		Position of the first element beyond the range of elements to be added. 
	 */
	template< typename U >
	void	push_back(	const typename std::vector<U>::const_iterator begin,
						const typename std::vector<U>::const_iterator end )
	{
		assert( checkRW() );

		for(	typename std::vector< U >::const_iterator iter = begin;
				iter != end;
				++iter )
		{
			push_back( static_cast< const T >(*iter) );
		}
	}
	
	//@}



	/** 
	 * @name Inserts elements.
	 * 
	 * @todo all insert methods.
	 */
	//@{
	
	void  insert ( const uint32 index, const T& rItem )
	{
		assert( checkRW() );

		assert( isIndexValid( index ) );

		typename std::vector<T>::iterator iter = m_vectorMF.begin() + index;

		m_vectorMF.insert( iter, rItem );
	}

	//@}



	/** 
	 * @name Erase.
	 * 
	 * @todo pop_back
	 */
	//@{
	
	void	erase( const uint32 index )
	{
		assert( checkRW() );

		assert( isIndexValid( index ) );

		typename std::vector<T>::iterator iter = m_vectorMF.begin() + index;

		m_vectorMF.erase( iter );
	}



	void	pop_back()
	{
		assert( checkRW() );

		assert( m_vectorMF.size() >= 1 );
		
		m_vectorMF.pop_back();
	}



	void  erase( const uint32 indexStart, const uint32 indexEnd )
	{
		assert( checkRW() );

		assert( isIndexValid( indexStart ) );
		assert( isIndexValid( indexEnd ) );

		typename std::vector<T>::iterator iterStart = m_vectorMF.begin() + indexStart;
		typename std::vector<T>::iterator iterEnd   = m_vectorMF.begin() + indexEnd;

		m_vectorMF.erase( iterStart, iterEnd );
	}



	void  clear()
	{
		assert( checkRW() );

		m_vectorMF.clear();
	}
    
	//@}



	/** 
	 * @name Swap.
	 */
	//@{
	
	void  swap   ( const uint32 indexItem1, const uint32 indexItem2 )
	{
		assert( checkRW() );

		assert( isIndexValid( indexItem1 ) );
		assert( isIndexValid( indexItem2 ) );

		T *pTmp = m_vectorMF[indexItem1];
		
		m_vectorMF[indexItem1] = m_vectorMF[indexItem2];
		m_vectorMF[indexItem2] = pTmp;
	}



	void swap( TMultiField<T>& other )
	{
		assert( checkRW() );
		assert( other.checkRW() );
		    	
		m_vectorMF.swap( other );
	}
	//@}



	/** 
	 * @name Find.
	 */
	//@{

	/**
	 * @brief Find an item.
	 * 
	 * @param	rItem	an item.
	 * @return	Index of item (0 to size()-1), or size() if not found.
	 */
	const uint32 find( const T& rItem ) const
	{
		assert( checkRO() );

		uint32 index = 0;
		typename std::vector< T >::const_iterator vectorIter;
		for( vectorIter=m_vectorMF.begin(); (vectorIter != m_vectorMF.end()); ++vectorIter, ++index )
		{
			if ( (*vectorIter) == rItem )
			{
				return ( index );
			}
		}
		
		return ( size() );
	}
	//@}



private:

	/**
	 * @name Data.
	 */
	//@{

	/**
	 * @brief Vector that contains all values for this field.
	 */
	std::vector< T >	m_vectorMF;
	
	//@}



	/**
	 * @brief Test if an index is valid ( >=0 and < size() ).
	 */
	const bool isIndexValid( const uint32 index ) const
	{
		assert( checkRO() );

		return (	( 0 <= index		) &&
					( index < size()	)
				);
	}
};



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_TMULTIFIELD_H
