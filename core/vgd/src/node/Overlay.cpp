// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Overlay.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< Overlay > Overlay::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Overlay > node( new Overlay(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< Overlay > Overlay::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< Overlay > node = Overlay::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< Overlay > Overlay::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Overlay > node = Overlay::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



Overlay::Overlay( const std::string nodeName ) :
	vgd::node::LayerPlan( nodeName )
{
	// Adds field(s)
}



void Overlay::setToDefaults( void )
{
	LayerPlan::setToDefaults();
}



void Overlay::setOptionalsToDefaults()
{
	LayerPlan::setOptionalsToDefaults();
}



// Field name accessor(s)
IMPLEMENT_INDEXABLE_CLASS_CPP( , Overlay );



const vgd::basic::RegisterNode<Overlay> Overlay::m_registrationInstance;



} // namespace node

} // namespace vgd

