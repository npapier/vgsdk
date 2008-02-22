// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/DrawStyle.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( DrawStyle );



DrawStyle::DrawStyle( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Add field
	addField( new FShapeType(getFShape()) );
	addField( new FNormalLengthType(getFNormalLength()) );
	addField( new FShowOrientationType(getFShowOrientation()) );	
	addField( new FBoundingBoxType(getFBoundingBox()) );
	
	// Link(s)
	link( getDFNode() );
}



void DrawStyle::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
}



void DrawStyle::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	
	setShape(				DEFAULT_SHAPE );
	setNormalLength(		0.f );
	setShowOrientation( 	false );
	setBoundingBox(		DEFAULT_BOUNDING_BOX );
}



// SHAPE
bool DrawStyle::getShape( ShapeValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< ShapeParameterType, ShapeValueType >( this, getFShape(), SHAPE, value )
		);
}



void DrawStyle::setShape( ShapeValueType value )
{
	vgd::field::setParameterValue< ShapeParameterType, ShapeValueType >( this, getFShape(), SHAPE, value );
}



void DrawStyle::eraseShape()
{
	vgd::field::eraseParameterValue< ShapeParameterType, ShapeValueType >( this, getFShape(), SHAPE );
}



// NORMAL_LENGTH
bool DrawStyle::getNormalLength( NormalLengthValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< NormalLengthParameterType, NormalLengthValueType >( this, getFNormalLength(), NORMAL_LENGTH, value )
		);
}



void DrawStyle::setNormalLength( NormalLengthValueType value )
{
	vgd::field::setParameterValue< NormalLengthParameterType, NormalLengthValueType >( this, getFNormalLength(), NORMAL_LENGTH, value );
}



void DrawStyle::eraseNormalLength()
{
	vgd::field::eraseParameterValue< NormalLengthParameterType, NormalLengthValueType >( this, getFNormalLength(), NORMAL_LENGTH );
}



// SHOW_ORIENTATION
bool DrawStyle::getShowOrientation( ShowOrientationValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< ShowOrientationParameterType, ShowOrientationValueType >( this, getFShowOrientation(), SHOW_ORIENTATION, value )
		);
}



void DrawStyle::setShowOrientation( ShowOrientationValueType value )
{
	vgd::field::setParameterValue< ShowOrientationParameterType, ShowOrientationValueType >( this, getFShowOrientation(), SHOW_ORIENTATION, value );
}



void DrawStyle::eraseShowOrientation()
{
	vgd::field::eraseParameterValue< ShowOrientationParameterType, ShowOrientationValueType >( this, getFShowOrientation(), SHOW_ORIENTATION );
}



// BOUNDING_BOX
bool DrawStyle::getBoundingBox( BoundingBoxValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< BoundingBoxParameterType, BoundingBoxValueType >( this, getFBoundingBox(), BOUNDING_BOX, value )
		);
}



void DrawStyle::setBoundingBox( BoundingBoxValueType value )
{
	vgd::field::setParameterValue< BoundingBoxParameterType, BoundingBoxValueType >( this, getFBoundingBox(), BOUNDING_BOX, value );
}



void DrawStyle::eraseBoundingBox()
{
	vgd::field::eraseParameterValue< BoundingBoxParameterType, BoundingBoxValueType >( this, getFBoundingBox(), BOUNDING_BOX );
}



const std::string DrawStyle::getFShape( void )
{
	return ( "f_shape" );
}



const std::string DrawStyle::getFNormalLength( void )
{
	return ( "f_normalLength" );
}



const std::string DrawStyle::getFShowOrientation( void )
{
	return ( "f_showOrientation" );
}



const std::string DrawStyle::getFBoundingBox( void )
{
	return ( "f_boundingBox" );
}


} // namespace node

} // namespace vgd
