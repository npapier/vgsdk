// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/PointStyle.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< PointStyle > PointStyle::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< PointStyle > node( new PointStyle(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< PointStyle > PointStyle::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< PointStyle > node = PointStyle::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< PointStyle > PointStyle::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< PointStyle > node = PointStyle::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



PointStyle::PointStyle( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FSizeType(getFSize()) );
	addField( new FDistanceAttenuationType(getFDistanceAttenuation()) );
	addField( new FSmoothType(getFSmooth()) );
	addField( new FPointSpriteType(getFPointSprite()) );

	// Sets link(s)

	link( getDFNode() );
}



void PointStyle::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
}



void PointStyle::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	setSize( (1.f) );
	setDistanceAttenuation( vgm::Vec3f(1.f, 0.f, 0.f) );
	setSmooth( (false) );
	setPointSprite( (false) );
}



// Size

const PointStyle::SizeValueType PointStyle::DEFAULT_SIZE = (1.f);



const bool PointStyle::getSize( SizeValueType& value ) const
{
	return getFieldRO<FSizeType>(getFSize())->getValue( value );
}



void PointStyle::setSize( const SizeValueType& value )
{
	getFieldRW<FSizeType>(getFSize())->setValue( value );
}



void PointStyle::eraseSize()
{
	getFieldRW<FSizeType>(getFSize())->eraseValue();
}


const bool PointStyle::hasSize() const
{
	return getFieldRO<FSizeType>(getFSize())->hasValue();
}



// DistanceAttenuation

const PointStyle::DistanceAttenuationValueType PointStyle::DEFAULT_DISTANCEATTENUATION = vgm::Vec3f(1.f, 0.f, 0.f);



const bool PointStyle::getDistanceAttenuation( DistanceAttenuationValueType& value ) const
{
	return getFieldRO<FDistanceAttenuationType>(getFDistanceAttenuation())->getValue( value );
}



void PointStyle::setDistanceAttenuation( const DistanceAttenuationValueType& value )
{
	getFieldRW<FDistanceAttenuationType>(getFDistanceAttenuation())->setValue( value );
}



void PointStyle::eraseDistanceAttenuation()
{
	getFieldRW<FDistanceAttenuationType>(getFDistanceAttenuation())->eraseValue();
}


const bool PointStyle::hasDistanceAttenuation() const
{
	return getFieldRO<FDistanceAttenuationType>(getFDistanceAttenuation())->hasValue();
}



// Smooth

const PointStyle::SmoothValueType PointStyle::DEFAULT_SMOOTH = (false);



const bool PointStyle::getSmooth( SmoothValueType& value ) const
{
	return getFieldRO<FSmoothType>(getFSmooth())->getValue( value );
}



void PointStyle::setSmooth( const SmoothValueType& value )
{
	getFieldRW<FSmoothType>(getFSmooth())->setValue( value );
}



void PointStyle::eraseSmooth()
{
	getFieldRW<FSmoothType>(getFSmooth())->eraseValue();
}


const bool PointStyle::hasSmooth() const
{
	return getFieldRO<FSmoothType>(getFSmooth())->hasValue();
}



// PointSprite

const PointStyle::PointSpriteValueType PointStyle::DEFAULT_POINTSPRITE = (false);



const bool PointStyle::getPointSprite( PointSpriteValueType& value ) const
{
	return getFieldRO<FPointSpriteType>(getFPointSprite())->getValue( value );
}



void PointStyle::setPointSprite( const PointSpriteValueType& value )
{
	getFieldRW<FPointSpriteType>(getFPointSprite())->setValue( value );
}



void PointStyle::erasePointSprite()
{
	getFieldRW<FPointSpriteType>(getFPointSprite())->eraseValue();
}


const bool PointStyle::hasPointSprite() const
{
	return getFieldRO<FPointSpriteType>(getFPointSprite())->hasValue();
}



// Field name accessor(s)
const std::string PointStyle::getFSize( void )
{
	return "f_size";
}



const std::string PointStyle::getFDistanceAttenuation( void )
{
	return "f_distanceAttenuation";
}



const std::string PointStyle::getFSmooth( void )
{
	return "f_smooth";
}



const std::string PointStyle::getFPointSprite( void )
{
	return "f_pointSprite";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , PointStyle );



const vgd::basic::RegisterNode<PointStyle> PointStyle::m_registrationInstance;



} // namespace node

} // namespace vgd

