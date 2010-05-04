// VGSDK - Copyright (C) 2004, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/basic/MatrixTransform.hpp"

#include <vgd/node/MatrixTransform.hpp>

#include "vge/handler/MatrixTransform.hpp"
#include "vge/engine/Engine.hpp"
#include "vge/service/ComputeBoundingBox.hpp"



namespace vge
{

namespace handler
{

namespace basic
{



META_HANDLER_CPP( MatrixTransform );



const Handler::TargetVector MatrixTransform::getTargets()	const
{
	TargetVector targets;

	targets.push_back( vgd::node::MatrixTransform::getClassIndexStatic() );

	return targets;
}



void MatrixTransform::apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgd::node::MatrixTransform* >(pNode) != 0 );
	vgd::node::MatrixTransform *pCastedNode = dynamic_cast< vgd::node::MatrixTransform* >(pNode);

	vge::handler::MatrixTransform::apply( pEngine, pCastedNode );
}



void MatrixTransform::unapply( vge::engine::Engine *, vgd::node::Node * )
{
	// nothing to do
}



void MatrixTransform::setToDefaults()
{
}



} // namespace basic

} // namespace handler

} // namespace vge