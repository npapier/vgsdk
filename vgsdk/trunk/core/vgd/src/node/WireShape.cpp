// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/WireShape.hpp"



namespace vgd
{

namespace node
{



WireShape::WireShape( const std::string nodeName ) :
	vgd::node::VertexShape( nodeName )
{
}



void WireShape::setToDefaults( void )
{
	VertexShape::setToDefaults();
}



void WireShape::setOptionalsToDefaults()
{
	VertexShape::setOptionalsToDefaults();
}



} // namespace node

} // namespace vgd
