// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGQT_ENGINE_RECORDSETTINGSDIALOG_HPP_
#define _VGQT_ENGINE_RECORDSETTINGSDIALOG_HPP_

#include <QDialog>
#include <QWidget>

#include "vgQt/vgQt.hpp"

namespace vgQt
{

namespace engine
{

struct RecordSettings;

/**
 * @brief A dialog containing RecordSettings gui
 */
struct VGQT_API RecordSettingsDialog : public QDialog
{
Q_OBJECT
public:
	/**
	 * @brief	Constructor
	 */
	RecordSettingsDialog( QWidget* parent );


	/**
	 * @brief	Retrieves the record settings GUI
	 */
	vgQt::engine::RecordSettings* getGUI();


//Q_SIGNALS:
//	void changed();	///< Emitted when the user settings have changed

//private Q_SLOTS:
//	void onSettingsChanged();

private:
	RecordSettings* m_settingsGUI;
};


} // namespace engine

} // namespace vgQt

#endif // _VGQT_ENGINE_RECORDSETTINGSDIALOG_HPP_
