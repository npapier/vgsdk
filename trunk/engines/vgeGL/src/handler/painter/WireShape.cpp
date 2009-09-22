// VGSDK - Copyright (C) 2004, 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/WireShape.hpp"

#include <vgd/node/Material.hpp>
#include <vgd/node/WireBox.hpp>
#include <vgd/node/WireQuad.hpp>

#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( WireShape );



const vge::handler::Handler::TargetVector WireShape::getTargets() const
{
	TargetVector targets;
	
	targets.reserve( 2 );
	targets.push_back( vgd::node::WireBox::getClassIndexStatic() );
	targets.push_back( vgd::node::WireQuad::getClassIndexStatic() );	

	return ( targets );
}



void WireShape::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);

	using vgd::node::Material;

	vgm::Vec3f		diffuseColor = glEngine->getGLState().getDiffuse();

	// pre
	// @todo OPTME
	GLboolean bLightingState;
	glGetBooleanv( GL_LIGHTING, &bLightingState );

	glDisable( GL_LIGHTING );
	glDisable( GL_COLOR_MATERIAL );

	glColor3fv( diffuseColor.getValue() );

	// render
	VertexShape::apply( engine, node );

	// post
	if ( bLightingState == GL_TRUE )
	{
		glEnable( GL_LIGHTING );
	}
}



void WireShape::unapply ( vge::engine::Engine* , vgd::node::Node* )
{
}



void WireShape::setToDefaults()
{
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
