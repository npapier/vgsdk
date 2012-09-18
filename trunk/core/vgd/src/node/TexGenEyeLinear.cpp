// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/TexGenEyeLinear.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< TexGenEyeLinear > TexGenEyeLinear::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< TexGenEyeLinear > node( new TexGenEyeLinear(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< TexGenEyeLinear > TexGenEyeLinear::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< TexGenEyeLinear > node = TexGenEyeLinear::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< TexGenEyeLinear > TexGenEyeLinear::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< TexGenEyeLinear > node = TexGenEyeLinear::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



TexGenEyeLinear::TexGenEyeLinear( const std::string nodeName ) :
	vgd::node::TexGen( nodeName )
{
	// Adds field(s)
	addField( new FParametersType(getFParameters()) );

	// Sets link(s)

	link( getDFNode() );
}



void TexGenEyeLinear::setToDefaults( void )
{
	TexGen::setToDefaults();
}



void TexGenEyeLinear::setOptionalsToDefaults()
{
	TexGen::setOptionalsToDefaults();
	setParameters( vgm::MatrixR(vgm::MatrixR::getIdentity()) );
}



// Parameters

const TexGenEyeLinear::ParametersValueType TexGenEyeLinear::DEFAULT_PARAMETERS = vgm::MatrixR(vgm::MatrixR::getIdentity());



const bool TexGenEyeLinear::getParameters( ParametersValueType& value ) const
{
	return getFieldRO<FParametersType>(getFParameters())->getValue( value );
}



void TexGenEyeLinear::setParameters( const ParametersValueType& value )
{
	getFieldRW<FParametersType>(getFParameters())->setValue( value );
}



void TexGenEyeLinear::eraseParameters()
{
	getFieldRW<FParametersType>(getFParameters())->eraseValue();
}


const bool TexGenEyeLinear::hasParameters() const
{
	return getFieldRO<FParametersType>(getFParameters())->hasValue();
}



// Field name accessor(s)
const std::string TexGenEyeLinear::getFParameters( void )
{
	return "f_parameters";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , TexGenEyeLinear );



const vgd::basic::RegisterNode<TexGenEyeLinear> TexGenEyeLinear::m_registrationInstance;



} // namespace node

} // namespace vgd

