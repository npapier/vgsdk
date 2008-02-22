// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/Camera.hpp"

#include <vgd/node/Camera.hpp>

#include "vge/engine/Engine.hpp"



namespace vge
{

namespace handler
{



void Camera::apply( vge::engine::Engine *pEngine, vgd::node::Camera *pNode )
{
	// PROJECTION MATRIX
	// Get the transformation.
	const vgm::MatrixR& matrix	( pNode->getMatrix() );
	
	if ( pNode->getComposeTransformation() )
	{
		// Compose and update engine.
		vgm::MatrixR& 		current(	pEngine->getProjectionMatrix().getTop() );
		
		current		= matrix * current;
	}
	else
	{
		// Update engine.
		pEngine->getProjectionMatrix().setTop( matrix );
	}
}



void Camera::unapply( vge::engine::Engine *, vgd::node::Camera * )
{
}



} // namespace handler

} // namespace vge
