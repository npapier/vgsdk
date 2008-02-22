// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/MultiTransformation.hpp"



namespace vgd
{

namespace node
{



//META_NODE_CPP( MultiTransformation ); abstract class.



MultiTransformation::MultiTransformation( const std::string nodeName ) :
	vgd::node::MultiAttribute( nodeName )
{
	// Add field
	addField( new FComposeTransformationType(getFComposeTransformation()) );

	// Link(s)
	link( getDFNode() );
}



void MultiTransformation::setToDefaults( void )
{
	MultiAttribute::setToDefaults();
	
	setComposeTransformation( true );
}



void MultiTransformation::setOptionalsToDefaults()
{
	MultiAttribute::setOptionalsToDefaults();
}



const bool& MultiTransformation::getComposeTransformation( void ) const
{
	return ( getFieldRO<FComposeTransformationType>(getFComposeTransformation())->getValue() );
}



void MultiTransformation::setComposeTransformation( const bool bComposeTransformation )
{
	getFieldRW<FComposeTransformationType>(getFComposeTransformation())->setValue( bComposeTransformation );
}



const std::string MultiTransformation::getFComposeTransformation( void )
{
	return ( "f_composeTransformation" );
}



} // namespace node

} // namespace vgd
