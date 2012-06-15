// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_GRAPH_TREEMODELCOLUMNRECORD_HPP_
#define _VGQT_GRAPH_TREEMODELCOLUMNRECORD_HPP_

#include <vgd/Shp.hpp>
#include <vgd/node/Node.hpp>

#include <QTreeWidgetItem>

#include "vgQt/vgQt.hpp"

namespace vgQt
{

namespace graph
{

/**
 *
 * @brief	Provides a custom TreeWidgetItem that allows to store the node.
 *
 */
struct VGQT_API TreeModelColumnRecord : public QTreeWidgetItem
{
    /**
     * @brief	Constructors
     */
    TreeModelColumnRecord(QTreeWidget *parent = 0); ///< This constructor is for the root element
    TreeModelColumnRecord(QTreeWidgetItem *parent); ///< This constructor is for the child elements

    vgd::Shp< vgd::node::Node >	m_node; ///< Defines a pointer to a vgd::node::Node.

    /**
     * @brief	Returns the path of the item
     */
    QString getPath();

    /**
     * @brief   Returns the index of the item
     */
    int getIndexOfChild();
};

} // namespace graph

} // namespace vgQt

#endif // _VGQT_GRAPH_TREEMODELCOLUMNRECORD_HPP_
