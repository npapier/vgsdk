// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/TextureMatrixTransform.hpp"

#include <vgd/node/TextureMatrixTransform.hpp>

#include "vge/engine/Engine.hpp"



namespace vge
{

namespace handler
{



void TextureMatrixTransform::apply( vge::engine::Engine* pEngine, vgd::node::TextureMatrixTransform *pNode )
{
	// TEXTURE MATRIX
	// Get the transformation.
	const vgm::MatrixR& matrix	( pNode->getMatrix() );
	
	if ( pNode->getComposeTransformation() )
	{
		// Compose and update engine.
		assert( pNode->getMultiAttributeIndex() < pEngine->getMaxTexUnits() );
		vgm::MatrixR& 		current(	pEngine->getTextureMatrix().getTop( pNode->getMultiAttributeIndex() ) );
		
		current		= matrix * current;
	}
	else
	{
		// Update engine.
		assert( pNode->getMultiAttributeIndex() < pEngine->getMaxTexUnits() );		
		pEngine->getTextureMatrix().setTop( matrix, pNode->getMultiAttributeIndex() );
	}	
}



void TextureMatrixTransform::unapply( vge::engine::Engine* pEngine, vgd::node::TextureMatrixTransform *pNode )
{
}



} // namespace handler

} // namespace vge
