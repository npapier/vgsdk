// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/cbb/Group.hpp"

#include <vgd/node/Group.hpp>
#include <vgd/node/MultiSwitch.hpp>
#include <vgd/node/Separator.hpp>
#include <vgd/node/Switch.hpp>

#include "vge/engine/Engine.hpp"
#include "vge/service/ComputeBoundingBox.hpp"



namespace vge
{

namespace handler
{

namespace cbb
{



META_HANDLER_CPP( Group );



const Handler::TargetVector Group::getTargets()	const
{
	TargetVector targets;
	
	targets.reserve( 4 );
	targets.push_back( vgd::node::Group::getClassIndexStatic() );
	targets.push_back( vgd::node::MultiSwitch::getClassIndexStatic() );
	targets.push_back( vgd::node::Separator::getClassIndexStatic() );
	targets.push_back( vgd::node::Switch::getClassIndexStatic() );				
		
	return ( targets );
}



void Group::apply( vge::engine::Engine *, vgd::node::Node * )
{
	// Nothing to do.
}



void Group::unapply( vge::engine::Engine *, vgd::node::Node *pNode )
{
	// All children have already been traversed. Update now the bounding box of this group.
	assert( dynamic_cast< vgd::node::Group* >(pNode) != 0 );
	vgd::node::Group *pCastedNode = static_cast< vgd::node::Group* >(pNode);
	
	vgm::MatrixR dummy;
	pCastedNode->computeBoundingBox( dummy /* not used */);
}



void Group::setToDefaults()
{
}



} // namespace cbb
	
} // namespace handler

} // namespace vge
