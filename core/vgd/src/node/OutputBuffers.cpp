// VGSDK - Copyright (C) 2011, Nicolas Papier.
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



vgd::Shp< OutputBuffers > OutputBuffers::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< OutputBuffers > node = OutputBuffers::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

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
	addField( new FCurrentType(getFCurrent()) );

	// Sets link(s)

	link( getDFNode() );
}



void OutputBuffers::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
}



void OutputBuffers::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



// Current
vgd::field::EditorRO< OutputBuffers::FCurrentType > OutputBuffers::getCurrentRO() const
{
	return getFieldRO<FCurrentType>( getFCurrent() );
}



vgd::field::EditorRW< OutputBuffers::FCurrentType > OutputBuffers::getCurrentRW()
{
	return getFieldRW<FCurrentType>( getFCurrent() );
}



// Field name accessor(s)
const std::string OutputBuffers::getFCurrent( void )
{
	return "f_current";
}



void OutputBuffers::setCurrent( const int which )
{
	using vgd::field::EditorRW;

	EditorRW< FCurrentType > current = getCurrentRW();
	current->clear();
	if ( which >= 0 )
	{
		current->push_back( which );
	}
	// else nothing to do
}
IMPLEMENT_INDEXABLE_CLASS_CPP( , OutputBuffers );



const vgd::basic::RegisterNode<OutputBuffers> OutputBuffers::m_registrationInstance;



} // namespace node

} // namespace vgd

