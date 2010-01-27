// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/Engine.hpp"

#include <glo/GLSLProgram.hpp>
#include <glo/Texture.hpp>
#include <vgd/basic/Image.hpp>
#include <vgd/node/DirectionalLight.hpp>
#include <vgd/node/Texture2D.hpp>
//#include <vgd/node/TextureCubeMap.hpp>
#include <vgd/node/TextureMatrixTransform.hpp>
#include <vgDebug/convenience.hpp>
#include <vge/handler/Handler.hpp>
#include <vge/handler/HandlerRegistry.hpp>
#include "vgeGL/engine/ProgramGenerator.hpp"
#include <vgio/FilenameCollector.hpp>



namespace vgeGL
{

namespace engine
{



// CONSTRUCTORS
Engine::Engine()
:	m_isTextureMappingEnabled(true),
	m_isDisplayListEnabled(true),
	m_isGLSLEnabled(true),
	m_currentProgram(0),
	// m_glStateStack()
	//m_glslStateStack()
	m_glslProgramGenerator( new ProgramGenerator() )
{
	// Reset cache
	m_maxViewportSize.setInvalid();
	m_maxLights = m_maxTexUnits = m_maxTexSize = m_max3DTexSize = m_maxCubeMapTexSize = 0;
}



void Engine::reset()
{
	// @todo remove me, because getMaxTexUnits() and getMaxLights() are OpenGL context protected...
	if ( isGLContextCurrent() == false )
	{
		vgLogDebug("Engine::reset(): OpenGL context not current. Checks behavior.");
		//return;
	}

	//
	setTextureMappingEnabled();
	//setDisplayListEnabled();

	//
	m_currentProgram	= 0;

	// Reset cache
	m_maxViewportSize.setInvalid();
	m_maxLights = m_maxTexUnits = m_maxTexSize = m_max3DTexSize = m_maxCubeMapTexSize = 0;

	//
	getGLStateStack().clear( GLState() );
	getGLSLStateStack().clear( GLSLState(getMaxLights(), getMaxTexUnits()) );

	if ( m_firstInstance )
	{
		// @todo move to constructor ? yes, but only when dynamic management of state for Light and Texture would be done

		// This is the first instance of this class.

		// Do some initialization
		// and don't do the same for any others instances if populateNodeRegistry returns true
		m_firstInstance = (populateNodeRegistry() == false);
	}

	//if ( m_firstInstance == false )
	//{
		::vge::engine::Engine::reset();
	//}
}



void Engine::setToDefaults()
{
	if ( isGLContextCurrent() == false )
	{
		return;
	}

	// GLOBAL INITIALIZATION
	glEnable( GL_LIGHTING );
	glEnable( GL_DEPTH_TEST );

	if ( false /*isGL_EXT_rescale_normal() */)		// @todo uncomment and test with GLSL
	{
		vgLogDebug( "vgeGL.Engine: GL_EXT_rescale_normal extension detected and used." );
		glEnable( GL_RESCALE_NORMAL );  // gle: GL_EXT_rescale_normal
	}
	else
	{
		glEnable( GL_NORMALIZE );
	}

	if ( isGL_EXT_separate_specular_color() )
	{
		vgLogDebug( "vgeGL.Engine: GL_EXT_separate_specular_color extension detected." );
		vgLogDebug( "vgeGL.Engine: GL_LIGHT_MODEL_COLOR_CONTROL=GL_SEPARATE_SPECULAR_COLOR" );
		glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR );
	}
	else
	{
		vgLogDebug( "vgeGL.Engine: Warning : GL_EXT_separate_specular_color extension is detected" );
		vgLogDebug( "vgeGL.Engine: GL_LIGHT_MODEL_COLOR_CONTROL=GL_SINGLE_COLOR" );
		vgLogDebug( "vgeGL.Engine: Using both texture mapping and specular highlights would not be well supported." );
		glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR );
	}

	// For each handler in registry, do
	vge::handler::HandlerRegistry&	handlerRegistry= vge::handler::Handler::getClassRegistry();
	
	vge::handler::HandlerRegistry::HandlersSet::iterator i_handler;
	vge::handler::HandlerRegistry::HandlersSet::iterator ie_handler;

	for(	boost::tie( i_handler, ie_handler ) = handlerRegistry.getIterators();
			i_handler != ie_handler;
			i_handler++ )
	{
		(*i_handler)->setToDefaults();
	}
	
	//
	vgLogDebug3( "vgeGL.Engine: MAX VIEWPORT SIZE		= %i x %i", getMaxViewportSize()[0],  getMaxViewportSize()[1] );

	vgLogDebug2( "vgeGL.Engine: MAX_LIGHTS			= %i", getMaxLights() );

	vgLogDebug2( "vgeGL.Engine: GL_MAX_TEXTURE_UNITS		= %i", getMaxTexUnits() );

	vgLogDebug2( "vgeGL.Engine: GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS = %i", getMaxVertexTexImageUnits() );
	vgLogDebug2( "vgeGL.Engine: GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS = %i", getMaxCombinedTexImageUnits() );
	vgLogDebug2( "vgeGL.Engine: GL_MAX_TEXTURE_IMAGE_UNITS = %i", getMaxTexImageUnits() );
	vgLogDebug2( "vgeGL.Engine: GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_ARB = %i", getMaxGeometryTexImageUnits() );

	vgLogDebug2( "vgeGL.Engine: GL_MAX_TEXTURE_SIZE		= %i", getMaxTexSize() );
	vgLogDebug2( "vgeGL.Engine: GL_MAX_3D_TEXTURE_SIZE		= %i", getMax3DTexSize() );
	vgLogDebug2( "vgeGL.Engine: GL_MAX_CUBE_MAP_TEXTURE_SIZE	= %i", getMaxCubeMapTexSize() );
}



// STATE
const Engine::GLStateStack& Engine::getGLStateStack() const
{
	return m_glStateStack;
}

Engine::GLStateStack& Engine::getGLStateStack()
{
	return m_glStateStack;
}


const Engine::GLSLStateStack& Engine::getGLSLStateStack() const
{
	return m_glslStateStack;
}

Engine::GLSLStateStack& Engine::getGLSLStateStack()
{
	return m_glslStateStack;
}



const GLState& Engine::getGLState() const
{
	return m_glStateStack.getTop();
}

GLState& Engine::getGLState()
{
	return m_glStateStack.getTop();
}


const GLSLState& Engine::getGLSLState() const
{
	return m_glslStateStack.getTop();
}

GLSLState& Engine::getGLSLState()
{
	return m_glslStateStack.getTop();
}



// MANAGER
vge::rc::Manager& Engine::getGLManager()
{
	return m_glManager;
}



Engine::GLSLProgramManagerType& Engine::getGLSLManager()
{
	return m_glslManager;
}



const bool Engine::isTextureMappingEnabled() const
{
	return m_isTextureMappingEnabled;
}



void Engine::setTextureMappingEnabled( const bool enabled )
{
	m_isTextureMappingEnabled = enabled;
}



const bool Engine::isDisplayListEnabled() const
{
	return m_isDisplayListEnabled;
}



void Engine::setDisplayListEnabled( const bool enabled )
{
	m_isDisplayListEnabled = enabled;
}



// 
/**
 * @todo All OpenGL objects are destroyed by this method. Not very cute.
 */
void Engine::setGLSLEnabled( const bool isEnabled )
{
	m_isGLSLEnabled = isEnabled;

	// @todo FIXME
	//getGLManager().clear();			///< not very cute
}



const bool Engine::isGLSLEnabled() const
{
	return m_isGLSLEnabled;
}



const vgd::Shp< Engine::GLSLActivationState > Engine::getGLSLActivationState() const
{
	vgd::Shp< GLSLActivationState > memento( 
		new GLSLActivationState( isGLSLEnabled(), getCurrentProgram() )
			);
	return memento;
}



void Engine::setGLSLActivationState( const vgd::Shp< GLSLActivationState > state )
{
	sethCurrentProgram( state->m_currentProgram );
	setGLSLEnabled( state->m_isGLSLEnabled );
}



void Engine::setCurrentProgram( glo::GLSLProgram * program )
{
	m_currentProgram = program;
}



void Engine::sethCurrentProgram( glo::GLSLProgram * program )
{
	setCurrentProgram( program );

	if ( program )
	{
		setGLSLEnabled();
		program->use();
	}
	else
	{
		setGLSLEnabled( false );
		glo::GLSLProgram::useFixedPaths();
	}
}



glo::GLSLProgram * Engine::getCurrentProgram() const
{
	return m_currentProgram;
}



glo::GLSLProgram * Engine::gethCurrentProgram() const
{
	if ( isGLSLEnabled() )
	{
		return m_currentProgram;
	}
	else
	{
		return 0;
	}
}



vgd::Shp< ProgramGenerator > Engine::getGLSLProgramGenerator()
{
	return m_glslProgramGenerator;
}



void Engine::loadShaders( const std::string& path, const std::string& regex )
{
	using vgio::FilenameCollector;

	FilenameCollector filenameCollector( path );
	filenameCollector.setRegex( regex );
	const FilenameCollector::StringList& filenames = filenameCollector.run();

	for( std::list< std::string >::const_iterator	i		= filenames.begin(),
													iEnd	= filenames.end();
		i != iEnd;
		++i )
	{
		using ::glo::GLSLProgram;

		// Gets the filename
		const std::string filename( *i );

		// Loads file
		const std::string shaderString = GLSLProgram::loadFile( filename );

		if ( !shaderString.empty() )
		{
			// File not empty, creates the shader
			vgDebug::get().logDebug( "vgeGL.Engine: Loads shader %s", filename.c_str() );

			///@todo Creates glo::GLSLShader
			GLSLProgram *program = new GLSLProgram;

			// Determines the type of shader in the file from extension
			const bool isAVertexShader = (filename.rfind( "_vs.glsl" ) != std::string::npos );
			
			const GLSLProgram::ShaderType shaderType = isAVertexShader ? GLSLProgram::VERTEX : GLSLProgram::FRAGMENT;

			const bool addShaderRetVal = program->addShader( shaderString.c_str(), shaderType, true );

			if ( addShaderRetVal )
			{
				// Adds it to the GLSL manager
				getGLSLManager().add( filename, program );
				vgDebug::get().logDebug( "vgeGL.Engine: Shader %s successfully registered in GLSLManager", filename.c_str() );
			}
			else
			{
				vgDebug::get().logDebug( "vgeGL.Engine: Fails to registered shader %s", filename.c_str() );

				//const std::string infoLog = program->getInfoLog( program->getProgramObject() );??????????????????????? FIXME
				//vgDebug::get().logDebug( "Engine:\n%s\n", infoLog.c_str() );

				delete program;
			}
		}
		else
		{
			vgDebug::get().logDebug( "vgeGL.Engine: Empty shader %s", filename.c_str() );
		}
	}
}



const bool Engine::isGLContextCurrent() const
{
	// @todo FIXME should found a smarter method to test if OpenGL is current.
	const GLubyte *pString = glGetString(GL_EXTENSIONS);
	return ( pString != 0 );
}



/**
 * @todo Use glLoadIdentity() and creates synchronizeMatricesFromEngineToGL()
 */
void Engine::resetMatrices()
{
	// @todo remove me
	//if ( isGLContextCurrent() == false )
	//{
	//	return;
	//}

	// STEP 1 : call method from vge::engine::Engine
	vge::engine::Engine::resetMatrices();
	
	// STEP 2 : update OpenGL
	if ( /*!isGLContextCurrent() &&*/ gleGetCurrent() == 0 )
	{
		// FIXME not very smart.
		return;
	}
	
	// MODELVIEW
	assert( getGeometricalMatrix().size() == 1 );
	
	vgm::MatrixR& 	current(	getGeometricalMatrix().getTop() );

	glMatrixMode( GL_MODELVIEW );

	glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );

	// PROJECTION
	assert( getProjectionMatrix().size() == 1 );

	current = getProjectionMatrix().getTop();

	glMatrixMode( GL_PROJECTION );

	glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );
	
	// TEXTURE
	for(	int32	index	= 0,
					iMax	= getTextureMatrix().size();
			index < iMax;
			++index )
	{
		current = getTextureMatrix().getTop( index );

		activeTexture( index );

		glMatrixMode( GL_TEXTURE );

		glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );
	}
}



const vgm::Vec2i Engine::getMaxViewportSize() const
{
	if ( m_maxViewportSize.isInvalid() )
	{
		if ( isGLContextCurrent() )
		{
			GLint viewportSize[2];

			glGetIntegerv( GL_MAX_VIEWPORT_DIMS, &viewportSize[0] );
			m_maxViewportSize.setValue( viewportSize[0], viewportSize[1] );
		}
		else
		{
			vgLogDebug("Engine::getMaxViewportSize(): OpenGL context not current, so return arbitrary value (4096,4096).");
			return vgm::Vec2i(4096,4096);
		}
	}

	return m_maxViewportSize;
}



const int Engine::getMaxLights() const
{
	if ( m_maxLights == 0 )
	{
		if ( isGLContextCurrent() )
		{
			// @todo
			glGetIntegerv(GL_MAX_LIGHTS, &m_maxLights );
			m_maxLights = 4;
		}
		else
		{
			vgLogDebug("Engine::getMaxLights(): OpenGL context not current, so return arbitrary value 4.");
			return 4;
		}
	}

	return m_maxLights;
}



const int Engine::getMaxTexUnits() const
{
	if ( m_maxTexUnits == 0 )
	{
		if ( isGLContextCurrent() )
		{
			// @todo
			glGetIntegerv( GL_MAX_TEXTURE_UNITS, &m_maxTexUnits );
			m_maxTexUnits = 3;
		}
		else
		{
			vgLogDebug("Engine::getMaxTexUnits(): OpenGL context not current, so return arbitrary value 2.");
			return 3;
		}
	}

	return m_maxTexUnits;
}



const int Engine::getMaxTexSize() const
{
	if ( m_maxTexSize == 0 )
	{
		glGetIntegerv( GL_MAX_TEXTURE_SIZE, &m_maxTexSize );
	}

	return m_maxTexSize;
}



const int Engine::getMax3DTexSize() const
{
	if ( m_max3DTexSize == 0 )
	{
		glGetIntegerv( GL_MAX_3D_TEXTURE_SIZE, &m_max3DTexSize );
	}
	
	return m_max3DTexSize;
}



const int Engine::getMaxCubeMapTexSize() const
{
	if ( m_maxCubeMapTexSize == 0 )
	{
		glGetIntegerv( GL_MAX_CUBE_MAP_TEXTURE_SIZE, &m_maxCubeMapTexSize );
	}

	return m_maxCubeMapTexSize;
}



const int Engine::getMaxVertexTexImageUnits() const
{
	GLint value;
	glGetIntegerv( GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &value );

	return value;
}



const int Engine::getMaxCombinedTexImageUnits() const
{
	GLint value;
	glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &value );

	return value;
}



const int Engine::getMaxTexImageUnits() const
{
	GLint value;
	glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &value );

	return value;
}



const int Engine::getMaxGeometryTexImageUnits() const
{
	GLint value;
	glGetIntegerv( GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_ARB, &value );

	return value;
}



void Engine::getGLViewport( vgm::Rectangle2i& viewport ) /*const*/
{
	GLint viewportGL[4];

	glGetIntegerv( GL_VIEWPORT, viewportGL );

	viewport.set( viewportGL[0], viewportGL[1], viewportGL[2], viewportGL[3] );
}



const int Engine::getGLDepthBits() /* const */
{
	GLint depthBits;
	glGetIntegerv( GL_DEPTH_BITS, &depthBits );

	return depthBits;
}



const GLenum Engine::convertDepthTextureFormat( const int depthBits ) /* const */
{
	GLenum retVal;

	switch ( depthBits )
	{
		case 24:
			retVal = GL_DEPTH_COMPONENT24_ARB;
			break;

		case 32:
			retVal = GL_DEPTH_COMPONENT32_ARB;
			break;

		case 16:
			retVal = GL_DEPTH_COMPONENT16_ARB;
			break;

		default:
			vgLogDebug( "vgeGL.Engine:getGLDepthTextureFormat(): Performance warning : No matching between given depth buffer bits and depth texture format." );
			vgLogDebug( "vgeGL.Engine:getGLDepthTextureFormat(): Performance warning : Use GL_DEPTH_COMPONENT16_ARB" );
			retVal = GL_DEPTH_COMPONENT16_ARB;
			break;
	}

	return retVal;
}



const GLenum Engine::getGLDepthTextureFormatFromDepthBits() /*const */
{
	const int32 depthBits = getGLDepthBits();

	const GLenum retVal = convertDepthTextureFormat(depthBits);

	return retVal;
}



vgd::Shp< vgd::basic::Image > Engine::captureGLFramebuffer() const
{
	// Reads back the framebuffer color values
	using vgd::basic::Image;

	const vgm::Vec2i drawingSurfaceSize = getDrawingSurfaceSize();

	vgd::Shp< Image > image( new Image() );
	image->create(	3, drawingSurfaceSize[0], drawingSurfaceSize[1], 1,
					Image::BGR, Image::UINT8 );	// @todo always BGR ? and UINT8 ?
	uint8 *imageData = static_cast<uint8*>( image->editPixels() );

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(	0, 0, drawingSurfaceSize[0], drawingSurfaceSize[1], 
					GL_BGR, GL_UNSIGNED_BYTE,
					imageData );
	image->editPixelsDone();

	return image;
}



void Engine::activeTexture( const int desiredTextureUnit )
{
//	static int currentTextureUnit = 0;

//#ifdef _DEBUG
//	GLint glcurrentTextureUnit;
//	glGetIntegerv( GL_ACTIVE_TEXTURE_ARB, &glcurrentTextureUnit );
//	glcurrentTextureUnit -= GL_TEXTURE0_ARB;
//
//	if ( glcurrentTextureUnit != currentTextureUnit )
//	{
//		vgLogDebug( "Unexpected current active texture unit." );
//		
//		// Repairs cache
//		currentTextureUnit = glcurrentTextureUnit;
//	}
//	//assert( glcurrentTextureUnit == currentTextureUnit && "Unexpected current active texture unit." );
//
//#endif

	// @todo This code is disabled => see method comments about glPush/glPop*.
//	if ( desiredTextureUnit != currentTextureUnit )
//	{
		// Activates the desired texture unit
		::glo::Texture::active( GL_TEXTURE0_ARB + desiredTextureUnit );

//		// Fills the current texture unit cache
//		currentTextureUnit = desiredTextureUnit;
//	}
	// else nothing to do, i.e. already done
}



void Engine::activeTexture( const vgd::node::Texture * textureNode )
{
	const int desiredTextureUnit = textureNode->getMultiAttributeIndex();

	activeTexture( desiredTextureUnit );
}



void Engine::begin2DRendering( const vgm::Rectangle2i * optionalViewport )
{
	// OpenGL attributes
	glPushAttrib( GL_ALL_ATTRIB_BITS );	// @todo OPTME

	glDisable( GL_LIGHTING );
	glDisable( GL_DEPTH_TEST );

	// Viewport and scissor
	vgm::Rectangle2i viewport;
	if ( optionalViewport )
	{
		viewport = (*optionalViewport);
	}
	else
	{
		// @todo Uses engine.viewport ? glEngine must be a method param or remove static
		getGLViewport( viewport );
		//
		// assert( viewport == getViewport() ); // ???
	}

	glViewport( viewport[0], viewport[1], viewport[2], viewport[3] );

	glScissor( viewport[0], viewport[1], viewport[2], viewport[3] );
	glEnable(GL_SCISSOR_TEST);

	// Matrix stacks
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho( 0.f, 1.f, 0.f, 1.f, 0.f, 1.f );

	activeTexture(0);
	glMatrixMode( GL_TEXTURE );
	glPushMatrix();
	glLoadIdentity();
}



void Engine::end2DRendering()
{
	// Matrix stacks
	activeTexture(0);
	glMatrixMode( GL_TEXTURE );
	glPopMatrix();

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	// OpenGL attributes
	glPopAttrib();
}



void Engine::push()
{
	getGLSLStateStack().push();
	getGLStateStack().push();
	glPushAttrib( GL_ALL_ATTRIB_BITS );

	vge::engine::Engine::push();
}


void Engine::pop()
{
	vge::engine::Engine::pop();

	glPopAttrib();
	getGLStateStack().pop();
	getGLSLStateStack().pop();
}



bool Engine::populateNodeRegistry()
{
	// DirectionalLight
	for(	int8	i		= 1,
					iMax	= static_cast< int8 >(getMaxLights());
			i < iMax;
			++i )
	{
		vgd::basic::RegisterNode< vgd::node::DirectionalLight >	registerNode( i );
	}

	// TextureMatrixTransform, Texture2D, TextureCubeMap
	for(	int8	i		= 1,
					iMax	= static_cast< int8 >(getMaxTexUnits());
			i < iMax;
			++i )
	{
		vgd::basic::RegisterNode< vgd::node::Texture2D >				registerNode1( i );
		vgd::basic::RegisterNode< vgd::node::TextureMatrixTransform >	registerNode2( i );
		//vgd::basic::RegisterNode< vgd::node::TextureCubeMap>			registerNode3( i );
	}

	// @todo remove this returned value
	return true;
}



vge::rc::Manager				Engine::m_glManager;

Engine::GLSLProgramManagerType	Engine::m_glslManager("GLSL Program Manager");

bool							Engine::m_firstInstance = true;



} // namespace engine

} // namespace vgeGL
