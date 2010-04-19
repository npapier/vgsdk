// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_NODE_HIDDENNODE_HPP_
#define _VGGTK_NODE_HIDDENNODE_HPP_

#include "vgGTK/vgGTK.hpp"

#include <gtkmm/menu.h>

#include <vgd/Shp.hpp>
#include <vgd/WeakPtr.hpp>
#include <vgd/node/VertexShape.hpp>



namespace vgGTK
{

namespace node
{


struct HiddenNode
{
	HiddenNode(vgd::Shp< vgd::node::VertexShape > node );

	~HiddenNode();

	void hide();

	void restorePrimitives();

	vgd::Shp< vgd::node::VertexShape > getNode();

	bool hasNode();

	Gtk::MenuItem * getMenuItem();

	void setMenuItem( Gtk::MenuItem * menuItem );

private:
	vgd::WeakPtr< vgd::node::VertexShape >	m_node;
	std::vector< vgd::node::Primitive >		m_primitives;
	Gtk::MenuItem							* m_hiddenMenuItem;
};



} // namespace node

} // namespace vgGTK

#endif /*_VGGTK_NODE_ACTIONSNODE_HPP_*/
