// VGSDK - Copyright (C) 2014, Nicolas Papier.
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
	addField( new FNoiseModelType(getFNoiseModel()) );
	addField( new FFactorsType(getFFactors()) );
	addField( new FChannelsSeparatedType(getFChannelsSeparated()) );
	addField( new FRandomTextureScaleFactorsType(getFRandomTextureScaleFactors()) );
	addField( new FUseTextureLessRandomType(getFUseTextureLessRandom()) );
	addField( new FFrequencyType(getFFrequency()) );

	// Sets link(s)

	link( getDFNode() );
}



void Noise::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setNoiseModel( (PHOTON) );
	setFactors( vgm::Vec4f(0.025f, 0.025f, 4.f, 1.f) );
	setChannelsSeparated( (false) );
	setRandomTextureScaleFactors( vgm::Vec2f(1.f, 1.f) );
	setUseTextureLessRandom( (false) );
}



void Noise::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	setFrequency( (25) );
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



// Factors

const Noise::FactorsValueType Noise::DEFAULT_FACTORS = vgm::Vec4f(0.025f, 0.025f, 4.f, 1.f);



const Noise::FactorsValueType Noise::getFactors() const
{
	return getFieldRO<FFactorsType>(getFFactors())->getValue();
}



void Noise::setFactors( const FactorsValueType value )
{
	getFieldRW<FFactorsType>(getFFactors())->setValue( value );
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



// RandomTextureScaleFactors

const Noise::RandomTextureScaleFactorsValueType Noise::DEFAULT_RANDOMTEXTURESCALEFACTORS = vgm::Vec2f(1.f, 1.f);



const Noise::RandomTextureScaleFactorsValueType Noise::getRandomTextureScaleFactors() const
{
	return getFieldRO<FRandomTextureScaleFactorsType>(getFRandomTextureScaleFactors())->getValue();
}



void Noise::setRandomTextureScaleFactors( const RandomTextureScaleFactorsValueType value )
{
	getFieldRW<FRandomTextureScaleFactorsType>(getFRandomTextureScaleFactors())->setValue( value );
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



// Frequency

const Noise::FrequencyValueType Noise::DEFAULT_FREQUENCY = (25);



const bool Noise::getFrequency( FrequencyValueType& value ) const
{
	return getFieldRO<FFrequencyType>(getFFrequency())->getValue( value );
}



void Noise::setFrequency( const FrequencyValueType& value )
{
	getFieldRW<FFrequencyType>(getFFrequency())->setValue( value );
}



void Noise::eraseFrequency()
{
	getFieldRW<FFrequencyType>(getFFrequency())->eraseValue();
}


const bool Noise::hasFrequency() const
{
	return getFieldRO<FFrequencyType>(getFFrequency())->hasValue();
}



// Field name accessor(s)
const std::string Noise::getFNoiseModel( void )
{
	return "f_noiseModel";
}



const std::string Noise::getFFactors( void )
{
	return "f_factors";
}



const std::string Noise::getFChannelsSeparated( void )
{
	return "f_channelsSeparated";
}



const std::string Noise::getFRandomTextureScaleFactors( void )
{
	return "f_randomTextureScaleFactors";
}



const std::string Noise::getFUseTextureLessRandom( void )
{
	return "f_useTextureLessRandom";
}



const std::string Noise::getFFrequency( void )
{
	return "f_frequency";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , Noise );



const vgd::basic::RegisterNode<Noise> Noise::m_registrationInstance;



} // namespace node

} // namespace vgd

