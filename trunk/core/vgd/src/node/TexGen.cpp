// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/TexGen.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



TexGen::TexGen( const std::string nodeName ) :
	vgd::node::MultiAttribute( nodeName )
{
	// Adds field(s)
	addField( new FOnType(getFOn()) );

	// Sets link(s)
	link( getDFNode() );
}



void TexGen::setToDefaults( void )
{
	MultiAttribute::setToDefaults();
	setOn( true );
}



void TexGen::setOptionalsToDefaults()
{
	MultiAttribute::setOptionalsToDefaults();
}



// On
const TexGen::OnValueType TexGen::getOn() const
{
	return getFieldRO<FOnType>(getFOn())->getValue();
}



void TexGen::setOn( const OnValueType value )
{
	getFieldRW<FOnType>(getFOn())->setValue( value );
}



// Field name accessor(s)
const std::string TexGen::getFOn( void )
{
	return "f_on";
}



} // namespace node

} // namespace vgd

