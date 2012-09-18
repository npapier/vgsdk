// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Noise.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< Noise > Noise::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Noise > node( new Noise(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< Noise > Noise::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< Noise > node = Noise::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< Noise > Noise::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Noise > node = Noise::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



Noise::Noise( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FChannelsSeparatedType(getFChannelsSeparated()) );
	addField( new FUseTextureLessRandomType(getFUseTextureLessRandom()) );
	addField( new FFactorsType(getFFactors()) );
	addField( new FNoiseModelType(getFNoiseModel()) );

	// Sets link(s)

	link( getDFNode() );
}



void Noise::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setChannelsSeparated( (false) );
	setUseTextureLessRandom( (false) );
	setFactors( vgm::Vec2f(0.025, 0.025) );
	setNoiseModel( (PHOTON) );
}



void Noise::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



// ChannelsSeparated

const Noise::ChannelsSeparatedValueType Noise::DEFAULT_CHANNELSSEPARATED = (false);



const Noise::ChannelsSeparatedValueType Noise::getChannelsSeparated() const
{
	return getFieldRO<FChannelsSeparatedType>(getFChannelsSeparated())->getValue();
}



void Noise::setChannelsSeparated( const ChannelsSeparatedValueType value )
{
	getFieldRW<FChannelsSeparatedType>(getFChannelsSeparated())->setValue( value );
}



// UseTextureLessRandom

const Noise::UseTextureLessRandomValueType Noise::DEFAULT_USETEXTURELESSRANDOM = (false);



const Noise::UseTextureLessRandomValueType Noise::getUseTextureLessRandom() const
{
	return getFieldRO<FUseTextureLessRandomType>(getFUseTextureLessRandom())->getValue();
}



void Noise::setUseTextureLessRandom( const UseTextureLessRandomValueType value )
{
	getFieldRW<FUseTextureLessRandomType>(getFUseTextureLessRandom())->setValue( value );
}



// Factors

const Noise::FactorsValueType Noise::DEFAULT_FACTORS = vgm::Vec2f(0.025, 0.025);



const Noise::FactorsValueType Noise::getFactors() const
{
	return getFieldRO<FFactorsType>(getFFactors())->getValue();
}



void Noise::setFactors( const FactorsValueType value )
{
	getFieldRW<FFactorsType>(getFFactors())->setValue( value );
}



// NoiseModel

const Noise::NoiseModelValueType Noise::getNoiseModel() const
{
	return getFieldRO<FNoiseModelType>(getFNoiseModel())->getValue();
}



void Noise::setNoiseModel( const NoiseModelValueType value )
{
	getFieldRW<FNoiseModelType>(getFNoiseModel())->setValue( value );
}



// Field name accessor(s)
const std::string Noise::getFChannelsSeparated( void )
{
	return "f_channelsSeparated";
}



const std::string Noise::getFUseTextureLessRandom( void )
{
	return "f_useTextureLessRandom";
}



const std::string Noise::getFFactors( void )
{
	return "f_factors";
}



const std::string Noise::getFNoiseModel( void )
{
	return "f_noiseModel";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , Noise );



const vgd::basic::RegisterNode<Noise> Noise::m_registrationInstance;



} // namespace node

} // namespace vgd

