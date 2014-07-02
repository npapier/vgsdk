// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/FrontFace.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< FrontFace > FrontFace::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< FrontFace > node( new FrontFace(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< FrontFace > FrontFace::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< FrontFace > node = FrontFace::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< FrontFace > FrontFace::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< FrontFace > node = FrontFace::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



FrontFace::FrontFace( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FOrientationType(getFOrientation()) );

	// Sets link(s)

	link( getDFNode() );
}



void FrontFace::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setOrientation( (CCW) );
}



void FrontFace::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



// Orientation

const FrontFace::OrientationValueType FrontFace::getOrientation() const
{
	return getFieldRO<FOrientationType>(getFOrientation())->getValue();
}



void FrontFace::setOrientation( const OrientationValueType value )
{
	getFieldRW<FOrientationType>(getFOrientation())->setValue( value );
}



// Field name accessor(s)
const std::string FrontFace::getFOrientation( void )
{
	return "f_orientation";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( FrontFace );
//IMPLEMENT_INDEXABLE_CLASS_CPP( , FrontFace );



const vgd::basic::RegisterNode<FrontFace> FrontFace::m_registrationInstance;



} // namespace node

} // namespace vgd

