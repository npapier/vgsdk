// VGSDK - Copyright (C) 2012, Nicolas Papier.
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
	addField( new FFragmentFunctionType(getFFragmentFunction()) );
	addField( new FWrapType(getFWrap()) );
	addField( new FImageType(getFImage()) );
	addField( new FMipmapType(getFMipmap()) );
	addField( new FFilterType(getFFilter()) );
	addField( new FVertexFunctionType(getFVertexFunction()) );
	addField( new FInternalFormatType(getFInternalFormat()) );
	addField( new FUsageType(getFUsage()) );

	// Adds dirty flag(s)
	addDirtyFlag(getDFImage());
	addDirtyFlag(getDFParameters());

	// Sets link(s)
	link( getFImage(), getDFImage() );
	link( getFWrap(), getDFParameters() );
	link( getFFilter(), getDFParameters() );
	link( getFMipmap(), getDFParameters() );
	link( getFUsage(), getDFParameters() );

	link( getDFNode() );
}



void Texture::setToDefaults( void )
{
	MultiAttribute::setToDefaults();
	setInternalFormat( AUTOMATIC );
	setUsage( IMAGE );
}



void Texture::setOptionalsToDefaults()
{
	MultiAttribute::setOptionalsToDefaults();

	setWrap( WRAP_T, REPEAT );
	setWrap( WRAP_S, REPEAT );
	setWrap( WRAP_R, REPEAT );


	setMipmap( false );
	setFilter( MIN_FILTER, LINEAR );
	setFilter( MAG_FILTER, LINEAR );


}



// FragmentFunction
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



// VertexFunction
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



// InternalFormat
const Texture::InternalFormatValueType Texture::getInternalFormat() const
{
	return getFieldRO<FInternalFormatType>(getFInternalFormat())->getValue();
}



void Texture::setInternalFormat( const InternalFormatValueType value )
{
	getFieldRW<FInternalFormatType>(getFInternalFormat())->setValue( value );
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
const std::string Texture::getFFragmentFunction( void )
{
	return "f_fragmentFunction";
}



const std::string Texture::getFWrap( void )
{
	return "f_wrap";
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



const std::string Texture::getFVertexFunction( void )
{
	return "f_vertexFunction";
}



const std::string Texture::getFInternalFormat( void )
{
	return "f_internalFormat";
}



const std::string Texture::getFUsage( void )
{
	return "f_usage";
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

