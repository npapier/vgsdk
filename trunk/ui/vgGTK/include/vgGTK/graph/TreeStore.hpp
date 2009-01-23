#ifndef __VGGTK_GRAPH_TREESTORE_HPP__
#define __VGGTK_GRAPH_TREESTORE_HPP__

#include <gtkmm/treestore.h>

#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>



namespace vgGTK
{

namespace graph
{



struct TreeModelColumnRecord;



/**
 * @brief	Implements a specialized Gtk::TreeStore that handles drag and drop operations.
 */
struct TreeStore : public Gtk::TreeStore
{
	/**
	 * @brief	Constructor
	 */
	TreeStore( const TreeModelColumnRecord & columns );
	
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
	
protected:

	/**
	 * @name	Drag & Drop Overrides
	 */
	//@{
	bool drag_data_delete_vfunc( const TreeModel::Path& path );
	bool drag_data_received_vfunc( const TreeModel::Path & dest, const Gtk::SelectionData & selection_data );
	bool row_draggable_vfunc( const Gtk::TreeModel::Path & path ) const;
	bool row_drop_possible_vfunc( const Gtk::TreeModel::Path & dest, const Gtk::SelectionData & selection_data ) const;
	//@}
	
private:

	const TreeModelColumnRecord		& m_columns;	///< Keeps track of the column of the managed tree model.
	vgd::Shp< vgd::node::Group >	m_root;			///< References the root node.
	
	/**
	 * @brief	Update the activeness of the child rows of the given model row.
	 */
	void updateChildRowsActiveness( const Gtk::TreeRow & parentRow );
};



} // namespace graph

} // namespace vgGTK

#endif // __VGGTK_GRAPH_TREESTORE_HPP__
