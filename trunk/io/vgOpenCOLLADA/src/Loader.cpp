// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/Loader.hpp"



namespace vgOpenCOLLADA
{

Loader::Loader(LOAD_TYPE type) throw (std::runtime_error) :
	m_reader(type),
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

	bool loadResult = m_root.loadDocument(colladaFileURI);
	
	if (!m_reader.getScene().second || !loadResult)
		throw std::runtime_error("Scene-import failed.");
		
	return m_reader.getScene();
}

} // namespace vgCollada

