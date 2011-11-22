// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson
// Author Nicolas Papier

#include "vgOpenCOLLADA/exporter/SceneExporter.hpp"

#include <COLLADASWAsset.h>
#include "COLLADASWScene.h"

#include <vgAlg/actions/ApplyGeometricalTransformation.hpp>
#include <vgAlg/actions/InvertTriangleOrientation.hpp>
#include <vgAlg/actions/Triangulate.hpp>


#include <vgDebug/helpers.hpp>

#include <vge/technique/CollectNode.hpp>
#include <vgeGL/engine/Engine.hpp>


namespace vgOpenCOLLADA
{

namespace exporter
{

SceneExporter::SceneExporter( vgOpenCOLLADA::Settings exportSettings, vgd::Shp< vgd::node::Group > rootNode )
:	m_streamWriter ( COLLADASW::NativeString ( exportSettings.getFilename() ), false ),
	m_rootNode ( rootNode ),
	m_outputFileUri(  exportSettings.getFilename()  ),
	m_exportSettings( exportSettings )
{}



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
	vgLogDebug("Collecting nodes...");
	collectNodes();

	vgLogDebug("Preparing scene to be exported...");
	prepareExport();
	
	vgLogDebug("Creating COLLADA document...");
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
	vgLogDebug("COLLADA document created!");
	
	//@todo: check if export finish well.
	return true;
}



void SceneExporter::prepareExport()
{
	if( m_exportSettings.getApplyGeometricalTransformation() )
	{
		vgAlg::actions::ApplyGeometricalTransformation action;
		action.setRoot( m_rootNode );
		action.execute();
		collectNodes();
	}

	if( m_exportSettings.getTriangulate() || m_exportSettings.getInvertPrimitiveOrientation() )
	{
		typedef collectedMapType::left_map::const_iterator left_const_iterator;

		for( left_const_iterator left_iter = m_collectedMap.left.begin(), iend = m_collectedMap.left.end();
			 left_iter != iend; ++left_iter )
		{
			if( m_exportSettings.getTriangulate() )
			{
				vgAlg::actions::Triangulate action;
				action.setNode( left_iter->first->getShape() );
				action.execute();
			}
			if( m_exportSettings.getInvertPrimitiveOrientation() )
			{
				vgAlg::actions::InvertTriangleOrientation action;
				action.setNode( left_iter->first->getShape() );
				action.execute();
			}
		}		
	}

	if( m_exportSettings.getEncrypt() )
	{

	}
}



void SceneExporter::loadExporter()
{
	m_effectExporter = new EffectExporter( &m_streamWriter, m_collectedMap, m_exportSettings );
	m_materialExporter = new MaterialExporter( &m_streamWriter, m_collectedMap, m_exportSettings );
	m_imageExporter = new ImageExporter( &m_streamWriter, m_collectedMap, m_outputFileUri, m_exportSettings );
	m_geometryExporter = new GeometryExporter( &m_streamWriter, m_collectedMap, m_exportSettings );
	m_visualSceneExporter = new VisualSceneExporter( &m_streamWriter, m_collectedMap, m_exportSettings );
}




void SceneExporter::collectNodes()
{
	using vge::visitor::NodeCollectorExtended;
	vge::technique::CollectNode technique;

	vge::engine::Engine engine;
	engine.setTrace( true );
	NodeCollectorExtended<> collector( true, false, NodeCollectorExtended<>::IGNORE_KIT );
	m_rootNode->traverse( collector );

	technique.setParameters( &engine, collector.getTraverseElements() );
	technique.apply( &engine, collector.getTraverseElements() );

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
	if( m_exportSettings.getLevel() > MATERIAL )
	{
		m_imageExporter->doExport();
	}
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

