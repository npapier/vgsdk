// VGSDK - Copyright (C) 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/basic/Camera.hpp"

#include <vgd/node/Camera.hpp>

#include "vge/handler/Camera.hpp"
#include "vge/engine/Engine.hpp"
#include "vge/service/ComputeBoundingBox.hpp"



namespace vge
{

namespace handler
{

namespace basic
{



META_HANDLER_CPP( Camera );



const Handler::TargetVector Camera::getTargets() const
{
	TargetVector targets;

	targets.push_back( vgd::node::Camera::getClassIndexStatic() );

	return targets;
}



void Camera::apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgd::node::Camera* >(pNode) != 0 );
	vgd::node::Camera *pCastedNode = dynamic_cast< vgd::node::Camera* >(pNode);

	vge::handler::Camera::apply( pEngine, pCastedNode );
}



void Camera::unapply( vge::engine::Engine *, vgd::node::Node * )
{
	// nothing to do
	//assert( dynamic_cast< vgd::node::Camera* >(pNode) != 0 );
	//vgd::node::Camera *pCastedNode = static_cast< vgd::node::Camera* >(pNode);

	//vge::handler::Camera::unapply( pEngine, pCastedNode );
}



void Camera::setToDefaults()
{
}



} // namespace basic

} // namespace handler

} // namespace vge
