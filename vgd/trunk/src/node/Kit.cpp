// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Kit.hpp"



namespace vgd
{

namespace node
{



//META_NODE_CPP( Kit ); // abstract class.



Kit::Kit( const std::string nodeName ) :
	vgd::node::Separator( nodeName )
{
}



void Kit::setToDefaults( void )
{
	Separator::setToDefaults();
}



void Kit::setOptionalsToDefaults()
{
	Separator::setOptionalsToDefaults();
}



} // namespace node

} // namespace vgd
