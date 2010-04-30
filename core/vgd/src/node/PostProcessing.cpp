// VGSDK - Copyright (C) 2010, Nicolas Papier.
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
	addField( new FFilterType(getFFilter()) );
	addField( new FInput0Type(getFInput0()) );
	addField( new FInput1Type(getFInput1()) );

	// Sets link(s)
	link( getDFNode() );
}



void PostProcessing::setToDefaults( void )
{
	MultiAttribute::setToDefaults();
	setFilter( NO_FILTER );
	setInput0( PREVIOUS_COLOR );
	setInput1( INPUT1_NONE );
}



void PostProcessing::setOptionalsToDefaults()
{
	MultiAttribute::setOptionalsToDefaults();
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



// Field name accessor(s)
const std::string PostProcessing::getFFilter( void )
{
	return "f_filter";
}



const std::string PostProcessing::getFInput0( void )
{
	return "f_input0";
}



const std::string PostProcessing::getFInput1( void )
{
	return "f_input1";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , PostProcessing );



const vgd::basic::RegisterNode<PostProcessing> PostProcessing::m_registrationInstance;



} // namespace node

} // namespace vgd

