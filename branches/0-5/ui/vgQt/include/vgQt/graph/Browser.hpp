// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_GRAPH_BROWSER_HPP_
#define _VGQT_GRAPH_BROWSER_HPP_

#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>

#include <vgAlg/actions/SelectedNode.hpp>

#include "vgQt/graph/TreeModelColumnRecord.hpp"
#include "vgQt/graph/TreeView.hpp"
#include "vgQt/graph/FieldManagerEditor.hpp"
#include "vgQt/node/ActionsMenu.hpp"

#include <QLabel>
#include <QTreeWidget>

#include "vgQt/vgQt.hpp"

namespace vgUI { struct Canvas; }
namespace vgQt { namespace engine { class ShadersEditor; } }


namespace vgQt
{

namespace graph
{


class VGQT_API Browser : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief	Constructor
     */
    Browser( QWidget *parent = 0 );

    /**
     * @brief	Assignes the pointer to the canvas to refesh on graph changes.
     *
     * @param	canvas	a pointer to a canvas, null if none
     */
    void setCanvas( vgUI::Canvas * canvas );

    /**
     * @brief	Updates the root node of the graph to browse
     *
     * You can pass an empty reference to clear the browser's content.
     *
     * @param	root	a reference to the new root node, empty if none
     */
    void setRoot( vgd::Shp< vgd::node::Group > root );

    /**
     * @brief	Refresh the whole tree.
     */
    void refreshTree();

    /**
     * @brief	Get pointer to the Shader Editor.
     */
	vgQt::engine::ShadersEditor* getShadersEditor() { return m_shadersEditor; }

private:

    /**
     * @name	Widgets
     */
    //@{
    QLabel * m_path;                ///< Shows the current selection path.
    TreeModelColumnRecord* m_selected;
    vgQt::node::ActionsMenu*    m_actionsMenu;
    //@}

    vgUI::Canvas	* m_canvas;     ///< Points to the canvas to refresh.

    /**
     * @name	Widgets
     */
    //@{
    TreeView * m_treeView;         ///< The treeview widget that shows the vgSDK graph.
    FieldManagerEditor * m_editor;  ///< Allows to edit the fields of the selected node.
	vgQt::engine::ShadersEditor*	m_shadersEditor;
    //@}

    /**
     * @name	Data
     */
    //@{
    vgd::Shp< vgd::node::Group >	m_root;			///< References the root node.
    //@}

    void onExpandSubTree();
    void expandSubTree(QTreeWidgetItem* item);
    void selectNode( vgd::Shp< vgd::node::Node > node );
    bool searchNode( TreeModelColumnRecord* currentItem, vgd::Shp< vgd::node::Node > node, TreeModelColumnRecord *&foundItem );

public Q_SLOTS:
    /**
     * @name	Signal Handlers
     */
    //@{
    void onActionChanged( vgAlg::actions::ActionOnNode action );
    void onMenuRequested(QPoint);
    void onSelectionChanged();
    void onExpandAll();                             ///< Handles the action that will expand all tree view content.
    void onFullRefresh();                           ///< Handles the action that will perfrom a refresh of the whole tree.
    void refresh();                                 ///< Handles the action that will perform a refresh of the fieldManagerEditor
    //@}
};

} // namespace graph

} // namespace vgQt

#endif // _VGQT_GRAPH_BROWSER_HPP_
