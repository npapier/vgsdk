// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Material.hpp"

#include <vgd/node/Material.hpp>

#include "vgeGL/rc/TDisplayListHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( Material );



/*const vge::service::List Material::getServices() const
{
	vge::service::List list;
	list.push_back( vgd::Shp<vge::service::Service>( new vge::service::Painter ) );

	return ( list );
}*/



const vge::handler::Handler::TargetVector Material::getTargets() const
{
	vge::handler::Handler::TargetVector targets;

	targets.push_back( vgd::node::Material::getClassIndexStatic() );

	return ( targets );
}



void Material::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
	vgeGL::rc::applyUsingDisplayList< vgd::node::Material, Material >( pEngine, pNode, this );
}



void Material::unapply ( vge::engine::Engine* engine, vgd::node::Node* pNode )
{
}



void Material::setToDefaults()
{
	vgm::Vec4f color4;
	
	// COLOR and PROPERTY
	color4.setValue( 0.2f, 0.2f, 0.2f, 1.f );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, color4.getValue() );

	color4.setValue( 0.8f, 0.8f, 0.8f, 1.f );
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, color4.getValue() );	

	color4.null();
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, color4.getValue() );
	
	glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, color4.getValue() );

	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 0.f );
}



void Material::paint( vgeGL::engine::Engine *pGLEngine, vgd::node::Material *pMaterial )
{
	float			transparency;	
	
	bool			bDefined;
	vgm::Vec3f	color3;

	vgm::Vec4f	color4;

	// TRANSPARENCY
	transparency = pMaterial->getTransparency();

	// SHININESS
	float shininess;
	bDefined = pMaterial->getShininess( shininess );
	
	if ( bDefined )
	{
		assert( shininess >= 0.f && "Negativ shininess." );
		assert( shininess <= 1.f && "Shininess superior to 1." );
		
		shininess *= 128.f;
		glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shininess );
	}

	//	COLOR
	bDefined = pMaterial->getColor( vgd::node::Material::AMBIENT, color3 );

	if ( bDefined )
	{
		color4.setValue( color3[0], color3[1], color3[2], transparency );
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, color4.getValue() );
	}
	
	//
	bDefined = pMaterial->getColor( vgd::node::Material::DIFFUSE, color3 );

	if ( bDefined )
	{
		color4.setValue( color3[0], color3[1], color3[2], transparency );
		glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, color4.getValue() );
	}
	
	//
	bDefined = pMaterial->getColor( vgd::node::Material::SPECULAR, color3 );

	if ( bDefined )
	{
		color4.setValue( color3[0], color3[1], color3[2], transparency );
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, color4.getValue() );
	}

	//
	bDefined = pMaterial->getColor( vgd::node::Material::EMISSION, color3 );

	if ( bDefined )
	{
		color4.setValue( color3[0], color3[1], color3[2], transparency );
		glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, color4.getValue() );
	}
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
