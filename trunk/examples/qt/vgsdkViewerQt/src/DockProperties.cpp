// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgsdkViewerQt/DockProperties.hpp"
#include "vgsdkViewerQt/MyCanvas.hpp"

namespace vgsdkViewerQt
{

DockProperties::DockProperties(QWidget *parent)
    : QDockWidget( "Properties", parent ),
      m_notebook( new vgQt::Notebook(this) )
{
	setObjectName( "vgsdkViewerQt.Properties" );
    setAllowedAreas(Qt::LeftDockWidgetArea);
    setFeatures(QDockWidget::DockWidgetClosable);
    setWidget(m_notebook);
}

void DockProperties::setCanvas( MyCanvas* canvas )
{
    m_notebook->setCanvas( (vgUI::BasicManipulator*) canvas );
}

void DockProperties::hideEvent ( QHideEvent * event )
{
    Q_UNUSED(event);
    Q_EMIT visibilityChanged();
}

void DockProperties::showEvent ( QShowEvent * event )
{
    Q_UNUSED(event);
    Q_EMIT visibilityChanged();
}

}
