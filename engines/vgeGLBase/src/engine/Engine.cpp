//// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/engine/Engine.hpp"
//
//#include <gle/OpenGLExtensionsGen.hpp>
//#include <glo/FrameBufferObject.hpp>
//#include <glo/helpers.hpp>
//#include <glo/GLSLProgram.hpp>
//#include <glo/Texture.hpp>
//#include <vgd/basic/Image.hpp>
//#include <vgd/basic/TimeDuration.hpp>
//#include <vgd/node/DirectionalLight.hpp>
//#include <vgd/node/Texture2D.hpp>
////#include <vgd/node/TextureCubeMap.hpp>
//#include <vgd/node/TextureMatrixTransform.hpp>
//
//#include <vge/handler/Handler.hpp>
//#include <vge/handler/HandlerRegistry.hpp>
//#include "vgeGLBase/engine/GLSLState.hpp"
//#include "vgeGLBase/engine/ProgramGenerator.hpp"
//#include "vgeGLBase/technique/helpers.hpp"
////#include <vgio/FilenameCollector.hpp>
//
//
//namespace vgeGLBase
//{
//
//namespace engine
//{
//
//
//// CONSTRUCTOR
//Engine::Engine( Engine * sharedEngine )
//:	m_isLightingEnabled(true),
//	m_isTextureMappingEnabled(true),
//	m_isDrawCallsEnabled(true),
//	m_isDisplayListEnabled(true),
//	m_isDepthPrePassEnabled(false),
//	m_isShadowEnabled(true),
//	//m_isDSAEnabled(false),
//
//	m_glManager(		sharedEngine != 0 ? sharedEngine->m_glManager		: vgd::makeShp( new GLManagerType("GL object manager") )					),
//	m_glslManager(		sharedEngine != 0 ? sharedEngine->m_glslManager		: vgd::makeShp( new GLSLProgramManagerType("GLSL Program Manager") )		),
//	m_glslManagerExt(	sharedEngine != 0  ? sharedEngine->m_glslManagerExt	: vgd::makeShp( new GLSLProgramManagerExtType("GLSL Program ManagerExt") )	),
//
//	m_isGLSLEnabled(true),
//	m_currentProgram(0),
//	// m_glStateStack()
//	//m_glslStateStack()
//	//m_builtinUniformState
//	//m_uniformState
//	//m_globalGLSLState
//	//m_outputBuffers
//	//m_currentPrivateOutputBuffers
//	m_glslProgramGenerator( new ProgramGenerator() )
//{
//	// Connects OpenGL manager to node destruction signal.
//	m_glManagerConnection = vgd::node::Node::connect( boost::bind(&GLManagerType::remove, getGLManager().get(), _1) );
//
//	// Reset cache
//	m_maxViewportSize.setInvalid();
//	m_maxLights = m_maxTexUnits = m_maxTexSize = m_max3DTexSize = m_maxCubeMapTexSize = 0;
//}
//
//
//
//Engine::~Engine()
//{
//	m_glManagerConnection.disconnect();
//}
//
//
//
//void Engine::reset()
//{
//	// @todo remove me, because getMaxTexUnits() and getMaxLights() are OpenGL context protected...
//	if ( isGLContextCurrent() == false )
//	{
//		vgLogDebug("Engine::reset(): OpenGL context not current. Checks behavior.");
//		//return;
//	}
//
//	// Enables advanced OpenGL errors management using GL_ARB_debug_output extension in debug configuration
//#ifdef _DEBUG
//	gleGetCurrent()->setDebugOutput( gle::OpenGLExtensions::SYNCHRONOUS );
//#endif
//
//	// Configures engine
//	setLightingEnabled();
//	setTextureMappingEnabled();
//	setDisplayListEnabled();
//	setDepthPrePassEnabled( false );
//
//	// Detects drivers provider
//	vgLogMessage( "%s driver found", gleGetCurrent()->getDriverProviderString().c_str() );
//	const gle::OpenGLExtensions::DriverProviderType driverProvider = gleGetCurrent()->getDriverProvider();
//	switch ( driverProvider )
//	{
//		case gle::OpenGLExtensions::NVIDIA_DRIVERS:
//			vgLogMessage("Engine: Detected NVIDIA GPU.");
//			break;
//
//		case gle::OpenGLExtensions::ATI_DRIVERS:
//			vgLogMessage("Engine: Detected ATI GPU.");
//			break;
//
//		case gle::OpenGLExtensions::UNKNOWN_DRIVERS:
//		default:
//			vgLogMessage("Engine: Unknown GPU encountered.");
//	}
//
//	setShadowEnabled();
//
//	//
//	m_currentProgram	= 0;
//
//	// Reset cache
//	m_maxViewportSize.setInvalid();
//	m_maxLights = m_maxTexUnits = m_maxTexSize = m_max3DTexSize = m_maxCubeMapTexSize = 0;
//
//	//
//	getGLStateStack().clear( vgd::makeShp(new GLState()) );
//	m_glslStateStack.clear( vgd::makeShp(new GLSLState(getMaxTexUnits()) ) );
//	getBuiltinUniformState().clear();
//	getUniformState().clear();
//	m_globalGLSLState.reset();
//	setOutputBuffers();
//	setCurrentPrivateOutputBuffers();
//
//	if ( m_firstInstance )
//	{
//		// @todo move to constructor ? yes, but only when dynamic management of state for Light and Texture would be done
//
//		// This is the first instance of this class.
//
//		// Do some initialization
//		// and don't do the same for any others instances if populateNodeRegistry returns true
//		m_firstInstance = (populateNodeRegistry() == false);
//	}
//
//	//if ( m_firstInstance == false )
//	//{
//		::vge::engine::Engine::reset();
//	//}
//}
//
//
//
//void Engine::setToDefaults()
//{
//	if ( isGLContextCurrent() == false )
//	{
//		return;
//	}
//
//	// MARKER
//	if ( isGL_GREMEDY_string_marker() )
//	{
//		std::stringstream ss;
//		ss << "BEGIN( Engine::setToDefaults() )";
//		glStringMarkerGREMEDY( 0, ss.str().c_str() );
//	}
//
//	// GLOBAL INITIALIZATION
//	glEnable( GL_LIGHTING );
//
//	if ( false /*isGL_EXT_rescale_normal() */)		// @todo uncomment and test with GLSL
//	{
//		vgLogDebug( "vgeGLBase.Engine: GL_EXT_rescale_normal extension detected and used." );
//		glEnable( GL_RESCALE_NORMAL );  // gle: GL_EXT_rescale_normal
//	}
//	else
//	{
//		glEnable( GL_NORMALIZE );
//	}
//
//	if ( isGL_EXT_separate_specular_color() )
//	{
//		vgLogDebug( "vgeGLBase.Engine: GL_EXT_separate_specular_color extension detected." );
//		vgLogDebug( "vgeGLBase.Engine: GL_LIGHT_MODEL_COLOR_CONTROL=GL_SEPARATE_SPECULAR_COLOR" );
//		glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR );
//	}
//	else
//	{
//		vgLogDebug( "vgeGLBase.Engine: Warning : GL_EXT_separate_specular_color extension is detected" );
//		vgLogDebug( "vgeGLBase.Engine: GL_LIGHT_MODEL_COLOR_CONTROL=GL_SINGLE_COLOR" );
//		vgLogDebug( "vgeGLBase.Engine: Using both texture mapping and specular highlights would not be well supported." );
//		glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR );
//	}
//
//	// For each handler in registry, do
//	vge::handler::HandlerRegistry&	handlerRegistry= vge::handler::Handler::getClassRegistry();
//	
//	vge::handler::HandlerRegistry::HandlersSet::iterator i_handler;
//	vge::handler::HandlerRegistry::HandlersSet::iterator ie_handler;
//
//	for(	boost::tie( i_handler, ie_handler ) = handlerRegistry.getIterators();
//			i_handler != ie_handler;
//			i_handler++ )
//	{
//		(*i_handler)->setToDefaults();
//	}
//
//
//	// MARKER
//	if ( isGL_GREMEDY_string_marker() )
//	{
//		std::stringstream ss;
//		ss << "END( Engine::setToDefaults() )";
//		glStringMarkerGREMEDY( 0, ss.str().c_str() );
//	}
//}
//
//
//
//// STATE
//const Engine::GLStateStack& Engine::getGLStateStack() const
//{
//	return m_glStateStack;
//}
//
//Engine::GLStateStack& Engine::getGLStateStack()
//{
//	return m_glStateStack;
//}
//
//
//
//void Engine::pushGLSLState()
//{
//	m_glslStateStack.push();
//}
//
//void Engine::popGLSLState()
//{
//	m_glslStateStack.pop();
//	m_glslStateStack.getTop()->validate(false);
//}
//
//
//
//const GLState& Engine::getGLState() const
//{
//	const vgd::Shp< GLState > glState = m_glStateStack.getTop();
//	return *glState;
//}
//
//GLState& Engine::getGLState()
//{
//	vgd::Shp< GLState > glState = m_glStateStack.getTop();
//	return *glState;
//}
//
//
//const GLSLState& Engine::getGLSLState() const
//{
//	const vgd::Shp< GLSLState > glslState = m_glslStateStack.getTop();
//	return *glslState;
//}
//
//GLSLState& Engine::getGLSLState()
//{
//	vgd::Shp< GLSLState > glslState = m_glslStateStack.getTop();
//	return *glslState;
//}
//
//
//const Engine::UniformState& Engine::getBuiltinUniformState() const
//{
//	return m_builtinUniformState;
//}
//
//Engine::UniformState& Engine::getBuiltinUniformState()
//{
//	return m_builtinUniformState;
//}
//
//
//const Engine::UniformState& Engine::getUniformState() const
//{
//	return m_uniformState;
//}
//
//Engine::UniformState& Engine::getUniformState()
//{
//	return m_uniformState;
//}
//
//
//void Engine::setUniformRandom()
//{
//	vgm::Vec4f random(
//		static_cast<float>(rand()) / 32767.f,
//		static_cast<float>(rand()) / 32767.f,
//		static_cast<float>(rand()) / 32767.f,
//		static_cast<float>(rand()) / 32767.f );
//
//	vgAssertN( !getBuiltinUniformState().isUniform( "random" ), "Uniform named 'random' already used" );
//	getBuiltinUniformState().addUniform( "random", random );
//}
//
//
//void Engine::setUniformTime()
//{
//	const vgd::basic::TimeDuration duration = getElapsedTime();
//	vgAssertN( !getBuiltinUniformState().isUniform( "time" ), "Uniform named 'time' already used" );
//	getBuiltinUniformState().addUniform( "time", static_cast<int>(duration.ms()) );
//}
//
//
//void Engine::setUniformNearFarAndViewport()
//{
//	const vgm::Vec2f nearFar = getNearFar();
//	vgAssert( nearFar.isValid() );
//
//	const vgm::Rectangle2i& viewport = getViewport();
//
//	vgAssertN( !getBuiltinUniformState().isUniform( "nearFar"), "Uniform named 'nearFar' already used" );
//	getBuiltinUniformState().addUniform( "nearFar", nearFar );
//
//	vgAssertN( !getBuiltinUniformState().isUniform( "viewport"), "Uniform named 'viewport' already used" );
//	getBuiltinUniformState().addUniform( "viewport", vgm::Vec4f(viewport) );
//}
//
//
//
//const vgd::Shp< vgeGLBase::engine::GLSLState > Engine::getGlobalGLSLState() const
//{
//	return m_globalGLSLState;
//}
//
//
//void Engine::setGlobalGLSLState( vgeGLBase::engine::GLSLState& state )
//{
//	m_globalGLSLState.reset( new vgeGLBase::engine::GLSLState( state ) );
//}
//
//
//const Engine::OutputBufferPropertyStateContainer& Engine::getOutputBufferProperties() const
//{
//	return m_globalGLSLState->outputBufferProperties;
//}
//
//
//vgd::Shp< glo::FrameBufferObject > Engine::getOutputBuffers() const
//{
//	return m_outputBuffers;
//}
//
//void Engine::setOutputBuffers( vgd::Shp< glo::FrameBufferObject > buffers )
//{
//	m_outputBuffers = buffers;
//}
//
//
//
//// CURRENT PRIVATE OUTPUT BUFFERS
//void Engine::setCurrentPrivateOutputBuffers( const int which )
//{
//	m_currentPrivateOutputBuffers.clear();
//
//	if ( which >= 0 )
//	{
//		m_currentPrivateOutputBuffers.push_back( which );
//	}
//	// else nothing to do
//}
//
//
//void Engine::setCurrentPrivateOutputBuffers( const int which0, const int which1 )
//{
//	m_currentPrivateOutputBuffers.clear();
//
//	if ( which0 >= 0 )
//	{
//		m_currentPrivateOutputBuffers.push_back( which0 );
//	}
//	// else nothing to do
//
//	if ( which1 >= 0 )
//	{
//		m_currentPrivateOutputBuffers.push_back( which1 );
//	}
//	// else nothing to do
//}
//
//
//void Engine::updateFromCurrentPrivateDrawBuffers( std::vector< int >& drawBuffers ) const
//{
//	vgd::basic::IndexContainerConstIterator i, iEnd;
//	for(	boost::tie(i, iEnd) = getCurrentPrivateOutputBuffersIterators();
//			i != iEnd;
//			++i )
//	{
//		const int outputBufferIndex = (*i);
//		drawBuffers[outputBufferIndex] = outputBufferIndex;
//	}
//}
//
//
//const vgd::basic::IndexContainer& Engine::getCurrentPrivateOutputBuffers() const
//{
//	return m_currentPrivateOutputBuffers;
//}
//
//
//vgd::basic::IndexContainerConstIterators Engine::getCurrentPrivateOutputBuffersIterators() const
//{
//	return std::make_pair( m_currentPrivateOutputBuffers.begin(), m_currentPrivateOutputBuffers.end() );
//}
//
//
//
//// MANAGER
//vgd::Shp< Engine::GLManagerType > Engine::getGLManager()
//{
//	return m_glManager;
//}
//
//
//vgd::Shp< Engine::GLSLProgramManagerType > Engine::getGLSLManager()
//{
//	return m_glslManager;
//}
//
//
//vgd::Shp< Engine::GLSLProgramManagerExtType > Engine::getGLSLManagerExt()
//{
//	return m_glslManagerExt;
//}
//
//
//const bool Engine::isLightingEnabled() const
//{
//	return m_isLightingEnabled;
//}
//
//
//
//const bool Engine::setLightingEnabled( const bool enabled )
//{
//	const bool retVal = m_isLightingEnabled;
//	m_isLightingEnabled = enabled;
//	return retVal;
//}
//
//
//
//const bool Engine::isTextureMappingEnabled() const
//{
//	return m_isTextureMappingEnabled;
//}
//
//
//
//const bool Engine::setTextureMappingEnabled( const bool enabled )
//{
//	const bool retVal = m_isTextureMappingEnabled;
//	m_isTextureMappingEnabled = enabled;
//	return retVal;
//}
//
//
//
//const bool Engine::isDrawCallsEnabled() const
//{
//	return m_isDrawCallsEnabled;
//}
//
//
//
//const bool Engine::setDrawCallsEnabled( const bool enabled )
//{
//	const bool retVal = m_isDrawCallsEnabled;
//	m_isDrawCallsEnabled = enabled;
//	return retVal;
//}
//
//
//
//const bool Engine::isDisplayListEnabled() const
//{
//	return m_isDisplayListEnabled;
//}
//
//
//
//void Engine::setDisplayListEnabled( const bool enabled )
//{
//	m_isDisplayListEnabled = enabled;
//}
//
//
//
//const bool Engine::isDepthPrePassEnabled() const
//{
//	return m_isDepthPrePassEnabled;
//}
//
//
//
//void Engine::setDepthPrePassEnabled( const bool enabled )
//{
//	m_isDepthPrePassEnabled = enabled;
//}
//
//
//
//const bool Engine::isShadowEnabled() const
//{
//	return m_isShadowEnabled;
//}
//
//
//
//const bool Engine::setShadowEnabled( const bool enabled )
//{
//	const bool retVal = m_isShadowEnabled;
//	m_isShadowEnabled = enabled;
//	return retVal;
//}
//
//
//
//const bool Engine::isDSAEnabled() const
//{
//	return glo::isDSAEnabled();
//}
//
//
//
//const bool Engine::setDSAEnabled( const bool enabled )
//{
//	return glo::setDSAEnabled(enabled);
//}
//
//
//
//// 
///**
// * @todo All OpenGL objects are destroyed by this method. Not very cute.
// */
//void Engine::setGLSLEnabled( const bool isEnabled )
//{
//	m_isGLSLEnabled = isEnabled;
//
//	// @todo FIXME
//	//getGLManager().clear();			///< not very cute
//}
//
//
//
//const bool Engine::isGLSLEnabled() const
//{
//	return m_isGLSLEnabled;
//}
//
//
//
//const vgd::Shp< Engine::GLSLActivationState > Engine::getGLSLActivationState() const
//{
//	vgd::Shp< GLSLActivationState > memento( 
//		new GLSLActivationState( isGLSLEnabled(), getCurrentProgram() )
//			);
//	return memento;
//}
//
//
//
//void Engine::setGLSLActivationState( const vgd::Shp< GLSLActivationState > state )
//{
//	sethCurrentProgram( state->m_currentProgram );
//	setGLSLEnabled( state->m_isGLSLEnabled );
//}
//
//
//
//void Engine::setCurrentProgram( glo::GLSLProgram * program )
//{
//	m_currentProgram = program;
//}
//
//
//
//void Engine::sethCurrentProgram( glo::GLSLProgram * program )
//{
//	setCurrentProgram( program );
//
//	if ( program )
//	{
//		setGLSLEnabled();
//		program->use();
//	}
//	else
//	{
//		setGLSLEnabled( false );
//		glo::GLSLProgram::useFixedPaths();
//	}
//}
//
//
//
//glo::GLSLProgram * Engine::getCurrentProgram() const
//{
//	return m_currentProgram;
//}
//
//
//
//glo::GLSLProgram * Engine::gethCurrentProgram() const
//{
//	if ( isGLSLEnabled() )
//	{
//		return m_currentProgram;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//
//
//vgd::Shp< ProgramGenerator > Engine::getGLSLProgramGenerator()
//{
//	return m_glslProgramGenerator;
//}
//
//
//
////void Engine::loadShaders( const std::string& path, const std::string& regex )
////{
//	//using vgio::FilenameCollector;
//
//	//FilenameCollector filenameCollector( path );
//	//filenameCollector.setRegex( regex );
//	//const FilenameCollector::StringList& filenames = filenameCollector.run();
//
//	//for( std::list< std::string >::const_iterator	i		= filenames.begin(),
//	//												iEnd	= filenames.end();
//	//	i != iEnd;
//	//	++i )
//	//{
//	//	using ::glo::GLSLProgram;
//
//	//	// Gets the filename
//	//	const std::string filename( *i );
//
//	//	// Loads file
//	//	const std::string shaderString = GLSLProgram::loadFile( filename );
//
//	//	if ( !shaderString.empty() )
//	//	{
//	//		// File not empty, creates the shader
//	//		vgLogDebug( "vgeGLBase.Engine: Loads shader %s", filename.c_str() );
//
//	//		///@todo Creates glo::GLSLShader
//	//		GLSLProgram *program = new GLSLProgram;
//
//	//		// Determines the type of shader in the file from extension
//	//		const bool isAVertexShader = (filename.rfind( "_vs.glsl" ) != std::string::npos );
//	//		
//	//		const GLSLProgram::ShaderType shaderType = isAVertexShader ? GLSLProgram::VERTEX : GLSLProgram::FRAGMENT;
//
//	//		const bool addShaderRetVal = program->addShader( shaderString.c_str(), shaderType, true );
//
//	//		if ( addShaderRetVal )
//	//		{
//	//			// Adds it to the GLSL manager
//	//			getGLSLManager().add( filename, program );
//	//			vgLogDebug( "vgeGLBase.Engine: Shader %s successfully registered in GLSLManager", filename.c_str() );
//	//		}
//	//		else
//	//		{
//	//			vgLogDebug( "vgeGLBase.Engine: Fails to registered shader %s", filename.c_str() );
//
//	//			//const std::string infoLog = program->getInfoLog( program->getProgramObject() );??????????????????????? FIXME
//	//			//vgLogDebug( "Engine:\n%s\n", infoLog.c_str() );
//
//	//			delete program;
//	//		}
//	//	}
//	//	else
//	//	{
//	//		vgLogDebug( "vgeGLBase.Engine: Empty shader %s", filename.c_str() );
//	//	}
//	//}
////}
//
//
//
//const bool Engine::isGLContextCurrent() const
//{
//	return gleIsOpenGLCurrent();
//}
//
//
//
///**
// * @todo Use glLoadIdentity() and creates synchronizeMatricesFromEngineToGL()
// */
//void Engine::resetMatrices()
//{
//	// @todo remove me
//	//if ( isGLContextCurrent() == false )
//	//{
//	//	return;
//	//}
//
//	// STEP 1 : call method from vge::engine::Engine
//	vge::engine::Engine::resetMatrices();
//
//	// STEP 2 : update OpenGL
//	if ( /*!isGLContextCurrent() &&*/ gleGetCurrent() == 0 )
//	{
//		// FIXME not very smart.
//		return;
//	}
//	
//	// MODELVIEW
//	assert( getGeometricalMatrix().size() == 1 );
//	
//	vgm::MatrixR& 	current(	getGeometricalMatrix().getTop() );
//
//	glMatrixMode( GL_MODELVIEW );
//
//	glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );
//
//	// PROJECTION
//	assert( getProjectionMatrix().size() == 1 );
//
//	current = getProjectionMatrix().getTop();
//
//	glMatrixMode( GL_PROJECTION );
//
//	glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );
//
//	// TEXTURE
//	for(	int32	index	= 0,
//					iMax	= isTextureMappingEnabled() ? getTextureMatrix().size() : 0;
//			index < iMax;
//			++index )
//	{
//		current = getTextureMatrix().getTop( index );
//
//		activeTexture( index );
//
//		glMatrixMode( GL_TEXTURE );
//
//		glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );
//	}
//}
//
//
//void Engine::setDefaultMaxAnisotropy( const float value )
//{
//	vge::engine::Engine::setDefaultMaxAnisotropy( value );
//
//	// Invalidates Texture.parameters dirty flags.
//	vgd::Shp< GLManagerType > manager = getGLManager();
//
//	typedef std::vector< vgd::node::Node * > ContainerType;
//	typedef ContainerType::iterator ContainerIterator;
//
//	ContainerType nodes;
//	manager->gethKeys( nodes );
//
//	for( ContainerIterator	i	= nodes.begin(),
//							iEnd= nodes.end();
//		i != iEnd;
//		++i )
//	{
//		vgd::node::Texture * texture = dynamic_cast< vgd::node::Texture * >( *i );
//		if ( texture )
//		{
//			vgd::field::DirtyFlag* parametersDF = texture->getDirtyFlag( texture->getDFParameters() );
//			parametersDF->dirty();
//		}
//	}
//}
//
//const vgm::Vec2i Engine::getMaxViewportSize() const
//{
//	if ( m_maxViewportSize.isInvalid() )
//	{
//		if ( isGLContextCurrent() )
//		{
//			GLint viewportSize[2];
//
//			glGetIntegerv( GL_MAX_VIEWPORT_DIMS, &viewportSize[0] );
//			m_maxViewportSize.setValue( viewportSize[0], viewportSize[1] );
//		}
//		else
//		{
//			vgLogDebug("Engine::getMaxViewportSize(): OpenGL context not current, so return arbitrary value (4096,4096).");
//			return vgm::Vec2i(4096,4096);
//		}
//	}
//
//	return m_maxViewportSize;
//}
//
//
//
//const int Engine::getMaxLights() const
//{
//	if ( m_maxLights == 0 )
//	{
//		if ( isGLContextCurrent() )
//		{
//			// @todo
//			glGetIntegerv(GL_MAX_LIGHTS, &m_maxLights );
//			m_maxLights = 4;
//		}
//		else
//		{
//			vgLogDebug("Engine::getMaxLights(): OpenGL context not current, so return arbitrary value 4.");
//			return 4;
//		}
//	}
//
//	return m_maxLights;
//}
//
//
//
//const int Engine::getMaxTexUnits() const
//{
//	const uint maxTexUnits = 6;
//	//const uint maxTexUnits = 16 AMD; 32 NV
//
//	if ( m_maxTexUnits == 0 )
//	{
//		if ( isGLContextCurrent() )
//		{
//			// @todo
//			glGetIntegerv( GL_MAX_TEXTURE_UNITS, &m_maxTexUnits );
//			m_maxTexUnits = maxTexUnits;
//		}
//		else
//		{
//			vgLogDebug("Engine::getMaxTexUnits(): OpenGL context not current, so return arbitrary value %i.", maxTexUnits);
//			return maxTexUnits;
//		}
//	}
//
//	return m_maxTexUnits;
//}
//
//
//
//const int Engine::getMaxTexSize() const
//{
//	if ( m_maxTexSize == 0 )
//	{
//		glGetIntegerv( GL_MAX_TEXTURE_SIZE, &m_maxTexSize );
//	}
//
//	return m_maxTexSize;
//}
//
//
//
//const int Engine::getMax3DTexSize() const
//{
//	if ( m_max3DTexSize == 0 )
//	{
//		glGetIntegerv( GL_MAX_3D_TEXTURE_SIZE, &m_max3DTexSize );
//	}
//	
//	return m_max3DTexSize;
//}
//
//
//
//const int Engine::getMaxCubeMapTexSize() const
//{
//	if ( m_maxCubeMapTexSize == 0 )
//	{
//		glGetIntegerv( GL_MAX_CUBE_MAP_TEXTURE_SIZE, &m_maxCubeMapTexSize );
//	}
//
//	return m_maxCubeMapTexSize;
//}
//
//
//
//void Engine::getGLViewport( vgm::Rectangle2i& viewport ) /*const*/
//{
//	GLint viewportGL[4];
//
//	glGetIntegerv( GL_VIEWPORT, viewportGL );
//
//	viewport.set( viewportGL[0], viewportGL[1], viewportGL[2], viewportGL[3] );
//}
//
//
//
//const int Engine::getGLDepthBits() /* const */
//{
//	GLint depthBits;
//	glGetIntegerv( GL_DEPTH_BITS, &depthBits );
//
//	return depthBits;
//}
//
//
//
//const GLenum Engine::convertDepthTextureFormat( const int depthBits ) /* const */
//{
//	GLenum retVal;
//
//	switch ( depthBits )
//	{
//		case 24:
//			retVal = GL_DEPTH_COMPONENT24_ARB;
//			break;
//
//		case 32:
//			retVal = GL_DEPTH_COMPONENT32_ARB;
//			break;
//
//		case 16:
//			retVal = GL_DEPTH_COMPONENT16_ARB;
//			break;
//
//		default:
//			vgLogDebug( "vgeGLBase.Engine:getGLDepthTextureFormat(): Performance warning : No matching between given depth buffer bits and depth texture format." );
//			vgLogDebug( "vgeGLBase.Engine:getGLDepthTextureFormat(): Performance warning : Use GL_DEPTH_COMPONENT16_ARB" );
//			retVal = GL_DEPTH_COMPONENT16_ARB;
//			break;
//	}
//
//	return retVal;
//}
//
//
//
//const GLenum Engine::getGLDepthTextureFormatFromDepthBits() /*const */
//{
//	const int32 depthBits = getGLDepthBits();
//
//	const GLenum retVal = convertDepthTextureFormat(depthBits);
//
//	return retVal;
//}
//
//
//
//vgd::Shp< vgd::basic::Image > Engine::captureGLFramebuffer( const CaptureBufferType what ) const
//{
//	vgd::Shp< vgd::basic::Image > image;
//	void * imageData = 0;
//	captureGLFramebuffer( what, image, imageData );
//
//	return image;
//}
//
//
//void Engine::captureGLFramebuffer( const CaptureBufferType what, vgd::Shp< vgd::basic::Image >& oImage, void *& imageData ) const
//{
//	vgd::Shp< glo::FrameBufferObject > fbo = getOutputBuffers();
//	if ( fbo && (what != COLOR) )
//	{
//		// RENDERING IN A FBO
//		vgeGLBase::technique::getImage( fbo, what, oImage, imageData );
//	}
//	else
//	{
//		// RENDERING USING OPENGL DEFAULT FRAMEBUFFER
//		if ( what == COLOR )
//		{
//			const vgm::Vec3i imageSize3i( getDrawingSurfaceSize(), 1 );
//
//			using vgd::basic::Image;
//			const bool matchingImage =	oImage && imageData &&
//										(oImage->getSize3i() == imageSize3i);/*	&&
//										/*(image->format() == myFormat)			&&
//										(image->type() == myType)*/
//
//			if ( !matchingImage )
//			{
//				// no image given or not matching (size) // @todo format or type
//#ifdef _WIN32
//				oImage.reset( new Image( imageSize3i[0], imageSize3i[1], 1, Image::BGR, Image::UINT8 ) );
//#else
//				oImage.reset( new Image( imageSize3i[0], imageSize3i[1], 1, Image::RGB, Image::UINT8 ) );
//#endif
//				imageData = static_cast<uint8*>( oImage->editPixels() );
//				oImage->editPixelsDone();
//			}
//			// else use oImage and imageData
//
//			//
//			glPixelStorei(GL_PACK_ALIGNMENT, 1);
//#ifdef _WIN32
//			glReadPixels(	0, 0, imageSize3i[0], imageSize3i[1], 
//							GL_BGR, GL_UNSIGNED_BYTE,
//							imageData );
//#else
//			glReadPixels(	0, 0, imageSize3i[0], imageSize3i[1], 
//							GL_RGB, GL_UNSIGNED_BYTE,
//							imageData );
//#endif
//		}
//		else
//		{
//			vgAssertN( false, "Capture not supported for buffer other than COLOR buffer" );
//			oImage.reset( new vgd::basic::Image() );
//			imageData = 0;
//		}
//	}
//}
//
//
//// @todo move into gle ?
//void Engine::setGLEnable( const GLenum capability, const bool isEnabled ) /*const*/
//{
//	if ( isEnabled )
//	{
//		glEnable( capability );
//	}
//	else
//	{
//		glDisable( capability );
//	}
//}
//
//
//
//void Engine::activeTexture( const int desiredTextureUnit )
//{
////	static int currentTextureUnit = 0;
//
////#ifdef _DEBUG
////	GLint glcurrentTextureUnit;
////	glGetIntegerv( GL_ACTIVE_TEXTURE_ARB, &glcurrentTextureUnit );
////	glcurrentTextureUnit -= GL_TEXTURE0_ARB;
////
////	if ( glcurrentTextureUnit != currentTextureUnit )
////	{
////		vgLogDebug( "Unexpected current active texture unit." );
////		
////		// Repairs cache
////		currentTextureUnit = glcurrentTextureUnit;
////	}
////	//assert( glcurrentTextureUnit == currentTextureUnit && "Unexpected current active texture unit." );
////
////#endif
//
//	// @todo This code is disabled => see method comments about glPush/glPop*.
////	if ( desiredTextureUnit != currentTextureUnit )
////	{
//		// Activates the desired texture unit
//		::glo::Texture::active( GL_TEXTURE0_ARB + desiredTextureUnit );
//
////		// Fills the current texture unit cache
////		currentTextureUnit = desiredTextureUnit;
////	}
//	// else nothing to do, i.e. already done
//}
//
//
//
//void Engine::activeTexture( const vgd::node::Texture * textureNode )
//{
//	const int desiredTextureUnit = textureNode->getMultiAttributeIndex();
//
//	activeTexture( desiredTextureUnit );
//}
//
//
//
//void Engine::clearTextureUnits( const int begin, const int end )
//{
//	int32 iMax;
//	if (end == -1)
//	{
//		iMax = isTextureMappingEnabled() ? getTextureMatrix().size() : 0;
//	}
//	else
//	{
//		iMax = end;
//	}
//
//	for(	int32	index	= begin;
//			index < iMax;
//			++index )
//	{
//		activeTexture( index );
//		glBindTexture( GL_TEXTURE_2D, 0 );
//	}
//}
//
//
//
//void Engine::begin2DRendering( const vgm::Rectangle2i * optionalViewport, const bool pushAttribs )
//{
//	// OpenGL attributes
//	if ( pushAttribs )
//	{
//		glPushAttrib( GL_ALL_ATTRIB_BITS );
//	}
//
//	glDisable( GL_LIGHTING );
//	glDisable( GL_DEPTH_TEST );
//
//	// Viewport and scissor
//	vgm::Rectangle2i viewport;
//	if ( optionalViewport )
//	{
//		viewport = (*optionalViewport);
//	}
//	else
//	{
//		// @todo Uses engine.viewport ? glEngine must be a method param or remove static
//		getGLViewport( viewport );
//		//
//		// assert( viewport == getViewport() ); // ???
//	}
//
//	glViewport( viewport[0], viewport[1], viewport[2], viewport[3] );
//
//	glScissor( viewport[0], viewport[1], viewport[2], viewport[3] );
//	glEnable(GL_SCISSOR_TEST);
//
//	// Matrix stacks
//	glMatrixMode( GL_MODELVIEW );
//	glPushMatrix();
//	glLoadIdentity();
//
//	glMatrixMode( GL_PROJECTION );
//	glPushMatrix();
//	glLoadIdentity();
//	glOrtho( 0.f, 1.f, 0.f, 1.f, 0.f, 1.f );
//
//	glMatrixMode( GL_TEXTURE );
//	for(	int8	i		= 0,
//					iMax	= 1; //static_cast< int8 >(getMaxTexUnits()); // @todo OPTME
//			i < iMax;
//			++i )
//	{
//		activeTexture(i);
//		glPushMatrix();
//		glLoadIdentity();
//	}
//}
//
//
//
//void Engine::end2DRendering( const bool popAttribs )
//{
//	// Matrix stacks
//	glMatrixMode( GL_TEXTURE );
//	for(	int8	i		= 0,
//					iMax	= 1; //static_cast< int8 >(getMaxTexUnits()); // @todo OPTME
//			i < iMax;
//			++i )
//	{
//		activeTexture(i);
//		glPopMatrix();
//	}
//
//	glMatrixMode( GL_PROJECTION );
//	glPopMatrix();
//
//	glMatrixMode( GL_MODELVIEW );
//	glPopMatrix();
//
//	// OpenGL attributes
//	if ( popAttribs )
//	{
//		glPopAttrib();
//	}
//}
//
//
//
//void Engine::push()
//{
//	m_glslStateStack.push();
//	getGLStateStack().push();
//
//	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
//	glPushAttrib( GL_ALL_ATTRIB_BITS );
//
//	vge::engine::Engine::push();
//}
//
//
//void Engine::pop()
//{
//	vge::engine::Engine::pop();
//
//	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
//	glPopAttrib();
//
//	getGLStateStack().pop();
//	m_glslStateStack.pop();
//
//	getBuiltinUniformState().clear(); // @todo push/pop too
//	getUniformState().clear(); // @todo push/pop too
//}
//
//
//
//bool Engine::populateNodeRegistry()
//{
//	// DirectionalLight
//	for(	int8	i		= 1,
//					iMax	= static_cast< int8 >(getMaxLights());
//			i < iMax;
//			++i )
//	{
//		vgd::basic::RegisterNode< vgd::node::DirectionalLight >	registerNode( i );
//	}
//
//	// TextureMatrixTransform, Texture2D, TextureCubeMap
//	for(	int8	i		= 1,
//					iMax	= static_cast< int8 >(getMaxTexUnits());
//			i < iMax;
//			++i )
//	{
//		vgd::basic::RegisterNode< vgd::node::Texture2D >				registerNode1( i );
//		vgd::basic::RegisterNode< vgd::node::TextureMatrixTransform >	registerNode2( i );
//		//vgd::basic::RegisterNode< vgd::node::TextureCubeMap>			registerNode3( i );
//	}
//
//	// @todo remove this returned value
//	return true;
//}
//
//
//
//const Engine::GLSLStateStack& Engine::getGLSLStateStack() const
//{
//	return m_glslStateStack;
//}
//
//Engine::GLSLStateStack& Engine::getGLSLStateStack()
//{
//	return m_glslStateStack;
//}
//
//
//
////Engine::GLManagerType			Engine::m_glManager("GL object manager");
//
////Engine::GLSLProgramManagerType	Engine::m_glslManager("GLSL Program Manager");
//
//bool							Engine::m_firstInstance = true;
//
//
//
//} // namespace engine
//
//} // namespace vgeGLBase
//