// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/field/FieldEditorDock.hpp"

namespace vgQt
{

namespace field
{

FieldEditorDock::FieldEditorDock(const QString &title, QWidget* parent)
    : QDockWidget(title, parent)
{
    m_fieldName = title;
}

void FieldEditorDock::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    Q_EMIT closed(this);
}

} // field

} // vgQt
