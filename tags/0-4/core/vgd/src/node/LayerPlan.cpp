// VGSDK - Copyright (C) 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/LayerPlan.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( LayerPlan );



LayerPlan::LayerPlan( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Add fields
	addField( new FPositionType(getFPosition()) );
	addField( new FSizeType(getFSize()) );
	addField( new FIImageType(getFIImage()) );
	addField( new FAlphaScaleType(getFAlphaScale()) );

	// Add dirty flags
	addDirtyFlag(getDFIImage());

	// Link(s)
	link( getFIImage(), getDFIImage() );
	link( getDFNode() );
}



void LayerPlan::setToDefaults( void )
{
	SingleAttribute::setToDefaults();

	setPosition( vgm::Vec2f(0.f, 0.f) );
	setSize( vgm::Vec2f(1.f, 1.f) );
	setAlphaScale( 1.f );
}



void LayerPlan::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



const LayerPlan::PositionValueType LayerPlan::getPosition() const
{
	return ( getFieldRO<FPositionType>(getFPosition())->getValue() );
}



void LayerPlan::setPosition( const PositionValueType value )
{
	getFieldRW<FPositionType>(getFPosition())->setValue( value );
}



const LayerPlan::SizeValueType LayerPlan::getSize() const
{
	return ( getFieldRO<FSizeType>(getFSize())->getValue() );
}



void LayerPlan::setSize( const SizeValueType value )
{
	getFieldRW<FSizeType>(getFSize())->setValue( value );
}



const LayerPlan::IImageValueType LayerPlan::getIImage() const
{
	return ( getFieldRO<FIImageType>(getFIImage())->getValue() );
}



void LayerPlan::setIImage( const IImageValueType value )
{
	getFieldRW<FIImageType>(getFIImage())->setValue( value );
}



const LayerPlan::AlphaScaleValueType LayerPlan::getAlphaScale() const
{
	return ( getFieldRO<FAlphaScaleType>(getFAlphaScale())->getValue() );
}



void LayerPlan::setAlphaScale( const AlphaScaleValueType value )
{
	getFieldRW<FAlphaScaleType>(getFAlphaScale())->setValue( value );
}



const std::string LayerPlan::getFPosition()
{
	return "f_position";
}



const std::string LayerPlan::getFSize()
{
	return "f_size";
}



const std::string LayerPlan::getFIImage()
{
	return "f_iimage";
}



const std::string LayerPlan::getFAlphaScale()
{
	return "f_alphaScale";
}



const std::string LayerPlan::getDFIImage()
{
	return "df_iimage";
}



} // namespace node

} // namespace vgd
