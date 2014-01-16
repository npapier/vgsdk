// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/ClearFrameBuffer.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< ClearFrameBuffer > ClearFrameBuffer::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< ClearFrameBuffer > node( new ClearFrameBuffer(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< ClearFrameBuffer > ClearFrameBuffer::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< ClearFrameBuffer > node = ClearFrameBuffer::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< ClearFrameBuffer > ClearFrameBuffer::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< ClearFrameBuffer > node = ClearFrameBuffer::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



ClearFrameBuffer::ClearFrameBuffer( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FClearColorType(getFClearColor()) );

	// Sets link(s)

	link( getDFNode() );
}



void ClearFrameBuffer::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
}



void ClearFrameBuffer::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	setClearColor( vgm::Vec4f(0.f, 0.f, 0.f, 0.f) );
}



// ClearColor

const ClearFrameBuffer::ClearColorValueType ClearFrameBuffer::DEFAULT_CLEARCOLOR = vgm::Vec4f(0.f, 0.f, 0.f, 0.f);



const bool ClearFrameBuffer::getClearColor( ClearColorValueType& value ) const
{
	return getFieldRO<FClearColorType>(getFClearColor())->getValue( value );
}



void ClearFrameBuffer::setClearColor( const ClearColorValueType& value )
{
	getFieldRW<FClearColorType>(getFClearColor())->setValue( value );
}



void ClearFrameBuffer::eraseClearColor()
{
	getFieldRW<FClearColorType>(getFClearColor())->eraseValue();
}


const bool ClearFrameBuffer::hasClearColor() const
{
	return getFieldRO<FClearColorType>(getFClearColor())->hasValue();
}



// Field name accessor(s)
const std::string ClearFrameBuffer::getFClearColor( void )
{
	return "f_clearColor";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , ClearFrameBuffer );



const vgd::basic::RegisterNode<ClearFrameBuffer> ClearFrameBuffer::m_registrationInstance;



} // namespace node

} // namespace vgd

