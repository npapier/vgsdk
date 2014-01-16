// VGSDK - Copyright (C) 2008, 2009, 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Maxime Peresson

#include "vgGTK/graph/Browser.hpp"

#include <cassert>
#include <iostream>
#include <fstream>

#include <boost/bind.hpp>
#include <boost/signal.hpp>

#include <gtkmm.h>

#include <vgd/node/Group.hpp>
#include <vgd/node/VertexShape.hpp>
#include <vgd/node/TriSet.hpp>

#include <vgUI/Canvas.hpp>

//#include <vgGTK/actions/alg/ExportNode.hpp>

#include "vgGTK/graph/icons/expand.xpm"
#include "vgGTK/graph/icons/synchronize.xpm"


namespace vgGTK
{

namespace graph
{

namespace
{
	/**
	 * @brief	Helper that adds some other widgets for decoration arround a given widget.
	 *
	 * @param	widget	a reference to a widget
	 *
	 * @return	a pointer to the decoration widget, that is managed
	 */
	Gtk::Widget * addDecoration( Gtk::Widget & widget )
	{
		Gtk::ScrolledWindow	* scrolled	= Gtk::manage( new Gtk::ScrolledWindow() );
		
		scrolled->add( widget );
		scrolled->set_shadow_type( Gtk::SHADOW_IN );
		scrolled->set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );

		return scrolled;
	}
	
	/**
	 * @brief	Implements a backup of the selection of a Gtk::TreeView.
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
		SelectionBackup( Gtk::TreeView & treeView )
		{
			treeView.get_selection()->selected_foreach_path( sigc::mem_fun(this, &SelectionBackup::storePath) );
		}
		
		/**
		 * @brief	Restores the saved selection to the given tree view
		 */
		void restore( Gtk::TreeView & treeView ) const
		{
			Glib::RefPtr< Gtk::TreeSelection >	selection = treeView.get_selection();
			
			selection->unselect_all();
			for( Strings::const_iterator i = m_selectedPaths.begin(); i != m_selectedPaths.end(); ++i )
			{
				const Gtk::TreeModel::Path	path( *i );
				
//				treeView.expand_to_path( path );
				selection->select( path );
			}
		}
		
	private:
		
		typedef std::vector< Glib::ustring > Strings;
		
		Strings	m_selectedPaths;	///< Holds the back up of selected paths.
		
		/**
		 * @brief	Stores the given path.
		 */
		void storePath( const Gtk::TreeModel::Path & path )
		{
			m_selectedPaths.push_back( path.to_string() );
		}
	};

	/**
	 * @brief	Implements a backup of the expanded rows of a Gtk::TreeView.
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
		ExpandedRowsBackup( Gtk::TreeView & treeView )
		{
			treeView.map_expanded_rows( sigc::mem_fun(this, &ExpandedRowsBackup::storePath) );
		}
		
		/**
		 * @brief	Restores the saved selection to the given tree view
		 */
		void restore( Gtk::TreeView & treeView ) const
		{
			treeView.collapse_all();
			
			for( Strings::const_iterator i = m_expandedPath.begin(); i != m_expandedPath.end(); ++i )
			{
				const Gtk::TreeModel::Path	path( *i );
				
				treeView.expand_to_path( path );
			}
		}
		
	private:
		
		typedef std::vector< Glib::ustring > Strings;
		
		Strings	m_expandedPath;	///< Holds the back up of expanded paths.
		
		/**
		 * @brief	Stores the given path.
		 */
		void storePath( Gtk::TreeView * treeView, const Gtk::TreeModel::Path & path )
		{
			m_expandedPath.push_back( path.to_string() );
		}
	};
}



const Glib::ustring	Browser::m_uiDefinition =
	"<ui>"
	"  <toolbar>"
	"    <toolitem action='FullRefresh'/>"
	"    <toolitem action='ExpandAll'/>"
	"    <separator/>"
	"    <toolitem action='SaveAs'/>"
	"    <toolitem action='ExportScene'/>"
//	"    <separator/>"
//	"    <toolitem action='Synchronize'/>"
	"  </toolbar>"
	"</ui>";



Browser::Browser()
:	m_canvas( 0 ),
	m_actions( Gtk::ActionGroup::create() ),
	m_uiManager( Gtk::UIManager::create() )
{
	// Creates the additionnal icons
	const Gtk::StockID					expandID( Glib::ustring("vgGTK::graph::icons::expand") ); 
	const Gtk::StockID					synchronizeID( Glib::ustring("vgGTK::graph::icons::synchronize") ); 
	Glib::RefPtr< Gtk::IconFactory >	iconFactory = Gtk::IconFactory::create();
	
	iconFactory->add( expandID, Gtk::IconSet(Gdk::Pixbuf::create_from_xpm_data(expand_xpm)) );
	iconFactory->add( synchronizeID, Gtk::IconSet(Gdk::Pixbuf::create_from_xpm_data(synchronize_xpm)) );
	iconFactory->add_default();
	

	// Populates all user interface actions and set it unsensitive.
	m_actions->add( Gtk::Action::create("ExpandAll", expandID), sigc::mem_fun(this, &Browser::onExpandAll) );
	m_actions->add( Gtk::Action::create("FullRefresh", Gtk::Stock::REFRESH), sigc::mem_fun(this, &Browser::onFullRefresh) );
	m_actions->add( Gtk::Action::create("ExportScene", Gtk::Stock::CONVERT), sigc::mem_fun(this, &Browser::onExportScene) );
//	m_actions->add( Gtk::Action::create("Synchronize", synchronizeID), sigc::mem_fun(this, &Browser::onSaveAs) );
	m_actions->set_sensitive( false );


	// Initializes the user interface manager.
	m_uiManager->insert_action_group( m_actions );
	m_uiManager->add_ui_from_string( m_uiDefinition );


	// Retrieves the toolbar and configures it.
	Gtk::Toolbar	* toolbar = dynamic_cast< Gtk::Toolbar * >( Gtk::manage(m_uiManager->get_widget("/toolbar")) );

	toolbar->set_icon_size( Gtk::ICON_SIZE_SMALL_TOOLBAR );
	toolbar->set_toolbar_style( Gtk::TOOLBAR_ICONS );
	toolbar->set_tooltips();
	
	
	// Configures the path label.
	m_path.set_selectable( true );
	m_path.set_alignment( 0, 0 );


	// Builds the widget hieararchy.
	m_vpaned.pack1( *addDecoration(m_treeView) );
	m_vpaned.pack2( *addDecoration(m_editor) );

	this->pack_start( *toolbar, Gtk::PACK_SHRINK, 3 );
	this->pack_start( m_path, Gtk::PACK_SHRINK, 3 );
	this->add( m_vpaned );
	
	
	// Creates the tree store model.
	m_treeStore = Glib::RefPtr< TreeStore >( new TreeStore(m_columns) );


	// Configures the managed tree view to show the model build-up from a vgSDK graph.
	m_treeView.set_enable_tree_lines();
	m_treeView.set_model( m_treeStore );

	m_treeView.append_column( "Name", m_columns.m_nameColumn );
	m_treeView.append_column( "Type", m_columns.m_typeColumn );
	m_treeView.append_column( "Active", m_columns.m_activeColumn );
	m_treeView.append_column( "Shared", m_columns.m_sharedColumn );

	m_treeView.get_column(0)->set_resizable();
	m_treeView.get_column(1)->set_resizable();

	Gtk::TreeViewColumn			* column		= 0;
	Gtk::CellRenderer			* renderer		= 0;
	
	column		= m_treeView.get_column(0);
	renderer	= column->get_first_cell_renderer();
	column->set_cell_data_func( *renderer, sigc::bind< 0 >(sigc::mem_fun(this, &Browser::textCellDataFunc), m_columns.m_nameColumn) );

//	column		= m_treeView.get_column(1);
//	renderer	= column->get_first_cell_renderer();
//	column->set_cell_data_func( *renderer, sigc::bind< 0 >(sigc::mem_fun(this, &Browser::textCellDataFunc), columnRecord.m_typeColumn) );


	// Enable drag&drop on the tree view.
	// We explicitly tell that only moves are possible (no copy).
	//m_treeView.enable_model_drag_source( Gdk::MODIFIER_MASK, Gdk::ACTION_MOVE );
	//m_treeView.enable_model_drag_dest();	


	// Connects several signal handlers on the tree view.
	m_treeView.signal_button_release_event().connect_notify( sigc::mem_fun(this, &Browser::onButtonReleaseEvent) );


	// Connects signal handlers on the tree view's selection
	m_treeView.get_selection()->signal_changed().connect( sigc::mem_fun(this, &Browser::onSelectionChanged) );

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
		case vgAlg::actions::MOVE_PREVIOUS:
			movePrevious();
			break;
		case vgAlg::actions::MOVE_NEXT:
			moveNext();
			break;
		default:
			assert(false && "Action not defined.");
			break;
	}
}



void Browser::setCanvas( vgUI::Canvas * canvas )
{
	m_canvas = canvas;
	m_editor.setCanvas( canvas );

	m_actionsMenu = vgd::makeShp( new vgGTK::node::ActionsMenu( vgGTK::node::TREE ) );
	m_actionsMenu->setCanvas( m_canvas );
}



void Browser::setRoot( vgd::Shp< vgd::node::Group > root )
{
	m_root = root;
	m_treeStore->setRoot( root );
	m_actions->set_sensitive( root != 0 );
}


bool Browser::searchNode( Gtk::TreeModel::Children children, vgd::Shp< vgd::node::Node > node, Gtk::TreeModel::Row *it )
{
	for(Gtk::TreeModel::Children::iterator iter = children.begin(); iter != children.end(); ++iter)
	{
		vgd::Shp< vgd::node::Node >	thisNode = (*iter)[ m_columns.m_nodeColumn ];
		Gtk::TreeModel::Row row = *iter;

		if( node == thisNode )
		{
			*it = *iter;
			return true;
		}

		if (searchNode(row->children(), node, it) )
		{
			return true;
		}
	}
	return false;
}



void Browser::selectNode( vgd::Shp< vgd::node::Node > node )
{	
	Glib::RefPtr< Gtk::TreeSelection >	selection = m_treeView.get_selection();
	if( selection->count_selected_rows() > 0 )
	{
		Gtk::TreeModel::iterator		rowIterator = selection->get_selected();
		vgd::Shp< vgd::node::Node >		selectedNode = (*rowIterator)[ m_columns.m_nodeColumn ];

		if( node == selectedNode )
		{
			return;
		}
	}

	Gtk::TreeModel::Row it;
	if ( searchNode(m_treeStore->children(), node, &it) )
	{
		Gtk::TreePath path( it );
		path.up(); //expand to parent row

		if( !m_treeView.row_expanded( path ) ) //only if parent row is not expanded.
		{
			m_treeView.expand_to_path( path );
		}
		
		m_treeView.scroll_to_row( Gtk::TreePath( it ) );
		selection->select(it);
	}
}



void Browser::movePrevious()
{
	Glib::RefPtr< Gtk::TreeSelection >	selection = m_treeView.get_selection();
	if( selection->count_selected_rows() > 0 )
	{
		Gtk::TreeModel::iterator		rowIterator = selection->get_selected();
		m_treeStore->iter_swap( rowIterator, rowIterator-- );
	}
}



void Browser::moveNext()
{
	Glib::RefPtr< Gtk::TreeSelection >	selection = m_treeView.get_selection();
	if( selection->count_selected_rows() > 0 )
	{
		Gtk::TreeModel::iterator		rowIterator = selection->get_selected();
		m_treeStore->iter_swap( rowIterator, rowIterator++ );
	}
}



void Browser::refreshTree()
{
	onFullRefresh();
}



void Browser::onExpandSubTree()
{
	Glib::RefPtr< Gtk::TreeSelection >	selection = m_treeView.get_selection();
	Gtk::TreeModel::iterator			rowIterator = selection->get_selected();

	if( rowIterator )
	{
		m_treeView.expand_row( m_treeStore->get_path(rowIterator), true );
	}
}



void Browser::onRemoveNode()
{
	//Glib::RefPtr< Gtk::TreeSelection >	selection = m_treeView.get_selection();
	//Gtk::TreeModel::iterator			rowIterator = selection->get_selected();

	//if( rowIterator )
	//{
	//	Gtk::TreePath	rowPath( rowIterator );
	//	
	//	if( rowPath.get_depth() == 1 )
	//	{
	//		Gtk::MessageDialog("You can't remove the root node.").run();
	//	}
	//	else
	//	{
	//		// Asks the user to confirm the node removal.
	//		const Glib::ustring	nodeName = (*rowIterator)[ m_columns.m_nameColumn ];
	//		Gtk::MessageDialog	messageDialog("<big><b>Do you really want to remove the node <i>" + nodeName + "</i> ?</b></big>\n\nThis can break then rendering or may even cause the program to crash.", true, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_YES_NO );
	//		
	//		if( messageDialog.run() == Gtk::RESPONSE_YES )
	//		{
	//			// Moves the path to the parent node.
	//			rowPath.up();
	//			
	//			// Retrieves the parent row iterator, the node to remove and the parent group.
	//			Gtk::TreeModel::iterator		parentRowIterator	= m_treeStore->get_iter( rowPath );
	//			vgd::Shp< vgd::node::Node >		node				= (*rowIterator)[ m_columns.m_nodeColumn ];
	//			vgd::Shp< vgd::node::Node >		parentNode			= (*parentRowIterator)[ m_columns.m_nodeColumn ];
	//			vgd::Shp< vgd::node::Group >	parentGroup			= vgd::dynamic_pointer_cast< vgd::node::Group >( parentNode );
	//			
	//			Gtk::TreePath nextPath( rowIterator );
	//			Gtk::TreePath prevPath( rowIterator );

	//			nextPath.next();
	//			if( m_treeStore->get_iter( nextPath ) )
	//			{
	//				 selection->select( m_treeStore->get_iter( nextPath ) );
	//			}
	//			else if( prevPath.prev() )
	//			{
	//				selection->select( m_treeStore->get_iter( prevPath ) );
	//			}
	//			else
	//			{
	//				selection->select( parentRowIterator );
	//			}

	//			// Removes the node and the row in the tree model.
	//			parentGroup->removeChild( node );
	//			m_treeStore->erase( rowIterator );

	//			m_canvas->refreshForced();
	//			// @todo refresh shared information for remaining rows containing the node being removed.
	//		}
	//	}
	//}
}



void Browser::onExportScene()
{
	vgAssert( false);

/*
	vgGTK::actions::alg::ExportNode exportNode;
	exportNode.setNode( m_canvas->getRoot() );
	exportNode.execute();*/
}



void Browser::onButtonReleaseEvent( GdkEventButton * event )
{
	if( event->button == 3 )
	{
		m_actionsMenu->showPopup(event, vgGTK::node::TREE);
	}
}



void Browser::onExpandAll()
{
	m_treeView.expand_all();
}



void Browser::onFullRefresh()
{
	// Saves selection and expanded rows.
	const SelectionBackup		selectionBackup( m_treeView );
	const ExpandedRowsBackup	expandedRowsBackup( m_treeView );

	// Do the refresh.
	m_editor.setFieldManager( vgd::Shp< vgd::field::FieldManager >() );
	m_treeStore->refresh();

	// Restores the selection and the expanded rows.
	expandedRowsBackup.restore( m_treeView );
	selectionBackup.restore( m_treeView );
}



void Browser::onSelectionChanged()
{
	Glib::RefPtr< Gtk::TreeSelection >	selection = m_treeView.get_selection();
	Gtk::TreeModel::iterator			selected = selection->get_selected();

	if( selected )
	{
		// Retrieves the row that is selected.
		const Gtk::TreeModel::Row	& row = *selected;
		
		// Updates the field manager editor.
		m_editor.setFieldManager( row.get_value(m_columns.m_nodeColumn) );
		
		// Updates the path label.
		Glib::ustring	pathString;
		
		for( Gtk::TreeModel::iterator i = selected; i; i = i->parent() )
		{
			pathString = "/" + i->get_value(m_columns.m_nameColumn) + pathString;
		}
		
		m_path.set_text( pathString );
		m_path.set_has_tooltip( true );
		m_path.set_tooltip_text( pathString );

		//retrieve current node and its parent.
		Gtk::TreePath	rowPath( selected );

		vgd::Shp< vgd::node::Node >		node = (*selected)[ m_columns.m_nodeColumn ];
		vgd::Shp< vgd::node::Group >	parentGroup;
		if( rowPath.get_depth() > 1 )
		{
			// Moves the path to the parent node.
			rowPath.up();

			// Retrieves the parent row iterator, the node to remove and the parent group.
			Gtk::TreeModel::iterator		parentRowIterator	= m_treeStore->get_iter( rowPath );
			vgd::Shp< vgd::node::Node >		parentNode			= (*parentRowIterator)[ m_columns.m_nodeColumn ];
			parentGroup											= vgd::dynamic_pointer_cast< vgd::node::Group >( parentNode );	
		}

		vgAlg::actions::SelectedNode::getSelectedNodeObject()->setSelectedNode( node, parentGroup );
	}
	else
	{
		m_path.set_text( Glib::ustring() );
		m_path.set_has_tooltip( false );
		
		m_editor.clear();
	}
}



void Browser::textCellDataFunc( const Gtk::TreeModelColumn< Glib::ustring > & textColumn, Gtk::CellRenderer * renderer, const Gtk::TreeModel::iterator & i )
{
	const Gtk::TreeModel::Row	& row = *i;
	Gtk::CellRendererText		* textRenderer = dynamic_cast< Gtk::CellRendererText * >( renderer );

	if( textRenderer == 0 )
	{
		// Add some loggin info here !
		return;
	}

	textRenderer->property_text()			= row[ textColumn ];
	textRenderer->property_style()			= row[ m_columns.m_activeColumn ] == true ? Pango::STYLE_NORMAL : Pango::STYLE_ITALIC;
	textRenderer->property_strikethrough()	= row[ m_columns.m_activeColumn ] == false;
}



} // namespace graph

} // namespace vgGTK

