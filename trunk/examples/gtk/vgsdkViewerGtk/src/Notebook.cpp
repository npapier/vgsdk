#include "vgsdkViewerGtk/Notebook.hpp"

#include <vgUI/Canvas.hpp>



namespace vgsdkViewerGtk
{



Notebook::Notebook()
{
	m_graphBrowser.set_border_width( 2 );
	
	append_page( m_graphBrowser, "Graph" );
	append_page( m_engineSettings, "Engine" );
}



void Notebook::setCanvas( vgUI::Canvas & canvas )
{
	m_graphBrowser.setRoot( canvas.getRoot() );
	m_engineSettings.setCanvas( &canvas );
}



} // namespace vgsdkViewerGtk
