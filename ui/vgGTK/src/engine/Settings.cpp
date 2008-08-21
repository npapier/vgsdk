// VGSDK - Copyright (C) 2008, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/engine/Settings.hpp"

#include <vector>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/separator.h>
#include <vgeGL/engine/Engine.hpp>
#include <vgUI/Canvas.hpp>



namespace vgGTK
{

namespace engine
{



Settings::Settings()
:	m_canvas( 0 )

{
	// Creates child widgets.
	Gtk::CheckButton	* glslButton	= Gtk::manage( new Gtk::CheckButton("Use GLSL pipeline") );
	Gtk::Button			* benchButton	= Gtk::manage( new Gtk::Button("Bench") );
	
	set_spacing( 8 );	
	pack_start( *glslButton, Gtk::PACK_SHRINK );
	pack_start( *Gtk::manage(new Gtk::HSeparator()), Gtk::PACK_SHRINK );
	pack_start( *benchButton, Gtk::PACK_SHRINK );
	
	
	// Connects signal handlers.
	glslButton->signal_clicked().connect( sigc::mem_fun(this, &Settings::onGLSL) );
	benchButton->signal_clicked().connect( sigc::mem_fun(this, &Settings::onBench) );
	
	
	// Refresh child sensitiveness.
	refreshChildrenSensitiveness();
}




void Settings::setCanvas( vgUI::Canvas * canvas )
{
	m_canvas = canvas;
	refreshChildrenSensitiveness();
}



void Settings::onBench()
{
	assert( m_canvas != 0 );
	
	m_canvas->bench(100);
}



void Settings::onGLSL()
{
	assert( m_canvas != 0 );
	
	m_canvas->getGLEngine()->setGLSLEnabled( ! m_canvas->getGLEngine()->isGLSLEnabled() );
	m_canvas->refresh( vgUI::Canvas::REFRESH_FORCE );
}



void Settings::refreshChildrenSensitiveness()
{
	typedef	std::vector< Gtk::Widget * > WidgetContainer;
	
	WidgetContainer	children = get_children();
	
	for( WidgetContainer::iterator i = children.begin(); i != children.end(); ++i )
	{
		Gtk::Widget	* widget = *i;
		
		widget->set_sensitive( m_canvas != 0 );
	}
}




} // namespace engine

} // namespace vgGTK
