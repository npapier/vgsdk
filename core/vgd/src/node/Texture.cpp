// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Texture.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



Texture::Texture( const std::string nodeName ) :
	vgd::node::MultiAttribute( nodeName )
{
	// Adds field(s)
	addField( new FUsageType(getFUsage()) );
	addField( new FInternalFormatType(getFInternalFormat()) );
	addField( new FImageType(getFImage()) );
	addField( new FWrapSType(getFWrapS()) );
	addField( new FWrapTType(getFWrapT()) );
	addField( new FWrapRType(getFWrapR()) );
	addField( new FMinFilterType(getFMinFilter()) );
	addField( new FMagFilterType(getFMagFilter()) );
	addField( new FMipmapType(getFMipmap()) );
	addField( new FMaxAnisotropyType(getFMaxAnisotropy()) );
	addField( new FVertexFunctionType(getFVertexFunction()) );
	addField( new FFragmentFunctionType(getFFragmentFunction()) );

	// Adds dirty flag(s)
	addDirtyFlag(getDFImage());
	addDirtyFlag(getDFParameters());

	// Sets link(s)
	link( getFImage(), getDFImage() );
	link( getFWrapS(), getDFParameters() );
	link( getFWrapT(), getDFParameters() );
	link( getFWrapR(), getDFParameters() );
	link( getFMinFilter(), getDFParameters() );
	link( getFMagFilter(), getDFParameters() );
	link( getFMipmap(), getDFParameters() );
	link( getFMaxAnisotropy(), getDFParameters() );
	link( getFUsage(), getDFParameters() );

	link( getDFNode() );
}



void Texture::setToDefaults( void )
{
	MultiAttribute::setToDefaults();
	setUsage( (IMAGE) );
	setInternalFormat( (AUTOMATIC) );
}



void Texture::setOptionalsToDefaults()
{
	MultiAttribute::setOptionalsToDefaults();
	setImage( vgd::basic::IImageShp() );
	setWrapS( (REPEAT) );
	setWrapT( (REPEAT) );
	setWrapR( (REPEAT) );
	setMinFilter( (LINEAR) );
	setMagFilter( (LINEAR) );
	setMipmap( (false) );
	setMaxAnisotropy( (1.f) );
	setVertexFunction( std::string() );
	setFragmentFunction( std::string() );
}



// Usage

const Texture::UsageValueType Texture::getUsage() const
{
	return getFieldRO<FUsageType>(getFUsage())->getValue();
}



void Texture::setUsage( const UsageValueType value )
{
	getFieldRW<FUsageType>(getFUsage())->setValue( value );
}



// InternalFormat

const Texture::InternalFormatValueType Texture::getInternalFormat() const
{
	return getFieldRO<FInternalFormatType>(getFInternalFormat())->getValue();
}



void Texture::setInternalFormat( const InternalFormatValueType value )
{
	getFieldRW<FInternalFormatType>(getFInternalFormat())->setValue( value );
}



// Image

const Texture::ImageValueType Texture::DEFAULT_IMAGE = vgd::basic::IImageShp();



const bool Texture::getImage( ImageValueType& value ) const
{
	return getFieldRO<FImageType>(getFImage())->getValue( value );
}



void Texture::setImage( const ImageValueType& value )
{
	getFieldRW<FImageType>(getFImage())->setValue( value );
}



void Texture::eraseImage()
{
	getFieldRW<FImageType>(getFImage())->eraseValue();
}


const bool Texture::hasImage() const
{
	return getFieldRO<FImageType>(getFImage())->hasValue();
}



// WrapS

const bool Texture::getWrapS( WrapSValueType& value ) const
{
	return getFieldRO<FWrapSType>(getFWrapS())->getValue( value );
}



void Texture::setWrapS( const WrapSValueType& value )
{
	getFieldRW<FWrapSType>(getFWrapS())->setValue( value );
}



void Texture::eraseWrapS()
{
	getFieldRW<FWrapSType>(getFWrapS())->eraseValue();
}


const bool Texture::hasWrapS() const
{
	return getFieldRO<FWrapSType>(getFWrapS())->hasValue();
}



// WrapT

const bool Texture::getWrapT( WrapTValueType& value ) const
{
	return getFieldRO<FWrapTType>(getFWrapT())->getValue( value );
}



void Texture::setWrapT( const WrapTValueType& value )
{
	getFieldRW<FWrapTType>(getFWrapT())->setValue( value );
}



void Texture::eraseWrapT()
{
	getFieldRW<FWrapTType>(getFWrapT())->eraseValue();
}


const bool Texture::hasWrapT() const
{
	return getFieldRO<FWrapTType>(getFWrapT())->hasValue();
}



// WrapR

const bool Texture::getWrapR( WrapRValueType& value ) const
{
	return getFieldRO<FWrapRType>(getFWrapR())->getValue( value );
}



void Texture::setWrapR( const WrapRValueType& value )
{
	getFieldRW<FWrapRType>(getFWrapR())->setValue( value );
}



void Texture::eraseWrapR()
{
	getFieldRW<FWrapRType>(getFWrapR())->eraseValue();
}


const bool Texture::hasWrapR() const
{
	return getFieldRO<FWrapRType>(getFWrapR())->hasValue();
}



// MinFilter

const bool Texture::getMinFilter( MinFilterValueType& value ) const
{
	return getFieldRO<FMinFilterType>(getFMinFilter())->getValue( value );
}



void Texture::setMinFilter( const MinFilterValueType& value )
{
	getFieldRW<FMinFilterType>(getFMinFilter())->setValue( value );
}



void Texture::eraseMinFilter()
{
	getFieldRW<FMinFilterType>(getFMinFilter())->eraseValue();
}


const bool Texture::hasMinFilter() const
{
	return getFieldRO<FMinFilterType>(getFMinFilter())->hasValue();
}



// MagFilter

const bool Texture::getMagFilter( MagFilterValueType& value ) const
{
	return getFieldRO<FMagFilterType>(getFMagFilter())->getValue( value );
}



void Texture::setMagFilter( const MagFilterValueType& value )
{
	getFieldRW<FMagFilterType>(getFMagFilter())->setValue( value );
}



void Texture::eraseMagFilter()
{
	getFieldRW<FMagFilterType>(getFMagFilter())->eraseValue();
}


const bool Texture::hasMagFilter() const
{
	return getFieldRO<FMagFilterType>(getFMagFilter())->hasValue();
}



// Mipmap

const Texture::MipmapValueType Texture::DEFAULT_MIPMAP = (false);



const bool Texture::getMipmap( MipmapValueType& value ) const
{
	return getFieldRO<FMipmapType>(getFMipmap())->getValue( value );
}



void Texture::setMipmap( const MipmapValueType& value )
{
	getFieldRW<FMipmapType>(getFMipmap())->setValue( value );
}



void Texture::eraseMipmap()
{
	getFieldRW<FMipmapType>(getFMipmap())->eraseValue();
}


const bool Texture::hasMipmap() const
{
	return getFieldRO<FMipmapType>(getFMipmap())->hasValue();
}



// MaxAnisotropy

const Texture::MaxAnisotropyValueType Texture::DEFAULT_MAXANISOTROPY = (1.f);



const bool Texture::getMaxAnisotropy( MaxAnisotropyValueType& value ) const
{
	return getFieldRO<FMaxAnisotropyType>(getFMaxAnisotropy())->getValue( value );
}



void Texture::setMaxAnisotropy( const MaxAnisotropyValueType& value )
{
	getFieldRW<FMaxAnisotropyType>(getFMaxAnisotropy())->setValue( value );
}



void Texture::eraseMaxAnisotropy()
{
	getFieldRW<FMaxAnisotropyType>(getFMaxAnisotropy())->eraseValue();
}


const bool Texture::hasMaxAnisotropy() const
{
	return getFieldRO<FMaxAnisotropyType>(getFMaxAnisotropy())->hasValue();
}



// VertexFunction

const Texture::VertexFunctionValueType Texture::DEFAULT_VERTEXFUNCTION = std::string();



const bool Texture::getVertexFunction( VertexFunctionValueType& value ) const
{
	return getFieldRO<FVertexFunctionType>(getFVertexFunction())->getValue( value );
}



void Texture::setVertexFunction( const VertexFunctionValueType& value )
{
	getFieldRW<FVertexFunctionType>(getFVertexFunction())->setValue( value );
}



void Texture::eraseVertexFunction()
{
	getFieldRW<FVertexFunctionType>(getFVertexFunction())->eraseValue();
}


const bool Texture::hasVertexFunction() const
{
	return getFieldRO<FVertexFunctionType>(getFVertexFunction())->hasValue();
}



// FragmentFunction

const Texture::FragmentFunctionValueType Texture::DEFAULT_FRAGMENTFUNCTION = std::string();



const bool Texture::getFragmentFunction( FragmentFunctionValueType& value ) const
{
	return getFieldRO<FFragmentFunctionType>(getFFragmentFunction())->getValue( value );
}



void Texture::setFragmentFunction( const FragmentFunctionValueType& value )
{
	getFieldRW<FFragmentFunctionType>(getFFragmentFunction())->setValue( value );
}



void Texture::eraseFragmentFunction()
{
	getFieldRW<FFragmentFunctionType>(getFFragmentFunction())->eraseValue();
}


const bool Texture::hasFragmentFunction() const
{
	return getFieldRO<FFragmentFunctionType>(getFFragmentFunction())->hasValue();
}



// Field name accessor(s)
const std::string Texture::getFUsage( void )
{
	return "f_usage";
}



const std::string Texture::getFInternalFormat( void )
{
	return "f_internalFormat";
}



const std::string Texture::getFImage( void )
{
	return "f_image";
}



const std::string Texture::getFWrapS( void )
{
	return "f_wrapS";
}



const std::string Texture::getFWrapT( void )
{
	return "f_wrapT";
}



const std::string Texture::getFWrapR( void )
{
	return "f_wrapR";
}



const std::string Texture::getFMinFilter( void )
{
	return "f_minFilter";
}



const std::string Texture::getFMagFilter( void )
{
	return "f_magFilter";
}



const std::string Texture::getFMipmap( void )
{
	return "f_mipmap";
}



const std::string Texture::getFMaxAnisotropy( void )
{
	return "f_maxAnisotropy";
}



const std::string Texture::getFVertexFunction( void )
{
	return "f_vertexFunction";
}



const std::string Texture::getFFragmentFunction( void )
{
	return "f_fragmentFunction";
}



// DIRTY FLAG(S)
const std::string Texture::getDFImage()
{
	return "df_image";
}


const std::string Texture::getDFParameters()
{
	return "df_parameters";
}


// Function
const bool Texture::getFunction( FunctionValueType& value ) const
{
	return getFragmentFunction( value );
}



void Texture::setFunction( const FunctionValueType& value )
{
	setFragmentFunction( value );
}



void Texture::eraseFunction()
{
	eraseFragmentFunction();
}


const bool Texture::hasFunction() const
{
	return hasFragmentFunction();
}


// High level accessor to FUNCTION
void Texture::sethFunction( OldFunctionValueType value )
{
	if ( value == FUN_REPLACE )
	{
		const std::string function = "color = texture(texMap2D[MAI], mgl_TexCoord[MAI].xy);\n";
		setFunction( function );
	}
	else if ( value == FUN_MODULATE )
	{
		const std::string function = "color *= texture(texMap2D[MAI], mgl_TexCoord[MAI].xy);\n";
		setFunction( function );
	}
	else
	{
		vgAssertN( false, "Not yet implemented" );
	}
}
} // namespace node

} // namespace vgd

