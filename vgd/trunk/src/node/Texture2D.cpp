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
	// Add field
	addField( new FIImageType(getFIImage()) );
	
	// Add dirty flag
	addDirtyFlag( getDFIImage() );
	
	// Link(s)
	link( getFIImage(), getDFIImage() );
	link( getFIImage(), getDFNode() );
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
	return ( 
		vgd::field::getParameterValue< IImageParameterType, IImageValueType >( this, getFIImage(), IIMAGE, value )
		);
}



void Texture2D::setIImage( vgd::Shp< vgd::basic::IImage > value )
{
	vgd::field::setParameterValue< IImageParameterType, IImageValueType >( this, getFIImage(), IIMAGE, value );
}



void Texture2D::eraseIImage()
{
	vgd::field::eraseParameterValue< IImageParameterType, IImageValueType >( this, getFIImage(), IIMAGE );
}



const std::string Texture2D::getFIImage( void )
{
	return ( "f_iimage" );
}



const std::string Texture2D::getDFIImage()
{
	return ( "df_iimage" );
}



} // namespace node

} // namespace vgd
