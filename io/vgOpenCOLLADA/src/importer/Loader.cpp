// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/importer/Loader.hpp"



namespace vgOpenCOLLADA
{

namespace importer
{

Loader::Loader(LOAD_TYPE type) throw (std::runtime_error) :
	m_reader(type, this),
	m_saxLoader(&m_errorHandler),
	m_root(&m_saxLoader, &m_reader)
{
		//only read flaged elements.
		m_saxLoader.setObjectFlags(COLLADASaxFWL::Loader::ASSET_FLAG | COLLADASaxFWL::Loader::VISUAL_SCENES_FLAG |\
									COLLADASaxFWL::Loader::LIBRARY_NODES_FLAG | COLLADASaxFWL::Loader::GEOMETRY_FLAG |\
									COLLADASaxFWL::Loader::IMAGE_FLAG | COLLADASaxFWL::Loader::EFFECT_FLAG | COLLADASaxFWL::Loader::MATERIAL_FLAG );	
		
}

std::pair< bool, vgd::Shp< vgd::node::Group > > Loader::load(const std::string filePath) throw (std::runtime_error)
{
	COLLADAFW::String colladaFileURI = COLLADABU::URI::nativePathToUri(filePath);

	m_saxLoader.registerExtraDataCallbackHandler ( &m_extraDataCallbackHandler );

	bool loadResult = m_root.loadDocument(colladaFileURI);

	if( loadResult )
	{
		if ( m_reader.getScene().second )
		{
			return m_reader.getScene();
		}
		else
		{
			throw std::runtime_error("Scene-import failed.");
		}
	}
	else
	{
		throw std::runtime_error("Scene-import failed.");
	}
}



const ExtraDataCallbackHandler& Loader::getExtraDataCallbackHandler()
{
	return m_extraDataCallbackHandler;
}



} // namespace importer

} // namespace vgCollada

