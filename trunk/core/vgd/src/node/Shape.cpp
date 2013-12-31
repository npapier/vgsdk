// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Shape.hpp"



namespace vgd
{

namespace node
{



// META_NODE_CPP( Shape ); abstract class.



Shape::Shape( const std::string nodeName ) :
	vgd::node::Node( nodeName ),
	vgd::node::IBoundingBox(),
	vgd::node::IShape()
{
}



void Shape::setToDefaults( void )
{
	Node::setToDefaults();
}



void Shape::setOptionalsToDefaults()
{
	Node::setOptionalsToDefaults();
}



} // namespace node

} // namespace vgd
