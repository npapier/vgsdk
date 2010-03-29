// VGSDK - Copyright (C) 2009, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/Properties.hpp"

#include <cassert>

#include <gtkmm/adjustment.h>
#include <gtkmm/box.h>
#include <gtkmm/expander.h>
#include <gtkmm/frame.h>
#include <gtkmm/viewport.h>

#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgUI/BasicViewer.hpp>



namespace vgGTK
{

namespace 
{
	Gtk::Widget * createExpander( const Glib::ustring & label, Gtk::Widget * content )
	{
		Gtk::Expander	* expander	= Gtk::manage( new Gtk::Expander(label) );
		Gtk::Frame		* frame		= Gtk::manage( new Gtk::Frame() );

		frame->add( *content );
		frame->set_shadow_type( Gtk::SHADOW_IN );

		expander->add( *frame );
		expander->set_use_markup( true );

		return expander;
	}
}



Properties::Properties()
{
	m_engineSettingsEditor.set_border_width( 5 );
	m_drawStyleEditor.set_border_width( 5 );
	m_lightModelEditor.set_border_width( 5 );

	Gtk::VBox	* box	= Gtk::manage( new Gtk::VBox() );

	box->set_border_width( 3 );
	box->set_spacing( 5 );
	box->pack_start( *createExpander("<b>Draw Style</b>", &m_drawStyleEditor), Gtk::PACK_SHRINK );
	box->pack_start( *createExpander("<b>Light Model</b>", &m_lightModelEditor), Gtk::PACK_SHRINK );
	box->pack_start( *createExpander("<b>Engine Settings</b>", &m_engineSettingsEditor), Gtk::PACK_SHRINK );

	Gtk::Adjustment adj_ref(0,0,0);
	Gtk::Viewport	* viewport = Gtk::manage( new Gtk::Viewport(adj_ref, adj_ref) );

	viewport->add( *box );
	viewport->set_shadow_type( Gtk::SHADOW_NONE );

	set_policy( Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC );
	add( *viewport );
}



void Properties::setCanvas( vgUI::BasicViewer * canvas )
{
	m_engineSettingsEditor.setCanvas( canvas );
	m_drawStyleEditor.setCanvas( canvas );
	m_lightModelEditor.setCanvas( canvas );

	m_drawStyleEditor.setDrawStyle( canvas ? canvas->getOptionalNodeAs< vgd::node::DrawStyle >(vgUI::BasicViewer::DRAW_STYLE) : vgd::Shp< vgd::node::DrawStyle >() );
	m_lightModelEditor.setLightModel( canvas ? canvas->getOptionalNodeAs< vgd::node::LightModel >(vgUI::BasicViewer::LIGHT_MODEL) : vgd::Shp< vgd::node::LightModel >() );
}



} // namespace vgGTK
