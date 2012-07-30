// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/graph/TreeView.hpp"
#include "vgQt/graph/TreeModelFillVisitor.hpp"
#include <QWidget>

namespace vgQt
{

namespace graph
{

TreeView::TreeView( QWidget *parent ) : QTreeWidget( parent )
{
    setColumnCount( 4 );
    QStringList titles;
    titles << "Name" << "Type" << "Active" << "Shared";
    setHeaderLabels( titles );

	setColumnWidth(0, 300); 
}

void TreeView::refresh()
{
    // Clears the the model's content.
    clear();

    // Fills the model according to the given new root
    if( m_root )
    {
        TreeModelFillVisitor	fillVisitor( this );

        m_root->traverse( fillVisitor );
    }
}

void TreeView::setRoot( vgd::Shp< vgd::node::Group > root )
{
    // Updates the reference to the root node and refreshes the model.
    m_root = root;
    refresh();
}

} // namespace graph

} // namespace vgQt
