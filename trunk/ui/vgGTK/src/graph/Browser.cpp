// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/graph/Browser.hpp"

#include <iostream>
#include <gtkmm/cellrenderertext.h>
#include <gtkmm/stock.h>


namespace vgGTK
{

namespace graph
{



Browser::Browser()
:	m_refreshButton( Gtk::Stock::REFRESH )
{
	// Builds the toolbar content
//	m_toolbar.set_icon_size( Gtk::ICON_SIZE_SMALL_TOOLBAR );
	m_toolbar.set_toolbar_style( Gtk::TOOLBAR_ICONS );
	m_toolbar.set_tooltips();
	m_toolbar.append( m_refreshButton, sigc::mem_fun(this, &Browser::onRefresh) );


	// Builds the widget hieararchy.
	m_scrolled.add( m_treeView );
	m_scrolled.set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );

	this->pack_start( m_toolbar, Gtk::PACK_SHRINK );
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
}



void Browser::setRoot( vgd::Shp< vgd::node::Group > root )
{
	m_modelProvider.setRoot( root );
}



void Browser::onRefresh()
{
	m_modelProvider.refresh();
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
