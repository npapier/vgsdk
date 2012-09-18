// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/PostProcessing.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< PostProcessing > PostProcessing::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< PostProcessing > node( new PostProcessing(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< PostProcessing > PostProcessing::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< PostProcessing > node = PostProcessing::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< PostProcessing > PostProcessing::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< PostProcessing > node = PostProcessing::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



PostProcessing::PostProcessing( const std::string nodeName ) :
	vgd::node::MultiAttribute( nodeName )
{
	// Adds field(s)
	addField( new FInput2Type(getFInput2()) );
	addField( new FInput0Type(getFInput0()) );
	addField( new FInput1Type(getFInput1()) );
	addField( new FCustomFilterDefinitionType(getFCustomFilterDefinition()) );
	addField( new FFilterType(getFFilter()) );
	addField( new FParam4f1Type(getFParam4f1()) );
	addField( new FTexture0Type(getFTexture0()) );
	addField( new FInput0SamplingType(getFInput0Sampling()) );
	addField( new FCustomFilterApplyType(getFCustomFilterApply()) );
	addField( new FOutputType(getFOutput()) );
	addField( new FParam1f0Type(getFParam1f0()) );
	addField( new FParam1f1Type(getFParam1f1()) );
	addField( new FParam4f0Type(getFParam4f0()) );
	addField( new FParam4x4f0Type(getFParam4x4f0()) );

	// Sets link(s)

	link( getDFNode() );
}



void PostProcessing::setToDefaults( void )
{
	MultiAttribute::setToDefaults();
	setInput2( (INPUT2_NONE) );
	setInput0( (PREVIOUS0) );
	setInput1( (INPUT1_NONE) );
	setCustomFilterDefinition( std::string() );
	setFilter( (NO_FILTER) );
	setInput0Sampling( (INPUT0SAMPLING_NONE) );
	setCustomFilterApply( std::string() );
	setOutput( (OUTPUT_TMP0) );
}



void PostProcessing::setOptionalsToDefaults()
{
	MultiAttribute::setOptionalsToDefaults();
	setParam4f1( vgm::Vec4f(0.0, 0.0, 0.0, 0.0) );
	setTexture0( vgd::node::NodeWkp() );
	setParam1f0( (0.0) );
	setParam1f1( (0.0) );
	setParam4f0( vgm::Vec4f(0.0, 0.0, 0.0, 0.0) );
	setParam4x4f0( vgm::MatrixR(vgm::MatrixR::getIdentity()) );
}



// Input2

const PostProcessing::Input2ValueType PostProcessing::getInput2() const
{
	return getFieldRO<FInput2Type>(getFInput2())->getValue();
}



void PostProcessing::setInput2( const Input2ValueType value )
{
	getFieldRW<FInput2Type>(getFInput2())->setValue( value );
}



// Input0

const PostProcessing::Input0ValueType PostProcessing::getInput0() const
{
	return getFieldRO<FInput0Type>(getFInput0())->getValue();
}



void PostProcessing::setInput0( const Input0ValueType value )
{
	getFieldRW<FInput0Type>(getFInput0())->setValue( value );
}



// Input1

const PostProcessing::Input1ValueType PostProcessing::getInput1() const
{
	return getFieldRO<FInput1Type>(getFInput1())->getValue();
}



void PostProcessing::setInput1( const Input1ValueType value )
{
	getFieldRW<FInput1Type>(getFInput1())->setValue( value );
}



// CustomFilterDefinition

const PostProcessing::CustomFilterDefinitionValueType PostProcessing::DEFAULT_CUSTOMFILTERDEFINITION = std::string();



const PostProcessing::CustomFilterDefinitionValueType PostProcessing::getCustomFilterDefinition() const
{
	return getFieldRO<FCustomFilterDefinitionType>(getFCustomFilterDefinition())->getValue();
}



void PostProcessing::setCustomFilterDefinition( const CustomFilterDefinitionValueType value )
{
	getFieldRW<FCustomFilterDefinitionType>(getFCustomFilterDefinition())->setValue( value );
}



// Filter

const PostProcessing::FilterValueType PostProcessing::getFilter() const
{
	return getFieldRO<FFilterType>(getFFilter())->getValue();
}



void PostProcessing::setFilter( const FilterValueType value )
{
	getFieldRW<FFilterType>(getFFilter())->setValue( value );
}



// Param4f1

const PostProcessing::Param4f1ValueType PostProcessing::DEFAULT_PARAM4F1 = vgm::Vec4f(0.0, 0.0, 0.0, 0.0);



const bool PostProcessing::getParam4f1( Param4f1ValueType& value ) const
{
	return getFieldRO<FParam4f1Type>(getFParam4f1())->getValue( value );
}



void PostProcessing::setParam4f1( const Param4f1ValueType& value )
{
	getFieldRW<FParam4f1Type>(getFParam4f1())->setValue( value );
}



void PostProcessing::eraseParam4f1()
{
	getFieldRW<FParam4f1Type>(getFParam4f1())->eraseValue();
}


const bool PostProcessing::hasParam4f1() const
{
	return getFieldRO<FParam4f1Type>(getFParam4f1())->hasValue();
}



// Texture0

const PostProcessing::Texture0ValueType PostProcessing::DEFAULT_TEXTURE0 = vgd::node::NodeWkp();



const bool PostProcessing::getTexture0( Texture0ValueType& value ) const
{
	return getFieldRO<FTexture0Type>(getFTexture0())->getValue( value );
}



void PostProcessing::setTexture0( const Texture0ValueType& value )
{
	getFieldRW<FTexture0Type>(getFTexture0())->setValue( value );
}



void PostProcessing::eraseTexture0()
{
	getFieldRW<FTexture0Type>(getFTexture0())->eraseValue();
}


const bool PostProcessing::hasTexture0() const
{
	return getFieldRO<FTexture0Type>(getFTexture0())->hasValue();
}



// Input0Sampling

const PostProcessing::Input0SamplingValueType PostProcessing::getInput0Sampling() const
{
	return getFieldRO<FInput0SamplingType>(getFInput0Sampling())->getValue();
}



void PostProcessing::setInput0Sampling( const Input0SamplingValueType value )
{
	getFieldRW<FInput0SamplingType>(getFInput0Sampling())->setValue( value );
}



// CustomFilterApply

const PostProcessing::CustomFilterApplyValueType PostProcessing::DEFAULT_CUSTOMFILTERAPPLY = std::string();



const PostProcessing::CustomFilterApplyValueType PostProcessing::getCustomFilterApply() const
{
	return getFieldRO<FCustomFilterApplyType>(getFCustomFilterApply())->getValue();
}



void PostProcessing::setCustomFilterApply( const CustomFilterApplyValueType value )
{
	getFieldRW<FCustomFilterApplyType>(getFCustomFilterApply())->setValue( value );
}



// Output

const PostProcessing::OutputValueType PostProcessing::getOutput() const
{
	return getFieldRO<FOutputType>(getFOutput())->getValue();
}



void PostProcessing::setOutput( const OutputValueType value )
{
	getFieldRW<FOutputType>(getFOutput())->setValue( value );
}



// Param1f0

const PostProcessing::Param1f0ValueType PostProcessing::DEFAULT_PARAM1F0 = (0.0);



const bool PostProcessing::getParam1f0( Param1f0ValueType& value ) const
{
	return getFieldRO<FParam1f0Type>(getFParam1f0())->getValue( value );
}



void PostProcessing::setParam1f0( const Param1f0ValueType& value )
{
	getFieldRW<FParam1f0Type>(getFParam1f0())->setValue( value );
}



void PostProcessing::eraseParam1f0()
{
	getFieldRW<FParam1f0Type>(getFParam1f0())->eraseValue();
}


const bool PostProcessing::hasParam1f0() const
{
	return getFieldRO<FParam1f0Type>(getFParam1f0())->hasValue();
}



// Param1f1

const PostProcessing::Param1f1ValueType PostProcessing::DEFAULT_PARAM1F1 = (0.0);



const bool PostProcessing::getParam1f1( Param1f1ValueType& value ) const
{
	return getFieldRO<FParam1f1Type>(getFParam1f1())->getValue( value );
}



void PostProcessing::setParam1f1( const Param1f1ValueType& value )
{
	getFieldRW<FParam1f1Type>(getFParam1f1())->setValue( value );
}



void PostProcessing::eraseParam1f1()
{
	getFieldRW<FParam1f1Type>(getFParam1f1())->eraseValue();
}


const bool PostProcessing::hasParam1f1() const
{
	return getFieldRO<FParam1f1Type>(getFParam1f1())->hasValue();
}



// Param4f0

const PostProcessing::Param4f0ValueType PostProcessing::DEFAULT_PARAM4F0 = vgm::Vec4f(0.0, 0.0, 0.0, 0.0);



const bool PostProcessing::getParam4f0( Param4f0ValueType& value ) const
{
	return getFieldRO<FParam4f0Type>(getFParam4f0())->getValue( value );
}



void PostProcessing::setParam4f0( const Param4f0ValueType& value )
{
	getFieldRW<FParam4f0Type>(getFParam4f0())->setValue( value );
}



void PostProcessing::eraseParam4f0()
{
	getFieldRW<FParam4f0Type>(getFParam4f0())->eraseValue();
}


const bool PostProcessing::hasParam4f0() const
{
	return getFieldRO<FParam4f0Type>(getFParam4f0())->hasValue();
}



// Param4x4f0

const PostProcessing::Param4x4f0ValueType PostProcessing::DEFAULT_PARAM4X4F0 = vgm::MatrixR(vgm::MatrixR::getIdentity());



const bool PostProcessing::getParam4x4f0( Param4x4f0ValueType& value ) const
{
	return getFieldRO<FParam4x4f0Type>(getFParam4x4f0())->getValue( value );
}



void PostProcessing::setParam4x4f0( const Param4x4f0ValueType& value )
{
	getFieldRW<FParam4x4f0Type>(getFParam4x4f0())->setValue( value );
}



void PostProcessing::eraseParam4x4f0()
{
	getFieldRW<FParam4x4f0Type>(getFParam4x4f0())->eraseValue();
}


const bool PostProcessing::hasParam4x4f0() const
{
	return getFieldRO<FParam4x4f0Type>(getFParam4x4f0())->hasValue();
}



// Field name accessor(s)
const std::string PostProcessing::getFInput2( void )
{
	return "f_input2";
}



const std::string PostProcessing::getFInput0( void )
{
	return "f_input0";
}



const std::string PostProcessing::getFInput1( void )
{
	return "f_input1";
}



const std::string PostProcessing::getFCustomFilterDefinition( void )
{
	return "f_customFilterDefinition";
}



const std::string PostProcessing::getFFilter( void )
{
	return "f_filter";
}



const std::string PostProcessing::getFParam4f1( void )
{
	return "f_param4f1";
}



const std::string PostProcessing::getFTexture0( void )
{
	return "f_texture0";
}



const std::string PostProcessing::getFInput0Sampling( void )
{
	return "f_input0Sampling";
}



const std::string PostProcessing::getFCustomFilterApply( void )
{
	return "f_customFilterApply";
}



const std::string PostProcessing::getFOutput( void )
{
	return "f_output";
}



const std::string PostProcessing::getFParam1f0( void )
{
	return "f_param1f0";
}



const std::string PostProcessing::getFParam1f1( void )
{
	return "f_param1f1";
}



const std::string PostProcessing::getFParam4f0( void )
{
	return "f_param4f0";
}



const std::string PostProcessing::getFParam4x4f0( void )
{
	return "f_param4x4f0";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , PostProcessing );



const vgd::basic::RegisterNode<PostProcessing> PostProcessing::m_registrationInstance;



} // namespace node

} // namespace vgd

