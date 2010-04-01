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
#include <vgOpenCOLLADA/exporter/SceneExporter.hpp>



namespace vgGTK
{

namespace node
{

vgd::Shp< ActionsNode > ActionsNode::m_actionsNode;

vgd::Shp< ActionsNode > ActionsNode::getActionsNode()
{
	if(!m_actionsNode)
	{
		m_actionsNode = vgd::Shp< ActionsNode >( new ActionsNode );
	}
	
	return m_actionsNode;
}



ActionsNode::ActionsNode() :
m_actions( Gtk::ActionGroup::create() ),
m_uiManager( Gtk::UIManager::create() ),
m_location( CANVAS )
{
	// Initializes the user interface manager.
	m_uiDefinition =
		"<ui>"
		"  <popup name='popup'>"
		"    <menuitem action='GetNodeInTree'/>"
		"    <separator/>"
		"    <menuitem action='ExpandSubTree'/>"
		"    <menuitem action='RemoveNode'/>"
		"    <menuitem action='HideNode'/>"
		"    <menu action='HiddenNode'/>"
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
	m_actions->add( Gtk::Action::create("HiddenNode", "Hidden Nodes") );
	m_actions->add( Gtk::Action::create("ExportNode", "Export"), sigc::mem_fun(this, &ActionsNode::onExportNode) );
	m_actions->add( Gtk::Action::create("SetToDefault", "SetToDefault"), sigc::mem_fun(this, &ActionsNode::onSetToDefault) );
	m_actions->add( Gtk::Action::create("SetOptionalToDefault", "SetOptionalToDefault"), sigc::mem_fun(this, &ActionsNode::onSetOptionalToDefault) );
	m_actions->add( Gtk::Action::create("InvertTriangleOrientation", "InvertTriangleOrientation"), sigc::mem_fun(this, &ActionsNode::onInvertTriangleOrientation) );
	m_actions->add( Gtk::Action::create("InvertNormalOrientation", "InvertNormalOrientation"), sigc::mem_fun(this, &ActionsNode::onInvertNormalOrientation) );

	Gtk::Widget		* hiddenWidget	= m_uiManager->get_widget("/popup/HiddenNode");
	m_hiddenMenuItem= dynamic_cast< Gtk::MenuItem * >( hiddenWidget );

	m_hiddenMenu	= Gtk::manage( new Gtk::Menu() );

	m_hiddenMenuItem->set_submenu( *m_hiddenMenu );

	m_hiddenMenuItem->property_visible() = false;

	//Gtk::MenuItem	* test = Gtk::manage( new Gtk::MenuItem("test") );
	//test->signal_activate().connect( sigc::mem_fun(this, &ActionsNode::onShowNode) );

	//hiddenMenu->append(*test);
	//hiddenMenu->show_all();
}



void ActionsNode::setCanvas( vgUI::Canvas * canvas )
{
	m_canvas = canvas;
}



void ActionsNode::setBrowser( vgGTK::graph::Browser * browser )
{
	m_browser = browser;
}



bool ActionsNode::onBoutonPressEvent( GdkEventButton * event )
{
	if( event->button == 3 )
	{
		// Retrieves some properties of the window.
		gint	x;
		gint	y;
		gint	width;
		gint	height;
		gint	depth;

		gdk_window_get_geometry( event->window, &x, &y, &width, &height, &depth );

		vgd::node::Node * node = m_canvas->castRay( event->x, height - event->y );

		if ( node )
		{
			vgd::Shp< vgd::node::Node > currentNode = node->shpFromThis();

			showPopup(event, currentNode, NODE);
		}
		else
		{
			showPopup(event, m_currentNode, CANVAS);
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
	m_actions->get_action("ExportNode")->set_visible(false);
	m_actions->get_action("SetToDefault")->set_visible(false);
	m_actions->get_action("SetOptionalToDefault")->set_visible(false);
	m_actions->get_action("InvertTriangleOrientation")->set_visible(false);
	m_actions->get_action("InvertNormalOrientation")->set_visible(false);

	//m_hiddenMenuItem->property_visible() = false;

	if( m_location == CANVAS && m_hiddenMenuItem->property_visible() == false)
	{
		return;
	}
	else if( m_location == NODE )
	{
		m_actions->get_action("RemoveNode")->set_visible(true);
		m_actions->get_action("SetToDefault")->set_visible(true);
		m_actions->get_action("SetOptionalToDefault")->set_visible(true);
		m_actions->get_action("ExportNode")->set_visible(true);
		m_actions->get_action("HideNode")->set_visible(true);
		m_actions->get_action("InvertTriangleOrientation")->set_visible(true);
		m_actions->get_action("InvertNormalOrientation")->set_visible(true);
		
		if(!m_browser)
		{
			m_actions->get_action("GetNodeInTree")->set_sensitive(false);
		}

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
			m_actions->get_action("GetNodeInTree")->set_visible(true);
			m_actions->get_action("ExpandSubTree")->set_visible(true);
		}
		else
		{
			m_actions->get_action("ExportNode")->set_visible(true);
			m_actions->get_action("HideNode")->set_visible(true);
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
	m_browser->selectNode(m_currentNode);
}



void ActionsNode::onExpandSubTree()
{
	m_browser->expandSubTree();
}



void ActionsNode::onRemoveNode()
{
	if(m_browser)
	{
		if (m_location == NODE)
		{
			m_browser->selectNode(m_currentNode);
		}

		m_browser->removeNode();
	}
	else
	{
		m_currentNode->getParent()->removeChild(m_currentNode);
	}
}



void ActionsNode::onHideNode()
{
	Gtk::MenuItem	* item = Gtk::manage( new Gtk::MenuItem(m_currentNode->getName()) );

	m_hiddenMenu->append( *item );
	m_hiddenMenu->show_all();	
	m_hiddenMenuItem->property_visible() = true;

	vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::dynamic_pointer_cast< vgd::node::VertexShape >(m_currentNode );

	vgd::Shp < HiddenNode > hidden = vgd::makeShp( new HiddenNode(vertexShape, item) );
	hidden->hide();
	
	item->signal_activate().connect( sigc::bind<0>( sigc::mem_fun(this, &ActionsNode::onShowNode), hidden) );

	m_canvas->refreshForced();
}



void ActionsNode::onShowNode( vgd::Shp < HiddenNode > hidden )
{
	hidden->restorePrimitives();

	delete hidden->getMenuItem();
	hidden.reset();
	
	if( m_hiddenMenu->items().size() < 1 )
	{
		m_hiddenMenuItem->property_visible() = false;
	}

	m_canvas->refreshForced();
}



void ActionsNode::onExportNode()
{
	Gtk::Window				* topLevel = dynamic_cast< Gtk::Window * >(m_browser->get_toplevel());
	Gtk::FileChooserDialog	chooser( *topLevel, "Save VertexShape As", Gtk::FILE_CHOOSER_ACTION_SAVE );
	Gtk::FileFilter			dotFilter;

	dotFilter.set_name( "COLLADA file (*.DAE)" );
	dotFilter.add_pattern( "*.DAE" );

	chooser.add_filter( dotFilter );
	chooser.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL );
	chooser.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK );
	chooser.set_do_overwrite_confirmation( true );

	const int result = chooser.run();
	if( result == Gtk::RESPONSE_OK )
	{
		const Glib::ustring	filename( chooser.get_filename() );
		
		vgOpenCOLLADA::exporter::SceneExporter exporter( filename, m_canvas->getRoot(), vgd::dynamic_pointer_cast< vgd::node::VertexShape >( m_currentNode ) );

		if( !exporter.doExport() )
		{
			Gtk::MessageDialog	messageDlg(*topLevel, "Unable to save VertexShape.", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
			
			messageDlg.run();
		}
	}
}



void ActionsNode::onSetToDefault()
{
	m_currentNode->setToDefaults();

	m_canvas->refreshForced();
}



void ActionsNode::onSetOptionalToDefault()
{
	m_currentNode->setOptionalsToDefaults();

	m_canvas->refreshForced();
}



void ActionsNode::onInvertTriangleOrientation()
{
	if( m_currentNode->isA<vgd::node::VertexShape>() )
	{
		vgAlg::node::invertPrimitiveOrientation( vgd::dynamic_pointer_cast< vgd::node::VertexShape >( m_currentNode ) );
	}
	else if( m_currentNode->isA<vgd::node::TriSet>() )
	{
		vgAlg::node::invertTriangleOrientation( vgd::dynamic_pointer_cast< vgd::node::TriSet >( m_currentNode ) );
	}

	m_canvas->refreshForced();
}



void ActionsNode::onInvertNormalOrientation()
{
	vgAlg::node::invertNormalOrientation( vgd::dynamic_pointer_cast< vgd::node::VertexShape >( m_currentNode ) );

	m_canvas->refreshForced();
}


} // namespace node

} // namespace vgGTK

