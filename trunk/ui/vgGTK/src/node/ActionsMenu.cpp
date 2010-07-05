// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/node/ActionsMenu.hpp"

#include <gtkmm/filechooserdialog.h>
#include <gtkmm/menu.h>
#include <gtkmm/menushell.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/stock.h>
#include <gtkmm/window.h>

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>
#include <vgAlg/actions/input/IParentInput.hpp>
#include <vgAlg/actions/input/IRootInput.hpp>
#include <vgAlg/actions/SelectedNode.hpp>
#include <vgAlg/node/TriSet.hpp>
#include <vgAlg/node/VertexShape.hpp>

#include <vgDebug/convenience.hpp>
#include <vgd/node/TriSet.hpp>
#include <vge/technique/ApplyGeometricalTransformations.hpp>
#include <vgeGL/engine/Engine.hpp>
#include <vgUI/actions/State.hpp>



namespace vgGTK
{

namespace node
{

ActionsMenu::ActionsMenu( POPUP_LOCATION location ) 
:	m_actions( Gtk::ActionGroup::create() ),
	m_uiManager( Gtk::UIManager::create() ),
	m_location( location )
{
	// Initializes the user interface manager.
	m_uiDefinition =
		"<ui>"
		"  <popup name='popup'>"
		"    <menu action='InsertNode'/>"
		"    <separator/>"
		"  </popup>"
		"</ui>";

	m_uiManager->insert_action_group( m_actions );
	m_uiManager->add_ui_from_string( m_uiDefinition );

	m_actions->add( Gtk::Action::create("InsertNode", "Insert Node") );


	Gtk::Widget		* insertWidget	= m_uiManager->get_widget("/popup/InsertNode");
	m_insertMenuItem				= dynamic_cast< Gtk::MenuItem * >( insertWidget );

	m_insertNode					= new InsertNode();

	m_insertMenuItem->set_submenu( *m_insertNode->getMenu() );
	m_insertMenuItem->property_visible() = false;



	Gtk::Widget* rootWidget	= m_uiManager->get_widget("/popup");
	m_rootMenu				= dynamic_cast< Gtk::Menu* >( rootWidget );

	if( m_rootMenu )
	{
		manageMenu( m_actionsRegistry.getActionList() );
	}
}



ActionsMenu::~ActionsMenu()
{
	delete m_insertMenuItem;
	delete m_insertNode;
	delete m_rootMenu;

	std::map< vgd::Shp < vgUI::actions::IActionUI >, Gtk::MenuItem* >::iterator it = m_actionMap.begin();
	for( it; it != m_actionMap.end(); it++ )
	{
		delete (*it).second;
	}
	m_actionMap.clear();
}



void ActionsMenu::setCanvas( vgUI::Canvas * canvas )
{
	m_canvas = canvas;
}



bool ActionsMenu::onBoutonPressEvent( GdkEventButton * event )
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
	node.reset();

	if( event->button == 3 )
	{
		// Retrieves some properties of the window.
		gint	x;
		gint	y;
		gint	width;
		gint	height;
		gint	depth;

		gdk_window_get_geometry( event->window, &x, &y, &width, &height, &depth );

		vgd::node::Node *castNode = m_canvas->castRay( event->x, height - event->y );

		if ( castNode )
		{
			vgd::Shp< vgd::node::Node > currentNode = castNode->shpFromThis();

			vgAlg::actions::SelectedNode::getSelectedNodeObject()->setSelectedNode( currentNode, currentNode->getParent() );
			showPopup(event, NODE);
		}
		else
		{
			if( node )
			{
				vgAlg::actions::SelectedNode::getSelectedNodeObject()->setSelectedNode(  node, node->getParent() );
				showPopup(event, CANVAS);
			}
			else
			{
				vgd::Shp< vgd::node::Group > parent;
				vgAlg::actions::SelectedNode::getSelectedNodeObject()->setSelectedNode( node );
				showPopup(event, CANVAS);
			}
		}
	}
	// else do nothing.

	return true;
}


void ActionsMenu::showPopup( GdkEventButton * event, POPUP_LOCATION location )
{
	//@todo don't show "ExpandSubTree" if node don't have any children.
	//if there is no shape in graph, don't display menu at all.
	if( getTotalNumberOfShape() < 1 && m_location == CANVAS )
	{
		return; //no menu needed.
	}

	m_currentNode = vgAlg::actions::SelectedNode::getSelectedNodeObject()->getSelectedNode();
	m_currentParentNode = vgAlg::actions::SelectedNode::getSelectedNodeObject()->getParentSelectedNode();
	m_location = location;

	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
	vgd::Shp< vgd::node::Node > parentNode = m_currentParentNode.lock();

	manageHiddenNodeMenu();
	applyState();
	ManageMenuVisibility( m_rootMenu );

	//InsertNode
	if( m_location == TREE )
	{
		m_insertMenuItem->show();
	}
	else
	{
		m_insertMenuItem->hide();
	}

	Gtk::Menu *	popupMenu = dynamic_cast< Gtk::Menu * >( m_uiManager->get_widget("/popup") );
	popupMenu->popup( event->button, event->time );
}



void ActionsMenu::manageMenu( std::list< vgd::Shp< vgUI::actions::IActionUI > > actionsList )
{
	std::list< vgd::Shp< vgUI::actions::IActionUI > >::iterator it = actionsList.begin();
	for( it; it != actionsList.end(); it++ )
	{
		std::vector< std::string > contrib = (*it)->getMenuContribList();
		Gtk::Menu* currentMenu = m_rootMenu;
		for( uint i = 0; i < contrib.size(); i++ )
		{
			Gtk::MenuItem* menuItem = 0;
			
			if( i == contrib.size() -1 )
			{
				//create menuitem and add to currentMenu;
				if( m_actionMap.count( *it ) == 0 )
				{
					menuItem = new Gtk::MenuItem( (*it)->getName() );
					menuItem->signal_activate().connect( sigc::mem_fun( (*it)->getAction(), &vgAlg::actions::IAction::execute ) );			
					currentMenu->append( *menuItem );
					currentMenu->show_all();

					m_actionMap[ *it ] = menuItem;
				}
			}
			else
			{
				//check if sub menu exist
				Gtk::Menu_Helpers::MenuList children = currentMenu->items();
				Gtk::Menu_Helpers::MenuList::iterator iter = children.begin();
				for( iter; iter != children.end(); iter++ )
				{
					std::string name = iter->get_name();
					if( contrib[i] == iter->get_name() )
					{
						menuItem = &*iter;
					}
				}
				
				//if it don't exist, create it and assign to "currentMenu"
				if( !menuItem )
				{
					menuItem = new Gtk::MenuItem( contrib[i] );	
					menuItem->set_name( contrib[i] );

					currentMenu->append( *menuItem );
					currentMenu->show_all();

					Gtk::Menu* newMenu = new Gtk::Menu();
					newMenu->set_name( contrib[i] );
					menuItem->set_submenu( *newMenu );
					currentMenu = newMenu;
				}
				//else assign it to currentMenu
				else
				{
					currentMenu = menuItem->get_submenu();
				}
			}
		}
	}
}



void ActionsMenu::ManageMenuVisibility( Gtk::Menu* menu, Gtk::MenuItem* menuItem )
{				
	//check if sub menu exist
	Gtk::Menu_Helpers::MenuList children = menu->items();
	std::string name = menu->get_name();
	if( children.empty() &&  menuItem )
	{
		menuItem->hide();
	}
	else
	{
		bool hasToBeVisible = false;

		Gtk::Menu_Helpers::MenuList::iterator iter = children.begin();
		for( iter; iter != children.end(); iter++ )
		{
			if( iter->is_visible() )
			{
				hasToBeVisible = true;
			}
			
			if( iter->has_submenu() )
			{
				ManageMenuVisibility( iter->get_submenu(), dynamic_cast< Gtk::MenuItem* >( &*iter ) );
			}
		}

		if( hasToBeVisible && menuItem )
		{
			menuItem->show();
		}
		else if( menuItem )
		{
			menuItem->hide();
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

	std::map< vgd::Shp < vgUI::actions::IActionUI >, Gtk::MenuItem* >::iterator it = m_actionMap.begin();

	for( it; it != m_actionMap.end(); it++ )
	{
		if( it->first->isValide( state ) )
		{
			it->second->show();
			setParams( it->first->getAction() );
		}
		else
		{
			it->second->hide();
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



void ActionsMenu::manageHiddenNodeMenu()
{
	manageMenu( m_actionsRegistry.getHiddenNodeActionList() );
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



} // namespace node

} // namespace vgGTK
