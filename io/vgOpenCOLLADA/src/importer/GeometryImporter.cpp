// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/importer/GeometryImporter.hpp"

#include <boost/functional/hash.hpp>
#include <boost/unordered_map.hpp>  

#include <COLLADAFWTriangles.h>


namespace vgOpenCOLLADA
{

namespace importer
{

GeometryImporter::GeometryImporter( const COLLADAFW::Geometry* geometry, LOAD_TYPE loadType ) :
m_loadType( loadType )
{
	m_mesh = (COLLADAFW::Mesh*) geometry;
}



std::pair< bool, vgd::Shp< vgd::node::Group > > GeometryImporter::loadMesh()
{
	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;
	retVal.first = true;
	vgd::Shp< vgd::node::Group > group = vgd::node::Group::create( m_mesh->getUniqueId().toAscii() );
	retVal.second = group;

	int totalTrianglesCount = m_mesh->getTrianglesTriangleCount() + m_mesh->getTristripsTriangleCount() + m_mesh->getTrifansTriangleCount();

	if ( totalTrianglesCount < 1 )
	{
		throw std::runtime_error("Only triangles/polygons mesh are supported.");
	}

	importTriangleMeshPositions();

	importTriangleMeshNormals();

	importTriangleMeshUVCoords();

	retVal.first = importMeshPrimitives( group );

	return retVal;
}



void GeometryImporter::importTriangleMeshPositions()
{
	const COLLADAFW::MeshVertexData& meshPositions = m_mesh->getPositions();

	if ( meshPositions.getType() != COLLADAFW::FloatOrDoubleArray::DATA_TYPE_FLOAT )
	{
		throw std::runtime_error("Position Data types are not float!");
	}

	int32 positionsSize = (int)meshPositions.getValuesCount();
	int32 positionsStride = 3;

	const COLLADAFW::FloatArray* positionsArray = meshPositions.getFloatValues();

	int32 positionsCount = positionsSize / positionsStride;

	for ( int i = 0; i < positionsCount; ++i)
	{
		m_positions.push_back(vgm::Vec3f( (float)(*positionsArray)[3*i],	(float)(*positionsArray)[3*i + 1], (float)(*positionsArray)[3*i + 2] ));
	}
}



void GeometryImporter::importTriangleMeshNormals()
{
	const COLLADAFW::MeshVertexData& meshNormals = m_mesh->getNormals();

	if ( meshNormals.getType() != COLLADAFW::FloatOrDoubleArray::DATA_TYPE_FLOAT )
	{
		throw std::runtime_error("Normal Data types are not float!");
	}

	int32 normalsSize = (int)meshNormals.getValuesCount();
	int32 normalsStride = 3;

	const COLLADAFW::FloatArray* normalsArray = meshNormals.getFloatValues();

	int32 normalsCount = normalsSize / normalsStride;

	std::vector< vgm::Vec3f > normals;
	for ( int i = 0; i < normalsCount; ++i)
	{
		m_normals.push_back(vgm::Vec3f( (float)(*normalsArray)[3*i],	(float)(*normalsArray)[3*i + 1], (float)(*normalsArray)[3*i + 2] ));
	}
}



void GeometryImporter::importTriangleMeshUVCoords()
{
	const COLLADAFW::MeshVertexData& uvCoordinates = m_mesh->getUVCoords();
	//const COLLADAFW::MeshVertexData::InputInfosArray& uvInputInfos = uvCoordinates.getInputInfosArray();
	//COLLADAFW::MeshVertexData::InputInfos* inputInfo = uvInputInfos[ 0 ];

	int32 textCoordSize = (int)uvCoordinates.getValuesCount();
	int32 textCoordStride = 3;//inputInfo->mStride;

	const COLLADAFW::FloatArray* textCoordArray = uvCoordinates.getFloatValues();

	int32 textCoordCount = textCoordSize / textCoordStride;

	std::vector< vgm::Vec2f > textCoords;
	for ( int i = 0; i < textCoordCount; ++i)
	{
		m_textCoords.push_back(vgm::Vec2f( (float)(*textCoordArray)[textCoordStride*i], (float)(*textCoordArray)[textCoordStride*i + 1] ));
	}
}



bool GeometryImporter::importMeshPrimitives( vgd::Shp< vgd::node::Group > group )
{
	COLLADAFW::MeshPrimitiveArray& meshPrimitiveArray = m_mesh->getMeshPrimitives();

	//for each <triangles> tag of the mesh.
	for ( size_t i = 0; i < meshPrimitiveArray.getCount(); i++)
	{
		const COLLADAFW::MeshPrimitive* meshPrimitive = meshPrimitiveArray[i];
		if ( !meshPrimitive )
		{
			continue;		
		}
		if( meshPrimitive->getPrimitiveType() != COLLADAFW::MeshPrimitive::TRIANGLES )
		{
			throw std::runtime_error("Only triangles/polygons mesh are supported.");
		}

		const COLLADAFW::Triangles* triangles = (const COLLADAFW::Triangles*) meshPrimitive;
		const COLLADAFW::UIntValuesArray& positionIndices = triangles->getPositionIndices();
		const COLLADAFW::UIntValuesArray& normalIndices = triangles->getNormalIndices();		
		
		//check if mesh has texture coordinates.
		bool hasTextCoords = false;
		if( triangles->hasUVCoordIndices() && m_textCoords.size() > 0 && m_loadType > LOAD_MATERIAL)
		{
			hasTextCoords = true;
		}

		int trianglesNumber = positionIndices.getCount();

		std::stringstream ss;
		ss << triangles->getMaterialId();
		std::string name = ss.str();
		//Create vertexshape with its material ID. Very important, name used to bind material to vertexshape during instanciation.
		vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::node::VertexShape::create( name );

		vgd::field::EditorRW< vgd::field::MFUInt32>	editVertexIndex	= vertexShape->getFVertexIndexRW();

		vgd::field::EditorRW< vgd::field::MFVec3f >	editPositions = vertexShape->getFVertexRW();
		editPositions->clear();
		editPositions->reserve( trianglesNumber );

		vgd::field::EditorRW< vgd::field::MFVec3f >	editNormals = vertexShape->getFNormalRW();
		editNormals->clear();
		editNormals->reserve( trianglesNumber );
		vertexShape->setNormalBinding( vgd::node::BIND_PER_VERTEX );

		vgd::field::EditorRW< vgd::field::MFVec2f > editTextCoords;
		if ( hasTextCoords )
		{
			vertexShape->createTexUnits( 2, 0, 1 );	// @todo FIXME multitexture multiTexcoord
			vertexShape->setTexCoordBinding( 0, vgd::node::BIND_PER_VERTEX );
			editTextCoords = vertexShape->getFTexCoordRW<vgd::field::MFVec2f>( 0 );
			editTextCoords->clear();
			editTextCoords->reserve( trianglesNumber );
		}

		//hashmap used to check if the vertex/normal/textCoord set doesn't exists yet.
		boost::unordered_map<std::size_t, int> hashmap;
		for ( size_t j = 0; j < trianglesNumber; j++ )
		{
			std::vector<float> hash_me;

			hash_me.push_back( m_positions[ positionIndices[j] ][0] );
			hash_me.push_back( m_positions[ positionIndices[j] ][1] );
			hash_me.push_back( m_positions[ positionIndices[j] ][2] );

			hash_me.push_back( m_normals[ normalIndices[j] ][0] );
			hash_me.push_back( m_normals[ normalIndices[j] ][1] );
			hash_me.push_back( m_normals[ normalIndices[j] ][2] );

			if ( hasTextCoords )
			{
				hash_me.push_back( m_textCoords[ triangles->getUVCoordIndicesArray()[0]->getIndices()[j] ][0] );
				hash_me.push_back( m_textCoords[ triangles->getUVCoordIndicesArray()[0]->getIndices()[j] ][1] );
				hash_me.push_back( m_textCoords[ triangles->getUVCoordIndicesArray()[0]->getIndices()[j] ][2] );
			}


			//create hash with vecotr of each coordinate.
			std::size_t hash = boost::hash_range(hash_me.begin(), hash_me.end());

			//if hash exist, adds index of existing set to vertex index.
			if( hashmap.find(hash) != hashmap.end() )
			{
				editVertexIndex->push_back( hashmap[hash] );
			}
			else
			{
				//adds all.
				editPositions->push_back( m_positions[ positionIndices[j] ] );
				editNormals->push_back( m_normals[ normalIndices[j] ] );

				if ( hasTextCoords )
				{
					editTextCoords->push_back( m_textCoords[ triangles->getUVCoordIndicesArray()[0]->getIndices()[j] ] );
				}
				
				editVertexIndex->push_back( editPositions->size()-1 );

				hashmap[hash] = editPositions->size()-1;
			}
		}
		vgd::field::EditorRW< vgd::field::MFPrimitive >	editPrimitive = vertexShape->getFPrimitiveRW();
		editPrimitive->clear();

		vgd::node::Primitive prim( vgd::node::Primitive::TRIANGLES, 0, editVertexIndex->size() );
		editPrimitive->push_back( prim );

		if ( vertexShape->getNormalBinding() != vgd::node::BIND_PER_VERTEX )
		{
			vertexShape->computeNormals();
		}

		group->addChild( vertexShape );
	}

	return true;
}


} // namespace importer

} // namespace vgOpenCOLLADA
