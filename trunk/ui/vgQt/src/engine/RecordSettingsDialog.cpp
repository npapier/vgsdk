// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgQt/engine/RecordSettingsDialog.hpp"

#include "vgQt/engine/RecordSettings.hpp"



namespace vgQt
{

namespace engine
{


RecordSettingsDialog::RecordSettingsDialog( QWidget* parent )
:	QDialog(parent),
	m_settingsGUI( new RecordSettings() )
{
	setWindowTitle("Recording settings");
	setLayout( m_settingsGUI );
	//connect( m_settings, SIGNAL(changed()), this, SLOT(onSettingsChanged()) );
}


vgQt::engine::RecordSettings* RecordSettingsDialog::getGUI()
{
	return m_settingsGUI;
}


/*void RecordSettingsDialog::onSettingsChanged(
{
	Q_EMIT changed();
}*/


} // namespace engine

} // namespace vgQt
