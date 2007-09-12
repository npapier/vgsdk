// VGSDK - Copyright (C) 2004, 2006, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_ENGINE_ENGINE_HPP
#define _VGEGL_ENGINE_ENGINE_HPP

#include <vge/engine/Engine.hpp>
#include <vge/rc/Manager.hpp>

#include "vgeGL/vgeGL.hpp"

namespace vgd { namespace node { struct Texture; } }



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
	 * @brief Default constructor
	 */
	Engine();



	/**
	 * @name Constructor like
	 */
	//@{
	
	// Overridden
	void reset();

	//@}



	/**
	 * @name Accessors
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
	 * @name OpenGL implementations specifics capabilities
	 */
	//@{
	
	const int32 getMaxLights() const;

	const int32 getMaxTexUnits() const;
	
	const int32 getMaxTexSize() const;

	const int32 getMax3DTexSize() const;
	
	const int32 getMaxCubeMapTexSize() const;

	//@}

	
	/**
	 * @name OpenGL state accessors
	 */
	//@{

	/**
	 * @brief Returns current OpenGL viewport.
	 * 
	 * @param viewport	the output viewport
	 */
	void getViewport( vgm::Rectangle2i& viewport ) const;
	
	/**
	 * @brief Returns the number of bitplanes in the depth buffer.
	 * 
	 * @return the number of bitplanes in the depth buffer
	 */
	const int32 getDepthBits() const;

	/**
	 * @brief Returns the depth texture format computed from the number of bitplanes in the depth buffer.
	 * 
	 * @return the desired depth texture format
	 */
	const GLenum getDepthTextureFormatFromDepthBits() const;

	//@}



	/**
	 * @name OpenGL state modifiers
	 *
	 * @todo Same method as activeTexture() but for others OpenGL api => @todo template ?
	 */
	//@{

	/**
	 * @brief Activates the desired texture unit
	 *
	 * @param textureNode	the texture node (used to know which texture unit must be activated, i.e. getMultiAttributeIndex())
	 */
	void activeTexture( const vgd::node::Texture * textureNode );

	//@}



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
	 * @name Cache implementations specifics capabilities
	 */
	//@{
	mutable GLint	m_maxLights;

	mutable GLint	m_maxTexUnits;
	mutable GLint	m_maxTexSize;
	mutable GLint	m_max3DTexSize;
	mutable GLint	m_maxCubeMapTexSize;
	//@}

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

#endif //#ifndef _VGEGL_ENGINE_ENGINE_HPP
