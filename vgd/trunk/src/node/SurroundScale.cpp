// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/SurroundScale.hpp"

#include "vgd/field/TAccessors.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( SurroundScale );



SurroundScale::SurroundScale( const std::string nodeName ) :
	vgd::node::GeometricalTransformation( nodeName )
{
	// Add field
	addField( new FSurroundType(getFSurround()) );
	
	// Link(s)
	link( getDFNode() );
}



void SurroundScale::setToDefaults()
{
	GeometricalTransformation::setToDefaults();
}



void SurroundScale::setOptionalsToDefaults()
{
	GeometricalTransformation::setOptionalsToDefaults();
}



// SURROUND
const SurroundScale::SurroundValueType SurroundScale::getSurround() const
{
	return ( getFieldRO<FSurroundType>(getFSurround())->getValue() );
}



void SurroundScale::setSurround( const SurroundValueType value )
{
	getFieldRW<FSurroundType>(getFSurround())->setValue( value );
}



//
const std::string SurroundScale::getFSurround()
{
	return ( "f_surround" );
}



} // namespace node

} // namespace vgd
