// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/cbb/Layers.hpp"

#include "vge/engine/Engine.hpp"
#include <vgd/node/Layers.hpp>



namespace vge
{

namespace handler
{

namespace cbb
{



META_HANDLER_CPP( Layers );



const Handler::TargetVector Layers::getTargets() const
{
	TargetVector targets;

	targets.push_back( vgd::node::Layers::getClassIndexStatic() );	
	
	return ( targets );
}



void Layers::apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgd::node::Layers* >(pNode) != 0 );
	vgd::node::Layers *pLayers = static_cast< vgd::node::Layers* >(pNode);
	
	// compute bounding.
	vgm::MatrixR&	current( pEngine->getGeometricalMatrix().getTop() );
	pLayers->computeBoundingBox( current );
}



void Layers::unapply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	// nothing to do
}



void Layers::setToDefaults()
{
}



} // namespace cbb
	
} // namespace handler

} // namespace vge
