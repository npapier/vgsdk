// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/SpotLight.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< SpotLight > SpotLight::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< SpotLight > node( new SpotLight(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< SpotLight > SpotLight::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< SpotLight > node = SpotLight::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< SpotLight > SpotLight::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< SpotLight > node = SpotLight::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



SpotLight::SpotLight( const std::string nodeName ) :
	vgd::node::PointLight( nodeName )
{
	// Adds field(s)
	addField( new FDirectionType(getFDirection()) );
	addField( new FCutOffAngleType(getFCutOffAngle()) );
	addField( new FDropOffRateType(getFDropOffRate()) );

	// Sets link(s)

	link( getDFNode() );
}



void SpotLight::setToDefaults( void )
{
	PointLight::setToDefaults();
}



void SpotLight::setOptionalsToDefaults()
{
	PointLight::setOptionalsToDefaults();
	setDirection( vgm::Vec3f(0.f, 0.f, -1.f) );
	setCutOffAngle( (90.f) );
	setDropOffRate( (0.f) );
}



// Direction

const SpotLight::DirectionValueType SpotLight::DEFAULT_DIRECTION = vgm::Vec3f(0.f, 0.f, -1.f);



const bool SpotLight::getDirection( DirectionValueType& value ) const
{
	return getFieldRO<FDirectionType>(getFDirection())->getValue( value );
}



void SpotLight::setDirection( const DirectionValueType& value )
{
	getFieldRW<FDirectionType>(getFDirection())->setValue( value );
}



void SpotLight::eraseDirection()
{
	getFieldRW<FDirectionType>(getFDirection())->eraseValue();
}


const bool SpotLight::hasDirection() const
{
	return getFieldRO<FDirectionType>(getFDirection())->hasValue();
}



// CutOffAngle

const SpotLight::CutOffAngleValueType SpotLight::DEFAULT_CUTOFFANGLE = (90.f);



const bool SpotLight::getCutOffAngle( CutOffAngleValueType& value ) const
{
	return getFieldRO<FCutOffAngleType>(getFCutOffAngle())->getValue( value );
}



void SpotLight::setCutOffAngle( const CutOffAngleValueType& value )
{
	getFieldRW<FCutOffAngleType>(getFCutOffAngle())->setValue( value );
}



void SpotLight::eraseCutOffAngle()
{
	getFieldRW<FCutOffAngleType>(getFCutOffAngle())->eraseValue();
}


const bool SpotLight::hasCutOffAngle() const
{
	return getFieldRO<FCutOffAngleType>(getFCutOffAngle())->hasValue();
}



// DropOffRate

const SpotLight::DropOffRateValueType SpotLight::DEFAULT_DROPOFFRATE = (0.f);



const bool SpotLight::getDropOffRate( DropOffRateValueType& value ) const
{
	return getFieldRO<FDropOffRateType>(getFDropOffRate())->getValue( value );
}



void SpotLight::setDropOffRate( const DropOffRateValueType& value )
{
	getFieldRW<FDropOffRateType>(getFDropOffRate())->setValue( value );
}



void SpotLight::eraseDropOffRate()
{
	getFieldRW<FDropOffRateType>(getFDropOffRate())->eraseValue();
}


const bool SpotLight::hasDropOffRate() const
{
	return getFieldRO<FDropOffRateType>(getFDropOffRate())->hasValue();
}



// Field name accessor(s)
const std::string SpotLight::getFDirection( void )
{
	return "f_direction";
}



const std::string SpotLight::getFCutOffAngle( void )
{
	return "f_cutOffAngle";
}



const std::string SpotLight::getFDropOffRate( void )
{
	return "f_dropOffRate";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , SpotLight );



const vgd::basic::RegisterNode<SpotLight> SpotLight::m_registrationInstance;



} // namespace node

} // namespace vgd

