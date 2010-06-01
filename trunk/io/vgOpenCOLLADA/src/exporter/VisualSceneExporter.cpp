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

VisualSceneExporter::VisualSceneExporter( COLLADASW::StreamWriter * streamWriter, collectedMapType collectedMap ) :
COLLADASW::LibraryVisualScenes ( streamWriter ),
m_collectedMap ( collectedMap )
{
}

void VisualSceneExporter::doExport()
{
	vgDebug::get().logDebug("Exporting visual scenes");
	openLibrary();

	openVisualScene( "scene" );
	
	typedef collectedMapType::left_map::const_iterator left_const_iterator;

	for( left_const_iterator left_iter = m_collectedMap.left.begin(), iend = m_collectedMap.left.end();
		 left_iter != iend; ++left_iter )
	{
		std::string geomName = left_iter->first->getColladaShapeName();

		COLLADASW::Node colladaNode( mSW );

		colladaNode.setNodeId( NODE_ID_PRAEFIX + geomName );

		colladaNode.setNodeName( COLLADASW::Utils::checkNCName( COLLADABU::NativeString(NODE_ID_PRAEFIX + geomName) ) );

		colladaNode.start();	

		double m[4][4];
		double n[4][4];

		left_iter->first->getGeometricalMatrix().getValue( m );

		for (size_t iRow = 0 ;iRow < 4 ; iRow++) 
		{
			for (size_t iCol = 0; iCol < 4; iCol++) 
			{
				n[iRow][iCol] = m[iCol][iRow];
			}
		}

		colladaNode.addMatrix( n );

		COLLADASW::InstanceGeometry instanceGeometry ( mSW );

		instanceGeometry.setUrl ( "#" + geomName );

		if ( left_iter->second->getMaterial() )
		{
			COLLADASW::InstanceMaterial instanceMaterial( left_iter->second->getMaterialSymbol(), "#"+left_iter->second->getMaterialId() );
			
			if( left_iter->second->getTexture() )
			{
				COLLADASW::BindVertexInput bindVertexInput("CHANNEL1", "TEXTCOORD", 1); //@todo manage multi texture		
				instanceMaterial.push_back( bindVertexInput );
			}

			instanceGeometry.getBindMaterial().getInstanceMaterialList().push_back( instanceMaterial );
		}
		instanceGeometry.add();

		colladaNode.end();
	}

	closeVisualScene();
	closeLibrary();
}


} // namespace exporter

} // namespace vgOpenCOLLADA

