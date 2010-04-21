// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/node/ActionsNode.hpp"

#include <gtkmm/filechooserdialog.h>
#include <gtkmm/menu.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/stock.h>
#include <gtkmm/window.h>

#include <vgAlg/node/TriSet.hpp>
#include <vgAlg/node/VertexShape.hpp>
#include <vgDebug/convenience.hpp>
#include <vgd/node/TriSet.hpp>
#include <vgGTK/graph/Browser.hpp>
#include <vgGTK/node/SelectedNode.hpp>
#include <vgOpenCOLLADA/exporter/SceneExporter.hpp>



namespace vgGTK
{

namespace node
{

ActionsNode::ActionsNode( POPUP_LOCATION location ) :
m_actions( Gtk::ActionGroup::create() ),
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
		"  </popup>"
		"</ui>";
	
	
	m_uiManager->insert_action_group( m_actions );
	m_uiManager->add_ui_from_string( m_uiDefinition );

	m_actions->add( Gtk::Action::create("GetNodeInTree", "GetNode"), sigc::mem_fun(this, &ActionsNode::onGetNodeInTree) );
	m_actions->add( Gtk::Action::create("ExpandSubTree", "Expand"), sigc::mem_fun(this, &ActionsNode::onExpandSubTree) );
	m_actions->add( Gtk::Action::create("RemoveNode", "Remove"), sigc::mem_fun(this, &ActionsNode::onRemoveNode) );
	m_actions->add( Gtk::Action::create("HideNode", "Hide"), sigc::mem_fun(this, &ActionsNode::onHideNode) );
	m_actions->add( Gtk::Action::create("HideAllNode", "Hide All"), sigc::mem_fun(this, &ActionsNode::onHideAll) );
	m_actions->add( Gtk::Action::create("HideAllExceptSelectedNode", "Hide All Except Selection"), sigc::mem_fun(this, &ActionsNode::onHideAllExceptSelected) );
	m_actions->add( Gtk::Action::create("HiddenNode", "Hidden Nodes") );
	m_actions->add( Gtk::Action::create("ShowAllHiddenNode", "Show All"), sigc::mem_fun(this, &ActionsNode::onShowAllHiddenNode) );
	m_actions->add( Gtk::Action::create("ExportNode", "Export"), sigc::mem_fun(this, &ActionsNode::onExportNode) );
	m_actions->add( Gtk::Action::create("SetToDefault", "SetToDefault"), sigc::mem_fun(this, &ActionsNode::onSetToDefault) );
	m_actions->add( Gtk::Action::create("SetOptionalToDefault", "SetOptionalToDefault"), sigc::mem_fun(this, &ActionsNode::onSetOptionalToDefault) );
	m_actions->add( Gtk::Action::create("InvertTriangleOrientation", "InvertTriangleOrientation"), sigc::mem_fun(this, &ActionsNode::onInvertTriangleOrientation) );
	m_actions->add( Gtk::Action::create("InvertNormalOrientation", "InvertNormalOrientation"), sigc::mem_fun(this, &ActionsNode::onInvertNormalOrientation) );

	Gtk::Widget		* hiddenWidget	= m_uiManager->get_widget("/popup/HiddenNode");
	m_hiddenMenuItem= dynamic_cast< Gtk::MenuItem * >( hiddenWidget );

	m_hiddenMenu	= new Gtk::Menu();

	m_hiddenMenuItem->set_submenu( *m_hiddenMenu );
	m_hiddenMenuItem->property_visible() = false;
}



void ActionsNode::setCanvas( vgUI::Canvas * canvas )
{
	m_canvas = canvas;
}



bool ActionsNode::onBoutonPressEvent( GdkEventButton * event )
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

		vgd::node::Node * castNode = m_canvas->castRay( event->x, height - event->y );

		if ( castNode )
		{
			vgd::Shp< vgd::node::Node > currentNode = castNode->shpFromThis();

			showPopup(event, currentNode, NODE);
		}
		else
		{
			showPopup(event, node, CANVAS);
		}
	}

	return true;
}



void ActionsNode::showPopup(GdkEventButton * event, vgd::Shp< vgd::node::Node > node, POPUP_LOCATION location)
{
	//@todo don't show "ExpandSubTree" if node don't have any children.
	m_currentNode = node;
	m_location = location;

	m_actions->get_action("GetNodeInTree")->set_visible(false);
	m_actions->get_action("ExpandSubTree")->set_visible(false);
	m_actions->get_action("RemoveNode")->set_visible(false);
	m_actions->get_action("HideNode")->set_visible(false);
	m_actions->get_action("HideAllNode")->set_visible(false);
	m_actions->get_action("HideAllExceptSelectedNode")->set_visible(false);
	m_actions->get_action("ShowAllHiddenNode")->set_visible(false);	
	m_actions->get_action("ExportNode")->set_visible(false);
	m_actions->get_action("SetToDefault")->set_visible(false);
	m_actions->get_action("SetOptionalToDefault")->set_visible(false);
	m_actions->get_action("InvertTriangleOrientation")->set_visible(false);
	m_actions->get_action("InvertNormalOrientation")->set_visible(false);

	//if there is no shape in graph, don't display menu at all.
	vgd::visitor::predicate::ByType<vgd::node::VertexShape> predicate;
	vgd::Shp< vgd::node::NodeList > result;
	result = vgd::visitor::find( m_canvas->getRoot(), predicate );
	if( result->size() < 1 && m_location == CANVAS )
	{
		return;
	}

	int displayedNode = getDisplayedNodeNumber();
	if (displayedNode > 0 && m_location == CANVAS )
	{
		m_actions->get_action("HideAllNode")->set_visible(true); //show "hide all" only if there is at least one node displayed.
	}

	//check if all node contained in m_hiddenNodes exists and display their menu items.
	vgd::Shp < HiddenNode > hidden;
	vgd::Shp< std::list< vgd::Shp < HiddenNode > > > hiddenNodes = vgGTK::node::SelectedNode::getSelectedNode()->getHiddenNodeList();
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
			Gtk::MenuItem	* item = Gtk::manage( new Gtk::MenuItem( hidden->getNode()->getName() ) );
			hidden->setMenuItem( item );
			item->signal_activate().connect( sigc::bind<0>( sigc::mem_fun(this, &ActionsNode::onShowNode), hidden) );			
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

	if( m_location == NODE )
	{
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
	else if( m_location == TREE )
	{
		m_actions->get_action("RemoveNode")->set_visible(true);
		m_actions->get_action("SetToDefault")->set_visible(true);
		m_actions->get_action("SetOptionalToDefault")->set_visible(true);		

		if(!node->isAKindOf<vgd::node::VertexShape>())
		{
			m_actions->get_action("ExpandSubTree")->set_visible(true);
		}
		else
		{
			m_actions->get_action("ExportNode")->set_visible(true);
			if( !isAlreadyHidden( node ) )
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
	}

	Gtk::Menu *	popupMenu = dynamic_cast< Gtk::Menu * >( m_uiManager->get_widget("/popup") );

	Gtk::manage( popupMenu );
	popupMenu->popup( event->button, event->time );
}



void ActionsNode::onGetNodeInTree()
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
	vgGTK::node::SelectedNode::getSelectedNode()->setSelectedNode( node );
	vgDebug::get().logStatus( "Node %s selected.", node->getName().c_str() );
}



void ActionsNode::onExpandSubTree()
{
	vgGTK::node::SelectedNode::getSelectedNode()->setAction( EXPAND );
}



void ActionsNode::onRemoveNode()
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
	vgGTK::node::SelectedNode::getSelectedNode()->setSelectedNode( node );
	vgGTK::node::SelectedNode::getSelectedNode()->setAction( REMOVE );
	vgDebug::get().logStatus( "Node %s removed.", node->getName().c_str() );
}



void ActionsNode::onHideNode()
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();

	if( isAlreadyHidden( node ) )
	{
		return;
	}
	
	Gtk::MenuItem	* item = new Gtk::MenuItem(node->getName());

	vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::dynamic_pointer_cast< vgd::node::VertexShape >( node );

	vgd::Shp < HiddenNode > hidden = vgd::makeShp( new HiddenNode(vertexShape) );
	vgGTK::node::SelectedNode::getSelectedNode()->getHiddenNodeList()->push_back( hidden );
	hidden->hide();
	
	item->signal_activate().connect( sigc::bind<0>( sigc::mem_fun(this, &ActionsNode::onShowNode), hidden) );

	vgGTK::node::SelectedNode::getSelectedNode()->setAction( REFRESH );

	vgDebug::get().logStatus( "Node %s hidden.", node->getName().c_str() );
}



bool ActionsNode::isAlreadyHidden( vgd::Shp< vgd::node::Node > node )
{
	bool retVal = false;
	
	vgd::Shp < HiddenNode > hidden;
	vgd::Shp< std::list< vgd::Shp < HiddenNode > > > hiddenNodes = vgGTK::node::SelectedNode::getSelectedNode()->getHiddenNodeList();	
	std::list< vgd::Shp < HiddenNode > >::iterator it = hiddenNodes->begin();
	for( it; it !=  hiddenNodes->end(); it++)
	{
		hidden = (*it);

		if( hidden->getNode() == node )
		{
			return true;
		}
	}

	return retVal;
}



int ActionsNode::getDisplayedNodeNumber()
{
	int counter = 0;

	vgd::visitor::predicate::ByType<vgd::node::VertexShape> predicate;
	vgd::Shp< vgd::node::NodeList > result;
	result = vgd::visitor::find( m_canvas->getRoot(), predicate );

	std::list< vgd::Shp < vgd::node::Node > >::iterator iter = result->begin();
	for( iter; iter !=  result->end(); iter++ )
	{
		if( !isAlreadyHidden( (*iter) ) )
		{
			counter++;
		}
	}

	return counter;
}



void ActionsNode::onShowNode( vgd::Shp < HiddenNode > hidden )
{
	hidden->restorePrimitives();

	vgGTK::node::SelectedNode::getSelectedNode()->getHiddenNodeList()->remove(hidden);
	vgDebug::get().logStatus( "Node %s restored.", hidden->getNode()->getName().c_str() );
	hidden.reset();

	vgGTK::node::SelectedNode::getSelectedNode()->setAction( REFRESH );
}



void ActionsNode::onShowAllHiddenNode()
{
	vgd::Shp < HiddenNode > hidden;
	vgd::Shp< std::list< vgd::Shp < HiddenNode > > > hiddenNodes = vgGTK::node::SelectedNode::getSelectedNode()->getHiddenNodeList();	
	std::list< vgd::Shp < HiddenNode > >::iterator it = hiddenNodes->begin();
	for( it; it !=  hiddenNodes->end(); )
	{
		hidden = (*it);
		it++;
		onShowNode( hidden );
	}
}



void ActionsNode::onHideAll()
{
	vgd::Shp < vgd::node::Node > currentNode = m_currentNode.lock();
	vgd::visitor::predicate::ByType<vgd::node::VertexShape> predicate;
	vgd::Shp< vgd::node::NodeList > result;
	result = vgd::visitor::find( m_canvas->getRoot(), predicate );

	std::list< vgd::Shp < vgd::node::Node > >::iterator it = result->begin();
	for( it; it !=  result->end(); it++ )
	{
		m_currentNode = (*it);
		onHideNode();
	}

	m_currentNode = currentNode;
}



void ActionsNode::onHideAllExceptSelected()
{
	vgd::Shp < vgd::node::Node > currentNode = m_currentNode.lock();
	vgd::visitor::predicate::ByType<vgd::node::VertexShape> predicate;
	vgd::Shp< vgd::node::NodeList > result;
	result = vgd::visitor::find( m_canvas->getRoot(), predicate );

	std::list< vgd::Shp < vgd::node::Node > >::iterator it = result->begin();
	for( it; it !=  result->end(); it++ )
	{
		if ( currentNode != (*it) )
		{
			m_currentNode = (*it);
			onHideNode();
		}
	}

	m_currentNode = currentNode;
}



void ActionsNode::onExportNode()
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
	vgGTK::node::SelectedNode::getSelectedNode()->setSelectedNode( node );
	vgGTK::node::SelectedNode::getSelectedNode()->setAction( EXPORT );
	vgDebug::get().logStatus( "Node %s exported.", node->getName().c_str() );
}



void ActionsNode::onSetToDefault()
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();

	node->setToDefaults();

	vgGTK::node::SelectedNode::getSelectedNode()->setAction( REFRESH );
}



void ActionsNode::onSetOptionalToDefault()
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();

	node->setOptionalsToDefaults();

	vgGTK::node::SelectedNode::getSelectedNode()->setAction( REFRESH );
}



void ActionsNode::onInvertTriangleOrientation()
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
	
	if( node->isA<vgd::node::VertexShape>() )
	{
		vgAlg::node::invertPrimitiveOrientation( vgd::dynamic_pointer_cast< vgd::node::VertexShape >( node ) );
	}
	else if( node->isA<vgd::node::TriSet>() )
	{
		vgAlg::node::invertTriangleOrientation( vgd::dynamic_pointer_cast< vgd::node::TriSet >( node ) );
	}

	vgGTK::node::SelectedNode::getSelectedNode()->setAction( REFRESH );
}



void ActionsNode::onInvertNormalOrientation()
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();

	vgAlg::node::invertNormalOrientation( vgd::dynamic_pointer_cast< vgd::node::VertexShape >( node ) );

	vgGTK::node::SelectedNode::getSelectedNode()->setAction( REFRESH );
}



} // namespace node

} // namespace vgGTK
