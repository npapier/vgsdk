// VGSDK - Copyright (C) 2004, 2006, 2008, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/SpotLight.hpp"

#include <vgd/node/SpotLight.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/GLSLState.hpp"
#include "vgeGL/rc/TDisplayListHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( SpotLight );



const vge::handler::Handler::TargetVector SpotLight::getTargets() const
{
	vge::handler::Handler::TargetVector targets;

	targets.push_back( vgd::node::SpotLight::getClassIndexStatic() );

	return targets;
}



void SpotLight::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);

	assert( dynamic_cast< vgd::node::SpotLight* >(node) != 0 );
	vgd::node::SpotLight *spotLight = static_cast< vgd::node::SpotLight* >(node);

	//
	updateGLSLState( glEngine, spotLight, glEngine->getGLSLState() );

	//
	vgeGL::rc::applyUsingDisplayList<vgd::node::SpotLight, SpotLight>( engine, node, this );
}



void SpotLight::unapply ( vge::engine::Engine*, vgd::node::Node* )
{}



void SpotLight::setToDefaults()
{
}



void SpotLight::updateGLSLState( vgeGL::engine::Engine * engine, vgd::node::SpotLight * spotLight, vgeGL::engine::GLSLState& glslState )
{
	using vgeGL::engine::GLSLState;
	typedef vgeGL::engine::LightState LightState;

	// Updates GLSL state
	glslState.setEnabled( vgeGL::engine::SPOT_LIGHT );

	if ( !glslState.isEnabled( vgeGL::engine::SPOT_LIGHT_CASTING_SHADOW ) )
	{
		const bool castShadow = spotLight->getCastShadow();
		if ( castShadow )	glslState.setEnabled( vgeGL::engine::SPOT_LIGHT_CASTING_SHADOW );
	}

	// Light state
	const uint unit = spotLight->getMultiAttributeIndex();

	vgd::Shp< LightState > lightState = glslState.lights.getState( unit );

	if ( !lightState )
	{
		// Creates a new unit state
		// type
		lightState.reset( new LightState(vgeGL::engine::SPOT_LIGHT) );
		glslState.lights.setState( unit, lightState );
	}
	else
	{
		// type
		lightState->setLightType( vgeGL::engine::SPOT_LIGHT );
		glslState.lights.dirty();
	}

	updateUnitState( engine, spotLight, lightState );
}


void SpotLight::updateUnitState( vgeGL::engine::Engine * engine, vgd::node::SpotLight * spotLight, vgd::Shp< vgeGL::engine::LightState > lightState )
{
	PointLight::updateUnitState( engine, spotLight, lightState );

	// Updates unit state
	// lightModelViewMatrix
	lightState->setModelViewMatrix( engine->getGeometricalMatrix().getTop() );

	// CUTOFFANGLE
	vgd::node::SpotLight::CutOffAngleValueType cutOffAngle;
	bool bDefined = spotLight->getCutOffAngle( cutOffAngle );
	if ( bDefined )		lightState->setCutOffAngle( cutOffAngle );

	// DIRECTION field
	vgd::node::SpotLight::DirectionValueType direction;
	bDefined = spotLight->getDirection( direction );
	if ( bDefined )		lightState->setDirection( direction );
}



void SpotLight::paint( vgeGL::engine::Engine *pGLEngine, vgd::node::SpotLight *pSpotLight )
{
	// Handles PointLight and Light fields
	PointLight::paint( pGLEngine, pSpotLight );

	// Computes the light index
	const GLenum lightIndex = GL_LIGHT0 + pSpotLight->getMultiAttributeIndex();

	// Handles SpotLight fields
	using vgd::node::SpotLight;
	bool			bDefined;

	// DIRECTION field
	SpotLight::DirectionValueType direction;

	bDefined = pSpotLight->getDirection( direction );

	if ( bDefined )
	{
		glLightfv( lightIndex, GL_SPOT_DIRECTION, direction.getValue() );
	}

	// CUTOFFANGLE field
	SpotLight::CutOffAngleValueType cutOffAngle;

	bDefined = pSpotLight->getCutOffAngle( cutOffAngle );
	
	if ( bDefined )
	{
		vgAssertN(	((cutOffAngle >= 0.f) && (cutOffAngle <= 90.f )) ||
					(cutOffAngle == 180.f), "Unexpected value for cutOffAngle %f", cutOffAngle);

		glLightfv( lightIndex, GL_SPOT_CUTOFF, &cutOffAngle );
	}

	// DROPOFFRATE field
	SpotLight::DropOffRateValueType dropOffRate;

	bDefined = pSpotLight->getDropOffRate( dropOffRate );

	if ( bDefined )
	{
		vgAssertN(	(dropOffRate >= 0.f) && (dropOffRate <= 1.f), "Unexpected value for dropOffRate %f", dropOffRate );

		SpotLight::DropOffRateValueType dropOffRateGL = dropOffRate * 128.f;

		glLightfv( lightIndex, GL_SPOT_EXPONENT, &dropOffRateGL );
	}

	// Validates node
	pSpotLight->getDirtyFlag(pSpotLight->getDFNode())->validate();
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
