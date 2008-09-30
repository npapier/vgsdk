// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_ENGINE_ENGINE_HPP
#define _VGEGL_ENGINE_ENGINE_HPP

#include <vge/engine/Engine.hpp>
#include <vge/rc/Manager.hpp>
#include <vge/rc/TManager.hpp>

#include "vgeGL/engine/GLSLState.hpp"

namespace glo 
{
	struct GLSLProgram;
	struct IResource;
//	struct Texture; 
}
namespace vgd { namespace node { struct Texture; } }
namespace vgeGL { namespace engine { struct ProgramGenerator; } }



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

private:
	/**
	 * @brief Initializes all shaders from vgsdk repository
	 * 
	 * @remarks vgsdk repository is a directory named data. Not very practical for deployment.
	 * @todo Shaders should be in a zip file or in the code ?
	 * 
	 * @remarks This method is automatically called by setTodefaults() 
	 */
	void setupGLSLShaders();
public:
	//@}



	/**
	 * @name Accessors
	 */
	//@{

	/**
	 * @brief Sets OpenGL state variables to their defaults values.
	 *
	 * \li Lighting computation is enabled (use the current lighting parameters to compute the vertex color).
	 * \li Depth test is enabled (do depth comparisons and update the depth buffer).
	 * \li Normalization of normals is enabled (normal vectors specified with glNormal are scaled to unit length after 
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
	 * @name GLSL related methods
	 */
	//@{

	/**
	 * @brief Enables or disables the GLSL rendering pipeline depending on the value of the parameter \c isEnabled.
	 *
	 * When this option is enabled, vgSDK generates on the fly GLSL programs and uses them in its rendering pipeline, otherwise the
	 * fixed functionality pipeline is used.
	 *
	 * @param isEnabled		true when GLSL rendering pipeline must be enabled, false otherwise
	 */
	void setGLSLEnabled( const bool isEnabled = true );

	/**
	 * @brief Determines whether the GLSL rendering pipeline is enabled.
	 *
	 * @return true if the GLSL rendering pipeline is enabled, false otherwise
	 */
	const bool isGLSLEnabled() const;



	/**
	 * @brief Memento DP used to capture and restore GLSL activation state.
	 *
	 * GLSL activation state is composed by the GLSL enabled state and the current GLSL program (see isGLSLEnabled() and getCurrentProgram()).
	 */
	struct GLSLActivationState
	{
		private:
		/**
		 * @brief Default constructor
		 *
		* @param isEnabled	true when GLSL rendering pipeline is enabled, false otherwise
		* @param	program	a pointer on the GLSL program
		*/
		GLSLActivationState( const bool isGLSLEnabled, glo::GLSLProgram * currentProgram )
		:	m_isGLSLEnabled(isGLSLEnabled),
			m_currentProgram(currentProgram)
		{}

		const bool					m_isGLSLEnabled;
		glo::GLSLProgram * const	m_currentProgram;

		friend struct Engine;
	};

	/**
	 * @brief Returns an opaque object that store activation state of GLSL
	 *
	 * @see GLSLActivationState
	 */
	const vgd::Shp< GLSLActivationState > getGLSLActivationState() const;

	/**
	 * @brief */
	void setGLSLActivationState( const vgd::Shp< GLSLActivationState > state );



	/**
	 * @brief Sets the current GLSL program.
	 *
	 * @param	program	a pointer on the GLSL program
	 */
	void setCurrentProgram( glo::GLSLProgram * program = 0 );

	/**
	 * @brief Sets the current GLSL program and updates the GLSL enabled state.
	 *
	 * @param	program	a pointer on the GLSL program that must be installed in the current rendering context.
	 *
	 * If the given parameter is an null pointer, then the programmable processors will be
	 * disabled, and fixed functionality will be used (at OpenGL and vgSDK engine level).
	 * Otherwise, if the given parameter is not null pointer, then the programmable processors will be
	 * enabled, and fixed functionality will be disabled (at OpenGL and vgSDK engine level).
	 */
	void sethCurrentProgram( glo::GLSLProgram * program = 0 );

	/**
	 * @brief Retrieves the current GLSL program.
	 *
	 * @return a pointer on the current GLSL program or an empty shared pointer
	 */
	glo::GLSLProgram * getCurrentProgram() const;

	/**
	 * @brief Retrieves the current GLSL program.
	 *
	 * @return if GLSL is enabled in this engine (see isGLSLEnabled()), then returns a pointer on the current GLSL program. 
	 * Otherwise returns an null pointer.
	 */
	glo::GLSLProgram * gethCurrentProgram() const;


	/**
	 * @brief Retrieves the current GLSL state.
	 *
	 * @return the current GLSL state.
	 */
	const GLSLState& getGLSLState() const;

	/**
	 * @brief Retrieves the current GLSL state.
	 *
	 * @return the current GLSL state.
	 */
	GLSLState& getGLSLState();


	/**
	 * @brief Returns the OpenGL GLSL program generator.
	 *
	 * @return a shared pointer on the OpenGL GLSL program generator
	 */
	vgd::Shp< ProgramGenerator > getGLSLProgramGenerator();


	/**
	 * @brief Typedef for the glsl program manager
	 * 
	 * This manager associates a single string to a single glo::GLSLProgram
	 */
	typedef vge::rc::TManager< std::string, glo::IResource > GLSLProgramManagerType;

	/**
	 * @brief Gets the glsl program manager.
	 */
	GLSLProgramManagerType& getGLSLManager();


	/**
	 * @brief Loads shaders from files
	 *
	 * This method loads shaders from files and registers them in the GLSL manager (see getGLSLManager()).
	 *
	 * @param path		path from where files would be searched
	 * @param regex		regular expression used to filter files to load
	 */
	void loadShaders( const std::string& path, const std::string& regex );
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
	const bool isGLContextCurrent() const;

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
	static void getViewport( vgm::Rectangle2i& viewport ) /*const*/;
	// @todo 	static vgm::Rectangle2i getViewport( & viewport )

	/**
	 * @brief Returns the number of bitplanes in the depth buffer.
	 * 
	 * @return the number of bitplanes in the depth buffer
	 */
	const int getDepthBits() const;

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
	 * @todo Same method as activeTexture() but for others OpenGL api => @todo template ? impact of glPush/glPop (attribs)
	 */
	//@{

	/**
	 * @brief Activates the desired texture unit
	 *
	 * @param desiredTextureUnit	the index of the texture unit that must be activated
	 */
	void activeTexture( const int desiredTextureUnit );

	/**
	 * @brief Activates the desired texture unit
	 *
	 * @param textureNode	the texture node (used to know which texture unit must be activated, i.e. getMultiAttributeIndex())
	 */
	void activeTexture( const vgd::node::Texture * textureNode );

	/**
	 * @brief Configures OpenGL for 2D rendering.
	 *
	 * @param optionalViewport		a pointer on the viewport or a null pointer to used current viewport.
	 *
	 * Lighting and depth test are disabled.
	 * ModelView and Texture matrices are initialized to identity.
	 * Projection matrix is initialized using an orthographic matrix (see glOrtho( 0.f, 1.f, 0.f, 1.f, 0.f, 1.f ) ).
	 * The viewport and scissor are initialized using the given \c optionalViewport parameter.
	 */
	static void begin2DRendering( const vgm::Rectangle2i * optionalViewport = 0 );

	/**
	 * @brief Restores OpenGL states modified by begin2DRendering()
	 */
	static void end2DRendering();
	//@}



	/**
	 * @name Render target
	 * @todo
	 */
	//@{
	//Nonstereo double-buffered : GL_FRONT, GL_BACK
	//Stereo double-buffered :GL_FRONT_LEFT, GL_FRONT_RIGHT, GL_BACK_LEFT, GL_BACK_RIGHT
	//[GL_AUXi]
	//beginTexture/endTexture([node] or texRC or [FBO])
	//MRT
	// color or depth buffer

	// setRenderTarget/getRenderTarget
	// beginRT/endRT

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
	static vge::rc::Manager			m_glManager;
	
	/**
	 * @brief Manager for all glsl programs.
	 */
	static GLSLProgramManagerType	m_glslManager;
	// @todo manager for glsl shaders


	/**
	 * @brief Boolean value to indicate if glsl must be used by engine/handler
	 */
	bool m_isGLSLEnabled;

	/**
	 * @brief The current GLSL program.
	 */
	glo::GLSLProgram *	m_currentProgram;


	/**
	 * @brief The GLSL rendering state.
	 */
	GLSLState						m_glslState;

	/**
	 * @brief OpenGL GLSL program generator.
	 */
	vgd::Shp< ProgramGenerator >	m_glslProgramGenerator;



	/**
	 * @brief Used to know if this instance is the first one or not (for doiing some initializations).
	 */
	static bool m_firstInstance;
};



} // namespace engine

} // namespace vgeGL

#endif //#ifndef _VGEGL_ENGINE_ENGINE_HPP
