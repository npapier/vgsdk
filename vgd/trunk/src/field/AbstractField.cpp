// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/field/AbstractField.hpp"

#include <algorithm>

#include "vgd/field/IFieldObserver.hpp"



namespace vgd
{

namespace field
{



AbstractField::AbstractField( const std::string& strFieldName ) :
	vgd::basic::NamedObject( strFieldName ),
	m_editingMode	( NONE )
{}



AbstractField::~AbstractField()
{
	//notify( DESTROY ); ??? FIXME

	assert( m_editingMode == NONE );
}



bool AbstractField::findObserver( IFieldObserver *pFieldObserver ) const
{
	assert( m_editingMode == NONE );

	TListObserver::const_iterator iter;
	iter = std::find( getObservers().begin(), getObservers().end(), pFieldObserver );

	return ( iter != getObservers().end() );
}



void AbstractField::attach( IFieldObserver* pObserver )
{
	assert( m_editingMode == NONE );
	assert( !findObserver(pObserver) );

	getObservers().push_back( pObserver );
}



void AbstractField::detach( IFieldObserver* pObserver )
{
	assert( m_editingMode == NONE );	
	assert( findObserver(pObserver) );

	getObservers().remove( pObserver );
}



void AbstractField::detach()
{
	assert( m_editingMode == NONE );	
	getObservers().clear();
}



void AbstractField::sendNotify( const Event& event ) const
{
	assert( m_editingMode == NONE );

    // notify all observers.
    for(	TListObserver::const_iterator i = getObservers().begin();
        	i != getObservers().end();
        	i++ )
    {
    	IFieldObserver *pFieldObserver = *i;
    	assert( *i != 0 );
    	
    	(*i)->updateField( *this, event );
    }
}



/*void AbstractField::receiveNotify( const Event& event )
{
	switch ( event )
	{
		default:
			assert( false && "Do something." );
	}
}*/



bool AbstractField::isSubject() const
{
	assert( m_editingMode == NONE );

	return ( getObservers().size() > 0 );
}



bool AbstractField::startEditingRO() const
{
	switch ( m_editingMode )
	{
		case NONE:
		case RO:
			m_editingMode = RO;
			return ( true );

		case RW:
			return ( false );
			
		default:
			assert( false && "Unknown case" );
			return ( false );
	}
}



bool AbstractField::startEditingRW() const
{
	switch ( m_editingMode )
	{
		case NONE:
			m_editingMode = RW;
			return ( true );

		case RO:
		case RW:
			return ( false );

		default:
			assert( false && "Unknown case" );
			return ( false );
	}
}



bool AbstractField::finishEditing() const
{
	switch ( m_editingMode )
	{
		case NONE:
			return ( false );

		case RO:
			m_editingMode = NONE; // not true if multi threaded !!! FIXME
			return ( true );

		case RW:
			m_editingMode = NONE; // not true if multi threaded !!! FIXME
			sendNotify( UPDATE );
			return ( true );

		default:
			assert( false && "Unknown case" );
			return ( false );
	}
}



bool AbstractField::isSameEditingMode( const EditingMode mode ) const
{
	return ( m_editingMode == mode );
}



} // namespace vgd

} // namespace field
