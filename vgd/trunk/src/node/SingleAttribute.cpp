// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



// META_NODE_CPP( SingleAttribute ); abstract class.



SingleAttribute::SingleAttribute( const std::string nodeName ) :
	vgd::node::Attribute( nodeName )
{
}



void SingleAttribute::setToDefaults( void )
{
	Attribute::setToDefaults();
}



void SingleAttribute::setOptionalsToDefaults()
{
	Attribute::setOptionalsToDefaults();
}



} // namespace node

} // namespace vgd
