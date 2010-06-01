// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/exporter/SceneExporter.hpp"

#include <COLLADASWAsset.h>
#include "COLLADASWScene.h"

#include <vgDebug/Global.hpp>

#include <vge/technique/CollectNode.hpp>
#include <vgeGL/engine/Engine.hpp>


namespace vgOpenCOLLADA
{

namespace exporter
{

SceneExporter::SceneExporter( std::string filepath, vgd::Shp< vgd::node::Group > rootNode ) :
m_streamWriter ( COLLADASW::NativeString (filepath), false ),
m_rootNode ( rootNode ),
m_outputFileUri( filepath )
{
}



SceneExporter::~SceneExporter()
{
	//std::list< vgd::Shp< vge::technique::CollectedShape > >::iterator it;

	//for( it = m_collectedShapeList.begin(); it != m_collectedShapeList.end(); it++ )
	//{
	//	(*it).reset();
	//}
}



bool SceneExporter::doExport()
{
	vgDebug::get().logDebug("Collecting nodes...");
	collectNodes();
	
	vgDebug::get().logDebug("Creating COLLADA document...");
	m_streamWriter.startDocument();

	loadExporter();

	exportAsset();

	exportImage();

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
	m_effectExporter = new EffectExporter( &m_streamWriter, m_collectedMap );
	m_materialExporter = new MaterialExporter( &m_streamWriter, m_collectedMap );
	m_imageExporter = new ImageExporter( &m_streamWriter, m_collectedMap, m_outputFileUri );
	m_geometryExporter = new GeometryExporter( &m_streamWriter, m_collectedMap );
	m_visualSceneExporter = new VisualSceneExporter( &m_streamWriter, m_collectedMap );
}




void SceneExporter::collectNodes()
{
	using vge::visitor::NodeCollectorExtended;
	vge::technique::CollectNode technique;

	vgeGL::engine::Engine* engine = new vgeGL::engine::Engine();
	engine->setTrace( true );
	NodeCollectorExtended<> collector( true, false, NodeCollectorExtended<>::IGNORE_KIT );
	m_rootNode->traverse( collector );

	technique.apply( engine, collector.getTraverseElements() );

	m_collectedMap = technique.getCollectedMap();
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


void SceneExporter::exportImage()
{
	m_imageExporter->doExport();
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



} // namespace exporter

} // namespace vgOpenCOLLADA

