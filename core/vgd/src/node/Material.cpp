// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Material.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< Material > Material::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Material > node( new Material(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< Material > Material::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< Material > node = Material::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



Material::Material( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FOpacityType(getFOpacity()) );
	addField( new FShininessType(getFShininess()) );
	addField( new FEmissionType(getFEmission()) );
	addField( new FSpecularType(getFSpecular()) );
	addField( new FAmbientType(getFAmbient()) );
	addField( new FDiffuseType(getFDiffuse()) );

	// Sets link(s)
	link( getDFNode() );
}



void Material::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setOpacity( 1.f );
}



void Material::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	setShininess( 0.f );
	setEmission( vgm::Vec3f(0.f, 0.f, 0.f) );
	setSpecular( vgm::Vec3f(0.f, 0.f, 0.f) );
	setAmbient( vgm::Vec3f(0.2f, 0.2f, 0.2f) );
	setDiffuse( vgm::Vec3f(0.8f, 0.8f, 0.8f) );
}



// Opacity
const Material::OpacityValueType Material::getOpacity() const
{
	return getFieldRO<FOpacityType>(getFOpacity())->getValue();
}



void Material::setOpacity( const OpacityValueType value )
{
	getFieldRW<FOpacityType>(getFOpacity())->setValue( value );
}



// Shininess
const bool Material::getShininess( ShininessValueType& value ) const
{
	return (
		vgd::field::getParameterValue< ShininessParameterType, ShininessValueType >( this, getFShininess(), static_cast<ShininessParameterType>(SHININESS), value )
		);
}



void Material::setShininess( ShininessValueType value )
{
	vgd::field::setParameterValue< ShininessParameterType, ShininessValueType >( this, getFShininess(), static_cast<ShininessParameterType>(SHININESS), value );
}



void Material::eraseShininess()
{
	vgd::field::eraseParameterValue< ShininessParameterType, ShininessValueType >( this, getFShininess(), static_cast<ShininessParameterType>(SHININESS) );
}



// Emission
const bool Material::getEmission( EmissionValueType& value ) const
{
	return (
		vgd::field::getParameterValue< EmissionParameterType, EmissionValueType >( this, getFEmission(), static_cast<EmissionParameterType>(EMISSION), value )
		);
}



void Material::setEmission( EmissionValueType value )
{
	vgd::field::setParameterValue< EmissionParameterType, EmissionValueType >( this, getFEmission(), static_cast<EmissionParameterType>(EMISSION), value );
}



void Material::eraseEmission()
{
	vgd::field::eraseParameterValue< EmissionParameterType, EmissionValueType >( this, getFEmission(), static_cast<EmissionParameterType>(EMISSION) );
}



// Specular
const bool Material::getSpecular( SpecularValueType& value ) const
{
	return (
		vgd::field::getParameterValue< SpecularParameterType, SpecularValueType >( this, getFSpecular(), static_cast<SpecularParameterType>(SPECULAR), value )
		);
}



void Material::setSpecular( SpecularValueType value )
{
	vgd::field::setParameterValue< SpecularParameterType, SpecularValueType >( this, getFSpecular(), static_cast<SpecularParameterType>(SPECULAR), value );
}



void Material::eraseSpecular()
{
	vgd::field::eraseParameterValue< SpecularParameterType, SpecularValueType >( this, getFSpecular(), static_cast<SpecularParameterType>(SPECULAR) );
}



// Ambient
const bool Material::getAmbient( AmbientValueType& value ) const
{
	return (
		vgd::field::getParameterValue< AmbientParameterType, AmbientValueType >( this, getFAmbient(), static_cast<AmbientParameterType>(AMBIENT), value )
		);
}



void Material::setAmbient( AmbientValueType value )
{
	vgd::field::setParameterValue< AmbientParameterType, AmbientValueType >( this, getFAmbient(), static_cast<AmbientParameterType>(AMBIENT), value );
}



void Material::eraseAmbient()
{
	vgd::field::eraseParameterValue< AmbientParameterType, AmbientValueType >( this, getFAmbient(), static_cast<AmbientParameterType>(AMBIENT) );
}



// Diffuse
const bool Material::getDiffuse( DiffuseValueType& value ) const
{
	return (
		vgd::field::getParameterValue< DiffuseParameterType, DiffuseValueType >( this, getFDiffuse(), static_cast<DiffuseParameterType>(DIFFUSE), value )
		);
}



void Material::setDiffuse( DiffuseValueType value )
{
	vgd::field::setParameterValue< DiffuseParameterType, DiffuseValueType >( this, getFDiffuse(), static_cast<DiffuseParameterType>(DIFFUSE), value );
}



void Material::eraseDiffuse()
{
	vgd::field::eraseParameterValue< DiffuseParameterType, DiffuseValueType >( this, getFDiffuse(), static_cast<DiffuseParameterType>(DIFFUSE) );
}



// Field name accessor(s)
const std::string Material::getFOpacity( void )
{
	return "f_opacity";
}



const std::string Material::getFShininess( void )
{
	return "f_shininess";
}



const std::string Material::getFEmission( void )
{
	return "f_emission";
}



const std::string Material::getFSpecular( void )
{
	return "f_specular";
}



const std::string Material::getFAmbient( void )
{
	return "f_ambient";
}



const std::string Material::getFDiffuse( void )
{
	return "f_diffuse";
}




// Transparency
const Material::TransparencyValueType Material::getTransparency() const
{
	return getOpacity();
}



void Material::setTransparency( const TransparencyValueType value )
{
	setOpacity( value );
}



// Color
bool Material::getColor( const ColorParameterType param, ColorValueType& value ) const
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
	else if ( param == EMISSION )
	{
		return getEmission( value );
	}
	else
	{
		assert( false );
		return false;
	}
}



void Material::setColor( const ColorParameterType param, ColorValueType value )
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
	else if ( param == EMISSION )
	{
		setEmission( value );
	}
	else
	{
		assert( false );
	}
}



void Material::eraseColor( const ColorParameterType param )
{
	if ( param == AMBIENT )
	{
		eraseAmbient();
	}
	else if ( param == DIFFUSE )
	{
		eraseDiffuse();
	}
	else if ( param == SPECULAR )
	{
		eraseSpecular();
	}
	else if ( param == EMISSION )
	{
		eraseEmission();
	}
	else
	{
		assert( false );
	}
}
		IMPLEMENT_INDEXABLE_CLASS_CPP( , Material );



const vgd::basic::RegisterNode<Material> Material::m_registrationInstance;



} // namespace node

} // namespace vgd
