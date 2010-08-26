// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/exporter/VisualSceneExporter.hpp"

#include <vgOpenCOLLADA/exporter/InstanceGeometry.hpp>
#include <vgOpenCOLLADA/exporter/SceneExporter.hpp>


#include <vgDebug/Global.hpp>
#include <vgd/node/MultipleInstances.hpp>
#include <vgd/visitor/helpers.hpp>

#include <COLLADASWNode.h>


namespace vgOpenCOLLADA
{

namespace exporter
{

const std::string VisualSceneExporter::NODE_ID_PRAEFIX = "node-";

VisualSceneExporter::VisualSceneExporter( COLLADASW::StreamWriter * streamWriter, collectedMapType collectedMap, vgOpenCOLLADA::Settings exportSettings ) :
COLLADASW::LibraryVisualScenes ( streamWriter ),
m_collectedMap ( collectedMap ),
m_exportSettings( exportSettings )
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

		std::string nodeName = COLLADASW::Utils::checkNCName( COLLADABU::NativeString(NODE_ID_PRAEFIX + geomName) );
		colladaNode.setNodeName( nodeName );

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

		InstanceGeometry instanceGeometry ( mSW );

		if( left_iter->first->getShapeType() == vge::technique::MULTIPLEINSTANCES )
		{
			vgd::Shp< vgd::node::MultipleInstances > multipleInstances = vgd::dynamic_pointer_cast< vgd::node::MultipleInstances >(  left_iter->first->getShape() );
			
			instanceGeometry.setName( nodeName );
			vgd::field::EditorRO< vgd::node::MultipleInstances::FMatrixType > matrixEdit = multipleInstances->getMatrixRO();
			for( uint it = 0; it < matrixEdit->size(); it++ )
			{
				vgm::MatrixR m = (*matrixEdit)[it];
				instanceGeometry.addMultipleInstanceMatrix( m );
			}

			instanceGeometry.createMultipleInstances();
		}

		instanceGeometry.setUrl ( "#" + geomName );

		if ( left_iter->second->getMaterial() && m_exportSettings.getLevel() > GEOMETRY )
		{
			COLLADASW::InstanceMaterial instanceMaterial( left_iter->second->getMaterialSymbol(), "#"+left_iter->second->getMaterialId() );
			
			if( left_iter->second->getTexture() && m_exportSettings.getLevel() > MATERIAL )
			{
				COLLADASW::BindVertexInput bindVertexInput("CHANNEL1", "TEXTCOORD", 1); //@todo manage multi texture		
				instanceMaterial.push_back( bindVertexInput );
			}

			instanceGeometry.getBindMaterial().getInstanceMaterialList().push_back( instanceMaterial );
		}
		else
		{
			COLLADASW::InstanceMaterial instanceMaterial( left_iter->second->getMaterialSymbol(), "#DefaultWhole-material" );

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
