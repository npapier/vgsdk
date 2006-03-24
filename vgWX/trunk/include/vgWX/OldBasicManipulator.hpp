// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGWX_OLDBASICMANIPULATOR_HPP
#define _VGWX_OLDBASICMANIPULATOR_HPP

#include <vgd/node/Transform.hpp>
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
 * - a new vgd::node::Transformation node in the \c setup group named TRANSFORM_SCENE.
 * 
 * @ingroup g_vgWXGroup
 * 
 * @todo Add timer service ?
 * @todo Manipulation mode should be customizable.
 */
struct VGWX_API OldBasicManipulator : public BasicViewer
{
	/**
	 * @name Constructor/Destructor.
	 */
	//@{
	
	/**
	 * @brief Constructor.
	 * 
	 * @param	pParent	A pointer to the parent window.
	 */
	OldBasicManipulator(
					wxWindow *parent,
					const wxString& name = _T("OldBasicManipulator"),
					const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
					long style = 0,
					int* gl_attrib = NULL,
					const wxWindowID id = -1 );
					
	/**
	 * @brief Destructor.
	 */
	~OldBasicManipulator();
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
	vgd::Shp< vgd::node::Transform >		getSceneTransformation();

	//@}
	
	
	
	/**
	 * @name Overrided methods.
	 */
	//@{

	/**
	 * @brief Overrided method.
	 */
	void viewAll();
	
	/**
	 * @brief Overrided method.
	 */
	void onEvent( vgd::Shp<vgd::event::Event> event );
	//@}



	/**
	 * @name Useful methods.
	 */
	//@{
	
	/**
	 * @todo Add more methods from ktvs/src/view/Abstract.cpp, move to another file/class
	 * 
	 * @todo Doc.
	 * @todo work only for simple scene graph (1 camera node).
	 */
	const bool ConvertVectorsFromWindowToObject(	vgm::Vec3f& oLeftToRightO,
																vgm::Vec3f& oUpToDownO,
																vgm::Vec3f& oNearToFarO );
	//@}



protected:
	/**
	 * @name wxWidgets events processing methods.
	 */
	//@{
	/**
	 * @brief Handles \c EVT_MOUSE_EVENTS.
	 */
	void OnMouseEvent		(wxMouseEvent& event);

	/**
	 * Handles \c EVT_CHAR events.
	 */
	void OnChar( wxKeyEvent& event );
	//@}


	
protected:
	DECLARE_EVENT_TABLE();
	
	/**
	 * @name Normal Manipulation Mode data.
	 */
	//@{
	
	/**
	 * @brief Previous mouse coordinates.
	 */
	vgm::Vec2f	m_previousMouseCoord;

	//@}



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
	 vgd::Shp< vgd::node::Transform >		m_sceneTransform;
};



} // namespace vgWX

#endif // #ifndef _VGWX_OLDBASICMANIPULATOR_HPP
