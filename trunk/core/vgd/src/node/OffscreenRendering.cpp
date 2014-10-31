// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/OffscreenRendering.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< OffscreenRendering > OffscreenRendering::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< OffscreenRendering > node( new OffscreenRendering(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< OffscreenRendering > OffscreenRendering::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< OffscreenRendering > node = OffscreenRendering::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< OffscreenRendering > OffscreenRendering::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< OffscreenRendering > node = OffscreenRendering::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



OffscreenRendering::OffscreenRendering( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FRootType(getFRoot()) );

	// Sets link(s)

	link( getDFNode() );
}



void OffscreenRendering::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setRoot( vgd::node::GroupShp() );
}



void OffscreenRendering::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



// Root

const OffscreenRendering::RootValueType OffscreenRendering::DEFAULT_ROOT = vgd::node::GroupShp();



const OffscreenRendering::RootValueType OffscreenRendering::getRoot() const
{
	return getFieldRO<FRootType>(getFRoot())->getValue();
}



void OffscreenRendering::setRoot( const RootValueType value )
{
	getFieldRW<FRootType>(getFRoot())->setValue( value );
}



// Field name accessor(s)
const std::string OffscreenRendering::getFRoot( void )
{
	return "f_root";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( OffscreenRendering );



const vgd::basic::RegisterNode<OffscreenRendering> OffscreenRendering::m_registrationInstance;



} // namespace node

} // namespace vgd

