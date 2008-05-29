// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/Engine.hpp"

#include <glo/Texture.hpp>
#include <vgDebug/Global.hpp>
#include <vgd/node/DirectionalLight.hpp>
#include <vgd/node/Texture2D.hpp>
//#include <vgd/node/TextureCubeMap.hpp>
#include <vgd/node/TextureMatrixTransform.hpp>
#include <vge/handler/Handler.hpp>
#include <vge/handler/HandlerRegistry.hpp>



namespace vgeGL
{

namespace engine
{



Engine::Engine()
{}



void Engine::reset()
{
	if ( isGLContextCurrent() == false )
	{
		return;
	}

	// Reset cache
	m_maxLights = m_maxTexUnits = m_maxTexSize = m_max3DTexSize = m_maxCubeMapTexSize = 0;

	m_texture.clear();
	m_texture.resize( getMaxTexUnits() );

	if ( m_firstInstance )
	{
		// This is the first instance of this class.

		// Do some initialization
		// and don't do the same for any others instances if populateNodeRegistry returns true
		m_firstInstance = (populateNodeRegistry() == false);
	}

	if ( m_firstInstance == false )
	{
		::vge::engine::Engine::reset();
	}
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
	
//	glEnable( GL_NORMALIZE );

	if ( isGL_EXT_rescale_normal() )
	{
		vgDebug::get().logDebug( "vgeGL.Engine: GL_EXT_rescale_normal extension detected and used." );
		glEnable( GL_RESCALE_NORMAL );  // gle: GL_EXT_rescale_normal
	}
	else
	{
		glEnable( GL_NORMALIZE );
	}

	if ( isGL_EXT_separate_specular_color() )
	{
		vgDebug::get().logDebug( "vgeGL.Engine: GL_EXT_separate_specular_color extension detected." );
		vgDebug::get().logDebug( "vgeGL.Engine: GL_LIGHT_MODEL_COLOR_CONTROL=GL_SEPARATE_SPECULAR_COLOR" );
		glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR );
	}
	else
	{
		vgDebug::get().logDebug( "vgeGL.Engine: Warning : GL_EXT_separate_specular_color extension is detected" );
		vgDebug::get().logDebug( "vgeGL.Engine: GL_LIGHT_MODEL_COLOR_CONTROL=GL_SINGLE_COLOR" );
		vgDebug::get().logDebug( "vgeGL.Engine: Using both texture mapping and specular highlights would not be well supported." );
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
	vgDebug::get().logDebug( "vgeGL.Engine:GL_MAX_LIGHTS			= %i", getMaxLights() );
	vgDebug::get().logDebug( "vgeGL.Engine:GL_MAX_TEXTURE_UNITS		= %i", getMaxTexUnits() );
	vgDebug::get().logDebug( "vgeGL.Engine:GL_MAX_TEXTURE_SIZE		= %i", getMaxTexSize() );
	vgDebug::get().logDebug( "vgeGL.Engine:GL_MAX_3D_TEXTURE_SIZE		= %i", getMax3DTexSize() );
	vgDebug::get().logDebug( "vgeGL.Engine:GL_MAX_CUBE_MAP_TEXTURE_SIZE	= %i", getMaxCubeMapTexSize() );
}



vge::rc::Manager& Engine::getGLManager()
{
	return m_glManager;
}



const bool Engine::isGLContextCurrent() const
{
	// FIXME: founded a smarter method to test if OpenGL is current.
	const GLubyte *pString = glGetString(GL_EXTENSIONS);
	return ( pString != 0 );
}


	
void Engine::resetMatrices()
{
	if ( isGLContextCurrent() == false )
	{
		return;
	}
	
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



const int32 Engine::getMaxLights() const
{
	if ( m_maxLights == 0 )
	{
		glGetIntegerv(GL_MAX_LIGHTS, &m_maxLights );
	}

	return m_maxLights;
}
	
	
	
const int32 Engine::getMaxTexUnits() const
{
	if ( m_maxTexUnits == 0 )
	{
		glGetIntegerv( GL_MAX_TEXTURE_UNITS, &m_maxTexUnits );
	}

	return m_maxTexUnits;
}



const int32 Engine::getMaxTexSize() const
{
	if ( m_maxTexSize == 0 )
	{
		glGetIntegerv( GL_MAX_TEXTURE_SIZE, &m_maxTexSize );
	}

	return m_maxTexSize;
}



const int32 Engine::getMax3DTexSize() const
{
	if ( m_max3DTexSize == 0 )
	{
		glGetIntegerv( GL_MAX_3D_TEXTURE_SIZE, &m_max3DTexSize );
	}
	
	return m_max3DTexSize;
}



const int32 Engine::getMaxCubeMapTexSize() const
{
	if ( m_maxCubeMapTexSize == 0 )
	{
		glGetIntegerv( GL_MAX_CUBE_MAP_TEXTURE_SIZE, &m_maxCubeMapTexSize );
	}

	return m_maxCubeMapTexSize;
}



void Engine::getViewport( vgm::Rectangle2i& viewport ) const
{
	GLint viewportGL[4];
	
	glGetIntegerv( GL_VIEWPORT, viewportGL );

	viewport.set( viewportGL[0], viewportGL[1], viewportGL[2], viewportGL[3] );
}



const int32 Engine::getDepthBits() const
{
	GLint depthBits;
	glGetIntegerv( GL_DEPTH_BITS, &depthBits );

	return depthBits;
}



const GLenum Engine::getDepthTextureFormatFromDepthBits() const
{
	GLenum retVal;

	const int32 depthBits = getDepthBits();
	
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
			vgDebug::get().logDebug( "vgeGL.Engine:getDepthTextureFormatFromDepthBits(): Performance warning : No matching between depth buffer bits and depth texture format." );
			vgDebug::get().logDebug( "vgeGL.Engine:getDepthTextureFormatFromDepthBits(): Performance warning : Use GL_DEPTH_COMPONENT16_ARB" );
			retVal = GL_DEPTH_COMPONENT16_ARB;
			break;
	}

	return retVal;
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
//		vgDebug::get().logDebug( "Unexpected current active texture unit." );
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



::glo::Texture *Engine::getTexture( const int indexTexUnit )
{
	assert( indexTexUnit >= 0 && "Invalid texture unit index." );
	assert( indexTexUnit < getMaxTexUnits() && "Invalid texture unit index." );

	return m_texture[indexTexUnit];
}



::glo::Texture *Engine::setTexture( const int indexTexUnit, ::glo::Texture * texture )
{
	assert( indexTexUnit >= 0 && "Invalid texture unit index." );
	assert( indexTexUnit < getMaxTexUnits() && "Invalid texture unit index." );

	::glo::Texture * oldTexture = m_texture[indexTexUnit];

	m_texture[indexTexUnit] = texture;

	return oldTexture;
}



bool Engine::populateNodeRegistry()
{
	if ( isGLContextCurrent() )
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
		
		return true;
	}
	else
	{
		return false;
	}
}



vge::rc::Manager	Engine::m_glManager;

bool				Engine::m_firstInstance				= true;



} // namespace engine

} // namespace vgeGL
