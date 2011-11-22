// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgOpenCOLLADA/exporter/GeometryExporter.hpp"

#include <vgDebug/helpers.hpp>
#include <vgd/node/MultipleInstances.hpp>
#include <vgd/visitor/helpers.hpp>

#include "COLLADASWSource.h"
#include "COLLADASWBaseInputElement.h"
#include "COLLADASWControlVertices.h"
#include "COLLADASWConstants.h"

namespace vgOpenCOLLADA
{

namespace exporter
{
	
GeometryExporter::GeometryExporter( COLLADASW::StreamWriter * streamWriter, collectedMapType collectedMap, vgOpenCOLLADA::Settings exportSettings )
:	COLLADASW::LibraryGeometries ( streamWriter ),
	m_collectedMap( collectedMap ),
	m_exportSettings( exportSettings )
{
}



void GeometryExporter::doExport()
{
	openLibrary();

	//export all
	vgLogDebug("Exporting geometry...");
	
	typedef collectedMapType::left_map::const_iterator left_const_iterator;

	for( left_const_iterator left_iter = m_collectedMap.left.begin(), iend = m_collectedMap.left.end();
		 left_iter != iend; ++left_iter )
	{
		exportMesh( left_iter->first, left_iter->second );
		m_texCoordsList.clear();
	}


	closeLibrary();
}



void GeometryExporter::exportMesh( vgd::Shp< vge::technique::CollectedShape > collectedShape, vgd::Shp< vge::technique::CollectedMaterial > collectedMaterial )
{
	vgd::Shp< vgd::node::Shape > shape = collectedShape->getShape();
	vgd::Shp< vgd::node::VertexShape > vertexShape;
	std::string shapeName;
	if( collectedShape->getShapeType() == vge::technique::VERTEXSHAPE )
	{
		vertexShape = vgd::dynamic_pointer_cast< vgd::node::VertexShape >( shape );
		shapeName = vertexShape->getName();
	}
	else if( collectedShape->getShapeType() == vge::technique::MULTIPLEINSTANCES )
	{
		vgd::Shp< vgd::node::MultipleInstances > multipleInstance = vgd::dynamic_pointer_cast< vgd::node::MultipleInstances >( shape );
		vgd::Shp< vgd::node::Node > shape = multipleInstance->getShape();
		
		if( shape->isAKindOf< vgd::node::VertexShape >() )
		{
			vertexShape = vgd::dynamic_pointer_cast< vgd::node::VertexShape >( shape->shpFromThis() );
			shapeName = multipleInstance->getName();
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}

	//check if geom name is already used.
	m_currentGeometryName = COLLADASW::Utils::checkNCName( COLLADASW::NativeString( COLLADASW::LibraryGeometries::GEOMETRY_ID_PRAEFIX + shapeName ) );
	bool inserted = m_geomIds.insert( m_currentGeometryName ).second;

	int counter = 0;
	while( !inserted )
	{
		std::stringstream ss;
		ss << counter << std::endl;
		m_currentGeometryName = COLLADASW::Utils::checkNCName( COLLADASW::NativeString( COLLADASW::LibraryGeometries::GEOMETRY_ID_PRAEFIX + shapeName + ss.str() ) );
		inserted = m_geomIds.insert( m_currentGeometryName ).second;
		counter++;
	}

	std::string currentGeometryMaterialSymbol;
	if( collectedMaterial->getMaterial() && m_exportSettings.getLevel() > GEOMETRY )
	{
		currentGeometryMaterialSymbol = COLLADASW::Utils::checkNCName( COLLADASW::NativeString( collectedMaterial->getMaterial()->getName() ) ) + "_symbol";
	}
	else
	{
		currentGeometryMaterialSymbol = COLLADASW::Utils::checkNCName( COLLADASW::NativeString( "DefaultWhole" ) ) + "_symbol";
	}
	collectedMaterial->setMaterialSymbol( currentGeometryMaterialSymbol );

	//open mesh & geometry tag.
	openMesh( m_currentGeometryName, COLLADASW::Utils::checkNCName( COLLADASW::NativeString(vertexShape->getName()) ) );
	
	collectedShape->setColladaShapeName( m_currentGeometryName );

	exportPositions( vertexShape );
	exportNormals( vertexShape );
	if( m_exportSettings.getLevel() > MATERIAL )
	{
		exportTexCoords( vertexShape );
	}
	exportVerticies( m_currentGeometryName );

	vgd::field::EditorRO< vgd::field::MFPrimitive > primitives = vertexShape->getFPrimitiveRO();
	for( uint i = 0; i < primitives->size(); ++i )
	{
		if( (*primitives)[i].getType() == vgd::node::Primitive::TRIANGLES )
		{
			exportPrimitives< COLLADASW::Triangles >( vertexShape, currentGeometryMaterialSymbol );
		}
		else if( (*primitives)[i].getType() == vgd::node::Primitive::QUADS )
		{
			exportPrimitives< COLLADASW::Polylist >( vertexShape, currentGeometryMaterialSymbol );
		}
		else
		{
			assert( false && "Primitives type not supported." );
		}
	}

	closeMesh();
	closeGeometry();
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
		vgm::Vec3f vec = (*vertex)[i];
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
		vgm::Vec3f vec = (*normals)[i];
		source.appendValues( vec[0], vec[1], vec[2] );
	}

	source.finish();
}



void GeometryExporter::exportTexCoords( vgd::Shp< vgd::node::VertexShape > vertexShape )
{
	
	for( int i = 0; i < vertexShape->getNumTexUnits(); i++ )
	{
		std::stringstream ss;

		ss << "-" << i;

		COLLADASW::FloatSource source( mSW );
		source.setId( m_currentGeometryName + COLLADASW::LibraryGeometries::TEXCOORDS_SOURCE_ID_SUFFIX + ss.str() );
		source.setArrayId( m_currentGeometryName + COLLADASW::LibraryGeometries::TEXCOORDS_SOURCE_ID_SUFFIX + COLLADASW::LibraryGeometries::ARRAY_ID_SUFFIX + ss.str()  );
		m_texCoordsList.push_back( "#" + m_currentGeometryName + COLLADASW::LibraryGeometries::TEXCOORDS_SOURCE_ID_SUFFIX + ss.str() );
		source.setAccessorStride( 3 );

		source.getParameterNameList().push_back( "S" );
		source.getParameterNameList().push_back( "T" );
		source.getParameterNameList().push_back( "P" );


		vgd::field::EditorRO< vgd::field::MFVec2f >	texCoords = vertexShape->getFTexCoordRO<vgd::field::MFVec2f>( i );
		int texCoordsCount = texCoords->size();
		source.setAccessorCount( texCoordsCount );
		source.prepareToAppendValues();

		for( int i = 0; i < texCoordsCount; ++i )
		{
			vgm::Vec2f vec = (*texCoords)[i];
			source.appendValues( vec[0], vec[1], 0 );
		}

		source.finish();
	}
}



void GeometryExporter::exportVerticies( std::string meshName )
{
	COLLADASW::VerticesElement vertices( mSW );
	vertices.setId( meshName + COLLADASW::LibraryGeometries::VERTICES_ID_SUFFIX );
	vertices.getInputList().push_back( COLLADASW::Input( COLLADASW::POSITION, "#" + meshName + COLLADASW::LibraryGeometries::POSITIONS_SOURCE_ID_SUFFIX ) );
	vertices.add();
}



void GeometryExporter::exportVCount(int numberOfFaces, COLLADASW::Polylist *primitive )
{
	for( uint i = 0; i < numberOfFaces / 4; ++i )
	{
		primitive->getVCountList().push_back( 4 );
	}
}



void GeometryExporter::exportVCount(int numberOfFaces, COLLADASW::Triangles *primitive )
{
	//nothing to do for Triangles.
}



} // namespace exporter

} // namespace vgOpenCOLLADA

