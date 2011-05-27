// VGSDK - Copyright (C) 2010, 2011, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGGTK_ENGINE_USERSETTINGSDIALOG_HPP_
#define _VGGTK_ENGINE_USERSETTINGSDIALOG_HPP_

#include <gtkmm.h>

#include "vgGTK/engine/UserSettings.hpp"

namespace vge { namespace engine { struct UserSettings; } }



namespace vgGTK
{

namespace engine
{



/**
 * @brief A dialog containing UserSettings gui
 */
struct UserSettingsDialog : public Gtk::Dialog
{
	/**
	 * @brief	Constructor
	 */
	VGGTK_API UserSettingsDialog( Gtk::Window * toplevel, vgd::Shp< vge::engine::UserSettings > settings = vgd::Shp< vge::engine::UserSettings >() );

	/**
	 * @brief	Retrieves the user settings GUI.
	 */
	VGGTK_API vgGTK::engine::UserSettings& getGUI();

	/**
	 * @brief	Retrieves the user settings.
	 */
	VGGTK_API const vgd::Shp< vge::engine::UserSettings > get() const;

	/**
	 * @brief	Assignes the user settings.
	 */
	VGGTK_API void set( vgd::Shp< vge::engine::UserSettings > settings );

private:

	vgGTK::engine::UserSettings		m_userSettingsGUI;
};



} // namespace engine

} // namespace vgGTK



#endif // _VGGTK_ENGINE_USERSETTINGSDIALOG_HPP_
