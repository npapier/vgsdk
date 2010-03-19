// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/exporter/EffectExporter.hpp"

#include <vgDebug/Global.hpp>
#include <vgd/visitor/helpers.hpp>


namespace vgOpenCOLLADA
{

namespace exporter
{
	
EffectExporter::EffectExporter(COLLADASW::StreamWriter * streamWriter, vgd::Shp< vgd::node::Group > sceneGraph, bool exportVertexShape) :
COLLADASW::LibraryEffects ( streamWriter ),
m_sceneGraph( sceneGraph ),
m_exportVertexShape( exportVertexShape )
{
}

void EffectExporter::doExport()
{
	vgDebug::get().logDebug("Exporting effects");
	openLibrary();

	if ( m_exportVertexShape )
	{
		//export vertexShape only ==> export default effect.
		vgd::Shp< vgd::node::Material > effect = vgd::node::Material::create( "default" );
		vgm::Vec3f color;
		color[0] = 1.0f;
		color[1] = 1.0f;
		color[2] = 1.0f;

		effect->setAmbient( color );
		effect->setDiffuse( color );
		effect->setSpecular( color );
		effect->setEmission( color );
		effect->setShininess( 1.0f );
		effect->setOpacity( 1.0f );

		exportSimpleEffect( effect );
	}
	else
	{
		//@todo: export all effects
	}

	closeLibrary();
}

void EffectExporter::exportSimpleEffect( vgd::Shp< vgd::node::Material > effect )
{
	m_currentEffectName = COLLADASW::Utils::checkNCName( COLLADASW::NativeString( effect->getName() ) );	
	openEffect ( m_currentEffectName );
	
	m_effectIdList.push_back( m_currentEffectName );

	COLLADASW::EffectProfile effectProfile ( mSW );

	//@todo: consider other type of effect
	exportColorEffect( effect, effectProfile);

	addEffectProfile ( effectProfile );

	closeEffect();
}


void EffectExporter::exportColorEffect( vgd::Shp< vgd::node::Material > effect, COLLADASW::EffectProfile &effectProfile )
{
    effectProfile.setShaderType ( COLLADASW::EffectProfile::PHONG );

	vgm::Vec3f color;

	effect->getAmbient(color);
    COLLADASW::Color ambiantColor ( color[0], color[1], color[2] );
    effectProfile.setAmbient ( COLLADASW::ColorOrTexture ( ambiantColor ) );

	effect->getDiffuse(color);
    COLLADASW::Color diffuseColor ( color[0], color[1], color[2] );
    effectProfile.setDiffuse ( COLLADASW::ColorOrTexture ( diffuseColor ) );

	effect->getSpecular(color);
    COLLADASW::Color specularColor ( color[0], color[1], color[2] );
    effectProfile.setSpecular ( COLLADASW::ColorOrTexture ( specularColor ) );

	float real;
	effect->getShininess( real );
    effectProfile.setShininess ( real );

    effectProfile.setTransparent ( COLLADASW::ColorOrTexture ( COLLADASW::Color::WHITE ) );
    effectProfile.setTransparency ( 1.0 );
    effectProfile.setReflective ( COLLADASW::ColorOrTexture ( COLLADASW::Color::BLACK ) );
}


std::vector<std::string> EffectExporter::getEffectIdList()
{
	return m_effectIdList;
}

} // namespace exporter

} // namespace vgOpenCOLLADA

