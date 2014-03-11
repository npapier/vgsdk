// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgGTK/ContainerDialog.hpp"

#include "vgGTK/Container.hpp"



namespace vgGTK
{



ContainerDialog::ContainerDialog( Gtk::Window * toplevel, const std::string dialogName, vgd::Shp< vgGTK::Container > container )
:	Gtk::Dialog( dialogName, *toplevel ),
	m_container( container ? container : vgd::makeShp(new vgGTK::Container()) )
{
	m_container->set_border_width( 12 );

	add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK );
	get_vbox()->add( *m_container );
}



vgd::Shp< vgGTK::Container > ContainerDialog::get()
{
	return m_container;
}



} // namespace vgGTK

