// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/DirectionalLight.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< DirectionalLight > DirectionalLight::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< DirectionalLight > node( new DirectionalLight(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< DirectionalLight > DirectionalLight::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< DirectionalLight > node = DirectionalLight::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< DirectionalLight > DirectionalLight::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< DirectionalLight > node = DirectionalLight::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



DirectionalLight::DirectionalLight( const std::string nodeName ) :
	vgd::node::Light( nodeName )
{
	// Adds field(s)
	addField( new FDirectionType(getFDirection()) );

	// Sets link(s)

	link( getDFNode() );
}



void DirectionalLight::setToDefaults( void )
{
	Light::setToDefaults();
}



void DirectionalLight::setOptionalsToDefaults()
{
	Light::setOptionalsToDefaults();
	setDirection( vgm::Vec3f(0.f, 0.f, -1.f) );
}



// Direction
const bool DirectionalLight::getDirection( DirectionValueType& value ) const
{
	return getFieldRO<FDirectionType>(getFDirection())->getValue( value );
}



void DirectionalLight::setDirection( const DirectionValueType& value )
{
	getFieldRW<FDirectionType>(getFDirection())->setValue( value );
}



void DirectionalLight::eraseDirection()
{
	getFieldRW<FDirectionType>(getFDirection())->eraseValue();
}


const bool DirectionalLight::hasDirection() const
{
	return getFieldRO<FDirectionType>(getFDirection())->hasValue();
}



// Field name accessor(s)
const std::string DirectionalLight::getFDirection( void )
{
	return "f_direction";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , DirectionalLight );



const vgd::basic::RegisterNode<DirectionalLight> DirectionalLight::m_registrationInstance;



} // namespace node

} // namespace vgd

