// VGSDK - Copyright (C) 2004, 2006, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/SpotLight.hpp"

#include <vgd/node/SpotLight.hpp>
#include "vgeGL/engine/Engine.hpp"
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

	using vgeGL::engine::GLSLState;
	typedef vgeGL::engine::GLSLState::LightState LightState;

	// *** Retrieves GLSL state ***
	GLSLState& state = glEngine->getGLSLState();

	vgd::Shp< LightState > lightState;
	/* lightState = state.getLight( node->getMultiAttributeIndex() );
	if ( lightState->getLightType() != GLSLState::SPOT_LIGHT )
	{
		lightState.reset();
	}*/

	// *** Computes light informations ***
	const vgm::MatrixR& current( glEngine->getGeometricalMatrix().getTop() );

	// fields
	bool isDefined;
	vgd::node::SpotLight::PositionValueType		position;
	vgd::node::SpotLight::DirectionValueType	direction;

	isDefined = spotLight->getPosition( position );
	assert( isDefined );
	/* @todo
	if ( !isDefined )
	{
		// from light state
		isDefined = lightState->getSpotLightNode()->getPosition( position );

		if ( !isDefined )
		{
			// from default value of the engine
			// @todo getPosition() that returns the value for the field if field is defined, else default value. 
			// @todo or getPosition( position, default) like in python dict. <<< this one is my preferred api.
			position = vgm::Vec3f(0.f, 0.f, 1.f);
		}
	}*/

	isDefined = spotLight->getDirection( direction );
	assert( isDefined );
	/* @todo
	if ( !isDefined )
	{
		// from light state
		isDefined = lightState->getSpotLightNode()->getDirection( direction );

		if ( !isDefined )
		{
			// from default value of the engine
			direction = vgm::Vec3f(0.f, 0.f, -1.f);
		}
	}*/

	// @todo but only with MODEL_MATRIX
	//current.multVecMatrix( position, position );
	//current.multVecMatrix( direction, direction );

	const vgm::Vec3f	eye		( position );
	const vgm::Vec3f	center	( position + direction );
	vgm::Vec3f			up		( 0.f, 1.f, 0.f );

	if ( direction.dot( up ) > 0.5f )
	{
		up.setValue( 1.f, 0.f, 0.f );
	}

	// Updates GLSL state
	const bool castShadow = spotLight->getCastShadow();
	if ( castShadow )
	{
		state.setEnabled( GLSLState::SPOT_LIGHT_CASTING_SHADOW );
	}

	state.setEnabled( GLSLState::SPOT_LIGHT );
	lightState.reset( new LightState(spotLight, GLSLState::SPOT_LIGHT) );
	// @todo api in light state
	lightState->lightViewMatrix.setLookAt( eye, center, up );
	lightState->lightMODELVIEWMatrix = current;

	state.setLight(	node->getMultiAttributeIndex(), lightState );

	//
	vgeGL::rc::applyUsingDisplayList<vgd::node::SpotLight, SpotLight>( engine, node, this );
}



void SpotLight::unapply ( vge::engine::Engine*, vgd::node::Node* )
{}



void SpotLight::setToDefaults()
{
}



void SpotLight::paint( vgeGL::engine::Engine *pGLEngine, vgd::node::SpotLight *pSpotLight )
{
	// Handles PointLight and Light fields
	PointLight::paint( pGLEngine, pSpotLight );

	// Computes the light index
	const GLenum	lightIndex = GL_LIGHT0 + pSpotLight->getMultiAttributeIndex();	
	
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
		assert(	((cutOffAngle >= 0.f) && (cutOffAngle <= 90.f )) ||
				(cutOffAngle == 180.f) && "Unexpected value for cutOffAngle");

		glLightfv( lightIndex, GL_SPOT_CUTOFF, &cutOffAngle );
	}

	// DROPOFFRATE field
	SpotLight::DropOffRateValueType dropOffRate;

	bDefined = pSpotLight->getDropOffRate( dropOffRate );
	
	if ( bDefined )
	{
		assert(	(dropOffRate >= 0.f) && (dropOffRate <= 1.f) && "Unexpected value for dropOffRate" );

		SpotLight::DropOffRateValueType dropOffRateGL = dropOffRate * 128.f;

		glLightfv( lightIndex, GL_SPOT_EXPONENT, &dropOffRateGL );
	}

	// Validates node
	pSpotLight->getDirtyFlag(pSpotLight->getDFNode())->validate();
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
