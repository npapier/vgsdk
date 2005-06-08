// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/DrawStyle.hpp"

#include <vgd/node/DrawStyle.hpp>
#include <vge/service/Painter.hpp>

#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( DrawStyle );



const vge::handler::Handler::TargetVector DrawStyle::getTargets() const
{
	TargetVector targets;
	
	targets.reserve( 1 );
	targets.push_back( vgd::node::DrawStyle::getClassIndexStatic() );

	return ( targets );
}



void DrawStyle::apply ( vge::engine::Engine* , vgd::node::Node * )
{
}



void DrawStyle::unapply ( vge::engine::Engine* , vgd::node::Node* )
{
}



void DrawStyle::setToDefaults()
{
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
