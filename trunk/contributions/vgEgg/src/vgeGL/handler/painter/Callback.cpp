// VGSDK - Copyright (C) 2006, Clement Forest.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Callback.hpp"

#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/Callback.hpp>
#include <vge/rc/Manager.hpp>
#include <vge/service/Painter.hpp>

#include "vgeGL/engine/Engine.hpp"


namespace vgeGL
{

namespace handler
{

namespace painter
{

META_HANDLER_CPP( Callback );



const vge::handler::Handler::TargetVector Callback::getTargets() const
{
	TargetVector targets;
	
	targets.reserve( 1 );
	targets.push_back( vgd::node::Callback::getClassIndexStatic() );

	return ( targets );
}



void Callback::apply ( vge::engine::Engine*, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgd::node::Callback* >(pNode) != 0 );
	vgd::node::Callback *pCastedNode = static_cast< vgd::node::Callback* >(pNode);

	bool	bDefined;

	// FUNCTION
	vgd::node::Callback::CallbackType callback;
	bDefined = pCastedNode->getCallback( callback );

	if ( bDefined )
	{
		callback(pCastedNode);
	}
}



void Callback::unapply ( vge::engine::Engine*, vgd::node::Node* )
{
}



void Callback::setToDefaults()
{
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
