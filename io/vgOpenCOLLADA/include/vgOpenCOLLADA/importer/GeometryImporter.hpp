// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_IMPORTER_GEOMETRYIMPORTER_HPP
#define _VGOPENCOLLADA_IMPORTER_GEOMETRYIMPORTER_HPP


#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <boost/unordered_map.hpp>  

#include <vgOpenCOLLADA/convenience.hpp>
#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>

#include <COLLADAFWMeshPrimitive.h>
#include <COLLADAFWMesh.h>

namespace vgOpenCOLLADA
{

namespace importer
{

/**
 * @brief The COLLADA geometry importer.
 */
struct VGOPENCOLLADA_API GeometryImporter
{
	GeometryImporter( const COLLADAFW::Geometry* geometry, LOAD_TYPE loadType, vgd::Shp< boost::unordered_map< vgd::Shp< vgd::node::VertexShape >, int > > mapShapeMaterial );
	
	/**
	 * @brief Creates geometry.
	 * 
	 * @param geometry: the COLLADA geometry attribute.
	 * 
	 * @param mesh: the COLLADA mesh attribute of current geometry
	 *
	 * @return: a pair bool/group. Return false if the mesh don't create correctly.
	 * the group contains one or more vertexShape. Each vertexShape is a <triangles> tag.
	 */
	std::pair< bool, vgd::Shp< vgd::node::Group > > loadMesh();

	/**
	* @brief: Import all position for current mesh.
	*
	* @return: a vector of every position of current mesh
	*/
	void importMeshPositions();

	/**
	* @brief: Import all normals for current mesh.
	*
	* @return: a vector of every normals of current mesh
	*/
	void importMeshNormals();

	/**
	* @brief: Import all texture coordinates for current mesh.
	*
	* @return: a vector of every texture coordinates of current mesh
	*/
	void importMeshUVCoords();

	/**
	* @brief: Import primitives of the mesh considering the type. Each primitives (<triangles> tag) is a vertexShape.
	*
	* @return: bool. True if everything is ok.
	*/
	bool importMeshPrimitives( vgd::Shp< vgd::node::Group > group );

private:
	COLLADAFW::Mesh*			m_mesh;
	std::vector< vgm::Vec3f >	m_positions;
	std::vector< vgm::Vec3f >	m_normals;
	std::vector< vgm::Vec2f >	m_texCoords;
	LOAD_TYPE					m_loadType;

	vgd::Shp< boost::unordered_map< vgd::Shp< vgd::node::VertexShape >, int > > m_mapShapeMaterial;

};



} // namespace importer

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_IMPORTER_GEOMETRYIMPORTER_HPP
