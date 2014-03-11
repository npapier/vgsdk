// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_ACTIONS_ICONS_HPP_
#define _VGGTK_ACTIONS_ICONS_HPP_

#include "vgGTK/vgGTK.hpp"

#include <gtkmm/stock.h>

#include <vgUI/actions/Icons.hpp>

namespace vgGTK
{


namespace actions
{

/**
 * @brief Convert icon to Gtk Stock ID.
 *
 * @param icon	Icon name.
 *
 * @return A Gtk StockID.
 */
Gtk::StockID getIcon( vgUI::actions::Icons icon );


} // namespace actions

} // namespace vgGTK

#endif /*_VGGTK_ACTIONS_ICONS_HPP_*/

