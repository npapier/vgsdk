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
struct UserSettingsDialog : public QDialog
{
    /**
     * @brief	Constructor
     */
    VGQT_API UserSettingsDialog( QWidget* parent, vgd::Shp< vge::engine::UserSettings > settings = vgd::Shp< vge::engine::UserSettings >() );

    /**
     * @brief	Retrieves the user settings.
     */
    VGQT_API const vgd::Shp< vge::engine::UserSettings > UserSettingsDialog::get() const;

    /**
     * @brief	Assignes the user settings.
     */
    VGQT_API void UserSettingsDialog::set( vgd::Shp< vge::engine::UserSettings > settings );


private :
    UserSettings* m_userSettingsGUI;
};

} // namespace engine

} // namespace vgQt

#endif // _VGQT_ENGINE_USERSETTINGSDIALOG_HPP_
