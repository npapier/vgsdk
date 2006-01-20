// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Attribute.hpp"



namespace vgd
{

namespace node
{



// META_NODE_CPP( Attribute ); abstract class.



Attribute::Attribute( const std::string nodeName ) :
	vgd::node::Node( nodeName )
{
}



void Attribute::setToDefaults( void )
{
	Node::setToDefaults();
}



void Attribute::setOptionalsToDefaults()
{
	Node::setOptionalsToDefaults();
}



} // namespace node

} // namespace vgd
