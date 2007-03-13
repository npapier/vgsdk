// VGSDK - Copyright (C) 2004, 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/field/detail/FieldsToDirtyFlags.hpp"

#include "vgd/field/DirtyFlag.hpp"



namespace vgd
{

namespace field
{
	
namespace detail
{



FieldsToDirtyFlags::FieldsToDirtyFlags() 
{}



const bool FieldsToDirtyFlags::add( const std::string strFieldName, const std::string strDirtyFlagName )
{
	SetDirtyFlagNames& rsetDirtyFlags = get( strFieldName );

	std::pair< SetDirtyFlagNames::iterator, bool > retVal = 
		rsetDirtyFlags.insert( strDirtyFlagName );
		
	return retVal.second;
}



const bool FieldsToDirtyFlags::remove( const std::string strFieldName, const std::string strDirtyFlagName )
{
	MapLinks::iterator iMapLinks = m_links.find( strFieldName );
	
	if ( iMapLinks != m_links.end() )
	{
		// Found the desired field.
		return ( iMapLinks->second.erase( strDirtyFlagName ) == 1 );
	}
	else
	{
		// Field not found.
		return false;
	}
}



const bool FieldsToDirtyFlags::removeField( const std::string strFieldName )
{
	MapLinks::iterator iMapLinks = m_links.find( strFieldName );
	
	if ( iMapLinks != m_links.end() )
	{
		// Found the desired field.
		iMapLinks->second.clear();
		
		return true;
	}
	else
	{
		// Field not found.
		return false;
	}
}



std::pair< FieldsToDirtyFlags::SetDirtyFlagNames::iterator, FieldsToDirtyFlags::SetDirtyFlagNames::iterator >
	FieldsToDirtyFlags::getIterators( const std::string strFieldName )
{
	SetDirtyFlagNames& rsetDirtyFlags = get( strFieldName );
	
	std::pair< SetDirtyFlagNames::iterator, SetDirtyFlagNames::iterator > retVal;
	
	retVal.first	= rsetDirtyFlags.begin();
	retVal.second	= rsetDirtyFlags.end();
	
	return retVal;
}



const uint32 FieldsToDirtyFlags::getNumFields() const
{
	return static_cast<uint32>( m_links.size() );
}



const uint32 FieldsToDirtyFlags::getNumLinkedDirtyFlags( const std::string strFieldName )
{
	return static_cast<uint32>( get(strFieldName).size() );
}



FieldsToDirtyFlags::SetDirtyFlagNames& FieldsToDirtyFlags::get( const std::string strFieldName )
{
	MapLinks::iterator iMapLinks = m_links.find( strFieldName );
	
	if ( iMapLinks != m_links.end() )
	{
		// Found the desired field.
		return iMapLinks->second;
	}
	else
	{
		// Field not found, insert it.
		std::pair< MapLinks::iterator, bool > retVal = 
			m_links.insert( std::make_pair(strFieldName, SetDirtyFlagNames()) );

		assert( retVal.second );
		return retVal.first->second;
	}
}



} // namespace detail

} // namespace field

} // namespace vgd
