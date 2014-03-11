#include "vgGTK/graph/TreeStore.hpp"

#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/Node.hpp>

#include "vgGTK/graph/TreeModelFillVisitor.hpp"



namespace vgGTK
{

namespace graph
{



TreeStore::TreeStore( const TreeModelColumnRecord & columns )
:	Gtk::TreeStore( columns ),
	m_columns( columns )
{}



bool TreeStore::drag_data_delete_vfunc( const TreeModel::Path & path )
{
	// Gets the index of the child node to remive.
	const int	childIndex = path.back();
	
	
	// Gets the parent paths.
	Gtk::TreeModel::Path	parentPath( path );
	
	parentPath.up();
	
	
	// Gets iterators on the child and parent row.
	Gtk::TreeIter	parentRow = get_iter( parentPath );
	
	
	// Now unreferences the child node from its parent node.
	if( parentRow )
	{
		vgd::Shp< vgd::node::Group >	parentNode	= vgd::dynamic_pointer_cast< vgd::node::Group >( parentRow->get_value( m_columns.m_nodeColumn ) );
		
		// Updates the child node list and the child rows activeness
		parentNode->removeChild( childIndex );
		updateChildRowsActiveness( *parentRow );
	}
	
	
	// Do the normal processing.
	return Gtk::TreeStore::drag_data_delete_vfunc( path );
}



bool TreeStore::drag_data_received_vfunc( const TreeModel::Path & dest, const Gtk::SelectionData & selection_data )
{
	// Do the normal processing.
	if( Gtk::TreeStore::drag_data_received_vfunc(dest, selection_data) == false )
	{
		return false;
	}
	
	// Retrieves the path of the row that has been dropped.
	Gtk::TreePath	childPath;
	
	Gtk::TreePath::get_from_selection_data(selection_data, childPath);
	
	
	// Retrieves the index for the futur child position in its parent.
	const int	insertIndex = dest.back();
	
	
	// Retrieves the path of the futur parent node.
	Gtk::TreePath	parentPath( dest );
	
	parentPath.up();
	
	
	// Gets iterators on the parent and child rows.
	Gtk::TreeIter	childRow	= get_iter( childPath );
	Gtk::TreeIter	parentRow	= get_iter( parentPath );
	
	
	// Now references the child node in its new parent
	if( childRow && parentRow )
	{
		vgd::Shp< vgd::node::Node >		childNode	= childRow->get_value( m_columns.m_nodeColumn );
		vgd::Shp< vgd::node::Group >	parentNode	= vgd::dynamic_pointer_cast< vgd::node::Group >( parentRow->get_value( m_columns.m_nodeColumn ) );
		
		// Updates the parent's children list and child rows activeness
		parentNode->insertChild( childNode, insertIndex );
		updateChildRowsActiveness( *parentRow );
	}
	
	
	// Job's done.
	return true;
}



void TreeStore::refresh()
{
	// Clears the the model's content.
	clear();


	// Fills the model according to the given new root
	if( m_root )
	{
		TreeModelFillVisitor	fillVisitor( *this, m_columns );

		m_root->traverse( fillVisitor );
	}
}



bool TreeStore::row_draggable_vfunc( const Gtk::TreeModel::Path & path ) const
{
	// All rows, expect the root, can be dragged.
	return path.get_depth() > 1;
}



bool TreeStore::row_drop_possible_vfunc( const Gtk::TreeModel::Path & dest, const Gtk::SelectionData & selection_data ) const
{
	// Nodes cannot be dropped beside the root node.
	return dest.get_depth() > 1;
}



void TreeStore::setRoot( vgd::Shp< vgd::node::Group > root )
{
	// Updates the reference to the root node and refreshes the model.
	m_root = root;
	refresh();
}



void TreeStore::updateChildRowsActiveness( const Gtk::TreeRow & parentRow )
{
	vgd::Shp< vgd::node::Group >	parentNode	= vgd::dynamic_pointer_cast< vgd::node::Group >( parentRow.get_value(m_columns.m_nodeColumn) );
	vgd::node::NodeList				enabledChildren;
	
	parentNode->getEnabledChildren( enabledChildren );
	
	for( Gtk::TreeIter childRow = parentRow.children().begin(); childRow != parentRow.children().end(); ++childRow )
	{
		vgd::Shp< vgd::node::Node >	childNode	= childRow->get_value( m_columns.m_nodeColumn );
		bool						active		= std::find( enabledChildren.begin(), enabledChildren.end(), childNode ) != enabledChildren.end();
		
		childRow->set_value( m_columns.m_activeColumn, active );
	}
}



} // namespace graph

} // namespace vgGTK
