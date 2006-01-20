// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_EDITORRO_H
#define _VGD_FIELD_EDITORRO_H

#include "vgd/vgd.hpp"



namespace vgd
{
	
namespace field
{



/**
 * @brief Reference to a field for read-only access.
 * 
 * The template class describes an object that stores a pointer to a field object of type T that ensures that the object
 * to which it points gets notified with startEditingRO() and finishEditing() automatically when it is created and destroyed.
 * 
 * @todo More errors proof when calling start/finishEditing().
 */
template< typename T >
struct EditorRO
{
	/**
	 * @name Constructor/Destructor.
	 */
	//@{
	
	/**
	 * @brief Create an editor without an associated field.
	 */	
	EditorRO() :
		m_pField(0)
	{}
	
	
	/**
	 * @brief Lock the field in read-only mode.
	 */	
	EditorRO( const T* pField ) :
		m_pField( pField )
	{
		if ( pField != 0 )
		{
			bool bRetVal;
			bRetVal = m_pField->startEditingRO();
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
	~EditorRO()
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
	EditorRO( const EditorRO& rField )
	{
		copy( rField );
	}
	
	
	
	EditorRO& operator =( const EditorRO& rField )
	{
		if ( this != &rField )
		{
			if ( m_pField != rField.m_pField )
			{
				release();
			}
			copy(rField);
		}
		
		return ( *this );
	}
	//@}



	/**
	 * @name Accessors.
	 */
	//@{

	const T& operator*() const		{ return ( *m_pField ); }
	const T* operator->() const	{ return ( m_pField ); }
	const T* get() const				{ return ( m_pField ); }
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
	void copy( const EditorRO& rField )
	{
		// Transfert owner ship.
		m_pField												= rField.m_pField;
		const_cast< EditorRO& >(rField).m_pField	= 0;
	}

	/**
	 * @brief Reference to the field.
	 */
	const T*	m_pField;
};



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_EDITORRO_H
