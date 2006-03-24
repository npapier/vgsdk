// VGSDK - Copyright (C) 2004, Nicolas Papier.
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
 * - Provide a contextual menu to be able to change things like drawing style (vgd::node::DrawStyle), the lighting model 
 * 	(vgd::node::LightModel) and so on. It is disabled by default.
 * 
 * @todo Move contextual menu in another place.
 * 
 * @ingroup g_vgWXGroup
 */
struct VGWX_API Canvas : public wxGLCanvas, public vgeGL::engine::SceneManager
{
	/**
	 * @name Constructors/Destructor
	 */
	//@{
	
	/**
	 * @brief Construct a Canvas with its own OpenGL context.
	 * 
	 * @param	pParent		A pointer to the parent window.
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
	 * @param	pParent		A pointer to the parent window.
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
	 * @brief Destructor.
	 */
	virtual ~Canvas();
	//@}



	/**
	 * @name Contextual menu methods.
	 */
	//@{
	
	/**
	 * @brief Identifier used by the default contextual menu.
	 * 
	 * Don't use the same. Identifier inside [wxID_HIGHEST + 1024,wxID_HIGHEST + 2048] are reserved.
	 */
	enum {
		// DRAWSTYLE
		wxID_CTX_DRAWSTYLE = wxID_HIGHEST + 1024,
		
		wxID_CTX_DRAWSTYLE_NONE,
		wxID_CTX_DRAWSTYLE_POINT,
		wxID_CTX_DRAWSTYLE_FLAT,
		wxID_CTX_DRAWSTYLE_SMOOTH,
		wxID_CTX_DRAWSTYLE_WIREFRAME,
		wxID_CTX_DRAWSTYLE_HIDDEN_LINE,
		wxID_CTX_DRAWSTYLE_FLAT_HIDDEN_LINE,
		wxID_CTX_DRAWSTYLE_SMOOTH_HIDDEN_LINE,
		wxID_CTX_DRAWSTYLE_NEIGHBOUR,

		wxID_CTX_DRAWSTYLE_NORMALLENGTHNEGATIV,
		wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS8,
		wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS4,
		wxID_CTX_DRAWSTYLE_NORMALLENGTH0,
		wxID_CTX_DRAWSTYLE_NORMALLENGTH4,
		wxID_CTX_DRAWSTYLE_NORMALLENGTH8,
		wxID_CTX_DRAWSTYLE_NORMALLENGTHPOSITIV,
		
		wxID_CTX_DRAWSTYLE_SHOWORIENTATION,
		
		wxID_CTX_DRAWSTYLE_NO_BOUNDING_BOX,
		wxID_CTX_DRAWSTYLE_OBJECT_SPACE,
		wxID_CTX_DRAWSTYLE_AA_OBJECT_SPACE,
		wxID_CTX_DRAWSTYLE_OBJECT_AND_AA_OBJECT_SPACE,

		
		// LIGHTMODEL
		wxID_CTX_LIGHTMODEL_MODEL,
		
		wxID_CTX_LIGHTMODEL_MODEL_LIGHTING_OFF,
		wxID_CTX_LIGHTMODEL_MODEL_STANDARD_PER_VERTEX,
		wxID_CTX_LIGHTMODEL_MODEL_STANDARD_PER_PIXEL,

		//wxID_CTX_LIGHTMODEL_AMBIENT

		wxID_CTX_LIGHTMODEL_VIEWER,
		
		wxID_CTX_LIGHTMODEL_TWOSIDED
	};

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
	bool isContextualMenuEnabled() const;
	
	/**
	 * @brief Construct the contextual menu.
	 * 
	 * @param xMouse		x-coordinate for mouse
	 * @param yMouse		y-coordinate for mouse
	 */
	virtual wxMenu *createContextualMenu( const int32 xMouse, const int32 yMouse ) /*const*/;
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
	 * @brief Repaint the window.
	 * 
	 * @param force		set to REFRESH_FORCE to force the repaint even if no changes have been made in the scene graph,
	 * 					or to REFRESH_IF_NEEDED to repaint only when at least one change in the scene graph has occured.
	 * @param sync		set to SYNCHRONOUS to wait the end of the repaint before returning from this method, or
	 * 					to ASYNCHRONOUS to post a paint message to the window and returning without beiing blocked.
	 */
	void refresh( const RefreshType type = REFRESH_IF_NEEDED, const WaitType wait = ASYNCHRONOUS );
	//@}



protected:
	// Overrides
	void paint( const vgm::Vec2i size, const bool bUpdateBoundingBox );

	/**
	 * @brief This sets the window to receive keyboard input.
	 */
	/**
	 * @name wxWidgets events processing methods.
	 */
	//@{

	DECLARE_EVENT_TABLE();

private:	
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
	 * @brief Handles \c EVT_MOUSE_EVENTS.
	 */
	void OnMouseEvent		(wxMouseEvent& event);

	/**
	 * @brief Handles wxMenuEvent.
	 */
	void OnCtxMenu			( wxCommandEvent& event );



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
	 * @name Members for OpenGL/gle/vgeGL initialization.
	 */
	//@{
	
	/**
	 * @brief Returns the number of instance of this class.
	 * 
	 * @return the canvas count
	 */
	uint32 getCanvasCount() const;

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
	 * @brief Default OpenGL attributes for VGSDK.
	 */
	static int					m_vgsdk_attrib[];
	
	// FIXME ???
	static std::ofstream		m_gleLog;

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
	 * @name Members for GUI.
	 */
	//@{
	
	bool						m_isContextualMenuEnabled;

	//@}	
};



} // namespace vgWX

#endif // #ifndef _VGWX_CANVAS_HPP
