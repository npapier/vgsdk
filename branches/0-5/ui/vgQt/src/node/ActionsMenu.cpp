// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>
#include <vgAlg/actions/input/IParentInput.hpp>
#include <vgAlg/actions/input/IRootInput.hpp>
#include <vgAlg/actions/SelectedNode.hpp>
#include <vgAlg/node/TriSet.hpp>
#include <vgAlg/node/VertexShape.hpp>


#include <vgd/node/TriSet.hpp>
#include <vge/technique/ApplyGeometricalTransformations.hpp>
#include <vgeGL/engine/Engine.hpp>
#include <vgUI/actions/State.hpp>

#include <vgUI/actions/ActionsRegistry.hpp>

#include <QMouseEvent>

#include "vgQt/node/ActionsMenu.hpp"
#include "vgQt/node/Action.hpp"
#include "vgQt/node/InsertNode.hpp"

#include "vgQt/actions/ui/ExportNodeUI.hpp"
#include "vgQt/actions/alg/ExportNode.hpp"

#include "vgQt/actions/alg/EncryptFileAction.hpp"
// #include "vgQt/actions/ui/EncryptFileUI.hpp"

#include "vgQt/actions/ui/RemoveNodeUI.hpp"
#include "vgQt/actions/alg/RemoveNode.hpp"

namespace vgQt
{

namespace node
{

ActionsMenu::ActionsMenu( QWidget* parent, POPUP_LOCATION location )
    : QMenu(parent),
      m_location( location )
{
    m_actionsRegistry = vgUI::actions::ActionsRegistry::getActionsRegistry();
    vgd::Shp< vgUI::actions::ActionsRegistry >	actionsRegistry = m_actionsRegistry.lock();

    manageMenu( actionsRegistry->getActionMap() );

    m_insertMenuItem = new InsertNode(this);
    addMenu(m_insertMenuItem);
}

void ActionsMenu::initActions()
{
    // vgUI::actions::RegisterAction< actions::ui::EncryptFileUI > action1(16);
    vgUI::actions::RegisterAction< actions::ui::ExportNodeUI > action2(41);
    vgUI::actions::RegisterAction< actions::ui::RemoveNodeUI > action3(15);
}

void ActionsMenu::onCanvasMenuRequested(QPoint point)
{
	assert( m_canvas );

	// Actually, the canvas is based on a QWidget. So we can retrieve the widget for later use.
	QWidget	* widget = dynamic_cast< QWidget* >( m_canvas );
	
    // Retrieves the eventual node currently under the mouse pointer.
    vgd::node::Node *castNode = m_canvas->castRay( point.x(), widget->height() - point.y() );

    if ( castNode )
    {
        vgd::Shp< vgd::node::Node > currentNode = castNode->shpFromThis();

        vgAlg::actions::SelectedNode::getSelectedNodeObject()->setSelectedNode( currentNode, currentNode->getParent() );
        showPopup( widget->mapToGlobal(point), NODE );
    }
    else
    {
		vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
		node.reset();
	
        if( node )
        {
            vgAlg::actions::SelectedNode::getSelectedNodeObject()->setSelectedNode(  node, node->getParent() );
            showPopup( widget->mapToGlobal(point), CANVAS );
        }
        else
        {
            // vgd::Shp< vgd::node::Group > parent;
            vgAlg::actions::SelectedNode::getSelectedNodeObject()->setSelectedNode( node );
            showPopup( widget->mapToGlobal(point), CANVAS );
        }
    }
}

void ActionsMenu::setCanvas( vgUI::Canvas * canvas )
{
    m_canvas = canvas;
}

void ActionsMenu::showPopup( QPoint point, POPUP_LOCATION location )
{
    m_location = location;
    if( getTotalNumberOfShape() < 1 && m_location == CANVAS )
    {
        return; //no menu needed.
    }

    m_currentNode = vgAlg::actions::SelectedNode::getSelectedNodeObject()->getSelectedNode();
    m_currentParentNode = vgAlg::actions::SelectedNode::getSelectedNodeObject()->getParentSelectedNode();

    manageHiddenNodeMenu();
    applyState();
    manageMenuVisibility(this);

    if( m_location == TREE )
    {
        m_insertMenuItem->menuAction()->setVisible(true);
    }
    else
    {
        m_insertMenuItem->menuAction()->setVisible(false);
    }

    popup(point);
}

void ActionsMenu::refresh()
{
    m_canvas->refresh();
}

void ActionsMenu::manageMenu( std::map< int, vgd::Shp< vgUI::actions::IActionUI > > actionsMap )
{
    std::map< int, vgd::Shp< vgUI::actions::IActionUI > >::iterator it = actionsMap.begin();
    for( it; it != actionsMap.end(); it++ )
    {
        std::vector< std::string > contrib = it->second->getMenuContribList();
        QMenu* currentMenu = this;
        for( uint i = 0; i < contrib.size(); i++ )
        {
            if( i == contrib.size() -1 )
            {
                if( m_actionMap.count( it->second ) == 0 )
                {
                    Action* action = new Action(QString(it->second->getName().c_str()), currentMenu, it->second->getAction());
                    connect(action, SIGNAL(triggered()), this, SLOT(refresh()));
                    currentMenu->addAction(action);
                    m_actionMap[ it->second ] = action;
                }
            }
            else
            {
                QMenu* menuItem = 0;

                Q_FOREACH(QMenu* menu, findChildren<QMenu *>())
                {
                    if(menu->title() == QString::fromStdString(contrib[i]))
                    {
                        menuItem = menu;
                    }
                }

                if(!menuItem)
                {
                    QMenu* menu = new QMenu(contrib[i].c_str(), this);
                    currentMenu->addMenu(menu);
                    currentMenu = menu;
                }
                else
                {
                    currentMenu = menuItem;
                }
            }
        }
    }
}

vgUI::actions::State ActionsMenu::createState()
{
    vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
    vgd::Shp< vgd::node::Group > parentNode = m_currentParentNode.lock();

    vgUI::actions::State state;

    state.setNumberOfNode( getTotalNumberOfShape() );

    state.setNumberOfDisplayedNode( getDisplayedNodeNumber() );

    bool isRoot = false;
    if( node == m_canvas->getRoot() )
    {
        isRoot = true;
    }
    state.isRoot( isRoot );

    state.setSelectedNode( node );

    bool hasClipboardedNode = false;
    vgd::Shp< vgd::node::Node > clipboardedNode = vgAlg::actions::SelectedNode::getSelectedNodeObject()->getClipboardedNode();
    if( clipboardedNode )
    {
        hasClipboardedNode = true;
    }
    state.hasAClipboardedNode( hasClipboardedNode );

    vgUI::actions::LOCATION location;
    if( m_location == TREE )
    {
        location = vgUI::actions::TREE;
    }
    else if( m_location == CANVAS || m_location == NODE )
    {
        location = vgUI::actions::CANVAS;
    }

    state.setLocation( location );

    state.setParent( parentNode );

    bool isShape = false;
    if( node )
    {
        if( node->isAKindOf< vgd::node::Shape >() )
        {
            isShape = true;
        }
    }
    state.isShape( isShape );

    bool isGroup = false;
    if( node )
    {
        if( node->isAKindOf< vgd::node::Group >() )
        {
            isGroup = true;
        }
    }
    state.isGroup( isGroup );

    state.isHidden( vgAlg::actions::SelectedNode::getSelectedNodeObject()->isAlreadyHidden( node ) );

    state.setNumberOfHiddenNode( vgAlg::actions::SelectedNode::getSelectedNodeObject()->getHiddenNodeList()->size() );

    return state;
}

void ActionsMenu::applyState()
{
    vgUI::actions::State state = createState();

    std::map< vgd::Shp < vgUI::actions::IActionUI >, QAction* >::iterator it = m_actionMap.begin();

    for( it; it != m_actionMap.end(); it++ )
    {
        if( it->first->isValide( state ) )
        {
            it->second->setText( QString::fromStdString(it->first->getName()) );
            it->second->setVisible(true);
            setParams( it->first->getAction() );
        }
        else
        {
            it->second->setVisible(false);
        }
    }
}

void ActionsMenu::setParams( vgAlg::actions::IAction* action )
{
    vgAlg::actions::input::INodeInput*		nodeInput;
    vgAlg::actions::input::IParentInput*	parentInput;
    vgAlg::actions::input::IRootInput*		rootInput;

    vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
    vgd::Shp< vgd::node::Group > parentNode = m_currentParentNode.lock();

    if( nodeInput = dynamic_cast< vgAlg::actions::input::INodeInput* >( action ) )
    {
        nodeInput->setNode( node );
    }
    if( parentInput = dynamic_cast< vgAlg::actions::input::IParentInput* >( action ) )
    {
        parentInput->setParent( parentNode );
    }
    if( rootInput = dynamic_cast< vgAlg::actions::input::IRootInput* >( action ) )
    {
        rootInput->setRoot( m_canvas->getRoot() );
    }
}

int ActionsMenu::getTotalNumberOfShape()
{
    vgd::visitor::predicate::ByKindOfType<vgd::node::VertexShape> predicate;
    vgd::Shp< vgd::node::NodeList > result;
    result = vgd::visitor::find( m_canvas->getRoot(), predicate );

    return result->size();
}

int ActionsMenu::getDisplayedNodeNumber()
{
    int counter = 0;

    vgd::visitor::predicate::ByKindOfType<vgd::node::VertexShape> predicate;
    vgd::Shp< vgd::node::NodeList > result;
    result = vgd::visitor::find( m_canvas->getRoot(), predicate );

    std::list< vgd::Shp < vgd::node::Node > >::iterator iter = result->begin();
    for( iter; iter !=  result->end(); iter++ )
    {
        if( !vgAlg::actions::SelectedNode::getSelectedNodeObject()->isAlreadyHidden( (*iter) ) )
        {
            counter++;
        }
    }

    return counter;
}

void ActionsMenu::manageHiddenNodeMenu()
{
    vgd::Shp< vgUI::actions::ActionsRegistry >	actionsRegistry = m_actionsRegistry.lock();
    manageMenu( actionsRegistry->getHiddenNodeActionMap() );
}

void ActionsMenu::manageMenuVisibility( QMenu* menu )
{
    if(menu->findChildren<QMenu*>().size() == 0)
    {
            bool isVisible = false;
            Q_FOREACH(QAction* action, menu->findChildren<QAction*>())
            {
                if(action->isVisible() && action != menu->menuAction())
                {
                    isVisible = true;
                }
            }
            !isVisible ? menu->menuAction()->setVisible(false) : menu->menuAction()->setVisible(true);
    }
    else
    {
        Q_FOREACH(QMenu* menuItem, menu->findChildren<QMenu*>())
        {
            manageMenuVisibility(menuItem);
        }
    }
}

} // namespace node

} // namespace vgQt
