// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_EDITORRW_H
#define _VGD_FIELD_EDITORRW_H

#include "vgd/vgd.hpp"



namespace vgd
{
	
namespace field
{



/**
 * @brief Reference to a field for read-write access.
 * 
 * The template class describes an object that stores a pointer to a field object of type T that ensures that the object
 * to which it points gets notified with startEditingRW() and finishEditing() automatically when it is created and destroyed.
 * 
 * @todo More errors proof when calling start/finishEditing().
 */
template< typename T >
struct EditorRW
{
	/**
	 * @name Constructor/Destructor.
	 */
	//@{

	/**
	 * @brief Create an editor without an associated field.
	 */
	EditorRW( void ) :
		m_pField(0)
	{}

	/**
	 * @brief Lock the field in read-write mode.
	 */
	EditorRW( T* pField ) :
		m_pField( pField )
	{
		if ( pField != 0 )
		{
			bool bRetVal;
			bRetVal = m_pField->startEditingRW();
			assert(bRetVal);
		}
		else
		{
			assert( false );
		}
	}


	/**
	 * @brief Release the lock on the field.
	 */
	~EditorRW( void )
	{
		release();
	}
	//@}
	
	
	
	/**
	 * @name Copy constructor and assignement.
	 * 
	 * @remarks Ownership is transfered to the copy for theses methods.
	 */
	//@{
	
	EditorRW( const EditorRW& rField )
	{
		copy( rField );
	}
	
	
	
	EditorRW& operator =( const EditorRW& rField )
	{
		if ( this != &rField )
		{
			copy(rField);
		}
		
		return ( *this );
	}
	//@}



	/**
	 * @name Accessors.
	 */
	//@{

	T& operator*() const		{ return ( *m_pField ); }
	T* operator->() const	{ return ( m_pField ); }
	T* get() const				{ return ( m_pField ); }
	//@}
	
	
	
	/**
	 * @name Actions.
	 */
	//@{
	
	/**
	 * @brief Release the lock on the field.
	 */
	void release()
	{
		if ( m_pField != 0 )
		{
			bool bRetVal;
			bRetVal	= m_pField->finishEditing();
			m_pField	= 0;
			assert( bRetVal );
		}
	}
	//@}



private:
	/**
	 * @brief Used by the copy constructor and assignement methods.
	 */
	void copy( const EditorRW& rField )
	{
		// Transfert owner ship.
		m_pField		= rField.m_pField;
		const_cast<EditorRW&>(rField).m_pField	= 0;
	}

	/**
	 * @brief Reference to the field.
	 */
	T*	m_pField;
};



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_EDITORRW_H
