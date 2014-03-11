// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_NODE_INSERTNODE_HPP_
#define _VGQT_NODE_INSERTNODE_HPP_

#include <vgd/Shp.hpp>
#include <vgd/Wkp.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>

#include <QMenu>

#include "vgQt/vgQt.hpp"


namespace vgQt
{

namespace node
{


/**
 * @brief Sub menu of ActionsMenu to insert node in graph.
 */
class VGQT_API InsertNode : public QMenu
{
Q_OBJECT

public :
    InsertNode(QWidget* parent);

    ~InsertNode();

    /**
     * @brief Set the current selected node and its parent.
     *
     * @param currentNode Current selected node
     *
     * @param currentParentNode Parent node of the selected node
     */
    void setCurrentNode( vgd::Shp< vgd::node::Node > currentNode, vgd::Shp< vgd::node::Group > currentParentNode );

    /**
    * @brief Set the created node
    *
    * @param node the previously created node
    */
    void setCreatedNode( vgd::Shp< vgd::node::Node > node );

    /**
    * @brief Add a name to class name vector
    *
    * @param name new name to add
    */
    void addClassName( std::string name );

private Q_SLOTS:
    void onInsertNode( std::string name );

private:

    vgd::Shp< vgd::node::Node >			m_createdNode;			///< node to add.
    vgd::Wkp< vgd::node::Node >			m_currentNode;			///< current selected node.
    vgd::Wkp< vgd::node::Group >		m_currentParentNode;	///< current parent of selected node.
    std::vector< std::string >			m_classNames;			///< typeid name list of all creatable nodes.

};


} // namespace node

} // namespace vgQt

#endif // _VGQT_NODE_INSERTNODE_HPP_
