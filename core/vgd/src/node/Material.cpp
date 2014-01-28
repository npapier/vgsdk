// VGSDK - Copyright (C) 2014, Nicolas Papier.
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



vgd::Shp< Material > Material::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< Material > node = Material::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

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
	addField( new FAmbientType(getFAmbient()) );
	addField( new FDiffuseType(getFDiffuse()) );
	addField( new FSpecularType(getFSpecular()) );
	addField( new FEmissionType(getFEmission()) );
	addField( new FShininessType(getFShininess()) );

	// Sets link(s)

	link( getDFNode() );
}



void Material::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setOpacity( (1.f) );
}



void Material::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	setAmbient( vgm::Vec3f(0.2f, 0.2f, 0.2f) );
	setDiffuse( vgm::Vec3f(0.8f, 0.8f, 0.8f) );
	setSpecular( vgm::Vec3f(0.f, 0.f, 0.f) );
	setEmission( vgm::Vec3f(0.f, 0.f, 0.f) );
	setShininess( (0.f) );
}



// Opacity

const Material::OpacityValueType Material::DEFAULT_OPACITY = (1.f);



const Material::OpacityValueType Material::getOpacity() const
{
	return getFieldRO<FOpacityType>(getFOpacity())->getValue();
}



void Material::setOpacity( const OpacityValueType value )
{
	getFieldRW<FOpacityType>(getFOpacity())->setValue( value );
}



// Ambient

const Material::AmbientValueType Material::DEFAULT_AMBIENT = vgm::Vec3f(0.2f, 0.2f, 0.2f);



const bool Material::getAmbient( AmbientValueType& value ) const
{
	return getFieldRO<FAmbientType>(getFAmbient())->getValue( value );
}



void Material::setAmbient( const AmbientValueType& value )
{
	getFieldRW<FAmbientType>(getFAmbient())->setValue( value );
}



void Material::eraseAmbient()
{
	getFieldRW<FAmbientType>(getFAmbient())->eraseValue();
}


const bool Material::hasAmbient() const
{
	return getFieldRO<FAmbientType>(getFAmbient())->hasValue();
}



// Diffuse

const Material::DiffuseValueType Material::DEFAULT_DIFFUSE = vgm::Vec3f(0.8f, 0.8f, 0.8f);



const bool Material::getDiffuse( DiffuseValueType& value ) const
{
	return getFieldRO<FDiffuseType>(getFDiffuse())->getValue( value );
}



void Material::setDiffuse( const DiffuseValueType& value )
{
	getFieldRW<FDiffuseType>(getFDiffuse())->setValue( value );
}



void Material::eraseDiffuse()
{
	getFieldRW<FDiffuseType>(getFDiffuse())->eraseValue();
}


const bool Material::hasDiffuse() const
{
	return getFieldRO<FDiffuseType>(getFDiffuse())->hasValue();
}



// Specular

const Material::SpecularValueType Material::DEFAULT_SPECULAR = vgm::Vec3f(0.f, 0.f, 0.f);



const bool Material::getSpecular( SpecularValueType& value ) const
{
	return getFieldRO<FSpecularType>(getFSpecular())->getValue( value );
}



void Material::setSpecular( const SpecularValueType& value )
{
	getFieldRW<FSpecularType>(getFSpecular())->setValue( value );
}



void Material::eraseSpecular()
{
	getFieldRW<FSpecularType>(getFSpecular())->eraseValue();
}


const bool Material::hasSpecular() const
{
	return getFieldRO<FSpecularType>(getFSpecular())->hasValue();
}



// Emission

const Material::EmissionValueType Material::DEFAULT_EMISSION = vgm::Vec3f(0.f, 0.f, 0.f);



const bool Material::getEmission( EmissionValueType& value ) const
{
	return getFieldRO<FEmissionType>(getFEmission())->getValue( value );
}



void Material::setEmission( const EmissionValueType& value )
{
	getFieldRW<FEmissionType>(getFEmission())->setValue( value );
}



void Material::eraseEmission()
{
	getFieldRW<FEmissionType>(getFEmission())->eraseValue();
}


const bool Material::hasEmission() const
{
	return getFieldRO<FEmissionType>(getFEmission())->hasValue();
}



// Shininess

const Material::ShininessValueType Material::DEFAULT_SHININESS = (0.f);



const bool Material::getShininess( ShininessValueType& value ) const
{
	return getFieldRO<FShininessType>(getFShininess())->getValue( value );
}



void Material::setShininess( const ShininessValueType& value )
{
	getFieldRW<FShininessType>(getFShininess())->setValue( value );
}



void Material::eraseShininess()
{
	getFieldRW<FShininessType>(getFShininess())->eraseValue();
}


const bool Material::hasShininess() const
{
	return getFieldRO<FShininessType>(getFShininess())->hasValue();
}



// Field name accessor(s)
const std::string Material::getFOpacity( void )
{
	return "f_opacity";
}



const std::string Material::getFAmbient( void )
{
	return "f_ambient";
}



const std::string Material::getFDiffuse( void )
{
	return "f_diffuse";
}



const std::string Material::getFSpecular( void )
{
	return "f_specular";
}



const std::string Material::getFEmission( void )
{
	return "f_emission";
}



const std::string Material::getFShininess( void )
{
	return "f_shininess";
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

