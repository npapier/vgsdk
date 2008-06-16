// VGSDK - Copyright (C) 2008, Guillaume Brocker
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgeGL/handler/cbb/Callback.hpp"

#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/Callback.hpp>
#include <vge/rc/Manager.hpp>
#include <vge/service/Painter.hpp>

#include "vgeGL/engine/Engine.hpp"


namespace vgeGL
{

namespace handler
{

namespace cbb
{


META_HANDLER_CPP( Callback );



const vge::handler::Handler::TargetVector Callback::getTargets() const
{
	TargetVector targets;
	
	targets.reserve( 1 );
	targets.push_back( vgd::node::Callback::getClassIndexStatic() );

	return ( targets );
}



void Callback::apply ( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgd::node::Callback* >(pNode) != 0 );
	vgd::node::Callback *pCastedNode = static_cast< vgd::node::Callback* >(pNode);
	
	vgm::MatrixR&   current( pEngine->getGeometricalMatrix().getTop() );

	pCastedNode->computeBoundingBox( current );
}



void Callback::unapply ( vge::engine::Engine*, vgd::node::Node* )
{
	// Nothing to do.
}



void Callback::setToDefaults()
{
	// Nothing to do.
}



} // namespace cbb

} // namespace handler

} // namespace vgeGL
