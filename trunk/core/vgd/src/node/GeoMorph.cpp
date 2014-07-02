// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/GeoMorph.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< GeoMorph > GeoMorph::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< GeoMorph > node( new GeoMorph(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< GeoMorph > GeoMorph::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< GeoMorph > node = GeoMorph::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< GeoMorph > GeoMorph::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< GeoMorph > node = GeoMorph::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



GeoMorph::GeoMorph( const std::string nodeName ) :
	vgd::node::Group( nodeName ),
	vgd::node::IShape()
{
	// Adds field(s)
	addField( new FMethodType(getFMethod()) );
	addField( new FWeightsType(getFWeights()) );
	addField( new F__meshes__Type(getF__meshes__()) );

	// Sets link(s)

	link( getDFNode() );
}



void GeoMorph::setToDefaults( void )
{
	Group::setToDefaults();
	IShape::setToDefaults();
	setMethod( (NORMALIZED) );
	setWeights( vgm::Vec2f(0.f, 0.f) );
}



void GeoMorph::setOptionalsToDefaults()
{
	Group::setOptionalsToDefaults();
	IShape::setOptionalsToDefaults();
}



// Method

const GeoMorph::MethodValueType GeoMorph::getMethod() const
{
	return getFieldRO<FMethodType>(getFMethod())->getValue();
}



void GeoMorph::setMethod( const MethodValueType value )
{
	getFieldRW<FMethodType>(getFMethod())->setValue( value );
}



// Weights

const GeoMorph::WeightsValueType GeoMorph::DEFAULT_WEIGHTS = vgm::Vec2f(0.f, 0.f);



const GeoMorph::WeightsValueType GeoMorph::getWeights() const
{
	return getFieldRO<FWeightsType>(getFWeights())->getValue();
}



void GeoMorph::setWeights( const WeightsValueType value )
{
	getFieldRW<FWeightsType>(getFWeights())->setValue( value );
}



// __meshes__
vgd::field::EditorRO< GeoMorph::F__meshes__Type > GeoMorph::get__meshes__RO() const
{
	return getFieldRO<F__meshes__Type>( getF__meshes__() );
}



vgd::field::EditorRW< GeoMorph::F__meshes__Type > GeoMorph::get__meshes__RW()
{
	return getFieldRW<F__meshes__Type>( getF__meshes__() );
}



// Field name accessor(s)
const std::string GeoMorph::getFMethod( void )
{
	return "f_method";
}



const std::string GeoMorph::getFWeights( void )
{
	return "f_weights";
}



const std::string GeoMorph::getF__meshes__( void )
{
	return "f___meshes__";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( GeoMorph );
//IMPLEMENT_INDEXABLE_CLASS_CPP( , GeoMorph );



const vgd::basic::RegisterNode<GeoMorph> GeoMorph::m_registrationInstance;



} // namespace node

} // namespace vgd

