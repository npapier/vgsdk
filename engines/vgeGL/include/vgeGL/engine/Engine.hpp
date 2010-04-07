// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_ENGINE_ENGINE_HPP
#define _VGEGL_ENGINE_ENGINE_HPP

#include <vge/engine/Engine.hpp>
#include <vge/engine/TStack.hpp>
#include <vge/rc/TManager.hpp>

#include "vgeGL/engine/GLSLState.hpp"

// for GLState
#include <vgd/node/DrawStyle.hpp>
// endfor

namespace glo 
{
	struct GLSLProgram;
	struct IResource;
//	struct Texture; 
}

namespace vgd 
{
	namespace basic { struct Image; }
	namespace node { struct Texture; } 
}

namespace vgeGL 
{ 
	namespace engine { struct ProgramGenerator; } 
}



/**
 * @namespace vgeGL::engine
 * 
 * @brief Engine evaluate scene graph with handlers and take care of OpenGL resources and states.
 */
namespace vgeGL
{

namespace engine
{


/**
 * @brief GL rendering state
 *
 * This class is a specialized container for GL rendering state used by vgeGL to take care of the rendering state given by the scene graph. 
 *
 * @todo Moves this class in its own file
 */
struct VGEGL_API GLState
{
	// Default values must be identical to engine/node default values
	GLState()
	:	// MATERIAL
		m_opacity(1.f),
		m_diffuse(0.8f, 0.8f, 0.8f),

		// DRAWSTYLE
		m_shape( vgd::node::DrawStyle::DEFAULT_SHAPE ),
		m_normalLength( 0.f ),
		m_showOrientation( false ),
		m_boundingBox( vgd::node::DrawStyle::DEFAULT_BOUNDING_BOX ) 
	{}

	// MATERIAL
	void setOpacity( const float opacity )	{ m_opacity = opacity; }
	const float getOpacity() const			{ return m_opacity; }

	void setDiffuse( const vgm::Vec3f diffuse )	{ m_diffuse = diffuse; }
	const vgm::Vec3f getDiffuse() const			{ return m_diffuse; }

	// DRAWSTYLE
	void setShape( const vgd::node::DrawStyle::ShapeValueType& shape )										{ m_shape = shape; }
	const vgd::node::DrawStyle::ShapeValueType& getShape() const											{ return m_shape; }

	void setNormalLength( const vgd::node::DrawStyle::NormalLengthValueType& normalLength )					{ m_normalLength = normalLength; }
	const vgd::node::DrawStyle::NormalLengthValueType& getNormalLength() const								{ return m_normalLength; }

	void setShowOrientation( const vgd::node::DrawStyle::ShowOrientationValueType& showOrientation )		{ m_showOrientation = showOrientation; }
	const vgd::node::DrawStyle::ShowOrientationValueType& getShowOrientation() const						{ return m_showOrientation; }

	void setBoundingBox( const vgd::node::DrawStyle::BoundingBoxValueType& boundingBox )					{ m_boundingBox = boundingBox; }
	const vgd::node::DrawStyle::BoundingBoxValueType& getBoundingBox() const								{ return m_boundingBox; }

private:
	float											m_opacity;
	vgm::Vec3f										m_diffuse;

	vgd::node::DrawStyle::ShapeValueType			m_shape;
	vgd::node::DrawStyle::NormalLengthValueType		m_normalLength;
	vgd::node::DrawStyle::ShowOrientationValueType	m_showOrientation;
	vgd::node::DrawStyle::BoundingBoxValueType		m_boundingBox;
	
};


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
	 * @name Constructors
	 */
	//@{

	/**
	 * @brief Default constructor
	 */
	Engine();

	/**
	 * @brief Destructor
	 */
	~Engine();

	// Overridden
	void reset();

public:

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

	//@}



	/**
	 * @name State management
	 */
	//@{

	typedef vge::engine::TStack< GLState >		GLStateStack;	///< Type definition for the stack of GLState
	typedef vge::engine::TStack< GLSLState >	GLSLStateStack; ///< Type definition for the stack of GLSLState

	/**
	 * @brief Retrieves the OpenGL state stack.
	 *
	 * @return the OpenGL state stack
	 */
	const GLStateStack& getGLStateStack() const;

	/**
	 * @brief Retrieves the OpenGL state stack.
	 *
	 * @return the OpenGL state stack
	 */
	GLStateStack& getGLStateStack();


	/**
	 * @brief Retrieves the GLSL state stack.
	 *
	 * @return the GLSL state stack
	 */
	const GLSLStateStack& getGLSLStateStack() const;

	/**
	 * @brief Retrieves the GLSL state stack.
	 *
	 * @return the GLSL state stack
	 */
	GLSLStateStack& getGLSLStateStack();



	/**
	 * @brief Retrieves the current OpenGL state.
	 *
	 * @return the current OpenGL state.
	 */
	const GLState& getGLState() const;

	/**
	 * @brief Retrieves the current OpenGL state.
	 *
	 * @return the current OpenGL state.
	 */
	GLState& getGLState();


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

	//@}



	/**
	 * @name Manager accessors
	 */
	//@{

	/**
	 * @brief Typedef for the OpenGL object manager
	 * 
	 * This manager associates a node to an OpenGL resource
	 */
	typedef vge::rc::TManager< vgd::node::Node *, glo::IResource > GLManagerType;

	/**
	 * @brief Gets the OpenGL objects manager
	 */
	GLManagerType& getGLManager();

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

	//@}



	/**
	 * @name Engine configuration
	 *
	 * @todo Adds GREMEDY_string_marker
	 */
	//@{

	/**
	 * @brief Determines whether the texture mapping is enabled.
	 *
	 * @return true if texture mapping is enabled, false otherwise
	 */
	const bool isTextureMappingEnabled() const;

	/**
	 * @brief Enables or disables the texture mapping depending on the value of the parameter isEnabled.
	 *
	 * @param isEnabled		true when the texture mapping must be enabled, false otherwise
	 */
	void setTextureMappingEnabled( const bool enabled = true );


	/**
	 * @brief Determines whether the display list caching mechanism is enabled.
	 *
	 * @return true if display list caching mechanism is enabled, false otherwise
	 */
	const bool isDisplayListEnabled() const;

	/**
	 * @brief Enables or disables the display list caching mechanism depending on the value of the parameter isEnabled.
	 *
	 * @param isEnabled		true when the display list caching mechanism must be enabled, false otherwise
	 */
	void setDisplayListEnabled( const bool enabled = true );


	/**
	 * @brief Determines whether the shadow sampler usage is enabled.
	 *
	 * @return true if shadow sampler usage is enabled, false otherwise.
	 */
	const bool isShadowSamplerUsageEnabled() const;

	/**
	 * @brief Enables or disables the shadow sampler usage depending on the value of the parameter isEnabled.
	 *
	 * @param isEnabled		true when the shadow sampler usage must be enabled, false otherwise
	 */
	void setShadowSamplerUsageEnabled( const bool enabled = true );
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
		* @param program		a pointer on the GLSL program
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
	 * @brief Returns the OpenGL GLSL program generator.
	 *
	 * @return a shared pointer on the OpenGL GLSL program generator
	 */
	vgd::Shp< ProgramGenerator > getGLSLProgramGenerator();


// @todo remove me
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

	const vgm::Vec2i getMaxViewportSize() const;
	const int getMaxLights() const;
	const int getMaxTexUnits() const;
	const int getMaxTexSize() const;
	const int getMax3DTexSize() const;
	const int getMaxCubeMapTexSize() const;

	const int getMaxVertexTexImageUnits() const;
	const int getMaxCombinedTexImageUnits() const;
	const int getMaxTexImageUnits() const;
	const int getMaxGeometryTexImageUnits() const;
	//@}



	/**
	 * @name OpenGL state accessors
	 *
	 * @todo captureGLFramebuffer() for others buffers (depth, renderbuffers...)
	 */
	//@{

	/**
	 * @brief Returns current OpenGL viewport.
	 * 
	 * @param viewport	the output viewport
	 */
	static void getGLViewport( vgm::Rectangle2i& viewport ) /*const*/;
	// @todo 	static vgm::Rectangle2i getViewport( & viewport )

	/**
	 * @brief Returns the number of bitplanes in the depth buffer.
	 * 
	 * @return the number of bitplanes in the depth buffer
	 */
	static const int getGLDepthBits()/* const */;

	/**
	 * @brief Returns the depth texture format computed from the given number of depth bitplanes.
	 * 
	 * @return the desired depth texture format
	 */
	static const GLenum convertDepthTextureFormat( const int depthBits ) /* const */;

	/**
	 * @brief Returns the depth texture format computed from the number of bitplanes in the depth buffer.
	 * 
	 * @return the desired depth texture format
	 */
	static const GLenum getGLDepthTextureFormatFromDepthBits() /*const*/;

	/**
	 * @brief Returns an image containing the framebuffer color values.
	 *
	 * @remarks This method reads back the framebuffer color values, be careful this is slow and stalled the OpenGL pipeline.
	 */
	/*static*/ vgd::Shp< vgd::basic::Image > captureGLFramebuffer() const;

	/**
	 * @brief Enables or disables the given OpenGL capability.
	 *
	 * @param capability	specifies a symbolic constant indicating a GL capability
	 * @param isEnabled		true to enable the capability, false to disable it
	 */
	 static void setGLEnable( const GLenum capability, const bool isEnabled ) /*const*/;
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
	static void activeTexture( const int desiredTextureUnit );

	/**
	 * @brief Activates the desired texture unit
	 *
	 * @param textureNode	the texture node (used to know which texture unit must be activated, i.e. getMultiAttributeIndex())
	 */
	static void activeTexture( const vgd::node::Texture * textureNode );

	/**
	 * @brief Configures OpenGL for 2D rendering.
	 *
	 * @param optionalViewport		a pointer on the viewport or a null pointer to used current viewport.
	 * @param pushAttribs			true to call glPushAttrib( GL_ALL_ATTRIB_BITS ), false otherwise
	 * 
	 * Lighting and depth test are disabled.
	 * ModelView and Texture matrices are initialized to identity.
	 * Projection matrix is initialized using an orthographic matrix (see glOrtho( 0.f, 1.f, 0.f, 1.f, 0.f, 1.f ) ).
	 * The viewport and scissor are initialized using the given \c optionalViewport parameter.
	 */
	static void begin2DRendering( const vgm::Rectangle2i * optionalViewport = 0, const bool pushAttribs = false );

	/**
	 * @brief Restores OpenGL states modified by begin2DRendering()
	 *
	 * @param popAttribs	true to call glPopAttrib(), false otherwise
	 */
	static void end2DRendering( const bool popAttribs = false );

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



	/**
	 * @name Helpers
	 */
	//@{

	/**
	 * @brief Pushes all stacks.
	 */
	void push();

	/**
	 * @brief Pops all stacks.
	 */
	void pop();

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

	bool m_isTextureMappingEnabled;		//< true if texture mapping is enabled, false otherwise
	bool m_isDisplayListEnabled;		//< true if engine must used display list, false otherwise
	bool m_isShadowSamplerEnabled;		//< true if engine must used shadow sampler, false otherwise

	/**
	 * @name Cache implementations specifics capabilities
	 */
	//@{
	mutable vgm::Vec2i	m_maxViewportSize;

	mutable GLint		m_maxLights;

	mutable GLint		m_maxTexUnits;
	mutable GLint		m_maxTexSize;
	mutable GLint		m_max3DTexSize;
	mutable GLint		m_maxCubeMapTexSize;
	//@}



	/**
	 * @brief Manager for all opengl objects.
	 */
	GLManagerType					m_glManager;
	boost::signals::connection		m_glManagerConnection;
	
	/**
	 * @brief Manager for all glsl programs.
	 */
	GLSLProgramManagerType			m_glslManager;


	/**
	 * @brief Boolean value to indicate if glsl must be used by engine/handler
	 */
	bool m_isGLSLEnabled;

	/**
	 * @brief The current GLSL program.
	 */
	glo::GLSLProgram *	m_currentProgram;



	/**
	 * @brief The stack of OpenGL rendering state.
	 */
	vge::engine::TStack< GLState > m_glStateStack;

	/**
	 * @brief The stack of GLSL rendering state.
	 */
	vge::engine::TStack< GLSLState > m_glslStateStack;

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
