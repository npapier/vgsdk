// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/ClearFrameBuffer.hpp"

#include <vgd/node/ClearFrameBuffer.hpp>

#include "vgeGL/rc/TDisplayListHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{
	


META_HANDLER_CPP( ClearFrameBuffer );



const vge::handler::Handler::TargetVector ClearFrameBuffer::getTargets() const
{
	vge::handler::Handler::TargetVector	targets;

	targets.push_back( vgd::node::ClearFrameBuffer::getClassIndexStatic() );

	return ( targets );
}



void ClearFrameBuffer::apply ( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	vgeGL::rc::applyUsingDisplayList<vgd::node::ClearFrameBuffer, ClearFrameBuffer>( pEngine, pNode, this );	
}



void ClearFrameBuffer::unapply ( vge::engine::Engine*, vgd::node::Node* )
{
}



void ClearFrameBuffer::setToDefaults()
{
	glClearColor( 0.f, 0.f, 0.f, 0.f );
	glClearAccum( 0.f, 0.f, 0.f, 0.f );
}



void ClearFrameBuffer::paint ( vgeGL::engine::Engine *, vgd::node::ClearFrameBuffer *pFrameBuffer )
{
	// CLEAR COLOR
	vgm::Vec4f	clearValue;
	bool			defined;
	
	//
	defined = pFrameBuffer->getClear( vgd::node::ClearFrameBuffer::COLOR, clearValue );
	
	if ( defined )
	{
		glClearColor( 
			clearValue[0],
			clearValue[1],
			clearValue[2],
			clearValue[3]
			);
	}

	//
	defined = pFrameBuffer->getClear( vgd::node::ClearFrameBuffer::ACCUM, clearValue );
	
	if ( defined )
	{
		glClearAccum( 
			clearValue[0],
			clearValue[1],
			clearValue[2],
			clearValue[3]
			);
	}	

	// CLEAR MASK
	int32 clearMask = pFrameBuffer->getClearMask();
	
	GLbitfield clearMaskGL = 0;
	
	if ( clearMask & vgd::node::ClearFrameBuffer::COLOR_BUFFER_BIT )
	{
		clearMaskGL|= GL_COLOR_BUFFER_BIT;
	}
	
	if ( clearMask & vgd::node::ClearFrameBuffer::DEPTH_BUFFER_BIT )
	{
		clearMaskGL |= GL_DEPTH_BUFFER_BIT;
	}
	
	if ( clearMask & vgd::node::ClearFrameBuffer:: ACCUM_BUFFER_BIT )
	{
		clearMaskGL |= GL_ACCUM_BUFFER_BIT;
	}
	
	if ( clearMask & vgd::node::ClearFrameBuffer::STENCIL_BUFFER_BIT )
	{
		clearMaskGL |= GL_STENCIL_BUFFER_BIT;
	}
	
	glClear( clearMaskGL );
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
