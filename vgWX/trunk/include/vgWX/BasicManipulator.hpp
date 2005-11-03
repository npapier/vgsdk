// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGWX_BASICMANIPULATOR_H
#define _VGWX_BASICMANIPULATOR_H

#include <vgd/node/TransformDragger.hpp>
#include <wx/defs.h>

#include "vgWX/BasicViewer.hpp"
#include "vgWX/event/Keyboard.hpp"
#include "vgWX/event/Mouse.hpp"
#include "vgWX/vgWX.hpp"



namespace vgWX
{

/**
 * @brief A basic view to be able to manipulate interactively vgsdk graphics.
 * 
 * This class provides :
 * 
 * - a basic interface (with keyboard and mouse) for manipulating the whole scene :
 * 	- Rotation around the center of the scene : Hold down the left button of the mouse and move the mouse 
 * 		simultaneously.
 * 	- Translation on the screen plane : Hold down the left button of the mouse, press the Ctrl key and move the mouse 
 * 		simultaneously.
 * 	- Translation orthogonal to the screen plane : Hold down the Shift key, press the left button of the mouse and
 * 		move the mouse from top to bottom or use the wheel on the mouse.
 * 	- Rotation around an axis orthogonal to the screen plane : Hold down the Shift and Crlk key, press the left button
 * 		of the mouse and move the mouse from left to right.
 * 	- View the whole scene : Press the 'v' key.
 * 	- Keys 'Up', 'Down', 'Left' and 'Right' could be used instead of the mouse.
 *		- Press keys 'b' or 'B' to render respectively to 20, 100 frames directly (usage: benchmarking).
 * 
 * - a new vgd::node::TransformDragger node in the \c setup group named TRANSFORMDRAGGER_SCENE.
 * 
 * @ingroup g_vgWXGroup
 * 
 * @todo Add timer service ?
 * @todo Manipulation mode should be customizable.
 */
struct VGWX_API BasicManipulator : public BasicViewer
{
	/**
	 * @name Constructors/Destructor.
	 */
	//@{

	/**
	 * @brief Construct a BasicManipulator with its own OpenGL context.
	 * 
	 * @param	pParent	A pointer to the parent window.
	 */
	BasicManipulator(
					wxWindow *parent,
					const wxString& name = _T("BasicManipulator"),
					const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
					long style = 0,
					int* gl_attrib = NULL,
					const wxWindowID id = -1 );

	/**
	 * @brief Construct a BasicManipulator with its own OpenGL context, but that share OpenGL objects with another(s) 
	 * Canvas.
	 * 
	 * @param	pParent		A pointer to the parent window.
	 */
	BasicManipulator(
					wxWindow *parent,
					Canvas *pSharedCanvas,
					const wxString& name = _T("BasicManipulator"),
					const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
					long style = 0,
					int* gl_attrib = NULL,
					const wxWindowID id = -1 );
					
	/**
	 * @brief Destructor.
	 */
	~BasicManipulator();
	//@}



	/**
	 * @name Accessors to scene graph.
	 */
	//@{
	
	/**
	 * @brief Returns the transformation node applied to the whole scene.
	 * 
	 * @return the transformation node.
	 */
	vgd::Shp< vgd::node::TransformDragger >		getSceneTransformation();

	//@}
	
	
	
	/**
	 * @name Overriden methods.
	 */
	//@{

	/**
	 * @brief Overriden method.
	 */
	void viewAll();
	
	/**
	 * @brief Overriden method.
	 */
	void onEvent( vgd::Shp<vgd::event::Event> event );
	//@}



	/**
	 * @name Useful methods.
	 */
	//@{
	
	//@}



protected:
	/**
	 * @name wxWidgets events processing methods.
	 */
	//@{
//	/**
//	 * @brief Handles \c EVT_MOUSE_EVENTS.
//	 */
//	void OnMouseEvent		(wxMouseEvent& event);

	/**
	 * Handles \c EVT_CHAR events.
	 */
	void OnChar( wxKeyEvent& event );
	//@}


	
protected:
	DECLARE_EVENT_TABLE();
	


	/**
	 * @name Members for events.
	 */
	//@{
	vgWX::event::Keyboard	m_keyboard;
	vgWX::event::Mouse		m_mouse;
	//@}



private:
	/**
	 * @brief The transformation applyed to the whole scene.
	 */
	 vgd::Shp< vgd::node::TransformDragger >		m_sceneTransform;
};



} // namespace vgWX

#endif // #ifndef _VGWX_BASICMANIPULATOR_H
