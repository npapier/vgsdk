// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
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



void Camera::apply( vge::engine::Engine *engine, vgd::node::Camera *node )
{
	applyMatrix( engine, node );
	applyLookAt( engine, node );
}



void Camera::unapply( vge::engine::Engine *engine, vgd::node::Camera *node )
{
	//unapplyMatrix( engine, node );
	//unapplyLookAt( engine, node );
}



void Camera::applyMatrix( vge::engine::Engine *engine, vgd::node::Camera *node )
{
	// PROJECTION MATRIX
	// Gets the transformation
	const vgm::MatrixR& matrix( node->getProjection() );
	
	if ( node->getComposeTransformation() )
	{
		// Composes and updates engine
		vgm::MatrixR& 		current(	engine->getProjectionMatrix().getTop() );

		current		= matrix * current;
	}
	else
	{
		// Updates engine
		engine->getProjectionMatrix().setTop( matrix );
	}
}



void Camera::applyLookAt( vge::engine::Engine *engine, vgd::node::Camera *node )
{
	// GEOMETRICAL MATRIX
	// Gets the transformation
	const vgm::MatrixR& matrix( node->getLookAt() );

	// Updates engine
	engine->getGeometricalMatrix().setTop( matrix );
}



} // namespace handler

} // namespace vge
