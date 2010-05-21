// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/OutputBuffers.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< OutputBuffers > OutputBuffers::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< OutputBuffers > node( new OutputBuffers(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< OutputBuffers > OutputBuffers::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< OutputBuffers > node = OutputBuffers::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



OutputBuffers::OutputBuffers( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FOutputType(getFOutput()) );

	// Sets link(s)
	link( getDFNode() );
}



void OutputBuffers::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setOutput( BUFFERS0 );
}



void OutputBuffers::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



// Output
const OutputBuffers::OutputValueType OutputBuffers::getOutput() const
{
	return getFieldRO<FOutputType>(getFOutput())->getValue();
}



void OutputBuffers::setOutput( const OutputValueType value )
{
	getFieldRW<FOutputType>(getFOutput())->setValue( value );
}



// Field name accessor(s)
const std::string OutputBuffers::getFOutput( void )
{
	return "f_output";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , OutputBuffers );



const vgd::basic::RegisterNode<OutputBuffers> OutputBuffers::m_registrationInstance;



} // namespace node

} // namespace vgd

