// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/cbb/MatrixTransform.hpp"

#include <vgd/node/MatrixTransform.hpp>

#include "vge/handler/MatrixTransform.hpp"
#include "vge/engine/Engine.hpp"
#include "vge/service/ComputeBoundingBox.hpp"



namespace vge
{

namespace handler
{

namespace cbb
{



META_HANDLER_CPP( MatrixTransform );



const Handler::TargetVector MatrixTransform::getTargets()	const
{
	TargetVector targets;
	
	targets.push_back( vgd::node::MatrixTransform::getClassIndexStatic() );
	
	return ( targets );
}



void MatrixTransform::apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgd::node::MatrixTransform* >(pNode) != 0 );
	vgd::node::MatrixTransform *pCastedNode = static_cast< vgd::node::MatrixTransform* >(pNode);
	
	vge::handler::MatrixTransform::apply( pEngine, pCastedNode );	
}



void MatrixTransform::unapply( vge::engine::Engine *, vgd::node::Node * )
{
	// nothing to do
}



void MatrixTransform::setToDefaults()
{
}



} // namespace cbb
	
} // namespace handler

} // namespace vge
