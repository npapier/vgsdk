// VGSDK - Copyright (C) 2012, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgOpenAssetImport/Loader.hpp"

#include <assimp/Importer.hpp>		// C++ importer interface
#include <assimp/scene.h>			// Output data structure
#include <assimp/postprocess.h>		// Post processing flags

#include <vgd/basic/Image.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/MatrixTransform.hpp>
#include <vgd/node/Switch.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vgd/node/TransformSeparator.hpp>
#include <vgd/node/VertexShape.hpp>



namespace vgOpenAssetImport
{


namespace
{


/**
 * @name Helpers
 */
//@{
vgm::Vec3f toVec3f( aiVector3D * source )
{
	vgm::Vec3f retVal( source->x, source->y, source->z );
	return retVal;
}

vgm::Vec3f toVec3f( aiVector3D source )
{
	vgm::Vec3f retVal( source.x, source.y, source.z );
	return retVal;
}

vgm::Vec2f toVec2f( aiVector3D source )
{
	vgm::Vec2f retVal( source.x, source.y );
	return retVal;
}

vgm::Vec3f toVec3f( aiColor3D source )
{
	vgm::Vec3f retVal( source.r, source.g, source.b );
	return retVal;
}


aiVector3D toAiVector3D( vgm::Vec3f source )
{
	aiVector3D retVal( source[0], source[1], source[2] );
	return retVal;
}


const vgd::node::Primitive::Type numIndices2Primitive( const uint numIndices )
{
	using vgd::node::Primitive;

	if ( numIndices == 3 )
	{
		return Primitive::TRIANGLES;
	}
	else if ( numIndices == 2 )
	{
		return Primitive::LINES;
	}
	else if ( numIndices == 1 )
	{
		return Primitive::POINTS;
	}
	else if ( numIndices == 4 )
	{
		return Primitive::QUADS;
	}
	else if ( numIndices > 4 )
	{
		return Primitive::POLYGON;
	}
	else
	{
		vgAssert( false );
		return Primitive::NONE;
	}
}


// @todo check wrapping modes
vgd::node::Texture::WrapValueType toEnum( const aiTextureMapMode mapMode )
{
	using vgd::node::Texture;

	switch ( mapMode )
	{
		case aiTextureMapMode_Wrap:
			return Texture::WrapValueType(Texture::REPEAT);

		case aiTextureMapMode_Clamp:
			return Texture::WrapValueType(Texture::CLAMP_TO_EDGE);

		case aiTextureMapMode_Decal:
			return Texture::WrapValueType(Texture::CLAMP_TO_BORDER); // @todo no decal in vgsdk

		case aiTextureMapMode_Mirror:
			return Texture::WrapValueType(Texture::MIRRORED_REPEAT);

		default:
			vgAssertN( false, "Unsupported wrapping mode." );
			return Texture::WrapValueType(Texture::CLAMP_TO_EDGE);
	}
}
//@}


// TEXTURE2D
vgd::Shp< vgd::node::Texture2D > createTexture2D(	const boost::filesystem::path pathFilename, const int index, const aiString aiImagePath,
													const aiTextureMapMode mapU, const aiTextureMapMode mapV )
{
	// Compute image path
	std::string imagePathFilenameStr;

	namespace bfs = boost::filesystem;
	const bfs::path imagePathFilename = aiImagePath.C_Str();

	if ( imagePathFilename.is_absolute() )
	{
		imagePathFilenameStr = imagePathFilename.string();
	}
	else // relative path
	{
		const bfs::path rootPath = pathFilename.parent_path();

		imagePathFilenameStr = (rootPath / imagePathFilename).string();
	}

	// Texture node
	using vgd::node::Texture2D;
	vgd::Shp< Texture2D > texture = Texture2D::create( imagePathFilename.filename().string(), (int8)index );

	// IMAGE
	vgd::Shp< vgd::basic::IImage > image;

	image.reset( new vgd::basic::Image(imagePathFilenameStr) );
	texture->setImage( image );

	// Default values
	texture->setMipmap( true );
	texture->setFilter( Texture2D::MIN_FILTER, Texture2D::LINEAR_MIPMAP_LINEAR );
	texture->setFilter( Texture2D::MAG_FILTER, Texture2D::LINEAR );

	// WRAPPING
	texture->setWrap( Texture2D::WRAP_S, toEnum(mapU) );
	texture->setWrap( Texture2D::WRAP_T, toEnum(mapV) );

	// FUNCTION
	texture->sethFunction( vgd::node::Texture2D::FUN_MODULATE ); // @todo
	return texture;
}


// MATERIAL
vgd::Shp< vgd::node::Group > createMaterial( const boost::filesystem::path pathFilename, const aiMaterial * aiMat )
{
	// Group node
	using vgd::node::Group;
	vgd::Shp< Group > group = Group::create("");

	// Material node
	using vgd::node::Material;
	vgd::Shp< Material > material = Material::create("material");
	group->addChild( material );

	//
	float		valuef;
	aiString	str;
	aiColor3D	color;

	// NAME
	if ( aiMat->Get( AI_MATKEY_NAME, str ) == AI_SUCCESS )
	{
		const std::string name( str.C_Str() );

		material->setName( name );
		group->setName( name );
	}

	// AMBIENT
	if ( aiMat->Get( AI_MATKEY_COLOR_AMBIENT, color ) == AI_SUCCESS )
	{
		material->setAmbient( toVec3f(color) );
	}

	// DIFFUSE
	if ( aiMat->Get( AI_MATKEY_COLOR_DIFFUSE, color ) == AI_SUCCESS )
	{
		material->setDiffuse( toVec3f(color) );
	}

	// SPECULAR
	if ( aiMat->Get( AI_MATKEY_COLOR_SPECULAR, color ) == AI_SUCCESS )
	{
		material->setSpecular( toVec3f(color) );
	}

	// EMISSION
	if ( aiMat->Get( AI_MATKEY_COLOR_EMISSIVE, color ) == AI_SUCCESS )
	{
		material->setEmission( toVec3f(color) );
	}

	// SHININESS
	if ( aiMat->Get( AI_MATKEY_SHININESS, valuef ) == AI_SUCCESS )
	{
		material->setShininess( vgm::clamp(valuef, 0.f, 1.f) );
	}

	// OPACITY
	if ( aiMat->Get( AI_MATKEY_OPACITY, valuef ) == AI_SUCCESS )
	{
		material->setOpacity( valuef );
	}

	// TEXTURES
	aiTextureMapMode mapU(aiTextureMapMode_Wrap);
	aiTextureMapMode mapV(aiTextureMapMode_Wrap);

	// DIFFUSE TEXTURE
	if ( aiMat->Get( AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), str ) == AI_SUCCESS )
	{
		aiMat->Get( AI_MATKEY_MAPPINGMODE_U(aiTextureType_DIFFUSE, 0), mapU );
		aiMat->Get( AI_MATKEY_MAPPINGMODE_V(aiTextureType_DIFFUSE, 0), mapV );

		vgd::Shp< vgd::node::Texture2D > texture = createTexture2D( pathFilename, 0, str, mapU, mapV );
		group->addChild( texture );
	}

	// NORMALMAP TEXTURE
	if ( aiMat->Get( AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), str ) == AI_SUCCESS )
	{
		aiMat->Get( AI_MATKEY_MAPPINGMODE_U(aiTextureType_NORMALS, 0), mapU );
		aiMat->Get( AI_MATKEY_MAPPINGMODE_V(aiTextureType_NORMALS, 0), mapV );

		vgd::Shp< vgd::node::Texture2D > texture = createTexture2D( pathFilename, 1, str, mapU, mapV );
		group->addChild( texture );
	}

	/*// SPECULAR TEXTURE
	if ( aiMat->Get( AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), str ) == AI_SUCCESS )
	{
		aiMat->Get( AI_MATKEY_MAPPINGMODE_U(aiTextureType_SPECULAR, 0), mapU );
		aiMat->Get( AI_MATKEY_MAPPINGMODE_V(aiTextureType_SPECULAR, 0), mapV );

		vgd::Shp< vgd::node::Texture2D > texture = createTexture2D( pathFilename, 2, str, mapU, mapV );
		group->addChild( texture );
	}*/

	// @todo aiTextureType_AMBIENT
	// @todo aiTextureType_OPACITY
	// @todo aiTextureType_LIGHTMAP
	// @todo others textures

	return group;
}


// VERTEXSHAPE
vgd::Shp< vgd::node::VertexShape > createVertexShape( const aiMesh * mesh )
{
	// Vertex shape
	using vgd::node::VertexShape;
	vgd::Shp< VertexShape > vertexShape = VertexShape::create( mesh->mName.C_Str() );

	// Editors
	vgd::field::EditorRW< vgd::field::MFVec3f >		vertex		= vertexShape->getFVertexRW();
	vgd::field::EditorRW< vgd::field::MFUInt32>		vertexIndex	= vertexShape->getFVertexIndexRW();
	vgd::field::EditorRW< vgd::field::MFPrimitive >	primitives	= vertexShape->getFPrimitiveRW();

	// VERTEX
	vertex->reserve( mesh->mNumVertices );
	for( uint i = 0, iEnd = mesh->mNumVertices; i != iEnd; ++i )
	{
		vertex->push_back( toVec3f(mesh->mVertices[i]) );
	}

	// VERTEX INDEX
	vertexIndex->reserve( mesh->mNumFaces );
	for( uint i = 0, iEnd = mesh->mNumFaces; i != iEnd; ++i )
	{
		const aiFace * face = &mesh->mFaces[i];
		for( uint j=0, jEnd=face->mNumIndices; j != jEnd; ++j )
		{
			const int index = face->mIndices[j];
			vertexIndex->push_back( index );
		}
	}

	// PRIMITIVES
	using vgd::node::Primitive;
	Primitive primitive(vgd::node::Primitive::NONE, 0, 0);
	uint currentIndex = 0;
	for( uint i = 0, iEnd = mesh->mNumFaces; i != iEnd; ++i )
	{
		const aiFace *			face		= &mesh->mFaces[i];
		const Primitive::Type	primType	= numIndices2Primitive( face->mNumIndices );

		if ( primitive.getNumIndices() == 0 )	// new primitive object
		{
			vgAssert( primitive.getType() == Primitive::NONE );
			vgAssert( primitive.getIndex() == 0 );
			//vgAssert( primitive.getNumIndices() == 0 );

			primitive.setType( primType );
			primitive.setIndex( currentIndex );
			primitive.setNumIndices( face->mNumIndices );
		}
		else if ( primitive.getType() == primType ) // reuse current primitive object
		{
			primitive.addToNumIndices( face->mNumIndices );
		}
		else // new type of primitive
		{
			primitives->push_back( primitive );

			primitive.setType( primType );
			primitive.setIndex( currentIndex );
			primitive.setNumIndices( face->mNumIndices );
		}

		currentIndex += face->mNumIndices;
	}

	if ( primitive.getNumIndices() > 0 )
	{
		primitives->push_back( primitive );
	}

	// NORMALS
	if ( mesh->HasNormals() )
	{
		vgd::field::EditorRW< vgd::field::MFVec3f > normals = vertexShape->getFNormalRW();

		normals->reserve( mesh->mNumVertices );
		for( uint i = 0, iEnd = mesh->mNumVertices; i != iEnd; ++i )
		{
			normals->push_back( toVec3f(mesh->mNormals[i]) );
		}

		vertexShape->setNormalBinding( vgd::node::BIND_PER_VERTEX );
	}

	// TEX COORDS
	for( uint j = 0, jEnd=mesh->GetNumUVChannels(); j != jEnd; ++j )
	{
		vgAssert( mesh->mNumUVComponents[j] == 2 ); // @todo support of 1 and 3
		vertexShape->createTexUnits( mesh->mNumUVComponents[j], j );
		vertexShape->setTexCoordBinding( j, vgd::node::BIND_PER_VERTEX );

		vgd::field::EditorRW< vgd::field::MFVec2f >	texCoord = vertexShape->getFTexCoordRW<vgd::field::MFVec2f>( j );
		texCoord->reserve( mesh->mNumVertices );
		for( uint i = 0, iEnd = mesh->mNumVertices; i != iEnd; ++i )
		{
			texCoord->push_back( toVec2f(mesh->mTextureCoords[j][i]) );
		}
	}

	// TANGENTS
	if ( mesh->HasTangentsAndBitangents() )
	{
		vgd::field::EditorRW< vgd::field::MFVec3f > tangents = vertexShape->getFTangentRW();

		tangents->reserve( mesh->mNumVertices );
		for( uint i = 0, iEnd = mesh->mNumVertices; i != iEnd; ++i )
		{
			tangents->push_back( toVec3f(mesh->mTangents[i]) );
		}

		vertexShape->setTangentBinding( vgd::node::BIND_PER_VERTEX );
	}

	// @todo bitangents

	return vertexShape;
}


/**
 * @param scene		assimp scene
 * @param node		current node in assimp scene graph
 * @param meshes	meshes library
 * @param materials	materials library
 */
vgd::Shp< vgd::node::Group > recursiveImport(	const aiScene * aiscene, const aiNode * ainode,
												vgd::Shp< vgd::node::Switch > meshes,
												vgd::Shp< vgd::node::Switch > materials )
{
	using vgd::node::Group;
	using vgd::node::TransformSeparator;
	using vgd::node::MatrixTransform;

	// Container node
	vgd::Shp< Group > group;

	// Transformation
	aiMatrix4x4 aim = ainode->mTransformation;
	aim.Transpose();
	const vgm::MatrixR m(static_cast<float*>(&aim[0][0]));

	if ( !m.isIdentity() )
	{
		// has a transformation
		group = TransformSeparator::create( ainode->mName.C_Str() );

		vgd::Shp< MatrixTransform > matrixTransform = MatrixTransform::create("");
		matrixTransform->setMatrix( m );

		group->addChild( matrixTransform );
	}
	else
	{
		// no transformation
		group = Group::create( ainode->mName.C_Str() );
	}

	// For each mesh
	for( uint i = 0, iEnd = ainode->mNumMeshes; i != iEnd; ++i )
	{
		const uint		meshIndex		= ainode->mMeshes[i];
		const aiMesh *	aimesh			= aiscene->mMeshes[meshIndex];
		const uint		materialIndex	= aimesh->mMaterialIndex;

		group->addChild( materials->getAbstractChild(materialIndex) );
		group->addChild( meshes->getAbstractChild(meshIndex) );
	}

	// For each child
	for( uint i = 0, iEnd = ainode->mNumChildren; i != iEnd; ++i )
	{
		vgd::Shp< Group > childrenGroup = 
			recursiveImport( aiscene, ainode->mChildren[i], meshes, materials );
		if ( childrenGroup->getNumChildren() > 0 )
		{
			group->addChild( childrenGroup );
		}
	}

	return group;
}


}


META_LOADER_CPP( vgOpenAssetImport::Loader, "openAssetImport" )


Loader::Loader()
: 	//m_pathFilename
	//m_flags(0)
	m_flags(aiProcess_CalcTangentSpace)
{}


void Loader::addPostProcessing( unsigned int flags )
{
	m_flags = flags;
}


std::pair< bool, vgd::Shp< vgd::node::Group > > Loader::load( const std::string filePath, const bool bCCW )
{
	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;

	// Analysis of filePath
	namespace bfs = boost::filesystem;

	m_pathFilename = filePath;

	// Default pp steps
	unsigned int ppsteps = //aiProcess_CalcTangentSpace | // calculate tangents and bitangents if possible
			aiProcess_JoinIdenticalVertices    | // join identical vertices/ optimize indexing
			//aiProcess_ValidateDataStructure    | // perform a full validation of the loader's output
			//aiProcess_ImproveCacheLocality     | // improve the cache locality of the output vertices
			//aiProcess_RemoveRedundantMaterials | // remove redundant materials
			//aiProcess_FindDegenerates          | // remove degenerated polygons from the import
			//aiProcess_FindInvalidData          | // detect invalid model data, such as invalid normal vectors*/
			aiProcess_GenUVCoords              | // convert spherical, cylindrical, box and planar mapping to proper UVs
			aiProcess_TransformUVCoords        | // preprocess UV transformations (scaling, translation ...)
			aiProcess_FlipUVs					| // flips all UV coordinates along the y-axis and adjusts material settings and bitangents accordingly.
			//aiProcess_FindInstances            | // search for instanced meshes and remove them by references to one master
			//aiProcess_LimitBoneWeights         | // limit bone weights to 4 per vertex
			//aiProcess_OptimizeMeshes		   | // join small meshes, if possible;
			//aiProcess_SplitByBoneCount         | // split meshes with too many bones. Necessary for our (limited) hardware skinning shader*/
			0;

	// Create an instance of the Importer class
	Assimp::Importer importer;
	const aiScene * scene = importer.ReadFile( filePath,
		m_flags |
		ppsteps | /* configurable pp steps */
		//aiProcess_GenSmoothNormals		   | // generate smooth normal vectors if not existing
		//aiProcess_SplitLargeMeshes         | // split large, unrenderable meshes into submeshes
		aiProcess_Triangulate			   | // triangulate polygons with more than 3 edges
		//aiProcess_ConvertToLeftHanded	   | // convert everything to D3D left handed space
		//aiProcess_SortByPType              | // make 'clean' meshes which consist of a single typ of primitives
		0 );

	// If the import failed, report it
	retVal.first = (scene != 0);
	if ( !scene )
	{
		vgLogError( "assimp:load(%s):%s", filePath.c_str(), importer.GetErrorString() );
	}
	else
	{
		using vgd::node::Group;
		using vgd::node::Switch;
		using vgd::node::TransformSeparator;
		using vgd::node::VertexShape;

		// Now we can access the file's contents.
		vgd::Shp< Group > group = Group::create( "ROOT." + filePath );
		retVal.second = group;

		// Import all materials
		vgd::Shp< Switch > materials = Switch::create( "MATERIALS LIBRARY" );
		group->addChild( materials );

		for( uint i = 0, iEnd = scene->mNumMaterials; i != iEnd; ++i )
		{
			vgd::Shp< Group > material = createMaterial( m_pathFilename, scene->mMaterials[i] );
			vgAssert( material );
			materials->addChild( material );
		}

		// Import all meshes
		vgd::Shp< Switch > meshes = Switch::create( "MESHES LIBRARY" );
		group->addChild( meshes );

		for( uint i = 0, iEnd = scene->mNumMeshes; i != iEnd; ++i )
		{
			vgd::Shp< VertexShape > shape = createVertexShape( scene->mMeshes[i] );
			if ( shape )
			{
				meshes->addChild( shape );
			}
		}

		// @todo lights, cameras, animations...

		// Traverse the assimp scene graph
		using vgd::node::Group;
		vgd::Shp< Group > worldInstance = recursiveImport( scene, scene->mRootNode, meshes, materials );
		worldInstance->setName( m_pathFilename.filename().string() + ":" + worldInstance->getName() );

		//
		group->insertChild( worldInstance );
	}

	return retVal;
}


std::pair< bool, vgd::Shp< vgd::node::Group > > Loader::load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, const bool bCCW )
{
	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;
	return retVal;
}


std::pair< bool, vgd::Shp< vgd::node::Group > > Loader::load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, std::map< std::string, vgd::Shp< vgd::basic::Image > > imageMap, const bool bCCW )
{
	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;
	vgAssert( false );
	return retVal;
}


vgd::Shp< vgio::ILoader > Loader::clone()
{
	return vgd::makeShp( new Loader() );
}


} // namespace vgOpenAssetImport
