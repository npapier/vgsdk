// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgOpenAssetImport/actions/aiPostProcessing.hpp"

#include <assimp/scene.h>
#include <assimp/IOSystem.hpp>
#include <assimp/Exporter.hpp>

#include <vgAlg/actions/SelectedNode.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>
#include <vgOpenAssetImport/helpers.hpp>



namespace vgOpenAssetImport
{

namespace actions
{



// AIPOSTPROCESSING
aiPostProcessing::aiPostProcessing()
{}



void aiPostProcessing::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();

	using vgd::node::VertexShape;
	using vgd::node::Group;
	if ( node->isAKindOf< Group >() )
	{
		vgd::node::Group * group = vgd::dynamic_pointer_cast< Group >( node ).get();
		// @todo implementation
		vgAssertN( false, "Not yet implemented" );
	}
	else if( node->isA< VertexShape >() )
	{
		vgd::node::VertexShape * vertexShape = vgd::dynamic_pointer_cast< VertexShape >( node ).get();

		// Create aiScene and call apply()
		aiScene * aiscene = vgOpenAssetImport::createAiScene( vertexShape );
		const bool refresh = apply( aiscene );
		if ( refresh )
		{
			vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( vgAlg::actions::REFRESH );
		}
		// else nothing to do
		aiDeleteScene( aiscene );
	}
}


// AIEXPORTCOLLADA
const bool aiExportCollada::apply( const aiScene * scene )
{
	Assimp::Exporter exporter;
	exporter.Export( scene, "collada", "assimpExport.dae", 0u );

	return false;
}


// AIEXPORTOBJ
const bool aiExportObj::apply( const aiScene * scene )
{
	Assimp::Exporter exporter;
	exporter.Export( scene, "obj", "assimpExport.obj", 0u );

	return false;
}


// AIEXPORTSTL
const bool aiExportStl::apply( const aiScene * scene )
{
	Assimp::Exporter exporter;
	exporter.Export( scene, "stl", "assimpExport.stl", 0u );

	return false;
}


// AIEXPORTPLY
const bool aiExportPly::apply( const aiScene * scene )
{
	Assimp::Exporter exporter;
	exporter.Export( scene, "ply", "assimpExport.ply", 0u );

	return false;
}


} // namespace actions

} // namespace vgOpenAssetImport
