// VGSDK - Copyright (C) 2004, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/painter/Group.hpp"

#include <vgd/node/Node.hpp>



namespace vge
{

namespace handler
{

namespace painter
{



void Group::apply( vge::engine::Engine * /*engine*/, vgd::node::Node * node )
{
	// Validates node
	node->getDirtyFlag(node->getDFNode())->validate();
}



} // namespace painter

} // namespace handler

} // namespace vge
