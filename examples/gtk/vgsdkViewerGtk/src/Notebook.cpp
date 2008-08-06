#include "vgsdkViewerGtk/Notebook.hpp"

#include <vgUI/BasicManipulator.hpp>



namespace vgsdkViewerGtk
{



Notebook::Notebook()
{
	m_graphBrowser.set_border_width( 2 );
	m_drawStyleEditor.set_border_width( 8 );
		
	append_page( m_graphBrowser, "Graph" );
	append_page( m_engineSettings, "Engine" );
	append_page( m_drawStyleEditor, "Draw Style" );
}



void Notebook::setCanvas( vgUI::BasicManipulator & canvas )
{
	m_graphBrowser.setRoot( canvas.getRoot() );
	m_engineSettings.setCanvas( &canvas );
	m_drawStyleEditor.setDrawStyle( canvas.getOptionalNodeAs<vgd::node::DrawStyle>(vgUI::BasicManipulator::DRAW_STYLE) );
	m_drawStyleEditor.setCanvas( &canvas );
}



} // namespace vgsdkViewerGtk
