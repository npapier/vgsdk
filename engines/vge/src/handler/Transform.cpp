// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/Transform.hpp"

#include <vgd/node/Transform.hpp>

#include "vge/engine/Engine.hpp"



namespace vge
{

namespace handler
{



void Transform::apply( vge::engine::Engine *pEngine, vgd::node::Transform *pNode )
{
	// GEOMETRICAL MATRIX
	// Compute the transformation.
	vgm::MatrixR matrix;
	
	matrix = pNode->gethMatrix();

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



void Transform::unapply( vge::engine::Engine *, vgd::node::Transform * )
{
}



} // namespace handler

} // namespace vge
