// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/importer/ExtraDataMultiInstance.hpp"


namespace vgOpenCOLLADA
{

namespace importer
{



ExtraDataMultiInstance::ExtraDataMultiInstance() 
    :	m_isOriginalIdField (false)
{
}



ExtraDataMultiInstance::~ExtraDataMultiInstance()
{
}



std::vector<MultiInstanceInfo> ExtraDataMultiInstance::findExtraInfo ( const COLLADAFW::UniqueId uniqueId ) const
{
	std::vector< MultiInstanceInfo > extraInfos;
    ExtraInfosMap::const_iterator it = m_extraInfos.find ( uniqueId );
    if ( it != m_extraInfos.end () )
    {
        extraInfos = it->second;
		return extraInfos;
    }
    return extraInfos;
}



bool ExtraDataMultiInstance::parseElement ( 
    const GeneratedSaxParser::ParserChar* profileName, 
    const COLLADASaxFWL::StringHash& elementHash, 
    const COLLADAFW::UniqueId& uniqueId ) 
{
    if ( COLLADABU::Utils::equals ( "profile_vgsdk", profileName ) ) 
    {
        m_currentExtraInfo.setUniqueId( uniqueId );
		return true;
    }

    return false;
}



bool ExtraDataMultiInstance::elementBegin ( const GeneratedSaxParser::ParserChar* elementName, const GeneratedSaxParser::xmlChar** attributes ) 
{
	if ( COLLADABU::Utils::equals ( "matrix", std::string (elementName) ) )
    {
        m_isOriginalIdField = true;
    }

    return true;
}



bool ExtraDataMultiInstance::elementEnd ( const GeneratedSaxParser::ParserChar* elementName ) 
{
    if ( m_isOriginalIdField )
    {
        m_isOriginalIdField = false;

        m_extraInfos[ m_currentExtraInfo.getUniqueId() ].push_back( m_currentExtraInfo );
        m_currentExtraInfo.setMatrix ( "" );
    }

    return true;
}



bool ExtraDataMultiInstance::textData ( const GeneratedSaxParser::ParserChar* text, size_t textLength ) 
{
    if ( m_isOriginalIdField )
    {
		m_currentExtraInfo.setMatrix ( text, textLength );
    }
    return true;
}



} // namespace importer

} // namespace vgOpenCOLLADA