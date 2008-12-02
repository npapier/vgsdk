// VGSDK - Copyright (C) 2006, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/SpotLight.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( SpotLight );



SpotLight::SpotLight( const std::string nodeName ) :
	vgd::node::PointLight( nodeName )
{
	// Add field
	addField( new FDirectionType(getFDirection()) );
	addField( new FCutOffAngleType(getFCutOffAngle()) );
	addField( new FDropOffRateType(getFDropOffRate()) );

	// Link(s)
	link( getDFNode() );
}



void SpotLight::setToDefaults( void )
{
	PointLight::setToDefaults();
}



void SpotLight::setOptionalsToDefaults()
{
	PointLight::setOptionalsToDefaults();

	setDirection( vgm::Vec3f( 0.f, 0.f, -1.f ) );
	setCutOffAngle( 90 );
	setDropOffRate( 0 );
}



// DIRECTION
bool SpotLight::getDirection( DirectionValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< int /*DirectionParameterType*/, DirectionValueType >( this, getFDirection(), DIRECTION, value )
		);
}



void SpotLight::setDirection( DirectionValueType value )
{
	vgd::field::setParameterValue< int /*DirectionParameterType*/, DirectionValueType >( this, getFDirection(), DIRECTION, value );
}



void SpotLight::eraseDirection()
{
	vgd::field::eraseParameterValue< int /*DirectionParameterType*/, DirectionValueType >( this, getFDirection(), DIRECTION );
}



// CUTOFFANGLE
bool SpotLight::getCutOffAngle( CutOffAngleValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< int /*CutOffAngleParameterType*/, CutOffAngleValueType >( this, getFCutOffAngle(), CUTOFFANGLE, value )
		);
}



void SpotLight::setCutOffAngle( CutOffAngleValueType value )
{
	vgd::field::setParameterValue< int /*CutOffAngleParameterType*/, CutOffAngleValueType >( this, getFCutOffAngle(), CUTOFFANGLE, value );
}



void SpotLight::eraseCutOffAngle()
{
	vgd::field::eraseParameterValue< int /*CutOffAngleParameterType*/, CutOffAngleValueType >( this, getFCutOffAngle(), CUTOFFANGLE );
}



// DROPOFFRATE
bool SpotLight::getDropOffRate( DropOffRateValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< int /*DropOffRateParameterType*/, DropOffRateValueType >( this, getFDropOffRate(), DROPOFFRATE, value )
		);
}



void SpotLight::setDropOffRate( DropOffRateValueType value )
{
	vgd::field::setParameterValue< int /*DropOffRateParameterType*/, DropOffRateValueType >( this, getFDropOffRate(), DROPOFFRATE, value );
}



void SpotLight::eraseDropOffRate()
{
	vgd::field::eraseParameterValue< int /*DropOffRateParameterType*/, DropOffRateValueType >( this, getFDropOffRate(), DROPOFFRATE );
}



// FIELDS
const std::string SpotLight::getFDirection()
{
	return "f_direction";
}



const std::string SpotLight::getFCutOffAngle()
{
	return "f_cutOffAngle";
}



const std::string SpotLight::getFDropOffRate()
{
	return "f_dropOffRate";
}



} // namespace node

} // namespace vgd
