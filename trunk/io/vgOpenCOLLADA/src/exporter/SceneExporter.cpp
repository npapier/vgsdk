// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/exporter/SceneExporter.hpp"

#include <vgDebug/Global.hpp>

#include <COLLADASWAsset.h>
#include "COLLADASWScene.h"

namespace vgOpenCOLLADA
{

namespace exporter
{

SceneExporter::SceneExporter(std::string filepath, vgd::Shp< vgd::node::Group > sceneGraph, vgd::Shp< vgd::node::VertexShape > node) :
m_streamWriter ( COLLADASW::NativeString (filepath), false ),
m_sceneGraph ( sceneGraph ),
m_node ( node )
{
}


bool SceneExporter::doExport()
{
	vgDebug::get().logDebug("Creating COLLADA document...");
	m_streamWriter.startDocument();

	loadExporter();

	exportAsset();

	exportEffect();

	exportMaterial();

	exportGeometry();

	exportVisualScene();

	exportScene();

	m_streamWriter.endDocument();
	vgDebug::get().logDebug("COLLADA document created!");
	
	//@todo: check if export finish well.
	return true;
}

void SceneExporter::loadExporter()
{
	m_effectExporter = new EffectExporter(&m_streamWriter, m_sceneGraph, true);
	m_materialExporter = new MaterialExporter(&m_streamWriter, this, m_sceneGraph);
	m_geometryExporter = new GeometryExporter(&m_streamWriter, m_sceneGraph, m_node);
	m_visualSceneExporter = new VisualSceneExporter(&m_streamWriter, this, m_sceneGraph);
}

void SceneExporter::exportAsset()
{
    COLLADASW::Asset asset ( &m_streamWriter );

    // Add contributor information
    // Set the author
	std::string userName = getEnvironmentVariable ( "USERNAME" );

    if ( userName.empty() )
	{
        userName = getEnvironmentVariable ( "USER" );
	}

    if ( !userName.empty() )
	{
        asset.getContributor().mAuthor = std::string ( userName );
	}

	asset.getContributor().mAuthoringTool = "vgSDK";
	
	//@todo: get unit from vgsdk?
	asset.setUnit ( "millimeter", 0.001f );

    asset.setUpAxisType ( COLLADASW::Asset::Z_UP );

    asset.add();
}


void SceneExporter::exportEffect()
{
	m_effectExporter->doExport();
}


void SceneExporter::exportMaterial()
{
	m_materialExporter->doExport();
}


void SceneExporter::exportGeometry()
{
	m_geometryExporter->doExport();
}


void SceneExporter::exportVisualScene()
{
	m_visualSceneExporter->doExport();
}

void SceneExporter::exportScene()
{
	COLLADASW::Scene scene ( &m_streamWriter, COLLADASW::URI ( "#scene" ) );
	scene.add();
}


std::string SceneExporter::getEnvironmentVariable ( const std::string & variableName )
{
    //@todo: replace with a portable method, like one in GLIB
	char * buffer;
    size_t numberOfElements;
    errno_t error = _dupenv_s ( &buffer, &numberOfElements, variableName.c_str() );

    if ( error != 0 )
    {
        free ( buffer );
		return std::string();
    }

    std::string variableValue ( buffer, numberOfElements-1 );

    free ( buffer );
    return variableValue;
}


EffectExporter* SceneExporter::getEffectExporter()
{
	return m_effectExporter;
}


GeometryExporter* SceneExporter::getGeometryExporter()
{
	return m_geometryExporter;
}



} // namespace exporter

} // namespace vgOpenCOLLADA

