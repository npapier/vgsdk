// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, 2009, 2011, 2012, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGEGL_ENGINE_SCENEMANAGER_HPP
#define _VGEGL_ENGINE_SCENEMANAGER_HPP

#include <vgd/event/DeviceManager.hpp>
#include <vgd/event/MouseButtonEvent.hpp>
#include <vge/engine/SceneManager.hpp>
#include <vgm/Triangle.hpp>

#include "vgeGL/event/IEventProcessor.hpp"
#include "vgeGL/itf/IUnderlay.hpp"
#include "vgeGL/technique/RayCasting.hpp"

namespace vgd { namespace node { struct LayerPlan; struct VertexShape; } }
namespace vgeGL { namespace event { struct TimerEventProcessor; } }



namespace vgeGL
{

namespace engine
{



/**
 * @brief Properties of an OpenGL context
 */
struct VGEGL_API GLContextProperties
{
	/**
	 * @brief Default constructor
	 *
	 * @param enableQuadBufferStereo	true if quad buffer stereo (for stereoscopic rendering) is enabled, false otherwise.
	 */
	GLContextProperties( const bool enableQuadBufferStereo = false )
	:	m_enableQuadBufferStereo( enableQuadBufferStereo )
	{}

	const bool enableQuadBufferStereo() const { return m_enableQuadBufferStereo; }

	private:
	bool m_enableQuadBufferStereo;
};



/**
 * @brief Bridge between the scene graph and the GUI toolkit.
 * 
 * This class provides some methods to :
 * 
 * - To do your own setup (see initialize()).
 * - Specialized paint and resize rendering methods to link the rendering with the scene graph. 
 * 	- The first one, named \c paint is called by gtkmm inside method on_expose_event()  or by wxWidgets inside method OnPaint(), render the scene graph from the root 
 * 		node and optionnally update all bounding box in the scene graph. 
 * 	- The second method, named \c resize is called by gtkmm inside method on_configure_event() or by wxWidgets inside method OnSize(), should at least configure the 
 * 		camera node. By default nothing is done in it, because there is no vgd::node::Camera in the scene graph.
 * 		But if you derived this class and add a Camera node, you should write this piece of code.
 * - Event handling (listen and process events with event processors).
 * - A time base animation system. @ref g_time
 * - Casts ray under the mouse cursor and in the scene.
 * - Renders an overlay after the rendering of the scene graph. The typical use case is to draw a logo over the GUI window.
 * - Renders an underlay just after the clearing of the whole framebuffer in the MultiMain technique. This layer is only used by the MultiMain technique.
 *
 * @ingroup g_layerplan
 * @ingroup g_rayCasting
 */
struct VGEGL_API SceneManager : public vge::engine::SceneManager, public vgd::event::DeviceManager, public vgeGL::itf::IUnderlay
{
	/**
	 * @name Constructors/Destructor
	 */
	//@{

	/**
	 * @brief Constructor.
	 * 
	 * @param engine		reference on the engine that must be used by the scene manager.
	 */
	SceneManager( vgd::Shp< vgeGL::engine::Engine > engine );

	//@}



	/**
	 * @name Rendering methods
	 */
	//@{

	/**
	 * @brief Feel free to perform your own initialization in this method.
	 * 
	 * For example, you can construct your scene graph.
	 * 
	 * @remarks This method is called automatically before the first rendering was done by paint()/resize(). All 
	 * components needed for vgsdk are already initialized (components are OpenGL, glc/gle and vge* modules...).
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
	 * @name Events
	 */
	//@{

	/**
	 * @brief Called when a new event occurs
	 * 
	 * and use installed instances of IEventProcessor to process all incoming events.
	 * 
	 * @param event		event to process
	 * 
	 * @see vgd::event::Listener
	 */
	void onEvent( vgd::Shp<vgd::event::Event> event );

	/**
	 * @brief Installs a new event processor.
	 * 
	 * @param eventProcessor		event processor to install.
	 * @param index					the position where the event processor must be inserted.
	 * 
	 * @pre 0 <= index <= getNumEventProcessors()
	 */
	void insertEventProcessor( vgd::Shp< ::vgeGL::event::IEventProcessor > eventProcessor, const int32 index = 0 );

	/**
	 * @brief Installs a new event processor at a position relative to the the first encountered event processor of the 
	 * given type or that inherits of the given type.
	 * 
	 * If the event processor, named typeOfEventProcessor, is not founded, then the insertion is done at the end of the 
	 * container.
	 * 
	 * @pre the position where insertion would occurred must be valid
	 * 
	 * @param eventProcessor		event processor to install
	 * @param offset				the relative position
	 */
	template< typename typeOfEventProcessor >
	void insertRelativeEventProcessor( vgd::Shp< ::vgeGL::event::IEventProcessor > eventProcessor, const int32 offset = 0 )
	{
		const int32 index = findEventProcessor< typeOfEventProcessor >();
		
		if ( index == getNumEventProcessors() )
		{
			pushBackEventProcessor( eventProcessor );
		}
		else
		{
			insertEventProcessor( eventProcessor, index + offset );
		}
	}

	/**
	 * @brief Installs a new event processor
	 * 
	 * Installs a new event processor at the end of the event processors container.
	 * 
	 * @param eventProcessor		event processor to install.
	 */
	void pushBackEventProcessor( vgd::Shp< ::vgeGL::event::IEventProcessor > eventProcessor );

	/**
	 * @brief Removes an event processor.
	 * 
	 * @param index		the position of the event processor to be removed.
	 * 
	 * @pre 0 <= index < getNumEventProcessors()
	 */
	void removeEventProcessor( const int32 index = 0 );

	/**
	 * @brief Removes an event processor at a position relative to the the first encountered event processor of the 
	 * given type or that inherits of the given type.
	 * 
	 * If the event processor, named typeOfEventProcessor, is not founded, then nothing is done.
	 * 
	 * @pre the position where removal would occurred must be valid
	 * 
	 * @param offset				the relative position
	 * @return true if event processor has been founded and removed, otherwise false.
	 */
	template< typename typeOfEventProcessor >
	const bool removeRelativeEventProcessor( const int32 offset = 0 )
	{
		const int32 index = findEventProcessor< typeOfEventProcessor >();
		
		if ( index != getNumEventProcessors() )
		{
			removeEventProcessor( index + offset );

			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	 * @brief Removes an event processor.
	 * 
	 * Removes the event processor at the end of the event processors container.
	 * 
	 * @pre getNumEventProcessors() >= 1
	 */
	void popBackEventProcessor();

	/**
	 * @brief Removes an event processor.
	 * 
	 * @param eventProcessor		event processor to remove
	 * 
	 * @return true if event processor has been founded and removed, otherwise false.
	 */
	const bool removeEventProcessor( vgd::Shp< ::vgeGL::event::IEventProcessor > eventProcessor );
	//const bool removeEventProcessor( ::vgeGL::event::IEventProcessor * eventProcessor ); ///< @todo

	/**
	 * @brief Finds index of given event processor.
	 * 
	 * @return returns getNumEventProcessors() if not found, otherwise returns a value 
	 * between 0 and getNumEventProcessor()-1.
	 */
	const int32 findEventProcessor( ::vgeGL::event::IEventProcessor * eventProcessor ) const;

	/**
	 * @copydoc findEventProcessor(::vgeGL::event::IEventProcessor*)const
	 */
	const int32 findEventProcessor( vgd::Shp< ::vgeGL::event::IEventProcessor > eventProcessor ) const;

	/**
	 * @brief Finds index for the first event processor of the given type or that inherits of the given type.
	 * 
	 * @return returns getNumEventProcessors() if not found, otherwise returns a value 
	 * between 0 and getNumEventProcessor()-1.
	 */
	template < typename typeOfEventProcessor >
	const int32 findEventProcessor() const
	{
		int32 retVal = 0;
		
		for(	EventProcessorContainer::const_iterator	i	= m_eventProcessors.begin(),
														iEnd= m_eventProcessors.end();
				i != iEnd;
				++i )
		{
			ElementOfEventProcessorContainer currentEventProcessor = *i;
			
			if ( vgd::dynamic_pointer_cast< typeOfEventProcessor >(currentEventProcessor) != 0 )
			{
				return retVal;
			}
			
			++retVal;
		}
		
		return getNumEventProcessors();
	}

	/**
	 * @brief Retrives an event processor.
	 * 
	 * @param index		the position of the event processor to get
	 * 
	 * @pre 0 <= index < getNumEventProcessors()
	 */
	vgd::Shp< ::vgeGL::event::IEventProcessor > getEventProcessor( const int32 index = 0 ) const;
	
	/**
	 * @brief Retrives an event processor.
	 * 
	 * @param index		the position of the event processor to get
	 * 
	 * @pre 0 <= index < getNumEventProcessors()
	 */
	template< typename typeOfEventProcessor >
	vgd::Shp< typeOfEventProcessor > getEventProcessor( const int32 index = 0 ) const
	{
		return ( vgd::dynamic_pointer_cast< typeOfEventProcessor >( getEventProcessor(index) ) );
	}

	/**
	 * @brief Retrives the number of event processors.
	 * 
	 * @return the number of event processors.
	 */
	const int32 getNumEventProcessors() const;

	//@}



	/**
	 * @name Timer event processor methods
	 */
	//@{

	/**
	 * @brief Returns the default timer event processor.
	 *
	 * @return the timer event processor.
	 */
	vgd::Shp< ::vgeGL::event::TimerEventProcessor > getTimerEventProcessor();
	//@}



	/**
	 * @name Ray casting
	 */
	//@{

	/**
	 * @brief Cast a ray under mouse pointer
	 * 
	 * @param x  x-coordinate of the mouse pointer
	 * @param y  y-coordinate of the mouse pointer
	 * 
	 * @return the nearest hit or a null reference.
	 * 
	 * @remarks The returned hit reference is valid until the next ray casting.
	 */
	const vgeGL::basic::Hit* castRayForHit( const int32 x, const int32 y );

	/**
	 * @brief Cast a ray in the scene
	 * 
	 * @param raySourceW				starting point of the ray (in world space)
	 * @param rayDirectionW				direction of the ray (in world space)
	 * 
	 * @return the nearest hit or a null reference.
	 * 
	 * @remarks The returned hit reference is valid until the next ray casting.
	 */
	const vgeGL::basic::Hit* castRayForHit( const vgm::Vec3f raySourceW, const vgm::Vec3f rayDirectionW );



	/**
	 * @brief Cast a ray under mouse pointer
	 * 
	 * @param x  x-coordinate of the mouse pointer
	 * @param y  y-coordinate of the mouse pointer
	 * 
	 * @return the nearest node or a null reference.
	 *
	 * @remark Helper using castRayForHit(x,y)
	 */
	vgd::node::Node* castRay( const int32 x, const int32 y );

	/**
	 * @brief Cast a ray under mouse pointer
	 *
	 * @param x							x-coordinate of the mouse pointer
	 * @param y							y-coordinate of the mouse pointer
	 *
	 * @param oABCP						the nearest collided triangle, the three indices of the triangles (in the returned shape arrays) and the hit point P with barycentric coordinates (u,v) in (A, AB, BC). A is a local origin.
	 *
	 * @return the nearest node if ray casting hit a triangle, otherwise a null reference
	 *
	 * @remark Helper using castRay(x,y) and vgAlg::intersect::getTriangle()
	 */
	vgd::node::VertexShape * castRay( const int32 x, const int32 y, vgm::TriangleExt& oABCP );

	/**
	 * @brief Cast a ray in the scene
	 *
	 * @param raySourceW				starting point of the ray (in world space)
	 * @param rayDirectionW				direction of the ray (in world space)
	 *
	 * @param oABCP						the nearest collided triangle, the three indices of the triangles (in the returned shape arrays) and the hit point P with barycentric coordinates (u,v) in (A, AB, BC). A is a local origin.
	 *
	 * @return the nearest node if ray casting hit a triangle, otherwise a null reference
	 *
	 * @remark Helper using castRayForHit(raySourceW,rayDirectionW) and vgAlg::intersect::getTriangle()
	 */
	vgd::node::VertexShape * castRay( const vgm::Vec3f raySourceW, const vgm::Vec3f rayDirectionW, vgm::TriangleExt& oABCP );



	/**
	 * @brief Returns getRayCastingTechnique().getNearestHitNode()
	 */
	vgd::node::VertexShape * getNearestHitNode();

	/**
	 * @brief Returns getRayCastingTechnique).getNearestHit()
	 */
	const vgeGL::basic::Hit getNearestHit();

	/**
	 * @brief Returns a reference on the ray casting technique.
	 * 
	 * This reference could be used to access to the result of the last ray casting.
	 */
	const vgeGL::technique::RayCasting& getRayCastingTechnique() const;
	vgeGL::technique::RayCasting& getRayCastingTechnique();

	//@}



	/**
	 * @name OpenGL context management methods
	 *
	 * @todo setGLContextCurrent();
	 */
	//@{


	/**
	 * @brief Sets the requested properties for the OpenGL context
	 *
	 * @param properties	OpenGL context properties requested
	 *
	 * @remark	Called this method before OpenGL context has been created (see startOpenGLContext()/startVGSDK()), otherwise
	 * 			it will be ignored
	 */
	void setRequestedGLContextProperties( const GLContextProperties properties );

	/**
	 * @brief Returns the current properties of the OpenGL context allocated
	 *
	 * @param properties	the OpenGL context properties allocated (if any)
	 *
	 * @return true if an OpenGL context has been already allocated and \c properties output parameter is assigned, false otherwise
	 */
	const bool getGLContextProperties( GLContextProperties& properties ) const;


	/**
	 * @brief Tests if there is a current OpenGL context.
	 * 
	 * @return true if there is a current OpenGL context, false if not.
	 */
	const bool isGLContextCurrent() const;

	//@}



	/**
	 * @name Accessors to some vgsdk objects
	 */
	//@{

	/**
	 * @brief Returns the main evaluation engine.
	 * 
	 * @return the vgeGL engine.
	 */
	vgd::Shp< vgeGL::engine::Engine > getGLEngine();
	
	/**
	 * @brief Returns the main evaluation engine.
	 * 
	 * @return the vgeGL engine.
	 */
	vgd::Shp< vgeGL::engine::Engine > getGLEngine() const;
	
	//@}
	
	
	
	/**
	 * @name Accessors to technique used by paint()
	 * 
	 * Design Pattern \c Strategy
	 */
	//@{

	/**
	 * @brief Returns the current vgeGL technique used by paint method.
	 * 
	 * @return the current vgeGL technique used by paint method
	 */
	vgd::Shp< vgeGL::technique::Technique > getPaintTechnique() const;
	
	/**
	 * @brief Sets the current vgeGL technique used by paint method.
	 * 
	 * @param technique		the current vgeGL technique that must be used by paint method.
	 */
	void setPaintTechnique( vgd::Shp< vgeGL::technique::Technique > technique );

	//@}


	/**
	 * @name Overlay/underlay
	 */
	//@{

	/**
	 * @brief Sets the current overlay.
	 * @param overlay	the layer plan to use for overlay
	 *
	 * @ingroup g_layerplan	 
	 */
	void setOverlay( vgd::Shp< vgd::node::LayerPlan > overlay );

	/**
	 * @brief Returns the current overlay.
	 *
	 * @return the installed overlay
	 *
	 * @ingroup g_layerplan	 
	 */
	vgd::Shp< vgd::node::LayerPlan > getOverlay();


	/**
	 * @brief Sets the current underlay.
	 * @param underlay	the layer plan to use for underlay
	 *
	 * @see vgeGL::technique::MultiMain
	 *
	 * @ingroup g_layerplan	 
	 */
	void setUnderlay( vgd::Shp< vgd::node::LayerPlan > underlay );

	/**
	 * @brief Returns the current underlay.
	 *
	 * @return the installed underlay
	 *
	 * @see vgeGL::technique::MultiMain
	 *
	 * @ingroup g_layerplan	 
	 */
	vgd::Shp< vgd::node::LayerPlan > getUnderlay();
	//@}


protected:

	/**
	 * @name Private data
	 */
	//@{

	/**
	 * @brief Main evaluation engine.
	 */
	vgd::Shp< vgeGL::engine::Engine >		m_GLEngine;


	GLContextProperties						m_requestedGLContextProperties;

	bool									m_hasCurrentGLContextProperties;
	GLContextProperties						m_currentGLContextProperties;



	/**
	 * @brief The current vgeGL technique that must be used by paint method.
	 */
	vgd::Shp< vgeGL::technique::Technique >	m_paintTechnique;

	/**
	 * @brief An instance of raycasting technique.
	 */
	vgeGL::technique::RayCasting			m_rayCasting;


	/**
	 * @brief Boolean value set if initialize() has already been called.
	 */
	bool									m_bCallInitialize;


	/**
	 * @brief Typedef for event processor container.
	 */
	typedef vgd::Shp< ::vgeGL::event::IEventProcessor >		ElementOfEventProcessorContainer;
	typedef std::vector< ElementOfEventProcessorContainer >	EventProcessorContainer;
	
	EventProcessorContainer	m_eventProcessors;		///< event processor container

	vgd::Shp< ::vgeGL::event::TimerEventProcessor > m_timerEventProcessor;
	//@}

	vgd::Shp< vgd::node::LayerPlan > m_overlay;		///< reference to the current overlay
	vgd::Shp< vgd::node::LayerPlan > m_underlay;	///< reference to the current underlay
};



} // namespace engine

} // namespace vgeGL

#endif //#ifndef _VGEGL_ENGINE_SCENEMANAGER_HPP
