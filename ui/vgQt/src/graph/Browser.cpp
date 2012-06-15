// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgd/Wkp.hpp"

#include <boost/bind.hpp>
#include <boost/signal.hpp>

#include "vgQt/graph/Browser.hpp"
#include "vgQt/BasicManipulator.hpp"

#include "vgQt/graph/FieldManagerEditor.hpp"
#include "vgQt/graph/TreeView.hpp"

#include <QTableWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <QPushButton>

namespace vgQt
{

namespace graph
{




namespace
{
    /**
     * @brief	Implements a backup of the selection of a vgQt::TreeView.
     */
    struct SelectionBackup
    {
        /**
         * @brief	Constructor
         *
         * Saves the selection of the given tree view.
         *
         * @param	treeView	a tree view
         */
        SelectionBackup( TreeView* treeView )
        {
            for (int i = 0; i < treeView->topLevelItemCount(); ++i)
            {
                TreeModelColumnRecord *item = (TreeModelColumnRecord*) treeView->topLevelItem(i);
                processItem(item);
            }
        }
        void processItem(TreeModelColumnRecord *item)
        {
            if(item->isSelected())
            {
                storePath(item);
            }

            for (int i = 0; i < item->childCount(); i++)
            {
                TreeModelColumnRecord *child = (TreeModelColumnRecord*) item->child(i);
                processItem(child);
            }
        }

        /**
         * @brief	Restores the saved selection to the given tree view
         */
        void restore( TreeView* treeView )
        {
            for (int i = 0; i < treeView->topLevelItemCount(); ++i)
            {
                TreeModelColumnRecord *item = (TreeModelColumnRecord*) treeView->topLevelItem(i);
                processItemRestore(treeView, item);
            }
        }

        void processItemRestore( TreeView* treeView, TreeModelColumnRecord * item)
        {
            if(m_selectedItem.contains(item->getPath() + item->getIndexOfChild() ))
            {
                Q_FOREACH(QTreeWidgetItem* item, treeView->selectedItems())
                {
                    item->setSelected(false);
                }
                item->setSelected(true);
            }
            else if( treeView->selectedItems().size() == 0 &&
                     (m_selectedItem.contains(item->getPath() + (item->getIndexOfChild() + 1)) ||
                      m_selectedItem.contains(item->getPath() + (item->getIndexOfChild() - 1))))
            {
                item->setSelected(true);
            }

            for (int i = 0; i < item->childCount(); i++)
            {
                processItemRestore(treeView, (TreeModelColumnRecord*)item->child(i));
            }
        }

    private:

        QList< QString > m_selectedItem; ///< Holds the back up of selected paths.

        /**
         * @brief	Stores the given path.
         */
        void storePath( TreeModelColumnRecord* item )
        {
            m_selectedItem.append(item->getPath() + item->getIndexOfChild());
        }
    };


    /**
     * @brief	Implements a backup of the expanded rows of a vgQt::TreeView.
     */
    struct ExpandedRowsBackup
    {
        /**
         * @brief	Constructor
         *
         * Saves the expanded rows of the given tree view.
         *
         * @param	treeView	a tree view
         */
        ExpandedRowsBackup( TreeView* treeView )
        {
            for (int i = 0; i < treeView->topLevelItemCount(); ++i)
            {
                TreeModelColumnRecord *item = (TreeModelColumnRecord*) treeView->topLevelItem(i);
                processItem(item);
            }
        }

        void processItem(TreeModelColumnRecord *item)
        {
            if(item->isExpanded())
            {
                storePath(item);
            }

            for (int i = 0; i < item->childCount(); i++)
            {
                TreeModelColumnRecord *child = (TreeModelColumnRecord*) item->child(i);
                processItem(child);
            }
        }

        /**
         * @brief	Restores the saved selection to the given tree view
         */
        void restore( TreeView* treeView )
        {
            treeView->collapseAll();
            for (int i = 0; i < treeView->topLevelItemCount(); ++i)
            {
                TreeModelColumnRecord *item = (TreeModelColumnRecord*) treeView->topLevelItem(i);
                processItemRestore(treeView, item);
            }
        }
        void processItemRestore( TreeView* treeView, TreeModelColumnRecord * item)
        {
            if(m_expandedItem.contains(item->getPath() + item->getIndexOfChild() ))
            {
                item->setExpanded(true);
            }

            for (int i = 0; i < item->childCount(); i++)
            {
                processItemRestore(treeView, (TreeModelColumnRecord*) item->child(i));
            }
        }
    private:

        QList< QString > m_expandedItem; ///< Holds the back up of expanded paths.

        /**
         * @brief	Stores the given path.
         */
        void storePath( TreeModelColumnRecord* item )
        {
            m_expandedItem.append(item->getPath() + item->getIndexOfChild() );
        }
    };
}





Browser::Browser(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout();

    m_treeView = new TreeView( this );
    m_editor = new FieldManagerEditor( this );
    m_path = new QLabel( tr("/"), this );

    QHBoxLayout *layoutButtons = new QHBoxLayout();
    QPushButton *expandButton = new QPushButton(QIcon(":/images/expand.xpm"), "" );
    expandButton->setFlat(true);
    expandButton->setFocusPolicy(Qt::NoFocus);
    QPushButton *synchronizeButton = new QPushButton(QIcon(":/images/view-refresh.png"), "" );
    synchronizeButton->setFlat(true);
    synchronizeButton->setFocusPolicy(Qt::NoFocus);
    layoutButtons->addWidget( synchronizeButton );
    layoutButtons->addWidget( expandButton );
    layoutButtons->addStretch();

    QSplitter *splitter = new QSplitter( this );
    splitter->setOrientation( Qt::Vertical );
    splitter->addWidget( ( TreeView*) m_treeView );
    splitter->addWidget( ( FieldManagerEditor* ) m_editor );

    layout->addLayout( layoutButtons );
    layout->addWidget( m_path );
    layout->addWidget( splitter );

    // If a node is selected in the treeview, we update the editor
    connect( m_treeView, SIGNAL(itemSelectionChanged()), this, SLOT(onSelectionChanged()) );

    connect( m_editor, SIGNAL(onChangeSignal()), this, SLOT(refresh()) );

    // The buttons
    connect(synchronizeButton, SIGNAL(clicked()), this, SLOT(onFullRefresh()));
    connect(expandButton, SIGNAL(clicked()), this, SLOT(onExpandAll()));

    setLayout(layout);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested ( const QPoint )), this, SLOT(onMenuRequested(QPoint)));

    vgAlg::actions::SelectedNode::getSelectedNodeObject()->signal_action_changed.connect( boost::bind( &Browser::onActionChanged, this, _1 ) );
}

void Browser::onActionChanged( vgAlg::actions::ActionOnNode action )
{
    switch( action )
    {
        case vgAlg::actions::EXPAND:
            onExpandSubTree();
            break;
        case vgAlg::actions::REFRESH:
            refreshTree();
            break;
        case vgAlg::actions::SELECT:
            selectNode( vgAlg::actions::SelectedNode::getSelectedNodeObject()->getSelectedNode() );
            break;
        case vgAlg::actions::MOVE_NEXT:
            break;
        case vgAlg::actions::MOVE_PREVIOUS:
            break;
        default:
            qDebug("Action not defined");
            break;
    }
}

bool Browser::searchNode( TreeModelColumnRecord* currentItem, vgd::Shp< vgd::node::Node > node, TreeModelColumnRecord *&foundItem )
{
    if( currentItem->m_node == node)
    {
        foundItem = currentItem;
        return true;
    }

    for (int i = 0; i < currentItem->childCount(); ++i)
    {
        TreeModelColumnRecord *nextItem = (TreeModelColumnRecord*) currentItem->child(i);
        if(searchNode(nextItem, node, foundItem))
        {
            return true;
        }
    }

    return false;
}

void Browser::selectNode( vgd::Shp< vgd::node::Node > node )
{
    if(m_treeView->selectedItems().size() > 0)
    {
        Q_FOREACH(QTreeWidgetItem* item, m_treeView->selectedItems())
        {
            item->setSelected(false);
        }
    }

    TreeModelColumnRecord* foundItem = 0;
    if(searchNode( (TreeModelColumnRecord*) m_treeView->topLevelItem(0), node, foundItem))
    {
        if (foundItem)
        {
            m_treeView->scrollToItem(foundItem, QAbstractItemView::PositionAtCenter);
            foundItem->setSelected(true);
        }
    }
}

void Browser::refreshTree()
{
    onFullRefresh();
}

void Browser::onExpandSubTree()
{
    if(m_treeView->selectedItems().size() > 0)
    {
        expandSubTree(m_treeView->selectedItems().last());
    }
}

void Browser::expandSubTree(QTreeWidgetItem* item)
{
    item->setExpanded(true);
    for (int i = 0; i < item->childCount(); i++)
    {
        expandSubTree(item->child(i));
    }
}

void Browser::onMenuRequested(QPoint point)
{
    m_actionsMenu->showPopup( mapToGlobal(point), vgQt::node::TREE );
}

void Browser::onExpandAll()
{
    m_treeView->expandAll();
}

void Browser::onSelectionChanged()
{
    if(m_treeView->selectedItems().size() > 0)
    {
        m_selected = (TreeModelColumnRecord *) m_treeView->selectedItems().last();

        m_treeView->scrollToItem(m_selected, QAbstractItemView::EnsureVisible);

        m_editor->setFieldManager(m_selected->m_node);
        m_selected->parent() ? m_editor->setPath( ((TreeModelColumnRecord *) m_selected->parent())->getPath()) : m_editor->setPath(QString("/"));

        m_path->setText( m_selected->getPath() );
        m_path->setMinimumWidth(0);

        vgd::Shp< vgd::node::Node >	node = 	m_selected->m_node;
        vgd::Shp< vgd::node::Group >	parentGroup;
        if(m_selected->parent())
        {
            vgd::Shp< vgd::node::Node >		parentNode = ((TreeModelColumnRecord *) m_selected->parent())->m_node;
            parentGroup	= vgd::dynamic_pointer_cast< vgd::node::Group >( parentNode );
        }

        vgAlg::actions::SelectedNode::getSelectedNodeObject()->setSelectedNode( node, parentGroup );
    }
}

void Browser::refresh()
{
    if(m_selected)
    {
        m_editor->setFieldManager(m_selected->m_node);
    }
    else
    {
        m_editor->setFieldManager( vgd::Shp< vgd::field::FieldManager >() );
    }
}

void Browser::setCanvas( vgUI::Canvas * canvas )
{
    m_canvas = canvas;
    m_editor->setCanvas( canvas );
    m_treeView->setRoot( m_canvas->getRoot() );
    m_treeView->refresh();
    m_editor->setFieldManager( vgd::Shp< vgd::field::FieldManager >() );
    m_actionsMenu = new vgQt::node::ActionsMenu(this, vgQt::node::TREE);
    m_actionsMenu->setCanvas( m_canvas );
}

void Browser::setRoot( vgd::Shp< vgd::node::Group > root )
{
    m_root = root;
    m_editor->setFieldManager( m_canvas->getRoot() );
}

void Browser::onFullRefresh()
{
    SelectionBackup		selectionBackup( m_treeView );
    ExpandedRowsBackup	expandedRowsBackup( m_treeView );
    // Do the refresh.
    m_editor->setFieldManager( vgd::Shp< vgd::field::FieldManager >() );
    m_treeView->refresh();
    // Restores the selection and the expanded rows.
    expandedRowsBackup.restore( m_treeView );
    selectionBackup.restore( m_treeView );
    if( m_treeView->selectedItems().size() > 0 )
    {
        m_treeView->scrollToItem(m_treeView->selectedItems().last(), QAbstractItemView::PositionAtCenter);
    }
}

} // namespace graph

} // namespace vgQt
