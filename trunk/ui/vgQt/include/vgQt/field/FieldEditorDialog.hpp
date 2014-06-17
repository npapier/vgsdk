// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_FIELD_FIELDEDITORDIALOG_HPP_
#define _VGQT_FIELD_FIELDEDITORDIALOG_HPP_

#include <QMainWindow>

#include <list>
#include <vgd/Shp.hpp>


namespace vgd {	namespace field { struct FieldManager; } }

namespace vgUI { struct Canvas; }


namespace vgQt
{
namespace field
{


struct FieldEditorDock;

/**
 * @brief	Implements a Qt Dialog that is specilized in editing a given field.
 */
struct FieldEditorDialog : public QMainWindow
{
Q_OBJECT

public:
    /**
     * @brief	Shows a modeless dialog for editing the given fieldmanager's field.
     *
     * @param	parent			a reference to the parent window for the dialog
     * @param	fieldManager	a field manager
     * @param	fieldName		a string containing the name of the field to edit
     * @param	canvas			a pointer to a canvas to refresh on field changes (null by default)
     */
    static void create( QWidget * parent, vgd::Shp< vgd::field::FieldManager > fieldManager, const QString fieldName, QString path, vgUI::Canvas * canvas=0);

    /**
     * @brief	Constructor
     *
     * @param	parent			a parent window for the dialog
     * @param	fieldManager	the field manager owning the field to edit
     * @param	fieldName		the name of the field to edit
     * @param	canvas			a pointer to the canvas to refresh on field changes (null by default)
     * @param   path            the complete path to the field
     */
    FieldEditorDialog( QWidget * parent, vgd::Shp< vgd::field::FieldManager > fieldManager, const QString fieldName, QString path ,vgUI::Canvas * canvas=0);

    /**
     * @brief   Add a field editor to the FieldEditorDialog
     * @param   fieldName       the field name to edit
     */
    void addField(const QString fieldName);

    /**
     * @brief   Handles close button clicks.
     * @param   dialog          the dialog to close.
     */
    static void onClose(FieldEditorDialog* dialog);

private:
    void closeEvent(QCloseEvent *event);

    typedef std::list< FieldEditorDialog * >	DialogContainer;
    static DialogContainer					m_dialogs;          ///< Holds all opened dialogs.
    vgd::Shp< vgd::field::FieldManager >	m_fieldManager;     ///< References the owner of the field to edit.
    QList<QString>                          m_fieldNames;       ///< Holds all names of opened fields.
    vgUI::Canvas*							m_canvas;           ///< Points to a canvas to refresh on field changes.
    QString                                 m_path;             ///< Holds the complete path to the field

public Q_SLOTS:
    void onEditorHidden(FieldEditorDock* editor);               ///< Handles close button click.
    void onTitleChanged(QString);                               ///< Handles title changes
};


} // namespace vgQt
} // namespace field

#endif // _VGQT_FIELD_FIELDEDITORDIALOG_HPP_
