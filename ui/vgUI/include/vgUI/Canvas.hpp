// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGUI_CANVAS_HPP
#define _VGUI_CANVAS_HPP

#include <boost/date_time/posix_time/posix_time.hpp>
#include <vgd/event/Device.hpp>
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
 * - Screenshot and video capture
 * - event debugging helpers
 * - debug overlay with runtime informations like fps
 *
 * @ingroup g_vgUIGroup
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

	//@}


	/**
	 * @name	Constructors & Destructor
	 */
	//@{
	/**
	 * @brief	Construct a Canvas with its own OpenGL context.
	 *
	 * @pre	getCanvasCount() == 0
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
	Canvas(	const Canvas * sharedCanvas );

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
	virtual const bool isCurrent() = 0;

	/**
	 * @brief Performs an OpenGL swap buffer command.
	 */
	virtual void swapBuffer() = 0;
	/**
	 * @brief Determines whether vgsdk is locally initialized or not.
	 *
	 * @return true if Vgsdk is localy initialized, false otherwise
	 */
	const bool isVGSDKLocalyInitialized() const;
	///@}



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

		const std::string buildFilename( const std::string filePrefix );
		void save( const std::string path, const std::string filePrefix, const bool feedback = false );

	private:
		const uint						m_frameNumber;	///< the frame number to identify a screenshot. This attribute could be used to order a sequence of screenshots.
		vgd::Shp< vgd::basic::Image >	m_image;		///< the screenshot is stored by this image
	};

	struct ScreenshotContainer : public std::list< Screenshot >
	{
		//void append( vgd::Shp< Screenshot > screenshot );

		void save( const std::string path, const std::string filePrefix, const bool feedback = false )
		{
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
			}
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
	 */
	void scheduleScreenshot();

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

	//@}



	/**
	 * @name	Debugging helpers
	 */
	//@{

	/**
	 * @brief Enables or disables the rendering of the debug overlay depending on the value of the parameter \c isEnabled.
	 *
	 * @param isEnabled		true when debug overlay must be rendered, false otherwise
	 */
	void setDebugOverlay( const bool isEnabled = true );

	/**
	 * @brief Determines whether the rendering of the debug overlay is enabled.
	 *
	 * @return true if the rendering of the debug overlay is enabled, false otherwise
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

	/**
	 * @brief Calls this method before using vgsdk.
	 *
	 * @return true if vgsdk could be used. OpenGL, glc, gle, vge, vgeGL are ready to be used, false otherwise.
	 */
	const bool startVGSDK();

	/**
	 * @brief Calls this method when you no longer need vgsdk.
	 *
	 * @return true if vgsdk shutdown has been completed successfuly, false otherwise.
	 */
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

	const Canvas *	m_sharedCanvas;				///< a pointer to another Canvas for OpenGL objects sharing, or null if sharing is not desired.
	bool			m_bLocalInitializedVGSDK;	///< Boolean value set if initializeVGSDK() has already been called for this instance of Canvas.
	bool			m_scheduleScreenshot;		///< Boolean value telling if a screen capture should be done at the end of next rendering.
	bool			m_videoCapture;				///< Boolean value telling if the video capture is enabled.

	bool			m_debugEvents;				///< Boolean value telling if events should be debugged or not.

protected: // @todo FIXME
	vgd::Shp< vgd::node::MultiSwitch >		m_debugOverlayContainer;	///< A reference on the overlay container node used internally by vgSDK
private:
	vgd::Shp< vgd::node::LayerPlan >		m_overlayForFPS;	///< A reference on the layer plan used to render fps

	/**
	 * @name Attributes used to compute fps
	 */
	//@{
	uint						m_frameBase;
	boost::posix_time::ptime	m_timeBase;
	int							m_fps;
	//@}
};



} // namespace vgUI

#endif // #ifndef _VGUI_CANVAS_HPP
