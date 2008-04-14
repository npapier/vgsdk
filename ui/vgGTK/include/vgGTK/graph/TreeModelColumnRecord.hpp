// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_GRAPH_TREEMODELCOLUMNRECORD_HPP_
#define _VGGTK_GRAPH_TREEMODELCOLUMNRECORD_HPP_

#include <gtkmm/treemodelcolumn.h>

#include <pangomm/fontdescription.h>

#include <vgd/Shp.hpp>
#include <vgd/node/Node.hpp>

#include "vgGTK/vgGTK.hpp"



namespace vgGTK
{

namespace graph
{



/**
 * @brief	Provides the description of the columns stored in TreeStore provided by TreeModelProvider.
 *
 * @see		TreeModelProvider
 */
struct VGGTK_API TreeModelColumnRecord : public Gtk::TreeModelColumnRecord
{
	/**
	 * @brief	Constructor
	 */
	TreeModelColumnRecord();

	/**
	 * @name	Tree Columns
	 */
	//@{
	Gtk::TreeModelColumn< vgd::Shp< vgd::node::Node > >	m_nodeColumn;			///< Defines the model column for the reference to a vgd::node::Node.
	Gtk::TreeModelColumn< Glib::ustring >				m_nameColumn;			///< Defines the model column for the name.
	Gtk::TreeModelColumn< Glib::ustring >				m_typeColumn;			///< Defines the model column for the type.
	Gtk::TreeModelColumn< bool >						m_activeColumn;			///< Defines the model column for the activeness (the node is rendered).
	Gtk::TreeModelColumn< bool >						m_sharedColumn;			///< Defines the model column for the sharedness (the node has several parents).
	//@}
};



} // namespace graph

} // namespace vgGTK



#endif /*_VGGTK_GRAPH_TREEMODELCOLUMNRECORD_HPP_*/
