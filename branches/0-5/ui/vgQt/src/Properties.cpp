// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/Properties.hpp"
#include "vgUI/Canvas.hpp"

namespace vgQt
{

Properties::Properties(QWidget* parent)
    : QWidget(parent)
{
    m_engineSettingsEditor = new engine::Settings();
    setLayout(m_engineSettingsEditor);
}

void Properties::setCanvas( vgUI::BasicViewer * canvas )
{
    m_engineSettingsEditor->setCanvas( (vgUI::Canvas*) canvas);
}

} // namespace vgQt


