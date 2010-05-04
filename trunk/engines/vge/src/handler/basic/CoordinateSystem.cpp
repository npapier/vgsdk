// VGSDK - Copyright (C) 2008, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/basic/CoordinateSystem.hpp"

#include <vgd/node/CoordinateSystem.hpp>

#include "vge/handler/CoordinateSystem.hpp"
#include "vge/engine/Engine.hpp"



namespace vge
{

namespace handler
{

namespace basic
{



META_HANDLER_CPP( CoordinateSystem );



const Handler::TargetVector CoordinateSystem::getTargets()	const
{
	TargetVector targets;

	targets.push_back( vgd::node::CoordinateSystem::getClassIndexStatic() );

	return targets;
}



void CoordinateSystem::apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgd::node::CoordinateSystem* >(pNode) != 0 );
	vgd::node::CoordinateSystem *pCastedNode = static_cast< vgd::node::CoordinateSystem* >(pNode);

	vge::handler::CoordinateSystem::apply( pEngine, pCastedNode );
}



void CoordinateSystem::unapply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	// Do nothing
	/*assert( dynamic_cast< vgd::node::CoordinateSystem* >(pNode) != 0 );
	vgd::node::CoordinateSystem *pCastedNode = static_cast< vgd::node::CoordinateSystem* >(pNode);

	vge::handler::CoordinateSystem::unapply( pEngine, pCastedNode );*/
}



void CoordinateSystem::setToDefaults()
{
}



} // namespace basic

} // namespace handler

} // namespace vge
