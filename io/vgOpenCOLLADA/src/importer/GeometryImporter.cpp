// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/importer/GeometryImporter.hpp"
#include <vgOpenCOLLADA/importer/Reader.hpp>

#include <COLLADAFWPolygons.h>
#include <COLLADAFWTriangles.h>

#include <vgOpenCOLLADA/importer/TPrimitiveImporter.hpp>

namespace vgOpenCOLLADA
{

namespace importer
{

GeometryImporter::GeometryImporter( const COLLADAFW::Geometry* geometry, vgOpenCOLLADA::Settings settings, Reader *reader ) :
m_settings( settings ),
m_mapShapeMaterial( reader->getMapShapeMaterial() )
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

	if ( totalTrianglesCount < 1 && m_mesh->getPolygonsPolygonCount() < 1 )
	{
		throw std::runtime_error("Only triangles/polygons mesh are supported.");
	}

	importMeshPositions();

	importMeshNormals();

	importMeshUVCoords();

	retVal.first = importMeshPrimitives( group );

	return retVal;
}



void GeometryImporter::importMeshPositions()
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



void GeometryImporter::importMeshNormals()
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



void GeometryImporter::importMeshUVCoords()
{
	const COLLADAFW::MeshVertexData& uvCoordinates = m_mesh->getUVCoords();
	size_t num = uvCoordinates.getNumInputInfos();
	COLLADAFW::MeshVertexData::InputInfos* inputInfo;
	const COLLADAFW::MeshVertexData::InputInfosArray& uvInputInfos = uvCoordinates.getInputInfosArray();
	int counter = 0;

	for( int i = 0; i < num; ++i )
	{
		std::vector< vgm::Vec2f > texCoords;
		inputInfo = uvInputInfos[ i ];

		int32 texCoordSize = inputInfo->mLength;
		int32 texCoordStride = inputInfo->mStride;

		const COLLADAFW::FloatArray* texCoordArray = uvCoordinates.getFloatValues();

		int32 texCoordCount = (texCoordSize / texCoordStride);

		for ( int i = 0; i < texCoordCount; ++i)
		{
			texCoords.push_back(vgm::Vec2f( (float)(*texCoordArray)[texCoordStride*i + counter], (float)(*texCoordArray)[texCoordStride*i + 1 + counter] ));
		}
		
		m_texCoords.push_back( texCoords );

		counter += texCoordCount;
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

		if( meshPrimitive->getPrimitiveType() == COLLADAFW::MeshPrimitive::TRIANGLES )
		{
			TPrimitiveImporter< COLLADAFW::Triangles > importer( m_positions, m_normals, m_texCoords, m_settings, m_mapShapeMaterial, group, meshPrimitive );
			importer.importMeshPrimitives();
		}
		else if( meshPrimitive->getPrimitiveType() == COLLADAFW::MeshPrimitive::POLYGONS )
		{
			PrimitivePolygonsImporter importer( m_positions, m_normals, m_texCoords, m_settings, m_mapShapeMaterial, group, meshPrimitive );
			importer.importMeshPrimitives();
		}
		else
		{
			throw std::runtime_error("Only triangles/polylist mesh are supported.");
		}
	}

	return true;
}


} // namespace importer

} // namespace vgOpenCOLLADA
