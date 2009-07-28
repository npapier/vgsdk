// VGSDK - Copyright (C) 2004, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/DirectionalLight.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( DirectionalLight );



DirectionalLight::DirectionalLight( const std::string nodeName ) :
	vgd::node::Light( nodeName )
{
	// Add field
	addField( new FDirectionType(getFDirection()) );

	// Link(s)
	link( getFDirection(), getDFNode() );
}




void DirectionalLight::setToDefaults( void )
{
	Light::setToDefaults();
}



void DirectionalLight::setOptionalsToDefaults()
{
	Light::setOptionalsToDefaults();

	setDirection( vgm::Vec3f( 0.f, 0.f, -1.f ) );
}



// DIRECTION
bool DirectionalLight::getDirection( DirectionValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< int /*DirectionParameterType*/, DirectionValueType >( this, getFDirection(), DIRECTION, value )
		);
}



void DirectionalLight::setDirection( DirectionValueType value )
{
	vgd::field::setParameterValue< int /*DirectionParameterType*/, DirectionValueType >( this, getFDirection(), DIRECTION, value );
}



void DirectionalLight::eraseDirection()
{
	vgd::field::eraseParameterValue< int /*DirectionParameterType*/, DirectionValueType >( this, getFDirection(), DIRECTION );
}



const std::string DirectionalLight::getFDirection( void )
{
	return "f_direction";
}



} // namespace node

} // namespace vgd