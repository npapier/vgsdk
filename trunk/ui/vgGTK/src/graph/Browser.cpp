// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/graph/Browser.hpp"

#include <iostream>
#include <gtkmm/action.h>
#include <gtkmm/cellrenderertext.h>
#include <gtkmm/iconfactory.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/stock.h>
#include <gtkmm/toolbar.h>

#include "vgGTK/graph/icons/expand.xpm"


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
	"  </toolbar>"
	"  <popup>"
	"    <menuitem action='ExpandSubTree'/>"
	"  </popup>"
	"</ui>";



Browser::Browser()
:	m_actions( Gtk::ActionGroup::create() ),
	m_uiManager( Gtk::UIManager::create() )
{
	// Creates the additionnal icons
	const Gtk::StockID					expandID( Glib::ustring("vgGTK::graph::icons::expand") ); 
	Glib::RefPtr< Gtk::IconFactory >	iconFactory = Gtk::IconFactory::create();
	
	iconFactory->add( expandID, Gtk::IconSet(Gdk::Pixbuf::create_from_xpm_data(expand_xpm)) );
	iconFactory->add_default();
	
	
	// Populates all user interface actions.
	m_actions->add( Gtk::Action::create("ExpandAll", expandID), sigc::mem_fun(this, &Browser::onExpandAll) );
	m_actions->add( Gtk::Action::create("ExpandSubTree", "Expand"), sigc::mem_fun(this, &Browser::onExpandSubTree) );
	m_actions->add( Gtk::Action::create("FullRefresh", Gtk::Stock::REFRESH), sigc::mem_fun(this, &Browser::onFullRefresh) );


	// Initializes the user interface manager.
	m_uiManager->insert_action_group( m_actions );
	m_uiManager->add_ui_from_string( m_uiDefinition );


	// Retrieves the toolbar and configures it.
	Gtk::Toolbar	* toolbar = dynamic_cast< Gtk::Toolbar * >( Gtk::manage(m_uiManager->get_widget("/toolbar")) );

//	toolbar->set_icon_size( Gtk::ICON_SIZE_SMALL_TOOLBAR );
	toolbar->set_toolbar_style( Gtk::TOOLBAR_ICONS );
	toolbar->set_tooltips();


	// Builds the widget hieararchy.
	m_vpaned.pack1( *addDecoration(m_treeView) );
	m_vpaned.pack2( *addDecoration(m_editor) );

	this->pack_start( *toolbar, Gtk::PACK_SHRINK );
	this->add( m_vpaned );


	// Configures the managed tree view to show the model build-up from a vgSDK graph.
	m_treeView.set_enable_tree_lines();
	m_treeView.set_model( m_modelProvider.getModel() );

	m_treeView.append_column( "Name", m_modelProvider.getColumnRecord().m_nameColumn );
	m_treeView.append_column( "Type", m_modelProvider.getColumnRecord().m_typeColumn );
	m_treeView.append_column( "Active", m_modelProvider.getColumnRecord().m_activeColumn );
	m_treeView.append_column( "Shared", m_modelProvider.getColumnRecord().m_sharedColumn );

	m_treeView.get_column(0)->set_resizable();
	m_treeView.get_column(1)->set_resizable();

	Gtk::TreeViewColumn			* column		= 0;
	Gtk::CellRenderer			* renderer		= 0;
	const TreeModelColumnRecord	& columnRecord	= m_modelProvider.getColumnRecord();

	column		= m_treeView.get_column(0);
	renderer	= column->get_first_cell_renderer();
	column->set_cell_data_func( *renderer, sigc::bind< 0 >(sigc::mem_fun(this, &Browser::textCellDataFunc), columnRecord.m_nameColumn) );

//	column		= m_treeView.get_column(1);
//	renderer	= column->get_first_cell_renderer();
//	column->set_cell_data_func( *renderer, sigc::bind< 0 >(sigc::mem_fun(this, &Browser::textCellDataFunc), columnRecord.m_typeColumn) );


	// Connects several signal handlers on the tree view.
	m_treeView.signal_button_release_event().connect_notify( sigc::mem_fun(this, &Browser::onButtonReleaseEvent) );


	// Connects signal handlers on the tree view's selection
	m_treeView.get_selection()->signal_changed().connect( sigc::mem_fun(this, &Browser::onSelectionChanged) );
}



void Browser::setRoot( vgd::Shp< vgd::node::Group > root )
{
	m_modelProvider.setRoot( root );
}



void Browser::onButtonReleaseEvent( GdkEventButton * event )
{
	if( event->button == 3 )
	{
		// Retrieves the selection and its path.
		Glib::RefPtr< Gtk::TreeSelection >	selection = m_treeView.get_selection();
		Gtk::TreeModel::iterator			rowIterator = selection->get_selected();
		
		if( rowIterator )
		{
			Gtk::Menu *	popupMenu = dynamic_cast< Gtk::Menu * >( m_uiManager->get_widget("/popup") );
	
			Gtk::manage( popupMenu );
			popupMenu->popup( event->button, event->time );			
		}
	}
}



void Browser::onExpandAll()
{
	m_treeView.expand_all();
}



void Browser::onExpandSubTree()
{
	Glib::RefPtr< Gtk::TreeSelection >	selection = m_treeView.get_selection();
	Gtk::TreeModel::iterator			rowIterator = selection->get_selected();

	if( rowIterator )
	{
		m_treeView.expand_row( m_modelProvider.getModel()->get_path(rowIterator), true );
	}
}



void Browser::onFullRefresh()
{
	// Saves selection and expanded rows.
	const SelectionBackup		selectionBackup( m_treeView );
	const ExpandedRowsBackup	expandedRowsBackup( m_treeView );

	// Do the refresh.
	m_modelProvider.refresh();

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
		const Gtk::TreeModel::Row	& row = *selected;

		m_editor.setFieldManager( row.get_value(m_modelProvider.getColumnRecord().m_nodeColumn) );
	}
	else
	{
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
	textRenderer->property_style()			= row[ m_modelProvider.getColumnRecord().m_activeColumn ] == true ? Pango::STYLE_NORMAL : Pango::STYLE_ITALIC;
	textRenderer->property_strikethrough()	= row[ m_modelProvider.getColumnRecord().m_activeColumn ] == false;
}



} // namespace graph

} // namespace vgGTK
