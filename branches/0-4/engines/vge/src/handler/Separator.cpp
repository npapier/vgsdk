// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/Separator.hpp"

#include <vgd/node/Separator.hpp>

#include "vge/engine/Engine.hpp"



namespace vge
{

namespace handler
{



/**
 * @todo Check overflow in stack.
 */
void Separator::apply ( vge::engine::Engine* pEngine, vgd::node::Separator * )
{
	//vge::TransformSeparator::apply( pEngine, pNode ); FIXME REMOVE ME

	// Push software part.
	pEngine->pushStateStack();
	assert( pEngine->sizeOfStateStack() <= 12 );
}



void Separator::unapply ( vge::engine::Engine* pEngine, vgd::node::Separator* )
{
	//vge::TransformSeparator::unapply( pEngine, pNode ); FIXME REMOVE ME

	// Pop software part.
	pEngine->popStateStack();
	assert( pEngine->sizeOfStateStack() >= 1 );
}



} // namespace handler

} // namespace vge
