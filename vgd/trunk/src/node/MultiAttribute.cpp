// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/MultiAttribute.hpp"



namespace vgd
{

namespace node
{



// META_NODE_CPP( MultiAttribute ); abstract class.



MultiAttribute::MultiAttribute( const std::string nodeName ) :
	vgd::node::Attribute( nodeName )
{
	// Add field.
	addField( new FMultiAttributeIndexType( getFMultiAttributeIndex() )	);
	
	// Links
	link( getDFNode() );
}



void MultiAttribute::setToDefaults( void )
{
	Attribute::setToDefaults();

	setMultiAttributeIndex( 0 );
}



void MultiAttribute::setOptionalsToDefaults()
{
	Attribute::setOptionalsToDefaults();
}



// MULTIATTRIBUTEINDEX
int8 MultiAttribute::getMultiAttributeIndex() const
{
	return ( getFieldRO<FMultiAttributeIndexType>(getFMultiAttributeIndex())->getValue() );
}



void MultiAttribute::setMultiAttributeIndex( const int8 index )
{
	getFieldRW<FMultiAttributeIndexType>(getFMultiAttributeIndex())->setValue( index );
}



const std::string MultiAttribute::getFMultiAttributeIndex( void )
{
	return ( "f_multiAttributeIndex" );
}



} // namespace node

} // namespace vgd
