// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Light.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



Light::Light( const std::string nodeName ) :
	vgd::node::MultiAttribute( nodeName )
{
	// Adds field(s)
	addField( new FSpecularType(getFSpecular()) );
	addField( new FOnType(getFOn()) );
	addField( new FAmbientType(getFAmbient()) );
	addField( new FDiffuseType(getFDiffuse()) );
	addField( new FCastShadowType(getFCastShadow()) );

	// Sets link(s)

	link( getDFNode() );
}



void Light::setToDefaults( void )
{
	MultiAttribute::setToDefaults();
	setCastShadow( (false) );
}



void Light::setOptionalsToDefaults()
{
	MultiAttribute::setOptionalsToDefaults();
	setSpecular( vgm::Vec4f(1.f, 1.f, 1.f, 0.f) );
	setOn( (false) );
	setAmbient( vgm::Vec4f(0.f, 0.f, 0.f, 0.f) );
	setDiffuse( vgm::Vec4f(1.f, 1.f, 1.f, 0.f) );
}



// Specular

const Light::SpecularValueType Light::DEFAULT_SPECULAR = vgm::Vec4f(1.f, 1.f, 1.f, 0.f);



const bool Light::getSpecular( SpecularValueType& value ) const
{
	return getFieldRO<FSpecularType>(getFSpecular())->getValue( value );
}



void Light::setSpecular( const SpecularValueType& value )
{
	getFieldRW<FSpecularType>(getFSpecular())->setValue( value );
}



void Light::eraseSpecular()
{
	getFieldRW<FSpecularType>(getFSpecular())->eraseValue();
}


const bool Light::hasSpecular() const
{
	return getFieldRO<FSpecularType>(getFSpecular())->hasValue();
}



// On

const Light::OnValueType Light::DEFAULT_ON = (false);



const bool Light::getOn( OnValueType& value ) const
{
	return getFieldRO<FOnType>(getFOn())->getValue( value );
}



void Light::setOn( const OnValueType& value )
{
	getFieldRW<FOnType>(getFOn())->setValue( value );
}



void Light::eraseOn()
{
	getFieldRW<FOnType>(getFOn())->eraseValue();
}


const bool Light::hasOn() const
{
	return getFieldRO<FOnType>(getFOn())->hasValue();
}



// Ambient

const Light::AmbientValueType Light::DEFAULT_AMBIENT = vgm::Vec4f(0.f, 0.f, 0.f, 0.f);



const bool Light::getAmbient( AmbientValueType& value ) const
{
	return getFieldRO<FAmbientType>(getFAmbient())->getValue( value );
}



void Light::setAmbient( const AmbientValueType& value )
{
	getFieldRW<FAmbientType>(getFAmbient())->setValue( value );
}



void Light::eraseAmbient()
{
	getFieldRW<FAmbientType>(getFAmbient())->eraseValue();
}


const bool Light::hasAmbient() const
{
	return getFieldRO<FAmbientType>(getFAmbient())->hasValue();
}



// Diffuse

const Light::DiffuseValueType Light::DEFAULT_DIFFUSE = vgm::Vec4f(1.f, 1.f, 1.f, 0.f);



const bool Light::getDiffuse( DiffuseValueType& value ) const
{
	return getFieldRO<FDiffuseType>(getFDiffuse())->getValue( value );
}



void Light::setDiffuse( const DiffuseValueType& value )
{
	getFieldRW<FDiffuseType>(getFDiffuse())->setValue( value );
}



void Light::eraseDiffuse()
{
	getFieldRW<FDiffuseType>(getFDiffuse())->eraseValue();
}


const bool Light::hasDiffuse() const
{
	return getFieldRO<FDiffuseType>(getFDiffuse())->hasValue();
}



// CastShadow

const Light::CastShadowValueType Light::DEFAULT_CASTSHADOW = (false);



const Light::CastShadowValueType Light::getCastShadow() const
{
	return getFieldRO<FCastShadowType>(getFCastShadow())->getValue();
}



void Light::setCastShadow( const CastShadowValueType value )
{
	getFieldRW<FCastShadowType>(getFCastShadow())->setValue( value );
}



// Field name accessor(s)
const std::string Light::getFSpecular( void )
{
	return "f_specular";
}



const std::string Light::getFOn( void )
{
	return "f_on";
}



const std::string Light::getFAmbient( void )
{
	return "f_ambient";
}



const std::string Light::getFDiffuse( void )
{
	return "f_diffuse";
}



const std::string Light::getFCastShadow( void )
{
	return "f_castShadow";
}



// COLOR
bool Light::getColor( const ColorParameterType param, ColorValueType& value ) const
{
	if ( param == AMBIENT )
	{
		return getAmbient( value );
	}
	else if ( param == DIFFUSE )
	{
		return getDiffuse( value );
	}
	else if ( param == SPECULAR )
	{
		return getSpecular( value );
	}
	else
	{
		assert( false );
		return false;
	}
}



void Light::setColor( const ColorParameterType param, ColorValueType value )
{
	if ( param == AMBIENT )
	{
		setAmbient( value );
	}
	else if ( param == DIFFUSE )
	{
		setDiffuse( value );
	}
	else if ( param == SPECULAR )
	{
		setSpecular( value );
	}
	else
	{
		assert( false );
	}
}



void Light::eraseColor( const ColorParameterType param )
{
	if ( param == AMBIENT )
	{
		return eraseAmbient();
	}
	else if ( param == DIFFUSE )
	{
		return eraseDiffuse();
	}
	else if ( param == SPECULAR )
	{
		return eraseSpecular();
	}
	else
	{
		assert( false );
	}
}
} // namespace node

} // namespace vgd

