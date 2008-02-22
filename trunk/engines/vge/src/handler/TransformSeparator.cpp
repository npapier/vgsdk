// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/TransformSeparator.hpp"

#include <vgd/node/TransformSeparator.hpp>

#include "vge/engine/Engine.hpp"



namespace vge
{

namespace handler
{



void TransformSeparator::apply ( vge::engine::Engine* pEngine, vgd::node::TransformSeparator *pNode )
{
	// Push.
	const int8 mask( pNode->getMask() );
	
	if ( mask & vgd::node::TransformSeparator::TEXTURE_MATRIX_BIT )
	{
		pEngine->getTextureMatrix().pushAll();
	}
	
	if ( mask & vgd::node::TransformSeparator::PROJECTION_MATRIX_BIT )
	{
		pEngine->getProjectionMatrix().push();
	}
	
	if ( mask & vgd::node::TransformSeparator::GEOMETRICAL_MATRIX_BIT )
	{
		pEngine->getGeometricalMatrix().push();
	}
}



void TransformSeparator::unapply ( vge::engine::Engine* pEngine, vgd::node::TransformSeparator* pNode )
{
	bool bRetVal;
	
	// Pop.
	const int8 mask	( pNode->getMask() );
	
	if ( mask & vgd::node::TransformSeparator::TEXTURE_MATRIX_BIT )
	{
		// Update engine.
		bRetVal = pEngine->getTextureMatrix().popAll();
		assert( bRetVal && "Stack underflow (texture)." );
	}
	
	if ( mask & vgd::node::TransformSeparator::PROJECTION_MATRIX_BIT )
	{
		// Update engine.
		bRetVal = pEngine->getProjectionMatrix().pop();
		assert( bRetVal && "Stack underflow (projection)." );
	}

	if ( mask & vgd::node::TransformSeparator::GEOMETRICAL_MATRIX_BIT )
	{
		// Update engine.
		bRetVal = pEngine->getGeometricalMatrix().pop();
		assert( bRetVal && "Stack underflow (geometrical)." );
	}
}



} // namespace handler

} // namespace vge
