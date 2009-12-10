// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/TexGen.hpp"

#include <vgd/node/TexGen.hpp>
#include <vgDebug/convenience.hpp>
#include "vgeGL/engine/Engine.hpp"
//#include "vgeGL/rc/TDisplayListHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



void TexGen::apply( vgeGL::engine::Engine * engine, vgd::node::TexGen * texGen )
{
	const uint texUnit = texGen->getMultiAttributeIndex();

	// Updates engine state
	using vgeGL::engine::GLSLState;
	typedef GLSLState::TexUnitState TexUnitState;

	GLSLState& glslState = engine->getGLSLState();

	vgd::Shp< TexUnitState > texUnitState( glslState.getTexture( texUnit ) );
	if ( texUnitState )
	{
		// Updates the existing texture unit state
		texUnitState->setTexGenNode( texGen );
		texUnitState->setTexCoordDim( 2 /* @todo FIXME not always 2 */ );
	}
	else
	{
		// Creates the new texture unit state
		texUnitState.reset( new GLSLState::TexUnitState(0, 0, 2 /*@todo FIXME not always 2*/, texGen) );
		glslState.setTexture( texUnit, texUnitState );
	}
}



void TexGen::paint( vgeGL::engine::Engine * engine, vgd::node::TexGen * texGen )
{
	// Activates the desired texture unit
	const int texUnit = texGen->getMultiAttributeIndex();

	engine->activeTexture( texUnit );

	// ON
	vgd::node::TexGen::OnValueType onValue = texGen->getOn();

	if ( onValue )
	{
		glEnable( GL_TEXTURE_GEN_S );
		glEnable( GL_TEXTURE_GEN_T );
		glEnable( GL_TEXTURE_GEN_R );
		glEnable( GL_TEXTURE_GEN_Q );
	}
	else
	{
		glDisable( GL_TEXTURE_GEN_S );
		glDisable( GL_TEXTURE_GEN_T );
		glDisable( GL_TEXTURE_GEN_R );
		glDisable( GL_TEXTURE_GEN_Q );
	}
}



void TexGen::paint( const GLenum textureGenModeValue, const GLenum planeType, /*const */vgm::MatrixR& params )
{
	glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, textureGenModeValue );
	glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, textureGenModeValue );
	glTexGeni( GL_R, GL_TEXTURE_GEN_MODE, textureGenModeValue );
	glTexGeni( GL_Q, GL_TEXTURE_GEN_MODE, textureGenModeValue );

	glTexGenfv( GL_S, planeType, params.getColumn(0).getValue() );
	glTexGenfv( GL_T, planeType, params.getColumn(1).getValue() );
	glTexGenfv( GL_R, planeType, params.getColumn(2).getValue() );
	glTexGenfv( GL_Q, planeType, params.getColumn(3).getValue() );
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
