// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/TessellationProperties.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< TessellationProperties > TessellationProperties::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< TessellationProperties > node( new TessellationProperties(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< TessellationProperties > TessellationProperties::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< TessellationProperties > node = TessellationProperties::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< TessellationProperties > TessellationProperties::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< TessellationProperties > node = TessellationProperties::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



TessellationProperties::TessellationProperties( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FTessellationType(getFTessellation()) );
	addField( new FPhongBiasType(getFPhongBias()) );
	addField( new FRangeType(getFRange()) );
	addField( new FPixelsPerEdgeType(getFPixelsPerEdge()) );

	// Sets link(s)

	link( getDFNode() );
}



void TessellationProperties::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
}



void TessellationProperties::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	setTessellation( (DISABLED) );
	setPhongBias( (0.55f) );
	setRange( vgm::Vec2f(1.0f, 5.0f) );
	setPixelsPerEdge( (20.f) );
}



// Tessellation

const bool TessellationProperties::getTessellation( TessellationValueType& value ) const
{
	return getFieldRO<FTessellationType>(getFTessellation())->getValue( value );
}



void TessellationProperties::setTessellation( const TessellationValueType& value )
{
	getFieldRW<FTessellationType>(getFTessellation())->setValue( value );
}



void TessellationProperties::eraseTessellation()
{
	getFieldRW<FTessellationType>(getFTessellation())->eraseValue();
}


const bool TessellationProperties::hasTessellation() const
{
	return getFieldRO<FTessellationType>(getFTessellation())->hasValue();
}



// PhongBias

const TessellationProperties::PhongBiasValueType TessellationProperties::DEFAULT_PHONGBIAS = (0.55f);



const bool TessellationProperties::getPhongBias( PhongBiasValueType& value ) const
{
	return getFieldRO<FPhongBiasType>(getFPhongBias())->getValue( value );
}



void TessellationProperties::setPhongBias( const PhongBiasValueType& value )
{
	getFieldRW<FPhongBiasType>(getFPhongBias())->setValue( value );
}



void TessellationProperties::erasePhongBias()
{
	getFieldRW<FPhongBiasType>(getFPhongBias())->eraseValue();
}


const bool TessellationProperties::hasPhongBias() const
{
	return getFieldRO<FPhongBiasType>(getFPhongBias())->hasValue();
}



// Range

const TessellationProperties::RangeValueType TessellationProperties::DEFAULT_RANGE = vgm::Vec2f(1.0f, 5.0f);



const bool TessellationProperties::getRange( RangeValueType& value ) const
{
	return getFieldRO<FRangeType>(getFRange())->getValue( value );
}



void TessellationProperties::setRange( const RangeValueType& value )
{
	getFieldRW<FRangeType>(getFRange())->setValue( value );
}



void TessellationProperties::eraseRange()
{
	getFieldRW<FRangeType>(getFRange())->eraseValue();
}


const bool TessellationProperties::hasRange() const
{
	return getFieldRO<FRangeType>(getFRange())->hasValue();
}



// PixelsPerEdge

const TessellationProperties::PixelsPerEdgeValueType TessellationProperties::DEFAULT_PIXELSPEREDGE = (20.f);



const bool TessellationProperties::getPixelsPerEdge( PixelsPerEdgeValueType& value ) const
{
	return getFieldRO<FPixelsPerEdgeType>(getFPixelsPerEdge())->getValue( value );
}



void TessellationProperties::setPixelsPerEdge( const PixelsPerEdgeValueType& value )
{
	getFieldRW<FPixelsPerEdgeType>(getFPixelsPerEdge())->setValue( value );
}



void TessellationProperties::erasePixelsPerEdge()
{
	getFieldRW<FPixelsPerEdgeType>(getFPixelsPerEdge())->eraseValue();
}


const bool TessellationProperties::hasPixelsPerEdge() const
{
	return getFieldRO<FPixelsPerEdgeType>(getFPixelsPerEdge())->hasValue();
}



// Field name accessor(s)
const std::string TessellationProperties::getFTessellation( void )
{
	return "f_tessellation";
}



const std::string TessellationProperties::getFPhongBias( void )
{
	return "f_phongBias";
}



const std::string TessellationProperties::getFRange( void )
{
	return "f_range";
}



const std::string TessellationProperties::getFPixelsPerEdge( void )
{
	return "f_pixelsPerEdge";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( TessellationProperties );
//IMPLEMENT_INDEXABLE_CLASS_CPP( , TessellationProperties );



const vgd::basic::RegisterNode<TessellationProperties> TessellationProperties::m_registrationInstance;



} // namespace node

} // namespace vgd

