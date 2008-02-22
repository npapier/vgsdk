// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/TextureTransformation.hpp"



namespace vgd
{

namespace node
{



//META_NODE_CPP( TextureTransformation ); // abstract class.



TextureTransformation::TextureTransformation( const std::string nodeName ) :
	vgd::node::MultiTransformation( nodeName )
{
}



void TextureTransformation::setToDefaults( void )
{
	MultiTransformation::setToDefaults();
}



void TextureTransformation::setOptionalsToDefaults()
{
	MultiTransformation::setOptionalsToDefaults();
}



} // namespace node

} // namespace vgd
