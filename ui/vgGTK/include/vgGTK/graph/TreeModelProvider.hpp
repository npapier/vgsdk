// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_GRAPH_TREEMODELPROVIDER_HPP_
#define _VGGTK_GRAPH_TREEMODELPROVIDER_HPP_

#include <gtkmm/treestore.h>

#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>

#include "vgGTK/vgGTK.hpp"
#include "vgGTK/graph/TreeModelColumnRecord.hpp"



namespace vgGTK
{

namespace graph
{



/**
 * @brief	Builds and maintains a Gtk::TreeModel synchronized with a given vgSDK sub-graph.
 *
 * The TreeModelProvider is meant to visualize a vgSDK sub-graph in GTK TreeView by managing
 * a GTK TreeModel.
 */
struct VGGTK_API TreeModelProvider
{
	/**
	 * @brief	Constructor
	 */
	TreeModelProvider();


	/**
	 * @name	Accessors
	 */
	//@{
	/**
	 * @brief	Retrioeves the column record used for the managed model
	 *
	 * @return	a reference to the tree model column record
	 */
	const TreeModelColumnRecord & getColumnRecord() const;

	/**
	 * @brief	Retrieves the reference to the managed tree model.
	 *
	 * @return	a reference to a Gtk::TreeModel
	 */
	const Glib::RefPtr< Gtk::TreeModel > getModel() const;

	/**
	 * @brief	Refreshes the managed model to reflect graph changes.
	 */
	void refresh();

	/**
	 * @brief	Assigns a new root node.
	 *
	 * The old model content will be cleared. If the passed root reference is empty,
	 * the model will remain empty.
	 *
	 * @param	root	a reference to the new root node, can be empty
	 */
	void setRoot( vgd::Shp< vgd::node::Group > root );
	//@}

private:

	TreeModelColumnRecord			m_columnRecord;	///< Keeps track of the column of the managed tree model.
	Glib::RefPtr< Gtk::TreeStore >	m_treeStore;	///< References the managed tree model.
	vgd::Shp< vgd::node::Group >	m_root;			///< References the root node.
};



} // namespace graph

} // namespace vgGTK



#endif /*_VGGTK_GRAPH_TREEMODELPROVIDER_HPP_*/
