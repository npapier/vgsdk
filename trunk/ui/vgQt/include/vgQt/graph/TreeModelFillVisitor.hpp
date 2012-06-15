// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_GRAPH_TREEMODELFILLVISITOR_HPP_
#define _VGQT_GRAPH_TREEMODELFILLVISITOR_HPP_

#include <vector>

#include <vgd/node/Node.hpp>
#include <vgd/visitor/Traverse.hpp>

#include "vgQt/graph/TreeView.hpp"
#include "vgQt/graph/TreeModelColumnRecord.hpp"

#include <QCheckBox>

namespace vgQt
{

namespace graph
{

/**
 * @brief	Implements vgSDK graph visitor that will walk through a graph and fill
 * 			a given Qt tree model.
 */
struct TreeModelFillVisitor : public vgd::visitor::Traverse< boost::null_visitor >
{
    /**
     * @brief	Constructor
     *
     * @param	treeStore		a reference to the tree store to fill
     */
    TreeModelFillVisitor( TreeView *treeStore );

    /**
     * @name	Overrides
     */
    //@{
    template<class Vertex, class Graph>
    void discover_vertex(Vertex u, const Graph &g)
    {
        Q_UNUSED(g);
        // Creates a new tree model row for the current node.
        TreeModelColumnRecord *current = m_ancestors.empty() ? new TreeModelColumnRecord( m_treeView ) : new TreeModelColumnRecord( ( QTreeWidgetItem* ) m_ancestors.last() );


        // Retrieves the vgd::node::Node from the current vertex.
        vgd::Shp< vgd::node::Node >	node = getNode( u );


        // Prepares the type string of the node.
        // We remove the "struct " prefix.
        static const QString prefix = "struct ";
        QString type = typeid(*node.get()).name();
        if( type.contains( prefix ) )
        {
            type.remove( 0,prefix.length() );
        }

        // Looks if the node is shared (has several parent nodes).
        bool					shared = false;
        vgd::node::NodeList		parents;
        node->getParents( parents );
        shared = parents.size() > 1;


        current->m_node = node; // Node


        current->setText(0, QString(node->getName().c_str())); // Name


        current->setText(1, type ); // Type


        QCheckBox *checkbox = new QCheckBox( m_treeView ); // Active
        checkbox->setChecked( m_active );
        checkbox->setEnabled( false );
        m_treeView->setItemWidget( current, 2, checkbox );


        QCheckBox *checkbox2 = new QCheckBox( m_treeView ); // Shared
        checkbox2->setChecked( shared );
        checkbox2->setEnabled( false );
        m_treeView->setItemWidget( current, 3, checkbox2 );


        m_ancestors.append( current );
}

    template<class Vertex, class Graph>
    void finish_vertex (Vertex u, const Graph &g)
    {
        Q_UNUSED(u);
        Q_UNUSED(g);
        if ( !m_ancestors.isEmpty() )
            m_ancestors.removeLast();
    }

    template<class Edge, class Graph>
    void examine_edge(Edge e, const Graph & g)
    {
        const vgd::graph::detail::EdgeName	edgeName = getEdgeName(e);

        m_active = edgeName.enable();

        vgd::visitor::Traverse< boost::null_visitor >::examine_edge( e, g );
    }
    //@}


private:

    TreeView						* m_treeView;		///< Refrences the tree store to fill.
    QList<TreeModelColumnRecord *>  m_ancestors;		///< Contains all ancestors' paths.
    bool							m_active;			///< Tells if the node is active or not.

};

} // namespace graph

} // namespace vgQt

#endif // _VGQT_GRAPH_TREEMODELFILLVISITOR_HPP_
