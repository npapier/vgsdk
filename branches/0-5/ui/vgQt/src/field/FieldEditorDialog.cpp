// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include <vgUI/Canvas.hpp>

#include "vgQt/graph/convenience.hpp"
#include "vgQt/field/operations.hpp"

#include "vgQt/field/FieldEditorDialog.hpp"

#include <QLabel>

namespace vgQt
{

namespace field
{

FieldEditorDialog::DialogContainer FieldEditorDialog::m_dialogs;


FieldEditorDialog::FieldEditorDialog( QWidget * parent, vgd::Shp< vgd::field::FieldManager > fieldManager, const QString fieldName, QString path, vgUI::Canvas * canvas )
    : QMainWindow( parent ),
      m_fieldManager ( fieldManager ),
      m_path ( path ),
      m_canvas ( canvas )

{
    QString	name = vgUI::graph::getFieldAsString(m_fieldManager, "f_name").c_str();
    setWindowTitle(m_path + "/" + name);

    addField(fieldName);

    show();
}

void FieldEditorDialog::create( QWidget * parent, vgd::Shp< vgd::field::FieldManager > fieldManager, const QString fieldName, QString path, vgUI::Canvas * canvas )
{
    // Searches for a dialog that already exists for the given field manager and field.
    DialogContainer::iterator	found = m_dialogs.end();
    bool alreadyOpened = false;

    for( found = m_dialogs.begin(); found != m_dialogs.end(); ++found )
    {
        FieldEditorDialog	* dialog = *found;

        if( dialog->m_fieldManager == fieldManager)
        {
            Q_FOREACH(QString fieldNameToFind, dialog->m_fieldNames)
            {
                if (fieldNameToFind == fieldName)
                {
                    alreadyOpened = true;
                    break;
                }
            }
            break;
        }
    }

    if (alreadyOpened)  // This field is already opened
    {
        FieldEditorDialog	* dialog = *found;
        dialog->show(); // focus on the good dialog
    }
    else if( found != m_dialogs.end() ) // there is no existing dialog, but there is a dialog opened with the same fieldManager
    {
        FieldEditorDialog	* dialog = *found;
        dialog->activateWindow(); // focus on the good dialog
        dialog->addField(fieldName); // append a row to this dialog
        dialog->show();
    }
    else // Or builds a new dialog and shows it.
    {
        FieldEditorDialog * dialog = new FieldEditorDialog( parent, fieldManager, fieldName, path, canvas );
        m_dialogs.insert( m_dialogs.end(), dialog );
    }
}

void FieldEditorDialog::addField(const QString fieldName)
{
    m_fieldNames.append(fieldName);
    FieldEditorDock *dock = new FieldEditorDock(fieldName, this);
    FieldEditor* editor = createEditor(m_fieldManager, fieldName);
    if (editor)
    {
        editor->initialize((QWidget*)parent(), m_canvas);

        dock->setWidget(editor);
        dock->setAllowedAreas(Qt::AllDockWidgetAreas);

        connect(editor, SIGNAL(titleChanged(QString)), this, SLOT(onTitleChanged(QString)));
    }
    else
    {
        QString	fieldTypeName	= m_fieldManager->getFieldType(fieldName.toStdString()).name();

        QLabel* label = new QLabel(fieldTypeName + " is not supported yet");
        dock->setWidget(label);
    }
    connect(dock, SIGNAL(closed(FieldEditorDock*)), this, SLOT(onEditorHidden(FieldEditorDock*)));
    height() < 500 ? addDockWidget(Qt::LeftDockWidgetArea, dock) : addDockWidget(Qt::RightDockWidgetArea, dock);
}

void FieldEditorDialog::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    onClose(this);
}

void FieldEditorDialog::onEditorHidden(FieldEditorDock* editor)
{
    removeDockWidget(editor);

    m_fieldNames.removeOne(editor->m_fieldName);

    delete editor; // remove the editor in the window

    if(m_fieldNames.size() == 0)
    {
        deleteLater(); // remove the window at the end of this method
    }
}

void FieldEditorDialog::onClose(FieldEditorDialog* dialog)
{
    DialogContainer::iterator	found = std::find( m_dialogs.begin(), m_dialogs.end(), dialog );

    if( found != m_dialogs.end() )
    {
        m_dialogs.erase( found );
        delete dialog;
    }
}

void FieldEditorDialog::onTitleChanged(QString title)
{
    setWindowTitle(m_path + "/" + title);
}

} // namespace vgQt

} // namespace field
