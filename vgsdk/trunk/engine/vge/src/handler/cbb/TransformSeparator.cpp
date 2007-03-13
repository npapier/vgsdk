// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/cbb/TransformSeparator.hpp"

#include <vgd/node/TransformSeparator.hpp>

#include "vge/handler/TransformSeparator.hpp"
#include "vge/engine/Engine.hpp"
#include "vge/service/ComputeBoundingBox.hpp"



namespace vge
{

namespace handler
{

namespace cbb
{



META_HANDLER_CPP( TransformSeparator );



const Handler::TargetVector TransformSeparator::getTargets()	const
{
	TargetVector targets;
	
	targets.push_back( vgd::node::TransformSeparator::getClassIndexStatic() );
	
	return ( targets );
}



void TransformSeparator::apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgd::node::TransformSeparator* >(pNode) != 0 );
	vgd::node::TransformSeparator *pCastedNode = static_cast< vgd::node::TransformSeparator* >(pNode);

	Group::apply( pEngine, pCastedNode ); // do nothing

	vge::handler::TransformSeparator::apply( pEngine, pCastedNode );	
}



void TransformSeparator::unapply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgd::node::TransformSeparator* >(pNode) != 0 );
	vgd::node::TransformSeparator *pCastedNode = static_cast< vgd::node::TransformSeparator* >(pNode);

	Group::unapply( pEngine, pCastedNode );

	vge::handler::TransformSeparator::unapply( pEngine, pCastedNode );
}



void TransformSeparator::setToDefaults()
{
}



} // namespace cbb
	
} // namespace handler

} // namespace vge
