// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/EngineProperties.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< EngineProperties > EngineProperties::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< EngineProperties > node( new EngineProperties(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< EngineProperties > EngineProperties::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< EngineProperties > node = EngineProperties::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< EngineProperties > EngineProperties::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< EngineProperties > node = EngineProperties::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



EngineProperties::EngineProperties( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FTessellationBiasType(getFTessellationBias()) );
	addField( new FMaxAnisotropyType(getFMaxAnisotropy()) );
	addField( new FTessellationFactorType(getFTessellationFactor()) );
	addField( new FTessellationType(getFTessellation()) );

	// Sets link(s)

	link( getDFNode() );
}



void EngineProperties::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setTessellationBias( (0.55f) );
	setTessellationFactor( (2.0f) );
	setTessellation( (false) );
}



void EngineProperties::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	setMaxAnisotropy( (1.f) );
}



// TessellationBias

const EngineProperties::TessellationBiasValueType EngineProperties::DEFAULT_TESSELLATIONBIAS = (0.55f);



const EngineProperties::TessellationBiasValueType EngineProperties::getTessellationBias() const
{
	return getFieldRO<FTessellationBiasType>(getFTessellationBias())->getValue();
}



void EngineProperties::setTessellationBias( const TessellationBiasValueType value )
{
	getFieldRW<FTessellationBiasType>(getFTessellationBias())->setValue( value );
}



// MaxAnisotropy

const EngineProperties::MaxAnisotropyValueType EngineProperties::DEFAULT_MAXANISOTROPY = (1.f);



const bool EngineProperties::getMaxAnisotropy( MaxAnisotropyValueType& value ) const
{
	return getFieldRO<FMaxAnisotropyType>(getFMaxAnisotropy())->getValue( value );
}



void EngineProperties::setMaxAnisotropy( const MaxAnisotropyValueType& value )
{
	getFieldRW<FMaxAnisotropyType>(getFMaxAnisotropy())->setValue( value );
}



void EngineProperties::eraseMaxAnisotropy()
{
	getFieldRW<FMaxAnisotropyType>(getFMaxAnisotropy())->eraseValue();
}


const bool EngineProperties::hasMaxAnisotropy() const
{
	return getFieldRO<FMaxAnisotropyType>(getFMaxAnisotropy())->hasValue();
}



// TessellationFactor

const EngineProperties::TessellationFactorValueType EngineProperties::DEFAULT_TESSELLATIONFACTOR = (2.0f);



const EngineProperties::TessellationFactorValueType EngineProperties::getTessellationFactor() const
{
	return getFieldRO<FTessellationFactorType>(getFTessellationFactor())->getValue();
}



void EngineProperties::setTessellationFactor( const TessellationFactorValueType value )
{
	getFieldRW<FTessellationFactorType>(getFTessellationFactor())->setValue( value );
}



// Tessellation

const EngineProperties::TessellationValueType EngineProperties::DEFAULT_TESSELLATION = (false);



const EngineProperties::TessellationValueType EngineProperties::getTessellation() const
{
	return getFieldRO<FTessellationType>(getFTessellation())->getValue();
}



void EngineProperties::setTessellation( const TessellationValueType value )
{
	getFieldRW<FTessellationType>(getFTessellation())->setValue( value );
}



// Field name accessor(s)
const std::string EngineProperties::getFTessellationBias( void )
{
	return "f_tessellationBias";
}



const std::string EngineProperties::getFMaxAnisotropy( void )
{
	return "f_maxAnisotropy";
}



const std::string EngineProperties::getFTessellationFactor( void )
{
	return "f_tessellationFactor";
}



const std::string EngineProperties::getFTessellation( void )
{
	return "f_tessellation";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , EngineProperties );



const vgd::basic::RegisterNode<EngineProperties> EngineProperties::m_registrationInstance;



} // namespace node

} // namespace vgd

