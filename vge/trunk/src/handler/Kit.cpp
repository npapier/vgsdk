// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/Kit.hpp"

#include <vgd/node/Kit.hpp>

#include "vge/engine/Engine.hpp"
#include "vge/technique/ComputeBoundingBox.hpp"
#include "vge/visitor/NodeCollectorExtended.hpp"



namespace vge
{

namespace handler
{



void Kit::apply( vge::engine::Engine *pEngine, vgd::node::Kit *pNode )
{
	// nothing to do
	
	// old version:
	//	// Step 1 : Collect nodes.
	//	vge::visitor::NodeCollectorExtended<> collector;
	//	pNode->getRoot()->traverse( collector );
	//	
	//	// Step 2 : Compute bounding box for the sub scene graph (encapsulate by the kit)
	//	vge::technique::ComputeBoundingBox computeBB;
	//	computeBB.apply( pEngine, collector.getTraverseElements() );
	//	
	//	// Step 3 : Update the bounding box of the kit.
	//	vgm::MatrixR dummy;
	//	pNode->computeBoundingBox( dummy );
}



void Kit::unapply( vge::engine::Engine *pEngine, vgd::node::Kit *pNode )
{
	vgm::MatrixR dummy;
	pNode->computeBoundingBox( dummy );	
}



} // namespace handler

} // namespace vge
