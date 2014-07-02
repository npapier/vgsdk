// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/FrameBuffer.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< FrameBuffer > FrameBuffer::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< FrameBuffer > node( new FrameBuffer(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< FrameBuffer > FrameBuffer::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< FrameBuffer > node = FrameBuffer::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< FrameBuffer > FrameBuffer::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< FrameBuffer > node = FrameBuffer::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



FrameBuffer::FrameBuffer( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
}



void FrameBuffer::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
}



void FrameBuffer::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



// Field name accessor(s)
IMPLEMENT_INDEXABLE_CLASS_CPP( FrameBuffer );
//IMPLEMENT_INDEXABLE_CLASS_CPP( , FrameBuffer );



const vgd::basic::RegisterNode<FrameBuffer> FrameBuffer::m_registrationInstance;



} // namespace node

} // namespace vgd

