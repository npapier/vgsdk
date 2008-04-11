// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGUI_CANVAS_HPP
#define _VGUI_CANVAS_HPP


#include <vgeGL/engine/SceneManager.hpp>

#include "vgUI/vgUI.hpp"



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
 *
 * @ingroup g_vgUIGroup
 */
struct VGUI_API Canvas : public vgeGL::engine::SceneManager
{
	/**
	 * @name gle log accessors
	 */
	//@{

	enum GleLogSystem {
		GLE_FILE,		//!< gle.txt file. This is the default log system.
		GLE_COUT		//!< standard output
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
	 * @pre		getCanvasCount() >= 1
	 */
	Canvas(	const Canvas * sharedCanvas );

	/**
	 * @brief	Destructor
	 */
	virtual ~Canvas();
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
	///@}


	/**
	 * @name	Events Debugging
	 */
	//@{
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
	 * @name	Overrides
	 */
	//@{
	void onEvent( vgd::Shp< vgd::event::Event > event );
	void paint( const vgm::Vec2i size, const bool bUpdateBoundingBox );
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
	enum RefreshType {
		REFRESH_FORCE,
		REFRESH_IF_NEEDED
	};

	/**
	 * @brief Wait behavior of refresh.
	 */
	enum WaitType {
		SYNCHRONOUS,
		ASYNCHRONOUS
	};

	/**
	 * @brief Repaints the window.
	 *
	 * @param type		set to REFRESH_FORCE to force the repaint even if no changes have been made in the scene graph,
	 * 					or to REFRESH_IF_NEEDED to repaint only when at least one change in the scene graph has occured.
	 * @param wait		set to SYNCHRONOUS to wait the end of the repaint before returning from this method, or
	 * 					to ASYNCHRONOUS to post a paint message to the window and returning without beiing blocked.
	 */
	void refresh( const RefreshType type = REFRESH_IF_NEEDED, const WaitType wait = ASYNCHRONOUS );
	//@}


protected:
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


protected:

	/**
	 * @brief gle main object to be able to access OpenGL extensions.
	 */
	gle::OpenGLExtensionsGen	m_gleContext;


private:

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
	bool			m_debugEvents;				///< Boolean value telling if events should be debugged or not.
};



} // namespace vgUI

#endif // #ifndef _VGUI_CANVAS_HPP
