// VGSDK - Copyright (C) 2010, 2011, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGGTK_ENGINE_USERSETTINGS_HPP_
#define _VGGTK_ENGINE_USERSETTINGS_HPP_

#include <gtkmm.h>

#include "vgGTK/Container.hpp"

namespace vge { namespace engine { struct UserSettings; } }



namespace vgGTK
{

namespace engine
{



/**
 * @brief	A widget that allows to configure high level settings.
 */
struct VGGTK_API UserSettings : public Gtk::VBox, public vgGTK::ContainerElement
{
	/**
	 * @brief	Constructor
	 */
	UserSettings( vgd::Shp< vge::engine::UserSettings > settings = vgd::Shp< vge::engine::UserSettings >() );



	/**
	 * @brief	Retrieves the user settings.
	 */
	const vgd::Shp< vge::engine::UserSettings > get() const;
	
	/**
	 * @brief	Set the user settings.
	 */
	void set( const vgd::Shp< vge::engine::UserSettings > settings );

	/**
	 * @brief Refreshes the level selection widget.
	 */
	void refreshLevel();

protected:
	virtual vgd::Shp< Gtk::Dialog >			createSelectionDialog(); ///< Creates an empty dialog box, skinned by the application if necessary

private:

	vgd::Shp< vge::engine::UserSettings >	m_settings;			///< The settings to configure.
	Gtk::ComboBoxText						m_levelCombo;		///< The scale use to select a level.
	Gtk::Button								m_selectCard;		///< The button to select a graphic card.
	Gtk::Label								m_description;		///< The label showing the selected level's description.

	/**
	 * @name	Signal Handlers
	 */
	//@{
	void onLevelChanged();		///< Handles level changes.
	void onSelectCardClicked();	///< Handles clicks on the select card button.
	//@}
};



} // namespace engine

} // namespace vgGTK



#endif // _VGGTK_ENGINE_USERSETTINGS_HPP_
