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
#include <vge/technique/ApplyGeometricalTransformations.hpp>
#include <vgeGL/engine/Engine.hpp>
#include <vgGTK/node/SelectedNode.hpp>
#include <vgOpenCOLLADA/exporter/SceneExporter.hpp>



namespace vgGTK
{

namespace node
{

ActionsNode::ActionsNode( POPUP_LOCATION location ) 
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
		"    <menuitem action='PastNode'/>"
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
	
	
	m_uiManager->insert_action_group( m_actions );
	m_uiManager->add_ui_from_string( m_uiDefinition );

	m_actions->add( Gtk::Action::create("GetNodeInTree", "GetNode"), sigc::mem_fun(this, &ActionsNode::onGetNodeInTree) );

	m_actions->add( Gtk::Action::create("ExpandSubTree", "Expand"), sigc::mem_fun(this, &ActionsNode::onExpandSubTree) );
	m_actions->add( Gtk::Action::create("RemoveNode", "Remove"), sigc::mem_fun(this, &ActionsNode::onRemoveNode) );

	m_actions->add( Gtk::Action::create("PreviousNode", "Previous"), sigc::mem_fun(this, &ActionsNode::onPreviousNode) );
	m_actions->add( Gtk::Action::create("NextNode", "Next"), sigc::mem_fun(this, &ActionsNode::onNextNode) );

	m_actions->add( Gtk::Action::create("CutNode", "Cut"), sigc::mem_fun(this, &ActionsNode::onCutNode) );
	m_actions->add( Gtk::Action::create("CopyNode", "Copy"), sigc::mem_fun(this, &ActionsNode::onCopyNode) );
	m_actions->add( Gtk::Action::create("PastNode", "Paste"), sigc::mem_fun(this, &ActionsNode::onPastNode) );
	m_actions->add( Gtk::Action::create("InsertNode", "Insert Node") );

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
	m_actions->add( Gtk::Action::create("ApplyGeometricalTransformation", "ApplyGeometricalTransformation"), sigc::mem_fun(this, &ActionsNode::onApplyGeometricalTransformation) );


	Gtk::Widget		* hiddenWidget	= m_uiManager->get_widget("/popup/HiddenNode");
	m_hiddenMenuItem				= dynamic_cast< Gtk::MenuItem * >( hiddenWidget );

	m_hiddenMenu					= new Gtk::Menu();

	m_hiddenMenuItem->set_submenu( *m_hiddenMenu );
	m_hiddenMenuItem->property_visible() = false;


	Gtk::Widget		* insertWidget		= m_uiManager->get_widget("/popup/InsertNode");
	m_insertMenuItem	= dynamic_cast< Gtk::MenuItem * >( insertWidget );

	m_insertNode = new InsertNode();

	m_insertMenuItem->set_submenu( *m_insertNode->getMenu() );
	m_insertMenuItem->property_visible() = false;
}



ActionsNode::~ActionsNode()
{
	delete m_hiddenMenu;
	delete m_hiddenMenuItem;
	delete m_insertMenuItem;
	delete m_insertNode;
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

		vgd::node::Node *castNode = m_canvas->castRay( event->x, height - event->y );

		if ( castNode )
		{
			vgd::Shp< vgd::node::Node > currentNode = castNode->shpFromThis();

			showPopup(event, currentNode, currentNode->getParent(), NODE);
		}
		else
		{
			if( node )
			{
				showPopup(event, node, node->getParent(), CANVAS);
			}
			else
			{
				vgd::Shp< vgd::node::Group > parent;
				showPopup(event, node, parent, CANVAS);
			}
		}
	}
	// else do nothing.

	return true;
}



void ActionsNode::showPopup( GdkEventButton * event, vgd::Shp< vgd::node::Node > node, vgd::Shp< vgd::node::Group > parentNode, POPUP_LOCATION location )
{
	//@todo don't show "ExpandSubTree" if node don't have any children.
	m_currentNode = node;
	m_currentParentNode = parentNode;
	m_location = location;

	m_insertNode->setCurrentNode( node, parentNode );

	m_actions->get_action("GetNodeInTree")->set_visible(false);
	m_actions->get_action("ExpandSubTree")->set_visible(false);
	m_actions->get_action("RemoveNode")->set_visible(false);

	m_actions->get_action("PreviousNode")->set_visible(false);
	m_actions->get_action("NextNode")->set_visible(false);
	m_actions->get_action("CutNode")->set_visible(false);
	m_actions->get_action("CopyNode")->set_visible(false);
	m_actions->get_action("PastNode")->set_visible(false);

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

	//if there is no shape in graph, don't display menu at all.
	vgd::visitor::predicate::ByKindOfType<vgd::node::VertexShape> predicate;
	vgd::Shp< vgd::node::NodeList > result;
	result = vgd::visitor::find( m_canvas->getRoot(), predicate );
	if( result->size() < 1 && m_location == CANVAS )
	{
		return; //no menu needed.
	}

	int displayedNode = getDisplayedNodeNumber();
	if (displayedNode > 0 && m_location == CANVAS )
	{
		m_actions->get_action("HideAllNode")->set_visible(true); //show "hide all" only if there is at least one node displayed.
	}

	//check if all node contained in hidden nodes list exists and display their menu items.
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
			Gtk::MenuItem	* item = new Gtk::MenuItem( hidden->getNode()->getName() );
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

	if( parentNode && m_location != CANVAS )
	{
		m_actions->get_action("CutNode")->set_visible(true);
		m_actions->get_action("CopyNode")->set_visible(true);
	}

	if( vgGTK::node::SelectedNode::getSelectedNode()->getClipboardedNode() && m_location == TREE )
	{
		m_actions->get_action("PastNode")->set_visible(true);
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

		m_insertMenuItem->property_visible() = true;
	}

	Gtk::Menu *	popupMenu = dynamic_cast< Gtk::Menu * >( m_uiManager->get_widget("/popup") );
	popupMenu->popup( event->button, event->time );
}



void ActionsNode::onGetNodeInTree()
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
	vgGTK::node::SelectedNode::getSelectedNode()->setAction( REFRESH );
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
		return; //node is already hidden.
	}

	vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::dynamic_pointer_cast< vgd::node::VertexShape >( node );

	vgd::Shp < HiddenNode > hidden = vgd::makeShp( new HiddenNode(vertexShape) );
	vgGTK::node::SelectedNode::getSelectedNode()->getHiddenNodeList()->push_back( hidden );
	hidden->hide();

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

	vgd::visitor::predicate::ByKindOfType<vgd::node::VertexShape> predicate;
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
	vgd::visitor::predicate::ByKindOfType<vgd::node::VertexShape> predicate;
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
	vgd::visitor::predicate::ByKindOfType<vgd::node::VertexShape> predicate;
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



void ActionsNode::onApplyGeometricalTransformation()
{
	using vge::visitor::NodeCollectorExtended;
	vge::technique::ApplyGeometricalTransformations technique;
	vgeGL::engine::Engine* engine = new vgeGL::engine::Engine();
	NodeCollectorExtended<> collector( true, false, NodeCollectorExtended<>::IGNORE_KIT );
	m_canvas->getRoot()->traverse( collector );
	technique.apply( engine, collector.getTraverseElements() );

	vgGTK::node::SelectedNode::getSelectedNode()->setAction( REFRESH );
}



void ActionsNode::onPreviousNode()
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
	vgd::Shp< vgd::node::Group > parentGroup = m_currentParentNode.lock();

	if( node && parentGroup )
	{
		int index = parentGroup->findChild( node );

		if ( index > 0 )
		{
			vgd::Shp< vgd::node::Node > prevNode = parentGroup->getAbstractChild( index - 1 );

			parentGroup->replaceChild( node, index - 1 );
			parentGroup->replaceChild( prevNode, index );

			vgGTK::node::SelectedNode::getSelectedNode()->setAction( REFRESH );
			vgGTK::node::SelectedNode::getSelectedNode()->setSelectedNode( node );
		}
	}	
}



void ActionsNode::onNextNode()
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
	vgd::Shp< vgd::node::Group > parentGroup = m_currentParentNode.lock();

	if( node && parentGroup )
	{
		int index = parentGroup->findChild( node );

		if ( index < parentGroup->size() -1 )
		{
			vgd::Shp< vgd::node::Node > nextNode = parentGroup->getAbstractChild( index + 1 );
			parentGroup->replaceChild( node, index + 1 );
			parentGroup->replaceChild( nextNode, index );
			
			vgGTK::node::SelectedNode::getSelectedNode()->setAction( REFRESH );
			vgGTK::node::SelectedNode::getSelectedNode()->setSelectedNode( node );
		}
	}
}



void ActionsNode::onCutNode()
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
	vgd::Shp< vgd::node::Group > parentGroup = m_currentParentNode.lock();

	if( node && parentGroup )
	{
		vgGTK::node::SelectedNode::getSelectedNode()->setClipboardedNode( node );
		parentGroup->removeChild( node );
		vgGTK::node::SelectedNode::getSelectedNode()->setAction( REFRESH );
	}
}



void ActionsNode::onCopyNode()
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
	vgd::Shp< vgd::node::Group > parentGroup = m_currentParentNode.lock();

	if( node && parentGroup )
	{
		vgGTK::node::SelectedNode::getSelectedNode()->setClipboardedNode( node );
	}
}



void ActionsNode::onPastNode()
{
	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
	vgd::Shp< vgd::node::Group > parentGroup = m_currentParentNode.lock();

	vgd::Shp< vgd::node::Node > clipboardedNode = vgGTK::node::SelectedNode::getSelectedNode()->getClipboardedNode();
	if( clipboardedNode )
	{
		if( node )
		{
			if( node->isAKindOf<vgd::node::Group>() )
			{
				vgd::dynamic_pointer_cast< vgd::node::Group >( node )->addChild( clipboardedNode );
			}
			else if( parentGroup )
			{
				parentGroup->insertChild( clipboardedNode, parentGroup->findChild( node ) );
			}
		}

		vgGTK::node::SelectedNode::getSelectedNode()->setAction( REFRESH );
	}
}



} // namespace node

} // namespace vgGTK
