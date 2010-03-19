// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/exporter/GeometryExporter.hpp"

#include <vgDebug/Global.hpp>
#include <vgd/visitor/helpers.hpp>

#include "COLLADASWSource.h"
#include "COLLADASWBaseInputElement.h"
#include "COLLADASWPrimitves.h"
#include "COLLADASWControlVertices.h"
#include "COLLADASWConstants.h"

namespace vgOpenCOLLADA
{

namespace exporter
{
	
GeometryExporter::GeometryExporter(COLLADASW::StreamWriter * streamWriter, vgd::Shp< vgd::node::Group > sceneGraph, vgd::Shp< vgd::node::VertexShape > node) :
COLLADASW::LibraryGeometries ( streamWriter ),
m_sceneGraph( sceneGraph ),
m_node( node )
{
}


void GeometryExporter::doExport()
{
	openLibrary();

	if (m_node)
	{
		//export vertexShape only
		vgDebug::get().logDebug("Exporting VertexShape");
		exportMesh( m_node );
	}
	else
	{
		//export all
		vgDebug::get().logDebug("Exporting geometry...");
	}

	closeLibrary();
}


void GeometryExporter::exportMesh( vgd::Shp< vgd::node::VertexShape > vertexShape )
{
	m_currentGeometryName = COLLADASW::Utils::checkNCName( COLLADASW::NativeString( COLLADASW::LibraryGeometries::GEOMETRY_ID_PRAEFIX + vertexShape->getName() ) );

	openMesh( m_currentGeometryName, COLLADASW::Utils::checkNCName( COLLADASW::NativeString(vertexShape->getName()) ) );
	
	m_geomNameList.push_back(m_currentGeometryName);

	exportPositions( vertexShape );
	exportNormals( vertexShape );
	exportVerticies( m_currentGeometryName );
	exportTriangles( vertexShape );
	
	closeMesh();
}

void GeometryExporter::exportPositions( vgd::Shp< vgd::node::VertexShape > vertexShape )
{
	COLLADASW::FloatSource source( mSW );
	source.setId( m_currentGeometryName + COLLADASW::LibraryGeometries::POSITIONS_SOURCE_ID_SUFFIX );
	source.setArrayId( m_currentGeometryName + COLLADASW::LibraryGeometries::POSITIONS_SOURCE_ID_SUFFIX + COLLADASW::LibraryGeometries::ARRAY_ID_SUFFIX );
	source.setAccessorStride( 3 );
	source.getParameterNameList().push_back( "X" );
	source.getParameterNameList().push_back( "Y" );
	source.getParameterNameList().push_back( "Z" );

	vgd::field::EditorRO< vgd::field::MFVec3f >	vertex	= vertexShape->getFVertexRO();
	int vertexCount = vertex->size();
	source.setAccessorCount( vertexCount );
	source.prepareToAppendValues();

	for( int i = 0; i < vertexCount; ++i )
	{
		vgm::Vec3f vec = vertex.get()[0][i];
		source.appendValues( vec[0], vec[1], vec[2] );
	}

	source.finish();
}


void GeometryExporter::exportNormals( vgd::Shp< vgd::node::VertexShape > vertexShape )
{
	COLLADASW::FloatSource source( mSW );
	source.setId( m_currentGeometryName + COLLADASW::LibraryGeometries::NORMALS_SOURCE_ID_SUFFIX );
	source.setArrayId( m_currentGeometryName + COLLADASW::LibraryGeometries::NORMALS_SOURCE_ID_SUFFIX + COLLADASW::LibraryGeometries::ARRAY_ID_SUFFIX );
	source.setAccessorStride( 3 );

	source.getParameterNameList().push_back( "X" );
	source.getParameterNameList().push_back( "Y" );
	source.getParameterNameList().push_back( "Z" );


	vgd::field::EditorRO< vgd::field::MFVec3f >	normals = vertexShape->getFNormalRO();
	int normalCount = normals->size();
	source.setAccessorCount( normalCount );
	source.prepareToAppendValues();

	for( int i = 0; i < normalCount; ++i )
	{
		vgm::Vec3f vec = normals.get()[0][i];
		source.appendValues( vec[0], vec[1], vec[2] );
	}

	source.finish();
}


void GeometryExporter::exportVerticies( std::string meshName )
{
	COLLADASW::VerticesElement vertices( mSW );
	vertices.setId( meshName + COLLADASW::LibraryGeometries::VERTICES_ID_SUFFIX );
	vertices.getInputList().push_back( COLLADASW::Input( COLLADASW::POSITION, "#" + meshName + COLLADASW::LibraryGeometries::POSITIONS_SOURCE_ID_SUFFIX ) );
	vertices.add();
}


void GeometryExporter::exportTriangles( vgd::Shp< vgd::node::VertexShape > vertexShape )
{
	COLLADASW::Triangles triangles( mSW );

	vgd::field::EditorRO< vgd::field::MFUInt32>	vertexIndex	= vertexShape->getFVertexIndexRO();	
	int numberOfFaces = vertexIndex->size();
	triangles.setCount( numberOfFaces );
	
	//@todo: need material symbol here (!= material name/id, it's only used in instanciation)
	triangles.setMaterial( "default" );

	int offset = 0;
	triangles.getInputList().push_back( COLLADASW::Input( COLLADASW::VERTEX, "#" + m_currentGeometryName + COLLADASW::LibraryGeometries::VERTICES_ID_SUFFIX, offset++ ) );
	triangles.getInputList().push_back( COLLADASW::Input( COLLADASW::NORMAL, "#" + m_currentGeometryName + COLLADASW::LibraryGeometries::NORMALS_SOURCE_ID_SUFFIX, offset++ ) );

	triangles.prepareToAppendValues();

	for( int i = 0; i < numberOfFaces; ++i )
	{
		//vgm::Vec3f vec = vertexIndex.get()[0][i];
		//2 times, one for vertices, one for normals.
		triangles.appendValues( vertexIndex.get()[0][i] );
		triangles.appendValues( vertexIndex.get()[0][i] );
	}

	triangles.finish();
}


std::vector<std::string> GeometryExporter::getGeomNameList()
{
	return m_geomNameList;
}


} // namespace exporter

} // namespace vgOpenCOLLADA

