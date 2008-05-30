// VGSDK - Copyright (C) 2008, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/engine/Settings.hpp"

#include <vector>
#include <gtkmm/button.h>
#include <vgUI/Canvas.hpp>



namespace vgGTK
{

namespace engine
{



Settings::Settings()
:	m_canvas( 0 )

{
	// Creates child widgets.
	Gtk::Button	* benchButton = Gtk::manage( new Gtk::Button("Bench") );
	
	set_layout( Gtk::BUTTONBOX_START );
	add( *benchButton );
	
	
	// Connects signal handlers.
	benchButton->signal_activate().connect( sigc::mem_fun(this, &Settings::onBench) );
	
	
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
	m_canvas->bench(100);
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
