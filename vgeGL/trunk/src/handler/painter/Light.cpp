// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Light.hpp"

#include <vgd/node/Light.hpp>
#include <vge/service/Painter.hpp>

#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{
	


//META_HANDLER_CPP( Light );



void Light::paint( vgeGL::engine::Engine *pEngine, vgd::node::Light *pLight )
{
	bool bDefined;
	bool value;
	bDefined = pLight->getOn( value );
	
	if ( bDefined )
	{
		// index of light
		if ( value )
		{
			glEnable( GL_LIGHT0 + pLight->getMultiAttributeIndex() );
		}
		else
		{
			glDisable( GL_LIGHT0 + pLight->getMultiAttributeIndex() );
		}
	}
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
		glDisable( lightI );
		
		//
		vgm::Vec4f positionGL( 0.f, 0.f, 1.f, 0.f );

		glLightfv( lightI, GL_POSITION, positionGL.getValue() );

		//
		GLfloat color[] = { 1.0, 1.0, 1.0, 1.0 };
		
		glLightfv( lightI, GL_DIFFUSE, color );
		glLightfv( lightI, GL_SPECULAR, color );
	}
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
