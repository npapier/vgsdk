// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/engine/UserSettingsDialog.hpp"

namespace vgQt
{

namespace engine
{


UserSettingsDialog::UserSettingsDialog( QWidget* parent, vgd::Shp< vge::engine::UserSettings > settings )
    : QDialog(parent)
{
    m_userSettingsGUI = new UserSettings( settings );

    setWindowTitle("Render Settings");
    setLayout( m_userSettingsGUI );
	connect( m_userSettingsGUI, SIGNAL(changed()), this, SLOT(onSettingsChanged()) );
}


const vgd::Shp< vge::engine::UserSettings > UserSettingsDialog::get() const
{
    return m_userSettingsGUI->get();
}


void UserSettingsDialog::onSettingsChanged()
{
	Q_EMIT changed();
}


void UserSettingsDialog::set( vgd::Shp< vge::engine::UserSettings > settings )
{
    m_userSettingsGUI->set( settings );
}


} // namespace engine

} // namespace vgQt
