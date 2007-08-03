// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/DirectionalLight.hpp"

#include <vgd/node/DirectionalLight.hpp>

#include "vgeGL/rc/TDisplayListHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{
	


META_HANDLER_CPP( DirectionalLight );



const vge::handler::Handler::TargetVector DirectionalLight::getTargets() const
{
	vge::handler::Handler::TargetVector targets;

	targets.push_back( vgd::node::DirectionalLight::getClassIndexStatic() );

	return targets;
}



void DirectionalLight::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
	vgeGL::rc::applyUsingDisplayList<vgd::node::DirectionalLight, DirectionalLight>( pEngine, pNode, this );
}



void DirectionalLight::unapply ( vge::engine::Engine*, vgd::node::Node* )
{}



void DirectionalLight::setToDefaults()
{
	Light::setToDefaults();
}



void DirectionalLight::paint(	vgeGL::engine::Engine *pGLEngine, vgd::node::DirectionalLight *pDirectionalLight )
{
	// render Light fields.
	Light::paint( pGLEngine, pDirectionalLight );

	// render DirectionalLight fields.
	GLenum lightIndex;
	bool bDefined;
	vgm::Vec3f direction;

	lightIndex	= GL_LIGHT0 + pDirectionalLight->getMultiAttributeIndex();
	
	bDefined		= pDirectionalLight->getDirection( direction );
		
	if ( bDefined )
	{
		// use direction field
		vgm::Vec4f positionGL(
				-direction[0], -direction[1], -direction[2],	// direction of light
				0.f 											// directional light
				);

		// direction of light is set by GL_POSITION for directional light
		glLightfv( lightIndex, GL_POSITION, positionGL.getValue() );
	}
	
	// Validate node
	pDirectionalLight->getDirtyFlag(pDirectionalLight->getDFNode())->validate();	
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
