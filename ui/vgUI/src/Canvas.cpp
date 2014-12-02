// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, 2012, 2013, 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgUI/Canvas.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <locale>
#include <sstream>

#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/logic/tribool.hpp>

#ifdef __USE_DDC__
#include <displayDriverConnector/displayDriverConnector.hpp>
#endif

#ifdef __USE_GLE__
#include <gle/gl.h>
#include <gle/OpenGLExtensionsGen.hpp>
#include <gle/WrapperGLXGen.hpp>
#endif

#include <glo/GLSLProgram.hpp>

#include <sbf/pkg/Module.hpp>

#ifdef __USE_VGCAIRO__
#include <vgCairo/helpers.hpp>
#include <vgCairo/ImageSurface.hpp>
#endif

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
#include <vgeGLBase/engine/Engine.hpp>

#include "vgUI/Screenshot.hpp"



namespace vgUI
{



namespace
{

static uint32					m_canvasCount	= 0;						///< Instance count of this class.

#ifdef __USE_GLE__
static Canvas::GleLogSystem		m_gleLogSystem	= Canvas::GLE_FILE_IN_VAR;	///< A value from GleLogSystem enumeration to specify the log system used by gle library.
static std::ofstream			m_gleLogFile;								///< The gle.txt file
#endif


void logDebugVerticalSynchronizationState( Canvas * canvas )
{
	const Canvas::SwapControlMode mode = canvas->getVerticalSynchronization();

	switch ( mode )
	{
		case Canvas::NO_VSYNC:
			vgLogDebug("Vertical synchronization is disabled");
			break;

		case Canvas::VSYNC:
			vgLogDebug("Vertical synchronization is enabled");
			break;

		case Canvas::ADAPTIVE_VSYNC:
			vgLogDebug("Adaptive synchronization is enabled");
			break;

		default:
			vgAssert( false );
	}
}

}


#ifdef __USE_GLE__
void Canvas::setGleLogSystem( const GleLogSystem logger )
{
	m_gleLogSystem = logger;
}



const Canvas::GleLogSystem Canvas::getGleLogSystem()
{
	return m_gleLogSystem;
}
#endif


Canvas::Canvas( const Canvas * sharedCanvas, const bool newOpenGLContextSharingObjects )
:	vgeGLBase::engine::SceneManager( sharedCanvas ?
		vgd::makeShp(new vgeGLBase::engine::Engine(sharedCanvas->getGLEngine().get())) :
		vgd::makeShp(new vgeGLBase::engine::Engine())
		),
	m_sharedCanvas					( sharedCanvas															),
	//m_drawable						( 0																	),
	m_glc							( 0																		),
#ifdef __USE_GLE__
	m_gleContext					( sharedCanvas ?
		sharedCanvas->m_gleContext : vgd::makeShp( new gle::OpenGLExtensionsGen(getGleOutputStream()) )		),
#endif
	m_initialVerticalSynchronization( ADAPTIVE_VSYNC														),
	m_scheduleScreenshot			( false																	),
	m_scheduleVideoCapture			( false																	),
	m_videoCapture					( false																	),
	m_video							( new ScreenshotContainer()												),
	//m_whats
	m_maxNumberOfCapturesPerSecond	( 25																	),
	m_debugEvents					( false																	),
	m_frameBase						( 0																		),
	// m_timeBase
	m_frameTime						( -1																	),
	m_fps							( -1																	)
{
	vgAssertN( newOpenGLContextSharingObjects == false, "newOpenGLContextSharingObjects not yet supported" );

	// Updates the number of canvas
	++m_canvasCount;

	// Resets the scene graph
	privateResetSceneGraph();
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

#ifdef __USE_VGCAIRO__
	//
	using vgCairo::ImageSurface;
	vgd::Shp< ImageSurface > imageSurface( new ImageSurface(128, 32) );
	m_overlayForFPS->setImage( imageSurface );
#endif
}



Canvas::~Canvas()
{
	// Updates the number of canvas
	vgAssert( m_canvasCount > 0 );
	--m_canvasCount;

	uninitDevices();
	shutdownOpenGLContext();
}



const bool Canvas::setCurrent()
{
	// glc is made current
	const bool retVal = (m_glc != 0) ? (glc_set_current( glc() ) != 0) : false;
	if ( retVal == false )
	{
		vgLogDebug("glc_set_current returns false");
	}

#ifdef __USE_GLE__
	// gle must be made current
	if ( retVal )
	{
		// glc context has been made current. gle must be current too.
		if ( gleGetCurrent() != getGleContext() )
		{
			gleSetCurrent( getGleContext() );
		}
		//else nothing to do (already current)
	}
	else
	{
		// gle must be not current.
		gleSetCurrent( 0 );
	}
#endif

	return retVal;
}


//#define USE_GDEBUGGER
const bool Canvas::unsetCurrent()
{
	// normal code path
	const bool retVal = (m_glc != 0) ? (glc_unset_current( glc() ) != 0) : false;
#ifdef __USE_GLE__
	gleSetCurrent( 0 );
#endif
	return retVal;
}


const bool Canvas::isCurrent() const
{
	if ( m_glc != 0 )
	{
		return glc_is_current( glc() ) != 0;
	}
	else
	{
		return false;
	}
}


void Canvas::swapBuffer()
{
	if ( m_glc != 0 )
	{
		glc_swap( glc() );
	}
	else
	{
		vgLogDebug("vgQt::Canvas::swapBuffer called without a glc context.");
	}
}


const bool Canvas::setFullscreen( const bool wantFullscreen )
{
	if ( wantFullscreen == isFullscreen() )
	{
		// Nothing to do
		return true;
	}

	// Updates the current state.
	if ( m_glc )
	{
		return glc_drawable_set_fullscreen( glc(), wantFullscreen, false /*no action on compositing window manager*/) != 0;
	}
	else
	{
		return false;
	}
}


const bool Canvas::isFullscreen()
{
	if ( m_glc )
	{
		return glc_drawable_is_fullscreen( glc() ) != 0;
	}
	else
	{
		return false;
	}
}


void Canvas::setInitialVerticalSynchronization( const SwapControlMode mode )
{
	m_initialVerticalSynchronization = mode;
}



const bool Canvas::hasVerticalSynchronizationControl() const
{
	vgAssertN( isCurrent(), "OpenGL context not current" );
#ifdef __USE_GLE__
	#ifdef _WIN32
		return isWGL_EXT_swap_control();
	#elif __MACOSX__
		#error "Platform not yet supported."
	#else
		return isGLX_EXT_swap_control();
	#endif
#else
	#pragma message ("Canvas::hasVerticalSynchronizationControl(): not supported")
	vgAssertN(false, "Canvas::hasVerticalSynchronizationControl() : not supported");
	return false;
#endif
}



const bool Canvas::hasAdaptiveVerticalSynchronizationControl() const
{
	vgAssertN( isCurrent(), "OpenGL context not current" );
#ifdef __USE_GLE__
	#ifdef _WIN32
		return isWGL_EXT_swap_control_tear();
	#elif __MACOSX__
		#error "Platform not yet supported."
	#else
		return isGLX_EXT_swap_control_tear();
	#endif
#else
	#pragma message ("Canvas::hasAdaptiveVerticalSynchronizationControl(): not supported")
	vgAssertN(false, "Canvas::hasAdaptiveVerticalSynchronizationControl() : not supported");
	return false;
#endif
}



void Canvas::setVerticalSynchronization( const SwapControlMode mode )
{
	vgAssertN( isCurrent(), "OpenGL context not current" );
#ifdef __USE_GLE__
	#ifdef _WIN32
		if ( isWGL_EXT_swap_control() )
		{
			if ( isWGL_EXT_swap_control_tear() )
			{
				wglSwapIntervalEXT( mode );
			}
			else
			{
				vgLogDebug("WGL_EXT_swap_control_tear not supported.");
				wglSwapIntervalEXT( (mode == ADAPTIVE_VSYNC) ? VSYNC : mode );
			}
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
			GLXDrawable drawable = glXGetCurrentDrawable();
			if ( drawable )
			{
				if ( isGLX_EXT_swap_control_tear() )
				{
					glXSwapIntervalEXT(dpy, drawable, mode ); 
				}
				else
				{
					vgLogDebug("GLX_EXT_swap_control_tear not supported.");
					glXSwapIntervalEXT( dpy, drawable, (mode == ADAPTIVE_VSYNC) ? VSYNC : mode );
				}
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
#else
	#pragma message ("Canvas::setVerticalSynchronization(): not supported")
	vgAssertN(false, "Canvas::setVerticalSynchronization() : not supported");
	return false;
#endif
}



const Canvas::SwapControlMode Canvas::getVerticalSynchronization() const
{
	vgAssertN( isCurrent(), "OpenGL context not current" );
#ifdef __USE_GLE__
	#ifdef _WIN32
		if ( isWGL_EXT_swap_control() )
		{
			const int retVal = wglGetSwapIntervalEXT();
			return static_cast<SwapControlMode>(retVal);
		}
		else
		{
			vgLogDebug("WGL_EXT_swap_control not supported.");
			return VSYNC;
		}
	#elif __MACOSX__
		#error "Platform not yet supported."
	#else
		if ( isGLX_EXT_swap_control() )
		{
			Display *dpy = glXGetCurrentDisplay();
			GLXDrawable drawable = glXGetCurrentDrawable();
			if ( drawable )
			{
				uint swapInterval;
				glXQueryDrawable( dpy, drawable, GLX_SWAP_INTERVAL_EXT, &swapInterval );
				return static_cast<SwapControlMode>(swapInterval);
			}
			else
			{
				vgLogDebug("Unable to retrieve drawable");
				return VSYNC;
			}
		}
		else
		{
			vgLogDebug("GLX_EXT_swap_control not supported.");
			return VSYNC;
		}
	#endif
#else
	#pragma message ("Canvas::getVerticalSynchronization(): not supported")
	vgAssertN(false, "Canvas::getVerticalSynchronization() : not supported");
	return false;
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
	vgeGLBase::engine::SceneManager::onEvent( event );

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
			vgLogMessage(
					"KeyboardButtonEvent (%s, %s)",
					toString( keyboardButtonEvent->getButtonID() ).c_str(),
					toString( keyboardButtonEvent->getState() ).c_str()
				);
		}
		else if( mouseButtonEvent != 0 )
		{
			vgLogMessage(
					"MouseButtonEvent (%s,%s)",
					toString( mouseButtonEvent->getButtonID() ).c_str(),
					toString( mouseButtonEvent->getState() ).c_str()
				);
		}
		else if( location2Event != 0 )
		{
			vgLogMessage(
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
			vgLogMessage(
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
			vgLogMessage("Unknown event");
		}
	}
}



void Canvas::paint( const vgm::Vec2i& size, const bool bUpdateBoundingBox )
{
	vgAssertN( isCurrent(), "OpenGL context must have been set current." );

	doInitialize();

	//
	bool hasVSyncState = false;
	SwapControlMode vsyncState;

	// paint() must do several renderings => This is a bench
	// So, disable V-SYNC
	if ( getNumberOfFrames() > 1 )
	{
		// Saves vsync state
		vsyncState = getVerticalSynchronization();
		hasVSyncState = true;

		// Disables vsync
		setVerticalSynchronization( NO_VSYNC );
	}

	while( getNumberOfFrames() > 0 )
	{
		namespace bpt = boost::posix_time;

		// Initializes attributes used by fps computation
		bpt::ptime beginPaint = bpt::microsec_clock::universal_time();
		if ( m_timeBase.is_not_a_date_time() )
		{
			m_frameBase	= getFrameCount();
			m_timeBase	= beginPaint;
		}

		::vgeGLBase::engine::SceneManager::paint( size, getBoundingBoxUpdate() );

		// Capture screenshot or video
		using vgd::basic::Image;

		// SCREENSHOT
		if ( isScreenshotScheduled() )
		{
			// Do the capture
			vgd::Shp< Image > capturedImage = getGLEngine()->captureGLFramebuffer();

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

		// VIDEO
		if ( m_scheduleVideoCapture )
		{
			startVideoCapture();
			m_scheduleVideoCapture = false;
		}

		//
		if ( isVideoCaptureEnabled() )
		{
			static bpt::ptime lastCapture;
			if ( lastCapture.is_not_a_date_time() )
			{
				lastCapture = bpt::microsec_clock::universal_time() - bpt::seconds(1);
			}

			const bpt::ptime			currentCapture = bpt::microsec_clock::universal_time();
			const bpt::time_duration	elapsedTimeBetweenTwoCaptures = currentCapture - lastCapture;

			const float desiredElapsedTimeBetween2Captures = 1000.f / m_maxNumberOfCapturesPerSecond;
			if ( elapsedTimeBetweenTwoCaptures.total_milliseconds() >= desiredElapsedTimeBetween2Captures  )
			{
				// Do the capture
				if ( m_video->sizeBuffering() > 0 )
				{
					// recycles a screenshot
					vgd::Shp< Screenshot > recycledShot = m_video->popBuffering();

					//	updates image(s)
					for( uint i=0; i != m_whats.size(); ++i )
					{
						const uint what = m_whats[i];

						vgd::Shp< vgd::basic::Image >& capturedImage = recycledShot->getImage( what );
						void *& captureImageData = recycledShot->getImageData( what );

						// captures using a recycled image
						using vgeGLBase::engine::Engine;
						getGLEngine()->captureGLFramebuffer( static_cast<Engine::CaptureBufferType>(what), capturedImage, captureImageData );
					}

					//	updates frame count
					recycledShot->setFrameNumber( getFrameCount() );

					//	updates camera informations
					const vgm::Vec2f nearFar			= getGLEngine()->getNearFar();

					const vgm::Rectangle2i viewport2i	= getGLEngine()->getViewport();
					const vgm::Vec4i viewport( viewport2i.x(), viewport2i.y(), viewport2i.width(), viewport2i.height() );
					const vgm::MatrixR& modelview		= getGLEngine()->getSceneGeometricalMatrix();
					const vgm::MatrixR& projection		= getGLEngine()->getCamera()->getProjectionLeft();
					recycledShot->setCameraInformations( nearFar, viewport, modelview, projection );

					//
					m_video->push( recycledShot );
				}
				else
				{
					// buffer is empty. unable to recycle a screenshot.
					vgLogMessage("Skip capturing frame %i. Waiting thread to serialize a screenshot (next frame ?).", getFrameCount() );
				}

				lastCapture = currentCapture;
			}
			// else nothing to do
		}

		// Exchanges back and front buffers
		swapBuffer();

		bpt::ptime endPaint = bpt::microsec_clock::universal_time();

		setFrameTime( static_cast<int>( (endPaint - beginPaint).total_milliseconds()) );

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

		setNumberOfFrames( getNumberOfFrames()-1 );
	}

	// Restores previous state of vsync if needed
	if ( hasVSyncState )
	{
		setVerticalSynchronization( vsyncState );
	}

	// Reset the number of frame to render next time to 1.
	setNumberOfFrames( 1 );
}


void Canvas::resize( const vgm::Vec2i& size )
{
	vgeGLBase::engine::SceneManager::resize( size );

	// Forward a resize notification event.
	vgd::Shp< vgd::event::Event > event( new vgd::event::SizeEvent(this, vgd::event::detail::GlobalButtonStateSet::get(), size) );

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
		//vgLogMessage("refreshIfNeeded(): because of node named %s\n", result->getName().c_str() );

		refreshForced( wait );
	}
	// else refresh not needed
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



void Canvas::setVideoCapture( const bool isEnabled, const std::string directoryNameFormat )
{
	if ( isEnabled )
	{
		// request the start of video capture (startVideoCapture() have to be called in paint() for Engine.getOutputBuffers())
		if ( !m_videoCapture ) // capture video is not currently done
		{
			m_scheduleVideoCapture				= isEnabled;
			m_videoCaptureDirectoryNameFormat	= directoryNameFormat;
		}
		// else nothing to do
	}
	else
	{
		// request the stop of video capture
		stopVideoCapture();
	}
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




#ifdef __USE_GLE__
gle::OpenGLExtensionsGen * Canvas::getGleContext()
{
	return m_gleContext ? m_gleContext.get() : 0;
}
#endif


const uint Canvas::increaseFrameCount()
{
	const uint count = vgeGLBase::engine::SceneManager::increaseFrameCount();

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
		initialize();

		m_bCallInitialize = true;
	}
}



const bool Canvas::startOpenGLContext()
{
	// Tests if glc context is already created
	if ( m_glc == 0 )
	{
		// glc context is not already created, creates a new one

		// First creates the drawable from the canvas
		glc_drawable_t * drawable = createDrawable();
		//m_drawable = drawable;
		if ( drawable == 0 )
		{
			vgLogWarning("Unable to create the drawable.");
			return false;
		}

		// Sets the desired property for the context
		const vgeGLBase::engine::GLContextProperties& requestedProperties = m_requestedGLContextProperties;
		glc_drawable_set_stereo( drawable, requestedProperties.enableQuadBufferStereo() );

		// Next, creates the glc context (shared or not)
		if ( m_sharedCanvas )
		{
			// Create a new glc sharing the given OpenGL rendering context
			m_glc = glc_create( drawable, m_sharedCanvas->glc() );
		}
		else
		{
			m_glc = glc_create( drawable );
		}

		if ( m_glc == 0 )
		{
			destroyDrawable( drawable );
			//m_drawable = 0;
			vgLogWarning("Unable to create the glc context.");
			return false;
		}

		vgLogMessage("glc context successfully created.");

		// Next, mades the glc context current
		const bool isGLCCurrent = setCurrent();
		if ( !isGLCCurrent )
		{
			vgLogWarning( "Unable to set glc context current. This is not expected !!!" );
			return false;
		}

		vgLogMessage("glc context made current.");

		// Analyses current OpenGL context
		GLboolean glbool;
		glGetBooleanv( GL_STEREO, &glbool );
		if ( glbool )
		{
			vgLogMessage("OpenGL context with stereo support");
			m_currentGLContextProperties = vgeGLBase::engine::GLContextProperties(true);
		}
		else
		{
			m_currentGLContextProperties = vgeGLBase::engine::GLContextProperties(false);
			vgLogMessage("OpenGL context without stereo support");
		}
		m_hasCurrentGLContextProperties = true;

#ifdef __USE_DDC__
		// Retrieves and prints informations about primary display adapter
		ddc_display_device_info_t displayDevice;
		ddc_get_primary_display_device_informations( &displayDevice );

		const std::string ddi = ddc_get_display_device_info(&displayDevice);
		getGleContext()->logEndl(ddi);
#endif

#ifdef __USE_GLE__
		// Finally, initializes gle and sets it current
// @todo only if not already done
		vgLogMessage("Start gle initialization...");
		getGleContext()->clear();
		getGleContext()->initialize();
		vgLogMessage("gle initialization successfully completed.");

		gleSetCurrent( getGleContext() );
#endif
		vgAssertN( isCurrent(), "Internal error." );

		return true;
	}
	else
	{
		// glc context is already created
		const bool retVal = setCurrent();

		return retVal;
	}
}


const bool Canvas::shutdownOpenGLContext()
{
	if ( m_glc != 0 )
	{
#ifdef __USE_GLE__
		// Cleans gle context
		gleSetCurrent(0);
		vgLogDebug("gle context unset current.");
#endif

		// Deletes glc context
		glc_destroy( glc() );
		m_glc = 0;
		vgLogDebug("glc context deleted.");

		return true;
	}
	else
	{
		return false;
	}
}


const bool Canvas::hasAnOpenGLContext() const
{
	return m_glc != 0;
}


#ifndef __USE_GLE__
// @todo
// Duplicated code from gle/glHelpers.hpp
namespace
{
	// OpenGL
	const int gleGetOpenGLMajorVersion()
	{
		assert(gleIsOpenGLCurrent());

		// version = "4.0.10151 Compatibility Profile Context"
		const char * version = (char*)glGetString(GL_VERSION);

		const int major = version[0] - '0';
		return major;
	}


	const int gleGetOpenGLMinorVersion()
	{
		assert(gleIsOpenGLCurrent());

		const char * version = (char*)glGetString(GL_VERSION);

		const int minor = version[2] - '0';
		return minor;
	}


	const float gleGetOpenGLVersion()
	{
		assert(gleIsOpenGLCurrent());

		const char * version = (char*)glGetString(GL_VERSION);

		const float major = static_cast<float>(version[0] - '0');
		const float minor = static_cast<float>(version[2] - '0');

		float versionNumber = major + minor / 10.f;
		return versionNumber;
	}



	// GLSL
	const int gleGetGLSLMajorVersion()
	{
		assert(gleIsOpenGLCurrent());

		// version = "4.00"
		const char * version = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

		const int major = version[0] - '0';
		return major;
	}


	const int gleGetGLSLMinorVersion()
	{
		assert(gleIsOpenGLCurrent());

		const char * version = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

		const int minor = version[2] - '0';
		return minor;
	}


	const float gleGetGLSLVersion()
	{
		assert(gleIsOpenGLCurrent());

		const char * version = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

		const float major = static_cast<float>(version[0] - '0');
		const float minor = static_cast<float>(version[2] - '0');

		float versionNumber = major + minor / 10.f;
		return versionNumber;
	}

}
#endif // #ifndef __USE_GLE__


const bool Canvas::startVGSDK()
{
	if ( startOpenGLContext() == false )
	{
		// No current OpenGL context
		vgLogMessage("No current OpenGL context.");
		vgLogMessage("vgSDK startup aborted...\n");
		return false;
	}

	vgAssertN( isCurrent(), "OpenGL context must have been set current." );

	using boost::logic::indeterminate;
	if ( indeterminate( hasVGSDK() ) )
	{
		vgLogMessage("Start vgSDK...");

		// Checks OpenGL requirements for vgsdk, i.e
		// full mode requested by enabled GLSL usage (engine->setGLSLEnabled(false)) => requirements OpenGL >= 4.2).
		// @todo deprecated: "compatibility" mode requested by disabling GLSL usage (engine->setGLSLEnabled(false)) => requirements OpenGL >= 2.0

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
#ifdef __OPENGLES2__
			const float requiredOpenGLVersion = 2.f;
			const float requiredGLSLVersion = 1.f;
#else
			const float requiredOpenGLVersion = 4.2f;
			const float requiredGLSLVersion = 4.2f;
#endif
			// Checks full mode
			vgLogMessage("Checks OpenGL requirements for vgsdk (i.e. OpenGL version >= %f, GLSL version >= %f)...", requiredOpenGLVersion, requiredGLSLVersion);
			vgLogMessage("OpenGL %i.%i found", gleGetOpenGLMajorVersion(), gleGetOpenGLMinorVersion() );
			vgLogMessage("GLSL %i.%i found", gleGetGLSLMajorVersion(), gleGetGLSLMinorVersion() );

			if (vgm::greaterThanEqual(gleGetOpenGLVersion(), requiredOpenGLVersion) &&
				vgm::greaterThanEqual(gleGetGLSLVersion(), requiredGLSLVersion))
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

		// Initializes vgeGLBase
// @todo only for the first canvas
		getGLEngine()->reset();

		// FIXME
		///@todo Remove setToDefaults().
// @todo only for the first canvas
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
			if ( getVerticalSynchronization() != m_initialVerticalSynchronization )
			{
				setVerticalSynchronization( m_initialVerticalSynchronization );

				// Success ?
				if ( getVerticalSynchronization() == m_initialVerticalSynchronization )
				{
					logDebugVerticalSynchronizationState( this );
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
	uninitDevices();

	//
	if ( indeterminate(hasVGSDK()) )
	{
		// Nothing to do
		vgLogDebug/*logMessage*/("vgSDK shutdown: nothing to do, because already shutdown or never started.\n");

		//
		shutdownOpenGLContext();

		return false;
	}
	else if ( !hasVGSDK() )
	{
		// Nothing to do
		vgLogDebug/*logMessage*/("vgSDK shutdown: nothing to do, because vgSDK startup failed. Checks OpenGL requirements.\n");

		//
		shutdownOpenGLContext();

		m_hasVGSDK = boost::logic::indeterminate;
		return false;
	}
	else
	{
		vgAssert( hasVGSDK() );
		m_hasVGSDK = boost::logic::indeterminate;

		// Do the shutdown
		vgLogDebug/*logMessage*/("Shutdown vgSDK...");

		if ( m_canvasCount >= 2 )
		{
			// There are at least two canvas

			// gle context and OpenGL engine are shared.

			// Only shutdown OpenGL context (i.e drawable and OpenGL context if not shared, unset gle context).
			shutdownOpenGLContext();

			vgLogMessage("vgSDK shutdown completed (delayed to the last canvas).\n");
			return false;
		}
		else
		{
			vgAssert( m_canvasCount == 1 );

			if ( startOpenGLContext() )
			{
				vgAssertN( isCurrent(), "OpenGL context must have been set current. So OpenGL objects could not be released properly." );

				// OpenGL engine
				// Try to destroy OpenGL objects
				vgLogDebug/*logMessage*/("Releases managed OpenGL objects...\n");

				getGLEngine()->getGLManager()->clear();

				::glo::GLSLProgram::useFixedPaths();
				getGLEngine()->getGLSLManager()->clear();

				shutdownOpenGLContext();

				vgLogMessage("vgSDK shutdown completed.\n");
				return true;
			}
			else
			{
				// No current OpenGL context
				vgLogDebug/*logWarning*/("No current OpenGL context.");
				vgLogDebug/*logMessage*/("vgSDK shutdown aborted...\n");

				//
				shutdownOpenGLContext();

				vgLogMessage("vgSDK shutdown finished, but not completed.\n");
				return false;
			}
		}
	}
}


void Canvas::updateFPSOverlay()
{
#ifdef __USE_VGCAIRO__
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
#else
	#pragma message ("Canvas::updateFPSOverlay(): not supported")
	vgAssertN(false, "Canvas::updateFPSOverlay() : not supported");
#endif
}


#ifdef __USE_GLE__
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
		vgAssertN( false, "vgUI::Canvas: Unsupported gle log system." );
		return &std::cout;
	}
}
#endif


void Canvas::startVideoCapture()
{
	// Test if video capture is not enabled
	if ( !m_videoCapture )
	{
		vgLogMessage("Starting video capture...");

		// COMPUTE DIRECTORY NAME
		using namespace boost::local_time;
		using namespace boost::posix_time;

		std::stringstream ss;
		time_facet * outputFacet = new time_facet(); 
		ss.imbue( std::locale(std::locale::classic(), outputFacet) );
		outputFacet->format(m_videoCaptureDirectoryNameFormat.c_str()); // default format : Monday-29-02-2009_14h30m12s
		ss << second_clock::local_time();
		const std::string videoDirectoryName = ss.str();

		// Computes full path for video
		namespace bfs = boost::filesystem;
		const bfs::path path = sbf::pkg::Module::get()->getPath(sbf::pkg::VarPath) / bfs::path("videos") / videoDirectoryName; // @todo improve sbf api

		// Creates directory
		m_video->createDirs( path.string() );

		// Configures buffering
		using vgd::basic::Image;
		using vgeGLBase::engine::Engine;

		// What to capture COLOR
		m_whats.clear();
		m_whats.push_back( 0 );
		// m_whats.push_back( 1 ); @todo use vgQt::engine::RecordSettings to choose if DEPTH have to be captured

		// creating a screenshot
		std::vector< vgd::Shp< Image > > images;

		for( uint i=0; i != m_whats.size(); ++i )
		{
			const uint what = m_whats[i];
			vgd::Shp< Image > image = getGLEngine()->captureGLFramebuffer( static_cast<Engine::CaptureBufferType>(what) );
			images.push_back( image );
		}

		// @todo use vgQt::engine::RecordSettings to choose the buffer size
		const uint bufferSize = std::max( m_maxNumberOfCapturesPerSecond * 3, static_cast<uint>(10) );
		m_video->setBufferingSize( bufferSize, vgd::makeShp( new Screenshot(0, images) ) );

		// Launches thread to serialize captured images
		vgLogMessage("Starting thread to serialize video capture.");
		m_video->startThread();
	}
	//else nothing to do

	m_videoCapture = true;
}

void Canvas::stopVideoCapture()
{
	// Test if video capture is enabled
	if ( m_videoCapture )
	{
		// Disable video capture
		vgLogMessage("Schedule interruption of thread to serialize video capture...");
		m_video->scheduleThreadInterrupt();
		m_video->getThread().join();
		vgLogMessage("Video capture thread interrupted.\n");
	}
	//else nothing to do

	m_videoCapture = false;
}



#ifdef __USE_GLE__
boost::filesystem::path Canvas::getGlePath()
{
	return sbf::pkg::Module::get()->getPathSafe(sbf::pkg::VarPath);
}
#endif


glc_t * Canvas::glc() const
{
	vgAssert( m_glc != 0);
	return m_glc;
}



} // namespace vgUI
