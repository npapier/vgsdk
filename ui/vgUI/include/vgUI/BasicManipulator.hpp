// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGUI_BASICMANIPULATOR_HPP
#define _VGUI_BASICMANIPULATOR_HPP

#include <vgd/node/TransformDragger.hpp>

#include "vgUI/BasicViewer.hpp"



namespace vgUI
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
 * - a default lighting
 *
 * - a default frame buffer clearing node
 *
 * @ingroup g_vgUIGroup
 *
 * @todo Add timer service ?
 * @todo Manipulation mode should be customizable.
 */
struct VGUI_API BasicManipulator : public BasicViewer
{
	/**
	 * @name Constructors
	 */
	//@{
	/**
	 * @brief	Constructs a BasicManipulator with its own OpenGL context.
	 */
	BasicManipulator();

	/**
	 * @brief	Constructs a BasicManipulator with its own OpenGL context, but that share OpenGL objects with another(s) Canvas.
	 *
	 * @param	parent	a pointer to the parent window.
	 */
	BasicManipulator( const vgUI::Canvas * pSharedCanvas );
	//@}



	/**
	 * @name Accessors to scene graph
	 */
	//@{

	// Overridden BasicViewer::setScene()
	void setScene( const vgd::Shp< vgd::node::Group > );

	/**
	 * @brief Returns the transformation node applied to the whole scene.
	 *
	 * @return the transformation node.
	 */
	vgd::Shp< vgd::node::TransformDragger > getSceneTransformation();
	//@}



	/**
	 * @name Overriden methods.
	 */
	//@{
	/**
	 * @brief Overriden method.
	 */
	void viewAll( const CameraDistanceHints cameraDistance = CAMERA_DISTANCE_HINTS_DEFAULT );

	/**
	 * @brief Overriden method.
	 */
	void onEvent( vgd::Shp<vgd::event::Event> event );
	//@}



private:
	 vgd::Shp< vgd::node::TransformDragger > m_sceneTransform;	///< The transformation applyed to the whole scene.
};



} // namespace vgUI

#endif // #ifndef _VGUI_BASICMANIPULATOR_HPP
