// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_ENGINE_SCENEMANAGER_H
#define _VGEGL_ENGINE_SCENEMANAGER_H

#include <vgd/event/Listener.hpp>
#include <vge/engine/SceneManager.hpp>
#include "vgeGL/vgeGL.hpp"
#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{
	
namespace engine
{



/**
 * @brief Bridge between the scene graph and the GUI toolkit.
 * 
 * This class provides some methods to :
 * 
 * - To do your own setup (see initialize()).
 * - Specialized paint and resize rendering methods to link the rendering with the scene graph. 
 * 	- The first one, named \c paint is called by the vgWX::Canvas::OnPaint(), render the scene graph from the root 
 * 		node and optionnally update all bounding box in the scene graph. 
 * 	- The second method, named \c resize is called by the vgWX::Canvas::OnSize(), should at least configure the 
 * 		camera node. By default nothing is done in it, because there is no vgd::node::Camera in the scene graph.
 * 		But if you derived this class and add a Camera node, you should write this piece of code.
 * - Event handling (listen and process events).
 */
struct VGEGL_API SceneManager : public vge::engine::SceneManager, public vgd::event::Listener
{
	/**
	 * @name Constructors/Destructor.
	 */
	//@{
	
	/**
	 * @brief Constructor.
	 * 
	 * @param pEngine		reference on the engine that must be used by the scene manager.
	 */
	SceneManager( vgd::Shp< vgeGL::engine::Engine > pEngine );
	
	//@}


	
	/**
	 * @name Rendering methods.
	 */
	//@{

	/**
	 * @brief Feel free to perform your own initialization in this method.
	 * 
	 * For example, you can construct your scene graph.
	 * 
	 * @remarks This method is called automatically before the first rendering was done by paint()/resize(). All 
	 * components needed for vgsdk are already initialized (components are OpenGL, gle and vge* modules...).
	 */
	virtual void initialize();

	/**
	 * @brief Render the scene graph from the root node and update the bounding box.
	 * 
	 * This method is called when a window's contents needs to be repainted.
	 * 
	 * @param size						the size of the window.
	 * @param bUpdateBoundingBox	true to update bounding box in the scene graph, false to do nothing.
	 */
	 virtual void paint( const vgm::Vec2i size, const bool bUpdateBoundingBox );
	 
	 /**
	  * @brief Called when the window is resized.
	  *
	  * @param size		the size of the window.
	  * 
	  * @code
	  * // Example of work that could be done in the method.
	  * // with m_camera a vgd::Shp< vgd::node::Camera > node.
	  * vgm::MatrixR matrix;
	  * matrix.setPerspective(
	  * 				45.f,
	  * 				size[0]/size[1],
	  * 				1.0,
	  * 				1000.0 );
	  * m_camera->setMatrix( matrix );
	  * m_camera->setViewport( 
	  * 	vgm::Rectangle2i( 0, 0, size.GetWidth(), size.GetHeight() )
	  * 		);
	  * @endcode
	  */
	virtual void resize( const vgm::Vec2i size );
	
	//@}



	/**
	 * @name Events.
	 */
	//@{
	
	/**
	 * @brief Process the given event by using service ProcessEvent on the scene graph
	 */
	void onEvent( vgd::Shp<vgd::event::Event> event );
	
	//@}



	/**
	 * @name Accessors to some vgsdk objects.
	 */
	//@{

	/**
	 * @brief Returns the main evaluation engine.
	 * 
	 * @return the vge engine.
	 */
	vgd::Shp< vgeGL::engine::Engine >			getGLEngine();
	
	//@}

	

protected:

	/**
	 * @name Private data.
	 */
	//@{

	/**
	 * @brief Boolean value set if initialize() has already been called.
	 */
	bool												m_bCallInitialize;
	
	/**
	 * @brief Main evaluation engine.
	 */
	vgd::Shp< vgeGL::engine::Engine >		m_GLEngine;	
	
	//@}
};



} // namespace engine

} // namespace vgeGL

#endif //#ifndef _VGEGL_ENGINE_SCENEMANAGER_H
