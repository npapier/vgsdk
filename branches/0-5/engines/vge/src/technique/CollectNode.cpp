// VGSDK - Copyright (C) 2010, Nicolas Papier, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vge/technique/CollectNode.hpp"

#include "vge/pass/ForEach.hpp"
#include "vge/service/Basic.hpp"
#include "vge/engine/Engine.hpp"


#include <vgd/node/Material.hpp>
#include <vgd/node/MatrixTransform.hpp>
#include <vgd/node/MultipleInstances.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vgd/node/TextureMatrixTransform.hpp>
#include <vgd/node/VertexShape.hpp>



namespace vge
{

namespace technique
{


//CollectNode technique.
void CollectNode::apply( vge::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements )
{
	vgd::Shp< vge::service::Service > service = vge::service::Basic::create();

	std::vector< vgd::Shp< vgd::node::GeometricalTransformation > >* transformList = new std::vector< vgd::Shp< vgd::node::GeometricalTransformation > >();

	prepareEval( engine, traverseElements );

	assert( service != 0 );
	assert( engine != 0 );

	beginPass( PassIsolationMask(0) );

	//assert( m_engine != 0 );
	assert( getTraverseElements() != 0 );

	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			i != iEnd;
			++i )
	{
		if( i->first->isAKindOf< vgd::node::VertexShape >() && i->second )
		{
			vgd::node::Node * node = dynamic_cast< vgd::node::Node * >( i->first );
			vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::dynamic_pointer_cast< vgd::node::VertexShape >( node->shpFromThis() );
			vgm::MatrixR matrix( engine->getGeometricalMatrix().getTop() );

			//if empty shape.
			if( vertexShape->getFVertexIndexRO()->size() > 0 )
			{
				addShape( vertexShape, matrix, engine, VERTEXSHAPE );
			}
		}
		else if( i->first->isA< vgd::node::MultipleInstances >() && i->second )
		{
			vgd::node::MultipleInstances * multipleInstance = dynamic_cast< vgd::node::MultipleInstances * >( i->first );

			vgd::Shp< vgd::node::Node > shape = multipleInstance->getShape();

			if( shape->isAKindOf< vgd::node::VertexShape >() )
			{
				vgd::Shp< vgd::node::MultipleInstances > multipleInstances = vgd::dynamic_pointer_cast< vgd::node::MultipleInstances >( multipleInstance->shpFromThis() );

				//if empty shape.
				if( vgd::dynamic_pointer_cast< vgd::node::VertexShape >( shape )->getFVertexIndexRO()->size() > 0 )
				{
					vgm::MatrixR matrix = engine->getGeometricalMatrix().getTop();
					addShape( multipleInstances, matrix, engine, MULTIPLEINSTANCES );				
				}
			}

		}
		engine->evaluate( service, i->first, i->second );
		
	}

	endPass();

	finishEval();
}



void CollectNode::addShape( vgd::Shp< vgd::node::Shape > shape, vgm::MatrixR matrix, vge::engine::Engine * engine, SHAPE_TYPE shapeType )
{
	vge::engine::Engine::NodeList* materialList = engine->getNodeListFromStateStackTop< vgd::node::Material >();
	vge::engine::Engine::NodeList* textureList = engine->getNodeListFromStateStackTop< vgd::node::Texture2D >();
	vge::engine::Engine::NodeList* textureTransformList = engine->getNodeListFromStateStackTop< vgd::node::TextureMatrixTransform >();


	//texture
	vgd::Shp< vgd::node::Texture2D > texture;
	
	//check if vertexshape has texture coordinate
	bool needTexture = false;
	vgd::Shp< vgd::node::VertexShape > vertexShape;
	if( shape->isAKindOf< vgd::node::VertexShape >() )
	{
		vertexShape = vgd::dynamic_pointer_cast< vgd::node::VertexShape >( shape );
	}
	else if( shape->isA< vgd::node::MultipleInstances >() )
	{
		vertexShape = vgd::dynamic_pointer_cast< vgd::node::VertexShape >( vgd::dynamic_pointer_cast< vgd::node::MultipleInstances >( shape )->getShape() );
	}

	if( vertexShape->getNumTexUnits() > 0 )
	{
		needTexture = true;

		//applies texture transformation
		if( textureTransformList->size() > 1 )
		{
			vgd::node::TextureMatrixTransform* textureTransform = dynamic_cast< vgd::node::TextureMatrixTransform* >( textureTransformList->back() );
			vertexShape->textureTransform( textureTransform->getMatrix(), textureTransform->getMultiAttributeIndex() );
		}
	}

	if( needTexture )
	{
		if( textureList->size() > 1 ) // == 1: default node only.
		{
			texture = vgd::node::Texture2D::create();
			
			vgd::node::Texture::InternalFormatValueType internalFormat;
			engine->getStateStackTopFromSingleField< vgd::node::Texture2D, vgd::node::Texture::FInternalFormatType, vgd::node::Texture::InternalFormatValueType >( "f_internalFormat", internalFormat );

			vgd::node::Texture::UsageValueType usage;
			engine->getStateStackTopFromSingleField< vgd::node::Texture2D, vgd::node::Texture::FUsageType, vgd::node::Texture::UsageValueType >( "f_usage", usage );

			vgd::node::Texture::FunctionValueType function;
			if( engine->getStateStackTopFromOptionalField< vgd::node::Texture2D, vgd::node::Texture::FFunctionType, vgd::node::Texture::FunctionValueType >( "f_function", function, false ) )
			{
				texture->setFunction( function );
			}

			vgd::node::Texture::ImageValueType image;
			if( engine->getStateStackTopFromOptionalField< vgd::node::Texture2D, vgd::node::Texture::FImageType, vgd::node::Texture::ImageValueType >( "f_image", image, false ) )
			{
				texture->setImage( image );
			}

			vgd::node::Texture::MipmapValueType mipmap;
			if( engine->getStateStackTopFromOptionalField< vgd::node::Texture2D, vgd::node::Texture::FMipmapType, vgd::node::Texture::MipmapValueType >( "f_mipmap", mipmap ) )
			{
				texture->setMipmap( mipmap );
			}

			vgd::node::Texture::WrapValueType wrap_s;
			engine->getStateStackTop< vgd::node::Texture2D, vgd::node::Texture::WrapParameterType, vgd::node::Texture::WrapValueType >( "f_wrap", vgd::node::Texture::WRAP_S, wrap_s );

			vgd::node::Texture::WrapValueType wrap_t;
			engine->getStateStackTop< vgd::node::Texture2D, vgd::node::Texture::WrapParameterType, vgd::node::Texture::WrapValueType >( "f_wrap", vgd::node::Texture::WRAP_T, wrap_t );

			vgd::node::Texture::FilterValueType min_filter;
			engine->getStateStackTop< vgd::node::Texture2D, vgd::node::Texture::FilterParameterType, vgd::node::Texture::FilterValueType >( "f_filter", vgd::node::Texture::MIN_FILTER, min_filter );

			vgd::node::Texture::FilterValueType mag_filter;
			engine->getStateStackTop< vgd::node::Texture2D, vgd::node::Texture::FilterParameterType, vgd::node::Texture::FilterValueType >( "f_filter", vgd::node::Texture::MAG_FILTER, mag_filter );

			std::string texName;
			engine->getStateStackTopFromSingleField< vgd::node::Texture2D, vgd::field::TSingleField< std::string >, std::string >( "f_name", texName );

			texture->setName( texName );
			texture->setInternalFormat( internalFormat );
			texture->setUsage( usage );
			texture->setWrap( vgd::node::Texture::WRAP_S, wrap_s );
			texture->setWrap( vgd::node::Texture::WRAP_T, wrap_t );
			texture->setFilter( vgd::node::Texture::MIN_FILTER, min_filter );
			texture->setFilter( vgd::node::Texture::MAG_FILTER, mag_filter );
		}
	}

	//material
	vgd::Shp< vgd::node::Material > material;

	if( materialList->size() > 1 ) // == 1: default node only.
	{
		material = vgd::node::Material::create();
		
		vgd::node::Material::OpacityValueType opacity;
		if( engine->getStateStackTopFromSingleField< vgd::node::Material, vgd::node::Material::FOpacityType, vgd::node::Material::OpacityValueType >( "f_opacity", opacity ) )
		{
			material->setOpacity( opacity );
		}
		
		vgd::node::Material::ShininessValueType shininess;
		if( engine->getStateStackTopFromOptionalField< vgd::node::Material, vgd::node::Material::FShininessType, vgd::node::Material::ShininessValueType >( "f_shininess", shininess, false ) )
		{
			material->setShininess( shininess );
		}

		vgd::node::Material::EmissionValueType emission;
		if( engine->getStateStackTopFromOptionalField< vgd::node::Material, vgd::node::Material::FEmissionType, vgd::node::Material::EmissionValueType >( "f_emission", emission, false ) )
		{
			material->setEmission( emission );
		}

		vgd::node::Material::DiffuseValueType diffuse;
		if( engine->getStateStackTopFromOptionalField< vgd::node::Material, vgd::node::Material::FDiffuseType, vgd::node::Material::DiffuseValueType >( "f_diffuse", diffuse, false ) )
		{
			material->setDiffuse( diffuse );
		}

		vgd::node::Material::SpecularValueType specular;
		if( engine->getStateStackTopFromOptionalField< vgd::node::Material, vgd::node::Material::FSpecularType, vgd::node::Material::SpecularValueType >( "f_specular", specular, false ) )
		{
			material->setSpecular( specular );
		}

		vgd::node::Material::AmbientValueType ambient;
		if(	engine->getStateStackTopFromOptionalField< vgd::node::Material, vgd::node::Material::FAmbientType, vgd::node::Material::AmbientValueType >( "f_ambient", ambient, false ) )
		{
			material->setAmbient( ambient );
		}

		std::string matName;
		if( engine->getStateStackTopFromSingleField< vgd::node::Material, vgd::field::TSingleField< std::string >, std::string >( "f_name", matName ) )
		{	
			//check unique mat name @todo create conveniance function to check unique id/name.
			int counter = 0;
			std::stringstream ss;
			ss.str( matName );
			while( !m_matNameList.insert( ss.str() ).second )
			{
				ss.str( "" );
				ss << matName << "_" << counter;
				counter++;
			}			
			material->setName( ss.str() );
		}
	}
	else if( needTexture )
	{
		material = vgd::node::Material::createWhole( "mat" + shape->getName() );
	}

	vgd::Shp< vge::technique::CollectedShape > collectedShape( new vge::technique::CollectedShape( shape, matrix, shapeType ) );
	vgd::Shp< vge::technique::CollectedMaterial > collectedMaterial( new vge::technique::CollectedMaterial( material, texture ) );

	m_collectedMap.insert( collectedMapType::value_type( collectedShape, collectedMaterial ) );
}



collectedMapType CollectNode::getCollectedMap()
{
	return m_collectedMap;
}



//CollectShape storing class
CollectedShape::CollectedShape(	vgd::Shp< vgd::node::Shape > shape, vgm::MatrixR geometricalMatrix, SHAPE_TYPE shapeType )
:	m_shape( shape ),
	m_shapeType( shapeType ),
	m_geometricalMatrix( geometricalMatrix )
{
}



CollectedShape::~CollectedShape()
{
	//m_shape.reset();
}



vgd::Shp< vgd::node::Shape > CollectedShape::getShape()
{
	return m_shape;
}



SHAPE_TYPE CollectedShape::getShapeType()
{
	return m_shapeType;
}



std::string CollectedShape::getColladaShapeName()
{
	return m_colladaShapeName;
}



void CollectedShape::setColladaShapeName( std::string colladaShapeName )
{
	m_colladaShapeName = colladaShapeName;
}



vgm::MatrixR CollectedShape::getGeometricalMatrix()
{
	return m_geometricalMatrix;
}




//CollectMaterial storing class
CollectedMaterial::CollectedMaterial(	vgd::Shp< vgd::node::Material > material, vgd::Shp< vgd::node::Texture2D > texture )
:	m_material( material ),
	m_texture( texture )
{
}



CollectedMaterial::~CollectedMaterial()
{
	//m_shape.reset();
}



vgd::Shp< vgd::node::Material >	CollectedMaterial::getMaterial()
{
	return m_material;
}



vgd::Shp< vgd::node::Texture2D > CollectedMaterial::getTexture()
{
	return m_texture;
}



void CollectedMaterial::setEffectId( std::string id )
{
	m_effectId = id;
}



void CollectedMaterial::setMaterialId( std::string id )
{
	m_materialId = id;
}



void CollectedMaterial::setMaterialSymbol( std::string symbol )
{
	m_materialSymbol = symbol;
}



void CollectedMaterial::setImageId( std::string id )
{
	m_imageId = id;
}



std::string	CollectedMaterial::getEffectId()
{
	return m_effectId;
}



std::string CollectedMaterial::getMaterialId()
{
	return m_materialId;
}



std::string CollectedMaterial::getMaterialSymbol()
{
	return m_materialSymbol;
}



std::string CollectedMaterial::getImageId()
{
	return m_imageId;
}



} // namespace technique

} // namespace vge
