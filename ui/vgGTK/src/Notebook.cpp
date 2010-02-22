// VGSDK - Copyright (C) 2008, 2009, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgGTK/Notebook.hpp"

#include <vgUI/BasicManipulator.hpp>



namespace vgGTK
{



Notebook::Notebook()
{
	m_graphBrowser.set_border_width( 2 );
	m_properties.set_border_width( 2 );

	append_page( m_graphBrowser, "Graph" );
	append_page( m_properties, "Properties" );

	popup_enable();

	set_tab_reorderable( m_graphBrowser );
	set_tab_reorderable( m_properties );
}



// @todo setRoot( for any view in MultiMain)
void Notebook::setCanvas( vgUI::BasicManipulator & canvas )
{
	m_graphBrowser.setCanvas( &canvas );

	m_graphBrowser.setRoot( canvas.getRoot() );

	m_properties.setCanvas( &canvas );
}



} // namespace vgGTK
