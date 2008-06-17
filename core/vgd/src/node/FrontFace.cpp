// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/FrontFace.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( FrontFace );



FrontFace::FrontFace( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FOrientationType(getFOrientation()) );

	// Sets link(s)
	link( getDFNode() );
}



void FrontFace::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setOrientation( CCW );
}



void FrontFace::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



const FrontFace::OrientationValueType FrontFace::getOrientation() const
{
	return getFieldRO<FOrientationType>(getFOrientation())->getValue();
}



void FrontFace::setOrientation( const OrientationValueType value )
{
	getFieldRW<FOrientationType>(getFOrientation())->setValue( value );
}



const std::string FrontFace::getFOrientation( void )
{
	return "f_orientation";
}



} // namespace node

} // namespace vgd

