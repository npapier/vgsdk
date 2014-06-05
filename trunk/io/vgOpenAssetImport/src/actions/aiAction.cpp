// VGSDK - Copyright (C) 2013, 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgOpenAssetImport/actions/aiAction.hpp"

#include <assimp/scene.h>

#include <vgAlg/actions/SelectedNode.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>
#include <vgOpenAssetImport/helpers.hpp>


#ifndef WIN32
namespace
{
	void aiDeleteScene( aiScene * scene )
	{
		if ( scene )
		{
			delete scene;
		}
	}
} 
#endif


namespace vgOpenAssetImport
{
namespace actions
{


void aiAction::execute()
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
	else if( node->isAKindOf< VertexShape >() )
	{
		vgd::node::VertexShape * vertexShape = vgd::dynamic_pointer_cast< VertexShape >( node ).get();

		// Create aiScene and call apply()
		aiScene * aiscene = vgOpenAssetImport::createAiScene( vertexShape );
		const bool refresh = aiExecute( aiscene );
		if ( refresh )
		{
			vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( vgAlg::actions::REFRESH );
		}
		// else nothing to do
		aiDeleteScene( aiscene );
	}
}


} // namespace actions
} // namespace vgOpenAssetImport
