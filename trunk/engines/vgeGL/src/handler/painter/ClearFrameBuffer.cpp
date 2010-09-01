// VGSDK - Copyright (C) 2004, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/ClearFrameBuffer.hpp"

#include <glo/FrameBufferObject.hpp>
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



void ClearFrameBuffer::apply( vge::engine::Engine *engine, vgd::node::Node *node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);

	// Updates engine state
	vgd::Shp< glo::FrameBufferObject > fbo = glEngine->getOutputBuffers();

	if (	glEngine->isGLSLEnabled() &&
			fbo && fbo->isBound() )
	{
		// glsl and engine contains active output buffers, then clears all output buffers

		// Backups current draw buffers
		const std::vector< int > drawBuffersBackup = fbo->getFullDrawBuffers();

		// Clears all draw buffers attached to fbo
		fbo->setDrawBuffersToAll();
		vgeGL::rc::applyUsingDisplayList<vgd::node::ClearFrameBuffer, ClearFrameBuffer>( engine, node, this );

		// Restores the draw buffers
		fbo->setDrawBuffers( drawBuffersBackup );
	}
	else
	{
		vgeGL::rc::applyUsingDisplayList<vgd::node::ClearFrameBuffer, ClearFrameBuffer>( engine, node, this );
	}
}



void ClearFrameBuffer::unapply ( vge::engine::Engine*, vgd::node::Node* )
{}



void ClearFrameBuffer::setToDefaults()
{
	glClearColor( 0.f, 0.f, 0.f, 0.f );
	glClearAccum( 0.f, 0.f, 0.f, 0.f );
	glClearDepth( 1.0f );
}



void ClearFrameBuffer::paint ( vgeGL::engine::Engine *, vgd::node::ClearFrameBuffer *pFrameBuffer )
{
	// CLEAR COLOR
	vgm::Vec4f	clearValue;
	bool		defined;
	
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
		clearMaskGL |= GL_COLOR_BUFFER_BIT;
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

	if ( clearMask != 0 )
	{
		glClear( clearMaskGL );
	}

	// Validates node
	pFrameBuffer->getDirtyFlag(pFrameBuffer->getDFNode())->validate();
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
