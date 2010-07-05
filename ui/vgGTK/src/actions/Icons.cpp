// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/actions/Icons.hpp"


namespace vgGTK
{

namespace actions
{


Gtk::StockID getIcon( vgUI::actions::Icons icon )
{
	switch( icon )
	{
		case vgUI::actions::COPY:
			return Gtk::Stock::COPY;
		case vgUI::actions::CUT:
			return Gtk::Stock::CUT;
		case vgUI::actions::PASTE:
			return Gtk::Stock::PASTE;
		case vgUI::actions::REMOVE:
			return Gtk::Stock::DELETE;
		case vgUI::actions::EXPORT:
			return Gtk::Stock::CONVERT;
		case vgUI::actions::NEXT:
			return Gtk::Stock::GO_FORWARD;
		case vgUI::actions::PREVIOUS:
			return Gtk::Stock::GO_BACK;
		case vgUI::actions::DEFAULT:
			return Gtk::Stock::OK;
		default:
			return Gtk::Stock::OK;
	}
}



} // namespace actions

} // namespace vgGTK
