// VGSDK - Copyright (C) 2007, Nicolas Papier.
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
	vgd::node::MultiAttribute( nodeName )
{
	// Add fields
	addField( new FTypeType(getFType()) );
	addField( new FPositionType(getFPosition()) );
	addField( new FSizeType(getFSize()) );
	addField( new FIImageType(getFIImage()) );

	// Add dirty flags
	addDirtyFlag(getDFIImage());

	// Link(s)
	link( getFIImage(), getDFIImage() );
	link( getDFNode() );
}



void LayerPlan::setToDefaults( void )
{
	MultiAttribute::setToDefaults();
	
	setType( OVERLAY );
	setPosition( vgm::Vec2f(0.f, 0.f) );
	setSize( vgm::Vec2f(1.f, 1.f) );
}



void LayerPlan::setOptionalsToDefaults()
{
	MultiAttribute::setOptionalsToDefaults();
}



const LayerPlan::TypeValueType LayerPlan::getType() const
{
	return ( getFieldRO<FTypeType>(getFType())->getValue() );
}



void LayerPlan::setType( const TypeValueType value )
{
	getFieldRW<FTypeType>(getFType())->setValue( value );
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



const std::string LayerPlan::getFType()
{
	return "f_type";
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



const std::string LayerPlan::getDFIImage()
{
	return "df_iimage";
}



} // namespace node

} // namespace vgd
