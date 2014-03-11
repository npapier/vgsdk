// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/cbb/CoordinateSystem.hpp"

#include <vgd/node/CoordinateSystem.hpp>

#include "vge/handler/CoordinateSystem.hpp"
#include "vge/engine/Engine.hpp"



namespace vge
{

namespace handler
{

namespace cbb
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



} // namespace cbb

} // namespace handler

} // namespace vge
