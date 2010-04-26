// VGSDK - Copyright (C) 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/engine/UserSettingsDialog.hpp"

#include <gtkmm/stock.h>



namespace vgGTK
{

namespace engine
{



UserSettingsDialog::UserSettingsDialog( Gtk::Window * toplevel, vge::engine::UserSettings settings )
:	Gtk::Dialog( "Settings", *toplevel )
{
	m_userSettings.set_border_width( 12 );
	m_userSettings.set( settings );

	add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK );
	add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL );
	get_vbox()->add( m_userSettings );
}



const vge::engine::UserSettings & UserSettingsDialog::get() const
{
	return m_userSettings.get();
}



void UserSettingsDialog::set( vge::engine::UserSettings & settings )
{
	m_userSettings.set( settings );
}



} // namespace engine

} // namespace vgGTK
