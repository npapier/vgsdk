// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/node/ActionsMenu.hpp"

#include <gtkmm/filechooserdialog.h>
#include <gtkmm/menu.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/stock.h>
#include <gtkmm/window.h>

#include <vgAlg/node/TriSet.hpp>
#include <vgAlg/node/VertexShape.hpp>
#include <vgDebug/convenience.hpp>
#include <vgd/node/TriSet.hpp>
#include <vge/technique/ApplyGeometricalTransformations.hpp>
#include <vgeGL/engine/Engine.hpp>
#include <vgGTK/node/SelectedNode.hpp>
#include <vgOpenCOLLADA/exporter/SceneExporter.hpp>



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
		"    <menuitem action='GetNodeInTree'/>"
		"    <separator/>"
		"    <menuitem action='ExpandSubTree'/>"
		"    <menuitem action='RemoveNode'/>"
		"    <separator/>"
		"    <menuitem action='PreviousNode'/>"
		"    <menuitem action='NextNode'/>"
		"    <separator/>"
		"    <menuitem action='CutNode'/>"
		"    <menuitem action='CopyNode'/>"
		"    <menuitem action='PasteNode'/>"
		"    <menu action='InsertNode'/>"
		"    <separator/>"
		"    <menuitem action='HideNode'/>"
		"    <menuitem action='HideAllNode'/>"
		"    <menuitem action='HideAllExceptSelectedNode'/>"
		"    <menu action='HiddenNode'/>"
		"	 <menuitem action='ShowAllHiddenNode'/>"
		"    <separator/>"
		"    <menuitem action='ExportNode'/>"
		"    <separator/>"
		"    <menuitem action='SetToDefault'/>"
		"    <menuitem action='SetOptionalToDefault'/>"
		"    <separator/>"
		"    <menuitem action='InvertTriangleOrientation'/>"
		"    <menuitem action='InvertNormalOrientation'/>"
		"    <menuitem action='ApplyGeometricalTransformation'/>"
		"  </popup>"
		"</ui>";
	
	m_actionsNode = vgd::Shp< ActionsNode >( new ActionsNode() );
	m_uiManager->insert_action_group( m_actions );
	m_uiManager->add_ui_from_string( m_uiDefinition );

	m_actions->add( Gtk::Action::create("GetNodeInTree", "GetNode"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onGetNodeInTree) );

	m_actions->add( Gtk::Action::create("ExpandSubTree", "Expand"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onExpandSubTree) );
	m_actions->add( Gtk::Action::create("RemoveNode", "Remove"), Gtk::AccelKey("Z"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onRemoveNode) );

	m_actions->add( Gtk::Action::create("PreviousNode", "Previous"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onPreviousNode) );
	m_actions->add( Gtk::Action::create("NextNode", "Next"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onNextNode) );

	m_actions->add( Gtk::Action::create("CutNode", "Cut"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onCutNode) );
	m_actions->add( Gtk::Action::create("CopyNode", "Copy"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onCopyNode) );
	m_actions->add( Gtk::Action::create("PasteNode", "Paste"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onPasteNode) );
	m_actions->add( Gtk::Action::create("InsertNode", "Insert Node") );

	m_actions->add( Gtk::Action::create("HideNode", "Hide"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onHideNode) );
	m_actions->add( Gtk::Action::create("HideAllNode", "Hide All"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onHideAll) );
	m_actions->add( Gtk::Action::create("HideAllExceptSelectedNode", "Hide All Except Selection"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onHideAllExceptSelected) );
	m_actions->add( Gtk::Action::create("HiddenNode", "Hidden Nodes") );
	m_actions->add( Gtk::Action::create("ShowAllHiddenNode", "Show All"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onShowAllHiddenNode) );
	
	m_actions->add( Gtk::Action::create("ExportNode", "Export"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onExportNode) );
	
	m_actions->add( Gtk::Action::create("SetToDefault", "SetToDefault"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onSetToDefault) );
	m_actions->add( Gtk::Action::create("SetOptionalToDefault", "SetOptionalToDefault"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onSetOptionalToDefault) );
	
	m_actions->add( Gtk::Action::create("InvertTriangleOrientation", "InvertTriangleOrientation"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onInvertTriangleOrientation) );
	m_actions->add( Gtk::Action::create("InvertNormalOrientation", "InvertNormalOrientation"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onInvertNormalOrientation) );
	m_actions->add( Gtk::Action::create("ApplyGeometricalTransformation", "ApplyGeometricalTransformation"), sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onApplyGeometricalTransformation) );


	Gtk::Widget		* hiddenWidget	= m_uiManager->get_widget("/popup/HiddenNode");
	m_hiddenMenuItem				= dynamic_cast< Gtk::MenuItem * >( hiddenWidget );

	m_hiddenMenu					= new Gtk::Menu();

	m_hiddenMenuItem->set_submenu( *m_hiddenMenu );
	m_hiddenMenuItem->property_visible() = false;


	Gtk::Widget		* insertWidget	= m_uiManager->get_widget("/popup/InsertNode");
	m_insertMenuItem				= dynamic_cast< Gtk::MenuItem * >( insertWidget );

	m_insertNode					= new InsertNode();

	m_insertMenuItem->set_submenu( *m_insertNode->getMenu() );
	m_insertMenuItem->property_visible() = false;
}



ActionsMenu::~ActionsMenu()
{
	delete m_hiddenMenu;
	delete m_hiddenMenuItem;
	delete m_insertMenuItem;
	delete m_insertNode;
}



void ActionsMenu::setCanvas( vgUI::Canvas * canvas )
{
	m_canvas = canvas;

	m_actionsNode->setCanvas( m_canvas );
}



bool ActionsMenu::onBoutonPressEvent( GdkEventButton * event )
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();

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

			vgGTK::node::SelectedNode::getSelectedNodeObject()->setSelectedNode( currentNode, currentNode->getParent() );
			showPopup(event, NODE);
		}
		else
		{
			if( node )
			{
				vgGTK::node::SelectedNode::getSelectedNodeObject()->setSelectedNode(  node, node->getParent() );
				showPopup(event, CANVAS);
			}
			else
			{
				vgd::Shp< vgd::node::Group > parent;
				vgGTK::node::SelectedNode::getSelectedNodeObject()->setSelectedNode( node );
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
	vgd::visitor::predicate::ByKindOfType<vgd::node::VertexShape> predicate;
	vgd::Shp< vgd::node::NodeList > result;
	result = vgd::visitor::find( m_canvas->getRoot(), predicate );
	if( result->size() < 1 && m_location == CANVAS )
	{
		return; //no menu needed.
	}

	m_currentNode = vgGTK::node::SelectedNode::getSelectedNodeObject()->getSelectedNode();
	m_currentParentNode = vgGTK::node::SelectedNode::getSelectedNodeObject()->getParentSelectedNode();
	m_location = location;

	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
	vgd::Shp< vgd::node::Node > parentNode = m_currentParentNode.lock();

	//m_actionsNode->setCurrentNode( node, parentNode );
	//m_insertNode->setCurrentNode( node, parentNode );

	int displayedNode = m_actionsNode->getDisplayedNodeNumber();

	hideAllMenu();

	//show cut/copy only if different from "root" and pointing on a node.
	if( parentNode && m_location != CANVAS )
	{
		m_actions->get_action("CutNode")->set_visible(true);
		m_actions->get_action("CopyNode")->set_visible(true);
	}

	//show paste only if a node is clipboarded.
	if( vgGTK::node::SelectedNode::getSelectedNodeObject()->getClipboardedNode() && m_location == TREE )
	{
		m_actions->get_action("PasteNode")->set_visible(true);
	}

	manageHiddenNodeMenu( displayedNode );

	switch( m_location )
	{
		case NODE:
			showOnNodeMenu( displayedNode );
			break;

		case TREE:
			showInTreeViewMenu( displayedNode );
			break;

		default:
			break;
	}

	Gtk::Menu *	popupMenu = dynamic_cast< Gtk::Menu * >( m_uiManager->get_widget("/popup") );
	popupMenu->popup( event->button, event->time );
}



void ActionsMenu::hideAllMenu()
{
	m_actions->get_action("GetNodeInTree")->set_visible(false);
	m_actions->get_action("ExpandSubTree")->set_visible(false);
	m_actions->get_action("RemoveNode")->set_visible(false);

	m_actions->get_action("PreviousNode")->set_visible(false);
	m_actions->get_action("NextNode")->set_visible(false);
	m_actions->get_action("CutNode")->set_visible(false);
	m_actions->get_action("CopyNode")->set_visible(false);
	m_actions->get_action("PasteNode")->set_visible(false);

	m_actions->get_action("HideNode")->set_visible(false);
	m_actions->get_action("HideAllNode")->set_visible(false);
	m_actions->get_action("HideAllExceptSelectedNode")->set_visible(false);
	m_actions->get_action("ShowAllHiddenNode")->set_visible(false);	
	m_actions->get_action("ExportNode")->set_visible(false);
	m_actions->get_action("SetToDefault")->set_visible(false);
	m_actions->get_action("SetOptionalToDefault")->set_visible(false);
	m_actions->get_action("InvertTriangleOrientation")->set_visible(false);
	m_actions->get_action("InvertNormalOrientation")->set_visible(false);
	//m_actions->get_action("ApplyGeometricalTransformation")->set_visible(false);
}



void ActionsMenu::manageHiddenNodeMenu( int displayedNode )
{
	//check if all node contained in hidden nodes list exists and display their menu items.
	vgd::Shp < HiddenNode > hidden;
	vgd::Shp< std::list< vgd::Shp < HiddenNode > > > hiddenNodes = vgGTK::node::SelectedNode::getSelectedNodeObject()->getHiddenNodeList();
	std::list< vgd::Shp < HiddenNode > >::iterator it = hiddenNodes->begin();
	m_hiddenMenu->items().clear();
	while( it !=  hiddenNodes->end() )
	{
		hidden = (*it);
		if( !hidden->hasNode() || hidden->getNode()->getNumParents() < 1 )
		{
			it = hiddenNodes->erase(it);
			hidden.reset();
		}
		else
		{
			Gtk::MenuItem	* item = new Gtk::MenuItem( hidden->getNode()->getName() );
			hidden->setMenuItem( item );
			item->signal_activate().connect( sigc::bind<0>( sigc::mem_fun(m_actionsNode.get(), &ActionsNode::onShowNode), hidden) );			
			m_hiddenMenu->append( *item );
			++it;
		}
	}
	m_hiddenMenu->show_all();

	if( m_hiddenMenu->items().size() < 1)
	{
		m_hiddenMenuItem->property_visible() = false;
	}
	else
	{
		m_actions->get_action("ShowAllHiddenNode")->set_visible(true);
		m_hiddenMenuItem->property_visible() = true;
	}

	//show "hide all" only if there is at least one node displayed.
	if (displayedNode > 0 && m_location == CANVAS )
	{
		m_actions->get_action("HideAllNode")->set_visible(true);
	}
}



void ActionsMenu::showOnNodeMenu( int displayedNode )
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
	m_actions->get_action("RemoveNode")->set_visible(true);
	m_actions->get_action("SetToDefault")->set_visible(true);
	m_actions->get_action("SetOptionalToDefault")->set_visible(true);
	m_actions->get_action("ExportNode")->set_visible(true);
	m_actions->get_action("HideNode")->set_visible(true);
	if( displayedNode > 1 )
	{
		m_actions->get_action("HideAllNode")->set_visible(true);
		m_actions->get_action("HideAllExceptSelectedNode")->set_visible(true);
	}
	m_actions->get_action("InvertTriangleOrientation")->set_visible(true);
	m_actions->get_action("InvertNormalOrientation")->set_visible(true);

	m_actions->get_action("GetNodeInTree")->set_visible(true);
	m_actions->get_action("GetNodeInTree")->set_label(node->getName());
}



void ActionsMenu::showInTreeViewMenu( int displayedNode )
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
	vgd::Shp< vgd::node::Group > parentNode = m_currentParentNode.lock();	
	
	m_actions->get_action("RemoveNode")->set_visible(true);
	m_actions->get_action("SetToDefault")->set_visible(true);
	m_actions->get_action("SetOptionalToDefault")->set_visible(true);		

	if( parentNode )
	{
		const int index = parentNode->findChild( node );
		if ( index > 0 )
		{
			m_actions->get_action("PreviousNode")->set_visible(true);
		}

		if ( index < parentNode->size() -1 )
		{
			m_actions->get_action("NextNode")->set_visible(true);
		}
	}

	if(!node->isAKindOf<vgd::node::VertexShape>())
	{
		m_actions->get_action("ExpandSubTree")->set_visible(true);
	}
	else
	{
		m_actions->get_action("ExportNode")->set_visible(true);
		if( !m_actionsNode->isAlreadyHidden( node ) )
		{
			m_actions->get_action("HideNode")->set_visible(true);
		}
		if( displayedNode > 1 )
		{
			m_actions->get_action("HideAllNode")->set_visible(true);
			m_actions->get_action("HideAllExceptSelectedNode")->set_visible(true);
		}

		m_actions->get_action("InvertTriangleOrientation")->set_visible(true);
		m_actions->get_action("InvertNormalOrientation")->set_visible(true);
	}

	m_insertMenuItem->property_visible() = true;
}



} // namespace node

} // namespace vgGTK
