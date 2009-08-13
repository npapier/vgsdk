// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/cbb/Transform.hpp"

#include <vgd/node/Transform.hpp>

#include "vge/handler/Transform.hpp"
#include "vge/engine/Engine.hpp"
#include "vge/service/ComputeBoundingBox.hpp"



namespace vge
{

namespace handler
{

namespace cbb
{



META_HANDLER_CPP( Transform );



const Handler::TargetVector Transform::getTargets()	const
{
	TargetVector targets;

	targets.push_back( vgd::node::Transform::getClassIndexStatic() );

	return targets;
}



void Transform::apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgd::node::Transform* >(pNode) != 0 );
	vgd::node::Transform *pCastedNode = dynamic_cast< vgd::node::Transform* >(pNode);

	vge::handler::Transform::apply( pEngine, pCastedNode );	
}



void Transform::unapply( vge::engine::Engine *, vgd::node::Node * )
{
	// nothing to do
}



void Transform::setToDefaults()
{
}



} // namespace cbb

} // namespace handler

} // namespace vge
