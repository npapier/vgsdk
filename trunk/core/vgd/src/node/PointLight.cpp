// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/PointLight.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< PointLight > PointLight::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< PointLight > node( new PointLight(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< PointLight > PointLight::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< PointLight > node = PointLight::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



PointLight::PointLight( const std::string nodeName ) :
	vgd::node::Light( nodeName )
{
	// Adds field(s)
	addField( new FPositionType(getFPosition()) );

	// Sets link(s)
	link( getDFNode() );
}



void PointLight::setToDefaults( void )
{
	Light::setToDefaults();
}



void PointLight::setOptionalsToDefaults()
{
	Light::setOptionalsToDefaults();
	setPosition( vgm::Vec3f(0.f, 0.f, 1.f) );
}



// Position
const bool PointLight::getPosition( PositionValueType& value ) const
{
	return getFieldRO<FPositionType>(getFPosition())->getValue( value );
}



void PointLight::setPosition( const PositionValueType& value )
{
	getFieldRW<FPositionType>(getFPosition())->setValue( value );
}



void PointLight::erasePosition()
{
	getFieldRW<FPositionType>(getFPosition())->eraseValue();
}


const bool PointLight::hasPosition() const
{
	return getFieldRO<FPositionType>(getFPosition())->hasValue();
}



// Field name accessor(s)
const std::string PointLight::getFPosition( void )
{
	return "f_position";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , PointLight );



const vgd::basic::RegisterNode<PointLight> PointLight::m_registrationInstance;



} // namespace node

} // namespace vgd

