// VGSDK - Copyright (C) 2004, 2006, 2011, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/field/FieldManager.hpp"

#include <utility>
#include <typeinfo>
#include <boost/tuple/tuple.hpp>

#include "vgd/Shp.hpp"
#include "vgd/field/Types.hpp"

#include <boost/thread/thread.hpp>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif



namespace
{
	boost::thread::id g_lockedID = boost::thread::id();
}


namespace vgd
{

namespace field
{



FieldManager::FieldManager()
{}



FieldManager::FieldManager( const FieldManager& rSrc )
{
	copy( rSrc );
}



FieldManager& FieldManager::operator= ( const FieldManager& rSrc )
{
	if ( this != &rSrc )
	{
		destroy();
		copy( rSrc );
	}

	return ( *this );
}



FieldManager::~FieldManager()
{
	destroy();
}



void FieldManager::destroy()
{}



void FieldManager::lockFieldAccess()
{
	g_lockedID = boost::this_thread::get_id();
}



const bool FieldManager::ensureFieldAccess(const std::string& strFieldName) const
{
	if( g_lockedID != boost::thread::id() && boost::this_thread::get_id() != g_lockedID )
	{
		std::cerr << "Access to field " << strFieldName << " from wrong thread" << std::endl;
		vgAssertN( false, "Access to field %s from wrong thread", strFieldName.c_str() );
/*#if ( defined _WIN32 ) && ( defined _DEBUG )
		if ( IsDebuggerPresent() )
		{
			DebugBreak();
		}
		//else nothing to do
#endif*/
		return false;
	}
	else
	{
		return true;
	}
}


/**
 * @todo Implement it.
 */
void FieldManager::copy( const FieldManager& /*rSrc*/ )
{
	vgAssert( false );
}



const bool FieldManager::isField( const std::string strFieldName ) const
{
	MapField::const_iterator iField;
	iField = m_fields.find( strFieldName );

	return ( iField != m_fields.end() );
}



const std::type_info& FieldManager::getFieldType( const std::string strFieldName ) const
{
	MapField::const_iterator iField;
	iField = m_fields.find( strFieldName );

	if ( iField != m_fields.end() )
	{
		// Found
		return typeid( *(iField->second.get()) );
	}
	else
	{
		// Not found
		return typeid( NotFound );
	}
}



void FieldManager::getFieldNames( std::vector< std::string >& oFieldNames ) const
{
	typedef std::vector< std::string > 						StringContainer;
	typedef std::back_insert_iterator< StringContainer >	InsertIterator;

	InsertIterator inserter( oFieldNames );
	getFieldNames( inserter );
}


/*
std::pair< MapField::const_iterator, MapField::const_iterator >
	FieldManager::getFieldIterators( void ) const
{
	std::pair< MapField::const_iterator, MapField::const_iterator > retVal;
	
	retVal.first	= m_fields.begin();
	retVal.second	= m_fields.end();
	
	return ( retVal );
}



std::pair< MapField::iterator, MapField::iterator >
	FieldManager::getFieldIterators( void )
{
	std::pair< MapField::iterator, MapField::iterator > retVal;
	
	retVal.first	= m_fields.begin();
	retVal.second	= m_fields.end();
	
	return ( retVal );
}*/



const bool FieldManager::addField( vgd::Shp< AbstractField > newField )
{
	// STEP 1 : Add field to field container
	std::pair< MapField::iterator, bool> retVal;

	retVal = m_fields.insert(
		std::make_pair( newField->name(), newField )
		);

	if ( retVal.second == false )
	{
		vgAssertN( false, "Unable to add this field named %s. Field name must be unique.", newField->name().c_str() );
		return false;
	}

	// STEP 2 : Add link between field and field manager.
	vgAssertN( newField->findObserver( this ) == false, "The added field is already observed by this manager of fields." );

	newField->attach( this );

	return retVal.second;
}

const bool FieldManager::addField( AbstractField* pField )
{
	vgd::Shp<AbstractField> shpField(pField);
	return addField(shpField);
}



const bool FieldManager::setField( vgd::Shp< AbstractField > field )
{
	const std::string& fieldName = field->name();

	MapField::iterator iField = m_fields.find( fieldName );

	if ( iField != m_fields.end() )
	{
		// Found the field named field name and replace it by the given field
		iField->second = field;

		// Add link between field and field manager.
		vgAssertN( field->findObserver( this ) == false, "The added field is already observed by this manager of fields." );
		field->attach( this );
		return true;
	}
	else
	{
		// Not found the field named fieldName
		vgAssertN( false, "Unable to find field named '%s'", fieldName.c_str() );
		return false;
	}
}



const bool FieldManager::setField( const FieldManager * fieldManager, const std::string& strFieldName )
{
	vgAssert( fieldManager->isField(strFieldName) );
	vgAssert( isField(strFieldName) );

	vgd::Shp< AbstractField > fieldToReplace = fieldManager->getField<AbstractField>(strFieldName);
	return setField( fieldToReplace );
}



const bool FieldManager::removeField( const std::string& strFieldName )
{
	vgAssertN( checkField( strFieldName ), "Unknown field name '%s'.", strFieldName.c_str() );

	// STEP 1 : Find the field.
	vgd::Shp<AbstractField>	shpAField = getField<AbstractField>( strFieldName );

	if ( shpAField == 0 )
	{
		// Not found.
		return false;
	}

	// STEP 2 : Remove link between field and field manager
	vgAssertN( shpAField->findObserver( this ) == true, "The removed field is not observed by this manager of fields." );
	shpAField->detach( this );

	// STEP 3 : Remove links between this field and all dirty flags.
	unlinkField( strFieldName );

	// STEP 4 : Remove field to field container.
	uint32 numRemovedElement = static_cast<uint32>(m_fields.erase( strFieldName ));
	vgAssert( numRemovedElement == 1 );

	return true;
}



void FieldManager::updateField( const AbstractField& rField, const Event event )
{
	switch ( event )
	{
		case UPDATE:
		
			updateFrom( rField.name() );
			break;

		case DESTROY:
			vgAssert(false);
			break;

		default:
			vgAssertN( false, "Unknown event" );
	}
}



void FieldManager::updateFrom( const std::string strFieldName )
{
	detail::FieldsToDirtyFlags::SetDirtyFlagNames::const_iterator iter, iterEnd;
	boost::tie( iter, iterEnd ) = m_fieldsToDirtyFlags.getIterators( strFieldName );
	
	while ( iter != iterEnd )
	{
		const std::string strDirtyFlag = *iter;
		
		MapDirtyFlag::iterator iDirtyFlag = m_dirtyFlags.find( strDirtyFlag );

		if ( iDirtyFlag != m_dirtyFlags.end() )
		{
			iDirtyFlag->second.dirty();
		}
		else
		{
			vgAssertN( false, "Dirty flag not founded" );
		}

		++iter;
	}
}



const bool FieldManager::link( const std::string strFieldName, const std::string strDirtyFlagName )
{
	vgAssertN( checkField( strFieldName ), "Unknown field name." );
	vgAssertN( checkDirtyFlag( strDirtyFlagName ), "Unknown dirty flag name." );

	// add link(in field manager) between field and dirty flag.
	// so fieldManager know how to propagate update message from
	// field(updateField method) to dirty flags.

	bool bRetVal = m_fieldsToDirtyFlags.add( strFieldName, strDirtyFlagName );
	//vgAssert( bRetVal && "This link already exist." );

	return bRetVal;
}



const bool FieldManager::link( const std::string strDirtyFlagName )
{
	vgAssertN( checkDirtyFlag( strDirtyFlagName ), "Unknown dirty flag name." );

	bool bRetVal = true;

	for(	MapField::const_iterator	i	= m_fields.begin(),
										ie	= m_fields.end();
			i != ie;
			i++ )
	{
		bRetVal &= link( i->first, strDirtyFlagName );
	}
	
	return bRetVal;
}



const bool FieldManager::unlink( const std::string strFieldName, const std::string strDirtyFlagName )
{
	vgAssertN( checkField( strFieldName ), "Unknown field name." );
	vgAssertN( checkDirtyFlag( strDirtyFlagName ), "Unknown dirty flag name." );

	// STEP 1 : Remove link(in field manager) between field and dirty flag.
	bool bRetVal = m_fieldsToDirtyFlags.remove( strFieldName, strDirtyFlagName );
	// vgAssertN( bRetVal, "nothing to unlinked, because link doesn't exist." );

	return bRetVal;
}



const bool FieldManager::unlinkField( const std::string strFieldName )
{
	vgAssertN( checkField( strFieldName ), "Unknown field name." );

	bool bRetVal = m_fieldsToDirtyFlags.removeField( strFieldName );

	return bRetVal;
}



const bool FieldManager::addDirtyFlag( const std::string& strFlagName )
{
	std::pair< MapDirtyFlag::iterator, bool > retVal;
	
	retVal = m_dirtyFlags.insert( 
		std::pair< std::string, DirtyFlag >(strFlagName, DirtyFlag(strFlagName) ) 
		);

	return retVal.second;
}



/*bool FieldManager::removeDirtyFlag( const std::string& strDirtyFlagName )
{
	assert( checkDirtyFlag( strDirtyFlagName ) && "Unknown dirty flag name." );
	
	int32 numberOfRemovedElt = m_dirtyFlags.erase( strDirtyFlagName );
	assert( (numberOfRemovedElt == 0) || (numberOfRemovedElt == 1) );

	return ( numberOfRemovedElt == 1 );
}*/



DirtyFlag* FieldManager::getDirtyFlag( const std::string strDirtyFlagName )
{
	MapDirtyFlag::iterator iDirtyFlag = m_dirtyFlags.find( strDirtyFlagName );

	if ( iDirtyFlag != m_dirtyFlags.end() )
	{
		// Found
		return ( &iDirtyFlag->second );
	}
	else
	{
		return 0;
	}
}



const DirtyFlag* FieldManager::getDirtyFlag( const std::string strDirtyFlagName ) const
{
	MapDirtyFlag::const_iterator iDirtyFlag;
	iDirtyFlag = m_dirtyFlags.find( strDirtyFlagName );

	if ( iDirtyFlag != m_dirtyFlags.end() )
	{
		// Found
		return ( &iDirtyFlag->second );
	}
	else
	{
		return 0;
	}
}



void FieldManager::getDirtyFlagNames( std::vector< std::string >& oDirtyFlagsNames ) const
{
	typedef std::vector< std::string > 						StringContainer;
	typedef std::back_insert_iterator< StringContainer >	InsertIterator;

	InsertIterator inserter( oDirtyFlagsNames );
	getDirtyFlagNames( inserter );
}



/*std::pair< MapDirtyFlag::const_iterator, MapDirtyFlag::const_iterator >	
	FieldManager::getDirtyFlagsIterators( void ) const
{
	std::pair< MapDirtyFlag::const_iterator, MapDirtyFlag::const_iterator > retVal(
		m_dirtyFlags.begin(),
		m_dirtyFlags.end() );
	
	return ( retVal );
}



std::pair< MapDirtyFlag::iterator, MapDirtyFlag::iterator >	
	FieldManager::getDirtyFlagsIterators( void )
{
	std::pair< MapDirtyFlag::iterator, MapDirtyFlag::iterator > retVal(
		m_dirtyFlags.begin(),
		m_dirtyFlags.end() );
	
	return ( retVal );
}*/



const bool FieldManager::checkField( const std::string strFieldName ) const
{
	MapField::const_iterator citer = m_fields.find( strFieldName );

	return ( citer != m_fields.end());
}



const bool FieldManager::checkDirtyFlag( const std::string strDirtyFlagName ) const
{
	MapDirtyFlag::const_iterator citer = m_dirtyFlags.find( strDirtyFlagName );

	return ( citer != m_dirtyFlags.end() );
}



} // namespace field

} // namespace vgd
