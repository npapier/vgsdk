// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/SingleTransformation.hpp"



namespace vgd
{

namespace node
{



//META_NODE_CPP( SingleTransformation ); abstract class.



SingleTransformation::SingleTransformation( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Add field
	addField( new FComposeTransformationType(getFComposeTransformation()) );

	// Link(s)
	link( getDFNode() );
}



void SingleTransformation::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	
	setComposeTransformation( true );
}



void SingleTransformation::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



const bool& SingleTransformation::getComposeTransformation( void ) const
{
	return ( getFieldRO<FComposeTransformationType>(getFComposeTransformation())->getValue() );
}



void SingleTransformation::setComposeTransformation( const bool bComposeTransformation )
{
	getFieldRW<FComposeTransformationType>(getFComposeTransformation())->setValue( bComposeTransformation );
}



const std::string SingleTransformation::getFComposeTransformation( void )
{
	return ( "f_composeTransformation" );
}



} // namespace node

} // namespace vgd
