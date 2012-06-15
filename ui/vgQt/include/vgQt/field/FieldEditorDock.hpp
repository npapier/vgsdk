// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_FIELD_FIELDEDITORDOCK_HPP_
#define _VGQT_FIELD_FIELDEDITORDOCK_HPP_

#include <QDockWidget>

namespace vgQt
{

namespace field
{

/**
 * @brief	Implements a dockable widget for the field edition.
 */
struct FieldEditorDock : public QDockWidget
{
Q_OBJECT
public :
    /**
     * @brief	Constructor
     *
     * @param	title			the title displayed.
     * @param	parent      	the parent of the FieldEditorDock.
     */
    FieldEditorDock(const QString &title, QWidget* parent);

    void closeEvent(QCloseEvent *event); ///< Handles when the user closes the widget.
    QString m_fieldName;                 ///< The name of the field to edit.

Q_SIGNALS:
    void closed(FieldEditorDock*);       ///< Signal emited when the widget is closed.
};

} // field

} // vgQt

#endif // _VGQT_FIELD_FIELDEDITORDOCK_HPP_
