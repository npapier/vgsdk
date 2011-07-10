// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Fluid.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< Fluid > Fluid::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Fluid > node( new Fluid(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< Fluid > Fluid::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< Fluid > node = Fluid::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< Fluid > Fluid::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Fluid > node = Fluid::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



Fluid::Fluid( const std::string nodeName ) :
	vgd::node::Shape( nodeName )
{
	// Adds field(s)
	addField( new FHeightMapSizeType(getFHeightMapSize()) );
	addField( new FSceneType(getFScene()) );
	addField( new FGravityType(getFGravity()) );

	// Sets link(s)

	link( getDFNode() );
}



void Fluid::setToDefaults( void )
{
	Shape::setToDefaults();
	setHeightMapSize( vgm::Vec2i(256, 256) );

	setGravity( vgm::Vec4f(0.f, -1.f, 0.f, 9.8f) );
}



void Fluid::setOptionalsToDefaults()
{
	Shape::setOptionalsToDefaults();
}



// HeightMapSize
const Fluid::HeightMapSizeValueType Fluid::getHeightMapSize() const
{
	return getFieldRO<FHeightMapSizeType>(getFHeightMapSize())->getValue();
}



void Fluid::setHeightMapSize( const HeightMapSizeValueType value )
{
	getFieldRW<FHeightMapSizeType>(getFHeightMapSize())->setValue( value );
}



// Scene
const Fluid::SceneValueType Fluid::getScene() const
{
	return getFieldRO<FSceneType>(getFScene())->getValue();
}



void Fluid::setScene( const SceneValueType value )
{
	getFieldRW<FSceneType>(getFScene())->setValue( value );
}



// Gravity
const Fluid::GravityValueType Fluid::getGravity() const
{
	return getFieldRO<FGravityType>(getFGravity())->getValue();
}



void Fluid::setGravity( const GravityValueType value )
{
	getFieldRW<FGravityType>(getFGravity())->setValue( value );
}



// Field name accessor(s)
const std::string Fluid::getFHeightMapSize( void )
{
	return "f_heightMapSize";
}



const std::string Fluid::getFScene( void )
{
	return "f_scene";
}



const std::string Fluid::getFGravity( void )
{
	return "f_gravity";
}



bool Fluid::computeBoundingBox( const vgm::MatrixR& transformation )
{
	return true;
}



bool Fluid::isBoundingBoxValid() const
{
	return true;
}



void Fluid::invalidateBoundingBox( bool /*bInvalidate*/ )
{
}
IMPLEMENT_INDEXABLE_CLASS_CPP( , Fluid );



const vgd::basic::RegisterNode<Fluid> Fluid::m_registrationInstance;



} // namespace node

} // namespace vgd

