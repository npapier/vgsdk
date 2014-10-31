// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/LayerPlan.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< LayerPlan > LayerPlan::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< LayerPlan > node( new LayerPlan(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< LayerPlan > LayerPlan::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< LayerPlan > node = LayerPlan::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< LayerPlan > LayerPlan::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< LayerPlan > node = LayerPlan::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



LayerPlan::LayerPlan( const std::string nodeName ) :
	vgd::node::MultiAttribute( nodeName )
{
	// Adds field(s)
	addField( new FPositionType(getFPosition()) );
	addField( new FSizeType(getFSize()) );
	addField( new FImageType(getFImage()) );
	addField( new FAlphaScaleType(getFAlphaScale()) );

	// Adds dirty flag(s)
	addDirtyFlag(getDFImage());

	// Sets link(s)
	link( getFImage(), getDFImage() );
	link( getFAlphaScale(), getDFImage() );

	link( getDFNode() );
}



void LayerPlan::setToDefaults( void )
{
	MultiAttribute::setToDefaults();
	setPosition( vgm::Vec2f(0.f, 0.f) );
	setSize( vgm::Vec2f(1.f, 1.f) );
	setImage( vgd::basic::IImageShp() );
	setAlphaScale( (1.f) );
}



void LayerPlan::setOptionalsToDefaults()
{
	MultiAttribute::setOptionalsToDefaults();
}



// Position

const LayerPlan::PositionValueType LayerPlan::DEFAULT_POSITION = vgm::Vec2f(0.f, 0.f);



const LayerPlan::PositionValueType LayerPlan::getPosition() const
{
	return getFieldRO<FPositionType>(getFPosition())->getValue();
}



void LayerPlan::setPosition( const PositionValueType value )
{
	getFieldRW<FPositionType>(getFPosition())->setValue( value );
}



// Size

const LayerPlan::SizeValueType LayerPlan::DEFAULT_SIZE = vgm::Vec2f(1.f, 1.f);



const LayerPlan::SizeValueType LayerPlan::getSize() const
{
	return getFieldRO<FSizeType>(getFSize())->getValue();
}



void LayerPlan::setSize( const SizeValueType value )
{
	getFieldRW<FSizeType>(getFSize())->setValue( value );
}



// Image

const LayerPlan::ImageValueType LayerPlan::DEFAULT_IMAGE = vgd::basic::IImageShp();



const LayerPlan::ImageValueType LayerPlan::getImage() const
{
	return getFieldRO<FImageType>(getFImage())->getValue();
}



void LayerPlan::setImage( const ImageValueType value )
{
	getFieldRW<FImageType>(getFImage())->setValue( value );
}



// AlphaScale

const LayerPlan::AlphaScaleValueType LayerPlan::DEFAULT_ALPHASCALE = (1.f);



const LayerPlan::AlphaScaleValueType LayerPlan::getAlphaScale() const
{
	return getFieldRO<FAlphaScaleType>(getFAlphaScale())->getValue();
}



void LayerPlan::setAlphaScale( const AlphaScaleValueType value )
{
	getFieldRW<FAlphaScaleType>(getFAlphaScale())->setValue( value );
}



// Field name accessor(s)
const std::string LayerPlan::getFPosition( void )
{
	return "f_position";
}



const std::string LayerPlan::getFSize( void )
{
	return "f_size";
}



const std::string LayerPlan::getFImage( void )
{
	return "f_image";
}



const std::string LayerPlan::getFAlphaScale( void )
{
	return "f_alphaScale";
}



// DIRTY FLAG(S)
const std::string LayerPlan::getDFImage()
{
	return "df_image";
}


IMPLEMENT_INDEXABLE_CLASS_CPP( LayerPlan );



const vgd::basic::RegisterNode<LayerPlan> LayerPlan::m_registrationInstance;



} // namespace node

} // namespace vgd

