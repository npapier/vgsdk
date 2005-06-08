// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Depth.hpp"

#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/Depth.hpp>
#include <vge/rc/Manager.hpp>
#include <vge/service/Painter.hpp>

#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/rc/TDisplayListHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{

META_HANDLER_CPP( Depth );



const vge::handler::Handler::TargetVector Depth::getTargets() const
{
	TargetVector targets;
	
	targets.reserve( 1 );
	targets.push_back( vgd::node::Depth::getClassIndexStatic() );

	return ( targets );
}



void Depth::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
	vgeGL::rc::applyUsingDisplayList< vgd::node::Depth, Depth >( pEngine, pNode, this );
}



void Depth::unapply ( vge::engine::Engine*, vgd::node::Node* )
{
}



void Depth::setToDefaults()
{
	glDepthFunc( GL_LESS );
	
	glDepthMask( GL_TRUE );
}



void Depth::paint( vgeGL::engine::Engine *, vgd::node::Depth *pNode )
{
	bool	bDefined;

	// FUNCTION
	vgd::node::Depth::FunctionValueType function;
	bDefined = pNode->getFunction( function );

	if ( bDefined )
	{
		glDepthFunc( m_functionParameter[function] );
	}
	
	// MASK
	vgd::node::Depth::MaskValueType mask;
	bDefined = pNode->getMask( mask );
	
	if ( bDefined )
	{
		glDepthMask( mask == vgd::node::Depth::RW );
	}
}



GLenum Depth::m_functionParameter[] = {
		GL_NEVER,
		GL_LESS,
		GL_LEQUAL,
		GL_EQUAL,
		GL_GREATER,
		GL_NOTEQUAL,
		GL_GEQUAL,
		GL_ALWAYS
};



} // namespace painter

} // namespace handler

} // namespace vgeGL
