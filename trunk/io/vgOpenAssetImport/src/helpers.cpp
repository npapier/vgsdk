// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgOpenAssetImport/helpers.hpp"

#include <algorithm>
#include <assimp/scene.h>
#include <vgd/node/Material.hpp>
#include <vgd/node/VertexShape.hpp>



namespace vgOpenAssetImport
{


namespace
{

aiVector3D toAiVector3D( vgm::Vec2f source )
{
	aiVector3D retVal( source[0], source[1], 0.f );
	return retVal;
}

aiVector3D toAiVector3D( vgm::Vec3f source )
{
	aiVector3D retVal( source[0], source[1], source[2] );
	return retVal;
}


aiColor3D toAiColor3D( vgm::Vec3f source )
{
	aiColor3D retVal( source[0], source[1], source[2] );
	return retVal;
}


void fillAiFace( aiFace * face, uint numIndices, vgd::field::EditorRO< vgd::field::MFUInt >& vertexIndex, uint index )
{
	face->mNumIndices = numIndices;
	vgAssertN( face->mIndices == 0, "Not the default aiFace. Already used ?" );

	face->mIndices = new unsigned int[numIndices];
	for( uint i=0; i != numIndices; ++i )
	{
		face->mIndices[i] = (*vertexIndex)[index + i];
	}
}

}


vgd::Shp< aiMesh > createAiMesh( vgd::node::VertexShape * vertexShape )
{
	vgd::Shp< aiMesh > aimesh( new aiMesh );
	fillAiMesh( vertexShape, aimesh.get() );
	return aimesh;
}


void fillAiMesh( vgd::node::VertexShape * vertexShape, aiMesh * aimesh )
{
	using vgd::field::EditorRO;

	// name
	aimesh->mName.Set( vertexShape->getName() );

	// VERTICES
	EditorRO< vgd::field::MFVec3f > vertices = vertexShape->getVertexRO();

	const bool changedNumVertices = (aimesh->mNumVertices != vertices->size());
	if ( changedNumVertices )
	{
		// Delete
		if ( aimesh->mVertices )	delete [] aimesh->mVertices;

		// New
		aimesh->mNumVertices = vertices->size();
		aimesh->mVertices = ( vertices->size() > 0 ) ? new aiVector3D[aimesh->mNumVertices] : 0;
	}

	for( uint i = 0, iEnd = vertices->size(); i != iEnd; ++i )
	{
		aimesh->mVertices[i] = toAiVector3D( (*vertices)[i] );
	}

	// NORMALS
	EditorRO< vgd::field::MFVec3f > normals = vertexShape->getNormalRO();

	const bool changedNumNormals =	(aimesh->mNormals && normals->size() == 0) ||
									(!aimesh->mNormals && normals->size() > 0);
	if ( changedNumVertices || changedNumNormals )
	{
		// Delete
		if ( aimesh->mNormals ) delete [] aimesh->mNormals;

		// New
		vgAssert( normals->size() /* == vertices->size() */ == aimesh->mNumVertices );
		aimesh->mNormals = ( normals->size() > 0 ) ? new aiVector3D[normals->size()] : 0;
	}

	for( uint i = 0, iEnd = normals->size(); i != iEnd; ++i )
	{
		aimesh->mNormals[i] = toAiVector3D( (*normals)[i] );
	}

	// TEXCOORD0
	// @todo all texture units
	// @todo all dimensions
	const uint unit = 0;
	if ( vertexShape->hasTexCoord(unit) && vertexShape->getTexCoordDim(unit) == 2 )
	{
		// unit 0 and dim(TEXCOORD0) == 2
		EditorRO< vgd::field::MFVec2f > texCoord = vertexShape->getTexCoordRO<vgd::field::MFVec2f>(unit);

		const bool changedNumTexCoords =	(aimesh->mTextureCoords[unit] && texCoord->size() == 0) ||
											(!aimesh->mTextureCoords[unit] && texCoord->size() > 0);

		if ( changedNumVertices || changedNumTexCoords )
		{
			// Delete
			if ( aimesh->mTextureCoords[unit] ) delete [] aimesh->mTextureCoords[unit];

			// New
			vgAssert( texCoord->size() /* == vertices->size() */ == aimesh->mNumVertices );
			aimesh->mTextureCoords[unit] = ( texCoord->size() > 0 ) ? new aiVector3D[texCoord->size()] : 0;
		}

		aiVector3D * aiTexCoord = aimesh->mTextureCoords[unit];
		for( uint i = 0, iEnd = texCoord->size(); i != iEnd; ++i )
		{
			aiTexCoord[i] = toAiVector3D( (*texCoord)[i] );
		}
	}

	// FACES
	//	Compute numFaces and numIndices
	uint numFaces	= 0;
	uint numIndices	= 0;
	EditorRO< vgd::field::MFPrimitive >		primitives	= vertexShape->getPrimitiveRO();
	for(	vgd::field::MFPrimitive::const_iterator	i	= primitives->begin(),
													ie	= primitives->end();
			i != ie;
			++i)
	{
		using vgd::node::Primitive;
		const Primitive& primitive(*i);

		if ( primitive.getType() == Primitive::TRIANGLES )
		{
			vgAssert( primitive.getNumIndices() % 3 == 0 );

			numFaces	+=	primitive.getNumIndices()/3;
			numIndices	=	std::max( numIndices, static_cast<uint>(primitive.getIndex() + primitive.getNumIndices()) );
		}
		else if ( primitive.getType() == Primitive::QUADS )
		{
			vgAssert( primitive.getNumIndices() % 4 == 0 );

			numFaces	+=	primitive.getNumIndices()/4;
			numIndices	=	std::max( numIndices, static_cast<uint>(primitive.getIndex() + primitive.getNumIndices()) );
		}
		else
		{
			// @todo support all primitives types
			vgAssertN( false, "Primitive of type %i is not supported.", static_cast<uint>(primitive.getType()) );
		}
	}

	//	Fill FACES
	if ( aimesh->mNumFaces != numFaces )
	{
		// Delete
		if ( aimesh->mFaces )	delete [] aimesh->mFaces;
		// New
		aimesh->mNumFaces = numFaces;
		aimesh->mFaces = new aiFace[aimesh->mNumFaces];
	}

	//	For each face,
	uint iFace = 0;
	uint iFaceEnd = aimesh->mNumFaces;
	aiFace * face = &aimesh->mFaces[iFace];

	EditorRO< vgd::field::MFUInt > vertexIndex = vertexShape->getVertexIndexRO();

	for(	vgd::field::MFPrimitive::const_iterator	i	= primitives->begin(),
													ie	= primitives->end();
			i != ie;
			++i)
	{
		using vgd::node::Primitive;
		const Primitive& primitive(*i);

		if ( primitive.getType() == Primitive::TRIANGLES )
		{
			for(	uint	i		= primitive.getIndex(),
							iEnd	= primitive.getIndex() + primitive.getNumIndices();
					i != iEnd;
					i += 3 )
			{
				fillAiFace( face, 3, vertexIndex, i );
				++iFace;
				face = &aimesh->mFaces[iFace];
			}
		}
		else if ( primitive.getType() == Primitive::QUADS )
		{
			for(	uint	i		= primitive.getIndex(),
							iEnd	= primitive.getIndex() + primitive.getNumIndices();
					i != iEnd;
					i += 4 )
			{
				fillAiFace( face, 4, vertexIndex, i );
				++iFace;
				face = &aimesh->mFaces[iFace];
			}
		}
		else
		{
			// @todo support all primitives types
			vgAssertN( false, "Primitive of type %i is not supported.", static_cast<uint>(primitive.getType()) );
		}
	}
}


void fillAiMaterial( vgd::node::Material * material, aiMaterial * aiMat )
{
	bool		isDefined;
	vgm::Vec3f	color;
	float		valuef;

	aiString	aiStr;
	aiColor3D	aiColor;

	// NAME
	aiStr.Set( material->getName() );
	aiMat->AddProperty( &aiStr, AI_MATKEY_NAME );

	// AMBIENT
	isDefined = material->getAmbient( color );

	if ( isDefined )
	{
		aiColor = toAiColor3D(color);
		aiMat->AddProperty< aiColor3D >( &aiColor, 1, AI_MATKEY_COLOR_AMBIENT );
	}
	// else nothing to do

	// DIFFUSE
	isDefined = material->getDiffuse( color );

	if ( isDefined )
	{
		aiColor = toAiColor3D(color);
		aiMat->AddProperty< aiColor3D >( &aiColor, 1, AI_MATKEY_COLOR_DIFFUSE );
	}
	// else nothing to do

	// SPECULAR
	isDefined = material->getSpecular( color );

	if ( isDefined )
	{
		aiColor = toAiColor3D(color);
		aiMat->AddProperty< aiColor3D >( &aiColor, 1, AI_MATKEY_COLOR_SPECULAR );
	}
	// else nothing to do

	// EMISSION
	isDefined = material->getEmission( color );

	if ( isDefined )
	{
		aiColor = toAiColor3D(color);
		aiMat->AddProperty< aiColor3D >( &aiColor, 1, AI_MATKEY_COLOR_EMISSIVE );
	}
	// else nothing to do

	// SHININESS
	isDefined = material->getShininess( valuef );

	if ( isDefined )
	{
		aiMat->AddProperty< float >( &valuef, 1, AI_MATKEY_SHININESS );
	}
	// else nothing to do

	// OPACITY
	valuef = material->getOpacity();

	aiMat->AddProperty< float >( &valuef, 1, AI_MATKEY_OPACITY );
}


aiScene * createAiScene( vgd::node::VertexShape * vertexShape )
{
	// SCENE
	aiScene * aiscene = aiCreateScene();

	// MESHES
	aiscene->mNumMeshes = 1;
	aiscene->mMeshes = new aiMesh*[aiscene->mNumMeshes];

	// mesh 0
	aiscene->mMeshes[0] = new aiMesh;
	fillAiMesh( vertexShape, aiscene->mMeshes[0] );

	// MATERIALS
	aiscene->mNumMaterials = 1;
	aiscene->mMaterials = new aiMaterial*[aiscene->mNumMaterials];

	// material 0
	aiscene->mMaterials[0] = new aiMaterial;

	using vgd::node::Material;
	vgd::Shp< Material > material = Material::createWhole();
	fillAiMaterial( material.get(), aiscene->mMaterials[0] );

	// ROOT NODE
	aiNode * rootNode = new aiNode;
	rootNode->mNumMeshes = 1;
	rootNode->mMeshes = new unsigned int[rootNode->mNumMeshes];
	rootNode->mMeshes[0] = 0;

	aiscene->mRootNode = rootNode;

	return aiscene;
}


} // namespace vgOpenAssetImport
