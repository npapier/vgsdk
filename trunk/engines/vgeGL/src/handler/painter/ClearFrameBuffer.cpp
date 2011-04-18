// VGSDK - Copyright (C) 2004, 2010, 2011, Nicolas Papier.
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

	return targets;
}



void ClearFrameBuffer::apply( vge::engine::Engine *engine, vgd::node::Node *node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);

	// Updates engine state
	const vge::engine::BufferUsagePolicy	bup = engine->getBufferUsagePolicy();
	vgd::Shp< glo::FrameBufferObject >		fbo = glEngine->getOutputBuffers();

	if ( fbo )
	{
		fbo->bind();
	}

	applyBufferUsagePolicy( bup, fbo );

	vgeGL::rc::applyUsingDisplayList<vgd::node::ClearFrameBuffer, ClearFrameBuffer>( engine, node, this );
}



void ClearFrameBuffer::unapply( vge::engine::Engine*, vgd::node::Node* )
{}



void ClearFrameBuffer::setToDefaults()
{
	glClearColor( 0.f, 0.f, 0.f, 0.f );
	glClearAccum( 0.f, 0.f, 0.f, 0.f );
	glClearDepth( 1.0f );

	glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
	glDrawBuffer( GL_BACK );

	glDepthMask( GL_TRUE );
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );
}



void ClearFrameBuffer::paint( vgeGL::engine::Engine * engine, vgd::node::ClearFrameBuffer * framebuffer )
{
	// CLEAR COLOR
	vgm::Vec4f	clearValue;
	bool		defined;
	
	//
	defined = framebuffer->getClear( vgd::node::ClearFrameBuffer::COLOR, clearValue );
	
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
	defined = framebuffer->getClear( vgd::node::ClearFrameBuffer::ACCUM, clearValue );
	
	if ( defined )
	{
		glClearAccum( 
			clearValue[0],
			clearValue[1],
			clearValue[2],
			clearValue[3]
			);
	}

/* @todo Generates ClearFrameBuffer node and remove clearMask
	// CLEAR MASK
	const int32 clearMask = framebuffer->getClearMask();
	
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
*/
	// Validates node
	framebuffer->getDirtyFlag(framebuffer->getDFNode())->validate();
}



// @todo cache in DL
void ClearFrameBuffer::applyBufferUsagePolicy( const vge::engine::BufferUsagePolicy policy, vgd::Shp< glo::FrameBufferObject > fbo )
{
	switch ( policy )
	{
		case vge::engine::BUP_NOT_DEFINED:
			vgAssertN( false, "BUP_NOT_DEFINED not expected" );
			return;

		case vge::engine::BUP_ONLY_DEPTH:
			if ( fbo )
			{
				// 1) disable writing to color buffer
				fbo->renderDepthOnly();

				// 2) enable writing to depth buffer
				glDepthMask( GL_TRUE );
			}
			else
			{
				// 1) disable writing to color buffer
				glDrawBuffer( GL_NONE );

				// 2) enable writing to depth buffer
				glDepthMask( GL_TRUE );
			}

			// set depth function
			glDepthFunc( GL_LEQUAL );
			glEnable( GL_DEPTH_TEST );

			// Clears buffer
			glClear( GL_DEPTH_BUFFER_BIT );
			break;

		case vge::engine::BUP_ONLY_COLOR:
			if ( fbo )
			{
				// 1) enable writing to color buffer already done by OutputBuffers node

				// 2) disable writing to depth buffer
				glDepthMask( GL_FALSE );

				// 3) clear buffers
				// Backups current draw buffers
				//std::vector< int > drawBuffersBackup = fbo->getFullDrawBuffers();

				// Clears all draw buffers
				fbo->setDrawBuffersToAll();
				glClear( GL_COLOR_BUFFER_BIT );

				// Restores the draw buffers
				//fbo->setDrawBuffers( drawBuffersBackup );

				fbo->setDrawBuffer(0);
			}
			else
			{
				// 1) enable writing to color buffer
				glDrawBuffer( GL_BACK );

				// 2) disable writing to depth buffer
				glDepthMask( GL_FALSE );

				// 3) clear buffer
				glClear( GL_COLOR_BUFFER_BIT );
			}

			// set depth function
			glDepthFunc( GL_EQUAL );
			glEnable( GL_DEPTH_TEST );
			break;

		case vge::engine::BUP_COLOR_AND_DEPTH:
			if ( fbo )
			{
				// 1) enable writing to color buffer already done by OutputBuffers node

				// 2) enable writing to depth buffer
				glDepthMask( GL_TRUE );

				// 3) clear buffers
				// Backups current draw buffers
				//std::vector< int > drawBuffersBackup = fbo->getFullDrawBuffers();

				// Clears all draw buffers
				fbo->setDrawBuffersToAll();
				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

				// Restores the draw buffers
				//fbo->setDrawBuffers( drawBuffersBackup );

				fbo->setDrawBuffer(0);
			}
			else
			{
				// 1) enable writing to color buffer
				glDrawBuffer( GL_BACK );

				// 2) enable writing to depth buffer
				glDepthMask( GL_TRUE );

				// 3) clear buffers
				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			}

			// set depth function
			glDepthFunc( GL_LEQUAL );
			glEnable( GL_DEPTH_TEST );
			break;

		case vge::engine::BUP_ONLY_COLOR_NO_CLEAR:
			if ( fbo )
			{
				// 1) enable writing to color buffer already done by OutputBuffers node

				// 2) disable writing to depth buffer
				glDepthMask( GL_FALSE );

				fbo->setDrawBuffer(0);
			}
			else
			{
				// 1) enable writing to color buffer
				glDrawBuffer( GL_BACK );

				// 2) enable writing to depth buffer
				glDepthMask( GL_FALSE );
			}

			// set depth function
			glDepthFunc( GL_LEQUAL );
			glEnable( GL_DEPTH_TEST );
			break;

		default:
			vgAssertN( false, "Unexpected value for buffer rendering policy %i", policy );
	}
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
