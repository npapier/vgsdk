// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/GeometricalTransformation.hpp"



namespace vgd
{

namespace node
{



//META_NODE_CPP( GeometricalTransformation ); // abstract class.



GeometricalTransformation::GeometricalTransformation( const std::string nodeName ) :
	vgd::node::SingleTransformation( nodeName )
{
}



void GeometricalTransformation::setToDefaults( void )
{
	SingleTransformation::setToDefaults();
}



void GeometricalTransformation::setOptionalsToDefaults()
{
	SingleTransformation::setOptionalsToDefaults();
}

} // namespace node

} // namespace vgd
