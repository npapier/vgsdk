// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Decal.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< Decal > Decal::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Decal > node( new Decal(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< Decal > Decal::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< Decal > node = Decal::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< Decal > Decal::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Decal > node = Decal::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



Decal::Decal( const std::string nodeName ) :
	vgd::node::MultiAttribute( nodeName )
{
	// Adds field(s)
	addField( new FTextureType(getFTexture()) );
	addField( new FShapeType(getFShape()) );
	addField( new FAlphaTestType(getFAlphaTest()) );
	addField( new FBlendingType(getFBlending()) );

	// Sets link(s)

	link( getDFNode() );
}



void Decal::setToDefaults( void )
{
	MultiAttribute::setToDefaults();
	setTexture( vgd::node::Texture2DShp() );
	setShape( vgd::node::VertexShapeShp() );
	setAlphaTest( (true) );
	setBlending( (false) );
}



void Decal::setOptionalsToDefaults()
{
	MultiAttribute::setOptionalsToDefaults();
}



// Texture

const Decal::TextureValueType Decal::DEFAULT_TEXTURE = vgd::node::Texture2DShp();



const Decal::TextureValueType Decal::getTexture() const
{
	return getFieldRO<FTextureType>(getFTexture())->getValue();
}



void Decal::setTexture( const TextureValueType value )
{
	getFieldRW<FTextureType>(getFTexture())->setValue( value );
}



// Shape

const Decal::ShapeValueType Decal::DEFAULT_SHAPE = vgd::node::VertexShapeShp();



const Decal::ShapeValueType Decal::getShape() const
{
	return getFieldRO<FShapeType>(getFShape())->getValue();
}



void Decal::setShape( const ShapeValueType value )
{
	getFieldRW<FShapeType>(getFShape())->setValue( value );
}



// AlphaTest

const Decal::AlphaTestValueType Decal::DEFAULT_ALPHATEST = (true);



const Decal::AlphaTestValueType Decal::getAlphaTest() const
{
	return getFieldRO<FAlphaTestType>(getFAlphaTest())->getValue();
}



void Decal::setAlphaTest( const AlphaTestValueType value )
{
	getFieldRW<FAlphaTestType>(getFAlphaTest())->setValue( value );
}



// Blending

const Decal::BlendingValueType Decal::DEFAULT_BLENDING = (false);



const Decal::BlendingValueType Decal::getBlending() const
{
	return getFieldRO<FBlendingType>(getFBlending())->getValue();
}



void Decal::setBlending( const BlendingValueType value )
{
	getFieldRW<FBlendingType>(getFBlending())->setValue( value );
}



// Field name accessor(s)
const std::string Decal::getFTexture( void )
{
	return "f_texture";
}



const std::string Decal::getFShape( void )
{
	return "f_shape";
}



const std::string Decal::getFAlphaTest( void )
{
	return "f_alphaTest";
}



const std::string Decal::getFBlending( void )
{
	return "f_blending";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( Decal );
//IMPLEMENT_INDEXABLE_CLASS_CPP( , Decal );



const vgd::basic::RegisterNode<Decal> Decal::m_registrationInstance;



} // namespace node

} // namespace vgd

