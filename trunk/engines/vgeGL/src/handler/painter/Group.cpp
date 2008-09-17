// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Group.hpp"

#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/MultiSwitch.hpp>
#include <vgd/node/Switch.hpp>
#include <vge/service/Painter.hpp>



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( Group );



const vge::service::List Group::getServices() const
{
	vge::service::List list;

	list.push_back( vgd::Shp<vge::service::Service>( new vge::service::Painter ) );

	return list;
}



const vge::handler::Handler::TargetVector Group::getTargets() const
{
	vge::handler::Handler::TargetVector targets;

	targets.reserve( 3 );
	targets.push_back( vgd::node::Group::getClassIndexStatic() );
	targets.push_back( vgd::node::MultiSwitch::getClassIndexStatic() );
	targets.push_back( vgd::node::Switch::getClassIndexStatic() );

	return targets;
}



void Group::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
	vge::handler::painter::Group::apply( engine, node );

	// Validates node ? no already done by vge::handler::painter::Group::apply( engine, node );
	// node->getDirtyFlag(node->getDFNode())->validate();
}



void Group::unapply( vge::engine::Engine *, vgd::node::Node * )
{
}



void Group::setToDefaults()
{
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
