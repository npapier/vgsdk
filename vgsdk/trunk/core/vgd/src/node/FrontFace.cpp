// VGSDK - Copyright (C) 2004, Nicolas Papier.
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
	// Add field
	addField( new FOrientationType(getFOrientation()) );

	// Link(s)
	link( getDFNode() );
}



void FrontFace::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
}



void FrontFace::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();

	setOrientation( CCW );
}



// ORIENTATION
bool FrontFace::getOrientation( OrientationValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< OrientationParameterType, OrientationValueType >( this, getFOrientation(), ORIENTATION, value )
		);
}



void FrontFace::setOrientation( OrientationValueType value )
{
	vgd::field::setParameterValue< OrientationParameterType, OrientationValueType >( this, getFOrientation(), ORIENTATION, value );
}



void FrontFace::eraseOrientation()
{
	vgd::field::eraseParameterValue< OrientationParameterType, OrientationValueType >( this, getFOrientation(), ORIENTATION );
}



const std::string FrontFace::getFOrientation( void )
{
	return ( "f_orientation" );
}



} // namespace node

} // namespace vgd
