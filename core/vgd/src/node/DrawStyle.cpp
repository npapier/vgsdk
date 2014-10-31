// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/DrawStyle.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< DrawStyle > DrawStyle::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< DrawStyle > node( new DrawStyle(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< DrawStyle > DrawStyle::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< DrawStyle > node = DrawStyle::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< DrawStyle > DrawStyle::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< DrawStyle > node = DrawStyle::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



DrawStyle::DrawStyle( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FShapeType(getFShape()) );
	addField( new FNormalLengthType(getFNormalLength()) );
	addField( new FTangentLengthType(getFTangentLength()) );
	addField( new FShowOrientationType(getFShowOrientation()) );
	addField( new FBoundingBoxType(getFBoundingBox()) );

	// Sets link(s)

	link( getDFNode() );
}



void DrawStyle::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
}



void DrawStyle::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	setShape( (SMOOTH) );
	setNormalLength( (0.f) );
	setTangentLength( (0.f) );
	setShowOrientation( (false) );
	setBoundingBox( (NO_BOUNDING_BOX) );
}



// Shape

const bool DrawStyle::getShape( ShapeValueType& value ) const
{
	return getFieldRO<FShapeType>(getFShape())->getValue( value );
}



void DrawStyle::setShape( const ShapeValueType& value )
{
	getFieldRW<FShapeType>(getFShape())->setValue( value );
}



void DrawStyle::eraseShape()
{
	getFieldRW<FShapeType>(getFShape())->eraseValue();
}


const bool DrawStyle::hasShape() const
{
	return getFieldRO<FShapeType>(getFShape())->hasValue();
}



// NormalLength

const DrawStyle::NormalLengthValueType DrawStyle::DEFAULT_NORMALLENGTH = (0.f);



const bool DrawStyle::getNormalLength( NormalLengthValueType& value ) const
{
	return getFieldRO<FNormalLengthType>(getFNormalLength())->getValue( value );
}



void DrawStyle::setNormalLength( const NormalLengthValueType& value )
{
	getFieldRW<FNormalLengthType>(getFNormalLength())->setValue( value );
}



void DrawStyle::eraseNormalLength()
{
	getFieldRW<FNormalLengthType>(getFNormalLength())->eraseValue();
}


const bool DrawStyle::hasNormalLength() const
{
	return getFieldRO<FNormalLengthType>(getFNormalLength())->hasValue();
}



// TangentLength

const DrawStyle::TangentLengthValueType DrawStyle::DEFAULT_TANGENTLENGTH = (0.f);



const bool DrawStyle::getTangentLength( TangentLengthValueType& value ) const
{
	return getFieldRO<FTangentLengthType>(getFTangentLength())->getValue( value );
}



void DrawStyle::setTangentLength( const TangentLengthValueType& value )
{
	getFieldRW<FTangentLengthType>(getFTangentLength())->setValue( value );
}



void DrawStyle::eraseTangentLength()
{
	getFieldRW<FTangentLengthType>(getFTangentLength())->eraseValue();
}


const bool DrawStyle::hasTangentLength() const
{
	return getFieldRO<FTangentLengthType>(getFTangentLength())->hasValue();
}



// ShowOrientation

const DrawStyle::ShowOrientationValueType DrawStyle::DEFAULT_SHOWORIENTATION = (false);



const bool DrawStyle::getShowOrientation( ShowOrientationValueType& value ) const
{
	return getFieldRO<FShowOrientationType>(getFShowOrientation())->getValue( value );
}



void DrawStyle::setShowOrientation( const ShowOrientationValueType& value )
{
	getFieldRW<FShowOrientationType>(getFShowOrientation())->setValue( value );
}



void DrawStyle::eraseShowOrientation()
{
	getFieldRW<FShowOrientationType>(getFShowOrientation())->eraseValue();
}


const bool DrawStyle::hasShowOrientation() const
{
	return getFieldRO<FShowOrientationType>(getFShowOrientation())->hasValue();
}



// BoundingBox

const bool DrawStyle::getBoundingBox( BoundingBoxValueType& value ) const
{
	return getFieldRO<FBoundingBoxType>(getFBoundingBox())->getValue( value );
}



void DrawStyle::setBoundingBox( const BoundingBoxValueType& value )
{
	getFieldRW<FBoundingBoxType>(getFBoundingBox())->setValue( value );
}



void DrawStyle::eraseBoundingBox()
{
	getFieldRW<FBoundingBoxType>(getFBoundingBox())->eraseValue();
}


const bool DrawStyle::hasBoundingBox() const
{
	return getFieldRO<FBoundingBoxType>(getFBoundingBox())->hasValue();
}



// Field name accessor(s)
const std::string DrawStyle::getFShape( void )
{
	return "f_shape";
}



const std::string DrawStyle::getFNormalLength( void )
{
	return "f_normalLength";
}



const std::string DrawStyle::getFTangentLength( void )
{
	return "f_tangentLength";
}



const std::string DrawStyle::getFShowOrientation( void )
{
	return "f_showOrientation";
}



const std::string DrawStyle::getFBoundingBox( void )
{
	return "f_boundingBox";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( DrawStyle );



const vgd::basic::RegisterNode<DrawStyle> DrawStyle::m_registrationInstance;



} // namespace node

} // namespace vgd

