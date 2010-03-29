// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/PointStyle.hpp"

#include <vgd/node/PointStyle.hpp>
#include <vgDebug/convenience.hpp>
#include "vgeGL/rc/TDisplayListHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( PointStyle );



const vge::handler::Handler::TargetVector PointStyle::getTargets() const
{
	TargetVector targets;

	targets.reserve( 1 );
	targets.push_back( vgd::node::PointStyle::getClassIndexStatic() );

	return targets;
}



void PointStyle::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine * glEngine = static_cast< vgeGL::engine::Engine* >(engine);

	assert( dynamic_cast< vgd::node::PointStyle* >(node) != 0 );
	vgd::node::PointStyle *pCastedNode = static_cast< vgd::node::PointStyle* >(node);

	if ( glEngine->isGLSLEnabled() )
	{
		// Retrieves GLSL state
		using vgeGL::engine::GLSLState;
		GLSLState& state = glEngine->getGLSLState();

		// Updates GLSLState
		state.setEnabled( GLSLState::POINT_STYLE, true );

		//
		glEnable( GL_VERTEX_PROGRAM_POINT_SIZE );
	}

	//paint( glEngine, pCastedNode );
	vgeGL::rc::applyUsingDisplayList< vgd::node::PointStyle, PointStyle >( engine, node, this );
}



void PointStyle::unapply ( vge::engine::Engine*, vgd::node::Node* )
{
}



void PointStyle::setToDefaults()
{
	glPointSize( 1.f );

	GLfloat coef[3] = { 1.f, 0.f, 0.f };
	glPointParameterfv( GL_POINT_DISTANCE_ATTENUATION, coef );

	glDisable( GL_POINT_SMOOTH );
}



void PointStyle::paint( vgeGL::engine::Engine *, vgd::node::PointStyle * node )
{
	// SIZE
	if ( node->hasSize() )
	{
		vgd::node::PointStyle::SizeValueType size;
		node->getSize( size );

		glPointSize( size );
	}

	// DISTANCEATTENUATION
	if ( node->hasDistanceAttenuation() )
	{
		vgd::node::PointStyle::DistanceAttenuationValueType distanceAttenuation;
		node->getDistanceAttenuation( distanceAttenuation );

		GLfloat coef[3] = { distanceAttenuation[0], distanceAttenuation[1], distanceAttenuation[2] };

		glPointParameterfv( GL_POINT_DISTANCE_ATTENUATION, coef ); //&distanceAttenuation[0] );

		//
		glPointParameterf( GL_POINT_SIZE_MIN, 1.f );
		glPointParameterf( GL_POINT_SIZE_MAX, 8192.f );

		//glPointParameterf( GL_POINT_FADE_THRESHOLD_SIZE, 3.0f );
	}

	// SMOOTH
	if ( node->hasSmooth() )
	{
		vgd::node::PointStyle::SmoothValueType smooth;
		node->getSmooth( smooth );

		if ( smooth )
		{
			glEnable( GL_POINT_SMOOTH );
		}
		else
		{
			glDisable( GL_POINT_SMOOTH );
		}
	}

	// Validates node df
	node->getDirtyFlag(node->getDFNode())->validate();
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
