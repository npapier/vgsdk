// VGSDK - Copyright (C) 2010 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_EXPORTER_GEOMETRYEXPORTER_HPP
#define _VGOPENCOLLADA_EXPORTER_GEOMETRYEXPORTER_HPP

#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>

#include "COLLADASWLibraryGeometries.h"

namespace vgOpenCOLLADA
{

namespace exporter
{

/**
 * @brief COLLADA geometry writer.
 */
struct VGOPENCOLLADA_API GeometryExporter : public COLLADASW::LibraryGeometries
{
	GeometryExporter(COLLADASW::StreamWriter * streamWriter, vgd::Shp< vgd::node::Group > sceneGraph, vgd::Shp< vgd::node::VertexShape > node);

	void doExport();

	void exportMesh( vgd::Shp< vgd::node::VertexShape > vertexShape );

	void exportPositions( vgd::Shp< vgd::node::VertexShape > vertexShape );

	void exportNormals( vgd::Shp< vgd::node::VertexShape > vertexShape );

	void exportVerticies( std::string meshName );

	void exportTriangles( vgd::Shp< vgd::node::VertexShape > vertexShape );

	std::vector<std::string> getGeomNameList();

private:
	vgd::Shp< vgd::node::Group >		m_sceneGraph;
	vgd::Shp< vgd::node::VertexShape >	m_node;
	std::string							m_currentGeometryName;
	std::vector<std::string>			m_geomNameList;
};

} // namespace exporter

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_EXPORTER_GEOMETRYEXPORTER_HPP

