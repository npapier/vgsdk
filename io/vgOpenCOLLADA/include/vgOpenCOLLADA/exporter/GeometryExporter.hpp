// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_EXPORTER_GEOMETRYEXPORTER_HPP
#define _VGOPENCOLLADA_EXPORTER_GEOMETRYEXPORTER_HPP

#include <boost/bimap.hpp>

#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>

#include <vge/technique/CollectNode.hpp>

#include "COLLADASWLibraryGeometries.h"
#include "COLLADASWPrimitves.h"

namespace vgOpenCOLLADA
{

namespace exporter
{

typedef vge::technique::collectedMapType	collectedMapType;

/**
 * @brief COLLADA geometry writer.
 */
struct VGOPENCOLLADA_API GeometryExporter : public COLLADASW::LibraryGeometries
{
	GeometryExporter( COLLADASW::StreamWriter * streamWriter, collectedMapType collectedMap );

	/**
	 * @brief start exporting
	 */
	void doExport();

	/**
	 * @brief export a COLLADA Mesh (a vgSDK VertexShape)
	 *
	 * @param collectedShape		a vgSDK shape to export
	 *
	 * @param collectedMaterial		vgSDK material binded to the shape
	 */
	void exportMesh( vgd::Shp< vge::technique::CollectedShape > collectedShape, vgd::Shp< vge::technique::CollectedMaterial > collectedMaterial );

	/**
	 * @brief export all positions of the shape (vertex)
	 *
	 * @param vertexShape the vgSDK shape to export
	 */
	void exportPositions( vgd::Shp< vgd::node::VertexShape > vertexShape );

	/**
	 * @brief export all normals of the shape
	 *
	 * @param vertexShape the vgSDK shape to export
	 */
	void exportNormals( vgd::Shp< vgd::node::VertexShape > vertexShape );

	/**
	 * @brief export all texture coordinates of the shape
	 *
	 * @param vertexShape the vgSDK shape to export
	 */
	void exportTexCoords( vgd::Shp< vgd::node::VertexShape > vertexShape );
	
	/**
	 * @brief export		COLLADA verticies tag
	 *
	 * @param meshName		the name of the mesh
	 */
	void exportVerticies( std::string meshName );

	/**
	 * @brief export all primitives (vertex index). T = COLLADA primitive type (triangle/polylist).
	 *
	 * @param vertexShape		the vgSDK shape to export
	 *
	 * @param materialSymbol	symbol of the material binded to the shape
	 */
	template< typename T >
	void exportPrimitives( vgd::Shp< vgd::node::VertexShape > vertexShape, std::string materialSymbol )
	{
		T primitive( mSW );

		vgd::field::EditorRO< vgd::field::MFUInt32>	vertexIndex	= vertexShape->getFVertexIndexRO();	
		int numberOfFaces = vertexIndex->size();
		primitive.setCount( numberOfFaces );
		
		primitive.setMaterial( materialSymbol );

		int offset = 0;
		primitive.getInputList().push_back( COLLADASW::Input( COLLADASW::VERTEX, "#" + m_currentGeometryName + COLLADASW::LibraryGeometries::VERTICES_ID_SUFFIX, offset++ ) );
		primitive.getInputList().push_back( COLLADASW::Input( COLLADASW::NORMAL, "#" + m_currentGeometryName + COLLADASW::LibraryGeometries::NORMALS_SOURCE_ID_SUFFIX, offset++ ) );

		for( uint i = 0; i < m_texCoordsList.size(); i++ )
		{
			primitive.getInputList().push_back( COLLADASW::Input( COLLADASW::TEXCOORD, m_texCoordsList[i], offset++, i+1 ) );
		}

		exportVCount( numberOfFaces, &primitive );

		primitive.prepareToAppendValues();
		for( uint i = 0; i < numberOfFaces; ++i )
		{
			//2 times, one for vertices, one for normals, and one for each texture.
			primitive.appendValues( (*vertexIndex)[i] );
			primitive.appendValues( (*vertexIndex)[i] );

			for( uint j = 0; j < m_texCoordsList.size(); j++ )
			{
				primitive.appendValues( (*vertexIndex)[i] );
			}
		}

		primitive.finish();
	}

	/**
	 * @brief export primitive face number (<vcount> COLLADA tag).
	 *
	 * @param numberOfFaces		number of face of the shape.
	 *
	 * @param primitive			current COLLADA primitive.
	 */
	void exportVCount(int numberOfFaces, COLLADASW::Polylist *primitive );

	/**
	 * @brief export primitive face number (<vcount> COLLADA tag). Useless for COLLADA triangle primitive tag.
	 *
	 * @param numberOfFaces		number of face of the shape.
	 *
	 * @param primitive			current COLLADA primitive.
	 */
	void exportVCount(int numberOfFaces, COLLADASW::Triangles *primitive );

private:
	collectedMapType					m_collectedMap;
	std::string							m_currentGeometryName;
	std::vector<std::string>			m_texCoordsList;

	std::set< std::string >				m_geomIds;

};

} // namespace exporter

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_EXPORTER_GEOMETRYEXPORTER_HPP

