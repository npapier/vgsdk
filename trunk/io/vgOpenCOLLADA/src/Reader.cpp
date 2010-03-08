// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/Reader.hpp"

#include <vgd/visitor/helpers.hpp>
#include <vgd/visitor/predicate/ByRegexName.hpp>
#include <vgd/node/Transform.hpp>
#include <vgd/node/TransformSeparator.hpp>
#include <vgd/node/MatrixTransform.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vgm/Matrix.hpp>
#include <vgio/Cache.hpp>

#include <boost/functional/hash.hpp>
#include <boost/unordered_map.hpp>  

#include <COLLADAFWNode.h>
#include <COLLADAFWVisualScene.h>
#include <COLLADAFWMaterial.h>
#include <COLLADAFWEffect.h>
#include <COLLADAFWSampler.h>
#include <COLLADAFWImage.h>

#include <COLLADAFWRotate.h>
#include <COLLADAFWTranslate.h>
#include <COLLADAFWScale.h>
#include <COLLADAFWMatrix.h>
#include <COLLADAFWLookAt.h>

namespace vgOpenCOLLADA
{


Reader::Reader(LOAD_TYPE type) :
m_loadType ( type )
{
	m_scene.first = true;
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

	//for each node of the rootnode
	for (std::size_t i = 0; i<rootNodes.getCount(); i++) 
	{
		const COLLADAFW::Node* node = rootNodes.getData()[i];

		createNode(node, m_group);
	}
	return true;
}

void Reader::createNode(const COLLADAFW::Node* node, vgd::Shp< vgd::node::Group > vgsdkNode)
{
	vgd::Shp< vgd::node::Group > vgsdkSubNode;
	//if direct child of the rootnode, we create a TransformSeparator (to prevent from geometry transformation..)
	if(vgsdkNode == m_group)
	{
		vgsdkSubNode = vgd::node::TransformSeparator::create(node->getName());
	}
	//else create normal group.
	else
	{
		vgsdkSubNode = vgd::node::Group::create(node->getName());
	}

	vgsdkNode->addChild(vgsdkSubNode);

	createNodeTransformation(node, vgsdkSubNode);

	createNodeGeometry(node, vgsdkSubNode);


	//recurcivity for child node.
	const COLLADAFW::NodePointerArray& childNodes = node->getChildNodes();
	for (std::size_t i = 0; i< childNodes.getCount(); i++) 
	{
		if (childNodes.getData()[i]->getType() == COLLADAFW::Node::NODE)
		{
			createNode(childNodes.getData()[i], vgsdkSubNode);
		}
		else
		{
			continue;
		}
	}
}

void Reader::createNodeTransformation( const COLLADAFW::Node* node, vgd::Shp< vgd::node::Group > vgsdkNode )
{
	const COLLADAFW::TransformationPointerArray& transformations = node->getTransformations();
	for (std::size_t i = 0; i < transformations.getCount(); i++ )
	{
		const COLLADAFW::Transformation* transformation = transformations.getData()[i];
		if (transformation->getTransformationType() == COLLADAFW::Transformation::MATRIX)
		{

			vgd::Shp< vgd::node::MatrixTransform > t = vgd::node::MatrixTransform::create("matrix");
			const COLLADAFW::Matrix* matrix = static_cast<const COLLADAFW::Matrix* >( transformation );
			vgm::MatrixR m;
			//m.setTranslate( vgm::Vec3f(2,3,4) );

			for (size_t iRow = 0 ;iRow < 4 ; iRow++) 
			{
				for (size_t iCol = 0; iCol < 4; iCol++) 
				{
					m[iRow][iCol] = (float)matrix->getMatrix()[iCol][iRow];
				}
			}

			t->setMatrix(m);

			vgsdkNode->addChild(t);
		}
		else if (transformation->getTransformationType() == COLLADAFW::Transformation::TRANSLATE)
		{
			vgd::Shp< vgd::node::Transform > t = vgd::node::Transform::create("translate");
			const COLLADAFW::Translate* translate = static_cast<const COLLADAFW::Translate* >( transformation );

			float x = static_cast<float >( translate->getTranslation()[0] );
			float y = static_cast<float >( translate->getTranslation()[1] );
			float z = static_cast<float >( translate->getTranslation()[2] );

			vgm::Vec3f translation = vgm::Vec3f(x, y , z);
			t->setTranslation(translation);

			vgsdkNode->addChild(t);
		}
		else if (transformation->getTransformationType() == COLLADAFW::Transformation::ROTATE)
		{
			vgd::Shp< vgd::node::Transform > t = vgd::node::Transform::create("rotate");
			const COLLADAFW::Rotate* rotate = static_cast<const COLLADAFW::Rotate* >( transformation );						

			float x = static_cast<float >( rotate->getRotationAxis()[0] );
			float y = static_cast<float >( rotate->getRotationAxis()[1] );
			float z = static_cast<float >( rotate->getRotationAxis()[2] );

			vgm::Vec3f axis = vgm::Vec3f(x, y , z);

			float angle = static_cast<float >( rotate->getRotationAngle() );
			
			t->setRotation(vgm::Rotation(axis, angle));

			vgsdkNode->addChild(t);
		}
		else if (transformation->getTransformationType() == COLLADAFW::Transformation::SCALE)
		{
			vgd::Shp< vgd::node::Transform > t = vgd::node::Transform::create("scale");

			const COLLADAFW::Scale* scale = static_cast<const COLLADAFW::Scale* >( transformation );

			float x = static_cast<float >( scale->getScale()[0] );
			float y = static_cast<float >( scale->getScale()[1] );
			float z = static_cast<float >( scale->getScale()[2] );

			vgm::Vec3f scaleFactor = vgm::Vec3f(x, y , z);

			t->setScaleFactor(scaleFactor);

			vgsdkNode->addChild(t);
		}
		else if (transformation->getTransformationType() == COLLADAFW::Transformation::LOOKAT)
		{
			//@todo: test it.
			vgd::Shp< vgd::node::MatrixTransform > t = vgd::node::MatrixTransform::create("lookat");
			const COLLADAFW::Lookat* lookat = static_cast<const COLLADAFW::Lookat* >( transformation );
			vgm::MatrixR m = vgm::MatrixR();

			vgm::Vec3f eye = vgm::Vec3f((float)lookat->getEyePosition()[0], (float)lookat->getEyePosition()[1], (float)lookat->getEyePosition()[2]);
			
			vgm::Vec3f center = vgm::Vec3f((float)lookat->getInterestPointPosition()[0], (float)lookat->getInterestPointPosition()[1], (float)lookat->getInterestPointPosition()[2]);					
			
			vgm::Vec3f up = vgm::Vec3f((float)lookat->getUpAxisDirection()[0], (float)lookat->getUpAxisDirection()[1], (float)lookat->getUpAxisDirection()[2]);		
			
			m.setLookAt(eye, center, up);

			t->setMatrix(m);

			vgsdkNode->addChild(t);
		}
		else if (transformation->getTransformationType() == COLLADAFW::Transformation::SKEW)
		{

		}
	}
}

void Reader::createNodeGeometry( const COLLADAFW::Node* node, vgd::Shp< vgd::node::Group > vgsdkNode )
{	
	const COLLADAFW::InstanceGeometryPointerArray& geometries = node->getInstanceGeometries();
	for (std::size_t i = 0; i < geometries.getCount(); i++ )
	{
		const COLLADAFW::UniqueId& id = geometries.getData()[i]->getInstanciatedObjectId();

		//add each material before adding geometry.
		if ( m_loadType > LOAD_TYPE::LOAD_GEOMETRY )
		{
			for (std::size_t j = 0; j < geometries.getData()[i]->getMaterialBindings().getCount(); j++)
			{
				int classId = geometries.getData()[i]->getMaterialBindings().getData()[j].getReferencedMaterial().getClassId();
				int objectId = (int)geometries.getData()[i]->getMaterialBindings().getData()[j].getReferencedMaterial().getObjectId();
				std::stringstream ss;
				ss << "mat:UniqueID\\(" << classId << "," << objectId << "\\)" << ".*";
				std::string regex = ss.str();

				vgd::visitor::predicate::ByRegexName predicate(regex);
				vgd::Shp< vgd::node::Group > material = vgd::visitor::findFirst< vgd::node::Group >( m_switchMaterial, predicate );
				vgsdkNode->addChild( material );
			}
		}

		vgsdkNode->addChild( vgd::visitor::findFirstByName< vgd::node::VertexShape >(m_switchVertexShape, id.toAscii()) );
	}
}

bool Reader::writeGeometry ( const COLLADAFW::Geometry* geometry )
{
	//@TODO: consider other types of geometry
	if (geometry->getType() == COLLADAFW::Geometry::GEO_TYPE_MESH) {
		
		const COLLADAFW::Mesh* mesh = static_cast<const COLLADAFW::Mesh* >( geometry );
		
		try 
		{
			vgd::Shp< vgd::node::VertexShape > vertexShape = loadMesh( geometry, mesh );
			if ( vertexShape->getNormalBinding() != vgd::node::BIND_PER_VERTEX )
			{
				vertexShape->computeNormals();
			}

			m_switchVertexShape->addChild( vertexShape );
		} 
		catch (const std::runtime_error& e) 
		{
			std::cerr << "Exception thrown: " << e.what() << std::endl;
			return false;
		}
	}
	
	return true;
}

vgd::Shp< vgd::node::VertexShape > Reader::loadMesh( const COLLADAFW::Geometry* geometry, const COLLADAFW::Mesh* mesh)
{
	vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::node::VertexShape::create( geometry->getUniqueId().toAscii() );
	
	if (mesh->getPositions().getType() != COLLADAFW::FloatOrDoubleArray::DATA_TYPE_FLOAT) {
		throw std::runtime_error("Position Data types are not float!");
	}
	
	if (mesh->getNormals().getType() != COLLADAFW::FloatOrDoubleArray::DATA_TYPE_FLOAT)
		throw std::runtime_error("Normal Data types are not float!");

	// TRIANGLES
	// read nb of faces
	COLLADAFW::MeshPrimitive* primitives = mesh->getMeshPrimitives()[0];
	//@TODO: consider other types of geometry
	if( primitives->getPrimitiveType() != COLLADAFW::MeshPrimitive::TRIANGLES || primitives->getPrimitiveType() != COLLADAFW::MeshPrimitive::POLYGONS )
	{
		assert("Only triangles/polygons mesh are supported.");
	}
	int32 i32NumTriangles = primitives->getFaceCount();

	// reserve memory for edges.
	// and neighbours FIXME
	vgd::field::EditorRW< vgd::field::MFUInt32>	vertexIndex	= vertexShape->getFVertexIndexRW();	
	vertexIndex->clear();
	vertexIndex->reserve( i32NumTriangles * 3 );

	// VERTEX
	// read nb of vertices
	int32 vertexSize = mesh->getPositions().getValuesCount();
	int32 vertexStride = 3; //mesh->getPositions()->getStride(0); //@todo don't work?!

	vgd::field::EditorRW< vgd::field::MFVec3f >	vertex	= vertexShape->getFVertexRW();

	vertex->clear();
	vertex->reserve( vertexSize / vertexStride );

	const COLLADAFW::FloatArray* verticies = mesh->getPositions().getFloatValues();

	// NORMAL
	// read nb of normals
	int32 normalSize = mesh->getNormals().getValuesCount();
	int32 normalStride = 3; //mesh->getNormals()->getStride(0); //@todo don't work?!

	vgd::field::EditorRW< vgd::field::MFVec3f >	normal = vertexShape->getFNormalRW();

	// read normals
	normal->clear();
	normal->reserve( normalSize / normalStride );
	vertexShape->setNormalBinding( vgd::node::BIND_PER_VERTEX );

	const COLLADAFW::FloatArray* normals = mesh->getNormals().getFloatValues();

	// TEXCOORD
	// read nb of texCoord
	int32 texNumber = primitives->getUVCoordIndicesArray().getCount();
	int32 texCoordSize = mesh->getUVCoords().getValuesCount() / texNumber;
	int32 texCoordStride = 3; //mesh->getUVCoords().getStride(0); //@todo don't work for all files?!

	vertexShape->createTexUnits( 2, 0, 1 );	// ??????????FIXME multitexture multiTexcoord
	vertexShape->setTexCoordBinding( 0, vgd::node::BIND_PER_VERTEX );
	
	// FIXME only for MFVec2f...
	std::vector< vgd::field::EditorRW< vgd::field::MFVec2f > > texCoord;
	for ( int iTex =0; iTex < texNumber; iTex++)
	{
		texCoord.push_back( vertexShape->getFTexCoordRW<vgd::field::MFVec2f>( iTex ) );
		texCoord[iTex]->clear();
		texCoord[iTex]->reserve( texCoordSize / texCoordStride );
	}
	//vgd::field::EditorRW< vgd::field::MFVec2f >	texCoord = vertexShape->getFTexCoordRW<vgd::field::MFVec2f>( 0 );

	// read texCoords
	const COLLADAFW::FloatArray* texCoords = mesh->getUVCoords().getFloatValues();

	// ok go.
	boost::unordered_map<std::size_t, int> hashmap;

	for (int i=0; i < i32NumTriangles * 3; i++ )
	{
		std::vector<float> hash_me;
		const float vX = verticies->getData()[primitives->getPositionIndices()[i] * vertexStride];
		const float vY = verticies->getData()[primitives->getPositionIndices()[i] * vertexStride+1];
		const float vZ = verticies->getData()[primitives->getPositionIndices()[i] * vertexStride+2];
		vgm::Vec3f vVec = vgm::Vec3f(vX, vY, vZ);
		hash_me.push_back(vX);
		hash_me.push_back(vY);
		hash_me.push_back(vZ);

		const float nX = normals->getData()[primitives->getNormalIndices()[i] * normalStride];
		const float nY = normals->getData()[primitives->getNormalIndices()[i] * normalStride+1];
		const float nZ = normals->getData()[primitives->getNormalIndices()[i] * normalStride+2];
		vgm::Vec3f nVec = vgm::Vec3f(nX, nY, nZ).getNormalized();
		hash_me.push_back(nX);
		hash_me.push_back(nY);
		hash_me.push_back(nZ);		

		std::vector< vgm::Vec2f > tVec;
		for ( int iTex = 0; iTex < texNumber; iTex++)
		{
			const float tX = texCoords->getData()[primitives->getUVCoordIndicesArray()[iTex]->getIndices()[i] * texCoordStride];
			const float tY = texCoords->getData()[primitives->getUVCoordIndicesArray()[iTex]->getIndices()[i] * texCoordStride+1];
			tVec.push_back(vgm::Vec2f(tX, tY));
			hash_me.push_back(tX);
			hash_me.push_back(tY);
		}

		//Les "find" font perdre de temps mais permette d'éviter de dupliquer des vertex/normales/coordonnées de texture déjà présente.
		//Faire la même chose en prétraitement du fichier COLLADA
		//Sur la cavité, on passe de 15360 vertex/normales à 2562 ==> ~ divisé par 6.
		//@todo: amélioré l'algorithme de recherche (par hash ou division de la boundingbox);

		//with a hash: very fast
		std::size_t hash = boost::hash_range(hash_me.begin(), hash_me.end());

		if( hashmap.find(hash) != hashmap.end() )
		{
			vertexIndex->push_back( hashmap[hash] );
		}
		else
		{
			vertex->push_back( vVec );
			normal->push_back( nVec );
			for ( int iTex = 0; iTex < texNumber; iTex++)
			{
				texCoord[iTex]->push_back( tVec[iTex] );
			}
			vertexIndex->push_back(vertex->size()-1);
			hashmap[hash] = vertex->size()-1;
		}

		//VERY slow way:
		//int s = vertex->size();
		//int vI = vertex->find(vVec);
		//bool createVertex = true;
		//if( vI != s )
		//{
		//	int nI = normal->find(nVec);
		//	if( vI == nI )
		//	{
		//		int tI = texCoord->find(tVec);
		//		if( vI == tI )
		//		{
		//			vertexIndex->push_back(vI);
		//			createVertex = false;
		//		}
		//	}
		//}
		//
		//if ( createVertex )
		//{
		//	vertex->push_back( vVec );
		//	normal->push_back( nVec );
		//	texCoord->push_back( tVec );
		//	vertexIndex->push_back(vertex->size()-1);
		//}

		//non optimized way (fast):
		//vertex->push_back( vVec );
		//normal->push_back( nVec );
		//texCoord->push_back( tVec );
		//vertexIndex->push_back(vertex->size()-1);
	}

	// primitive
	vgd::field::EditorRW< vgd::field::MFPrimitive >	primitive = vertexShape->getFPrimitiveRW();
	primitive->clear();

	vgd::node::Primitive prim( vgd::node::Primitive::TRIANGLES, 0, vertexIndex->size() );
	primitive->push_back( prim );

	return vertexShape;
}

bool Reader::writeMaterial( const COLLADAFW::Material* material )
{
	//called before writeEffect.
	//material name = effect id because it is the only why to find material in writeEffect method.
	//no problem until 1 effect == 1 material
	//can one effect used in many material?
	//if yes ==> problem to find the materiel (many material with same name) in writeEffect method.

	std::string name = "mat:" + material->getUniqueId().toAscii() + " effect:" + material->getInstantiatedEffect().toAscii();
	vgd::Shp< vgd::node::Group > container = vgd::node::Group::create( name );
	m_switchMaterial->addChild( container );

	return true;
}

bool Reader::writeEffect( const COLLADAFW::Effect* effect )
{

	vgd::Shp< vgd::node::Material > material = vgd::node::Material::create( effect->getName() );
	
	std::stringstream ss;
	int classId = effect->getUniqueId().getClassId();
	int objectId = (int)effect->getUniqueId().getObjectId();
	ss << ".*" << "effect:UniqueID\\(" << classId << "," << objectId << "\\)";
	std::string regex = ss.str();

	vgd::visitor::predicate::ByRegexName predicate(regex);
	vgd::Shp< vgd::node::Group > container = vgd::visitor::findFirst< vgd::node::Group >( m_switchMaterial, predicate );

	container->addChild( material );
	
	const COLLADAFW::EffectCommon* effectCommon = effect->getCommonEffects().getData()[0];

	vgm::Vec3f color;
	//
	//// ambient
	color[0] = (float)effectCommon->getAmbient().getColor().getRed();
	color[1] = (float)effectCommon->getAmbient().getColor().getGreen();
	color[2] = (float)effectCommon->getAmbient().getColor().getBlue();
	material->setAmbient( color );
	//
	//// diffuse
	if (effectCommon->getDiffuse().getColor().getRed() == -1)
	{
		color[0] = (float)effectCommon->getAmbient().getColor().getRed();
	}
	else
	{
		color[0] = (float)effectCommon->getDiffuse().getColor().getRed();
	}

	if (effectCommon->getDiffuse().getColor().getRed() == -1)
	{
		color[1] = (float)effectCommon->getAmbient().getColor().getGreen();
	}
	else
	{
		color[1] = (float)effectCommon->getDiffuse().getColor().getGreen();
	}

	if (effectCommon->getDiffuse().getColor().getRed() == -1)
	{
		color[2] = (float)effectCommon->getAmbient().getColor().getBlue();
	}
	else
	{
		color[2] = (float)effectCommon->getDiffuse().getColor().getBlue();
	}
	material->setDiffuse( color );
	//
	//// specular
	color[0] = (float)effectCommon->getSpecular().getColor().getRed();
	color[1] = (float)effectCommon->getSpecular().getColor().getGreen();
	color[2] = (float)effectCommon->getSpecular().getColor().getBlue();
	material->setSpecular( color );
	//
	//// emission
	color[0] = (float)effectCommon->getEmission().getColor().getRed();
	color[1] = (float)effectCommon->getEmission().getColor().getGreen();
	color[2] = (float)effectCommon->getEmission().getColor().getBlue();
	material->setEmission( color );
	//
	//// specularLevel/glosiness
	float real;
	real = effectCommon->getShininess().getFloatValue();
	if( real <= 1 )
	{
		material->setShininess( real );
	}
	else
	{
		//if > 1 ==> it uses Blinn Phong equation. How to use it? (p. 244 COLLADA Spec).
		///material->setShininess( real );
		material->setShininess( vgm::clamp<float>( real, 0.f, 1.f ) );
	}

	//// transparency
	real = (float)effectCommon->getOpacity().getColor().getAlpha(); //by default (opaque="A_ONE")Takes the transparency information from the color’s alpha channel, where the value 1.0 is opaque. 
	material->setOpacity( real );
	
	if ( m_loadType > LOAD_TYPE::LOAD_MATERIAL )
	{
		for (uint i = 0; i < effectCommon->getSamplerPointerArray().getCount(); i++)
		{
			const COLLADAFW::Sampler* sampler = effectCommon->getSamplerPointerArray().getData()[i];

			vgd::Shp< vgd::node::Texture2D > tex = vgd::visitor::findFirstByName< vgd::node::Texture2D >( m_switchTexture, sampler->getSourceImage().toAscii() );
			
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
				assert("UNSPECIFIED WRAP MODE");
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
				assert("UNSPECIFIED WRAP MODE");
			}

			//WRAP_T
			if ( sampler->getWrapT() == COLLADAFW::Sampler::WRAP_MODE_UNSPECIFIED )
			{
				assert("UNSPECIFIED WRAP MODE");
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
				assert("UNSPECIFIED WRAP MODE");
			}

			tex->sethFunction( Texture2D::FUN_MODULATE );
		}
	}

	return true;
}


bool Reader::writeImage( const COLLADAFW::Image* image )
{
	vgd::Shp< vgd::node::Texture2D > tex = vgd::node::Texture2D::create( image->getUniqueId().toAscii() );
	tex->setMultiAttributeIndex( (int8)0 ); //a quoi ca sert?


	//@TODO: manage path.
	std::string path = m_inputFile.getPathDir() + image->getImageURI().getPath();
	path = path.substr(1);

	vgd::Shp< vgd::basic::IImage > img = vgio::ImageCache::load( path );

	tex->setImage( img );

	//// default value.
	using vgd::node::Texture2D;
	tex->setMipmap( true );
	tex->setFilter( Texture2D::MIN_FILTER, Texture2D::LINEAR_MIPMAP_LINEAR );
	tex->setFilter( Texture2D::MAG_FILTER, Texture2D::LINEAR );
	
	m_switchTexture->addChild( tex );

	return true;
}

} // namespace vgCollada

