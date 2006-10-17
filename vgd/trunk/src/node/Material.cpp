// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Material.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( Material );



Material::Material( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Add field
	addField( new FColorType(getFColor()) );
	addField( new FShininessType(getFShininess()) );
	addField( new FTransparencyType(getFTransparency()) );

	// Link
	link( getDFNode() );
}



void Material::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	
	setTransparency( 1.f );
}



void Material::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	
	setColor( AMBIENT,	vgm::Vec3f( 0.2f, 0.2f, 0.2f ) );
	setColor( DIFFUSE,	vgm::Vec3f( 0.8f, 0.8f, 0.8f ) );
	setColor( SPECULAR,	vgm::Vec3f( 0.f, 0.f, 0.f ) );
	setColor( EMISSION,	vgm::Vec3f( 0.f, 0.f, 0.f ) );

	setShininess( 0.f );
}



// COLOR
bool Material::getColor( const ColorParameterType param, ColorValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< ColorParameterType, ColorValueType >( this, getFColor(), param, value )
		);
}



void Material::setColor( const ColorParameterType param, ColorValueType value )
{
	vgd::field::setParameterValue< ColorParameterType, ColorValueType >( this, getFColor(), param, value );
}



void Material::eraseColor( const ColorParameterType param )
{
	vgd::field::eraseParameterValue< ColorParameterType, ColorValueType >( this, getFColor(), param );
}



// PROPERTY
bool Material::getShininess( ShininessValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< ShininessParameterType, ShininessValueType >( this, getFShininess(), SHININESS, value )
		);
}



void Material::setShininess( ShininessValueType value )
{
	vgd::field::setParameterValue< ShininessParameterType, ShininessValueType >( this, getFShininess(), SHININESS, value );
}



void Material::eraseShininess()
{
	vgd::field::eraseParameterValue< ShininessParameterType, ShininessValueType >( this, getFShininess(), SHININESS );
}



// TRANSPARENCY
float Material::getTransparency( void ) const
{
	return ( getFieldRO<FTransparencyType>(getFTransparency())->getValue() );
}



void Material::setTransparency( float transparency )
{
	getFieldRW<FTransparencyType>(getFTransparency())->setValue( transparency );
}



// FIELDS
const std::string Material::getFColor()
{
	return ( "f_color" );
}



const std::string Material::getFShininess()
{
	return ( "f_shininess" );
}



const std::string Material::getFTransparency()
{
	return ( "f_transparency" );
}



} // namespace node

} // namespace vgd
