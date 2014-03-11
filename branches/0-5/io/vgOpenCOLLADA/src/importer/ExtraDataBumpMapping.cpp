// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/importer/ExtraDataBumpMapping.hpp"

#include <iostream>

namespace vgOpenCOLLADA
{

namespace importer
{



ExtraDataBumpMapping::ExtraDataBumpMapping() 
    :	m_isOriginalIdField (false)
{
}



ExtraDataBumpMapping::~ExtraDataBumpMapping()
{
}



std::vector<BumpMappingInfo> ExtraDataBumpMapping::findExtraInfo (const COLLADAFW::UniqueId uniqueId ) const
{
	std::vector< BumpMappingInfo > extraInfos;
    ExtraInfosMap::const_iterator it = m_extraInfos.find ( uniqueId );
    if ( it != m_extraInfos.end () )
    {
        extraInfos = it->second;
		return extraInfos;
    }
    return extraInfos;
}



bool ExtraDataBumpMapping::parseElement ( 
    const GeneratedSaxParser::ParserChar* profileName, 
    const COLLADASaxFWL::StringHash& elementHash, 
    const COLLADAFW::UniqueId& uniqueId ) 
{
    if ( COLLADABU::Utils::equals ( "OpenCOLLADA3dsMax", profileName ) ) 
    {
		m_currentId = uniqueId;
		return true;
    }

    return false;
}



bool ExtraDataBumpMapping::elementBegin ( const GeneratedSaxParser::ParserChar* elementName, const GeneratedSaxParser::xmlChar** attributes ) 
{
	if ( COLLADABU::Utils::equals ( "bump", std::string (elementName) ) )
    {
		m_isOriginalIdField = true;
    }
	else if( attributes )
	{
		for( int i = 0; i < ( sizeof( attributes ) / sizeof( char ) ) -1 ; ++i ) //last item dont count
		{
			std::string attribute = attributes[ i ];
			std::string value = attributes[ i+1 ];
			if( attribute == "texture" )
			{
				m_currentExtraInfo.setTexture( value );
			}

			if( attribute == "texcoord" )
			{
				m_currentExtraInfo.setChannel( value );
			}
		}
		
		m_currentExtraInfo.setUniqueId( m_currentId );
        m_extraInfos[ m_currentId ].push_back( m_currentExtraInfo );
	}

    return true;
}



bool ExtraDataBumpMapping::elementEnd ( const GeneratedSaxParser::ParserChar* elementName ) 
{
    if ( m_isOriginalIdField )
    {
        m_isOriginalIdField = false;
    }

    return true;
}



bool ExtraDataBumpMapping::textData ( const GeneratedSaxParser::ParserChar* text, size_t textLength ) 
{
  //  if ( m_isOriginalIdField )
  //  {
  //      if( m_currentId )
		//{
		//	std::string name;
		//	name.assign( text, textLength );
		//	m_currentExtraInfo.setId( name );
		//}
		//else
		//{
		//	m_currentExtraInfo.setTexture( text, textLength );
		//}
  //  }
    return true;
}



} // namespace importer

} // namespace vgOpenCOLLADA