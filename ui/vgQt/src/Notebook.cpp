// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/Notebook.hpp"

#include <vgUI/BasicManipulator.hpp>



namespace vgQt
{

Notebook::Notebook(QWidget* parent)
    : QTabWidget(parent),
      m_graphBrowser(new graph::Browser(this)),
      m_properties(new Properties(this))
{
    addTab( m_graphBrowser, "Graph" );
    addTab( m_properties, "Properties" );
}

void Notebook::setCanvas( vgUI::BasicManipulator* canvas )
{
    m_graphBrowser->setCanvas( canvas );
    m_graphBrowser->setRoot( canvas->getRoot() );
    m_properties->setCanvas( canvas );
}

} // namespace vgQt

