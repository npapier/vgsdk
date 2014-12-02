//// VGSDK - Copyright (C) 2009, 2011, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/event/SlideWindow.hpp"
//
//#include <vgd/event/TimerEvent.hpp>
////#include <glm/glm.hpp>
//
//
//
//namespace vgeGLBase
//{
//
//namespace event
//{
//
//
//
//SlideWindow::SlideWindow( vgeGLBase::engine::SceneManager * sceneManager )
//:	TimerCallback( vgd::makeShp<vgd::node::Node>(0), sceneManager )
//{
//	setTDuration( static_cast<uint>(1000.f * 0.5f) );
//	setTDirection( FORWARD );
//	setTLoopMode( ONCE );
//
//	setExecutionDuration( getTDuration() );
//	setFrequency( 60 );
//}
//
//
//void SlideWindow::reset()
//{
//	m_window.clear();
//}
//
//
//void SlideWindow::add(	vgd::Shp< vgeGLBase::technique::MultiMain::Window > window,
//						const vgm::Rectangle2f	destination,
//						const bool visible )
//{
//	assert( window != 0 && "Null window" );
//
//	const vgm::Rectangle2f sourceRect = window->getGeometry();
//	const vgm::Vec4f source( sourceRect[0], sourceRect[1], sourceRect[2], sourceRect[3] );
//
//	WindowInfo wi;
//	wi.window		= window;
//	wi.destination	= vgm::Vec4f( destination[0], destination[1], destination[2], destination[3] );
//	wi.visible		= visible;
//	wi.source		= source;
//
//	m_window.push_back( wi );
//}
//
//
//
//void SlideWindow::apply( vgd::Shp< vgd::event::TimerEvent > event )
//{
//	// Computes normalized time
//	const float t = getTf();
//
//	// Moves each window
//	for( uint i=0; i < m_window.size(); ++i )
//	{
//		vgm::Vec4f geom(
//			glm::mix( vgm::glm(m_window[i].source), vgm::glm(m_window[i].destination), t )
//				);
//
//		m_window[i].window->setGeometry( 
//			vgm::Rectangle2f( geom[0], geom[1], geom[2], geom[3] ) );
//		m_window[i].window->setVisible( true );
//	}
//
//	// Schedules a refresh
//	event->scheduleRefreshForced();
//}
//
//
//void SlideWindow::endExecution( const vgd::Shp< vgd::event::TimerEvent > event )
//{
//	// Sets each window to its final state
//	for( uint i=0; i < m_window.size(); ++i )
//	{
//		vgm::Rectangle2f geomRECT(
//			m_window[i].destination[0],
//			m_window[i].destination[1],
//			m_window[i].destination[2],
//			m_window[i].destination[3] );
//		m_window[i].window->setGeometry( geomRECT );
//		m_window[i].window->setVisible( m_window[i].visible );
//	}
//
//	// Schedules a refresh
//	event->scheduleRefreshForced();
//}
//
//
//
//} // namespace event
//
//} // namespace vgeGLBase
//