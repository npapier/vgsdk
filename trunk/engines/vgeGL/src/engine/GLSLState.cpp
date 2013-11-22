// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, 2012, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/GLSLState.hpp"

#include <vgd/basic/toString.hpp>
#include <vgd/node/LightModel.hpp>
#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace engine
{



namespace
{
	static const std::string defaultVertexGLPositionComputation = "	gl_Position = gl_ModelViewProjectionMatrix * position;\n";
	static const std::string defaultVertexECPositionComputation = "	ecPosition	= gl_ModelViewMatrix * position;\n";
	static const std::string defaultVertexECNormalComputation	= "	ecNormal	= normalize( gl_NormalMatrix * normal );\n";

	static const std::string defaultFragmentOutput				= "	gl_FragData[0] = color;\n";
}



const std::string GLSLState::m_indexString[] =
	{
		"LIGHTING",
		"PER_PIXEL_LIGHTING",
		"LOCAL_VIEWER",
		"TWO_SIDED_LIGHTING",

		"DIRECTIONAL_LIGHT",
		"POINT_LIGHT",
		"SPOT_LIGHT",
		"SPOT_LIGHT_CASTING_SHADOW",

		"CLIPPING_PLANE",

		"FLAT_SHADING",

		"POINT_STYLE",

		"PROGRAM",

		"COLOR4_BIND_PER_VERTEX",

		"IGNORE_POST_PROCESSING",

		"BUMP_MAPPING",

		"TESSELLATION",

		"GEOMORPH"
	};



const std::string& GLSLState::toString( const GLSLStateIndex bitSetIndexType )
{
	vgAssertN( bitSetIndexType >= 0, "Out of range index." );
	vgAssertN( bitSetIndexType < MAX_BITSETINDEXTYPE, "Out of range index." );

	return m_indexString[bitSetIndexType];
}



GLSLState::GLSLState( const uint maxTexUnits )
:	//lights(),
	textures(maxTexUnits),
	//decals(),
	//postProcessing(),
	//outputBufferProperties()
	//overlays(),
	m_dirtyFlag( "GLSLState" )
{
	init();
}


GLSLState::GLSLState( const GLSLState& src )
:	vgeGL::engine::TBitSet< MAX_BITSETINDEXTYPE >	(	src							),

	lights											(	src.lights					),
	textures										(	src.textures				),
	decals											(	src.decals					),
	postProcessing									(	src.postProcessing			),
	outputBufferProperties							(	src.outputBufferProperties	),
	overlays										(	src.overlays				),

	m_dirtyFlag										(	src.m_dirtyFlag				),

	m_program										(	src.m_program				),
	m_shaderStage									(	src.m_shaderStage			),
	m_lightModelShadow								(	src.m_lightModelShadow		),
	m_shadowMapType									(	src.m_shadowMapType			)
{}



GLSLState& GLSLState::operator = ( const GLSLState& src )
{
	if ( this != &src )
	{
		release();
		copy( src );
	}
	// else nothing to do, self assign

	return *this;
}



void GLSLState::resetToDefault()
{
	// TBitSet
	vgeGL::engine::TBitSet< MAX_BITSETINDEXTYPE >::reset();

	// LIGHT / TEXTURE /DECALS / POST PROCESSING / OVERLAY / OUTPUT BUFFER PROPERTY
	lights.clear();
	textures.clear();
	decals.clear();
	postProcessing.clear();
	outputBufferProperties.clear();
	overlays.clear();

	init();

	m_dirtyFlag.dirty();
}



void GLSLState::setEnabled( const uint index, const bool enabled )
{
	if ( isEnabled(index) != enabled )
	{
		vgeGL::engine::TBitSet< MAX_BITSETINDEXTYPE >::setEnabled( index, enabled );
		m_dirtyFlag.dirty();
	}
	//else nothing to do
}



void GLSLState::reset()
{
	vgeGL::engine::TBitSet< MAX_BITSETINDEXTYPE >::reset();
	m_dirtyFlag.dirty();
}



const bool GLSLState::isLightingEnabled() const
{
	return isEnabled( LIGHTING );
}


void GLSLState::setLightingEnabled( const bool enabled )
{
	setEnabled( LIGHTING, enabled );
}


const bool GLSLState::isTwoSidedLightingEnabled() const
{
	return isEnabled( TWO_SIDED_LIGHTING );
}


void GLSLState::setTwoSidedLightingEnabled( const bool enabled )
{
	setEnabled( TWO_SIDED_LIGHTING, enabled );
}


const bool GLSLState::isPerPixelLightingEnabled() const
{
	return isEnabled( PER_PIXEL_LIGHTING );
}


const bool GLSLState::isPerVertexLightingEnabled() const
{
	return !isPerPixelLightingEnabled();
}


void GLSLState::setPerPixelLightingEnabled( const bool enabled )
{
	setEnabled( PER_PIXEL_LIGHTING, enabled );
}

const bool GLSLState::isBumpMappingEnabled() const
{
	return isEnabled(BUMP_MAPPING);
}

void GLSLState::setBumpMappingEnabled( const bool value )
{
	setEnabled( BUMP_MAPPING, value );
}

const bool GLSLState::isTessellationEnabled() const
{
	return isEnabled(TESSELLATION);
}

void GLSLState::setTessellationEnabled( const bool enabled )
{
	setEnabled( TESSELLATION, enabled );
}


const bool GLSLState::isDirty() const
{
	return	m_dirtyFlag.isDirty()				||
			textures.isDirty()					||
			lights.isDirty()					||
			outputBufferProperties.isDirty()	||
			decals.isDirty()					||
			postProcessing.isDirty()			||
			overlays.isDirty();
}


const bool GLSLState::isValid() const
{
	return	m_dirtyFlag.isValid()				&&
			textures.isValid()					&&
			lights.isValid()					&&
			outputBufferProperties.isValid() 	&&
			decals.isValid()					&&
			postProcessing.isValid()			&&
			overlays.isValid();
}


void GLSLState::validate( const bool setToValid )
{
	m_dirtyFlag.validate( setToValid );
	textures.validate( setToValid );
	lights.validate( setToValid );
	outputBufferProperties.validate( setToValid );
	decals.validate( setToValid );
	postProcessing.validate( setToValid );
	overlays.validate( setToValid );
}


const uint GLSLState::getPrivateTexUnitIndex( const uint index ) const
{
	const uint retVal = (textures.getMax()-1) - index;
	return retVal;
}



const std::string GLSLState::getPrivateTexUnit( const uint index ) const
{
	const uint retVal = getPrivateTexUnitIndex( index );
	return vgd::basic::toString(retVal);
}



const uint GLSLState::getPrivateIndex( const uint privateTexUnitIndex )
{
	const uint retVal = (textures.getMax()-1) - privateTexUnitIndex;
	return retVal;
}



const std::string GLSLState::getPrivate( const uint privateTexUnitIndex )
{
	const uint retVal = getPrivateIndex( privateTexUnitIndex );
	return vgd::basic::toString(retVal);
}



vgd::node::Program * GLSLState::getProgram() const
{
	return m_program;
}



void GLSLState::setProgram( vgd::node::Program * program )
{
	if ( m_program != program )
	{
		m_program = program;
		m_dirtyFlag.dirty();
	}
}



void GLSLState::setShaderStage( const ShaderStage shaderStage, const std::string& glslCode )
{

// @todo section marker // begin	VERTEX_ECNORMAL_COMPUTATION
//						// end		VERTEX_ECNORMAL_COMPUTATION
// in getShaderStage() only ?
	if ( m_shaderStage[shaderStage] != glslCode )
	{
		m_shaderStage[shaderStage] = glslCode;
		m_dirtyFlag.dirty();
	}
}



void GLSLState::resetShaderStages()
{
	// SHADER STAGE
	m_shaderStage.clear();
	m_shaderStage.resize( MAX_SHADERSTAGE );

	//setShaderStage( VERTEX_GL_POSITION_COMPUTATION, defaultVertexGLPositionComputation );
	m_shaderStage[VERTEX_GL_POSITION_COMPUTATION] = defaultVertexGLPositionComputation;

	//setShaderStage( VERTEX_ECPOSITION_COMPUTATION, defaultVertexECPositionComputation );
	m_shaderStage[VERTEX_ECPOSITION_COMPUTATION] = defaultVertexECPositionComputation;


	//setShaderStage( VERTEX_ECNORMAL_COMPUTATION, defaultVertexECNormalComputation );
	m_shaderStage[VERTEX_ECNORMAL_COMPUTATION] = defaultVertexECNormalComputation;


	//setShaderStage( FRAGMENT_OUTPUT, defaultFragmentOutput );
	m_shaderStage[FRAGMENT_OUTPUT] = defaultFragmentOutput;
}



const std::string& GLSLState::getShaderStage( const ShaderStage shaderStage ) const
{
	return m_shaderStage[shaderStage];
}



void GLSLState::copy( const GLSLState& src )
{
	m_bitset				= src.m_bitset;

	lights					= src.lights;
	textures				= src.textures;
	decals					= src.decals;
	postProcessing			= src.postProcessing;
	outputBufferProperties	= src.outputBufferProperties;
	overlays				= src.overlays;

	m_dirtyFlag				= src.m_dirtyFlag;

	m_program					= src.m_program;
	m_shaderStage				= src.m_shaderStage;
	m_lightModelShadow			= src.m_lightModelShadow;
	m_shadowMapType				= src.m_shadowMapType;
}



void GLSLState::release()
{
	lights.clear();
	textures.clear();
	decals.clear();
	postProcessing.clear();
	outputBufferProperties.clear();
	overlays.clear();

	m_shaderStage.clear();
}



void GLSLState::init()
{
	m_program					= 0;

	resetShaderStages();

	//
	m_lightModelShadow			= vgd::node::LightModel::DEFAULT_SHADOW;
	m_shadowMapType				= vgd::node::LightModel::DEFAULT_SHADOWMAPTYPE;
}


} // namespace engine

} // namespace vgeGL
