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

namespace vgOpenCOLLADA
{

namespace exporter
{

	typedef boost::bimap< vgd::Shp< vge::technique::CollectedShape >, vgd::Shp< vge::technique::CollectedMaterial > > collectedMapType;

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
	 * @param collectedShape a vgSDK shape to export
	 *
	 * @param collectedMaterial vgSDK material binded to the shape
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
	 * @brief export COLLADA verticies tag
	 *
	 * @param meshName the name of the mesh
	 */
	void exportVerticies( std::string meshName );

	/**
	 * @brief export all triangle (vertex index)
	 *
	 * @param vertexShape the vgSDK shape to export
	 *
	 * @param materialSymbol symbol of the material binded to the shape
	 */
	void exportTriangles( vgd::Shp< vgd::node::VertexShape > vertexShape, std::string materialSymbol );

private:
	collectedMapType					m_collectedMap;
	std::string							m_currentGeometryName;
	std::vector<std::string>			m_texCoordsList;
};

} // namespace exporter

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_EXPORTER_GEOMETRYEXPORTER_HPP

