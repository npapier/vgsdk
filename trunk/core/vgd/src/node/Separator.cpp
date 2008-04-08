// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Separator.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( Separator );



Separator::Separator( const std::string nodeName ) :
	vgd::node::Group( nodeName )
{
}



void Separator::setToDefaults( void )
{
	Group::setToDefaults();
}



void Separator::setOptionalsToDefaults()
{
	Group::setOptionalsToDefaults();
}



} // namespace node

} // namespace vgd