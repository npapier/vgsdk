// VGSDK - Copyright (C) 2004, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/basic/Kits.hpp"

#include <vgd/node/NullDragger.hpp>
#include <vgd/node/Scale1Dragger.hpp>
#include <vgd/node/TransformDragger.hpp>



namespace vge
{

namespace handler
{

namespace basic
{



META_HANDLER_CPP( Kits );



const Handler::TargetVector Kits::getTargets() const
{
	TargetVector targets;

	targets.reserve( 3 );

	targets.push_back( vgd::node::NullDragger::getClassIndexStatic() );
	targets.push_back( vgd::node::Scale1Dragger::getClassIndexStatic() );
	targets.push_back( vgd::node::TransformDragger::getClassIndexStatic() );

	return targets;
}



void Kits::apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgd::node::Kit* >(pNode) != 0 );
	vgd::node::Kit *pKit = static_cast< vgd::node::Kit* >(pNode);

	vge::handler::Kit::apply( pEngine, pKit );
}



void Kits::unapply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgd::node::Kit* >(pNode) != 0 );
	vgd::node::Kit *pKit = static_cast< vgd::node::Kit* >(pNode);

	vge::handler::Kit::unapply( pEngine, pKit );
}



void Kits::setToDefaults()
{
}



} // namespace basic

} // namespace handler

} // namespace vge
