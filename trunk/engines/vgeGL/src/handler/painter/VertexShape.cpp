// VGSDK - Copyright (C) 2004-2006, 2008-2014, Nicolas Papier, Alexandre Di Pino.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Alexandre Di Pino

#include "vgeGL/handler/painter/VertexShape.hpp"

#include <glo/GLSLProgram.hpp>
#include <glo/Texture.hpp>

#include <vgd/basic/toString.hpp>
// @todo Move Box stuff to Box handler (FIXME)
#include <vgd/node/Box.hpp>
// @todo Move DrawStyle stuff to drawStyle handler (FIXME)
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/GeoMorph.hpp>
#include <vgd/node/Grid.hpp>
#include <vgd/node/Quad.hpp>
#include <vgd/node/MultipleInstances.hpp>
#include <vgd/node/Sphere.hpp>
#include <vgd/node/Texture.hpp>
#include <vgd/node/TriSet.hpp>
#include <vgd/node/VertexShape.hpp>


//#include <vgDebug/StdStreamsToFiles.hpp>
#include <vgm/Box.hpp>

#include "vgeGL/engine/GLSLState.hpp"
#include "vgeGL/engine/FragmentShaderGenerator.hpp"
#include "vgeGL/engine/GeometryShaderGenerator.hpp"
#include "vgeGL/engine/TessellationControlShaderGenerator.hpp"
#include "vgeGL/engine/TessellationEvaluationShaderGenerator.hpp"
#include "vgeGL/engine/ProgramGenerator.hpp"
#include "vgeGL/engine/VertexShaderGenerator.hpp"

#include "vgeGL/handler/painter/DrawStyle.hpp"
#include "vgeGL/handler/painter/OutputBufferProperty.hpp"

#include "vgeGL/rc/GLSLProgram.hpp"
#include "vgeGL/rc/TDisplayListHelper.hpp"
#include "vgeGL/rc/VertexShape.hpp"

#include <sstream>

/*
supported field (VBO):
TEXCOORDx
COLOR
TANGENT
NORMAL
VERTEX
VERTEX INDEX
not in VBO:
PRIMITIVE
*/

namespace
{


const GLenum convertDeformableHint2GLUsage( vgd::node::VertexShape * node )
{
	const vgd::node::VertexShape::DeformableHintValueType deformableHint = node->getDeformableHint();

	if ( deformableHint == vgd::node::VertexShape::STATIC )
	{
		return GL_STATIC_DRAW;
	}
	else if ( vgd::node::VertexShape::STREAM )
	{
		return GL_STREAM_DRAW;
	}
	else if ( vgd::node::VertexShape::DYNAMIC )
	{
		return GL_DYNAMIC_DRAW;
	}
	else
	{
		vgAssertN( false, "Internal error." );
		return GL_DYNAMIC_DRAW;
	}
}



void bindVAO( glo::VertexArrayObject& rc )
{
	const bool isEmpty = rc.isEmpty();

	if ( isEmpty )	rc.generate();

	rc.bind();
}



// Update data
template< typename GLOArrayBufferType >
void updateArrayBuffer( GLOArrayBufferType& buffer, GLsizeiptr size, const GLvoid * ptr, const GLenum bufferUsage )
{
	const bool isBufferEmpty = buffer.isEmpty();
	const bool useBufferData =	isBufferEmpty						||	// current buffer is empty
								size > buffer.getSize()				||	// data store must be expanded
								bufferUsage != buffer.getUsage();		// buffer usage has been modified

	if ( isBufferEmpty ) buffer.generate();

	buffer.bind();
	if ( useBufferData )
	{
		if (ptr)	buffer.bufferData( size, ptr, bufferUsage );
	}
	else
	{
		if (ptr)	buffer.bufferSubData( 0, size, ptr );
	}
}



//	update texCoord
namespace
{
	template< typename ValueType >
	void updateTexCoordArrayBuffer( vgd::node::VertexShape * vertexShape, const uint unit, vgeGL::rc::VertexShape * rc, const GLenum bufferUsage )
	{
		typedef vgd::field::TMultiField< ValueType > ValueContainerType;

		vgd::field::EditorRO< ValueContainerType > texCoord = vertexShape->getTexCoordRO< ValueContainerType >( unit );
		updateArrayBuffer( rc->texCoord[unit], texCoord->size()*sizeof(ValueType), texCoord->ptr(), bufferUsage );
	}
}



void updateTexCoord( vgd::node::VertexShape * vertexShape, const uint unit, const uint texCoordDim, vgeGL::rc::VertexShape * rc )
{
	if (	texCoordDim > 0 /*&&
			vertexShape->getTexCoordBinding( unit ) == vgd::node::BIND_PER_VERTEX*/ )
	{
		// Resize texCoord ArrayBuffer vector if needed
		if ( unit >= rc->texCoord.size() )
		{
			rc->texCoord.resize( unit + 1 );
		}

		if ( texCoordDim == 2 )
		{
			updateTexCoordArrayBuffer< vgm::Vec2f >( vertexShape, unit, rc, GL_STATIC_DRAW );
		}
		else if ( texCoordDim == 1 )
		{
			updateTexCoordArrayBuffer< float >( vertexShape, unit, rc, GL_STATIC_DRAW );
		}
		else if ( texCoordDim == 3 )
		{
			updateTexCoordArrayBuffer< vgm::Vec3f >( vertexShape, unit, rc, GL_STATIC_DRAW );
		}
		else if ( texCoordDim == 4 )
		{
			updateTexCoordArrayBuffer< vgm::Vec4f >( vertexShape, unit, rc, GL_STATIC_DRAW );
		}
		else
		{
			// NOT SUPPORTED
			vgAssertN( false, "VertexShape(%s).texCoord%u with dimension equal to %u", vertexShape->getName().c_str(), unit, texCoordDim );
		}
	}
	// else nothing to do
}


// Configure arrays
void configureTexCoord( vgeGL::engine::Engine * engine, vgd::node::VertexShape * vertexShape, const uint unit, const uint texCoordDim, vgeGL::rc::VertexShape * rc )
{
	if (	texCoordDim > 0 &&
			vertexShape->getTexCoordBinding( unit ) == vgd::node::BIND_PER_VERTEX )
	{
		// Compute informations
		const GLvoid *pArray = 0;

		if ( !engine->isGLSLEnabled() ) glClientActiveTexture( GL_TEXTURE0_ARB + unit );
		rc->texCoord[unit].bind();

		// Configure vertex attrib array
		if ( engine->isGLSLEnabled() )
		{
			glEnableVertexAttribArray( vgeGL::engine::TEXCOORD_INDEX + unit );
			glVertexAttribPointer( vgeGL::engine::TEXCOORD_INDEX + unit, texCoordDim, GL_FLOAT, GL_FALSE, 0, pArray );
		}
		else
		{
			glTexCoordPointer( texCoordDim, GL_FLOAT, 0, pArray );
			glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		}
	}
	else // texCoordDim > 0 && vertexShape->getTexCoordBinding( unit ) == vgd::node::BIND_PER_VERTEX )
	{
		if ( engine->isGLSLEnabled() )
		{
			glDisableVertexAttribArray( vgeGL::engine::TEXCOORD_INDEX + unit );
		}
		else
		{
			glClientActiveTexture( GL_TEXTURE0_ARB + unit );
			glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		}
	}
}


}



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( VertexShape );



const vge::handler::Handler::TargetVector VertexShape::getTargets() const
{
	vge::handler::Handler::TargetVector targets;

	targets.reserve( 6 );

	targets.push_back( vgd::node::Box::getClassIndexStatic() );
	targets.push_back( vgd::node::Grid::getClassIndexStatic() );
	targets.push_back( vgd::node::Quad::getClassIndexStatic() );
	targets.push_back( vgd::node::Sphere::getClassIndexStatic() );
	targets.push_back( vgd::node::TriSet::getClassIndexStatic() );
	targets.push_back( vgd::node::VertexShape::getClassIndexStatic() );

	return targets;
}


/**
 * @todo glPolygonMode( GL_FRONT_AND_BACK, *): is it always correct ? use GL_FRONT, GL_BACK ?
 *
 * @todo GL_ARB_shader_subroutine to reduce number of generated shaders and simplify GLSLState
 * @todo GL_ARB_separate_shader_objects
 * @todo [GL_ARB_get_program_binary]
 */
void VertexShape::apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	vgAssert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *engine = static_cast< vgeGL::engine::Engine* >(pEngine);

	vgAssert( dynamic_cast< vgd::node::VertexShape* >(pNode) != 0 );
	vgd::node::VertexShape *pVertexShape = static_cast< vgd::node::VertexShape* >(pNode);

	// GLSL STATE UPDATE
	using vgeGL::engine::GLSLState;
	GLSLState& glslState = engine->getGLSLState();

	// TESSELLATION (enabled if only TRIANGLES primitives)
	const bool tessellationSaved = glslState.isTessellationEnabled();

	//	Disable tessellation if at least one primitive is not a TRIANGLES
	vgd::field::EditorRO< vgd::field::MFPrimitive >	primitives( pVertexShape->getPrimitiveRO() );

	//		no primitives ? so, no rendering.
	if (primitives->size()==0)	return;

	for(	vgd::field::MFPrimitive::const_iterator	i	= primitives->begin(),
													ie	= primitives->end();
			i != ie;
			++i)
	{
		const vgd::node::Primitive& primitive(*i);

		if (primitive.getType() != vgd::node::Primitive::TRIANGLES)
		{
			glslState.setTessellationEnabled(false);
			break;
		}
	}

	// BUMPMAPPING (enabled if tangentBinding=PER_VERTEX and textures >= 2)
	const bool bumpSaved = glslState.isBumpMappingEnabled();

	//	Test if bumpmapping have to be disabled
	if (	(pVertexShape->getTangentBinding() == vgd::node::BIND_OFF) ||	// no tangents
			(glslState.textures.getNum() < 2) )								// not enough textures
	{
		glslState.setBumpMappingEnabled(false);
	}


	// Updates GLSL state with vertex shape info
	glslState.setEnabled( vgeGL::engine::COLOR_BIND_PER_VERTEX, pVertexShape->getColorBinding() == vgd::node::BIND_PER_VERTEX );

	// setTexCoordDim for texUnitState of glslState => MUST BE DONE for pg->generate() using generateFunction_ftexgen(), generate_samplers() and generate_texLookups()
	// engine->getGLSLStateStack().push();

	// @todo OPTME: VertexShape::getTexUnitsIterators() or iterator for glslState.textures
	if ( engine->isTextureMappingEnabled() )
	{
		vgd::node::VertexShape::ConstIteratorIndexSet i, iEnd;
		for(	boost::tie( i, iEnd ) = pVertexShape->getTexUnitsIterators();
				i != iEnd;
				++i )
		{
			const uint unit = *i;

			vgd::Shp< GLSLState::TexUnitState > texUnitState = glslState.textures.getState( unit );

			if ( pVertexShape->getTexCoordBinding( unit ) != vgd::node::BIND_OFF )
			{
				const int32 dimTexCoord = pVertexShape->getTexCoordDim( unit ); // @todo OPT pVertexShape->getTexCoordDim()
				if ( texUnitState->getTexCoordDim() != dimTexCoord )
				{
					// @toto glslState.setTexCoordDim( 0 Unit, 2  Dim ); that invalidate DF
					texUnitState->setTexCoordDim( static_cast< uint8 >(dimTexCoord) );
					glslState.textures.dirty();
				}
				//else nothing to do
			}
/*			else
			{
				texUnitState->setTexCoordDim( 0 );
#ifdef _DEBUG
				vgLogDebug(	"VertexShape(%s).texCoord%i is not empty, but there is no texture",
								pVertexShape->getName().c_str(), unit );
#endif
			}*/
		}
	}

	// // Update glslState.textures[].texCoordDim from vertexShape->texCoordDim
// // @todo iterate on vertexShape.texCoord? instead of glslState.textures
/*	if ( engine->isTextureMappingEnabled() )
	{
		//
		uint		i		= 0;
		const uint	iEnd	= glslState.textures.getMax();

		for( uint foundTexture = 0; i != iEnd; ++i )
		{
			const vgd::Shp< GLSLState::TexUnitState >  texUnitState = glslState.textures.getState( i );

			if (	texUnitState &&
					texUnitState->getTexGenNode() == 0
				)
			{
				const int32 dimTexCoord = pVertexShape->getTexCoordDim( i );			// @todo OPT pVertexShape->getTexCoordDim()
				if ( texUnitState->getTexCoordDim() != dimTexCoord )
				{
					// @toto glslState.setTexCoordDim( 0 Unit, 2  Dim  ); that invalidate DF
					texUnitState->setTexCoordDim( static_cast< uint8 >(dimTexCoord) );								// no more used !!! @todo OPTME remove me
					glslState.textures.dirty(); // @todo never validate and used to skip that work
				}
			}
			// else no state for the texture unit or texCoordDim from texGen node, so nothing to do
#ifdef _DEBUG
			//else
			//{
				//if ( !texUnitState && pVertexShape->getTexCoordDim( i ) > 0 )
				//{
				//	vgAssertN(	false, "VertexShape(%s).texCoord%i is not empty, but there is no texture",
				//						pVertexShape->getName().c_str(), i );
				//}
			//}
#endif
		}
	}*/


	// GLSL
	const bool tessellationIsEnabled = glslState.isTessellationEnabled();
	bool aNewProgramHasBeenGenerated = false;
	if ( engine->isGLSLEnabled() )
	{
		if ( glslState.isDirty() )
		{
			// GENERATION
			vgd::Shp< vgeGL::engine::ProgramGenerator > pg = engine->getGLSLProgramGenerator();
			pg->generate( engine );

			// CACHE
			const std::string	fullCode	= pg->getCode();

			const std::string&	vs			= pg->getVertexShaderGenerator()->getCode();
			std::string			tcs;
			std::string 		tes;
			std::string			gs;
			const std::string&	fs			= pg->getFragmentShaderGenerator()->getCode();

			using glo::GLSLProgram;
			GLSLProgram * program = engine->getGLSLManager()->get< GLSLProgram >( fullCode );
			if ( program == 0 )
			{
				// Not found in cache, so creates a new one
				vgd::Shp< GLSLProgram > shpProgram( new glo::GLSLProgram );
				program = shpProgram.get();

				// Compiles and links
				const bool compileVSRetVal = program->addShader( vs, pg->getVertexShaderGenerator()->getShaderType() );

				bool compileTCSRetVal = true;
				bool compileTESRetVal = true;

				if ( tessellationIsEnabled )
				{
					tcs = pg->getTessellationControlShaderGenerator()->getCode();
					tes = pg->getTessellationEvaluationShaderGenerator()->getCode();

					compileTCSRetVal = program->addShader( tcs, pg->getTessellationControlShaderGenerator()->getShaderType() );
					compileTESRetVal = program->addShader( tes, pg->getTessellationEvaluationShaderGenerator()->getShaderType() );
				}

				const bool compileGSRetVal = true;//program->addShader( gs, pg->getGeometryShaderGenerator()->getShaderType() );

				const bool compileFSRetVal = program->addShader( fs, pg->getFragmentShaderGenerator()->getShaderType() );

				const bool linkRetVal = program->link(false);

				// Register the new program
				aNewProgramHasBeenGenerated = true;
				const int programValue = static_cast<int>( program->getProgramObject() );
				engine->getGLSLManagerExt()->add( programValue , shpProgram );
				engine->getGLSLManager()->add( fullCode, shpProgram );

				if ( !compileVSRetVal || !compileTCSRetVal || !compileTESRetVal || !compileGSRetVal || !compileFSRetVal || !linkRetVal /*|| !validateRetVal*/ )
				{
					// Don't render this vertex shape
					engine->setCurrentProgram();
					vgLogDebug("Program %i generated for VertexShape named '%s' contains error(s).", programValue, pVertexShape->getName().c_str());
					return;
				}
				else
				{
					engine->setCurrentProgram();
				}
			}
			// else uses GLSL program found in cache

			// GLSL Program and samplers
			if ( engine->gethCurrentProgram() != program )
			{
				//	PROGRAM
				engine->sethCurrentProgram( program );

				//	SAMPLERS
				setSamplers( engine, program );

				//	VALIDATION
				if ( aNewProgramHasBeenGenerated )
				{
					const bool validateRetVal = program->validate();
				}
				// else nothing to do
			}
			// else nothing to do

			// Sets uniform(s)
			// 	UNIFORM
			engine->getBuiltinUniformState().apply( engine );
			engine->getUniformState().apply( engine );

			glslState.validate();
		}
		else // if ( glslState->isDirty() )
		{
			// glslState is valid, so nothing to do

			// Sets uniform(s)
			// 	UNIFORM

#ifdef _VGSDK_DEBUG
			// Checks if glslState->isValid() is the correct value

			// GENERATION
			vgd::Shp< vgeGL::engine::ProgramGenerator > pg = engine->getGLSLProgramGenerator();
			pg->generate( engine );

			// CACHE
			const std::string fullCode = pg->getCode();

			using glo::GLSLProgram;
			GLSLProgram * program = engine->getGLSLManager().get< GLSLProgram >( fullCode );
			if ( program != engine->getCurrentProgram() )
			{
				vgAssertN( program == engine->getCurrentProgram(), "glslState->isValid() should be dirty." );
			}
			//else nothing to do
#endif
		}
	}
	else // if ( engine->isGLSLEnabled() )
	{
		vgeGL::rc::GLSLProgram::useFixedPaths();
	}

	// Renders the VertexShape
	::vgeGL::handler::painter::DrawStyle::paintVertexShapeWithShapeProperty( engine, pVertexShape, this );

	// Renders additional properties of VertexShape
	using vgd::node::DrawStyle;

	DrawStyle::NormalLengthValueType	normalLength			= engine->getGLState().getNormalLength();
	DrawStyle::TangentLengthValueType	tangentLength			= engine->getGLState().getTangentLength();
	const bool							showOrientationValue	= engine->getGLState().getShowOrientation();
	DrawStyle::BoundingBoxValueType		bbValue					= engine->getGLState().getBoundingBox();

	const bool additionalProperties =	(normalLength > 0.f) || (tangentLength > 0.f) ||showOrientationValue ||
										(bbValue != vgd::node::DrawStyle::NO_BOUNDING_BOX);

	if ( additionalProperties )
	{
		// Gets resource associated to the given node
		vgeGL::rc::VertexShape * vertexShapeRC = engine->getGLManager()->get< vgeGL::rc::VertexShape >( pVertexShape );

		// Makes a backup of GLSL activation state
		using vgeGL::engine::Engine;

		vgd::Shp< Engine::GLSLActivationState > glslActivationState = engine->getGLSLActivationState();
		engine->sethCurrentProgram();

		glPushAttrib( GL_ALL_ATTRIB_BITS );

		glDisable( GL_LIGHTING );
		glDisable( GL_TEXTURE_1D );
		glDisable( GL_TEXTURE_2D );

		glLineWidth( 2.f );

		// *** DRAWSTYLE.normalLength ***
		if (	normalLength != 0.f &&
				pVertexShape->getNormalBinding() == vgd::node::BIND_PER_VERTEX	)
		{
			glColor3f( 1.f, 1.f, 1.f );

			vgd::field::EditorRO< vgd::field::MFVec3f > normals = pVertexShape->getNormalRO();
			drawVectorsFromVertices( pVertexShape, normals, normalLength, vertexShapeRC->drawNormalsVectors, vertexShapeRC->drawNormalsBuffer );
		}

		// *** DRAWSTYLE.tangentLength ***
		if (	tangentLength != 0.f &&
				pVertexShape->getTangentBinding() == vgd::node::BIND_PER_VERTEX	)
		{
			glColor3f( 1.f, 1.f, 0.f );

			vgd::field::EditorRO< vgd::field::MFVec3f > tangents = pVertexShape->getTangentRO();
			drawVectorsFromVertices( pVertexShape, tangents, tangentLength, vertexShapeRC->drawTangentsVectors, vertexShapeRC->drawTangentsBuffer );
		}

		// *** DRAWSTYLE.showOrientation ***
		if ( showOrientationValue )
		{
			//float vColor[4];
			//glGetFloatv( GL_COLOR_CLEAR_VALUE, vColor );
			//glColor4fv( vColor );
			//glEnable( GL_POLYGON_OFFSET_FILL );
			//glPolygonOffset( 1.0f, 1.0f );
			//glDepthFunc( GL_EQUAL );

			//glDisable( GL_DEPTH_TEST );

			drawTriangleOrientation( pVertexShape, vertexShapeRC );
		}

		// *** DRAWSTYLE.boundingBox ***
		if ( bbValue != vgd::node::DrawStyle::NO_BOUNDING_BOX )
		{
			switch ( bbValue.value() )
			{
				case vgd::node::DrawStyle::NO_BOUNDING_BOX:
					break;

				case vgd::node::DrawStyle::OBJECT_SPACE:
					glColor3f( 0.f, 0.f, 1.f );
					drawBoundingBox( engine, pVertexShape );
					break;

				case vgd::node::DrawStyle::AA_OBJECT_SPACE:
					glColor3f( 1.f, 0.f, 0.f );
					drawXfBoundingBox( engine, pVertexShape );
					break;

				case vgd::node::DrawStyle::OBJECT_AND_AA_OBJECT_SPACE:
					glColor3f( 0.f, 0.f, 1.f );
					drawBoundingBox( engine, pVertexShape );
					glColor3f( 1.f, 0.f, 0.f );
					drawXfBoundingBox( engine, pVertexShape );
					break;

				default:
					vgAssertN( false, "Unknown DrawStyle.boundingBox value." );
			}
		}

		// Restore state
		glPopAttrib();

		// Restores GLSL activation state
		engine->setGLSLActivationState( glslActivationState );
	}

	// Restores glslState
	if ( engine->isTextureMappingEnabled() )
	{
		vgd::node::VertexShape::ConstIteratorIndexSet i, iEnd;
		for(	boost::tie( i, iEnd ) = pVertexShape->getTexUnitsIterators();
				i != iEnd;
				++i )
		{
			const uint unit = *i;

			vgd::Shp< GLSLState::TexUnitState > texUnitState = glslState.textures.getState( unit );

			if ( pVertexShape->getTexCoordBinding( unit ) != vgd::node::BIND_OFF )
			{
				texUnitState->setTexCoordDim( 0 );
				glslState.textures.dirty();
			}
		}
	}
//	glPopAttrib();

	// TESSELLATION
	engine->getGLSLState().setTessellationEnabled(tessellationSaved);

	// BUMP
	engine->getGLSLState().setBumpMappingEnabled(bumpSaved);

	// Validates node
	pNode->getDirtyFlag(pNode->getDFNode())->validate();
}



void VertexShape::unapply ( vge::engine::Engine* , vgd::node::Node* )
{
}



void VertexShape::setToDefaults()
{
}



void VertexShape::setSamplers( vgeGL::engine::Engine * engine, glo::GLSLProgram * program )
{
	// TEX COORD and uniform sampler (from VertexShape.texCoord*/TexGen and Texture)
	// Texture |	VertexShape.texCoord |	TexGen	=> action (sampler(S), vertex array(VA), warning (W) )
	// normal cases
	// y		y				n		=> S, VA
	// y		n				y		=> S
	// n		n				n		=> none
	// others cases (errors or warnings)
	// y		y				y		=> S, VA (use texCoord), W
	// y		n				n		=> none, W
	// n		 ?				?		=> none, W(print warning if needed).
// @todo not texture, but VertexShape.texCoord | TexGen

	using vgeGL::engine::GLSLState;
	GLSLState& glslState = engine->getGLSLState();

	uint		i		= 0;
	const uint	iEnd	= engine->isTextureMappingEnabled() ? glslState.textures.getMax() : 0;

	for( uint foundTexture = 0; i != iEnd; ++i )
	{
		const vgd::Shp< GLSLState::TexUnitState > current = glslState.textures.getState( i );

		// Empty texture unit, so do nothing
		if ( current == 0 )	continue;

		const uint&					unit	= i;
		const std::string			strUnit = vgd::basic::toString( unit );

		const vgd::node::Texture *	textureNode	= current->getTextureNode();
		glo::Texture *				texture		= current->getTexture();
		//const uint8				texCoordDim	= current->getTexCoordDim();
		//const vgd::node::TexGen *	texGen		= current->getTexGenNode();

		//
		// @todo hasImage() ? see handler Texture::preSynchronize() : idea boolean value in glo::Texture for "completeness" ?
		// @todo case textureNode and texture, but textureNode with IImage containing no data (texInfo.iimage->pixels() == 0)
		const bool isTextureComplete = textureNode && textureNode->hasImage() && texture; // @todo not accurate

		//
		//const bool hasTexCoord = texCoordDim > 0; // pVertexShape->getTexCoordDim(unit) || texGen;

		//
		const bool isUnitComplete = isTextureComplete /*&& hasTexCoord*/;

		// SAMPLER
		if ( isUnitComplete )
		{
			if ( program )
			{
#ifdef _DEBUG
				if ( !engine->isDSAEnabled() )
				{
					vgAssert( program->isInUse() );
				}
#endif

				const vgd::node::Texture::UsageValueType usage = textureNode->getUsage();

				if ( usage == vgd::node::Texture::SHADOW )
				{
					program->setUniform1i( "texMap2DShadow[" + glslState.getPrivate( unit ) + "]", unit );
				}
				else if ( usage == vgd::node::Texture::IMAGE )
				{
					program->setUniform1i( "texMap2D[" + strUnit + "]", unit );
				}
				else
				{
					vgAssertN( false, "Unexpected usage for Texture named, '%s'.", textureNode->getName().c_str() );
				}
			}
			// else nothing to do
		}

		//
		++foundTexture;
		if ( foundTexture == glslState.textures.getNum() )
		{
			break;
		}
	}
}


void VertexShape::paint( vgeGL::engine::Engine * engine, vgd::node::VertexShape * vertexShape )
{
	vgd::node::VertexShape * node = vertexShape;

	// using VertexArray stored in buffer objects
	typedef vgeGL::rc::VertexShape GLResourceType;


	// RC
	// Gets the resource manager
	vgd::Shp< vgeGL::engine::Engine::GLManagerType > manager = engine->getGLManager();

	// Gets node dirty flag
	vgd::field::DirtyFlag * nodeDF = node->getDirtyFlag( node->getDFNode() );

	// Gets resource associated to the given node
	::glo::IResource 	* resource			= manager->getAbstract( node );
	GLResourceType		* castedResource	= dynamic_cast< GLResourceType * >(resource);

	// STEP 1
	// Sometimes GLResourceType must be changed for a given node (display list to/from vbo for example).
	// is it the case now ?
	if (	(resource != 0) && (castedResource == 0)	)
	{
		// There is a resource, but not with the expected type.
		// Dynamic change of handler ? or node that must be process differently (static, dynamic for VertexShape) ?

		// Removes the resource from the manager
		manager->remove( node );
		resource = 0;
		vgAssertN( (resource == 0) && (castedResource==0), "Internal error." );
	}
	// else if resource != 0 && castedResource != 0 => see step 2
	// else if resource == 0 && castedResource == 0 => see step 2
	// else if resource == 0 && castedResource != 0 => impossible

	// STEP 2
	vgAssertN(	(resource!=0 && castedResource!=0) ||
				(resource==0 && castedResource==0)
				, "Internal error." );

	// Creates resource if needed
	if ( resource == 0 )
	{
		vgAssertN( castedResource == 0, "Internal error." );

		// Creates the resource
		castedResource = new GLResourceType();
		resource = castedResource;

		// Adds the resource to the manager
		manager->add( node, castedResource );
	}
	// else reuses the resource => nothing to do

	vgAssertN( resource!=0 && castedResource!=0, "Internal error." );

	// STEP 3
	// What else ? synchronization and/or binding part of the work
	if ( nodeDF->isDirty() )
	{
		// Node has been invalidated

//		// Binds the resource
//		handler->bind( engine, node, castedResource );

		// Updates resource
		/*handler->*/update( engine, node, castedResource );
		/*handler->*/configureRenderingArrays( engine, node, castedResource );
		/*handler->*/renderArrays(	engine, node, castedResource );

		// Checks if synchronize() method have validated the node dirty flag
		// assert( nodeDF->isValid() );	not always validated by synchronize, so don't check
	}
	else
	{
		// No modifications in the node

		// Binds the resource
		//handler->bind( engine, node, castedResource );

		if ( !engine->isGLSLEnabled() ) /*handler->*/configureRenderingArrays( engine, node, castedResource );

		// begin:	GeoMorp specific
		if ( geoMorph2 )
		{
			//	Gets resource associated to the geoMorph2 node
			GLResourceType		* geoMorph2RC	= manager->get< GLResourceType >( geoMorph2 );
			vgAssert( geoMorph2RC != 0 );

			//	configureRenderingArrays
			bindVAO(castedResource->vao);//.bind();
			/*handler->*/configureRenderingArraysForGeoMorph( engine, geoMorph2, geoMorph2RC );
			/*handler->*/renderArrays( engine, node, castedResource );
			castedResource->vao.bind();
			/*handler->*/unconfigureRenderingArraysForGeoMorph( engine, geoMorph2, geoMorph2RC );
			castedResource->vao.unbind();
		}
		// end:		GeoMorp specific
		else
		{
			/*handler->*/renderArrays(	engine, node, castedResource );
		}
	}
}



// @todo take care of deformable hint modification
void VertexShape::update(	vgeGL::engine::Engine * engine, vgd::node::VertexShape * vertexShape,
							vgeGL::rc::VertexShape * rc )
{
	// VAO
	bindVAO( rc->vao ); // move this call ?

	// Updates all VBO
	const GLenum bufferUsage = convertDeformableHint2GLUsage( vertexShape );

	// TEXCOORD
	// always update texCoord array(s) even if engine->isTextureMappingEnabled() == false
	vgd::node::VertexShape::ConstIteratorIndexSet i, iEnd;
	for(	boost::tie( i, iEnd ) = vertexShape->getTexUnitsIterators();
			i != iEnd;
			++i )
	{
		const uint unit = *i;
		const uint8 texCoordDim = vertexShape->getTexCoordDim(unit);
		updateTexCoord( vertexShape, unit,  texCoordDim, rc );
	}

	// COLOR
	if ( vertexShape->getColorBinding() == vgd::node::BIND_PER_VERTEX )
	{
		vgd::field::EditorRO< vgd::field::MFVec4f > color = vertexShape->getColorRO();
		updateArrayBuffer( rc->color, color->size()*sizeof(vgm::Vec4f), color->ptr(), bufferUsage );
	}

	// TANGENT
	if ( vertexShape->getTangentBinding() == vgd::node::BIND_PER_VERTEX )
	{
		vgd::field::EditorRO< vgd::field::MFVec3f > tangent = vertexShape->getTangentRO();
		updateArrayBuffer( rc->tangent, tangent->size()*sizeof(vgm::Vec3f), tangent->ptr(), bufferUsage );
	}

	// NORMAL
	if ( vertexShape->getNormalBinding() == vgd::node::BIND_PER_VERTEX )
	{
		vgd::field::EditorRO< vgd::field::MFVec3f > normal = vertexShape->getNormalRO();
		updateArrayBuffer( rc->normal, normal->size()*sizeof(vgm::Vec3f), normal->ptr(), bufferUsage );
	}

	// VERTEX
	vgd::field::EditorRO< vgd::field::MFVec3f > vertex = vertexShape->getVertexRO();
	updateArrayBuffer( rc->vertex, vertex->size()*sizeof(vgm::Vec3f), vertex->ptr(), bufferUsage );

	// VERTEX INDEX
	vgd::field::EditorRO< vgd::field::MFUInt > vertexIndex = vertexShape->getVertexIndexRO();
	updateArrayBuffer( rc->vertexIndex, vertexIndex->size()*sizeof(uint32), vertexIndex->ptr(), GL_STATIC_DRAW /*bufferUsage adds hints in VertexShape node*/ );

	// @todo primitives data ?
	// @todo multiple instances data
}


void VertexShape::configureRenderingArrays( vgeGL::engine::Engine * engine, vgd::node::VertexShape * vertexShape, vgeGL::rc::VertexShape * rc )
{
	glo::GLSLProgram *	program	= engine->gethCurrentProgram();
	const GLvoid *		pArray	= 0;

	// *** Step 1 : Setup arrays. ***

	// TEXCOORD
	if ( true /*engine->isTextureMappingEnabled()*/ )
	{
		vgd::node::VertexShape::ConstIteratorIndexSet i, iEnd;
		for(	boost::tie( i, iEnd ) = vertexShape->getTexUnitsIterators();
				i != iEnd;
				++i )
		{
			const uint unit = *i;

			if ( !program )
			{
				engine->activeTexture( unit );
				glEnable( GL_TEXTURE_2D );
			}
			// else nothing to do

			configureTexCoord( engine, vertexShape, unit, vertexShape->getTexCoordDim(unit) /* @todo OPTME */, rc );
		} // end for
	}
	// else nothing to do


	// COLOR
	if ( vertexShape->getColorBinding() == vgd::node::BIND_PER_VERTEX )
	{
		rc->color.bind();

		glEnableVertexAttribArray( vgeGL::engine::COLOR_INDEX );
		glVertexAttribPointer( vgeGL::engine::COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, 0, pArray );
	}
	else
	{
		glDisableVertexAttribArray( vgeGL::engine::COLOR_INDEX );
	}

	// TANGENT
	if ( vertexShape->getTangentBinding() == vgd::node::BIND_PER_VERTEX )
	{
		rc->tangent.bind();

		glEnableVertexAttribArray( vgeGL::engine::TANGENT_INDEX );
		glVertexAttribPointer( vgeGL::engine::TANGENT_INDEX, 3, GL_FLOAT, GL_FALSE, 0, pArray );
	}
	else
	{
		glDisableVertexAttribArray( vgeGL::engine::TANGENT_INDEX );
	}

	// NORMAL
	if ( vertexShape->getNormalBinding() == vgd::node::BIND_PER_VERTEX )
	{
		rc->normal.bind();

		glEnableVertexAttribArray( vgeGL::engine::NORMAL_INDEX );
		glVertexAttribPointer( vgeGL::engine::NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, 0, pArray );
	}
	else
	{
		glDisableVertexAttribArray( vgeGL::engine::NORMAL_INDEX );
	}

	// VERTEX
	rc->vertex.bind();

	glEnableVertexAttribArray( vgeGL::engine::VERTEX_INDEX );
	glVertexAttribPointer( vgeGL::engine::VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, 0, pArray );

	// VERTEX INDEX
	vgd::field::EditorRO< vgd::field::MFUInt > vertexIndex;
	rc->vertexIndex.bind();
}


void VertexShape::configureRenderingArraysForGeoMorph( vgeGL::engine::Engine * engine, vgd::node::VertexShape * vertexShape, vgeGL::rc::VertexShape * rc )
{
	const GLvoid * pArray = 0;

	// TANGENT1
	if ( vertexShape->getTangentBinding() == vgd::node::BIND_PER_VERTEX )
	{
		rc->tangent.bind();

		glEnableVertexAttribArray( vgeGL::engine::TANGENT1_INDEX );
		glVertexAttribPointer( vgeGL::engine::TANGENT1_INDEX, 3, GL_FLOAT, GL_FALSE, 0, pArray );
	}

	// NORMAL1
	if ( vertexShape->getNormalBinding() == vgd::node::BIND_PER_VERTEX )
	{
		rc->normal.bind();

		glEnableVertexAttribArray( vgeGL::engine::NORMAL1_INDEX );
		glVertexAttribPointer( vgeGL::engine::NORMAL1_INDEX, 3, GL_FLOAT, GL_FALSE, 0, pArray );
	}

	// VERTEX1
	rc->vertex.bind();

	glEnableVertexAttribArray( vgeGL::engine::VERTEX1_INDEX );
	glVertexAttribPointer( vgeGL::engine::VERTEX1_INDEX, 3, GL_FLOAT, GL_FALSE, 0, pArray );
}



void VertexShape::unconfigureRenderingArraysForGeoMorph( vgeGL::engine::Engine * engine, vgd::node::VertexShape * vertexShape, vgeGL::rc::VertexShape * rc )
{
	glDisableVertexAttribArray( vgeGL::engine::TANGENT1_INDEX );
	glDisableVertexAttribArray( vgeGL::engine::VERTEX1_INDEX );
	glDisableVertexAttribArray( vgeGL::engine::NORMAL1_INDEX );
}



// @todo improves support of primitives
// @todo improve support of instancing
void VertexShape::renderArrays( vgeGL::engine::Engine * engine, vgd::node::VertexShape * vertexShape, vgeGL::rc::VertexShape * rc )
{
	// *** Step 1: Precondition: GLSL program in a good state to be able to render something ***
	if ( engine->isGLSLEnabled() )
	{
		if (engine->getCurrentProgram())
		{
			if ( !engine->getCurrentProgram()->getLinkSuccess() )	return;
		}
		else
		{
			return;
		}
	}
	// else nothing to do

	// GeoMorph
	vgd::node::GeoMorph * geoMorph = engine->getGeoMorph();
	if ( geoMorph && engine->isGLSLEnabled() )
	{
		// GeoMorph is enabled

		// Updates geoMorpg.__meshes__ field
		using vgd::field::MFVertexShapePtr;
		vgd::field::EditorRW< MFVertexShapePtr > meshes = geoMorph->get__meshes__RW();
		meshes->push_back( vertexShape );
	}

	// *** Step 2 : RENDERING ***
	if ( !engine->isDrawCallsEnabled() )	return;

	rc->vao.bind();

	// For each primitive
	using vgd::field::EditorRO;
	using vgd::field::MFPrimitive;
	EditorRO< MFPrimitive > primitives( vertexShape->getPrimitiveRO() );

	for(	MFPrimitive::const_iterator	i	= primitives->begin(),
										ie	= primitives->end();
			i != ie;
			++i	)
	{
		const vgd::node::Primitive&	primitive		= *i;
		const GLenum				primitiveType	= m_primTypeArray[ primitive.getType() ];

		if ( primitive.getType() == vgd::node::Primitive::NONE )	continue;

		const GLvoid *pArray = (uint32*)0 + primitive.getIndex();

		const vgd::node::MultipleInstances * multipleInstances = engine->getGLState().getMultipleInstances();
		if ( multipleInstances )
		{
			// MATRIX
			typedef vgd::node::MultipleInstances::FMatrixType FMatrixType;

			EditorRO< FMatrixType > matrix = multipleInstances->getMatrixRO();

			// Gets the geometrical matrix transformation.
			const vgm::MatrixR backup( engine->getGeometricalMatrix().getTop() );

			//
			glMatrixMode( GL_MODELVIEW );

			for(	FMatrixType::const_iterator	i		= matrix->begin(),
												iEnd	= matrix->end();
					i != iEnd;
					++i	)
			{
				// Updates geometrical transformation
				const vgm::MatrixR& iMatrix = *i;
				const vgm::MatrixR current = iMatrix * backup;

				glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );

				if ( engine->gethCurrentProgram() && engine->getGLSLState().isTessellationEnabled() )
				{
					// RENDER
					glDrawElements( GL_PATCHES, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
				}
				else
				{
					glDrawElements( primitiveType, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
				}
			}

			//
			glLoadMatrixf( reinterpret_cast<const float*>( backup.getValue() ) );

			//
			engine->getGLState().setMultipleInstances( 0 );
		}
		else
		{
			if ( engine->gethCurrentProgram() && engine->getGLSLState().isTessellationEnabled() )
			{
				glDrawElements( GL_PATCHES, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
			}
			else
			{
				glDrawElements( primitiveType, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
				//glDrawRangeElements( primitiveType, 0, vertex->size()-1, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
			}
			// RENDER
			//glDrawRangeElements( primitiveType, 0, vertex->size()-1, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
			//glDrawElements( primitiveType, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
			// or glDrawElements( primitiveType, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
		}
	} // for each primitive

	rc->vao.unbind();
}


void VertexShape::drawBoundingBox( vgeGL::engine::Engine *, vgd::node::VertexShape *vertexShape )
{
	drawBox3f( vertexShape->getBoundingBox() );
}



void VertexShape::drawXfBoundingBox( vgeGL::engine::Engine *, vgd::node::VertexShape *vertexShape )
{
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	drawBox3f( vertexShape->getProjectXfBoundingBox() );

	glPopMatrix();
}


// move to handler/operations.hpp.cpp
// @todo remove glBegin/glEnd
void VertexShape::drawBox3f( const vgm::Box3f& box )
{
	float	width, height, depth;
	box.getSize( width, height, depth );

	vgm::Vec3f	frontUL, frontUR, frontDL, frontDR;
	vgm::Vec3f	backUL, backUR, backDL, backDR;

	frontDL = box.getMin();
	frontDR = frontDL + vgm::Vec3f( width, 0.f, 0.f );

	frontUL = frontDL + vgm::Vec3f( 0.f, height, 0.f );
	frontUR = frontDR + vgm::Vec3f( 0.f, height, 0.f );

	backUR	= box.getMax();
	backUL	= backUR + vgm::Vec3f( -width, 0.f, 0.f );
	
	backDR	= backUR + vgm::Vec3f( 0.f, -height, 0.f );
	backDL	= backUL + vgm::Vec3f( 0.f, -height, 0.f );

	// front
	glBegin( GL_LINE_STRIP );
	
	glVertex3fv( frontDL.getValue() );
	glVertex3fv( frontDR.getValue() );
	glVertex3fv( frontUR.getValue() );
	glVertex3fv( frontUL.getValue() );
	glVertex3fv( frontDL.getValue() );

	glEnd();

	// back
	glBegin( GL_LINE_STRIP );

	glVertex3fv( backDL.getValue() );
	glVertex3fv( backDR.getValue() );
	glVertex3fv( backUR.getValue() );
	glVertex3fv( backUL.getValue() );
	glVertex3fv( backDL.getValue() );
	
	glEnd();

	// left
	glBegin( GL_LINES );

	glVertex3fv( frontDL.getValue() );
	glVertex3fv( backDL.getValue() );
	glVertex3fv( frontUL.getValue() );
	glVertex3fv( backUL.getValue() );

	glEnd();

	// right
	glBegin( GL_LINES );

	glVertex3fv( frontDR.getValue() );
	glVertex3fv( backDR.getValue() );
	glVertex3fv( frontUR.getValue() );
	glVertex3fv( backUR.getValue() );

	glEnd();
}



void VertexShape::drawVectorsFromVertices(	vgd::node::VertexShape *vertexShape,
											vgd::field::EditorRO< vgd::field::MFVec3f >& vectorsField, const float vectorsLength,
											std::vector< vgm::Vec3f >& vectors, glo::ArrayBuffer& buffer	)
{
	vgd::field::EditorRO< vgd::field::MFVec3f >		vertices		= vertexShape->getVertexRO();

	if (	vectorsField->size() == 0 ||
			vectorsField->size() != vertices->size() )
	{
		// @todo vgAssertN(vectorsField->size() != vertices->size(), ... )
		// do nothing
		return;
	}

	vectors.resize( vertices->size() * 2 );
	uint vectorsIndex = 0;

	// For each primitive:
	for(	uint i = 0, iEnd = vertices->size();
			i != iEnd;
			++i)
	{
		const vgm::Vec3f vertex	= (*vertices)[i];

		vectors[vectorsIndex] = vertex;
		++vectorsIndex;
		vectors[vectorsIndex] = vertex + (*vectorsField)[i] * vectorsLength;
		++vectorsIndex;
	}

	// Render all vectors from vertices for all primitives
	glo::VertexArrayObject::staticBindToDefault();
	glDisableVertexAttribArray( vgeGL::engine::VERTEX_INDEX );

	updateArrayBuffer( buffer, vectors.size()*sizeof(vgm::Vec3f), &vectors.front(), GL_DYNAMIC_DRAW );
	glVertexPointer( 3, GL_FLOAT, 0, 0 );
	glEnableClientState( GL_VERTEX_ARRAY );

	glDrawArrays( GL_LINES, 0, vectorsIndex );
}


void VertexShape::drawTriangleOrientation( vgd::node::VertexShape *vertexShape, vgeGL::rc::VertexShape * rc )
{
	std::vector< vgm::Vec3f >& drawCentersOfTrianglesVectors	= rc->drawCentersOfTrianglesVectors;
	std::vector< vgm::Vec3f >& drawRedArrowVectors				= rc->drawRedArrowVectors;
	std::vector< vgm::Vec3f >& drawGreenArrowVectors			= rc->drawGreenArrowVectors;
	std::vector< vgm::Vec3f >& drawBlueArrowVectors				= rc->drawBlueArrowVectors;

	vgd::field::EditorRO< vgd::field::MFVec3f >		vertex			= vertexShape->getVertexRO();

	vgd::field::EditorRO< vgd::field::MFUInt >	vertexIndex		= vertexShape->getVertexIndexRO();
	vgd::field::EditorRO< vgd::field::MFPrimitive >	primitives		= vertexShape->getPrimitiveRO();

	for(	vgd::field::MFPrimitive::const_iterator	i	= primitives->begin(),
													ie	= primitives->end();
		 i != ie;
		 ++i++	)
	{
		const vgd::node::Primitive& primitive(*i);

		// Start rendering the primitive.
		if ( primitive.getType() != vgd::node::Primitive::TRIANGLES )
		{
			// Next primitive ?
			vgAssertN( false, "Only vgd::node::Primitive::TRIANGLES is supported" );
			return;
		}

		//GLenum primitiveType = m_primTypeArray[ primitive.getType() ];

		vgAssert( primitive.getNumIndices() % 3 == 0 );
		drawCentersOfTrianglesVectors.resize( primitive.getNumIndices()/3 );
		drawRedArrowVectors.resize(		primitive.getNumIndices()/3 * 2 );
		drawGreenArrowVectors.resize(	primitive.getNumIndices()/3 * 2 );
		drawBlueArrowVectors.resize(	primitive.getNumIndices()/3 * 2 );

		const float fFactorArrowLength = 0.4f;

		uint index = 0;
		const uint iEnd = primitive.getIndex() + primitive.getNumIndices();
		for(	uint i = primitive.getIndex();
				i != iEnd;
				// nothing
			)
		{
			const uint vertexIndexA = (*vertexIndex)[i++];
			const uint vertexIndexB = (*vertexIndex)[i++];
			const uint vertexIndexC = (*vertexIndex)[i++];

			const vgm::Vec3f vA = (*vertex)[vertexIndexA];
			const vgm::Vec3f vB = (*vertex)[vertexIndexB];
			const vgm::Vec3f vC = (*vertex)[vertexIndexC];

			const vgm::Vec3f vTriangleCenter = (vA + vB + vC ) / 3.f;

			// triangle center
			drawCentersOfTrianglesVectors[index/2] = vTriangleCenter;

			// AB
			drawRedArrowVectors[index]		= vB;
			drawRedArrowVectors[index+1]	= vB + (vTriangleCenter - vB ) * fFactorArrowLength;

			// BC
			drawGreenArrowVectors[index]	= vC;
			drawGreenArrowVectors[index+1]	= vC + (vTriangleCenter - vC ) * fFactorArrowLength;

			// CA
			drawBlueArrowVectors[index] = vA;
			drawBlueArrowVectors[index+1] = vA + (vTriangleCenter - vA ) * fFactorArrowLength;

			index += 2;
		}
	}

	// Render calls
	glo::VertexArrayObject::staticBindToDefault();
	glDisableVertexAttribArray( vgeGL::engine::VERTEX_INDEX );

	//	centers of triangles
	updateArrayBuffer(	rc->drawCentersOfTrianglesBuffer,
						drawCentersOfTrianglesVectors.size()*sizeof(vgm::Vec3f), &drawCentersOfTrianglesVectors.front(),
						GL_DYNAMIC_DRAW );
	glVertexPointer( 3, GL_FLOAT, 0, 0 );
	glEnableClientState( GL_VERTEX_ARRAY );

	glPointSize( 3.f );
	glColor3f( 1.f, 1.f, 1.f );
	glDrawArrays( GL_POINTS, 0, drawCentersOfTrianglesVectors.size() );

	// AB
	glColor3f( 1.f, 0.f, 0.f );
	updateArrayBuffer(	rc->drawRedArrowBuffer,
						drawRedArrowVectors.size()*sizeof(vgm::Vec3f), &drawRedArrowVectors.front(),
						GL_DYNAMIC_DRAW );
	glVertexPointer( 3, GL_FLOAT, 0, 0 );
	//glEnableClientState( GL_VERTEX_ARRAY );

	glDrawArrays( GL_LINES, 0, drawRedArrowVectors.size() );

	// BC
	glColor3f( 0.f, 1.f, 0.f );
	updateArrayBuffer(	rc->drawGreenArrowBuffer,
						drawGreenArrowVectors.size()*sizeof(vgm::Vec3f), &drawGreenArrowVectors.front(),
						GL_DYNAMIC_DRAW );
	glVertexPointer( 3, GL_FLOAT, 0, 0 );
	//glEnableClientState( GL_VERTEX_ARRAY );

	glDrawArrays( GL_LINES, 0, drawGreenArrowVectors.size() );

	// CA
	glColor3f( 0.f, 0.f, 1.f );
	updateArrayBuffer(	rc->drawBlueArrowBuffer,
						drawBlueArrowVectors.size()*sizeof(vgm::Vec3f), &drawBlueArrowVectors.front(),
						GL_DYNAMIC_DRAW );
	glVertexPointer( 3, GL_FLOAT, 0, 0 );
	//glEnableClientState( GL_VERTEX_ARRAY );

	glDrawArrays( GL_LINES, 0, drawBlueArrowVectors.size() );
}



/**
 * Be careful, the elements of this enumeration are ordered(see vgd::node::Primitive)
 */
GLenum VertexShape::m_primTypeArray[] = {
	0, //NONE,

	GL_POINTS,

	GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP,

	GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, 

	GL_QUADS, GL_QUAD_STRIP,

	GL_POLYGON
};



} // namespace painter

} // namespace handler

} // namespace vgeGL
