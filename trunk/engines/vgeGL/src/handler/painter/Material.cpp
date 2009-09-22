// VGSDK - Copyright (C) 2004, 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Material.hpp"

#include <vgd/node/Material.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/rc/TDisplayListHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( Material );



const vge::handler::Handler::TargetVector Material::getTargets() const
{
	vge::handler::Handler::TargetVector targets;

	targets.push_back( vgd::node::Material::getClassIndexStatic() );

	return targets;
}



void Material::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);

	assert( dynamic_cast< vgd::node::Material* >(node) != 0 );
	vgd::node::Material *material = static_cast< vgd::node::Material* >(node);

	// Updates GLState
	// OPACITY
	const float	opacity = material->getOpacity();
	glEngine->getGLState().setOpacity( opacity );

	// DIFFUSE
	bool isDefined;
	vgm::Vec3f diffuse;

	isDefined = material->getDiffuse( diffuse );

	if ( isDefined )
	{
		glEngine->getGLState().setDiffuse( diffuse );
	}

	//
	vgeGL::rc::applyUsingDisplayList< vgd::node::Material, Material >( engine, node, this );
	//paint( glEngine, castedNode );
}



void Material::unapply ( vge::engine::Engine* , vgd::node::Node* )
{
}



void Material::setToDefaults()
{
	vgm::Vec4f color4;

	// COLOR and PROPERTY
	color4.setValue( 0.2f, 0.2f, 0.2f, 0.f );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, color4.getValue() );

	color4.setValue( 0.8f, 0.8f, 0.8f, 0.f );
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, color4.getValue() );

	color4.null();
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, color4.getValue() );

	glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, color4.getValue() );

	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 0.f );
}



void Material::paint( vgeGL::engine::Engine *, vgd::node::Material * material )
{
/*	// Default values
	const vgm::Vec3f	defaultAmbient		( 0.2f, 0.2f, 0.2f 	);
	const vgm::Vec3f	defaultDiffuse		( 0.8f, 0.8f, 0.8f 	);
	const vgm::Vec3f	defaultSpecular		( 0.f, 0.f, 0.f 	);
	const vgm::Vec3f	defaultEmission		( 0.f, 0.f, 0.f 	);

	const float			defaultShininess	( 0.f				);
*/
	//
	bool		bDefined;
	vgm::Vec3f	color3;
	vgm::Vec4f	color4;

	// OPACITY
	const float	opacity = material->getOpacity();

	// SHININESS
	float shininess;
	bDefined = material->getShininess( shininess );

	if ( bDefined )
	{
		assert( shininess >= 0.f && "Negative shininess." );
		assert( shininess <= 1.f && "Shininess superior to 1." );

		shininess *= 128.f;
		glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shininess );
	}

	// COLOR
	bDefined = material->getAmbient( color3 );

	if ( bDefined )
	{
		color4.setValue( color3[0], color3[1], color3[2], 0.f );
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, color4.getValue() );
	}

	//
	bDefined = material->getDiffuse( color3 );

	color4.setValue( color3[0], color3[1], color3[2], opacity );
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, color4.getValue() );

	//
	bDefined = material->getSpecular( color3 );

	if ( bDefined )
	{
		color4.setValue( color3[0], color3[1], color3[2], 0.f );
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, color4.getValue() );
	}

	//
	bDefined = material->getEmission( color3 );

	if ( bDefined )
	{
		color4.setValue( color3[0], color3[1], color3[2], 0.f );
		glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, color4.getValue() );
	}

	// Validates node
	material->getDirtyFlag(material->getDFNode())->validate();
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
