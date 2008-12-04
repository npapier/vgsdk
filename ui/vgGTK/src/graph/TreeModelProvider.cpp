// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/graph/TreeModelProvider.hpp"

#include <cassert>
#include "vgGTK/graph/TreeModelFillVisitor.hpp"



namespace vgGTK
{

namespace graph
{



TreeModelProvider::TreeModelProvider()
{
	// Creates the tree model, that is Actually a gtm::TreeStore
	m_treeStore = Gtk::TreeStore::create( m_columnRecord );
}



const TreeModelColumnRecord & TreeModelProvider::getColumnRecord() const
{
	return m_columnRecord;
}



const Glib::RefPtr< Gtk::TreeStore > TreeModelProvider::getModel() const
{
	return m_treeStore;
}



void TreeModelProvider::refresh()
{
	assert( m_treeStore );


	// Clears the the model's content.
	m_treeStore->clear();


	// Fills the model according to the given new root
	if( m_root )
	{
		TreeModelFillVisitor	fillVisitor( m_treeStore, m_columnRecord );

		m_root->traverse( fillVisitor );
	}
}



void TreeModelProvider::setRoot( vgd::Shp< vgd::node::Group > root )
{
	assert( m_treeStore );

	// Updates the reference to the root node and refreshes the model.
	m_root = root;
	refresh();
}



} // namespace graph

} // namespace vgGTK
