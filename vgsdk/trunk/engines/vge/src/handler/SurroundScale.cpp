// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/SurroundScale.hpp"

//#include <vgd/graph/Graph.hpp> ///< @todo FIXME see ->traverse()
#include <vgd/node/Group.hpp>
#include <vgd/node/Shape.hpp>
#include <vgd/node/SurroundScale.hpp>

#include "vge/engine/Engine.hpp"
#include "vge/technique/ComputeBoundingBox.hpp"
#include "vge/visitor/NodeCollectorExtended.hpp"



namespace vge
{

namespace handler
{



void SurroundScale::apply( vge::engine::Engine *pEngine, vgd::node::SurroundScale *pNode )
{
	if ( pNode->getSurround().get() == 0 )
	{
		// nothing to do
		return;
	}
	// else surround field is defined.

	// Compute geometrical transformation.
	vgm::MatrixR matrix;

	vgd::Shp< vgd::node::Group > pSurroundedGroup(
		vgd::dynamic_pointer_cast< vgd::node::Group >( pNode->getSurround() )
				);
				
	vgd::Shp< vgd::node::IBoundingBox > pSurrounded (
		vgd::dynamic_pointer_cast< vgd::node::IBoundingBox >( pNode->getSurround() )
				);

	if ( pSurroundedGroup.get() != 0 )
	{
		// Surround node is a group.
		
		// Step 1 : Collect nodes.
		vge::visitor::NodeCollectorExtended<> collector;
		pSurroundedGroup->traverse( collector );
	
		// Step 2 : Compute bounding box for the surrounded groug
		// FIXME optme : always recompute !!!
		// FIXME see vgd::node::SurroundScale todo
		vge::technique::ComputeBoundingBox computeBB;
	   
		// FIXME : push/pop is expensive => use another ready to use engine ?
		pEngine->pushStateStack();
		pEngine->getGeometricalMatrix().pushAll();
		pEngine->getProjectionMatrix().pushAll();
		pEngine->getTextureMatrix().pushAll();
	   
		computeBB.apply( pEngine, collector.getTraverseElements() );
	
		pEngine->getTextureMatrix().popAll();      
		pEngine->getProjectionMatrix().popAll();
		pEngine->getGeometricalMatrix().popAll();
		pEngine->popStateStack();
	   
		// Step 3 : Compute the transformation.
		const vgm::Box3f& box	= pSurroundedGroup->getBoundingBox();
		if ( !box.isEmpty() )
		{
			vgm::Vec3f boxSize		= box.getSize();
			vgm::Vec3f boxCenter	= box.getCenter();
	
			matrix.setTranslate( boxCenter );
			matrix.scale( boxSize );
		}
		else
		{
			matrix.setIdentity();			
		}
	}
	else if ( pSurrounded.get() != 0 )
	{
		// Surround node is not a group, but implements a IBoundingBox (it's a shape).
		assert( pNode->getSurround()->isAKindOf< vgd::node::Shape >() && "surround field is not a shape !!!" );
		
		// Step 1 : Compute the transformation.
		const vgm::Box3f&		box			= pSurrounded->getBoundingBox();

		vgm::Vec3f				boxSize		= box.getSize();
		vgm::Vec3f				boxCenter	= box.getCenter();

		matrix = pSurrounded->getTransformation();
		matrix.translate( boxCenter );
		matrix.scale( boxSize );
	}

	// GEOMETRICAL MATRIX
	if ( pNode->getComposeTransformation() )
	{
		// Compose and update engine.
		vgm::MatrixR& 		current(	pEngine->getGeometricalMatrix().getTop() );
		
		current		= matrix * current;
	}
	else
	{
		// Update engine.
		pEngine->getGeometricalMatrix().setTop( matrix );
	}
}



void SurroundScale::unapply( vge::engine::Engine *, vgd::node::SurroundScale * )
{
}



} // namespace handler

} // namespace vge
