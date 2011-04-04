// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGUI_CANVAS_HPP
#define _VGUI_CANVAS_HPP

#include <boost/date_time/posix_time/posix_time.hpp> // @todo uses vgsdk time classes
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/operations.hpp>
#include <gle/OpenGLExtensionsGen.hpp>
#include <vgd/event/Device.hpp>
#include <vgDebug/convenience.hpp>
#include <vgeGL/engine/SceneManager.hpp>

#include "vgUI/vgUI.hpp"

namespace vgd 
{ 

namespace basic 
{
	struct Image; 
}

namespace node 
{
	struct LayerPlan;
	struct MultiSwitch;
} 

}



namespace vgUI
{

/**
 * @brief An abstract canvas for displaying vgsdk graphics.
 *
 * This class do some cool things internally :
 *
 * - Use the vgeGL::engine::SceneManager to link GUI and the scene graph.
 * - Initialize OpenGL and its extensions (with gle) to being used by vgsdk.
 * - Report OpenGL errors before and after rendering (paint and resize methods).
 * - switch to/from fullscreen mode
 * - Screenshot and video capture
 * - event debugging helpers
 * - debug overlay with runtime informations like fps, frame time and frame count
 *
 * @ingroup g_vgUIGroup
 * @ingroup g_layerplan
 */
struct VGUI_API Canvas : public vgeGL::engine::SceneManager, public vgd::event::Device
{
	/**
	 * @name gle log accessors
	 */
	//@{

	enum GleLogSystem
	{
		GLE_FILE,			//!< gle.txt file. This is the default log system.
		GLE_FILE_IN_VAR,	//!< gle.txt file in ../var
		GLE_COUT			//!< standard output
	};

	/**
	 * @brief Sets the log system used by gle library.
	 *
	 * For additionnal information about the different log system, see GleLogSystem enumeration.
	 *
	 * @param logger		 specify the log system used to output gle informations about OpenGL context.
	 */
	static void setGleLogSystem( const GleLogSystem logger );

	/**
	 * @brief Gets the log system used by gle library.
	 *
	 * @return a value from GleLogSystem enumeration.
	 */
	static const GleLogSystem getGleLogSystem();

	/**
	 * @brief Gets the path to gle.txt file
	 *
	 * @return a path
	 */
	static boost::filesystem::path getGlePath();

	//@}


	/**
	 * @name	Constructors and destructor
	 */
	//@{
	/**
	 * @brief	Construct a Canvas with its own OpenGL context.
	 *
	 * @pre		getCanvasCount() == 0
	 * @post	getCanvasCount() == 1
	 */
	Canvas();

	/**
	 * @brief	Construct a Canvas with its own OpenGL context, but that share OpenGL objects with another(s) Canvas.
	 *
	 * @param	sharedCanvas	a pointer to another Canvas for OpenGL objects sharing
	 *
	 * @pre	getCanvasCount() >= 1
	 */
	Canvas( const Canvas * sharedCanvas );

	/**
	 * @brief	Virtual destructor
	 */
	virtual ~Canvas();

	/**
	 * @brief Resets scene graph
	 */
	virtual void resetSceneGraph();
	//@}


	/**
	 * @name	Rendering Context
	 */
	//@{

	/**
	 * @brief Sets the current OpenGL context to this window.
	 *
	 * @return true if the OpenGL context has been made current, false otherwise.
	 */
	virtual const bool setCurrent() = 0;

	/**
	 * @brief Unsets the current OpenGL context to this window.
	 *
	 * @return true if the OpenGL context has been unset current, false otherwise.
	 */
	virtual const bool unsetCurrent() = 0;

	/**
	 * @brief Tests if there is a current OpenGL context to this window.
	 *
	 * @return true if the OpenGL context has been made current, false otherwise.
	 */
	virtual const bool isCurrent() const = 0;

	/**
	 * @brief Performs an OpenGL swap buffer command.
	 */
	virtual void swapBuffer() = 0;

	//@}


	/**
	 * @name OpenGL swap control
	 */
	//@{

	/**
	 * @brief Sets the initial vertical synchronization state of this canvas
	 *
	 * At the end of the vgsdk startup (see startVGSDK()), the OpenGL context is configured using the setting
	 * given by this method. By default, vertical synchronization is enabled (if swap control is available and
	 * not overridden by driver).
	 */
	void setInitialVerticalSynchronization( const bool enabled );


	/**
	 * @brief Tests if vertical synchronization control is available
	 *
	 * @pre isCurrent()
	 *
	 * @return true if available, false otherwise
	 */
	const bool hasVerticalSynchronizationControl() const;

	/**
	 * @brief Sets the vertical synchronization state of the current OpenGL context
	 *
	 * @pre hasVerticalSynchronizationControl() and isCurrent()
	 */
	void setVerticalSynchronization( const bool enabled = true );

	/**
	 * @brief Tests if the vertical synchronization is enabled
	 *
	 * @pre hasVerticalSynchronizationControl() and isCurrent()
	 */
	const bool isVerticalSynchronizationEnabled() const;

	//@}


	/**
	 * @name Fullscreen
	 */
	//@{

	/**
	 * @brief Enables/disables fullscreen mode.
	 *
	 * @param wantFullscreen	true to enable fullscreen mode, false to disable fullscreen mode.
	 */
	virtual const bool setFullscreen( const bool wantFullscreen = true ) = 0;

	/**
	 * @brief Returns the fullscreen mode.
	 *
	 * @return true if in fullscreen mode, false otherwise.
	 */
	virtual const bool isFullscreen() = 0;

	/**
	 * @brief Enables or disables fullscreen mode depending on the current state.
	 *
	 * @remarks To check if mode switching occurs, checks return value of isFullscreen()
	 */
	virtual void switchFullscreen();

	//@}



	/**
	 * @name	Overridden methods
	 */
	//@{
	void onEvent( vgd::Shp< vgd::event::Event > event );
	void paint( const vgm::Vec2i size, const bool bUpdateBoundingBox );
	void resize( const vgm::Vec2i size );
	//@}


	/**
	 * @brief Returns the number of instance of this class.
	 *
	 * @return the canvas count
	 */
	const uint32 getCanvasCount() const;

	/**
	 * @brief Tests if OpenGL objects are shared with another(s) Canvas.
	 *
	 * @return true if OpenGL objects are shared, false otherwise.
	 *
	 * @remarks See constructors for sharing OpenGL objects.
	 */
	const bool isOpenGLObjectsShared() const;



	/**
	 * @name Refresh management
	 */
	//@{
	/**
	 * @brief Type of refresh.
	 */
	enum RefreshType
	{
		REFRESH_FORCE,
		REFRESH_IF_NEEDED
	};

	/**
	 * @brief Wait behavior of refresh.
	 */
	enum WaitType
	{
		SYNCHRONOUS,
		ASYNCHRONOUS
	};

	/**
	 * @brief Repaints the window.
	 *
	 * @param type		REFRESH_FORCE to force the repaint even if no changes have been made in the scene graph,
	 * 				or REFRESH_IF_NEEDED to repaint only when at least one change in the scene graph has occured since the
	 *				last repaint
	 * @param wait		SYNCHRONOUS to wait the end of the repaint before returning from this method, or
	 * 				ASYNCHRONOUS to post a paint message to the window and returning without being blocked.
	 */
	void refresh( const RefreshType type = REFRESH_IF_NEEDED, const WaitType wait = ASYNCHRONOUS );

	/**
	 * @brief Repaints the window only and only if at least one change in the scene graph has occured since the last repaint.
	 *
	 * @param wait		SYNCHRONOUS to wait the end of the repaint before returning from this method, or
	 * 				ASYNCHRONOUS to post a paint message to the window and returning without being blocked.
	 */
	void refreshIfNeeded( const WaitType wait = ASYNCHRONOUS );

	/**
	 * @brief Force the repaints of the window even if no changes have been made in the scene graph.
	 *
	 * @param wait		SYNCHRONOUS to wait the end of the repaint before returning from this method, or
	 * 				ASYNCHRONOUS to post a paint message to the window and returning without being blocked.
	 */
	void refreshForced( const WaitType wait = ASYNCHRONOUS );
	//@}


	/**
	 * @brief An image taken to record the 3d rendering
	 *
	 * @todo move this class
	 */
	struct Screenshot
	{
		Screenshot( const uint frameNumber, vgd::Shp< vgd::basic::Image > image )
		:	m_frameNumber( frameNumber ),
			m_image( image )
		{}

		const uint getFrameNumber() const				{ return m_frameNumber; }
		vgd::Shp< vgd::basic::Image > getImage() const	{ return m_image; }

		/**
		 * @brief Saves the screenshot to a file.
		 *
		 * @param filename	name of image file (with extension .png ) or 
		 *				empty to automatically construct a filename using prefix 'frame' and appending frame counter.
		 *
		 * @pre path directory must exist
		 *
		 * @remark If image specified by given parameters already exists, then it is overridden. Otherwise the image file is simply created.
		 */
		void save( const std::string path, const std::string filename = "", const bool feedback = true );

		void mkdirs( const std::string path )
		{
			namespace bfs = boost::filesystem;

			if ( bfs::exists( path ) == false )
			{
				vgLogDebug2( "Creates %s", path.c_str() );
				vgLogStatus2( "Creates %s", path.c_str() );

				bfs::create_directories( path );
			}
			// else nothing to do
		}

	private:
		const std::string buildFilename( const std::string filePrefix );

		const uint						m_frameNumber;	///< the frame number to identify a screenshot. This attribute could be used to order a sequence of screenshots.
		vgd::Shp< vgd::basic::Image >	m_image;		///< the screenshot is stored by this image
	};

	struct ScreenshotContainer : public std::list< Screenshot >
	{
		//void append( vgd::Shp< Screenshot > screenshot );

		/**
		 * @pre path directory must exist
		 */
		void save( const std::string path, const std::string filePrefix, const bool feedback = false )
		{
			namespace bfs = boost::filesystem;
			assert( bfs::exists( path ) && "Path not found" );

			while( size() >= 1 )
			{
				saveAndPopFront( path, filePrefix, feedback );
			}
			/*// 
			const_iterator	i		= begin(),
							iEnd	= end();

			while ( i != iEnd )
			{
				// Gets current screenshot
				Screenshot shot = *i;

				// Saves image
				shot.save( path, filePrefix, feedback );

				//
				++i;
			}*/
		}

		/**
		 * @pre path directory must exist
		 * @pre size() >= 1
		 */
		void saveAndPopFront( const std::string path, const std::string filePrefix, const bool feedback = false )
		{
			namespace bfs = boost::filesystem;
			assert( bfs::exists( path ) && "Path not found" );

			// Gets current screenshot
			Screenshot& shot = *begin();

			// Saves image
			shot.save( path, filePrefix, feedback );

			pop_front();
		}


		void mkdirs( const std::string path )
		{
			namespace bfs = boost::filesystem;

			if ( bfs::exists( path ) == false )
			{
				vgLogDebug2( "Creates %s", path.c_str() );
				vgLogStatus2( "Creates %s", path.c_str() );

				bfs::create_directories( path );
			}
			// else nothing to do
		}
	};
	//typedef std::list< Screenshot > ScreenshotContainerType;	///< a collection of screenshots

public://private:
	ScreenshotContainer 		m_video;
	//std::list< ScreenshotContainerType >	m_videos;
public:



	/**
	 * @name Screenshot and video capture
	 *
	 * Screen and video capture occurs only on 3d frame buffer.
	 */
	//@{

	/**
	 * @brief Schedules a screen capture at the end of next rendering.
	 *
	 * @param filename	name of the file containing the screen capture
	 */
	void scheduleScreenshot( const std::string filename = "" );

	/**
	 * @brief Tests if a screen capture is scheduled at the end of next rendering.
	 *
	 * @return true if a screen capture is scheduled at the end of next rendering, false otherwise.
	 */
	const bool isScreenshotScheduled() const;

	/**
	 * @brief Enables or disables the video capture depending on the value of the parameter \c isEnabled.
	 *
	 * When this option is enabled, vgSDK captures the screen at the end of each rendering until this option is disabled.
	 * To form a video file, captures the screen over an extended period of time.
	 *
	 * @param isEnabled		true when video capture is enables, false otherwise
	 */
	void setVideoCapture( const bool isEnabled = true );

	/**
	 * @brief Determines whether the video capture is enabled.
	 *
	 * @return true if the video capture is enabled, false otherwise
	 */
	const bool isVideoCaptureEnabled() const;

// @todo set/get/CapturesPerSecond()

	//@}



	/**
	 * @name	Debugging helpers
	 *
	 * @ingroup g_layerplan
	 */
	//@{

	/**
	 * @brief Enables or disables the rendering of the debug overlay depending on the value of the parameter \c isEnabled.
	 *
	 * @param isEnabled		true when debug overlay must be rendered, false otherwise
	 *
	 * @ingroup g_layerplan
	 */
	void setDebugOverlay( const bool isEnabled = true );

	/**
	 * @brief Determines whether the rendering of the debug overlay is enabled.
	 *
	 * @return true if the rendering of the debug overlay is enabled, false otherwise
	 *
	 * @ingroup g_layerplan
	 */
	const bool isDebugOverlay() const;

	/**
	 * @brief	Tells if the canvas will trace events.
	 *
	 * @return	true of false
	 */
	const bool debugEvents() const;

	/**
	 * @brief	Activates or deactivates the event debugging.
	 *
	 * @param	enable	a boolean with the new event debugging status
	 */
	void setDebugEvents( const bool enable );

	//@}



	/**
	 * @brief Returns the current fps, a shortcut for frames per second.
	 *
	 * @return the number of fps or a negative value if not available (this occurs at startup during the first second).
	 */
	const int getFPS() const;

	/**
	 * @brief Returns the time taken to render the last frame
	 *
	 * @return the time taken to render the last frame in ms
	 */
	const int getFrameTime() const;



protected:

	const uint increaseFrameCount();	///< Overridden method

	/**
	 * @brief Sets the frames per second counter.
	 *
	 * @param newFPS	the new counter value
	 *
	 * @return the new counter value
	 */
	virtual const int setFPS( const int newFPS );

	/**
	 * @brief Sets the time taken to render the last frame
	 *
	 * @param newFrameTime	the new value
	 */
	void setFrameTime( const int newFrameTime );



	/**
	 * @brief	Calls the overridable initialize method.
	 *
	 * @see		initialize()
	 */
	void doInitialize();



	/**
	 * @brief	Implementors must call the user interface toolkit dependent synchronious refresh method.
	 */
	virtual void doRefresh() = 0;

	/**
	 * @brief	Implementors must call the user interface toolkit dependent refresh method
	 * 			based on event passing.
	 */
	virtual void sendRefresh() = 0;


	/**
	 * @brief Calls this method to creates the OpenGL context (if needed) and makes it current.
	 *
	 * This method must return true if the OpenGL context is current or have been made current, false otherwise.
	 */
	virtual const bool startOpenGLContext() = 0;

	/**
	 * @brief Calls this method to delete the OpenGL context.
	 */
	virtual const bool shutdownOpenGLContext() = 0;

	// @todo documentation
	gle::OpenGLExtensionsGen& getGleContext();


	// Overridden
	const bool startVGSDK();
	// Overridden
	const bool shutdownVGSDK();


private:

	/**
	 * @brief gle main object to be able to access OpenGL extensions.
	 */
	gle::OpenGLExtensionsGen	m_gleContext;


private:

	/**
	 * @brief Resets scene graph
	 */
	void privateResetSceneGraph();

	/**
	 * @brief Updates the layer plan used by fps overlay.
	 */
	void updateFPSOverlay();

	static uint32			m_canvasCount;	///< Instance count of this class.
	static GleLogSystem		m_gleLogSystem;	///< A value from GleLogSystem enumeration to specify the log system used by gle library.
	static std::ofstream	m_gleLogFile;	///< The gle.txt file

	/**
	 * @brief Returns the output stream associated to the gle log system.
	 *
	 * @return the output stream
	 */
	static std::ostream* getGleOutputStream();

	const Canvas *		m_sharedCanvas;						///< a pointer to another Canvas for OpenGL objects sharing, or null if sharing is not desired.

	bool				m_initialVerticalSynchronization;	///< the initial vertical synchronization state of this canvas

	bool				m_scheduleScreenshot;				///< Boolean value telling if a screen capture should be done at the end of next rendering.
	std::string			m_screenshotFilename;				///< name of file used for the screenshot
	bool				m_videoCapture;						///< Boolean value telling if the video capture is enabled.

	bool				m_debugEvents;						///< Boolean value telling if events should be debugged or not.

protected: // @todo FIXME
	vgd::Shp< vgd::node::MultiSwitch >		m_debugOverlayContainer;	///< A reference on the overlay container node used internally by vgSDK
private:
	vgd::Shp< vgd::node::LayerPlan >		m_overlayForFPS;			///< A reference on the layer plan used to render fps

	/**
	 * @name Attributes used to compute fps
	 */
	//@{
	uint						m_frameBase;
	int							m_frameTime;	///< the time taken to render the last frame

	boost::posix_time::ptime	m_timeBase;
	int							m_fps;
	//@}
};



} // namespace vgUI

#endif // #ifndef _VGUI_CANVAS_HPP
