// VGSDK - Copyright (C) 2008-2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGUI_CANVAS_HPP
#define _VGUI_CANVAS_HPP

#include <boost/date_time/posix_time/posix_time.hpp> // @todo uses vgsdk time classes
#include <boost/filesystem/convenience.hpp>

#include <glc/glc.hpp>

#include <sbf/pkg/Module.hpp>
#include <vgd/event/Source.hpp>

#include <vgeGL/engine/SceneManager.hpp>

#include "vgUI/vgUI.hpp"

namespace gle { struct OpenGLExtensionsGen; }

namespace vgd 
{ 
	namespace basic { struct Image; }
	namespace node
	{
		struct LayerPlan;
		struct MultiSwitch;
	}
}


namespace vgUI
{

struct Screenshot;
struct ScreenshotContainer;

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
struct VGUI_API Canvas : public vgeGL::engine::SceneManager, public vgd::event::Source
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
	 * @name Constructors and destructor
	 */
	//@{

	/**
	 * @brief Construct a Canvas
	 *
	 * @param sharedCanvas						0 to construct a Canvas with its own engine and OpenGL context, otherwise construct a Canvas sharing resources. See newOpenGLContextSharingObjects parameter to control what resources are shared.
	 * @param newOpenGLContextSharingObjects	true to create a new OpenGL context sharing objects with the given canvas, false to reuse the OpenGL context.
	 *
	 * @remark The Engine is always shared.
	 */
	Canvas( const Canvas * sharedCanvas = 0, const bool newOpenGLContextSharingObjects = false );

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
	const bool setCurrent();

	/**
	 * @brief Unsets the current OpenGL context to this window.
	 *
	 * @return true if the OpenGL context has been unset current, false otherwise.
	 */
	const bool unsetCurrent();

	/**
	 * @brief Tests if there is a current OpenGL context to this window.
	 *
	 * @return true if the OpenGL context has been made current, false otherwise.
	 */
	const bool isCurrent() const;

	/**
	 * @brief Performs an OpenGL swap buffer command.
	 */
	void swapBuffer();

	//@}


	/**
	 * @name OpenGL swap control
	 */
	//@{

	typedef enum {
		NO_VSYNC		= 0,		///< Buffer swaps are not synchronized to a video frame.
		VSYNC			= 1,		///< Buffer swaps are synchronized to a video frame.
		ADAPTIVE_VSYNC	= -1		///< Late swaps can occur without synchronization to the video frame (to reduce the visual stutter on late frames and reduces the stall on subsequent frames). Otherwise buffer swaps are synchronized to a video frame (see in VSYNC).
	} SwapControlMode;

	/**
	 * @brief Sets the initial vertical synchronization state of this canvas
	 *
	 * At the end of the vgsdk startup (see startVGSDK()), the OpenGL context is configured using the setting
	 * given by this method. By default, adaptive vertical synchronization is enabled (if swap control is available and
	 * not overridden by driver).
	 */
	void setInitialVerticalSynchronization( const SwapControlMode mode );


	/**
	 * @brief Tests if vertical synchronization control is available (i.e. EXT_swap_control extension)
	 *
	 * @pre isCurrent()
	 *
	 * @return true if available, false otherwise
	 */
	const bool hasVerticalSynchronizationControl() const;

	/**
	 * @brief Tests if adaptive vertical synchronization control is available (i.e. EXT_swap_control_tear extension)
	 *
	 * @pre isCurrent()
	 *
	 * @return true if available, false otherwise
	 */
	const bool hasAdaptiveVerticalSynchronizationControl() const;

	/**
	 * @brief Sets the vertical synchronization state of the current OpenGL context
	 *
	 * @pre isCurrent()
	 *
	 * @remark If hasAdaptiveVerticalSynchronizationControl() returns false and mode is ADAPTIVE_VSYNC, then VSYNC is used.
	 */
	void setVerticalSynchronization( const SwapControlMode mode = ADAPTIVE_VSYNC );

	/**
	 * @brief Returns the vertical synchronization state
	 *
	 * @pre isCurrent()
	 */
	const SwapControlMode getVerticalSynchronization() const;

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
	virtual const bool setFullscreen( const bool wantFullscreen = true );

	/**
	 * @brief Returns the fullscreen mode.
	 *
	 * @return true if in fullscreen mode, false otherwise.
	 */
	virtual const bool isFullscreen();

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
	void paint( const vgm::Vec2i& size, const bool bUpdateBoundingBox );
	void resize( const vgm::Vec2i& size );
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
	 * @param wait	SYNCHRONOUS to wait the end of the repaint before returning from this method, or
	 * 				ASYNCHRONOUS to post a paint message to the window and returning without being blocked.
	 *
	 * Derived class must implement this method in order to perform relevant action to
	 * trigger painting according to the wait parameter.
	 */
	virtual void refreshForced( const WaitType wait = ASYNCHRONOUS ) = 0;
	//@}


private:
	vgd::Shp< ScreenshotContainer > m_video;
	std::vector< uint >				m_whats;
	uint							m_maxNumberOfCapturesPerSecond;
public:
	const uint getMaxNumberOfCapturesPerSecond() const { return m_maxNumberOfCapturesPerSecond; }
	void setMaxNumberOfCapturesPerSecond(const uint value ) { m_maxNumberOfCapturesPerSecond = value; }



	/**
	 * @name Screenshot and video capture
	 */
	//@{

	/**
	 * @brief Schedules a screen capture at the end of next rendering.
	 *
	 * @param filename	name of the file containing the screen capture
	 * @param module	used to compute the root directory where the screen capture would be saved
	 * @param subdir	used to compute the root directory where the screen capture would be saved
	 *
	 * The screen capture would be saved in a png file named 'var/subdir/filename' where var is the 'var' directory of the given module, subdir and filename are the given parameters.
	 */
	void scheduleScreenshot( const std::string filename = "", const boost::shared_ptr< sbf::pkg::Module > module = sbf::pkg::Module::get(), const std::string subdir = "screenshots" );

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
	 * @param isEnabled				true when video capture is enabled, false otherwise.
	 * @param directoryNameFormat	specifies the directory named created to store the video. "Monday-29-02-2009_14h30m12s" is generated by the default value of this parameter. See time_facet in boost::posix_time for documentation.
	 */
	void setVideoCapture( const bool isEnabled = true, const std::string directoryNameFormat = "%A-%d-%m-%Y_%Hh%Mm%Ss" );

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
	 * @brief	Creates the drawable that will be used by the canvas.
	 *
	 * @return	a pointer to a new drawable
	 *
	 * Subclasses must implement this method in order to create the drawable in a manner dedicated to the effective user interface toolkit.
	 */
	virtual glc_drawable_t * createDrawable() = 0;

	/** 
	 * @brief	Destroys the given drawable.
	 *
	 * @param	drawable	a pointer to teh drawable to destroy
 	 *
	 * Subclasses must implement this method in order to destroy the drawable in a manner dedicated to the effective user interface toolkit.
	 */
	virtual void destroyDrawable( glc_drawable_t * ) = 0;

	/**
	 * @brief Calls this method to creates the OpenGL context (if needed) and makes it current.
	 *
	 * This method must return true if the OpenGL context is current or have been made current, false otherwise.
	 */
	const bool startOpenGLContext();

	/**
	 * @brief Calls this method to delete the OpenGL context.
	 */
	const bool shutdownOpenGLContext();

	/**
	 * @brief	Tells if there is an OpenGL context.
	 */
	const bool hasAnOpenGLContext() const;


	// @todo documentation
	gle::OpenGLExtensionsGen * getGleContext();


	// Overridden
	const bool startVGSDK();
	// Overridden
	const bool shutdownVGSDK();


private:

	/**
	 * @brief Resets scene graph
	 */
	void privateResetSceneGraph();

	/**
	 * @brief Updates the layer plan used by fps overlay.
	 */
	void updateFPSOverlay();

	/**
	 * @brief Returns the output stream associated to the gle log system.
	 *
	 * @return the output stream
	 */
	static std::ostream* getGleOutputStream();

	void startVideoCapture();
	void stopVideoCapture();

protected:
	const Canvas *		m_sharedCanvas;						///< a pointer to another Canvas for OpenGL objects sharing, or null if sharing is not desired.
private:

	//glc_drawable_t *						m_drawable;		///< The drawable associated to the canvas window
	glc_t *									m_glc;			///< The GL context
	vgd::Shp< gle::OpenGLExtensionsGen >	m_gleContext;	///< gle main object to be able to access OpenGL extensions

	glc_t * glc() const;

	// VSYNC
	SwapControlMode		m_initialVerticalSynchronization;	///< the initial vertical synchronization state of this canvas

	// SCREENSHOT
	bool				m_scheduleScreenshot;				///< Boolean value telling if a screen capture should be done at the end of next rendering.
	std::string			m_screenshotPath;					///< path used for the screenshot
	std::string			m_screenshotFilename;				///< name of file used for the screenshot

	// VIDEO
	bool				m_scheduleVideoCapture;				///< Boolean value telling if a video capture should be start at the end of the next rendering
	std::string			m_videoCaptureDirectoryNameFormat;

	bool				m_videoCapture;						///< Boolean value telling if the video capture is enabled.

	//
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
	boost::posix_time::ptime	m_timeBase;

	int							m_frameTime;	///< the time taken to render the last frame
	int							m_fps;
	//@}
};



} // namespace vgUI

#endif // #ifndef _VGUI_CANVAS_HPP
