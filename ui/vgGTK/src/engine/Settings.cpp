// VGSDK - Copyright (C) 2008, 2009, 2011, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/engine/Settings.hpp"

#include <vector>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/separator.h>
#include <vgd/visitor/helpers.hpp>
#include <vgd/visitor/predicate/True.hpp>
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
	m_disableTexture							= Gtk::manage( new Gtk::CheckButton("Disable texture") );
	m_disableDisplayList						= Gtk::manage( new Gtk::CheckButton("Disable display list") );
	m_disableVBO								= Gtk::manage( new Gtk::CheckButton("Disable VBO") );
	Gtk::Button		* benchButton				= Gtk::manage( new Gtk::Button("Bench") );

	m_showFPS									= Gtk::manage( new Gtk::CheckButton("Show counters (fps and frame)") );
	m_debugEvents								= Gtk::manage( new Gtk::CheckButton("Log events") );
	Gtk::Button		* clearGLResourcesButton	= Gtk::manage( new Gtk::Button("Clear OpenGL Resources") );

	m_captureButton								= Gtk::manage( new Gtk::CheckButton("Enable capture HotKeys") );
	m_captureButton->set_tooltip_text( "Hotkeys\n---------\n\ns : captures a screenshot\n\nv : starts video capture\nb : stops and saves video capture\nc : cancels video capture");

	set_spacing( 8 );

	pack_start( *m_glslButton, Gtk::PACK_SHRINK );
	pack_start( *m_disableTexture, Gtk::PACK_SHRINK );
	pack_start( *m_disableDisplayList, Gtk::PACK_SHRINK );
	pack_start( *m_disableVBO, Gtk::PACK_SHRINK );

	pack_start( *Gtk::manage(new Gtk::HSeparator()), Gtk::PACK_SHRINK );
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
	m_disableDisplayList->signal_clicked().connect( sigc::mem_fun(this, &Settings::onDisableDisplayList ) );
	m_disableVBO->signal_clicked().connect( sigc::mem_fun(this, &Settings::onDisableVBO ) );

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
		m_disableTexture->set_active( !m_canvas->getGLEngine()->isTextureMappingEnabled() );
		m_disableDisplayList->set_active( !m_canvas->getGLEngine()->isDisplayListEnabled() );
		m_disableVBO->set_active( !m_canvas->getGLEngine()->isVertexBufferObjectEnabled() );
		m_showFPS->set_active( m_canvas->isDebugOverlay() );
	}
}



void Settings::onGLSL()
{
	assert( m_canvas != 0 );

	m_canvas->getGLEngine()->setGLSLEnabled( m_glslButton->get_active() );
	m_canvas->refreshForced();
}



void Settings::onDisableTexture()
{
	assert( m_canvas != 0 );
	m_canvas->getGLEngine()->setTextureMappingEnabled( !m_disableTexture->get_active() );

	// @todo a function to dirty all nodeDF
	vgd::Shp< vgd::node::NodeList > nodeList;
	nodeList = vgd::visitor::find( m_canvas->getRoot(), vgd::visitor::predicate::True() );

	using vgd::node::NodeList;

	for( NodeList::const_iterator	i		= nodeList->begin(),
									iEnd	= nodeList->end();
		i != iEnd;
		++i )
	{
		vgd::Shp< vgd::node::Node > node = *i;
		node->getDirtyFlag( node->getDFNode() )->dirty();
	}
	// end todo

	m_canvas->refreshForced();
}



void Settings::onDisableDisplayList()
{
	assert( m_canvas != 0 );

	m_canvas->getGLEngine()->setDisplayListEnabled( !m_disableDisplayList->get_active() );

	typedef vge::visitor::NodeCollectorExtended<> NodeCollectorExtended;
	NodeCollectorExtended nodeCollector;
	m_canvas->getRoot()->traverse( nodeCollector );

	typedef vge::visitor::TraverseElementVector TraverseElementVector;
	TraverseElementVector * traverseElements = nodeCollector.getTraverseElements();

	TraverseElementVector::iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			i != iEnd;
			++i )
	{
		vgd::node::Node * node = i->first;
		node->getDirtyFlag( node->getDFNode() )->dirty();
	}
	/*vgd::Shp< vgd::node::NodeList > nodeList;
	nodeList = vgd::visitor::find( m_canvas->getRoot(), vgd::visitor::predicate::True() );
	using vgd::node::NodeList;

	for( NodeList::const_iterator	i		= nodeList->begin(),
									iEnd	= nodeList->end();
		i != iEnd;
		++i )
	{
		vgd::Shp< vgd::node::Node > node = *i;
		node->getDirtyFlag( node->getDFNode() )->dirty();
	}*/

	m_canvas->refreshForced();
}



void Settings::onDisableVBO()
{
	assert( m_canvas != 0 );

	m_canvas->getGLEngine()->setVertexBufferObjectEnabled( !m_disableVBO->get_active() );
	typedef vge::visitor::NodeCollectorExtended<> NodeCollectorExtended;
	NodeCollectorExtended nodeCollector;
	m_canvas->getRoot()->traverse( nodeCollector );

	typedef vge::visitor::TraverseElementVector TraverseElementVector;
	TraverseElementVector * traverseElements = nodeCollector.getTraverseElements();

	TraverseElementVector::iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			i != iEnd;
			++i )
	{
		vgd::node::Node * node = i->first;
		node->getDirtyFlag( node->getDFNode() )->dirty();
	}
	//
	
	m_canvas->refreshForced();
}



void Settings::onBench()
{
	assert( m_canvas != 0 );

	const int fps = m_canvas->getFPS();

	if ( fps >= 0 )
	{
		m_canvas->refreshForced();
		m_canvas->refreshForced();
		const int paintCount = 5 * 1000 / m_canvas->getFrameTime();
		m_canvas->bench( paintCount );
		m_canvas->refreshForced();
	}
}




void Settings::onShowFPS()
{
	assert( m_canvas != 0 );

	const bool isDebugOverlay = m_showFPS->get_active();
	m_canvas->setDebugOverlay( isDebugOverlay );

	m_canvas->refreshForced();
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

	// @todo
	/* m_canvas->getGLEngine()->getGLManager().clear();
	m_canvas->getGLEngine()->getGLSLManager().clear(); */

	m_canvas->refreshForced();
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
