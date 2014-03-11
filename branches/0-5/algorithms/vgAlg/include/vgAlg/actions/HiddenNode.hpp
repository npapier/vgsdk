// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_HIDDENNODE_HPP_
#define _VGALG_ACTIONS_HIDDENNODE_HPP_

#include "vgAlg/vgAlg.hpp"

//#include <gtkmm/menu.h>

#include <vgd/Shp.hpp>
#include <vgd/Wkp.hpp>
#include <vgd/node/VertexShape.hpp>



namespace vgAlg
{

namespace actions
{

/**
 * @brief	Structure that contains a hidden node.
 *			Node is hidden by deletting its primitives.
 */
struct VGALG_API HiddenNode
{
	HiddenNode(vgd::Shp< vgd::node::VertexShape > node );

	~HiddenNode();

	/**
	* @brief	Hide the node by deleting its primitives.
	*			Primitives are stocked in m_primitives.
	*/
	void hide();

	/**
	* @brief	Show the node by resdtoring its primitives
	*/
	void restorePrimitives();

	/**
	* @brief	Get the current node.
	*
	* @return	the current node.
	*/
	vgd::Shp< vgd::node::VertexShape > getNode();

	/**
	* @brief	Check if the hidden node still existe. A node can be deleted even if it is hidden.
	*
	* @return	true if current node exists.
	*/
	bool hasNode();

private:
	vgd::Wkp< vgd::node::VertexShape >		m_node;
	std::vector< vgd::node::Primitive >		m_primitives;
};



} // namespace actions

} // namespace vgAlg

#endif /*_VGALG_ACTIONS_HIDDENNODE_HPP_*/
