// VGSDK - Copyright (C) 2004, 2006, 2008, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgd/field/AbstractField.hpp"

#include <algorithm>

#include "vgd/field/IFieldObserver.hpp"
#include "vgd/field/Types.hpp"
#include <vgDebug/helpers.hpp>



namespace vgd
{

namespace field
{



AbstractField::AbstractField( const std::string& strFieldName )
:	vgd::basic::NamedObject	( strFieldName	),
	m_editingMode			( NONE			)
{}



AbstractField::~AbstractField()
{
	//notify( DESTROY ); /// @todo FIXME

	vgAssert( m_editingMode == NONE );
}



std::list< IFieldObserver* >& AbstractField::getObservers()
{
	return m_listObservers;
}



const std::list< IFieldObserver* >& AbstractField::getObservers() const
{
	return m_listObservers;
}



const bool AbstractField::findObserver( IFieldObserver *pFieldObserver ) const
{
	vgAssert( m_editingMode >= NONE );

	TListObserver::const_iterator iter;
	iter = std::find( getObservers().begin(), getObservers().end(), pFieldObserver );

	return ( iter != getObservers().end() );
}



void AbstractField::attach( IFieldObserver* pObserver ) const
{
	vgAssert( m_editingMode >= NONE );
	vgAssert( !findObserver(pObserver) );

	m_listObservers.push_back( pObserver );
}



void AbstractField::detach( IFieldObserver* pObserver ) const
{
	vgAssert( m_editingMode >= NONE );
	vgAssert( findObserver(pObserver) );

	m_listObservers.remove( pObserver );
}



void AbstractField::detach() const
{
	vgAssert( m_editingMode >= NONE );

	m_listObservers.clear();
}



void AbstractField::sendNotify( const Event& event ) const
{
	vgAssert( m_editingMode >= NONE );

    // notify all observers.
    for(	TListObserver::const_iterator i = getObservers().begin();
        	i != getObservers().end();
        	i++ )
    {
    	IFieldObserver *pFieldObserver = *i;
    	vgAssert( pFieldObserver != 0 );
    	
    	pFieldObserver->updateField( *this, event );
    }
}



/*void AbstractField::receiveNotify( const Event& event )
{
	switch ( event )
	{
		default:
			vgAssert( false && "Do something." );
	}
}*/



const bool AbstractField::isSubject() const
{
	vgAssert( m_editingMode == NONE );

	return ( getObservers().size() > 0 );
}



const bool AbstractField::startEditingRO() const
{
	if ( m_editingMode == RW )
	{
		return false;
	}
	else
	{
		vgAssert( m_editingMode >= NONE );

		incrementEditingMode();

		return true;
	}
}



const bool AbstractField::startEditingRW() const
{
	if ( m_editingMode == NONE )
	{
		m_editingMode = RW;
		return true;
	}
	else
	{
		return false;
	}
}



const bool AbstractField::finishEditing() const
{
	if ( m_editingMode == RW )
	{
		m_editingMode = NONE;

		sendNotify( UPDATE );

		return true;
	}
	else if ( m_editingMode >= RO )
	{
		decrementEditingMode();

		return true;
	}
	else
	{
		vgAssert( m_editingMode == NONE );

		vgAssert2( false, "Internal error. Must never occurs." );

		return false;
	}
}



const bool AbstractField::isSameEditingMode( const EditingMode mode ) const
{
	const EditingMode thisEditingMode	= (m_editingMode >= RO) ? RO : m_editingMode;
	const EditingMode givenEditingMode	= (mode >= RO) ? RO : mode;

	return thisEditingMode == givenEditingMode;
}



const bool AbstractField::checkRO() const
{
	return ( !isSameEditingMode(NONE) );
}



const bool AbstractField::checkRW() const
{
	return isSameEditingMode(RW);
}



void AbstractField::incrementEditingMode() const
{
	vgAssert( m_editingMode >= NONE );

	const int editingMode = static_cast<int>(m_editingMode) + 1;
	m_editingMode = static_cast<EditingMode>( editingMode );

	vgAssert( m_editingMode >= NONE );
}



void AbstractField::decrementEditingMode() const
{
	vgAssert( m_editingMode > NONE );

	const int editingMode = static_cast<int>(m_editingMode) - 1;
	m_editingMode = static_cast<EditingMode>( editingMode );

	vgAssert( m_editingMode >= NONE );
}



} // namespace field

} // namespace vgd
