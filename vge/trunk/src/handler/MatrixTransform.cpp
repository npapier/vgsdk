// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/MatrixTransform.hpp"

#include <vgd/node/MatrixTransform.hpp>

#include "vge/engine/Engine.hpp"



namespace vge
{

namespace handler
{



void MatrixTransform::apply( vge::engine::Engine *pEngine, vgd::node::MatrixTransform *pNode )
{
	// GEOMETRICAL MATRIX
	// Get the transformation.
	const vgm::MatrixR& matrix	( pNode->getMatrix() );
	
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



void MatrixTransform::unapply( vge::engine::Engine *pEngine, vgd::node::MatrixTransform *pNode )
{
}



} // namespace handler

} // namespace vge
