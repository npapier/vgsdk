// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/importer/ExtraDataCallbackHandler.hpp"


namespace vgOpenCOLLADA
{

namespace importer
{



ExtraDataCallbackHandler::ExtraDataCallbackHandler() 
    :	m_isOriginalIdField (false),
		m_currentId( false )
{
}



ExtraDataCallbackHandler::~ExtraDataCallbackHandler()
{
}



std::vector<ExtraInfo> ExtraDataCallbackHandler::findExtraInfo ( const std::string id ) const
{
	std::vector< ExtraInfo > extraInfos;
    ExtraInfosMap::const_iterator it = m_extraInfos.find ( id );
    if ( it != m_extraInfos.end () )
    {
        extraInfos = it->second;
		return extraInfos;
    }
    return extraInfos;
}



bool ExtraDataCallbackHandler::parseElement ( 
    const GeneratedSaxParser::ParserChar* profileName, 
    const COLLADASaxFWL::StringHash& elementHash, 
    const COLLADAFW::UniqueId& uniqueId ) 
{
    if ( COLLADABU::Utils::equals ( "profile_vgsdk", profileName ) ) 
    {
        return true;
    }

    return false;
}



bool ExtraDataCallbackHandler::elementBegin ( const GeneratedSaxParser::ParserChar* elementName, const GeneratedSaxParser::xmlChar** attributes ) 
{
	if ( COLLADABU::Utils::equals ( "name", std::string (elementName) ) )
    {
        m_currentId = true;
		m_isOriginalIdField = true;
    }
	else if ( COLLADABU::Utils::equals ( "matrix", std::string (elementName) ) )
    {
        m_isOriginalIdField = true;
    }

    return true;
}



bool ExtraDataCallbackHandler::elementEnd ( const GeneratedSaxParser::ParserChar* elementName ) 
{
    if ( m_isOriginalIdField )
    {
        m_isOriginalIdField = false;

		if( m_currentId )
		{
			m_currentId = false;
			return true;
		}
        m_extraInfos[ m_currentExtraInfo.getId() ].push_back( m_currentExtraInfo );
        m_currentExtraInfo.setMatrix ( "" );
    }

    return true;
}



bool ExtraDataCallbackHandler::textData ( const GeneratedSaxParser::ParserChar* text, size_t textLength ) 
{
    if ( m_isOriginalIdField )
    {
        if( m_currentId )
		{
			std::string name;
			name.assign ( text, textLength );
			m_currentExtraInfo.setId( name );
		}
		else
		{
			m_currentExtraInfo.setMatrix ( text, textLength );
		}
    }
    return true;
}



} // namespace importer

} // namespace vgOpenCOLLADA