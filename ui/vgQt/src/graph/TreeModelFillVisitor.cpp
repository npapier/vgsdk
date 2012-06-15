// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/graph/TreeModelFillVisitor.hpp"

namespace vgQt
{

namespace graph
{

TreeModelFillVisitor::TreeModelFillVisitor( TreeView * treeStore )
:	vgd::visitor::Traverse< boost::null_visitor >( false, false ),
    m_treeView( treeStore ),
    m_active( true )
{}

} // namespace graph

} // namespace vgQt
