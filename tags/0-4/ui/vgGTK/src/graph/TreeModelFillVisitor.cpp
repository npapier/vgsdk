// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/graph/TreeModelFillVisitor.hpp"



namespace vgGTK
{

namespace graph
{



TreeModelFillVisitor::TreeModelFillVisitor( Glib::RefPtr< Gtk::TreeStore > treeStore, const TreeModelColumnRecord & columnRecord )
:	Traverse( false, false ),
	m_treeStore( treeStore ),
	m_columnRecord( columnRecord ),
	m_active( true )
{}



} // namespace graph

} // namespace vgGTK
