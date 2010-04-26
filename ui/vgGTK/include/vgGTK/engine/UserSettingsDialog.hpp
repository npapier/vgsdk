// VGSDK - Copyright (C) 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_ENGINE_USERSETTINGSDIALOG_HPP_
#define _VGGTK_ENGINE_USERSETTINGSDIALOG_HPP_

#include <gtkmm/dialog.h>

#include "vgGTK/vgGTK.hpp"
#include "vgGTK/engine/UserSettings.hpp"

namespace vge {
	namespace engine {
		struct UserSettings;
	}
}



namespace vgGTK
{

namespace engine
{



struct UserSettingsDialog : public Gtk::Dialog
{
	/**
	 * @brief	Constructor
	 */
	VGGTK_API UserSettingsDialog( Gtk::Window * toplevel, vge::engine::UserSettings settings );

	/**
	 * @brief	Retrieves the user settings.
	 */
	VGGTK_API const vge::engine::UserSettings & get() const;

	/**
	 * @brief	Assignes the user settings.
	 */
	VGGTK_API void set( vge::engine::UserSettings & settings );

private:

	UserSettings	m_userSettings;
};



} // namespace engine

} // namespace vgGTK



#endif // _VGGTK_ENGINE_USERSETTINGSDIALOG_HPP_
