// VGSDK - Copyright (C) 2004, 2010, 2011, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/ClearFrameBuffer.hpp"

#include <glo/FrameBufferObject.hpp>
#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgd/node/OutputBufferProperty.hpp>

#include "vgeGL/rc/TDisplayListHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



// @todo move in helpers.hpp
void updateCurrentDrawBuffers(	const vgeGL::engine::Engine::OutputBufferPropertyStateContainer& outputBuffersProperties,
								std::vector< int >& currentDrawBuffers )
{
	uint		count	= 0;

	uint		i		= 0;
	const uint	iEnd	= outputBuffersProperties.getMax();

	while( i != iEnd )
	{
		using vgeGL::engine::GLSLState;
		typedef GLSLState::OutputBufferPropertyState OutputBufferPropertyState;

		const vgd::Shp< OutputBufferPropertyState > state = outputBuffersProperties.getState(i);

		if ( state )
		{
			++count;

			vgd::node::OutputBufferProperty * node = state->getNode();
			vgAssert( node );

			if ( node->getCurrent() )
			{
				// This output buffer is current, i.e. used for drawing by default.
				vgAssert( (node->getMultiAttributeIndex() == i) || (node->getMultiAttributeIndex() == -1) );
				currentDrawBuffers[i] = i;
			}
			else
			{
				// This output buffer is not current
				vgAssert( currentDrawBuffers[i] == -1 );
			}
		}
		else
		{
			// no output buffer property
			vgAssert( currentDrawBuffers[i] == -1 );
		}

		//
		if ( count == outputBuffersProperties.getNum() )
		{
			break;
		}
		++i;
	}
}



META_HANDLER_CPP( ClearFrameBuffer );



const vge::handler::Handler::TargetVector ClearFrameBuffer::getTargets() const
{
	vge::handler::Handler::TargetVector	targets;

	targets.push_back( vgd::node::ClearFrameBuffer::getClassIndexStatic() );

	return targets;
}



// @todo move into vge::handler::ClearFrameBuffer
void ClearFrameBuffer::apply( vge::engine::Engine *engine, vgd::node::Node *node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);

	// Updates engine state

	const vgm::MatrixR& current( engine->getGeometricalMatrix().getTop() );
	glEngine->setSceneGeometricalMatrix( current );

	//
	const vge::engine::BufferUsagePolicy	bup = engine->getBufferUsagePolicy();
	const vge::engine::EyeUsagePolicy		eup = engine->getEyeUsagePolicy();
	vgeGL::rc::applyUsingDisplayList<vgd::node::ClearFrameBuffer, ClearFrameBuffer>( engine, node, this );

	applyBufferUsagePolicy( glEngine, bup, eup );
}



void ClearFrameBuffer::unapply( vge::engine::Engine*, vgd::node::Node* )
{}



void ClearFrameBuffer::setToDefaults()
{
	glClearColor( 0.f, 0.f, 0.f, 0.f );
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

	defined = framebuffer->getClearColor( clearValue );

	if ( defined )
	{
		glClearColor(
			clearValue[0],
			clearValue[1],
			clearValue[2],
			clearValue[3]
			);
	}

	// Validates node
	framebuffer->getDirtyFlag(framebuffer->getDFNode())->validate();
}



// @todo cache in DL
void ClearFrameBuffer::applyBufferUsagePolicy( vgeGL::engine::Engine * engine, const vge::engine::BufferUsagePolicy bufferPolicy, const vge::engine::EyeUsagePolicy eyePolicy )
{
	// Binds engine output buffers
	vgd::Shp< glo::FrameBufferObject > fbo = engine->getOutputBuffers();
	if ( fbo )
	{
		fbo->bind();
	}

	typedef vgeGL::engine::Engine::OutputBufferPropertyStateContainer OutputBufferPropertyStateContainer; // <=> vge::basic::TUnitContainer< OutputBufferPropertyState >
	const OutputBufferPropertyStateContainer& outputBuffersProperties = engine->getOutputBufferProperties();

	// By default, all drawing operations into color buffers are disabled
	std::vector< int > currentDrawBuffers( fbo ? fbo->getMaxColorAttachements() : 0, -1 );

	if ( fbo )
	{
		// Computes the current draw buffers (from OutputBufferProperty nodes).
		updateCurrentDrawBuffers( outputBuffersProperties, currentDrawBuffers );

		// Updates the current draw buffers using private draw buffers
		engine->updateFromCurrentPrivateDrawBuffers( currentDrawBuffers );
	}

	// Computes which draw buffer to use from eye policy
	GLenum drawBufferFromEyePolicy = GL_NONE;

	switch ( eyePolicy )
	{
		case vgd::node::Camera::EYE_LEFT:
			drawBufferFromEyePolicy = GL_BACK_LEFT;
			break;

		case vgd::node::Camera::EYE_RIGHT:
			drawBufferFromEyePolicy = GL_BACK_RIGHT;
			break;

		case vgd::node::Camera::EYE_BOTH:
			drawBufferFromEyePolicy = GL_BACK;
			break;

		//case EYE_DEFAULT:
		default:
			vgAssertN( false, "Unexpected value for eye usage policy %i", eyePolicy );
	}


	// Apply buffer policy and eye policy
	switch ( bufferPolicy )
	{
		case vge::engine::BUP_NOT_DEFINED:
			vgAssertN( false, "BUP_NOT_DEFINED not expected" );
			return;

		case vge::engine::BUP_ONLY_DEPTH:
			if ( fbo )
			{
				// 1) disable writing to color buffer
				fbo->renderDepthOnly();
			}
			else
			{
				// 1) disable writing to color buffer
				glDrawBuffer( GL_NONE );

			}

			// 2) enable writing to depth buffer
			glDepthMask( GL_TRUE );

			// set depth function
			glDepthFunc( GL_LEQUAL );
			glEnable( GL_DEPTH_TEST );

			// Clears buffer
			glClear( GL_DEPTH_BUFFER_BIT );
			break;

		case vge::engine::BUP_ONLY_COLOR:
			if ( fbo )
			{
				// 1) enable writing to current draw buffer(s).
				fbo->setDrawBuffers( currentDrawBuffers );

				// 2) disable writing to depth buffer
				glDepthMask( GL_FALSE );

				// 3) clear buffers
				glClear( GL_COLOR_BUFFER_BIT );
			}
			else
			{
				// 1) enable writing to color buffer
				glDrawBuffer( drawBufferFromEyePolicy );

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
				// 1) enable writing to current draw buffer(s).
				fbo->setDrawBuffers( currentDrawBuffers );

				// 2) enable writing to depth buffer
				glDepthMask( GL_TRUE );

				// 3) clear buffers
				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			}
			else
			{
				// 1) enable writing to color buffer
				glDrawBuffer( drawBufferFromEyePolicy );

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
				// 1) enable writing to current draw buffer(s).
				fbo->setDrawBuffers( currentDrawBuffers );

				// 2) disable writing to depth buffer
				glDepthMask( GL_FALSE );
			}
			else
			{
				// 1) enable writing to color buffer
				glDrawBuffer( drawBufferFromEyePolicy );

				// 2) enable writing to depth buffer
				glDepthMask( GL_FALSE );
			}

			// set depth function
			glDepthFunc( GL_LEQUAL );
			glEnable( GL_DEPTH_TEST );
			break;

		default:
			vgAssertN( false, "Unexpected value for buffer rendering policy %i", bufferPolicy );
	}
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
