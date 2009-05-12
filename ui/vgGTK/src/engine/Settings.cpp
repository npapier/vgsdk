// VGSDK - Copyright (C) 2008, 2009, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/engine/Settings.hpp"

#include <vector>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/separator.h>
#include <vgUI/event/CaptureEventProcessor.hpp>
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
	m_glslButton								= Gtk::manage( new Gtk::CheckButton("Use GLSL pipeline") );
	m_disableTexture							= Gtk::manage( new Gtk::CheckButton("Disable texture (todo)") );
	Gtk::Button		* benchButton				= Gtk::manage( new Gtk::Button("Bench") );

	m_showFPS									= Gtk::manage( new Gtk::CheckButton("Show counters (fps and frame)") );
	m_debugEvents								= Gtk::manage( new Gtk::CheckButton("Log events") );
	Gtk::Button		* clearGLResourcesButton	= Gtk::manage( new Gtk::Button("Clear OpenGL Resources") );

	m_captureButton								= Gtk::manage( new Gtk::CheckButton("Enable capture HotKeys") );

	set_spacing( 8 );

	pack_start( *m_glslButton, Gtk::PACK_SHRINK );
	pack_start( *m_disableTexture, Gtk::PACK_SHRINK );
	pack_start( *m_showFPS, Gtk::PACK_SHRINK );
	pack_start( *m_debugEvents, Gtk::PACK_SHRINK );

	pack_start( *Gtk::manage(new Gtk::HSeparator()), Gtk::PACK_SHRINK );
	pack_start( *benchButton, Gtk::PACK_SHRINK );
	pack_start( *clearGLResourcesButton, Gtk::PACK_SHRINK );

	pack_start( *Gtk::manage(new Gtk::HSeparator()), Gtk::PACK_SHRINK );
	pack_start( *m_captureButton, Gtk::PACK_SHRINK );

	// Connects signal handlers.
	m_glslButton->signal_clicked().connect( sigc::mem_fun(this, &Settings::onGLSL) );
	m_disableTexture->signal_clicked().connect( sigc::mem_fun(this, &Settings::onDisableTexture) );

	benchButton->signal_clicked().connect( sigc::mem_fun(this, &Settings::onBench) );

	m_showFPS->signal_clicked().connect( sigc::mem_fun(this, &Settings::onShowFPS) );
	m_debugEvents->signal_clicked().connect( sigc::mem_fun(this, &Settings::onDebugEvents) );
	clearGLResourcesButton->signal_clicked().connect( sigc::mem_fun(this, &Settings::onClearGLResources) );

	m_captureButton->signal_clicked().connect( sigc::mem_fun(this, &Settings::onCaptureButton) );

	// Refresh child sensitiveness.
	refreshChildrenSensitiveness();
}




void Settings::setCanvas( vgUI::Canvas * canvas )
{
	m_canvas = canvas;
	refreshChildrenSensitiveness();

	// Initializes button
	if( m_canvas != 0 )
	{
		m_glslButton->set_active( m_canvas->getGLEngine()->isGLSLEnabled() );
	}
}



void Settings::onGLSL()
{
	assert( m_canvas != 0 );

	m_canvas->getGLEngine()->setGLSLEnabled( m_glslButton->get_active() );
	m_canvas->refresh( vgUI::Canvas::REFRESH_FORCE );
}



void Settings::onDisableTexture()
{
	assert( m_canvas != 0 );

	// @todo
	/*m_canvas->getGLEngine()->setGLSLEnabled( m_glslButton->get_active() );
	m_canvas->refresh( vgUI::Canvas::REFRESH_FORCE );*/
}



void Settings::onBench()
{
	assert( m_canvas != 0 );

	const int fps = m_canvas->getFPS();

	if ( fps >= 0 )
	{
		m_canvas->bench( fps * 2 );
		m_canvas->refresh( vgUI::Canvas::REFRESH_FORCE, vgUI::Canvas::ASYNCHRONOUS );
	}
}




void Settings::onShowFPS()
{
	assert( m_canvas != 0 );

	const bool isDebugOverlay = m_showFPS->get_active();
	m_canvas->setDebugOverlay( isDebugOverlay );

	m_canvas->refresh(); // vgUI::Canvas::REFRESH_FORCE );
}



void Settings::onDebugEvents()
{
	assert( m_canvas != 0 );

	const bool isDebugEvents = m_debugEvents->get_active();

	m_canvas->setDebugEvents( isDebugEvents );
}



void Settings::onClearGLResources()
{
	assert( m_canvas != 0 );
	
	m_canvas->getGLEngine()->getGLManager().clear();
	m_canvas->getGLEngine()->getGLSLManager().clear();
}



void Settings::onCaptureButton()
{
	assert( m_canvas != 0 );

	const bool enableCapture = m_captureButton->get_active();

	using vgUI::event::CaptureEventProcessor;

	if ( enableCapture )
	{
		// Inserts capture event processor
		vgd::Shp< CaptureEventProcessor > captureEventProcessor( new CaptureEventProcessor(m_canvas) );
		m_canvas->insertEventProcessor( captureEventProcessor );
	}
	else
	{
		// Removes capture event processor
		const int index = m_canvas->findEventProcessor< CaptureEventProcessor >();
		if ( index != m_canvas->getNumEventProcessors() )
		{
			// Capture event processor found
			m_canvas->removeEventProcessor( index );
		}
		// else nothing to do
	}
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
