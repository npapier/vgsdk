// VGSDK - Copyright (C) 2004, 2006, 2008, 2009, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Light.hpp"

#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/Light.hpp>
#include <vge/service/Painter.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/GLSLState.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



//META_HANDLER_CPP( Light );



void Light::updateUnitState( vgeGL::engine::Engine * engine, vgd::node::Light * light, vgd::Shp< vgeGL::engine::LightState > lightState )
{
	// ON
	vgd::node::Light::OnValueType on;
	bool bDefined = light->getOn( on );
	if ( bDefined )		lightState->setOn( on );

	// CASTSHADOW
	if ( engine->isShadowEnabled() )
	{
		lightState->setCastShadow( light->getCastShadow() );
	}
}



void Light::paint( vgeGL::engine::Engine *, vgd::node::Light * light )
{
	// Computes the light index
	const GLenum lightIndex = GL_LIGHT0 + light->getMultiAttributeIndex();

	bool bDefined;

	// Handles field ON
	bool value;
	bDefined = light->getOn( value );

	if ( bDefined )
	{
		if ( value )
		{
			glEnable( lightIndex );
		}
		else
		{
			glDisable( lightIndex );
		}
	}
	
	// Handles field COLOR.(ambient,diffuse and specular)

	using vgd::node::Light;
	vgm::Vec4f color;

	bDefined = light->getAmbient( color );
	if ( bDefined )	glLightfv( lightIndex, GL_AMBIENT, color.getValue() );

	bDefined = light->getDiffuse( color );
	if ( bDefined )	glLightfv( lightIndex, GL_DIFFUSE, color.getValue() );

	bDefined = light->getSpecular( color );
	if ( bDefined )	glLightfv( lightIndex, GL_SPECULAR, color.getValue() );

	// Validates node
	light->getDirtyFlag(light->getDFNode())->validate();
}



void Light::setToDefaults()
{
	// FIXME
	GLint	maxLights;
	glGetIntegerv(GL_MAX_LIGHTS, &maxLights );

	for(	int32 lightI		= GL_LIGHT0;
			lightI < GL_LIGHT0 + maxLights;
			++lightI )
	{
		// ON
		glDisable( lightI );

		// COLOR
		GLfloat color0[] = { 0.f, 0.f, 0.f, 0.f };
		GLfloat color1[] = { 1.f, 1.f, 1.f, 0.f };

		glLightfv( lightI, GL_AMBIENT, color0 );
		glLightfv( lightI, GL_DIFFUSE, color1 );
		glLightfv( lightI, GL_SPECULAR, color1 );

		// POSITION
		vgm::Vec4f position( 0.f, 0.f, 1.f, 0.f );

		glLightfv( lightI, GL_POSITION, position.getValue() );

		// DIRECTION
		vgm::Vec3f direction( 0.f, 0.f, -1.f );

		glLightfv( lightI, GL_SPOT_DIRECTION, direction.getValue() );

		// CUTOFFANGLE
		const float cutOffAngle = 180.f;

		glLightfv( lightI, GL_SPOT_CUTOFF, &cutOffAngle );

		// DROPOFFRATE
		const float dropOffRate = 0;
		glLightfv( lightI, GL_SPOT_EXPONENT, &dropOffRate );
	}
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
