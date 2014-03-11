// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/graph/TreeModelColumnRecord.hpp"

namespace vgQt
{

namespace graph
{


TreeModelColumnRecord::TreeModelColumnRecord( QTreeWidget *parent ) : QTreeWidgetItem( parent )
{
}

TreeModelColumnRecord::TreeModelColumnRecord( QTreeWidgetItem *parent ) : QTreeWidgetItem( parent )
{
}

QString TreeModelColumnRecord::getPath()
{
    QString path = "/" + QString(m_node->getName().c_str());
    TreeModelColumnRecord *i = this;
    while (i->parent() > 0)
    {
        i = (TreeModelColumnRecord *) i->parent();
        path = "/" + QString(i->m_node->getName().c_str()) + path;
    }
    return path;
}

int TreeModelColumnRecord::getIndexOfChild()
{
    if ( parent() > 0 )
    {
        return parent()->indexOfChild(this);
    }
    else
    {
        return 0;
    }
}

} // namespace graph

} // namespace vgQt
