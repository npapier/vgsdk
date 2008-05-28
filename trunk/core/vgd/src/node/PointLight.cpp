// VGSDK - Copyright (C) 2004, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/PointLight.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( PointLight );



PointLight::PointLight( const std::string nodeName ) :
	vgd::node::Light( nodeName )
{
	// Add field
	addField( new FPositionType(getFPosition()) );

	// Link(s)
	link( getFPosition(), getDFNode() );
}




void PointLight::setToDefaults( void )
{
	Light::setToDefaults();
}



void PointLight::setOptionalsToDefaults()
{
	Light::setOptionalsToDefaults();

	setPosition( vgm::Vec3f( 0.f, 0.f, 1.f ) );
}



// POSITION
bool PointLight::getPosition( PositionValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< int /*PositionParameterType*/, PositionValueType >( this, getFPosition(), POSITION, value )
		);
}



void PointLight::setPosition( PositionValueType value )
{
	vgd::field::setParameterValue< int /*PositionParameterType*/, PositionValueType >( this, getFPosition(), POSITION, value );
}



void PointLight::erasePosition()
{
	vgd::field::eraseParameterValue< int /*PositionParameterType*/, PositionValueType >( this, getFPosition(), POSITION );
}



const std::string PointLight::getFPosition( void )
{
	return ( "f_position" );
}



} // namespace node

} // namespace vgd
