// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Texture1D.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( Texture1D );



Texture1D::Texture1D( const std::string nodeName ) :
	vgd::node::Texture( nodeName )
{
}



void Texture1D::setToDefaults( void )
{
	Texture::setToDefaults();
}



void Texture1D::setOptionalsToDefaults()
{
	Texture::setOptionalsToDefaults();
}



bool Texture1D::getIImage( vgd::Shp< vgd::basic::IImage >& value ) const
{
	return ( getIImages( DEFAULT_IIMAGES, value ) );
}



void Texture1D::setIImage( vgd::Shp< vgd::basic::IImage > value )
{
	setIImages( DEFAULT_IIMAGES, value );
}



void Texture1D::eraseIImage()
{
	eraseIImages( DEFAULT_IIMAGES );
}



const uint32 Texture1D::gethTextureDimension() const
{
	return ( 1 );
}



} // namespace node

} // namespace vgd
