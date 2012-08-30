// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_ENGINE_USERSETTINGSDIALOG_HPP_
#define _VGQT_ENGINE_USERSETTINGSDIALOG_HPP_

#include "vgQt/engine/UserSettings.hpp"

#include <QDialog>
#include <QWidget>

#include "vgQt/vgQt.hpp"

namespace vgQt
{

namespace engine
{

/**
 * @brief A dialog containing UserSettings gui
 */
struct VGQT_API UserSettingsDialog : public QDialog
{
	Q_OBJECT

public:

	/**
	 * @brief	Constructor
	 */
	UserSettingsDialog( QWidget* parent, vgd::Shp< vge::engine::UserSettings > settings = vgd::Shp< vge::engine::UserSettings >() );

	/**
	 * @brief	Retrieves the user settings GUI.
	 */
	vgQt::engine::UserSettings* getGUI();


	/**
	 * @brief	Retrieves the user settings.
	 */
	const vgd::Shp< vge::engine::UserSettings > get() const;

	/**
	 * @brief	Assignes the user settings.
	 */
	void set( vgd::Shp< vge::engine::UserSettings > settings );


Q_SIGNALS:
	void changed();	///< Emitted when the user settings have changed

private Q_SLOTS:
	void onSettingsChanged();

private :
	UserSettings* m_userSettingsGUI;
};


} // namespace engine

} // namespace vgQt

#endif // _VGQT_ENGINE_USERSETTINGSDIALOG_HPP_
