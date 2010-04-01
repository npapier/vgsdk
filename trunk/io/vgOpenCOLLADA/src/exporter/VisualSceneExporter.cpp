// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/exporter/VisualSceneExporter.hpp"

#include "vgOpenCOLLADA/exporter/SceneExporter.hpp"

#include <vgDebug/Global.hpp>
#include <vgd/visitor/helpers.hpp>

#include "COLLADASWNode.h"
#include "COLLADASWInstanceGeometry.h"


namespace vgOpenCOLLADA
{

namespace exporter
{

	const std::string VisualSceneExporter::NODE_ID_PRAEFIX = "node-";

VisualSceneExporter::VisualSceneExporter(COLLADASW::StreamWriter * streamWriter, SceneExporter * sceneExporter, vgd::Shp< vgd::node::Group > sceneGraph) :
COLLADASW::LibraryVisualScenes ( streamWriter ),
m_sceneExporter ( sceneExporter),
m_sceneGraph( sceneGraph )
{
}

void VisualSceneExporter::doExport()
{
	vgDebug::get().logDebug("Exporting visual scenes");
	openLibrary();

	openVisualScene( "scene" );
	
	std::vector<std::string> geomList = m_sceneExporter->getGeometryExporter()->getGeomNameList();

	for( uint i = 0; i < geomList.size(); i++ )
	{
		std::string geomName = geomList[i];

		COLLADASW::Node colladaNode( mSW );

		colladaNode.setNodeId( NODE_ID_PRAEFIX + geomName );

		colladaNode.setNodeName( COLLADASW::Utils::checkNCName( COLLADABU::NativeString(NODE_ID_PRAEFIX + geomName) ) );

		colladaNode.start();	

		COLLADASW::InstanceGeometry instanceGeometry ( mSW );

		instanceGeometry.setUrl ( "#" + geomName );
		//fillInstanceMaterialList(instanceGeometry.getBindMaterial().getInstanceMaterialList(), exportNode);
		instanceGeometry.add();

		colladaNode.end();
	}

	closeVisualScene();
	closeLibrary();
}


} // namespace exporter

} // namespace vgOpenCOLLADA

