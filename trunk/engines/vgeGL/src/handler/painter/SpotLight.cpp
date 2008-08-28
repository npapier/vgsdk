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
	vgd::node::SpotLight *spotlight = static_cast< vgd::node::SpotLight* >(node);

	if ( glEngine->isGLSLEnabled() )
	{
		// Retrieves GLSL state
		using vgeGL::engine::GLSLState;
		typedef vgeGL::engine::GLSLState::LightState LightState;

		GLSLState& state = glEngine->getGLSLState();

		// Updates GLSL state
		state.setEnabled( GLSLState::SPOT_LIGHT );

		vgd::Shp< LightState > lightState( new LightState(spotlight, GLSLState::SPOT_LIGHT) );
		state.setLight(	node->getMultiAttributeIndex(), lightState );
	}

	vgeGL::rc::applyUsingDisplayList<vgd::node::SpotLight, SpotLight>( engine, node, this );
}



void SpotLight::unapply ( vge::engine::Engine*, vgd::node::Node* )
{}



void SpotLight::setToDefaults()
{
	PointLight::setToDefaults();
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
