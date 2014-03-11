// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_GRAPH_TREESTORE_HPP_
#define _VGQT_GRAPH_TREESTORE_HPP_

#include <vgd/node/Group.hpp>

#include <QTreeWidget>

namespace vgQt
{

namespace graph
{

/**
 * @brief	Implements a specialized Qt:TreeView
 */
class TreeView : public QTreeWidget
{
    Q_OBJECT
public:
    /**
     * @brief	Constructor
     */
    TreeView( QWidget *parent );

    /**
     * @brief	Refreshes the tree to reflect graph changes.
     */
    void refresh();

    /**
     * @brief	Assigns a new root node.
     *
     * The tree content will be cleared. If the passed root reference is empty,
     * the model will remain empty.
     *
     * @param	root	a reference to the new root node, can be empty
     */
    void setRoot( vgd::Shp< vgd::node::Group > root );

protected:

    vgd::Shp< vgd::node::Group >    m_root; ///< References the root node.
};

} // namespace graph

} // namespace vgQt

#endif // _VGQT_GRAPH_TREESTORE_HPP_
