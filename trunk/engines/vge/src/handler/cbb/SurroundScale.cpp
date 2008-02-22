// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/cbb/SurroundScale.hpp"

#include <vgd/node/SurroundScale.hpp>

#include "vge/handler/SurroundScale.hpp"
#include "vge/engine/Engine.hpp"
#include "vge/service/ComputeBoundingBox.hpp"



namespace vge
{

namespace handler
{

namespace cbb
{



META_HANDLER_CPP( SurroundScale );



const Handler::TargetVector SurroundScale::getTargets()	const
{
	TargetVector targets;
	
	targets.push_back( vgd::node::SurroundScale::getClassIndexStatic() );
	
	return ( targets );
}



void SurroundScale::apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgd::node::SurroundScale* >(pNode) != 0 );
	vgd::node::SurroundScale *pCastedNode = static_cast< vgd::node::SurroundScale* >(pNode);
	
	vge::handler::SurroundScale::apply( pEngine, pCastedNode );	
}



void SurroundScale::unapply( vge::engine::Engine *, vgd::node::Node * )
{
	// nothing to do
}



void SurroundScale::setToDefaults()
{
}



} // namespace cbb
	
} // namespace handler

} // namespace vge
