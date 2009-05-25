// VGSDK - Copyright (C) 2008, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgsdkViewerGtk/Notebook.hpp"

#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgUI/BasicManipulator.hpp>



namespace vgsdkViewerGtk
{



Notebook::Notebook()
{
	m_graphBrowser.set_border_width( 2 );
	m_engineSettings.set_border_width( 8 );
	m_drawStyleEditor.set_border_width( 8 );
	m_lightModelEditor.set_border_width( 8 );
			
	append_page( m_graphBrowser, "Graph" );
	append_page( m_engineSettings, "Engine" );
	append_page( m_drawStyleEditor, "Draw Style" );
	append_page( m_lightModelEditor, "Light Model" );
}



void Notebook::setCanvas( vgUI::BasicManipulator & canvas )
{
	m_graphBrowser.setCanvas( &canvas );
	m_graphBrowser.setRoot( canvas.getRoot() );
	m_engineSettings.setCanvas( &canvas );
	m_drawStyleEditor.setDrawStyle( canvas.getOptionalNodeAs<vgd::node::DrawStyle>(vgUI::BasicManipulator::DRAW_STYLE) );
	m_drawStyleEditor.setCanvas( &canvas );
	m_lightModelEditor.setLightModel( canvas.getOptionalNodeAs<vgd::node::LightModel>(vgUI::BasicManipulator::LIGHT_MODEL) );
	m_lightModelEditor.setCanvas( &canvas );
}



} // namespace vgsdkViewerGtk
