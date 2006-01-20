// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/Engine.hpp"

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



void Engine::reset()
{
	if ( isGLContextCurrent() == false )
	{
		return;
	}

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
	glEnable( GL_NORMALIZE );
	
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
	vgDebug::get().logDebug( "GL_MAX_LIGHTS				= %i", getMaxLights() );
	vgDebug::get().logDebug( "GL_MAX_TEXTURE_UNITS		= %i", getMaxTexUnits() );
	vgDebug::get().logDebug( "GL_MAX_TEXTURE_SIZE		= %i", getMaxTexSize() );
}



vge::rc::Manager& Engine::getGLManager()
{
	return ( m_glManager );
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
		
		gleGetCurrent()->glActiveTextureARB( GL_TEXTURE0_ARB + index );
		
		glMatrixMode( GL_TEXTURE );

		glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );
	}
}



int32 Engine::getMaxLights() const
{
	GLint	maxLights;

	glGetIntegerv(GL_MAX_LIGHTS, &maxLights );
	
	return ( maxLights );
}
	
	
	
int32 Engine::getMaxTexUnits() const
{
	GLint maxTexUnits;

	glGetIntegerv( GL_MAX_TEXTURE_UNITS, &maxTexUnits );

	return ( maxTexUnits );
}



int32 Engine::getMaxTexSize() const
{
	GLint	maxTexSize;
	
	glGetIntegerv( GL_MAX_TEXTURE_SIZE, &maxTexSize );
	
	return ( maxTexSize );
}



int32 Engine::getMax3DTexSize() const
{
	GLint	maxTexSize;
	
	glGetIntegerv( GL_MAX_3D_TEXTURE_SIZE, &maxTexSize );
	
	return ( maxTexSize );
}



void Engine::getViewport( vgm::Rectangle2i& viewport ) const
{
	GLint viewportGL[4];
	
	glGetIntegerv( GL_VIEWPORT, viewportGL );
	
	viewport.set( viewportGL[0], viewportGL[1], viewportGL[2], viewportGL[3] );
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
		
		return ( true );
	}
	else
	{
		return ( false );
	}
}



vge::rc::Manager	Engine::m_glManager;

bool				Engine::m_firstInstance				= true;



} // namespace engine

} // namespace vgeGL
