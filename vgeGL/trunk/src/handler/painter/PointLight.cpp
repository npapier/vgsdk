// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/PointLight.hpp"

#include <vgd/node/PointLight.hpp>

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

	return ( targets );
}



void PointLight::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
	vgeGL::rc::applyUsingDisplayList<vgd::node::PointLight, PointLight>( pEngine, pNode, this );
}



void PointLight::unapply ( vge::engine::Engine* , vgd::node::Node* )
{
}



void PointLight::setToDefaults()
{
	Light::setToDefaults();
}



void PointLight::paint(	vgeGL::engine::Engine *pGLEngine, vgd::node::PointLight *pPointLight )
{
	// render Light fields.
	Light::paint( pGLEngine, pPointLight );

	// render PointLight fields.
	GLenum		lightGL;
	bool			bDefined;
	vgm::Vec3f	position;

	lightGL	= GL_LIGHT0 + pPointLight->getMultiAttributeIndex();
	
	bDefined		= pPointLight->getPosition( position );
		
	if ( bDefined )
	{
		// use position field
		vgm::Vec4f positionGL(
				position[0], position[1], position[2],		// position of light
				1.f 													// not a directional light
				);

		glLightfv( lightGL, GL_POSITION, positionGL.getValue() );
	}
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
