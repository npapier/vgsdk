// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgUI/Canvas.hpp"

#include <cassert>
#include <iostream>

#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgd/event/Location2Event.hpp>
#include <vgd/event/MouseButtonEvent.hpp>
#include <vgd/event/MouseWheelEvent.hpp>
#include <vgd/event/detail/helpers.hpp>
#include <vgd/visitor/FindFirstHelper.hpp>
#include <vgd/visitor/predicate/ByDirtyFlag.hpp>

#include <vgDebug/Global.hpp>

#include <vgeGL/engine/Engine.hpp>



namespace vgUI
{



void Canvas::setGleLogSystem( const GleLogSystem logger )
{
	m_gleLogSystem = logger;
}



const Canvas::GleLogSystem Canvas::getGleLogSystem()
{
	return m_gleLogSystem;
}



Canvas::Canvas()
:	vgeGL::engine::SceneManager( vgd::Shp< vgeGL::engine::Engine >( new vgeGL::engine::Engine() ) ),
	// m_gleLogSystem
	// m_gleLogFile
	m_gleContext				( getGleOutputStream()	),
	m_sharedCanvas				( 0						),
	m_bLocalInitializedVGSDK	( false					),
	m_debugEvents				( false					)
{
	assert( getCanvasCount() == 0 && "This is not the first canvas." );
	++m_canvasCount;
}



Canvas::Canvas(	const Canvas *sharedCanvas )
:	vgeGL::engine::SceneManager( vgd::Shp< vgeGL::engine::Engine >( new vgeGL::engine::Engine() ) ),
	// m_gleLogSystem
	// m_gleLogFile
	m_gleContext				( getGleOutputStream()	),
	m_sharedCanvas				( sharedCanvas			),
	m_bLocalInitializedVGSDK	( false					),
	m_debugEvents				( false					)
{
	assert( getCanvasCount() >= 1 && "This is the first canvas." );
	++m_canvasCount;
}




Canvas::~Canvas()
{
	assert( m_canvasCount > 0 );

	--m_canvasCount;
}



const bool Canvas::debugEvents() const
{
	return m_debugEvents;
}



void Canvas::setDebugEvents( const bool enable )
{
	m_debugEvents = enable;
}



void Canvas::onEvent( vgd::Shp< vgd::event::Event > event )
{
	vgeGL::engine::SceneManager::onEvent( event );

	if( m_debugEvents )
	{
		using namespace vgd::event;
		using namespace vgd::event::detail;

//		using vgd::event::KeyboardButtonEvent;
//		using vgd::event::MouseButtonEvent;
//		using vgd::event::Location2Event;
//		using vgd::event::MouseWheelEvent;

		const vgd::event::KeyboardButtonEvent * keyboardButtonEvent = dynamic_cast<KeyboardButtonEvent*>(event.get());
		const MouseButtonEvent                * mouseButtonEvent    = dynamic_cast<MouseButtonEvent*>(event.get());
		const Location2Event                  * location2Event      = dynamic_cast<Location2Event*>(event.get());
		const MouseWheelEvent                 * mouseWheelEvent     = dynamic_cast<MouseWheelEvent*>(event.get());

		if( keyboardButtonEvent != 0 )
		{
			vgDebug::get().logDebug(
					"KeyboardButtonEvent (%s, %s)",
					toString( keyboardButtonEvent->getButtonID() ).c_str(),
					toString( keyboardButtonEvent->getState() ).c_str()
				);
		}
		else if( mouseButtonEvent != 0 )
		{
			vgDebug::get().logDebug(
					"MouseButtonEvent (%s,%s)",
					toString( mouseButtonEvent->getButtonID() ).c_str(),
					toString( mouseButtonEvent->getState() ).c_str()
				);
		}
		else if( location2Event != 0 )
		{
			vgDebug::get().logDebug(
					"Location2Event ( previousLocation(%.2f,%.2f), location(%.2f,%.2f), size(%.2f,%.2f)",
					location2Event->getPreviousLocation()[0],
					location2Event->getPreviousLocation()[1],
					location2Event->getLocation()[0],
					location2Event->getLocation()[1],
					location2Event->getSize()[0],
					location2Event->getSize()[1]
				);
		}
		else if( mouseWheelEvent != 0 )
		{
			vgDebug::get().logDebug(
					"MouseWheelEvent (%s, %d)",
					toString( mouseWheelEvent->getAxis() ).c_str(),
					mouseWheelEvent->getDelta()
				);
		}
		else
		{
			vgDebug::get().logDebug("Unknown event");
		}
	}
}



void Canvas::paint( const vgm::Vec2i size, const bool bUpdateBoundingBox )
{
	assert( isCurrent() && "OpenGL context must have been set current." );

	doInitialize();

	while( getNumberOfFrames() > 0 )
	{
		gleGetCurrent()->reportGLErrors();

		::vgeGL::engine::SceneManager::paint( size, getBoundingBoxUpdate() );

		gleGetCurrent()->reportGLErrors();

		// Swap
		swapBuffer();

		setNumberOfFrames( getNumberOfFrames()-1 );
	}

	// Reset the number of frame to render next time to 1.
	setNumberOfFrames( 1 );
}



const uint32 Canvas::getCanvasCount() const
{
	return m_canvasCount;
}



const bool Canvas::isOpenGLObjectsShared() const
{
	return m_sharedCanvas != 0;
}



void Canvas::refresh( const RefreshType type, const WaitType wait )
{
	if ( type == REFRESH_IF_NEEDED )
	{
		// must schedule a refresh of the window ?
		std::pair< bool, vgd::Shp< vgd::node::Node > > retVal;
		retVal = vgd::visitor::findFirst( getRoot(), vgd::visitor::predicate::ByDirtyFlag() );

		if ( retVal.first )
		{
			// refresh must be done.

			// useful for debugging wrong dirty flags
			// vgDebug::get().logDebug("%s\n", retVal.second->getName().c_str() );

			if ( wait == ASYNCHRONOUS )
			{
				sendRefresh();
			}
			else
			{
				doRefresh();
			}
		}
		// else refresh not needed
	}
	else
	{
		if ( wait == ASYNCHRONOUS )
		{
			sendRefresh();
		}
		else
		{
			doRefresh();
		}
	}
}



void Canvas::doInitialize()
{
	// Call method initialize if needed.
	if ( !m_bCallInitialize )
	{
		// First rendering, call initialize().
		gleGetCurrent()->reportGLErrors();

		initialize();

		gleGetCurrent()->reportGLErrors();

		//
		m_bCallInitialize = true;
	}
}



const bool Canvas::startVGSDK()
{
	if ( startOpenGLContext() == false )
	{
		// No current OpenGL context
		vgDebug::get().logWarning("No current OpenGL context.");
		vgDebug::get().logMessage("vgSDK startup aborted...\n");
		return false;
	}

	assert( isCurrent() && "OpenGL context must have been set current." );

	if ( !m_bLocalInitializedVGSDK )
	{
		vgDebug::get().logMessage("Start vgSDK...");

		// Initializes vgeGL
		getGLEngine()->reset();

		// FIXME
		///@todo Remove setToDefaults().
		getGLEngine()->setToDefaults();

		// Theses two lines must go in setToDefaults()
		//vgd::Shp< vge::service::Service > paint = vge::service::Painter::create();
		//m_engine->evaluateTopStateWithoutTrace( paint, true /*isPreTraverse*/ ); //FIXME BUG BECAUSE SEPARATOR is evaluated pre and not post...
		//m_engine->evaluateTopStateWithoutTrace( paint, false /*isPreTraverse*/ ); //FIXME BUG BECAUSE SEPARATOR is evaluated pre and not post...

		//
		m_bLocalInitializedVGSDK = true;

		// Checks OpenGL requirements for vgsdk
		if ( m_gleContext.isGL_VERSION_1_5 == false )
		{
			vgDebug::get().logWarning("You don't have the basic requirements for vgsdk, i.e. at least OpenGL version 1.5.");
//			vgDebug::get().logError("You don't have the basic requirements for vgsdk, i.e. at least OpenGL version 1.5.");
		}
		else if ( m_gleContext.isGL_VERSION_2_0 == false )
		{
			vgDebug::get().logWarning("You don't have the full requirements for vgsdk, i.e. at least OpenGL version 2.0.");
//			vgDebug::get().logWarning("You don't have the full requirements for vgsdk, i.e. at least OpenGL version 2.0.");
		}
		else
		{
			assert( m_gleContext.isGL_VERSION_2_0 );
			vgDebug::get().logMessage("You have the full requirements for vgsdk.");
		}

		vgDebug::get().logDebug("vgSDK startup completed.\n");
	}

	return true;
}



const bool Canvas::shutdownVGSDK()
{
	vgDebug::get().logDebug("Shutdown vgSDK...");

	if ( m_bLocalInitializedVGSDK == false )
	{
		vgDebug::get().logDebug/*logWarning*/("Method shutdownVGSDK() called before startVGSDK() !!!");
		vgDebug::get().logDebug/*logMessage*/("vgSDK shutdown aborted...\n");

		return false;
	}

	if ( startOpenGLContext() == false )
	{
		// No current OpenGL context
		vgDebug::get().logDebug/*logWarning*/("No current OpenGL context.");
		vgDebug::get().logDebug/*logMessage*/("vgSDK shutdown aborted...\n");
		return false;
	}

	// Last canvas is about to be destroy
	if ( m_canvasCount == 1 )
	{
		assert( isCurrent() && "OpenGL context must have been set current. So OpenGL objects could not be released properly." );

		// Try to destroy OpenGL objects
		getGLEngine()->getGLManager().clear();
		//getGLEngine()->getGLSLManager().clear();

		//
		shutdownOpenGLContext();

		vgDebug::get().logDebug("vgSDK shutdown completed.\n");
		return true;
	}
	else
	{
		// Don't destroy OpenGL objects, because they could be shared between OpenGL contexts.
		vgDebug::get().logDebug("vgSDK shutdown completed (delayed to the last canvas).\n");
		return false;
	}
}


uint32 Canvas::m_canvasCount = 0;


Canvas::GleLogSystem Canvas::m_gleLogSystem = GLE_FILE;



std::ofstream Canvas::m_gleLogFile;



std::ostream* Canvas::getGleOutputStream()
{
	const GleLogSystem currentGleLogSystem = getGleLogSystem();

	if ( currentGleLogSystem == GLE_FILE )
	{
		// Opens gle.txt if not already done
		if ( m_gleLogFile.is_open() == false )
		{
			m_gleLogFile.open("gle.txt");
		}

		return &m_gleLogFile;
	}
	else if ( currentGleLogSystem == GLE_COUT )
	{
		return &std::cout;
	}
	else
	{
		assert( false && "vgUI::Canvas: Unsupported gle log system." );
		return &std::cout;
	}
}



} // namespace vgUI
