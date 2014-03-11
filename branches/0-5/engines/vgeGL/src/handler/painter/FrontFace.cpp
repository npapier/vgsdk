// VGSDK - Copyright (C) 2004, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/FrontFace.hpp"

#include <vgd/node/FrontFace.hpp>
#include "vgeGL/rc/TDisplayListHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( FrontFace );



const vge::handler::Handler::TargetVector FrontFace::getTargets() const
{
	TargetVector targets;

	targets.reserve( 1 );
	targets.push_back( vgd::node::FrontFace::getClassIndexStatic() );

	return targets;
}



void FrontFace::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
//	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
//	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

//	assert( dynamic_cast< vgd::node::FrontFace* >(pNode) != 0 );
//	vgd::node::FrontFace *pCastedNode = static_cast< vgd::node::FrontFace* >(pNode);

	vgeGL::rc::applyUsingDisplayList< vgd::node::FrontFace, FrontFace >( pEngine, pNode, this );
}



void FrontFace::unapply ( vge::engine::Engine*, vgd::node::Node* )
{
}



void FrontFace::setToDefaults()
{
}



void FrontFace::paint( vgeGL::engine::Engine *, vgd::node::FrontFace * node )
{
	// ORIENTATION
	vgd::node::FrontFace::OrientationValueType value = node->getOrientation();

	glFrontFace( (value == vgd::node::FrontFace::CCW) ? GL_CCW : GL_CW );

	// Validates node df
	node->getDirtyFlag(node->getDFNode())->validate();
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
