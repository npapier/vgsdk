// VGSDK - Copyright (C) 2010, 2011, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/engine/UserSettingsDialog.hpp"



namespace vgGTK
{

namespace engine
{



UserSettingsDialog::UserSettingsDialog( Gtk::Window * toplevel, vgd::Shp< vge::engine::UserSettings > settings )
:	Gtk::Dialog( "Render settings", *toplevel ),
	m_userSettingsGUI( settings )
{
	m_userSettingsGUI.set_border_width( 12 );

	//add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK );
	//add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL );

	get_vbox()->add( m_userSettingsGUI );
}



vgGTK::engine::UserSettings& UserSettingsDialog::getGUI()
{
	return m_userSettingsGUI;
}



const vgd::Shp< vge::engine::UserSettings > UserSettingsDialog::get() const
{
	return m_userSettingsGUI.get();
}



void UserSettingsDialog::set( vgd::Shp< vge::engine::UserSettings > settings )
{
	m_userSettingsGUI.set( settings );
}



} // namespace engine

} // namespace vgGTK
