// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_TMULTIFIELD_H
#define _VGD_FIELD_TMULTIFIELD_H

#include "vgd/vgd.hpp"

#include <vector>

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



	const int32		size	( void ) const
	{
		assert( checkRO() );

		return ( m_vectorMF.size() );
	}



	const uint32	capacity( void ) const
	{
		assert( checkRO() );
				
		return ( m_vectorMF.capacity() );
	}

	

	const bool		empty	( void ) const
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

	const T&	operator[] ( const int32 i32Index ) const
	{
		assert( checkRO() );

		assert( isIndexValid( i32Index ) );

		return ( m_vectorMF[i32Index] );
	}



	T&			operator[] ( const int32 i32Index )
	{
		assert( checkRW() );

		assert( isIndexValid( i32Index ) );

		return ( m_vectorMF[i32Index] );
	}



	const T&	front( void ) const
	{
		assert( checkRO() );

		assert( m_vectorMF.size() >= 1 );
		
		return ( m_vectorMF.front() );
	}



	T&			front( void )
	{
		assert( checkRW() );

		assert( m_vectorMF.size() >= 1 );
		
		return ( m_vectorMF.front() );
	}



	const T&	back( void ) const
	{
		assert( checkRO() );

		assert( m_vectorMF.size() >= 1 );
		
		return ( m_vectorMF.back() );
	}



	T&			back( void )
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
				iter++
			)
		{
			m_vectorMF.push_back( rItem );
		}
	}
	
	//@}



	/** 
	 * @name Inserts elements.
	 * 
	 * @todo all insert methods.
	 */
	//@{
	
	void  insert ( const int32 i32Index, const T& rItem )
	{
		assert( checkRW() );

		assert( isIndexValid( i32Index ) );

		typename std::vector<T>::iterator iter = m_vectorMF.begin() + i32Index;

		m_vectorMF.insert( iter, _rItem );
	}

	//@}



	/** 
	 * @name Erase.
	 * 
	 * @todo pop_back
	 */
	//@{
	
	void	erase( const int32 i32Index )
	{
		assert( checkRW() );

		assert( isIndexValid( i32Index ) );

		typename std::vector<T>::iterator iter = m_vectorMF.begin() + i32Index;

		m_vectorMF.erase( iter );
	}



	void	pop_back( void )
	{
		assert( checkRW() );

		assert( m_vectorMF.size() >= 1 );
		
		m_vectorMF.pop_back();
	}



	void  erase( const int32 i32IndexStart, const int32 i32IndexEnd )
	{
		assert( checkRW() );

		assert( isIndexValid( i32IndexStart ) );
		assert( isIndexValid( i32IndexEnd ) );

		typename std::vector<T>::iterator iterStart = m_vectorMF.begin() + i32Index;
		typename std::vector<T>::iterator iterEnd   = m_vectorMF.begin() + i32End;

		m_vectorMF.erase( iterStart, iterEnd );
	}



	void  clear( void )
	{
		assert( checkRW() );

		m_vectorMF.clear();
	}
    
	//@}



	/** 
	 * @name Swap.
	 */
	//@{
	
	void  swap   ( const int32 i32IndexItem1, const int32 i32IndexItem2 )
	{
		assert( checkRW() );

		assert( isIndexValid( i32IndexItem1 ) );
		assert( isIndexValid( i32IndexItem2 ) );

		T *pTmp = m_vectorMF[i32IndexItem1];
		
		m_vectorMF[i32IndexItem1] = m_vectorMF[i32IndexItem2];
		m_vectorMF[i32IndexItem2] = pTmp;
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
	 * @param rItem	an item.
	 * @return Index of item (0 to size()-1), or -1 if not found.
	 */
	const int32 find( const T& rItem ) const
	{
		assert( checkRO() );

		int32 i32Index = 0;
		typename std::vector< T >::const_iterator vectorIter;
		for( vectorIter=m_vectorMF.begin(); (vectorIter != m_vectorMF.end()); vectorIter++, i32Index++ )
		{
			if ( (*vectorIter) == rItem )
			{
				return ( i32Index );
			}
		}
		
		return ( -1 );
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
	const bool isIndexValid( const int32 i32Index ) const
	{
		assert( checkRO() );

		return (	( 0 <= i32Index		) &&
					( i32Index < size()	)
				);
	}
};



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_TMULTIFIELD_H
