// VGSDK - Copyright (C) 2004, 2006, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGWX_CANVAS_HPP
#define _VGWX_CANVAS_HPP

#include <wx/wx.h>

#include <vgeGL/engine/SceneManager.hpp>

#include <wx/glcanvas.h>	// this header file include GL.h like vgeGL/engine/SceneManager.hpp and gle.hpp, but on 
							// MacOSX it doesn't take the /usr/X11R6/include/GL/gl.h one, so typedef on OpenGL 
							// extensions are not defined !!!

#include "vgWX/vgWX.hpp"



class wxMenu;



namespace vgWX
{

/**
 * @brief A basic canvas for displaying vgsdk graphics.
 * 
 * This class do some cool things internally :
 * 
 * - Use the vgeGL::engine::SceneManager to link GUI and the scene graph.
 * - Initialize OpenGL and its extensions (with gle) to being used by vgsdk.
 * - Report OpenGL errors before and after rendering (OnPaint/paint, OnSize/resize, initialize()).
 * 
 *  This class has some methods to :
 * 
 * - Provide a contextual menu to be able to write the scene graph in dot file and change things like drawing 
 * 	style (vgd::node::DrawStyle), the lighting model (vgd::node::LightModel) and so on. It is disabled by default.
 * - do some stuffs when the application becomes idle (see onIdle method)
 * 
 * @ingroup g_vgWXGroup
 */
struct VGWX_API Canvas : public wxGLCanvas, public vgeGL::engine::SceneManager
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
	 * @name Constructors/Destructor
	 */
	//@{
	
	/**
	 * @brief Construct a Canvas with its own OpenGL context.
	 * 
	 * @param parent	A pointer to the parent window.
	 * 
	 * @pre	getCanvasCount() == 0
	 * @post	getCanvasCount() == 1
	 */
	Canvas(	wxWindow *parent, 
			const wxString& name = _T("vgsdkCanvas"),
			const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
			long style = 0,
			int* gl_attrib = NULL,
			const wxWindowID id = -1 );
				
	/**
	 * @brief Construct a Canvas with its own OpenGL context, but that share OpenGL objects with another(s) Canvas.
	 * 
	 * @param	parent		A pointer to the parent window.
	 * 
	 * @pre	getCanvasCount() >= 1
	 */
	Canvas(	wxWindow *parent,
			Canvas *pSharedCanvas,
			const wxString& name = _T("vgsdkCanvas"),
			const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
			long style = 0,
			int* gl_attrib = NULL,
			const wxWindowID id = -1 );
	
	/**
	 * @brief Default destructor
	 */
	virtual ~Canvas();
	//@}



	/**
	 * @name Repaint management
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



	/**
	 * @name Contextual menu methods
	 */
	//@{
	
	/**
	 * @brief Enable/disable contextual menu (draw when user right-click with the mouse on the window area).
	 * 
	 * @param bEnabled true to enable the contextual menu, false to disable it.
	 */
	void enableContextualMenu( const bool bEnabled );
	
	/**
	 * @brief Test the contextual menu state.
	 * 
	 * @return true if contextual menu is enabled, false if it is disabled.
	 */
	const bool isContextualMenuEnabled() const;
	
	/**
	 * @brief Construct the contextual menu.
	 * 
	 * @remarks A ray casting must have been done just before calling this method. So informations about ray casting
	 * could be found from getRayCastingTechnique()
	 */
	virtual wxMenu *createContextualMenu() const;

	//@}



	// Overridden
	void paint( const vgm::Vec2i size, const bool bUpdateBoundingBox );



	/**
	 * @brief This method is called when the application becomes idle.
	 * 
	 * @return true to request more idle events (a continuous stream of idle events), false to receive only one idle event.
	 * 
	 * @todo vgd::node::IdleSensor
	 */
	virtual const bool onIdle();



	// Overrides wxWidgets method
	bool Destroy();

	/**
	 * @name wxWidgets events processing methods
	 */
	//@{
private:
	DECLARE_EVENT_TABLE();

	/**
	 * @brief Handles \c EVT_PAINT events.
	 */
	void OnPaint( /*const*/ wxPaintEvent& event );

	/**
	 * Handles \c EVT_SIZE events.
	 */
	void OnSize( /*const*/ wxSizeEvent& event );

	/**
	 * @brief Handles	\c EVT_ERASE_BACKGROUND events.
	 */
	void OnEraseBackground( /*const*/ wxEraseEvent& event );



	/**
	 * @brief Handles \c EVT_RIGHT_UP
	 */
	void OnRightUp( wxMouseEvent& event );

	/**
	 * @brief Handles wxMenuEvent.
	 */
	void OnCtxMenu( wxCommandEvent& event );



	/**
	 * @brief Handles wxIdleEvent.
	 */
	void OnIdle( wxIdleEvent& event );



	/**
	 * @brief Handles @c EVT_ENTER_WINDOW.
	 */
	//void OnEnterWindow		( wxMouseEvent& event );

	/**
	 * @brief Handles @c EVT_KILL_FOCUS.
	 */
	//void OnKillFocus( wxFocusEvent& event );

	/**
	 * @brief Handle @c EVT_SET_FOCUS.
	 */
	//void OnSetFocus( wxFocusEvent& event );

	//@}



	/**
	 * @name Members for OpenGL/gle/vgeGL initialization
	 */
	//@{
	
	/**
	 * @brief Returns the number of instance of this class.
	 * 
	 * @return the canvas count
	 */
	const uint32 getCanvasCount() const;
	
	/**
	 * @brief Returns the shared canvas that have been used to initialize the current canvas.
	 * 
	 * @return	the shared canvas that have been used to initialize the current canvas or
	 * 			null if the canvas has been construct without another one.
	 */
	Canvas * getSharedCanvas() const;

protected:
	/**
	 * @brief Activate the OpenGL rendering context and initialize vgsdk (gle and vgeGL) if needed.
	 * 
	 * @return true if vgsdk and OpenGL are enabled, false otherwise.
	 *
	 * @remarks OpenGL context must be already initialized.
	 */
	bool			enableVGSDK();
private:

	/**
	 * @brief Instance count of this class.
	 */
	static uint32				m_canvasCount;

	/**
	 * @brief	the shared canvas that have been used to initialize the current canvas or
	 * 			null if the canvas has been construct without another one.
	 */
	Canvas *					m_sharedCanvas;

	/**
	 * @brief Default OpenGL attributes for VGSDK.
	 */
	static int					m_vgsdk_attrib[];

	/**
	 * @brief A value from GleLogSystem enumeration to specify the log system used by gle library.
	 */
	static GleLogSystem			m_gleLogSystem;

	/**
	 * @brief The gle.txt file
	 */
	static std::ofstream		m_gleLogFile;

	/**
	 * @brief Returns the output stream associated to the gle log system.
	 * 
	 * @return the output stream
	 */
	static std::ostream* getGleOutputStream();
	
	/**
	 * @brief gle main object to be able to access OpenGL extensions.
	 */
	gle::OpenGLExtensionsGen	m_gleContext;

	/**
	 * @brief Boolean value set if initializeVGSDK() has already been called (for all instances).
	 * 
	 * @todo FIXME : remove me : only here because Sharing OGL context is not really done (only OGL objects are shared).
	 */
	static bool					m_bGlobalInitializedVGSDK;

	/**
	 * @brief Boolean value set if initializeVGSDK() has already been called for this instance of Canvas.
	 */
	bool						m_bLocalInitializedVGSDK;

	//@}



	/**
	 * @name Members for GUI
	 */
	//@{
	
	bool						m_isContextualMenuEnabled;

	//@}
};



} // namespace vgWX

#endif // #ifndef _VGWX_CANVAS_HPP
