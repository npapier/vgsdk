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

			addShape( vertexShape, matrix, engine );
		}
		else if( i->first->isA< vgd::node::MultipleInstances >() && i->second )
		{
			vgd::node::MultipleInstances * multipleInstance = dynamic_cast< vgd::node::MultipleInstances * >( i->first );

			vgd::Shp< vgd::node::Node > shape = multipleInstance->getShape();

			if( shape->isAKindOf< vgd::node::VertexShape >() )
			{
				vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::dynamic_pointer_cast< vgd::node::VertexShape >( shape->shpFromThis() );

				vgd::field::EditorRO< vgd::node::MultipleInstances::FMatrixType > matrixEdit = multipleInstance->getMatrixRO();
				for( uint it = 0; it < matrixEdit->size(); it++ )
				{
					vgm::MatrixR matrix = (*matrixEdit)[it];
					matrix.multRight( engine->getGeometricalMatrix().getTop() );
					addShape( vertexShape, matrix, engine );
				}
			}

		}
		engine->evaluate( service, i->first, i->second );
		
	}

	endPass();

	finishEval();
}



void CollectNode::addShape( vgd::Shp< vgd::node::VertexShape > shape, vgm::MatrixR matrix, vge::engine::Engine * engine )
{
	vge::engine::Engine::NodeList* materialList = engine->getNodeListFromStateStackTop< vgd::node::Material >();
	vge::engine::Engine::NodeList* textureList = engine->getNodeListFromStateStackTop< vgd::node::Texture2D >();

	//material
	vgd::Shp< vgd::node::Material > material;
	
	if( materialList->size() > 1 )
	{
		materialList->pop_front(); //remove default node

		material = vgd::node::Material::create();
		
		vgd::node::Material::OpacityValueType opacity;
		if( engine->getStateStackTopFromSingleField< vgd::node::Material, vgd::node::Material::FOpacityType, vgd::node::Material::OpacityValueType >( "f_opacity", opacity ) )
		{
			material->setOpacity( opacity );
		}
		
		vgd::node::Material::ShininessValueType shininess;
		if( engine->getStateStackTopFromOptionalField< vgd::node::Material, vgd::node::Material::FShininessType, vgd::node::Material::ShininessValueType >( "f_shininess", shininess ) )
		{
			material->setShininess( shininess );
		}

		vgd::node::Material::EmissionValueType emission;
		if( engine->getStateStackTopFromOptionalField< vgd::node::Material, vgd::node::Material::FEmissionType, vgd::node::Material::EmissionValueType >( "f_emission", emission ) )
		{
			material->setEmission( emission );
		}

		vgd::node::Material::DiffuseValueType diffuse;
		if( engine->getStateStackTopFromOptionalField< vgd::node::Material, vgd::node::Material::FDiffuseType, vgd::node::Material::DiffuseValueType >( "f_diffuse", diffuse ) )
		{
			material->setDiffuse( diffuse );
		}

		vgd::node::Material::SpecularValueType specular;
		if( engine->getStateStackTopFromOptionalField< vgd::node::Material, vgd::node::Material::FSpecularType, vgd::node::Material::SpecularValueType >( "f_specular", specular ) )
		{
			material->setSpecular( specular );
		}

		vgd::node::Material::AmbientValueType ambient;
		if(	engine->getStateStackTopFromOptionalField< vgd::node::Material, vgd::node::Material::FAmbientType, vgd::node::Material::AmbientValueType >( "f_ambient", ambient ) )
		{
			material->setAmbient( ambient );
		}

		vgd::node::Material::TransparencyValueType transparency;
		if( engine->getStateStackTopFromSingleField< vgd::node::Material, vgd::node::Material::FTransparencyType, vgd::node::Material::TransparencyValueType >( "f_transparency", transparency ) )
		{
			material->setTransparency( transparency );
		}

		std::string matName;
		if( engine->getStateStackTopFromSingleField< vgd::node::Material, vgd::field::TSingleField< std::string >, std::string >( "f_name", matName ) )
		{	
			material->setName( matName );
		}
	}


	//texture
	vgd::Shp< vgd::node::Texture2D > texture;
	if( textureList->size() > 1 ) //if == 1, only default texture.
	{
		vgd::node::Texture::InternalFormatValueType internalFormat;
		engine->getStateStackTopFromSingleField< vgd::node::Texture2D, vgd::node::Texture::FInternalFormatType, vgd::node::Texture::InternalFormatValueType >( "f_internalFormat", internalFormat );

		vgd::node::Texture::UsageValueType usage;
		engine->getStateStackTopFromSingleField< vgd::node::Texture2D, vgd::node::Texture::FUsageType, vgd::node::Texture::UsageValueType >( "f_usage", usage );

		vgd::node::Texture::FunctionValueType function;
		engine->getStateStackTopFromOptionalField< vgd::node::Texture2D, vgd::node::Texture::FFunctionType, vgd::node::Texture::FunctionValueType >( "f_function", function );

		vgd::node::Texture::ImageValueType image;
		engine->getStateStackTopFromOptionalField< vgd::node::Texture2D, vgd::node::Texture::FImageType, vgd::node::Texture::ImageValueType >( "f_image", image );

		vgd::node::Texture::MipmapValueType mipmap;
		engine->getStateStackTopFromOptionalField< vgd::node::Texture2D, vgd::node::Texture::FMipmapType, vgd::node::Texture::MipmapValueType >( "f_mipmap", mipmap );

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

		texture = vgd::node::Texture2D::create( texName );
		texture->setInternalFormat( internalFormat );
		texture->setUsage( usage );
		texture->setFunction( function );
		texture->setImage( image );
		texture->setMipmap( mipmap );
		texture->setWrap( vgd::node::Texture::WRAP_S, wrap_s );
		texture->setWrap( vgd::node::Texture::WRAP_T, wrap_t );
		texture->setFilter( vgd::node::Texture::MIN_FILTER, min_filter );
		texture->setFilter( vgd::node::Texture::MAG_FILTER, mag_filter );
	}

	vgd::Shp< vge::technique::CollectedShape > collectedShape( new vge::technique::CollectedShape( shape, matrix ) );
	m_collectedShapeList.push_back( collectedShape );

	vgd::Shp< vge::technique::CollectedMaterial > collectedMaterial( new vge::technique::CollectedMaterial( material, texture ) );

	m_collectedMap.insert( collectedMapType::value_type( collectedShape, collectedMaterial ) );

	engine->resetStateStack(); // @todo FIX ME	
}



std::list< vgd::Shp< vge::technique::CollectedShape > > CollectNode::getCollectedShapeList()
{
	return m_collectedShapeList;
}



collectedMapType CollectNode::getCollectedMap()
{
	return m_collectedMap;
}



//CollectShape storing class
CollectedShape::CollectedShape(	vgd::Shp< vgd::node::VertexShape > shape, vgm::MatrixR geometricalMatrix )
:	m_shape( shape ),
	m_geometricalMatrix( geometricalMatrix )
{
}



CollectedShape::~CollectedShape()
{
	//m_shape.reset();
}



vgd::Shp< vgd::node::VertexShape > CollectedShape::getShape()
{
	return m_shape;
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
