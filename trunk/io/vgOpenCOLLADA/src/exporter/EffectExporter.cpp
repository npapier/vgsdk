// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/exporter/EffectExporter.hpp"

#include <COLLADASWSampler.h>

#include <vgDebug/Global.hpp>
#include <vgd/visitor/helpers.hpp>


namespace vgOpenCOLLADA
{

namespace exporter
{
	
EffectExporter::EffectExporter( COLLADASW::StreamWriter * streamWriter, collectedMapType collectedMap, vgOpenCOLLADA::Settings exportSettings ) :
COLLADASW::LibraryEffects ( streamWriter ),
m_collectedMap( collectedMap ),
m_exportSettings( exportSettings )
{
}

void EffectExporter::doExport()
{
	vgDebug::get().logDebug("Exporting effects");
	openLibrary();

	if( m_exportSettings.getLevel() > GEOMETRY )
	{
		typedef collectedMapType::right_map::const_iterator right_const_iterator;

		for( right_const_iterator right_iter = m_collectedMap.right.begin(), iend = m_collectedMap.right.end();
			 right_iter != iend; ++right_iter )
		{
			vgd::Shp< vge::technique::CollectedMaterial > collectedMaterial = right_iter->first;
			exportSimpleEffect( collectedMaterial );
		}
	}
	else
	{
		vgd::Shp< vge::technique::CollectedMaterial > collectedMaterial = vgd::makeShp( new vge::technique::CollectedMaterial( vgd::node::Material::createWhole(), vgd::node::Texture2D::createWhole() ) );
		exportSimpleEffect( collectedMaterial );
	}

	closeLibrary();
}

void EffectExporter::exportSimpleEffect( vgd::Shp< vge::technique::CollectedMaterial > collectedMaterial )
{
	vgd::Shp< vgd::node::Material > material = collectedMaterial->getMaterial();
	vgd::Shp< vgd::node::Texture2D > texture = collectedMaterial->getTexture();	
	
	if( material )
	{

		m_currentEffectName = COLLADASW::Utils::checkNCName( COLLADASW::NativeString( material->getName() ) );	

		collectedMaterial->setEffectId( m_currentEffectName );

		openEffect ( m_currentEffectName );

		COLLADASW::EffectProfile effectProfile ( mSW );

		effectProfile.setProfileType( COLLADASW::EffectProfile::COMMON );

		//@todo: consider other type of effect

		exportColorEffect( material, effectProfile);

		if( texture && m_exportSettings.getLevel() > MATERIAL )
		{
			exportTextureEffect( collectedMaterial, effectProfile );
		}

		addEffectProfile ( effectProfile );

		closeEffect();
	}
}


void EffectExporter::exportColorEffect( vgd::Shp< vgd::node::Material > material, COLLADASW::EffectProfile &effectProfile )
{
    effectProfile.setShaderType ( COLLADASW::EffectProfile::BLINN );

	vgm::Vec3f color;

	if( material->hasAmbient() )
	{
		material->getAmbient(color);
		COLLADASW::Color ambientColor ( color[0], color[1], color[2] );
		effectProfile.setAmbient ( COLLADASW::ColorOrTexture ( ambientColor ) );
	}

	if( material->hasDiffuse() )
	{
		material->getDiffuse(color);
		COLLADASW::Color diffuseColor ( color[0], color[1], color[2] );
		effectProfile.setDiffuse ( COLLADASW::ColorOrTexture ( diffuseColor ) );
	}

	if( material->hasEmission() )
	{
		material->getEmission(color);
		COLLADASW::Color emissionColor ( color[0], color[1], color[2] );
		effectProfile.setEmission ( COLLADASW::ColorOrTexture ( emissionColor ) );
	}

	if( material->hasSpecular() )
	{
		material->getSpecular(color);
		COLLADASW::Color specularColor ( color[0], color[1], color[2] );
		effectProfile.setSpecular ( COLLADASW::ColorOrTexture ( specularColor ) );
	}

	float real;
	if( material->hasShininess() )
	{
		material->getShininess( real );
		effectProfile.setShininess ( real );
	}

    //effectProfile.setTransparent ( COLLADASW::ColorOrTexture ( COLLADASW::Color::WHITE ) );
    //effectProfile.setTransparency ( 1.0 );
    //effectProfile.setReflective ( COLLADASW::ColorOrTexture ( COLLADASW::Color::BLACK ) );
}




void EffectExporter::exportTextureEffect( vgd::Shp< vge::technique::CollectedMaterial > collectedMaterial, COLLADASW::EffectProfile &effectProfile )
{
	std::string imageId = collectedMaterial->getImageId();
	vgd::Shp< vgd::node::Texture2D > tex = collectedMaterial->getTexture();	

	COLLADASW::Texture texture ( imageId );

    // Create the sampler
    std::string samplerSid = imageId + COLLADASW::Sampler::SAMPLER_SID_SUFFIX;
    std::string surfaceSid = imageId + COLLADASW::Sampler::SURFACE_SID_SUFFIX;
    COLLADASW::Sampler sampler( COLLADASW::Sampler::SAMPLER_TYPE_2D, samplerSid, surfaceSid );
	sampler.setImageId( imageId );

	using vgd::node::Texture2D;
	Texture2D::WrapValueType wrap_s;
	Texture2D::WrapValueType wrap_t;
	tex->getWrap( Texture2D::WRAP_S, wrap_s );
	tex->getWrap( Texture2D::WRAP_T, wrap_t );

	//WRAP_S
	if ( wrap_s == Texture2D::DEFAULT_WRAP )
	{
		sampler.setWrapS( COLLADASW::Sampler::WRAP_MODE_NONE );
	}
	else if ( wrap_s == Texture2D::REPEAT )
	{
		sampler.setWrapS( COLLADASW::Sampler::WRAP_MODE_WRAP );
	}
	else if ( wrap_s == Texture2D::MIRRORED_REPEAT )
	{
		sampler.setWrapS( COLLADASW::Sampler::WRAP_MODE_MIRROR );
	}
	else if ( wrap_s == Texture2D::CLAMP_TO_EDGE )
	{
		sampler.setWrapS( COLLADASW::Sampler::WRAP_MODE_CLAMP );
	}
	else if ( wrap_s == Texture2D::CLAMP_TO_BORDER )
	{
		sampler.setWrapS( COLLADASW::Sampler::WRAP_MODE_BORDER );
	}
	else
	{
		//assert(false && "Unsupported wrap mode.");
		sampler.setWrapS( COLLADASW::Sampler::WRAP_MODE_NONE );
	}

	//WRAP_T
	if ( wrap_t == Texture2D::DEFAULT_WRAP )
	{
		sampler.setWrapT( COLLADASW::Sampler::WRAP_MODE_NONE );
	}
	else if ( wrap_t == Texture2D::REPEAT )
	{
		sampler.setWrapT( COLLADASW::Sampler::WRAP_MODE_WRAP );
	}
	else if ( wrap_t == Texture2D::MIRRORED_REPEAT )
	{
		sampler.setWrapT( COLLADASW::Sampler::WRAP_MODE_MIRROR );
	}
	else if ( wrap_t == Texture2D::CLAMP_TO_EDGE )
	{
		sampler.setWrapT( COLLADASW::Sampler::WRAP_MODE_CLAMP );
	}
	else if ( wrap_t == Texture2D::CLAMP_TO_BORDER )
	{
		sampler.setWrapT( COLLADASW::Sampler::WRAP_MODE_BORDER );
	}
	else
	{
		//assert(false && "Unsupported wrap mode.");
		sampler.setWrapT( COLLADASW::Sampler::WRAP_MODE_NONE );
	}
	
	texture.setSampler( sampler );

    texture.setTexcoord ( "CHANNEL1" ); //@todo manage multitexture
	
	
	//effectProfile.addSampler( texture );
	//texture.setProfileName("vgsdkCOLLADAExporter");
	//texture.setChildElementName("bump");
	//effectProfile.setExtraTechniqueColorOrTexture(COLLADASW::ColorOrTexture(texture)); 

	effectProfile.setDiffuse( COLLADASW::ColorOrTexture ( texture ) );

}



} // namespace exporter

} // namespace vgOpenCOLLADA

