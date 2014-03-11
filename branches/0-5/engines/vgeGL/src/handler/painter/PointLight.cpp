// VGSDK - Copyright (C) 2004, 2008, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/PointLight.hpp"

#include <vgd/node/PointLight.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/GLSLState.hpp"
#include "vgeGL/rc/TDisplayListHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( PointLight );



const vge::handler::Handler::TargetVector PointLight::getTargets() const
{
	vge::handler::Handler::TargetVector targets;

	targets.push_back( vgd::node::PointLight::getClassIndexStatic() );

	return targets;
}



void PointLight::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);

	assert( dynamic_cast< vgd::node::PointLight* >(node) != 0 );
	vgd::node::PointLight *pointLight = static_cast< vgd::node::PointLight* >(node);

	//
	updateGLSLState( glEngine, pointLight, glEngine->getGLSLState() );

	//
	vgeGL::rc::applyUsingDisplayList<vgd::node::PointLight, PointLight>( engine, node, this );
}



void PointLight::unapply ( vge::engine::Engine* , vgd::node::Node* )
{
}



void PointLight::setToDefaults()
{
}



void PointLight::updateGLSLState( vgeGL::engine::Engine * engine, vgd::node::PointLight * light, vgeGL::engine::GLSLState& glslState )
{
	using vgeGL::engine::GLSLState;
	typedef vgeGL::engine::LightState LightState;

	// Updates GLSL state
	glslState.setEnabled( vgeGL::engine::POINT_LIGHT );

/* @todo
	if ( !glslState.isEnabled( vgeGL::engine::POINT_LIGHT_CASTING_SHADOW ) )
	{
		const bool castShadow = light->getCastShadow();
		if ( castShadow )	glslState.setEnabled( vgeGL::engine::POINT_LIGHT_CASTING_SHADOW );
	}
*/

	// Light state
	const uint unit = light->getMultiAttributeIndex();

	vgd::Shp< LightState > lightState = glslState.lights.getState( unit );

	if ( !lightState )
	{
		// Creates a new unit state
		// type
		lightState.reset( new LightState(vgeGL::engine::POINT_LIGHT) );
		glslState.lights.setState( unit, lightState );
	}
	else
	{
		// type
		lightState->setLightType( vgeGL::engine::POINT_LIGHT );
		glslState.lights.dirty();
	}

	updateUnitState( engine, light, lightState );
}



void PointLight::updateUnitState( vgeGL::engine::Engine * engine, vgd::node::PointLight * light, vgd::Shp< vgeGL::engine::LightState > lightState )
{
	Light::updateUnitState( engine, light, lightState );

	// POSITION
	vgd::node::PointLight::PositionValueType position;
	const bool bDefined = light->getPosition( position );
	if ( bDefined )		lightState->setPosition( position );
}


void PointLight::paint( vgeGL::engine::Engine *pGLEngine, vgd::node::PointLight *pPointLight )
{
	// render Light fields.
	Light::paint( pGLEngine, pPointLight );

	// render PointLight fields.
	GLenum		lightIndex;
	bool		bDefined;
	vgm::Vec3f	position;

	lightIndex	= GL_LIGHT0 + pPointLight->getMultiAttributeIndex();

	bDefined	= pPointLight->getPosition( position );

	if ( bDefined )
	{
		// use position field
		vgm::Vec4f positionGL(
				position[0], position[1], position[2],		// position of light
				1.f 										// not a directional light
				);

		glLightfv( lightIndex, GL_POSITION, positionGL.getValue() );
	}

	// Validates node
	pPointLight->getDirtyFlag(pPointLight->getDFNode())->validate();
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
