// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/importer/Reader.hpp"

#include <boost/functional/hash.hpp>
#include <boost/unordered_map.hpp>  

#include <COLLADAFWNode.h>
#include <COLLADAFWVisualScene.h>
#include <COLLADAFWMaterial.h>
#include <COLLADAFWEffect.h>
#include <COLLADAFWSampler.h>
#include <COLLADAFWImage.h>

#include <vgd/basic/Image.hpp>
#include <vgd/node/TransformSeparator.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/visitor/helpers.hpp>
#include <vgd/visitor/predicate/ByRegexName.hpp>
#include <vgd/visitor/predicate/ByType.hpp>
#include <vgDebug/Global.hpp>
#include <vgm/Utilities.hpp>
#include <vgio/Cache.hpp>

#include "vgOpenCOLLADA/importer/GeometryImporter.hpp"
#include "vgOpenCOLLADA/importer/VisualSceneImporter.hpp"

namespace vgOpenCOLLADA
{

namespace importer
{

Reader::Reader(LOAD_TYPE type) :
m_loadType ( type )
{
	m_scene.first = true;
	m_mapShapeMaterial = vgd::makeShp( new boost::unordered_map< vgd::Shp< vgd::node::VertexShape >, int > );
	m_mapMaterialEffect = vgd::makeShp( new boost::unordered_map< std::string, vgd::Shp< vgd::node::Group > > );
	m_mapMaterial = vgd::makeShp( new boost::unordered_map< std::string, vgd::Shp< vgd::node::Group > > );
	m_mapTextures = vgd::makeShp( new boost::unordered_map< std::string, vgd::Shp< vgd::node::Texture2D > > );
}



std::pair< bool, vgd::Shp< vgd::node::Group > > Reader::getScene() 
{ 
	//Disable all container switch
	m_switchVertexShape->setWhichChild( vgd::node::Switch::SWITCH_NONE );
	m_switchMaterial->setWhichChild( vgd::node::Switch::SWITCH_NONE );
	m_switchTexture->setWhichChild( vgd::node::Switch::SWITCH_NONE );	

	return m_scene; 
}



bool Reader::writeGlobalAsset ( const COLLADAFW::FileInfo* asset )
{
	m_inputFile = asset->getAbsoluteFileUri();
	
	//create main group
	m_group = vgd::node::Group::create(asset->getAbsoluteFileUri().getURIString());
	m_scene.second = m_group;

	//create geometry container group
	m_switchVertexShape = vgd::node::Switch::create("geometry");
	m_switchVertexShape->setWhichChild( vgd::node::Switch::SWITCH_ALL ); //SWITCH_ALL to manipulate them during scene construction
	//m_group->addChild( m_switchVertexShape );

	//create material container group
	m_switchMaterial = vgd::node::Switch::create("materials");
	m_switchMaterial->setWhichChild( vgd::node::Switch::SWITCH_ALL ); //SWITCH_ALL to manipulate them during scene construction
	m_group->addChild( m_switchMaterial );

	//create texture container group
	m_switchTexture = vgd::node::Switch::create("textures");
	m_switchTexture->setWhichChild( vgd::node::Switch::SWITCH_ALL ); //SWITCH_ALL to manipulate them during scene construction
	m_group->addChild( m_switchTexture );

	return true;
}



bool Reader::writeVisualScene ( const COLLADAFW::VisualScene* visualScene ) {
	
	//get the root nodes under the visual_scene element
	const COLLADAFW::NodePointerArray& rootNodes = visualScene->getRootNodes();
	vgOpenCOLLADA::importer::VisualSceneImporter importer( m_loadType, m_switchMaterial, m_switchVertexShape, m_mapShapeMaterial, m_mapMaterial );

	//for each node of the rootnode
	for (std::size_t i = 0; i<rootNodes.getCount(); i++) 
	{
		const COLLADAFW::Node* node = rootNodes.getData()[i];
		importer.createNode( node, m_group, node->getName() );
	}
	return true;
}



bool Reader::writeGeometry ( const COLLADAFW::Geometry* geometry )
{
	//@TODO: consider other types of geometry
	if (geometry->getType() == COLLADAFW::Geometry::GEO_TYPE_MESH)
	{
		try 
		{
			vgOpenCOLLADA::importer::GeometryImporter importer( geometry, m_loadType, m_mapShapeMaterial );
			std::pair< bool, vgd::Shp< vgd::node::Group > > retVal = importer.loadMesh();
			
			if ( !retVal.first )
			{
				return false;
			}

			vgd::Shp< vgd::node::Group > group = retVal.second;

			m_switchVertexShape->addChild( group );
		} 
		catch (const std::runtime_error& e) 
		{
			std::cerr << "Exception thrown: " << e.what() << std::endl;
			return false;
		}
	}
	else
	{
		throw std::runtime_error("Only mesh geometries are supported.");
	}
	
	return true;
}



bool Reader::writeMaterial( const COLLADAFW::Material* material )
{
	//called before writeEffect.
	std::string name = material->getInstantiatedEffect().toAscii();
	vgd::Shp< vgd::node::Group > container = vgd::node::Group::create( material->getName() );
	m_switchMaterial->addChild( container );
	(*m_mapMaterialEffect)[material->getInstantiatedEffect().toAscii()] = container;
	(*m_mapMaterial)[material->getUniqueId().toAscii()] = container;

	return true;
}



bool Reader::writeEffect( const COLLADAFW::Effect* effect )
{
	vgd::Shp< vgd::node::Material > material = vgd::node::Material::create( effect->getName() );
	
	if( m_mapMaterialEffect->find( effect->getUniqueId().toAscii() ) == m_mapMaterialEffect->end() )
	{
		return true; //effect is not instanciate.
	}

	vgd::Shp< vgd::node::Group > container = (*m_mapMaterialEffect)[effect->getUniqueId().toAscii()];

	container->addChild( material );
	
	const COLLADAFW::EffectCommon* effectCommon = effect->getCommonEffects().getData()[0];

	vgm::Vec3f color;
	//
	//// ambient
	if( effectCommon->getAmbient().getType() == COLLADAFW::ColorOrTexture::COLOR )
	{
		color[0] = (float)effectCommon->getAmbient().getColor().getRed();
		color[1] = (float)effectCommon->getAmbient().getColor().getGreen();
		color[2] = (float)effectCommon->getAmbient().getColor().getBlue();
		material->setAmbient( color );
	}
	
	//
	//// diffuse
	if( effectCommon->getDiffuse().getType() == COLLADAFW::ColorOrTexture::COLOR )
	{
		color[0] = (float)effectCommon->getDiffuse().getColor().getRed();
		color[1] = (float)effectCommon->getDiffuse().getColor().getGreen();
		color[2] = (float)effectCommon->getDiffuse().getColor().getBlue();
		material->setDiffuse( color );
	}
	else if( effectCommon->getDiffuse().getType() == COLLADAFW::ColorOrTexture::TEXTURE )
	{
		color[0] = 1;
		color[1] = 1;
		color[2] = 1;
		material->setDiffuse( color );
	}

	//
	//// specular
	if( effectCommon->getSpecular().getType() == COLLADAFW::ColorOrTexture::COLOR )
	{
		color[0] = (float)effectCommon->getSpecular().getColor().getRed();
		color[1] = (float)effectCommon->getSpecular().getColor().getGreen();
		color[2] = (float)effectCommon->getSpecular().getColor().getBlue();
		material->setSpecular( color );
	}

	//
	//// emission
	if( effectCommon->getEmission().getType() == COLLADAFW::ColorOrTexture::COLOR )
	{
		color[0] = (float)effectCommon->getEmission().getColor().getRed();
		color[1] = (float)effectCommon->getEmission().getColor().getGreen();
		color[2] = (float)effectCommon->getEmission().getColor().getBlue();
		material->setEmission( color );
	}

	//
	//// specularLevel/glosiness
	float real = 1.f;
	real = effectCommon->getShininess().getFloatValue();
	if( real <= 1 && real >= 0 )
	{
		material->setShininess( real );
	}
	else
	{
		//@todo if > 1 ==> it uses Blinn Phong equation. How to use it? (p. 244 COLLADA Spec).
		///material->setShininess( real );
		material->setShininess( vgm::clamp<float>( real, 0.f, 1.f ) );
	}

	//// transparency
	real = (float)effectCommon->getOpacity().getColor().getAlpha(); //by default (opaque="A_ONE")Takes the transparency information from the color’s alpha channel, where the value 1.0 is opaque. 
	material->setOpacity( real );
	
	//// reflective
	bool reflectiveTypeTexture = false;
	if( effectCommon->getReflective().getType() == COLLADAFW::ColorOrTexture::TEXTURE )
	{
		reflectiveTypeTexture = true;
	}

	if ( m_loadType > LOAD_MATERIAL )
	{
		for (uint i = 0; i < effectCommon->getSamplerPointerArray().getCount(); i++)
		{
			if( reflectiveTypeTexture )
			{
				break;
			}

			const COLLADAFW::Sampler* sampler = effectCommon->getSamplerPointerArray().getData()[i];

			if( m_mapTextures->find( sampler->getSourceImage().toAscii() ) == m_mapTextures->end() )
			{
				assert( false && "Instanciate texture not found." );
				return false;
			}

			vgd::Shp< vgd::node::Texture2D > texture = (*m_mapTextures)[sampler->getSourceImage().toAscii()];
			//@TODO: tex must be a copy of the stored texture because one texture can be used in several materials with different parameters.
			// cloneTexture function was created, but a function to clone Node may be better.
			vgd::Shp< vgd::node::Texture2D > tex = cloneTexture( texture );
			
			container->addChild( tex );

			//WRAP_MODE_UNSPECIFIED=0,
			//// NONE == GL_CLAMP_TO BORDER The defined behavior for NONE is 
			//// consistent with decal texturing where the border is black. 
			//// Mapping this calculation to GL_CLAMP_TO_BORDER is the best 
			//// approximation of this.
			//WRAP_MODE_NONE,
			//// WRAP == GL_REPEAT Ignores the integer part of texture coordinates, 
			//// using only the fractional part.
			//WRAP_MODE_WRAP, 
			//// MIRROR == GL_MIRRORED_REPEAT First mirrors the texture coordinate. 
			//// The mirrored coordinate is then clamped as described for CLAMP_TO_EDGE.
			//WRAP_MODE_MIRROR,
			//// CLAMP == GL_CLAMP_TO_EDGE Clamps texture coordinates at all 
			//// mipmap levels such that the texture filter never samples a 
			//// border texel. Note: GL_CLAMP takes any texels beyond the
			//// sampling border and substitutes those texels with the border 
			//// color. So CLAMP_TO_EDGE is more appropriate. This also works 
			//// much better with OpenGL ES where the GL_CLAMP symbol was removed 
			//// from the OpenGL ES specification.
			//WRAP_MODE_CLAMP,
			//// BORDER GL_CLAMP_TO_BORDER Clamps texture coordinates at all 
			//// MIPmaps such that the texture filter always samples border 
			//// texels for fragments whose corresponding texture coordinate
			//// is sufficiently far outside the range [0, 1].
			//WRAP_MODE_BORDER

			using vgd::node::Texture2D;
			//WRAP_S
			if ( sampler->getWrapS() == COLLADAFW::Sampler::WRAP_MODE_UNSPECIFIED )
			{
				assert(false && "Unspecified wrap mode.");
			}
			else if ( sampler->getWrapS() == COLLADAFW::Sampler::WRAP_MODE_NONE )
			{
				tex->setWrap( Texture2D::WRAP_S, Texture2D::DEFAULT_WRAP );
			}
			else if ( sampler->getWrapS() == COLLADAFW::Sampler::WRAP_MODE_WRAP )
			{
				tex->setWrap( Texture2D::WRAP_S, Texture2D::REPEAT );
			}
			else if ( sampler->getWrapS() == COLLADAFW::Sampler::WRAP_MODE_MIRROR )
			{
				tex->setWrap( Texture2D::WRAP_S, Texture2D::MIRRORED_REPEAT );
			}
			else if ( sampler->getWrapS() == COLLADAFW::Sampler::WRAP_MODE_CLAMP )
			{
				tex->setWrap( Texture2D::WRAP_S, Texture2D::CLAMP_TO_EDGE );
			}
			else if ( sampler->getWrapS() == COLLADAFW::Sampler::WRAP_MODE_BORDER )
			{
				tex->setWrap( Texture2D::WRAP_S, Texture2D::CLAMP_TO_BORDER );
			}
			else
			{
				assert(false && "Unsupported wrap mode.");
			}

			//WRAP_T
			if ( sampler->getWrapT() == COLLADAFW::Sampler::WRAP_MODE_UNSPECIFIED )
			{
				assert(false && "Unspecified wrap mode.");
			}
			else if ( sampler->getWrapT() == COLLADAFW::Sampler::WRAP_MODE_NONE )
			{
				tex->setWrap( Texture2D::WRAP_T, Texture2D::DEFAULT_WRAP );
			}
			else if ( sampler->getWrapT() == COLLADAFW::Sampler::WRAP_MODE_WRAP )
			{
				tex->setWrap( Texture2D::WRAP_T, Texture2D::REPEAT );
			}
			else if ( sampler->getWrapT() == COLLADAFW::Sampler::WRAP_MODE_MIRROR )
			{
				tex->setWrap( Texture2D::WRAP_T, Texture2D::MIRRORED_REPEAT );
			}
			else if ( sampler->getWrapT() == COLLADAFW::Sampler::WRAP_MODE_CLAMP )
			{
				tex->setWrap( Texture2D::WRAP_T, Texture2D::CLAMP_TO_EDGE );
			}
			else if ( sampler->getWrapT() == COLLADAFW::Sampler::WRAP_MODE_BORDER )
			{
				tex->setWrap( Texture2D::WRAP_T, Texture2D::CLAMP_TO_BORDER );
			}
			else
			{
				assert(false && "Unsupported wrap mode.");
			}

			tex->sethFunction( Texture2D::FUN_MODULATE );
		}
	}

 	return true;
}



bool Reader::writeImage( const COLLADAFW::Image* image )
{
	vgd::Shp< vgd::node::Texture2D > tex = vgd::node::Texture2D::create( image->getName() );
	//tex->setMultiAttributeIndex( (int8)0 ); //@todo manage multi textures

	//@todo manage full path. Only works with relative path atm.
	std::string path = m_inputFile.getPathDir() + image->getImageURI().getPath();
	path = path.substr(1); //removes first /

	path = COLLADABU::URI::uriDecode(path);

	vgd::Shp< vgd::basic::Image > img ( new vgd::basic::Image ( path ) );

	img->flip();

	tex->setImage( vgd::Shp< vgd::basic::Image >(img) );

	//// default value.
	using vgd::node::Texture2D;
	tex->setMipmap( true );
	tex->setFilter( Texture2D::MIN_FILTER, Texture2D::LINEAR_MIPMAP_LINEAR );
	tex->setFilter( Texture2D::MAG_FILTER, Texture2D::LINEAR );
	
	m_switchTexture->addChild( tex );
	(*m_mapTextures)[image->getUniqueId().toAscii()] = tex;

	return true;
}



// @todo copy fields from the given texture
vgd::Shp< vgd::node::Texture2D > Reader::cloneTexture(vgd::Shp< vgd::node::Texture2D > texture)
{
	vgd::Shp< vgd::node::Texture2D > tex = vgd::node::Texture2D::create( texture->getName() );

	vgd::Shp< vgd::basic::IImage > img;

	texture->getImage( img );

	tex->setImage( img );

	//// default value.
	using vgd::node::Texture2D;
	tex->setMipmap( true );
	tex->setFilter( Texture2D::MIN_FILTER, Texture2D::LINEAR_MIPMAP_LINEAR );
	tex->setFilter( Texture2D::MAG_FILTER, Texture2D::LINEAR );	

	return tex;
}


} // namespace importer

} // namespace vgCollada
