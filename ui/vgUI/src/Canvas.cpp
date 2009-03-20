// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgUI/Canvas.hpp"

#include <cassert>
#include <iostream>

#include <boost/format.hpp> 
//#include <boost/date_time/posix_time/posix_time.hpp>
//#include <boost/lexical_cast.hpp>
#include <boost/lexical_cast.hpp>
#include <vgCairo/helpers.hpp>
#include <vgCairo/ImageSurface.hpp>
#include <vgd/basic/Image.hpp>
//

#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgd/event/Location2Event.hpp>
#include <vgd/event/MouseButtonEvent.hpp>
#include <vgd/event/MouseWheelEvent.hpp>
#include <vgd/event/SizeEvent.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#include <vgd/event/detail/helpers.hpp>
#include <vgd/node/LayerPlan.hpp>
#include <vgd/node/MultiSwitch.hpp>
#include <vgd/visitor/helpers.hpp>
#include <vgDebug/convenience.hpp>
#include <vgDebug/Global.hpp>

#include <vgeGL/engine/Engine.hpp>



namespace vgUI
{



const std::string Canvas::Screenshot::buildFilename( const std::string filePrefix )
{
	// Constructs filename
	const std::string strCount = (boost::format("%|07|") % getFrameNumber()).str();
	const std::string filename = filePrefix + strCount + ".png";

	return filename;
}



void Canvas::Screenshot::save( const std::string path, const std::string filePrefix, const bool feedback )
{
	const std::string filename = buildFilename( filePrefix );

	// Tests path existance ???

	// User feedback
	if ( feedback )
	{
		vgLogDebug2( "Screenshot done in file %s", filename.c_str() );
		vgLogStatus2( "Screenshot done in file %s", filename.c_str() );
	}

	// Saves image
	getImage()->save( path + filename );
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
	m_gleContext				( getGleOutputStream()	),
	m_sharedCanvas				( 0						),
	m_bLocalInitializedVGSDK	( false					),
	m_scheduleScreenshot		( false					),
	m_videoCapture				( false					),
	m_debugEvents				( false					),
	m_frameBase					( 0						),
	// m_timeBase
	m_fps						( -1					)
{
	// Updates the number of canvas
	assert( getCanvasCount() == 0 && "This is not the first canvas." );
	++m_canvasCount;

	// Resets the scene graph
	privateResetSceneGraph();
}



Canvas::Canvas(	const Canvas *sharedCanvas )
:	vgeGL::engine::SceneManager( vgd::Shp< vgeGL::engine::Engine >( new vgeGL::engine::Engine() ) ),
	// m_gleLogSystem
	// m_gleLogFile
	m_gleContext				( getGleOutputStream()	),
	m_sharedCanvas				( 0						),
	m_bLocalInitializedVGSDK	( false					),
	m_scheduleScreenshot		( false					),
	m_videoCapture				( false					),
	m_debugEvents				( false					),
	m_frameBase					( 0						),
	// m_timeBase
	m_fps						( -1					)
{
	// Updates the number of canvas
	assert( getCanvasCount() >= 1 && "This is the first canvas." );
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
	using vgd::node::LayerPlan;

	m_debugOverlayContainer	= vgd::node::MultiSwitch::create(	"DEBUG_OVERLAY_CONTAINER"	);
	m_overlayForFPS = LayerPlan::create( "FPS" );
	m_debugOverlayContainer->addChild( m_overlayForFPS );

	// @todo position and size should be in pixel (LayerPlan must be improved)
	const float width = 0.2f;
	m_overlayForFPS->setPosition( vgm::Vec2f(1.f - width, 0.0f) );
	m_overlayForFPS->setSize( vgm::Vec2f(width, width * 32.f / 128.f) );

	//
	using vgCairo::ImageSurface;
	vgd::Shp< ImageSurface > imageSurface( new ImageSurface(128, 32) );
	m_overlayForFPS->setIImage( imageSurface );
}



Canvas::~Canvas()
{
	// Updates the number of canvas
	assert( m_canvasCount > 0 );
	--m_canvasCount;
}


const bool Canvas::isVGSDKLocalyInitialized() const
{
	return m_bLocalInitializedVGSDK;
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

		//
		namespace bpt = boost::posix_time;

		bpt::ptime beginPaint = bpt::microsec_clock::universal_time();

		// Initializes attributes used by fps computation
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
			capturedImage = getGLEngine()->captureFramebuffer();

			// Constructs the screenshot and saves the png image
			Screenshot shot( getFrameCount(), capturedImage );
			shot.save( "../var/vgsdk/screenshots/", "frame", true );		// @todo

			//
			m_scheduleScreenshot = false;
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
					capturedImage = getGLEngine()->captureFramebuffer();
				}

				m_video.push_back( Screenshot( getFrameCount(), capturedImage ) );

				lastCapture = currentCapture;
			}
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

		// Computes fps
		bpt::time_duration elapsedTimeBetweenFPSComputation = endPaint - m_timeBase;
		if ( elapsedTimeBetweenFPSComputation.total_milliseconds() > 1000 )
		{
			const uint numberOfFrames = getFrameCount() - m_frameBase;
			setFPS( numberOfFrames * 1000 / elapsedTimeBetweenFPSComputation.total_milliseconds() );

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
		//vgDebug::get().logDebug("refresh: because of node named %s\n", result->getName().c_str() );

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



void Canvas::scheduleScreenshot()
{
	m_scheduleScreenshot = true;
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



const int Canvas::setFPS( const int newFPS )
{
	m_fps = newFPS;

	return m_fps;
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
	//
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

		// Try to destroy OpenGL objects
		vgDebug::get().logDebug/*logMessage*/("Releases managed OpenGL objects (but without a current OpenGL context)...\n");
		getGLEngine()->getGLManager().clear();
		getGLEngine()->getGLSLManager().clear();

		return false;
	}

	// Last canvas is about to be destroy
	if ( m_canvasCount == 1 )
	{
		assert( isCurrent() && "OpenGL context must have been set current. So OpenGL objects could not be released properly." );

		// Try to destroy OpenGL objects
		vgDebug::get().logDebug/*logMessage*/("Releases managed OpenGL objects...\n");
		getGLEngine()->getGLManager().clear();
		getGLEngine()->getGLSLManager().clear();

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


void Canvas::updateFPSOverlay()
{
	// Updates fps overlay overlay
	using vgCairo::ImageSurface;
	vgd::Shp< ImageSurface > imageSurface = vgd::dynamic_pointer_cast< ImageSurface >( m_overlayForFPS->getIImage() );
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

	cairo_set_font_size( cr, 24.f );
	cairo_set_source_rgb( cr, 1.f, 1.f, 1.f );
	cairo_move_to( cr, 5.f, 24.f );

	const std::string strFrameCount = boost::lexical_cast< std::string >( getFrameCount() );
	const std::string strFPS = getFPS() >= 0 ? boost::lexical_cast< std::string >( getFPS() ) : "na";

	cairo_show_text( cr, (strFPS + " " + strFrameCount).c_str() );

	cairo_restore(cr);

	// Updates the image (invalidates the image).
	m_overlayForFPS->setIImage( m_overlayForFPS->getIImage() );
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
			m_gleLogFile.open("../var/gle.txt");
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
