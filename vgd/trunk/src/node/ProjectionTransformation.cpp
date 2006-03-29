// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/ProjectionTransformation.hpp"



namespace vgd
{

namespace node
{



//META_NODE_CPP( ProjectionTransformation ); // abstract class.



ProjectionTransformation::ProjectionTransformation( const std::string nodeName ) :
	vgd::node::SingleTransformation( nodeName )
{
}



void ProjectionTransformation::setToDefaults( void )
{
	SingleTransformation::setToDefaults();
}



void ProjectionTransformation::setOptionalsToDefaults()
{
	SingleTransformation::setOptionalsToDefaults();
}



} // namespace node

} // namespace vgd
