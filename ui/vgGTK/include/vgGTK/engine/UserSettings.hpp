// VGSDK - Copyright (C) 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_ENGINE_USERSETTINGS_HPP_
#define _VGGTK_ENGINE_USERSETTINGS_HPP_

#include <gtkmm/box.h>
#include <gtkmm/comboboxtext.h>

#include <sigc++/connection.h>

#include <vge/engine/UserSettings.hpp>

#include "vgGTK/vgGTK.hpp"


namespace vgGTK
{

namespace engine
{



/**
 * @brief	A widget that allows to configure high level settings.
 */
struct VGGTK_API UserSettings : public Gtk::VBox
{
	/**
	 * @brief	Constructor
	 */
	UserSettings();

	/**
	 * @brief	Retrieves the user settings.
	 */
	const vge::engine::UserSettings & get() const;
	
	/**
	 * @brief	Set the user settings.
	 */
	void set( const vge::engine::UserSettings & );

private:

	vge::engine::UserSettings	m_settings;		///< The settings to configure.
	Gtk::ComboBoxText			m_levelCombo;	///< The scale use to select a level.
	Gtk::ComboBoxText			m_cardCombo;	///< The combo box use to select a graphic card.

	/**
	 * @name	Signal connections
	 */
	//@{
	sigc::connection	m_cardChangedConnection;
	sigc::connection	m_levelChangedConnection;
	//@}

	/**
	 * @name	Signal Handlers
	 */
	//@{
	void onCardChanged();	///< Handles card changes.
	void onLevelChanged();	///< Handles level changes.
	//@}

	/**
	 * @name	Helpers
	 */
	//@{
	void refreshCard();		///< Refreshes the card selection widget.
	void refreshLevel();	///< Refreshes the level selection widget.
	//@}
};



} // namespace engine

} // namespace vgGTK



#endif // _VGGTK_ENGINE_USERSETTINGS_HPP_
