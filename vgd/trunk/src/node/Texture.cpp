// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Texture.hpp"

#include "vgd/field/TAccessors.hpp"



namespace vgd
{

namespace node
{



//META_NODE_CPP( Texture );



Texture::Texture( const std::string nodeName ) :
	vgd::node::MultiAttribute( nodeName )
{
	// Add field
	addField( new FIImagesType(getFIImages()) );
		
	addField( new FWrapType(getFWrap()) );
	addField( new FFilterType(getFFilter()) );
	addField( new FMipmapType(getFMipmap()) );
	addField( new FBorderType(getFBorder()) );
	addField( new FEnvColorType(getFEnvColor()) );

	addField( new FFunctionType(getFFunction()) );
	addField( new FCombineType(getFCombine()) );
	addField( new FSourceType(getFSource()) );
	addField( new FOperandType(getFOperand()) );
	addField( new FScaleType(getFScale()) );

	// Add dirty flags
	addDirtyFlag( getDFIImages() );
	
	addDirtyFlag( getDFParameters() );
	
	// Link(s)
	link( getFIImages(),	getDFIImages() );
		
	link( getFWrap(),		getDFParameters() );
	link( getFFilter(),		getDFParameters() );
	link( getFMipmap(),		getDFParameters() );
	link( getFBorder(),		getDFParameters() );
	link( getFEnvColor(),	getDFParameters() );
	
	link( getFFunction(),	getDFParameters() );
	link( getFCombine(),	getDFParameters() );
	link( getFSource(),		getDFParameters() );
	link( getFOperand(),	getDFParameters() );
	link( getFScale(),		getDFParameters() );									

	link( getDFNode() );	
}



void Texture::setToDefaults( void )
{
	MultiAttribute::setToDefaults();
}



void Texture::setOptionalsToDefaults()
{
	MultiAttribute::setOptionalsToDefaults();
	
	setWrap( WRAP_S,	DEFAULT_WRAP );
	setWrap( WRAP_T,	DEFAULT_WRAP );
	setWrap( WRAP_R,	DEFAULT_WRAP );
	
	setFilter( MIN_FILTER, DEFAULT_FILTER );
	setFilter( MAG_FILTER, DEFAULT_FILTER );

	setMipmap( true );
	
	setBorder( vgm::Vec4f( 0.f, 0.f, 0.f, 0.f ) );
	
	setEnvColor( vgm::Vec4f( 0.f, 0.f, 0.f, 0.f ) );

	setFunction( DEFAULT_FUN );
}



// IIMAGES
bool Texture::getIImages( const IImagesParameterType param, IImagesValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< IImagesParameterType, IImagesValueType >( this, getFIImages(), param, value )
		);
}



void Texture::setIImages( const IImagesParameterType param, IImagesValueType value )
{
	vgd::field::setParameterValue< IImagesParameterType, IImagesValueType >( this, getFIImages(), param, value );
}



void Texture::eraseIImages( const IImagesParameterType param )
{
	vgd::field::eraseParameterValue< IImagesParameterType, IImagesValueType >( this, getFIImages(), param );
}



// WRAP
bool Texture::getWrap( const WrapParameterType param, WrapValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< WrapParameterType, WrapValueType >( this, getFWrap(), param, value )
		);
}



void Texture::setWrap( const WrapParameterType param, WrapValueType value )
{
	vgd::field::setParameterValue< WrapParameterType, WrapValueType >( this, getFWrap(), param, value );
}



void Texture::eraseWrap( const WrapParameterType param )
{
	vgd::field::eraseParameterValue< WrapParameterType, WrapValueType >( this, getFWrap(), param );
}



// FILTER
bool Texture::getFilter( const FilterParameterType param, FilterValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< FilterParameterType, FilterValueType >( this, getFFilter(), param, value )
		);
}



void Texture::setFilter( const FilterParameterType param, FilterValueType value )
{
	vgd::field::setParameterValue< FilterParameterType, FilterValueType >( this, getFFilter(), param, value );
}



void Texture::eraseFilter( const FilterParameterType param )
{
	vgd::field::eraseParameterValue< FilterParameterType, FilterValueType >( this, getFFilter(), param );
}



// MIPMAP
bool Texture::getMipmap( MipmapValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< MipmapParameterType, MipmapValueType >( this, getFMipmap(), MIPMAP, value )
		);
}



void Texture::setMipmap( MipmapValueType value )
{
	vgd::field::setParameterValue< MipmapParameterType, MipmapValueType >( this, getFMipmap(), MIPMAP, value );
}



void Texture::eraseMipmap()
{
	vgd::field::eraseParameterValue< MipmapParameterType, MipmapValueType >( this, getFMipmap(), MIPMAP );
}



// BORDER
bool Texture::getBorder( BorderValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< BorderParameterType, BorderValueType >( this, getFBorder(), BORDER, value )
		);
}



void Texture::setBorder( BorderValueType value )
{
	vgd::field::setParameterValue< BorderParameterType, BorderValueType >( this, getFBorder(), BORDER, value );
}



void Texture::eraseBorder()
{
	vgd::field::eraseParameterValue< BorderParameterType, BorderValueType >( this, getFBorder(), BORDER );
}



// ENV_COLOR
bool Texture::getEnvColor( EnvColorValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< EnvColorParameterType, EnvColorValueType >( this, getFEnvColor(), ENV_COLOR, value )
		);
}



void Texture::setEnvColor( EnvColorValueType value )
{
	vgd::field::setParameterValue< EnvColorParameterType, EnvColorValueType >( this, getFEnvColor(), ENV_COLOR, value );
}



void Texture::eraseEnvColor()
{
	vgd::field::eraseParameterValue< EnvColorParameterType, EnvColorValueType >( this, getFEnvColor(), ENV_COLOR );
}



// FUNCTION
bool Texture::getFunction( FunctionValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< FunctionParameterType, FunctionValueType >( this, getFFunction(), FUNCTION, value )
		);
}



void Texture::setFunction( FunctionValueType value )
{
	vgd::field::setParameterValue< FunctionParameterType, FunctionValueType >( this, getFFunction(), FUNCTION, value );
}



void Texture::eraseFunction()
{
	vgd::field::eraseParameterValue< FunctionParameterType, FunctionValueType >( this, getFFunction(), FUNCTION );
}



// COMBINE
bool Texture::getCombine( const CombineParameterType param, CombineValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< CombineParameterType, CombineValueType >( this, getFCombine(), param, value )
		);
}



void Texture::setCombine( const CombineParameterType param, CombineValueType value )
{
	vgd::field::setParameterValue< CombineParameterType, CombineValueType >( this, getFCombine(), param, value );
}



void Texture::eraseCombine( const CombineParameterType param )
{
	vgd::field::eraseParameterValue< CombineParameterType, CombineValueType >( this, getFCombine(), param );
}



// SOURCE
bool Texture::getSource( const SourceParameterType param, SourceValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< SourceParameterType, SourceValueType >( this, getFSource(), param, value )
		);
}



void Texture::setSource( const SourceParameterType param, SourceValueType value )
{
	vgd::field::setParameterValue< SourceParameterType, SourceValueType >( this, getFSource(), param, value );
}



void Texture::eraseSource( const SourceParameterType param )
{
	vgd::field::eraseParameterValue< SourceParameterType, SourceValueType >( this, getFSource(), param );
}



// OPERAND
bool Texture::getOperand( const OperandParameterType param, OperandValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< OperandParameterType, OperandValueType >( this, getFOperand(), param, value )
		);
}



void Texture::setOperand( const OperandParameterType param, OperandValueType value )
{
	vgd::field::setParameterValue< OperandParameterType, OperandValueType >( this, getFOperand(), param, value );
}



void Texture::eraseOperand( const OperandParameterType param )
{
	vgd::field::eraseParameterValue< OperandParameterType, OperandValueType >( this, getFOperand(), param );
}



// SCALE
bool Texture::getScale( const ScaleParameterType param, ScaleValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< ScaleParameterType, ScaleValueType >( this, getFScale(), param, value )
		);
}



void Texture::setScale( const ScaleParameterType param, ScaleValueType value )
{
	vgd::field::setParameterValue< ScaleParameterType, ScaleValueType >( this, getFScale(), param, value );
}



void Texture::eraseScale( const ScaleParameterType param )
{
	vgd::field::eraseParameterValue< ScaleParameterType, ScaleValueType >( this, getFScale(), param );
}



const std::string Texture::getFIImages( void )
{
	return ( "f_iimages" );
}



const std::string Texture::getFWrap( void )
{
	return ( "f_wrap" );
}



const std::string Texture::getFFilter( void )
{
	return ( "f_filter" );
}



const std::string Texture::getFMipmap( void )
{
	return ( "f_mipmap" );
}



const std::string Texture::getFBorder( void )
{
	return ( "f_border" );
}



const std::string Texture::getFEnvColor( void )
{
	return ( "f_envColor" );
}



const std::string Texture::getFFunction( void )
{
	return ( "f_function" );
}



const std::string Texture::getFCombine( void )
{
	return ( "f_combine" );
}



const std::string Texture::getFSource( void )
{
	return ( "f_source" );
}



const std::string Texture::getFOperand( void )
{
	return ( "f_operand" );
}



const std::string Texture::getFScale( void )
{
	return ( "f_scale" );
}



const std::string Texture::getDFIImages()
{
	return ( "df_iimages" );
}



const std::string Texture::getDFParameters()
{
	return ( "df_parameters" );
}



} // namespace node

} // namespace vgd
