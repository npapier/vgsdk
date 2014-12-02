// VGSDK - Copyright (C) 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/OutputBuffers.hpp"

#include <boost/tuple/tuple.hpp>
#include <glo/FrameBufferObject.hpp>
#include <vgd/node/OutputBuffers.hpp>

#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( OutputBuffers );



const vge::handler::Handler::TargetVector OutputBuffers::getTargets() const
{
	TargetVector targets;

	targets.reserve( 1 );
	targets.push_back( vgd::node::OutputBuffers::getClassIndexStatic() );

	return targets;
}



void OutputBuffers::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);

	assert( dynamic_cast< vgd::node::OutputBuffers* >(node) != 0 );
	vgd::node::OutputBuffers *outputBuffers = static_cast< vgd::node::OutputBuffers* >(node);

	// Updates engine state
	const vge::engine::BufferUsagePolicy	bup = glEngine->getBufferUsagePolicy();
	vgd::Shp< glo::FrameBufferObject >		fbo = glEngine->getOutputBuffers();

	if ( fbo )
	{
		switch ( bup )
		{
			case vge::engine::BUP_NOT_DEFINED:
				vgAssertN( false, "BUP_NOT_DEFINED not expected" );
				break;

			case vge::engine::BUP_ONLY_DEPTH:
				break;

			case vge::engine::BUP_ONLY_COLOR:
			case vge::engine::BUP_COLOR_AND_DEPTH:
			case vge::engine::BUP_ONLY_COLOR_NO_CLEAR:
			{
				// glsl and engine contains active output buffers, then select output buffers

				// By default, all drawing operations into color buffers are disabled
				std::vector< int > drawBuffers( fbo->getMaxColorAttachements(), -1 );

				// Fills the drawBuffers mapping from output buffers node
				using vgd::field::EditorRO;
				typedef vgd::node::OutputBuffers::FCurrentType FCurrentType;

				EditorRO< FCurrentType > current = outputBuffers->getCurrentRO();

				for( uint i=0; i < current->size(); ++i )
				{
					const int outputBufferIndex = (*current)[i];
					drawBuffers[outputBufferIndex] = outputBufferIndex;
				}

				// Updates the current draw buffers using private draw buffers
				glEngine->updateFromCurrentPrivateDrawBuffers( drawBuffers );

				// Modifies the draw buffers
				fbo->setDrawBuffers( drawBuffers );
			}
			break;

			default:
				vgAssertN( false, "Unexpected value for buffer rendering policy %i", bup );
		}
	}
	else
	{
		switch ( bup )
		{
			case vge::engine::BUP_NOT_DEFINED:
				vgAssertN( false, "BUP_NOT_DEFINED not expected" );
				break;

			case vge::engine::BUP_ONLY_DEPTH:
				break;

			case vge::engine::BUP_ONLY_COLOR:
			case vge::engine::BUP_COLOR_AND_DEPTH:
				glo::FrameBufferObject::setDrawToDefaultFrameBuffer();
				break;

			default:
				vgAssertN( false, "Unexpected value for buffer rendering policy %i", bup );
		}
	}

// @todo cache mechanism
	//vgeGL::rc::applyUsingDisplayList< vgd::node::OutputBuffers, OutputBuffers >( engine, node, this );

	// Validates node df
	node->getDirtyFlag(node->getDFNode())->validate();
}



void OutputBuffers::unapply ( vge::engine::Engine*, vgd::node::Node* )
{
}



void OutputBuffers::setToDefaults()
{
}



/*void OutputBuffers::paint( vgeGL::engine::Engine *, vgd::node::OutputBuffers * node )
{
}*/



} // namespace painter

} // namespace handler

} // namespace vgeGL
