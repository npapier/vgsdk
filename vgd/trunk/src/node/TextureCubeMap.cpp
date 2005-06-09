// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/TextureCubeMap.hpp"

#include "vgd/field/TAccessors.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( TextureCubeMap );



TextureCubeMap::TextureCubeMap( const std::string nodeName ) :
	vgd::node::Texture( nodeName )
{
	// Add field
	addField( new FIImagesType(getFIImages()) );

	// Link(s)
	link( getDFNode() );	
}



void TextureCubeMap::setToDefaults( void )
{
	Texture::setToDefaults();
}



void TextureCubeMap::setOptionalsToDefaults()
{
	Texture::setOptionalsToDefaults();
}



// IImages
bool TextureCubeMap::getIImages( const IImagesParameterType param, IImagesValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< IImagesParameterType, IImagesValueType >( this, getFIImages(), param, value )
		);
}



void TextureCubeMap::setIImages( const IImagesParameterType param, IImagesValueType value )
{
	vgd::field::setParameterValue< IImagesParameterType, IImagesValueType >( this, getFIImages(), param, value );
}



void TextureCubeMap::eraseIImages( const IImagesParameterType param )
{
	vgd::field::eraseParameterValue< IImagesParameterType, IImagesValueType >( this, getFIImages(), param );
}



const std::string TextureCubeMap::getFIImages( void )
{
	return ( "f_iimages" );
}



const uint32 TextureCubeMap::gethTextureDimension() const
{
	return ( 6 );
}



} // namespace node

} // namespace vgd
