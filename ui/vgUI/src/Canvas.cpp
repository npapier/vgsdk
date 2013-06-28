// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, 2012, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgUI/Canvas.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>

#include <boost/lexical_cast.hpp>
#include <boost/logic/tribool.hpp>

#include <glo/GLSLProgram.hpp>

#include <sbf/pkg/Module.hpp>

#include <vgCairo/helpers.hpp>
#include <vgCairo/ImageSurface.hpp>
#include <vgd/basic/Image.hpp>
#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgd/event/Location2Event.hpp>
#include <vgd/event/MouseButtonEvent.hpp>
#include <vgd/event/MouseWheelEvent.hpp>
#include <vgd/event/SizeEvent.hpp>
#include <vgd/event/TimerEvent.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#include <vgd/event/detail/helpers.hpp>
#include <vgd/node/MultiSwitch.hpp>
#include <vgd/node/Overlay.hpp>
#include <vgd/visitor/helpers.hpp>
#include <vgDebug/helpers.hpp>
#include <vgeGL/engine/Engine.hpp>



namespace vgUI
{



namespace
{

void logDebugVerticalSynchronizationState( Canvas * canvas )
{
	if ( canvas->isVerticalSynchronizationEnabled() )
	{
		vgLogDebug("Vertical synchronization is enabled");
	}
	else
	{
		vgLogDebug("Vertical synchronization is disabled");
	}
}

}



void Canvas::Screenshot::save( const std::string path, const std::string filename, const bool feedback )
{
	namespace bfs = boost::filesystem;
	assert( bfs::exists( path ) && "Path not found" );

	const std::string lFilename = filename.size() > 0 ?
		filename : buildFilename( "frame" );

	// User feedback
	if ( feedback )
	{
		vgLogDebug( "Screenshot done in file %s", lFilename.c_str() );
		vgLogStatus( "Screenshot done in file %s", lFilename.c_str() );
	}

	// Output image
	const std::string output = (bfs::path(path) / lFilename).string();

	// Removes image if needed
	if ( bfs::exists( output ) )
	{
		bfs::remove( output );
	}

	// Saves image
	getImage()->save( output );
}



const std::string Canvas::Screenshot::buildFilename( const std::string filePrefix )
{
	// Constructs filename

	// FIXME boost::format seems to SEGV with boost 1.38 on win32, so boost lexical cast is used
	//const std::string strCount = (boost::format("%|07|") % getFrameNumber()).str();

	const std::string strFrameCount = boost::lexical_cast< std::string >( getFrameNumber() );
	const std::string strZero( (8 - strFrameCount.size()), '0' );

	const std::string filename = filePrefix + strZero + strFrameCount + ".png";

	return filename;
}



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
	m_gleContext					( getGleOutputStream()			),
	m_sharedCanvas					( 0								),
	m_initialVerticalSynchronization( true							),
	m_scheduleScreenshot			( false							),
	m_videoCapture					( false							),
	m_debugEvents					( false							),
	m_frameBase						( 0								),
	m_frameTime						( -1							),
	// m_timeBase
	m_fps							( -1							)
{
	// Updates the number of canvas
	vgAssertN( getCanvasCount() == 0, "Only the first canvas must be created with this constructor. Uses constructor with the following signature instead Canvas( const Canvas * )." );
	++m_canvasCount;

	// Resets the scene graph
	privateResetSceneGraph();

	// Fps
	// setDebugOverlay( true );
}



Canvas::Canvas( const Canvas *sharedCanvas )
:	vgeGL::engine::SceneManager( vgd::Shp< vgeGL::engine::Engine >( new vgeGL::engine::Engine() ) ),
	// m_gleLogSystem
	// m_gleLogFile
	m_gleContext					( getGleOutputStream()			),
	m_sharedCanvas					( sharedCanvas					),
	m_initialVerticalSynchronization( true							),
	m_scheduleScreenshot			( false							),
	m_videoCapture					( false							),
	m_debugEvents					( false							),
	m_frameBase						( 0								),
	m_frameTime						( -1							),
	// m_timeBase
	m_fps							( -1							)
{
	// Updates the number of canvas
	vgAssertN( getCanvasCount() >= 1, "The first canvas must be created with the following constructor Canvas()." );
	++m_canvasCount;

	// Resets the scene graph
	privateResetSceneGraph();

	// Fps
	// setDebugOverlay( true );
}



void Canvas::resetSceneGraph()
{
	privateResetSceneGraph();
}



void Canvas::privateResetSceneGraph()
{
	// Initializes ROOT node
	vgd::Shp< vgd::node::Group > rootNode = vgd::node::Group::create("ROOT");
	setRoot( rootNode );

	// Debug overlay scene graph
	using vgd::node::Overlay;

	m_debugOverlayContainer	= vgd::node::MultiSwitch::create(	"DEBUG_OVERLAY_CONTAINER"	);
	m_overlayForFPS = Overlay::create( "FPS" );
	m_overlayForFPS->setMultiAttributeIndex(-1);
	m_debugOverlayContainer->addChild( m_overlayForFPS );

	// @todo position and size should be in pixel (LayerPlan must be improved)
	const float width = 0.2f;
	m_overlayForFPS->setPosition( vgm::Vec2f(1.f - width, 0.0f) );
	m_overlayForFPS->setSize( vgm::Vec2f(width, width * 32.f / 128.f) );

	//
	using vgCairo::ImageSurface;
	vgd::Shp< ImageSurface > imageSurface( new ImageSurface(128, 32) );
	m_overlayForFPS->setImage( imageSurface );
}



Canvas::~Canvas()
{
	// Updates the number of canvas
	assert( m_canvasCount > 0 );
	--m_canvasCount;

	gleSetCurrent(0);
}



void Canvas::setInitialVerticalSynchronization( const bool enabled )
{
	m_initialVerticalSynchronization = enabled;
}



const bool Canvas::hasVerticalSynchronizationControl() const
{
	assert( isCurrent() && "OpenGL context not current" );

#ifdef _WIN32
	return isWGL_EXT_swap_control();
#elif __MACOSX__
	#error "Platform not yet supported."
#else
	return isGLX_EXT_swap_control();
#endif
}



void Canvas::setVerticalSynchronization( const bool enabled )
{
	assert( hasVerticalSynchronizationControl() && "Vertical synchronization control is not available" );
	assert( isCurrent() && "OpenGL context not current" );

#ifdef _WIN32
	if ( isWGL_EXT_swap_control() )
	{
		wglSwapIntervalEXT( enabled ? 1 : 0 );
	}
	else
	{
		vgLogDebug("WGL_EXT_swap_control not supported.");
	}
#elif __MACOSX__
	#error "Platform not yet supported."
#else
	if ( isGLX_EXT_swap_control() )
	{
		Display *dpy = glXGetCurrentDisplay();
		GLXDrawable drawable = getXGetCurrentDrawable();
		if ( drawable )
		{
			glXSwapIntervalEXT(dpy, drawable, enabled ? 1 : 0 ); 
		}
		else
		{
			vgLogDebug("Unable to retrieve drawable");
		}
	}
	else
	{
		vgLogDebug("GLX_EXT_swap_control not supported.");
	}
#endif
}



const bool Canvas::isVerticalSynchronizationEnabled() const
{
	assert( hasVerticalSynchronizationControl() && "Vertical synchronization control is not available" );
	assert( isCurrent() && "OpenGL context not current" );

#ifdef _WIN32
	if ( isWGL_EXT_swap_control() )
	{
		const int retVal = wglGetSwapIntervalEXT();
		return (retVal != 0);
	}
	else
	{
		vgLogDebug("WGL_EXT_swap_control not supported.");
		return false;
	}
#elif __MACOSX__
	#error "Platform not yet supported."
#else
	if ( isGLX_EXT_swap_control )
	{
		Display *dpy = glXGetCurrentDisplay();
		GLXDrawable drawable = getXGetCurrentDrawable();
		if ( drawable )
		{
			uint swapInterval;
			glXQueryDrawable( dpy, drawable, GLX_SWAP_INTERVAL_EXT, &swapInterval );
			return (swapInterval != 0);
		}
		else
		{
			vgLogDebug("Unable to retrieve drawable");
			return false;
		}
	}
	else
	{
		vgLogDebug("GLX_EXT_swap_control not supported.");
		return false;
	}
#endif
}



void Canvas::switchFullscreen()
{
	setFullscreen( !isFullscreen() );
}



/**
 * @todo toString( vgd::event::Event)
 */
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
		const TimerEvent                      * timerEvent          = dynamic_cast<TimerEvent*>(event.get());

		if( keyboardButtonEvent != 0 )
		{
			vgLogDebug(
					"KeyboardButtonEvent (%s, %s)",
					toString( keyboardButtonEvent->getButtonID() ).c_str(),
					toString( keyboardButtonEvent->getState() ).c_str()
				);
		}
		else if( mouseButtonEvent != 0 )
		{
			vgLogDebug(
					"MouseButtonEvent (%s,%s)",
					toString( mouseButtonEvent->getButtonID() ).c_str(),
					toString( mouseButtonEvent->getState() ).c_str()
				);
		}
		else if( location2Event != 0 )
		{
			vgLogDebug(
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
			vgLogDebug(
					"MouseWheelEvent (%s, %d)",
					toString( mouseWheelEvent->getAxis() ).c_str(),
					mouseWheelEvent->getDelta()
				);
		}
		else if ( timerEvent != 0 )
		{
			// Skip
		}
		else
		{
			vgLogDebug("Unknown event");
		}
	}
}



// @todo clean this method !!!
void Canvas::paint( const vgm::Vec2i size, const bool bUpdateBoundingBox )
{
	assert( isCurrent() && "OpenGL context must have been set current." );

	doInitialize();

	boost::logic::tribool vsyncState = boost::logic::indeterminate;

	// paint() must do several renderings => This is a bench
	// So, disable V-SYNC
	if ( getNumberOfFrames() > 1 )
	{
		// Saves vsync state
		vsyncState = isVerticalSynchronizationEnabled();

		// Disables vsync
		setVerticalSynchronization( false );
	}

	while( getNumberOfFrames() > 0 )
	{
		gleGetCurrent()->reportGLErrors();

		//
		namespace bpt = boost::posix_time;

		// Initializes attributes used by fps computation
		bpt::ptime beginPaint = bpt::microsec_clock::universal_time();
		if ( m_timeBase.is_not_a_date_time() )
		{
			m_frameBase	= getFrameCount();
			m_timeBase	= beginPaint;
		}

		//bpt::ptime current = bpt::microsec_clock::universal_time();

/*		m_elapsedTimeBetweenPaint = current - m_lastPaint;
		std::cout << "elapsedTimeBetweenPaint:" << m_elapsedTimeBetweenPaint.total_milliseconds() << std::endl;
		m_lastPaint = current;

		//
		bpt::ptime beginPaint = bpt::microsec_clock::universal_time();
*/

		::vgeGL::engine::SceneManager::paint( size, getBoundingBoxUpdate() );

		// Capture screenshot or video
		using vgd::basic::Image;
		vgd::Shp< Image > capturedImage;

		if ( isScreenshotScheduled() )
		{
			// Do the capture
			capturedImage = getGLEngine()->captureGLFramebuffer();

			// Constructs the screenshot and saves the png image
			Screenshot shot( getFrameCount(), capturedImage );

			// Path
			shot.mkdirs( m_screenshotPath );
			if ( m_screenshotFilename.size() > 0 )
			{
				// A filename has been specified
				shot.save( m_screenshotPath, m_screenshotFilename );
			}
			else
			{
				// No filename has been specified, so constructs a filename using 'frame' and frame counter.
				shot.save( m_screenshotPath );
			}

			//
			m_scheduleScreenshot = false;
			m_screenshotFilename.clear();
		}

		if ( isVideoCaptureEnabled() )
		{
			static bpt::ptime lastCapture;
			if ( lastCapture.is_not_a_date_time() )
			{
				lastCapture = bpt::microsec_clock::universal_time();
			}

			const bpt::ptime currentCapture = bpt::microsec_clock::universal_time();

			const bpt::time_duration elapsedTimeBetweenTwoCaptures = currentCapture - lastCapture;

			const float maxNumberOfCapturesPerSecond = 20.f; // @todo parameter
			const float desiredElapsedTimeBetween2Captures = 1000.f / maxNumberOfCapturesPerSecond;
			if ( elapsedTimeBetweenTwoCaptures.total_milliseconds() >= desiredElapsedTimeBetween2Captures  )
			{
				if ( capturedImage == 0 )
				{
					capturedImage = getGLEngine()->captureGLFramebuffer();
				}

				Screenshot screenshot( getFrameCount(), capturedImage );
				m_video.push_back( screenshot );

				lastCapture = currentCapture;
			}
/*			else
			// else save one image on disk
			{
				vgLogDebug("Time to save");
// ???			
			}*/
		}

/*
		//glFlush();
		//glFinish(); 
		{
			std::cout << "Skip\n";
		}
		// else nothing to do 
*/
		gleGetCurrent()->reportGLErrors();

		// Exchanges back and front buffers
		swapBuffer();

		bpt::ptime endPaint = bpt::microsec_clock::universal_time();

		setFrameTime( (endPaint - beginPaint).total_milliseconds() );

		// Computes fps
		bpt::time_duration elapsedTimeBetweenFPSComputation = endPaint - m_timeBase;
		if ( elapsedTimeBetweenFPSComputation.total_milliseconds() > 1000 )
		{
			const uint numberOfFrames = getFrameCount() - m_frameBase;
			setFPS( numberOfFrames * 1000 / (const int)elapsedTimeBetweenFPSComputation.total_milliseconds() );

			// Resets fps attributes
			m_frameBase	= getFrameCount();
			m_timeBase	= endPaint;
		}


/*
		bpt::ptime endPaint = bpt::microsec_clock::universal_time();
		m_paintDuration = endPaint - beginPaint;
		std::cout << "paintDuration:" << m_paintDuration.total_milliseconds() << std::endl;
*/
		setNumberOfFrames( getNumberOfFrames()-1 );
	}

	// Restores previous state of vsync if needed
	if ( !boost::logic::indeterminate(vsyncState) )
	{
		setVerticalSynchronization( vsyncState );
	}

	// Reset the number of frame to render next time to 1.
	setNumberOfFrames( 1 );
}


void Canvas::resize( const vgm::Vec2i size )
{
	vgeGL::engine::SceneManager::resize( size );

	// Forward a resize notification event.
	vgd::Shp< vgd::event::Event >	event( new vgd::event::SizeEvent(this, vgd::event::detail::GlobalButtonStateSet::get(), size) );

	fireEvent( event );
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
		refreshIfNeeded( wait );
	}
	else
	{
		refreshForced( wait );
	}
}



void Canvas::refreshIfNeeded( const WaitType wait )
{
	// Should we refresh the window ?
	using vgd::node::Node;
	vgd::Shp< Node > result = vgd::visitor::findFirstByDirtyFlag< Node >( getRoot() );

	if ( result )
	{
		// Do the refresh

		// Useful for debugging wrong dirty flags
		//vgLogDebug("refreshIfNeeded(): because of node named %s\n", result->getName().c_str() );

		refreshForced( wait );
	}
	// else refresh not needed
}



void Canvas::refreshForced( const WaitType wait )
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



void Canvas::scheduleScreenshot( const std::string filename, boost::shared_ptr< sbf::pkg::Module > module, const std::string subdir )
{
	m_scheduleScreenshot	= true;
	m_screenshotPath		= (module->getPath(sbf::pkg::VarPath) / subdir).string();
	m_screenshotFilename	= filename;
}



const bool Canvas::isScreenshotScheduled() const
{
	return m_scheduleScreenshot;
}



void Canvas::setVideoCapture( const bool isEnabled )
{
	m_videoCapture = isEnabled;
}



const bool Canvas::isVideoCaptureEnabled() const
{
	return m_videoCapture;
}



void Canvas::setDebugOverlay( const bool isEnabled )
{
	using vgd::node::MultiSwitch;
	m_debugOverlayContainer->setWhichChild( isEnabled ? MultiSwitch::MULTI_SWITCH_ALL : MultiSwitch::MULTI_SWITCH_OFF );
}



const bool Canvas::isDebugOverlay() const
{
	using vgd::node::MultiSwitch;

	const bool retVal = m_debugOverlayContainer->getWhichChild() == MultiSwitch::MULTI_SWITCH_ALL;

	return retVal;
}



const bool Canvas::debugEvents() const
{
	return m_debugEvents;
}



void Canvas::setDebugEvents( const bool enable )
{
	m_debugEvents = enable;
}



const int Canvas::getFPS() const
{
	return m_fps;
}



const int Canvas::getFrameTime() const
{
	return m_frameTime;
}


const int Canvas::setFPS( const int newFPS )
{
	m_fps = newFPS;

	return m_fps;
}



void Canvas::setFrameTime( const int newFrameTime )
{
	m_frameTime = newFrameTime;
}


gle::OpenGLExtensionsGen& Canvas::getGleContext()
{
	return m_gleContext;
}



const uint Canvas::increaseFrameCount()
{
	const uint count = vgeGL::engine::SceneManager::increaseFrameCount();

	if ( isDebugOverlay() )
	{
		updateFPSOverlay();
	}

	return count;
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
		vgLogMessage("No current OpenGL context.");
		vgLogMessage("vgSDK startup aborted...\n");
		return false;
	}

	assert( isCurrent() && "OpenGL context must have been set current." );

	using boost::logic::indeterminate;
	if ( indeterminate( hasVGSDK() ) )
	{
		vgLogMessage("Start vgSDK...");

		// Checks OpenGL requirements for vgsdk
		// Two modes :
		// - "compatibility" mode requested by disabling GLSL usage (engine->setGLSLEnabled(false)) => requirements OpenGL >= 2.0
		// - full mode requested by enabled GLSL usage (engine->setGLSLEnabled(false)) => requirements OpenGL >= 3.0).

		//vgLogMessage3("OpenGL %i.%i found", gleGetOpenGLMajorVersion(), gleGetOpenGLMinorVersion() );
		//vgLogMessage3("GLSL %i.%i found", gleGetGLSLMajorVersion(), gleGetGLSLMinorVersion() );
		//vgLogMessage("OpenGL %f found", gleGetOpenGLVersion() );
		//vgLogMessage("GLSL %f found", gleGetGLSLVersion() );

		if ( getGLEngine()->isGLSLEnabled() == false )
		{
			// Checks compatibility mode
			vgLogMessage("Checks OpenGL requirements for vgsdk compatibility mode (i.e. OpenGL version >= 2.0)...");
			vgLogMessage("OpenGL %i.%i found", gleGetOpenGLMajorVersion(), gleGetOpenGLMinorVersion() );
			if ( gleGetOpenGLMajorVersion() >= 2 )
			{
				vgLogMessage("The vgsdk compatibility mode is enabled.");
				m_hasVGSDK = true;
			}
			else
			{
				vgLogMessage("Unable to activate the vgsdk compatibility mode.");
				m_hasVGSDK = false;
				return m_hasVGSDK;
			}
		}
		else
		{
			// Checks full mode
			vgLogMessage("Checks OpenGL requirements for vgsdk (i.e. OpenGL version >= 3.3, GLSL version >= 3.3)...");
			vgLogMessage("OpenGL %i.%i found", gleGetOpenGLMajorVersion(), gleGetOpenGLMinorVersion() );
			vgLogMessage("GLSL %i.%i found", gleGetGLSLMajorVersion(), gleGetGLSLMinorVersion() );

			if (	vgm::greaterThanEqual(gleGetOpenGLVersion(), 3.3f) &&
					vgm::greaterThanEqual(gleGetGLSLVersion(), 3.3f) )
			{
				vgLogMessage("You have the full requirements for vgsdk.");
				m_hasVGSDK = true;
			}
			else
			{
				vgLogMessage("You don't have the full requirements for vgsdk.");
				m_hasVGSDK = false;
				return m_hasVGSDK;
			}
		}

		// Initializes vgeGL
		getGLEngine()->reset();

		// FIXME
		///@todo Remove setToDefaults().
		getGLEngine()->setToDefaults();

		// Theses two lines must go in setToDefaults()
		//vgd::Shp< vge::service::Service > paint = vge::service::Painter::create();
		//m_engine->evaluateTopStateWithoutTrace( paint, true /*isPreTraverse*/ ); //FIXME BUG BECAUSE SEPARATOR is evaluated pre and not post...
		//m_engine->evaluateTopStateWithoutTrace( paint, false /*isPreTraverse*/ ); //FIXME BUG BECAUSE SEPARATOR is evaluated pre and not post...

		// *** Vertical synchronization ***
		if ( hasVerticalSynchronizationControl() )
		{
			// Logs V-Sync state
			logDebugVerticalSynchronizationState( this );

			// Sets initial V-Sync state
			if ( isVerticalSynchronizationEnabled() != m_initialVerticalSynchronization )
			{
				setVerticalSynchronization( m_initialVerticalSynchronization );

				// Success ?
				if ( isVerticalSynchronizationEnabled() == m_initialVerticalSynchronization )
				{
					if ( m_initialVerticalSynchronization )
					{
						vgLogDebug("Enables vertical synchronization");
					}
					else
					{
						vgLogDebug("Disables vertical synchronization");
					}
				}
				else
				{
					vgLogDebug("Unable to modify the vertical synchronization.");
					vgLogDebug("Checks 'Wait for vertical refresh' or something similar in the settings of your graphic card.");
					vgLogDebug("It is certainly set to 'Always off' or 'Always on'");
				}
			}
			// else nothing to do
		}
		else
		{
			vgLogDebug("No control of the vertical synchronization (EXT_swap_control)");
		}

		//
		vgLogMessage("vgSDK startup completed.\n");
	}

	return hasVGSDK();
}



const bool Canvas::shutdownVGSDK()
{
	using boost::logic::indeterminate;

	// Leaves the fullscreen mode.
	if( isFullscreen() )
	{
		vgLogDebug/*logMessage*/("Leaving fullscreen...");
		setFullscreen( false );
	}

	//
	if ( indeterminate(hasVGSDK()) )
	{
		// Nothing to do
		vgLogDebug/*logMessage*/("vgSDK shutdown: nothing to do, because already shutdown or never started.\n");

		return false;
	}
	else if ( !hasVGSDK() )
	{
		// Nothing to do
		shutdownOpenGLContext();

		vgLogDebug/*logMessage*/("vgSDK shutdown: nothing to do, because vgSDK startup failed. Checks OpenGL requirements.\n");

		m_hasVGSDK = boost::logic::indeterminate;
		return false;
	}

	m_hasVGSDK = boost::logic::indeterminate;

	// Do the shutdown
	vgLogDebug/*logMessage*/("Shutdown vgSDK...");

	// Last canvas is about to be destroy
	if ( m_canvasCount == 1 )
	{
		if ( startOpenGLContext() )
		{
			assert( isCurrent() && "OpenGL context must have been set current. So OpenGL objects could not be released properly." );

			// Try to destroy OpenGL objects
			vgLogDebug/*logMessage*/("Releases managed OpenGL objects...\n");

			getGLEngine()->getGLManager().clear();

			::glo::GLSLProgram::useFixedPaths();
			getGLEngine()->getGLSLManager().clear();

			//
			shutdownOpenGLContext();

			vgLogDebug("vgSDK shutdown completed.\n");
			return true;
		}
		else
		{
			// No current OpenGL context
			vgLogDebug/*logWarning*/("No current OpenGL context.");
			vgLogDebug/*logMessage*/("vgSDK shutdown aborted...\n");

			// Try to destroy OpenGL objects
			vgLogDebug/*logMessage*/("Releases managed OpenGL objects (but without a current OpenGL context)...\n");

			getGLEngine()->getGLManager().clear();

			//::glo::GLSLProgram::useFixedPaths();
			getGLEngine()->getGLSLManager().clear();

			//
			shutdownOpenGLContext();

			vgLogDebug("vgSDK shutdown finished, but not completed.\n");
			return false;
		}
	}
	else
	{
		// Don't destroy OpenGL objects, because they could be shared between OpenGL contexts.
		shutdownOpenGLContext();

		vgLogDebug("vgSDK shutdown completed (delayed to the last canvas).\n");
		return false;
	}
}


void Canvas::updateFPSOverlay()
{
	// Updates fps overlay overlay
	using vgCairo::ImageSurface;
	vgd::Shp< ImageSurface > imageSurface = vgd::dynamic_pointer_cast< ImageSurface >( m_overlayForFPS->getImage() );
	assert( imageSurface != 0 && "Internal error." );

	// Draws on image surface with cairo
	cairo_t *			cr		= imageSurface->getContext();

	// Clears image surface with cairo
	cairo_save(cr);
	//cairo_set_source_rgba(cr, 0, 0.1, 0.1, 0.1);
	//cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
	cairo_set_operator(cr, CAIRO_OPERATOR_CLEAR);
	cairo_paint(cr);
	cairo_restore(cr);

	// Draws the capsule background and its boundary
	// @todo do a function in vgCairo
	cairo_save(cr);
	const float margin = 2.f;
	cairo_set_source_rgba( cr, 0.f, 0.f, 0.f, 0.3f );
	vgCairo::rounded_rectangle( cr, 0.5f + margin, 0.5f + margin, 127.5f - 2.f * margin, 31.5f - 2.f * margin, 10 );
	cairo_fill(cr);

	double ux = 1.f, uy = 1.f;
	cairo_device_to_user_distance(cr, &ux, &uy); //if (ux < uy) ux = uy;
	cairo_set_line_width(cr, 2.f * ux);

	cairo_set_source_rgb( cr, 1.f, 1.f, 1.f );
	vgCairo::rounded_rectangle( cr, 0.5f + margin, 0.5f + margin, 127.5f - 2.f * margin, 31.5f - 2.f * margin, 10 );
	cairo_stroke(cr);
	cairo_restore(cr);
	//

	// Draws the text in capsule
	cairo_save(cr);

	cairo_select_font_face( cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD );

	cairo_set_font_size( cr, 18.f );
	cairo_set_source_rgb( cr, 1.f, 1.f, 1.f );
	cairo_move_to( cr, 4.f, 23.f );

	const std::string strFrameCount	= boost::lexical_cast< std::string >( getFrameCount() );
	std::string strFrameTime;
	if ( getFrameTime() >= 0 )
	{
		const std::string strTmp = boost::lexical_cast< std::string >( getFrameTime() );
		const std::string strSpace( std::max(0, 3-(int)strTmp.size()), '0' );
		strFrameTime = strSpace + strTmp;
	}
	else
	{
		strFrameTime = " na";
	}

	std::string strFPS;
	if ( getFPS() >= 0 )
	{
		const std::string strTmp = boost::lexical_cast< std::string >( getFPS() );
		const std::string strSpace( std::max(0, 3-(int)strTmp.size()), '0' );
		strFPS = strSpace + strTmp;
	}
	else
	{
		strFPS = " na";
	}

	cairo_show_text( cr, (strFrameTime + " " + strFPS + " " + strFrameCount).c_str() );

	cairo_restore(cr);

	// Updates the image (invalidates the image).
	m_overlayForFPS->setImage( m_overlayForFPS->getImage() );
}



uint32 Canvas::m_canvasCount = 0;


Canvas::GleLogSystem Canvas::m_gleLogSystem = GLE_FILE_IN_VAR;



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
	else if ( currentGleLogSystem == GLE_FILE_IN_VAR )
	{
		// Opens gle.txt if not already done
		if ( m_gleLogFile.is_open() == false )
		{
			boost::filesystem::path glePath = getGlePath() / "gle.txt";
			m_gleLogFile.open( glePath.string().c_str() );
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


boost::filesystem::path Canvas::getGlePath()
{
	return sbf::pkg::Module::get()->getPathSafe(sbf::pkg::VarPath);
}


} // namespace vgUI
