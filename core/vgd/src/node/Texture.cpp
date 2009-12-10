// VGSDK - Copyright (C) 2009, Nicolas Papier.
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
	addField( new FFunctionType(getFFunction()) );
	addField( new FImageType(getFImage()) );
	addField( new FMipmapType(getFMipmap()) );
	addField( new FFilterType(getFFilter()) );
	addField( new FWrapType(getFWrap()) );
	addField( new FUsageType(getFUsage()) );

	// Sets link(s)
	link( getDFNode() );
}



void Texture::setToDefaults( void )
{
	MultiAttribute::setToDefaults();
	setUsage( IMAGE );
}



void Texture::setOptionalsToDefaults()
{
	MultiAttribute::setOptionalsToDefaults();


	setMipmap( false );
	setFilter( MIN_FILTER, LINEAR );
	setFilter( MAG_FILTER, LINEAR );

	setWrap( WRAP_T, REPEAT );
	setWrap( WRAP_S, REPEAT );
	setWrap( WRAP_R, REPEAT );

}



// Function
const bool Texture::getFunction( FunctionValueType& value ) const
{
	return getFieldRO<FFunctionType>(getFFunction())->getValue( value );
}



void Texture::setFunction( const FunctionValueType& value )
{
	getFieldRW<FFunctionType>(getFFunction())->setValue( value );
}



void Texture::eraseFunction()
{
	getFieldRW<FFunctionType>(getFFunction())->eraseValue();
}


const bool Texture::hasFunction() const
{
	return getFieldRO<FFunctionType>(getFFunction())->hasValue();
}



// Image
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



// Mipmap
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



// Filter
const bool Texture::getFilter( const FilterParameterType param, FilterValueType& value ) const
{
	return (
		vgd::field::getParameterValue< FilterParameterType, FilterValueType >( this, getFFilter(), static_cast<FilterParameterType>(param), value )
		);
}



void Texture::setFilter( const FilterParameterType param, FilterValueType value )
{
	vgd::field::setParameterValue< FilterParameterType, FilterValueType >( this, getFFilter(), static_cast<FilterParameterType>(param), value );
}



void Texture::eraseFilter( const FilterParameterType param )
{
	vgd::field::eraseParameterValue< FilterParameterType, FilterValueType >( this, getFFilter(), static_cast<FilterParameterType>(param) );
}



// Wrap
const bool Texture::getWrap( const WrapParameterType param, WrapValueType& value ) const
{
	return (
		vgd::field::getParameterValue< WrapParameterType, WrapValueType >( this, getFWrap(), static_cast<WrapParameterType>(param), value )
		);
}



void Texture::setWrap( const WrapParameterType param, WrapValueType value )
{
	vgd::field::setParameterValue< WrapParameterType, WrapValueType >( this, getFWrap(), static_cast<WrapParameterType>(param), value );
}



void Texture::eraseWrap( const WrapParameterType param )
{
	vgd::field::eraseParameterValue< WrapParameterType, WrapValueType >( this, getFWrap(), static_cast<WrapParameterType>(param) );
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



// Field name accessor(s)
const std::string Texture::getFFunction( void )
{
	return "f_function";
}



const std::string Texture::getFImage( void )
{
	return "f_image";
}



const std::string Texture::getFMipmap( void )
{
	return "f_mipmap";
}



const std::string Texture::getFFilter( void )
{
	return "f_filter";
}



const std::string Texture::getFWrap( void )
{
	return "f_wrap";
}



const std::string Texture::getFUsage( void )
{
	return "f_usage";
}



// FUNCTION
void Texture::sethFunction( OldFunctionValueType value )
{
	const std::string strIndex = vgd::basic::toString( getMultiAttributeIndex() );

	if ( value == FUN_REPLACE )
	{
		std::string function = "color = texture2D(texUnit" + strIndex + ", gl_TexCoord[" + strIndex + "].xy);\n";
		setFunction( function );
	}
	else if ( value == FUN_MODULATE )
	{
		std::string function = "color *= texture2D(texUnit" + strIndex + ", gl_TexCoord[" + strIndex + "].xy);\n";
		setFunction( function );
	}
	else
	{
		assert( false );
	}
}
} // namespace node

} // namespace vgd

