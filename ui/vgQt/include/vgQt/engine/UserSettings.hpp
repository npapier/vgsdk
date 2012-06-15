// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_ENGINE_USERSETTINGS_HPP_
#define _VGQT_ENGINE_USERSETTINGS_HPP_

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>

#include <vgd/Shp.hpp>
#include <vge/engine/UserSettings.hpp>

#include "vgQt/vgQt.hpp"

namespace vgQt
{

namespace engine
{

/**
 * @brief	A widget that allows to configure high level settings.
 */
struct VGQT_API UserSettings : public QVBoxLayout
{
Q_OBJECT
public:
    /**
     * @brief	Constructor
     */
    UserSettings( vgd::Shp< vge::engine::UserSettings > settings );

    /**
     * @brief	Retrieves the user settings.
     */
    const vgd::Shp< vge::engine::UserSettings > get() const;

    /**
     * @brief	Set the user settings.
     */
    void set( const vgd::Shp< vge::engine::UserSettings > settings );

    /**
     * @brief	Refreshes the level using the user settings.
     */
    void refreshLevel();

public Q_SLOTS:
    void onLevelChanged();
    void onSelectCardClicked();

private :
    vgd::Shp< vge::engine::UserSettings >	m_settings;			///< The settings to configure.
    QLabel*                                 m_description;
    QPushButton*                            m_selectCard;
    QComboBox*                              m_levelCombo;
};

} // namespace engine

} // namespace vgQt

#endif // _VGQT_ENGINE_USERSETTINGS_HPP_
