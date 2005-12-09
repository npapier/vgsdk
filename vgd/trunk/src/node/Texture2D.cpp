// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Texture2D.hpp"

#include "vgd/field/TAccessors.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( Texture2D );



Texture2D::Texture2D( const std::string nodeName ) :
	vgd::node::Texture( nodeName )
{
}



void Texture2D::setToDefaults( void )
{
	Texture::setToDefaults();
}



void Texture2D::setOptionalsToDefaults()
{
	Texture::setOptionalsToDefaults();
}



bool Texture2D::getIImage( vgd::Shp< vgd::basic::IImage >& value ) const
{
	return ( getIImages(DEFAULT_IIMAGES, value) );
}



void Texture2D::setIImage( vgd::Shp< vgd::basic::IImage > value )
{
	setIImages(DEFAULT_IIMAGES, value);
}



void Texture2D::eraseIImage()
{
	eraseIImages(DEFAULT_IIMAGES);
}



const uint32 Texture2D::gethTextureDimension() const
{
	return ( 2 );
}



} // namespace node

} // namespace vgd
