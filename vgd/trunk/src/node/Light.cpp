// VGSDK - Copyright (C) 2004, 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Light.hpp"

#include "vgd/field/TAccessors.hpp"



namespace vgd
{

namespace node
{



//META_NODE_CPP( Light );



Light::Light( const std::string nodeName ) :
	vgd::node::MultiAttribute( nodeName )
{
	// Add field
	addField( new FOnType(getFOn()) );
	addField( new FColorType(getFColor()) );

	// Link(s)
	link( getDFNode() );
}



void Light::setToDefaults( void )
{
	MultiAttribute::setToDefaults();
}



void Light::setOptionalsToDefaults()
{
	MultiAttribute::setOptionalsToDefaults();

	setOn( false );

	setColor( AMBIENT,	vgm::Vec4f( 0.f, 0.f, 0.f, 1.f ) );
	setColor( DIFFUSE,	vgm::Vec4f( 1.f, 1.f, 1.f, 1.f ) );
	setColor( SPECULAR,	vgm::Vec4f( 1.f, 1.f, 1.f, 1.f ) );
}



// ON
bool Light::getOn( OnValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< OnParameterType, OnValueType >( this, getFOn(), ON, value )
		);
}



void Light::setOn( OnValueType value )
{
	vgd::field::setParameterValue< OnParameterType, OnValueType >( this, getFOn(), ON, value );
}



void Light::eraseOn()
{
	vgd::field::eraseParameterValue< OnParameterType, OnValueType >( this, getFOn(), ON );
}



// COLOR
bool Light::getColor( const ColorParameterType param, ColorValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< ColorParameterType, ColorValueType >( this, getFColor(), param, value )
		);
}



void Light::setColor( const ColorParameterType param, ColorValueType value )
{
	vgd::field::setParameterValue< ColorParameterType, ColorValueType >( this, getFColor(), param, value );
}



void Light::eraseColor( const ColorParameterType param )
{
	vgd::field::eraseParameterValue< ColorParameterType, ColorValueType >( this, getFColor(), param );
}



// FIELDS
const std::string Light::getFOn()
{
	return ( "f_on" );
}



const std::string Light::getFColor()
{
	return ( "f_color" );
}



} // namespace node

} // namespace vgd
