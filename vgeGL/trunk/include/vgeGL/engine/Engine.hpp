// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_ENGINE_ENGINE_H
#define _VGEGL_ENGINE_ENGINE_H

#include "vgeGL/vgeGL.hpp"

#include <vge/engine/Engine.hpp>
#include <vge/rc/Manager.hpp>




/**
 * @namespace vgeGL::engine
 * 
 * @brief Engine evaluate scene graph with handlers and take care of OpenGL resources and states.
 * 
 */
namespace vgeGL
{
	
namespace engine
{



/**
 * @brief A specialized OpenGL version of Engine.
 * 
 * @todo Rework on attach() and setToDefaults().
 * 
 * @todo Initialization of multiAttribute nodes is not very smart...
 */
struct VGEGL_API Engine : public vge::engine::Engine
{
	/**
	 * @name Constructor like.
	 */
	//@{
	
	// Overridden
	void reset();
	//@}



	/**
	 * @name Accessors.
	 */
	//@{

	/**
	 * @brief Sets OpenGL state variables to their defaults values.
	 *
	 * \li Lighting computation is enable (use the current lighting parameters to compute the vertex color).
	 * \li Depth test is enable (do depth comparisons and update the depth buffer).
	 * \li Normalization of normals is enable (normal vectors specified with glNormal are scaled to unit length after 
	 * transformation).
	 * 
	 * \li Call the method setToDefaults() for each registered handler.
	 */
	virtual void setToDefaults();

	/**
	 * @brief Gets the OpenGL objects manager.
	 */
	vge::rc::Manager&	getGLManager();
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



	// overridden method
	void resetMatrices();

	/**
	 * @name OpenGL implementations specifics capabilities.
	 */
	//@{
	
	int32 getMaxLights() const;

	int32 getMaxTexUnits() const;
	
	int32 getMaxTexSize() const;

	//@}
	
	/**
	 * @brief Returns current OpenGL viewport.
	 * 
	 * @param viewport	the output viewport
	 */
	void getViewport( vgm::Rectangle2i& viewport ) const;



protected:
	/**
	 * @brief Populate the node registry with duplicate multi attribute nodes (with index>=1).
	 * 
	 * The number of duplication for a kind of multi attribute is generally given by getMaxLights(), getMaxTexUnits()...
	 * in the OpenGL implementations specifics capabilities section.
	 * 
	 * @return true if registry has been populate, false if not.
	 * 
	 * @todo A better method (generic and that work even for new kind of node) to know the max number of multi attribute
	 * nodes of each type.
	 */
	bool populateNodeRegistry();



private:
	/**
	 * @brief Manager for all opengl objects.
	 */
	static vge::rc::Manager		m_glManager;
	
	/**
	 * @brief Used to know if this instance is the first one or not (for doiing some initializations).
	 */
	static bool					m_firstInstance;	
};



} // namespace engine

} // namespace vgeGL

#endif //#ifndef _VGEGL_ENGINE_ENGINE_H
