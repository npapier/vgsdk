// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/importer/Loader.hpp"

namespace vgOpenCOLLADA
{

namespace importer
{

META_LOADER_CPP( vgOpenCOLLADA::importer::Loader, "collada" )


Loader::Loader( vgOpenCOLLADA::Settings settings ) throw (std::runtime_error)
:	m_reader( settings, this ),
	m_saxLoader( &m_errorHandler ),
	m_root( &m_saxLoader, &m_reader )
{
	//only read flaged elements.
	m_saxLoader.setObjectFlags(COLLADASaxFWL::Loader::ASSET_FLAG | COLLADASaxFWL::Loader::VISUAL_SCENES_FLAG |\
								COLLADASaxFWL::Loader::LIBRARY_NODES_FLAG | COLLADASaxFWL::Loader::GEOMETRY_FLAG |\
								COLLADASaxFWL::Loader::IMAGE_FLAG | COLLADASaxFWL::Loader::EFFECT_FLAG | COLLADASaxFWL::Loader::MATERIAL_FLAG );	
		
}



std::pair< bool, vgd::Shp< vgd::node::Group > > Loader::load( const std::string filePath, const bool bCCW ) throw (std::runtime_error)
{
	COLLADAFW::String colladaFileURI = COLLADABU::URI::nativePathToUri(filePath);

	m_saxLoader.registerExtraDataCallbackHandler ( &m_extraDataMultiInstance );
	m_saxLoader.registerExtraDataCallbackHandler ( &m_extraDataBumpMapping );

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



std::pair< bool, vgd::Shp< vgd::node::Group > > Loader::load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, const bool bCCW ) throw (std::runtime_error)
{
	COLLADAFW::String colladaFileURI = COLLADABU::URI::nativePathToUri(filePath);

	m_saxLoader.registerExtraDataCallbackHandler ( &m_extraDataMultiInstance );
	m_saxLoader.registerExtraDataCallbackHandler ( &m_extraDataBumpMapping );

	bool loadResult = m_root.loadDocument(colladaFileURI, &(*outBuffer)[0], outBuffer->size() );

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



std::pair< bool, vgd::Shp< vgd::node::Group > > Loader::load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, std::map< std::string, vgd::Shp< vgd::basic::Image > > imageMap, const bool bCCW )
{
	m_reader.setImageMap( imageMap );

	return load( filePath, outBuffer );
}



const ExtraDataMultiInstance& Loader::getExtraDataMultiInstance()
{
	return m_extraDataMultiInstance;
}



const ExtraDataBumpMapping& Loader::getExtraDataBumpMapping()
{
	return m_extraDataBumpMapping;
}



vgd::Shp< vgio::ILoader > Loader::clone()
{
	return vgd::Shp< vgio::ILoader >( new Loader );
}



} // namespace importer

} // namespace vgCollada

