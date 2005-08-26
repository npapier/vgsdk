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
#include "vgeGL/event/IEventProcessor.hpp"



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
 * - Event handling (listen and process events with event processors).
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
	 * @param size					the size of the window.
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
	 * @brief Called when a new event occurs (@see vgd::event::Listener)
	 * 
	 * and use installed instances of IEventProcessor to process all incoming events.
	 * 
	 * @param event		event to process
	 */
	void onEvent( vgd::Shp<vgd::event::Event> event );

	/**
	 * @brief Installs a new event processor.
	 * 
	 * @param eventProcessor		event processor to install.
	 * @param index					the position where the event processor must be inserted.
	 * 
	 * @pre index <= getNumEventProcessors()
	 */
	void insertEventProcessor( vgd::Shp< ::vgeGL::event::IEventProcessor > eventProcessor, const uint32 index = 0 );
	
	/**
	 * @brief Removes an event processor.
	 * 
	 * @param index					the position of the event processor to be removed.
	 * 
	 * @pre index < getNumEventProcessors()
	 */
	void removeEventProcessor( const uint32 index = 0 );
	
	/**
	 * @brief Removes an event processor.
	 * 
	 * @param eventProcessor		event processor to remove
	 * 
	 * @return true if event processor has been founded and removed, otherwise false.
	 */
	const bool removeEventProcessor( vgd::Shp< ::vgeGL::event::IEventProcessor > eventProcessor );

	/**
	 * @brief Finds index of given event processor.
	 * 
	 * @return returns -1 if not found, otherwise returns a value between 0 and getNumEventProcessor()-1.
	 */
	int32 findEventProcessor( vgd::Shp< ::vgeGL::event::IEventProcessor > eventProcessor ) const;

	/**
	 * @brief Retrives an event processor.
	 * 
	 * @param index					the position of the event processor to get.
	 * 
	 * @pre index < getNumEventProcessors()
	 */
	vgd::Shp< ::vgeGL::event::IEventProcessor > getEventProcessor( const uint32 index = 0 ) const;

	/**
	 * @brief Retrives the number of event processors.
	 * 
	 * @return the number of event processors.
	 */
	const uint32 getNumEventProcessors() const;
	//@}



	/**
	 * @name Ray casting.
	 */
	//@{

	/**
	 * @brief Cast a ray under mouse pointer.
	 * 
	 * @param x  x-coordinate of the mouse pointer
	 * @param y  y-coordinate of the mouse pointer
	 * 
	 * @return the nearest node or a null reference.
	 */
	vgd::node::Node* castRay( const int32 x, const int32 y );
	//@}
	
	

	/**
	 * @name OpenGL context management methods
	 * 
	 * @todo setGLContextCurrent();
	 */
	//@{

	/**
	 * @brief Tests if there is a current OpenGL context.
	 * 
	 * @return true if there is a current OpenGL context, false if not.
	 */
	const bool	isGLContextCurrent() const;

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
	vgd::Shp< vgeGL::engine::Engine >		getGLEngine();
	
	//@}

	

protected:

	/**
	 * @name Private data.
	 */
	//@{

	/**
	 * @brief Boolean value set if initialize() has already been called.
	 */
	bool									m_bCallInitialize;
	
	/**
	 * @brief Main evaluation engine.
	 */
	vgd::Shp< vgeGL::engine::Engine >		m_GLEngine;	


	/**
	 * @brief Typedef for event processor container.
	 */
	typedef vgd::Shp< ::vgeGL::event::IEventProcessor > ElementOfEventProcessorContainer;
	typedef std::vector< ElementOfEventProcessorContainer > EventProcessorContainer;
	
	/**
	 * @brief Event processor container.
	 */
	EventProcessorContainer	m_eventProcessors;
	//@}
};



} // namespace engine

} // namespace vgeGL

#endif //#ifndef _VGEGL_ENGINE_SCENEMANAGER_H
