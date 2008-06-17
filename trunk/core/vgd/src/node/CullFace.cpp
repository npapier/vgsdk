// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/CullFace.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( CullFace );



CullFace::CullFace( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FModeType(getFMode()) );

	// Sets link(s)
	link( getDFNode() );
}



void CullFace::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setMode( DISABLED );
}



void CullFace::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



const CullFace::ModeValueType CullFace::getMode() const
{
	return getFieldRO<FModeType>(getFMode())->getValue();
}



void CullFace::setMode( const ModeValueType value )
{
	getFieldRW<FModeType>(getFMode())->setValue( value );
}



const std::string CullFace::getFMode( void )
{
	return "f_mode";
}



} // namespace node

} // namespace vgd

