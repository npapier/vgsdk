// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgGTK/Container.hpp"

#include <vgDebug/helpers.hpp>



namespace vgGTK
{



Container::Container()
{
	set_spacing( 12 );
}



void Container::add( vgd::Shp< ContainerElement > element )
{
	// Adds element to container
	Gtk::Widget * widget = dynamic_cast< Gtk::Widget * >( element.get() );

	if ( widget )
	{
		if ( get_children().size() >= 1 )
		{
			pack_start( *Gtk::manage(new Gtk::HSeparator()) );
		}
		pack_start( *widget );
	}
	else
	{
		vgAssertN( false, "Only Gtk::Widget could be added to container" );
	}

	// Connects to signal changed from container element
	element->signalChanged().connect( sigc::mem_fun(this, &Container::onSignalChangedFromContainerElement) );
}



sigc::signal< void > & Container::signalChanged()
{
	return m_signalChanged;
}



void Container::onSignalChangedFromContainerElement()
{
	signalChanged().emit();
}



} // namespace vgGTK
