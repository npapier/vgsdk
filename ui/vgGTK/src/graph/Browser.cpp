// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/graph/Browser.hpp"

#include <iostream>
#include <gtkmm/action.h>
#include <gtkmm/cellrenderertext.h>
#include <gtkmm/stock.h>
#include <gtkmm/toolbar.h>


namespace vgGTK
{

namespace graph
{



const Glib::ustring	Browser::m_uiDefinition =
	"<ui>"
	"  <toolbar>"
	"    <toolitem action='FullRefresh'/>"
	"  </toolbar>"
	"  <popup>"
	"    <menuitem action='ExpandAll'/>"
	"  </popup>"
	"</ui>";



Browser::Browser()
:	m_actions( Gtk::ActionGroup::create() ),
	m_uiManager( Gtk::UIManager::create() )
{
	// Populates all user interface actions.
	m_actions->add( Gtk::Action::create("ExpandAll", "Expand All"), sigc::mem_fun(this, &Browser::onExpandAll) );
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
	m_scrolled.add( m_treeView );
	m_scrolled.set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );

	this->pack_start( *toolbar, Gtk::PACK_SHRINK );
	this->add( m_scrolled );


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
	m_treeView.signal_button_press_event().connect_notify( sigc::mem_fun(this, &Browser::onButtonPressEvent) );
	m_treeView.signal_row_collapsed().connect( sigc::mem_fun(this, &Browser::onRowCollapsed) );
	m_treeView.signal_row_expanded().connect( sigc::mem_fun(this, &Browser::onRowExpanded) );
}



void Browser::setRoot( vgd::Shp< vgd::node::Group > root )
{
	m_modelProvider.setRoot( root );
}



void Browser::onButtonPressEvent( GdkEventButton * event )
{
	if( event->button == 3 )
	{
		Gtk::Menu *	popupMenu = dynamic_cast< Gtk::Menu * >( m_uiManager->get_widget("/popup") );

		Gtk::manage( popupMenu );
		popupMenu->popup( event->button, event->time );
	}
}



void Browser::onExpandAll()
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
	// Saves expanded paths before the refresh.
	const StringSet	pathsToExpand = m_expandedPaths;


	// Do the refresh.
	m_expandedPaths.clear();
	m_modelProvider.refresh();


	// Restores old expanded paths.
	StringSet::const_iterator i;
	for( i = pathsToExpand.begin(); i != pathsToExpand.end(); ++i )
	{
		const Gtk::TreeModel::Path	path( *i );

		m_treeView.expand_to_path( path );
	}
}



void Browser::onRowCollapsed( const Gtk::TreeModel::iterator & iter, const Gtk::TreeModel::Path & path )
{
	// Retrieves the string representation of the given path.
	const Glib::ustring	strPath( path.to_string() );


	// Finds expanded sub-paths of the path begin collapsed.
	StringSet					subPaths;
	StringSet::const_iterator	i;
	for( i = m_expandedPaths.begin(); i != m_expandedPaths.end(); ++i )
	{
		const Glib::ustring	strExpandedPath( *i );

		if( strExpandedPath.find(strPath) != Glib::ustring::npos )
		{
			subPaths.insert( strExpandedPath );
		}
	}


	// Removes all expanded sub-paths from the expanded paths.
	for( i = subPaths.begin(); i != subPaths.end(); ++i )
	{
		m_expandedPaths.erase( *i );
	}


	// Removes the collapsed path.
	m_expandedPaths.erase( strPath );
}



void Browser::onRowExpanded( const Gtk::TreeModel::iterator & i, const Gtk::TreeModel::Path & path )
{
	m_expandedPaths.insert( path.to_string() );
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
