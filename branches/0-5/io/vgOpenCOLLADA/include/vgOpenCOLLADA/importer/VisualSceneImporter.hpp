// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGOPENCOLLADA_IMPORTER_VISUALSCENEIMPORTER_HPP
#define _VGOPENCOLLADA_IMPORTER_VISUALSCENEIMPORTER_HPP


#include "vgOpenCOLLADA/vgOpenCOLLADA.hpp"

#include <boost/unordered_map.hpp>

#include <COLLADAFWNode.h>

#include "vgOpenCOLLADA/Settings.hpp"
#include "vgOpenCOLLADA/importer/ExtraDataMultiInstance.hpp"

#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/Switch.hpp>
#include <vgd/node/VertexShape.hpp>
#include <vgd/node/MultipleInstances.hpp>


namespace vgOpenCOLLADA
{

namespace importer
{

struct Reader;

/**
 * @brief The COLLADA visual scene importer.
 */
struct VGOPENCOLLADA_API VisualSceneImporter
{
	VisualSceneImporter( vgOpenCOLLADA::Settings settings, Reader *reader );

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
	 * 
	 * @param name: name of the node. if empty, name of the parent node.
	 */
	void createNode( const COLLADAFW::Node* node, vgd::Shp< vgd::node::Group > vgsdkNode, std::string name );

private:

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
	 * 
	 * @param name: name of the node. if empty, name of the parent node.
	 */
	void createNodeGeometry( const COLLADAFW::Node* node, vgd::Shp< vgd::node::Group > vgsdkNode, std::string shapeName );

	/**
	 * @brief Create a multiple instances with a list of matrix.
	 * 
	 * @param multipleInstances: the multiple instances to create.
	 * 
	 * @param extraInfos: matrix list for the multiple instance.
	 */
	void createMultipleInstances( vgd::Shp< vgd::node::MultipleInstances > multipleInstances, std::vector< MultiInstanceInfo > extraInfos );

	vgOpenCOLLADA::Settings			m_settings;
	Reader							*m_reader;
	vgd::Shp< vgd::node::Switch >	m_switchMaterial;
	vgd::Shp< vgd::node::Switch >	m_switchVertexShape;
	vgd::Shp< boost::unordered_map< vgd::Shp< vgd::node::VertexShape >, int > > m_mapShapeMaterial;
	vgd::Shp< boost::unordered_map< std::string, vgd::Shp< vgd::node::Group > > > m_mapMaterial;

};


} // namespace importer

} // namespace vgOpenCOLLADA

#endif // _VGOPENCOLLADA_IMPORTER_VISUALSCENEIMPORTER_HPP
