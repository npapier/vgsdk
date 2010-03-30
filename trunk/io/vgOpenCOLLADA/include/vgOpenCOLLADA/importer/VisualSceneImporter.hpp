// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_IMPORTER_VISUALSCENEIMPORTER_HPP
#define _VGOPENCOLLADA_IMPORTER_VISUALSCENEIMPORTER_HPP


#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <COLLADAFWNode.h>

#include "vgOpenCOLLADA/convenience.hpp"
#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/Switch.hpp>
#include <vgd/node/VertexShape.hpp>

namespace vgOpenCOLLADA
{

namespace importer
{

/**
 * @brief The COLLADA visual scene importer.
 */
struct VGOPENCOLLADA_API VisualSceneImporter
{
	VisualSceneImporter( LOAD_TYPE loadType, vgd::Shp< vgd::node::Switch > switchMaterial, vgd::Shp< vgd::node::Switch > switchVertexShape );

	/**
	 * @brief Return the whole scene
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */
	std::pair< bool, vgd::Shp< vgd::node::Group > > getScene();

	/**
	 * @brief Creates a node as in the COLLADA file. 1 node = 1 group.
	 * 
	 * @param node: the COLLADA node.
	 * 
	 * @param vgsdkNode: the parent node in current vgsdk scene graph (m_group = root node)
	 */
	void createNode( const COLLADAFW::Node* node, vgd::Shp< vgd::node::Group > vgsdkNode );

	/**
	 * @brief Adds geometry transformation to the current node.
	 * 
	 * @param node: the COLLADA node.
	 * 
	 * @param vgsdkNode: the current node in current vgsdk scene graph (m_group = root node)
	 */
	void createNodeTransformation( const COLLADAFW::Node* node, vgd::Shp< vgd::node::Group > vgsdkNode );

	/**
	 * @brief Adds geometry to the current node.
	 * 
	 * @param node: the COLLADA node.
	 * 
	 * @param vgsdkNode: the current node in current vgsdk scene graph (m_group = root node)
	 */
	void createNodeGeometry( const COLLADAFW::Node* node, vgd::Shp< vgd::node::Group > vgsdkNode );

private:
	LOAD_TYPE						m_loadType;
	vgd::Shp< vgd::node::Switch >	m_switchMaterial;
	vgd::Shp< vgd::node::Switch >	m_switchVertexShape;

};


} // namespace importer

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_IMPORTER_VISUALSCENEIMPORTER_HPP
