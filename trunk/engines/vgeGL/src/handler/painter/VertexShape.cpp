// VGSDK - Copyright (C) 2004-2006, 2008, 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/VertexShape.hpp"

#include <glo/GLSLProgram.hpp>
#include <glo/Texture.hpp>

#include <vgd/basic/toString.hpp>
// @todo Move Box stuff to Box handler (FIXME)
#include <vgd/node/Box.hpp>
// @todo Move DrawStyle stuff to drawStyle handler (FIXME)
#include <vgd/node/DrawStyle.hpp>
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
#include "vgeGL/engine/ProgramGenerator.hpp"
#include "vgeGL/engine/VertexShaderGenerator.hpp"

#include "vgeGL/handler/painter/DrawStyle.hpp"
#include "vgeGL/handler/painter/OutputBufferProperty.hpp"

#include "vgeGL/rc/GLSLProgram.hpp"
#include "vgeGL/rc/TDisplayListHelper.hpp"
#include "vgeGL/rc/VertexShape.hpp"

/*
supported field (VBO):
TEXCOORD
NORMAL
VERTEX
VERTEX INDEX
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



void updateVAO( glo::VertexArrayObject& rc )
{
	const bool isEmpty = rc.isEmpty();

	if ( isEmpty )	rc.generate();

	rc.bind();
}



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
		buffer.bufferData( size, ptr, bufferUsage );
	}
	else
	{
		buffer.bufferSubData( 0, size, ptr );
	}
}



template< typename ValueType >
void updateTexCoordArrayBuffer( vgd::node::VertexShape * vertexShape, const uint unit, vgeGL::rc::VertexShape * rc, const GLenum bufferUsage )
{
	using vgd::field::EditorRO;
	typedef vgd::field::TMultiField< ValueType > ValueContainerType;

	EditorRO< ValueContainerType > texCoord = vertexShape->getFTexCoordRO< ValueContainerType >( unit );
	updateArrayBuffer( rc->texCoord[unit], texCoord->size()*sizeof(ValueType), texCoord->ptr(), bufferUsage );
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
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	vgAssert( dynamic_cast< vgd::node::VertexShape* >(pNode) != 0 );
	vgd::node::VertexShape *pVertexShape = static_cast< vgd::node::VertexShape* >(pNode);

	// GLSL STATE UPDATE
	using vgeGL::engine::GLSLState;
	GLSLState& glslState = pGLEngine->getGLSLState();

	// Updates GLSL state with vertex shape info
// @todo uncomment GLSLState::COLOR4_BIND_PER_VERTEX
	// glslState.setEnabled( GLSLState::COLOR4_BIND_PER_VERTEX, pVertexShape->getColor4Binding() == vgd::node::BIND_PER_VERTEX );

	// setTexCoordDim for texUnitState of glslState => MUST BE DONE for pg->generate() using generateFunction_ftexgen(), generate_samplers() and generate_texLookups()
	// pGLEngine->getGLSLStateStack().push();
	if ( pGLEngine->isTextureMappingEnabled() )
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
				const int32 dimTexCoord = pVertexShape->getTexCoordDim( i );
				if (							(texUnitState->getTexCoordDim() != dimTexCoord)	)
				{
					// @toto glslState.setTexCoordDim( 0/*Unit*/, 2 /* Dim */ ); that invalidate DF
					texUnitState->setTexCoordDim( static_cast< uint8 >(dimTexCoord) );
					glslState.textures.dirty();
				}
			}
			// else no state for the texture unit, so nothing to do
#ifdef _DEBUG
			else
			{
				if ( pVertexShape->getTexCoordDim( i ) > 0 )
				{
					vgAssertN(	false, "VertexShape(%s).texCoord%i is not empty, but there is no texture",
										pVertexShape->getName().c_str(), i );
				}
			}
#endif
		}



/*
		vgd::node::VertexShape::ConstIteratorIndexSet i, iEnd;
		for(	boost::tie( i, iEnd ) = pVertexShape->getTexUnitsIterators();
				i != iEnd;
				++i )
		{
			const uint unit = *i;

			vgd::Shp< GLSLState::TexUnitState > texUnitState = glslState.textures.getState( unit );

			if (	texUnitState &&
					(pVertexShape->getTexCoordBinding( unit ) != vgd::node::BIND_OFF)	)
			{
				
				if ( texUnitState->getTexCoordDim() != dimTexCoord )
				{
					// @toto glslState.setTexCoordDim( 0 Unit, 2  Dim ); that invalidate DF
					texUnitState->setTexCoordDim( static_cast< uint8 >(dimTexCoord) );
					glslState.textures.dirty();
				}
			}
			else
			{
				texUnitState->setTexCoordDim( 0 );
#ifdef _DEBUG
				vgLogDebug(	"VertexShape(%s).texCoord%i is not empty, but there is no texture",
								pVertexShape->getName().c_str(), unit );
#endif
			}
		}*/
	}

	// GLSL
	if ( pGLEngine->isGLSLEnabled() )
	{
		if ( glslState.isDirty() )
		{
			// GENERATION
			vgd::Shp< vgeGL::engine::ProgramGenerator > pg = pGLEngine->getGLSLProgramGenerator();
			pg->generate( pGLEngine );
			//pGLEngine->getGLSLStateStack().pop();

			// CACHE
			const std::string	fullCode	= pg->getCode();
			const std::string&	vs			= pg->getVertexShaderGenerator()->getCode();
			const std::string&	fs			= pg->getFragmentShaderGenerator()->getCode();

/*#ifdef _DEBUG
			static bool firstTime = true;
			vgDebug::StdStreamsToFiles redirection(	"GLSL.cout.txt", "GLSL.cerr.txt", firstTime ? vgDebug::StdStreamsToFiles::TRUNCATE : vgDebug::StdStreamsToFiles::APPEND );
			if ( firstTime ) firstTime = false;

			std::cout << "Generates shaders\n" << std::endl;
			std::cout << "Vertex shader\n" << std::endl << vs << std::endl;
			std::cout << "Fragment shader\n" << std::endl << fs << std::endl;
			std::cout << "\n\n\n";
#endif*/
			using glo::GLSLProgram;
			GLSLProgram * program = pGLEngine->getGLSLManager().get< GLSLProgram >( fullCode );

			if ( program == 0 )
			{
				// Not found in cache, so creates a new one
				program = new glo::GLSLProgram;

				// Compiles and links
				std::string vsInfoLog;
				std::string fsInfoLog;
				std::string linkInfoLog;
				const bool compileVSRetVal = program->addShader( vs.c_str(),pg->getVertexShaderGenerator()->getShaderType(), false );
				if ( !compileVSRetVal )	vsInfoLog = program->getInfoLog();

				const bool compileFSRetVal = program->addShader( fs.c_str(), pg->getFragmentShaderGenerator()->getShaderType(), false );
				if ( !compileFSRetVal )	fsInfoLog = program->getInfoLog();

//				const bool compileGSRetVal = program->addShader( fs.c_str(), pg->getGeometryShaderGenerator()->getShaderType(), false );

				//namespace vgeGLPainter = vgeGL::handler::painter;
				//vgeGLPainter::OutputBufferProperty::bindFragDataLocations( pGLEngine, program );

				const bool linkRetVal = program->link();
				if ( !linkRetVal )	linkInfoLog = program->getInfoLog();

				if ( !compileVSRetVal || !compileFSRetVal || !linkRetVal )
				{
					std::cout << "=======================================================================================\n" << std::endl;

					std::cout << "Vertex shader\n" << "=============\n" << std::endl << vs << std::endl;
					std::cout << "Fragment shader\n" << "===============\n" << std::endl << fs << std::endl;
					std::cout << "\n\n\n";

					// if ( !vsInfoLog.empty() )	std::cout << vsInfoLog << std::endl;
					// if ( !fsInfoLog.empty() )	std::cout << fsInfoLog << std::endl;
					// if ( !linkInfoLog.empty() )	std::cout << linkInfoLog << std::endl;
					std::cout << "Vertex shader info log:" << std::endl << vsInfoLog << std::endl;
					std::cout << "Fragment shader info log:" << std::endl << fsInfoLog << std::endl;
					std::cout << "Link info log:" << std::endl << linkInfoLog << std::endl;
				}

				if ( linkRetVal )
				{
					//std::cout << "Program link" << std::endl;
					pGLEngine->getGLSLManager().add( fullCode, program );
				}
				/*else
				{
					std::cout << "Program link fails !" << std::endl;
					std::cerr << "Program link fails !" << std::endl;

					std::cout << fullCode << std::endl;


					vgAssertN( false, "Program link fails !");
					vgLogDebug( "Program link fails !" );
					//std::cout << "Generates shaders\n" << std::endl;
					//std::cout << "Vertex shader\n" << std::endl << vs << std::endl;
					//std::cout << "Fragment shader\n" << std::endl << fs << std::endl;
					//std::cout << "\n\n\n";
					std::cerr << program->getInfoLog();
				}*/

/*#ifdef _DEBUG
				if ( !compileVSRetVal )	vgLogDebug("VERTEX shader compilation fails");
				if ( !compileFSRetVal )	vgLogDebug("FRAGMENT shader compilation fails");
//				if ( !compileGSRetVal )	vgLogDebug("GEOMETRY shader compilation fails");

				if ( !linkRetVal )
				{
					vgLogAssertN( false, "Program link fails !");
					cerr << program->getInfoLog();
				}
				else
				{
					vgLogDebug("Program link succeeded");
					vgLogDebug("Creates a new GLSL program.");
					vgLogDebug("GLSL managed program count : %i", pGLEngine->getGLSLManager().getNum());
				}
#endif*/
			}
			// else uses GLSL program found in cache



// @todo begin( OPTME only if new prog )
			// Sets uniform(s)
			if ( pGLEngine->gethCurrentProgram() != program )
			{
				//
				pGLEngine->sethCurrentProgram( program );

				// SAMPLERS
				setSamplers( pGLEngine, program );

				// UNIFORM
				if ( pGLEngine->getUniformState().getSize() > 0 )
				{
					pGLEngine->getUniformState().apply( pGLEngine );
				}
			}
			// else nothing to do

			glslState.validate();
// @todo end
		}
		else // if ( glslState->isDirty() )
		{
			// glslState is valid, so nothing to do
//#define _DEBUG
#ifdef _DEBUG
			// Checks if glslState->isValid() is the correct value
			//vgLogDebug("glslState is valid");

			// GENERATION
			vgd::Shp< vgeGL::engine::ProgramGenerator > pg = pGLEngine->getGLSLProgramGenerator();
			pg->generate( pGLEngine );

			// CACHE
			const std::string	fullCode	= pg->getCode();
			const std::string&	vs			= pg->getVertexShaderGenerator()->getCode();
			const std::string&	fs			= pg->getFragmentShaderGenerator()->getCode();
			using glo::GLSLProgram;
			GLSLProgram * program = pGLEngine->getGLSLManager().get< GLSLProgram >( fullCode );
			if ( program != pGLEngine->getCurrentProgram() )
			{
				vgAssertN( program == pGLEngine->getCurrentProgram(), "glslState->isValid() should be dirty." );
			}
#endif
		}
	}
	else
	{
		//pGLEngine->sethCurrentProgram();
		vgeGL::rc::GLSLProgram::useFixedPaths();
	}

	// Renders the VertexShape
	::vgeGL::handler::painter::DrawStyle::paintVertexShapeWithShapeProperty( pGLEngine, pVertexShape, this );

	// Renders additional properties of VertexShape
	using vgd::node::DrawStyle;

	DrawStyle::NormalLengthValueType	normalLength			= pGLEngine->getGLState().getNormalLength();
	const bool							showOrientationValue	= pGLEngine->getGLState().getShowOrientation();
	DrawStyle::BoundingBoxValueType		bbValue					= pGLEngine->getGLState().getBoundingBox();

	const bool additionalProperties =	(normalLength > 0.f) || showOrientationValue ||
										(bbValue != vgd::node::DrawStyle::NONE);

	if ( additionalProperties )
	{
		// Makes a backup of GLSL activation state
		using vgeGL::engine::Engine;

		vgd::Shp< Engine::GLSLActivationState > glslActivationState = pGLEngine->getGLSLActivationState();
		pGLEngine->sethCurrentProgram();

		// *** DRAWSTYLE.normalLength ***
		if ( normalLength > 0.f )
		{
			::vgeGL::handler::painter::DrawStyle::paintVertexShapeNormals( pGLEngine, pVertexShape, this );
		}

		// *** DRAWSTYLE.showOrientation ***
		if ( showOrientationValue )
		{
			// FIXME optimize me
			glPushAttrib( GL_ALL_ATTRIB_BITS );

			glDisable( GL_LIGHTING );
			//glColor3f( 1.f, 1.f, 1.f );
			// END FIXME

			//float vColor[4];
			//glGetFloatv( GL_COLOR_CLEAR_VALUE, vColor );
			//glColor4fv( vColor );
			//glEnable( GL_POLYGON_OFFSET_FILL );
			//glPolygonOffset( 1.0f, 1.0f );
			//glDepthFunc( GL_EQUAL );

			//glDisable( GL_DEPTH_TEST );
			drawTriangleOrientation( pVertexShape );

			//glDisable(GL_POLYGON_OFFSET_FILL);
			///@todo FIXME OPTME
			glPopAttrib();
		}

		// *** DRAWSTYLE.boundingBox ***
		if ( bbValue != vgd::node::DrawStyle::NONE )
		{
			// FIXME optimize me
			glPushAttrib( GL_ALL_ATTRIB_BITS );

			glDisable( GL_LIGHTING );

			glDisable( GL_TEXTURE_1D );
			glDisable( GL_TEXTURE_2D );

			glLineWidth( 2.f );
			// END FIXME

			switch ( bbValue )
			{
				case vgd::node::DrawStyle::NONE:
					break;

				case vgd::node::DrawStyle::OBJECT_SPACE:
					glColor3f( 0.f, 0.f, 1.f );
					drawBoundingBox( pGLEngine, pVertexShape );
					break;

				case vgd::node::DrawStyle::AA_OBJECT_SPACE:
					glColor3f( 1.f, 0.f, 0.f );
					drawXfBoundingBox( pGLEngine, pVertexShape );
					break;

				case vgd::node::DrawStyle::OBJECT_AND_AA_OBJECT_SPACE:
					glColor3f( 0.f, 0.f, 1.f );
					drawBoundingBox( pGLEngine, pVertexShape );
					glColor3f( 1.f, 0.f, 0.f );
					drawXfBoundingBox( pGLEngine, pVertexShape );
					break;

				default:
					vgAssertN( false, "Unknown DrawStyle.boundingBox value." );
			}

			///@todo FIXME OPTME
			glPopAttrib();
		}

		// Restores GLSL activation state
		pGLEngine->setGLSLActivationState( glslActivationState );
	}

	// Restores glslState
	/*if ( pGLEngine->isTextureMappingEnabled() )
	{
		vgd::node::VertexShape::ConstIteratorIndexSet i, iEnd;
		for(	boost::tie( i, iEnd ) = pVertexShape->getTexUnitsIterators();
				i != iEnd;
				++i )
		{
			const uint unit = *i;

			vgd::Shp< GLSLState::TexUnitState > texUnitState = glslState.textures.getState( unit );
	
			if (	(pVertexShape->getTexCoordBinding( unit ) != vgd::node::BIND_OFF) &&
					texUnitState	)
			{
				texUnitState->setTexCoordDim( 0 );
			}
		}
	}*/
//	glPopAttrib();

	// Validates node
	pNode->getDirtyFlag(pNode->getDFNode())->validate();
}



void VertexShape::setSamplers( vgeGL::engine::Engine * pGLEngine, glo::GLSLProgram * program )
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
	GLSLState& glslState = pGLEngine->getGLSLState();

	uint		i		= 0;
	const uint	iEnd	= pGLEngine->isTextureMappingEnabled() ? glslState.textures.getMax() : 0;

	for( uint foundTexture = 0; i != iEnd; ++i )
	{
		const vgd::Shp< GLSLState::TexUnitState > current = glslState.textures.getState( i );

		// Empty texture unit, so do nothing
		if ( current == 0 )	continue;

		const uint&					unit	= i;
		const std::string			strUnit = vgd::basic::toString( unit );

		const vgd::node::Texture *	textureNode	= current->getTextureNode();
		glo::Texture *				texture		= current->getTexture();
		const uint8					texCoordDim	= current->getTexCoordDim();
		//const vgd::node::TexGen *	texGen		= current->getTexGenNode();

		//
		// @todo hasImage() ? see handler Texture::preSynchronize() : idea boolean value in glo::Texture for "completeness" ?
		// @todo case textureNode and texture, but textureNode with IImage containing no data (texInfo.iimage->pixels() == 0)
		const bool isTextureComplete = textureNode && textureNode->hasImage() && texture; // @todo not accurate

		//
		const bool hasTexCoord = texCoordDim > 0; // pVertexShape->getTexCoordDim(unit) || texGen;

		//
		const bool isUnitComplete = isTextureComplete && hasTexCoord;

		// SAMPLER
		if ( isUnitComplete )
		{
			if ( program )
			{
				vgAssert( program->isInUse() );

				const vgd::node::Texture::UsageValueType usage = textureNode->getUsage();

				if ( usage == vgd::node::Texture::SHADOW )
				{
					program->setUniform1i( "texMap2DShadow[" + glslState.getPrivate( unit ) + "]", unit );
				}
				else if ( usage == vgd::node::Texture::IMAGE )
				{
					program->setUniform1i( "texMap2D[" + strUnit + "]", unit );
					//configureTexCoord( pVertexShape, unit, pVertexShape->getTexCoordDim(unit) /* @todo OPTME */ );
				}
				else
				{
					vgAssert( false );
				}
			}
			else
			{
				/*pGLEngine->activeTexture( unit );
				const uint texCoordDim = pVertexShape->getTexCoordDim(unit);
				if ( texCoordDim > 0 )
				{
					texture->enable();
				}*/
				//configureTexCoord( pVertexShape, unit,  texCoordDim );
			}
		}

		//
		++foundTexture;
		if ( foundTexture == glslState.textures.getNum() )
		{
			break;
		}
	}
}



void VertexShape::unapply ( vge::engine::Engine* , vgd::node::Node* )
{}



void VertexShape::setToDefaults()
{}



/**
 * @todo Use Settings (FIXME).
 */
void VertexShape::paintMethodChooser( vgeGL::engine::Engine* engine, vgd::node::VertexShape* vertexShape )
{
	paint(engine, vertexShape, vgeGL::engine::VertexArrayMethod() );

//glPushClientAttrib( GL_CLIENT_ALL_ATTRIB_BITS );
	//const vgd::node::VertexShape::DeformableHintValueType deformableHint = vertexShape->getDeformableHint();

	/* ImmediateMode */
	//paint( pGLEngine, pVertexShape );

	/* ImmediateMode in DL */
	//paintDisplayList	( pGLEngine, pVertexShape ); 

	/* Vertex Array */
	/* Vertex Array in DL */
	/*if ( deformableHint == vgd::node::VertexShape::STATIC )
	{
//		paint(engine, vertexShape, vgeGL::engine::VertexArrayMethod() );
// @todo Reenabled display list usage or uses VAO
		const vgd::node::MultipleInstances * multipleInstances = engine->getGLState().getMultipleInstances();
		if ( multipleInstances )
		{
			paint(engine, vertexShape, vgeGL::engine::VertexArrayMethod() );
		}
		else
		{
			paint(engine, vertexShape, vgeGL::engine::VertexArrayMethod() );
			//paint(engine, vertexShape, vgeGL::engine::VertexArrayDisplayListMethod() ); // @todo don't work on Radeon
		}
	}
	else
	{
		assert( 	(deformableHint == vgd::node::VertexShape::DYNAMIC) ||
					(deformableHint == vgd::node::VertexShape::STREAM)	);

		paint(engine, vertexShape, vgeGL::engine::VertexArrayMethod() );
	}*/
	
	/* Vertex Arrays in VBO */
	//paintVBO				( pGLEngine, pVertexShape );
	//paintVBOVertexArray	( pGLEngine, pVertexShape );

//glPopClientAttrib();
}



/**
 * Support for vertex.
 * 
 * Support for normal				with BIND_OFF, BIND_PER_VERTEX.
 * Support for color4				with BIND_OFF, BIND_PER_VERTEX.
 * Support for secondaryColor4		with BIND_OFF, BIND_PER_VERTEX.
 * Support for texCoord				with BIND_OFF, BIND_PER_VERTEX.
 * Support for edgeFlag				with BIND_OFF, BIND_PER_VERTEX.
 * 
 * Support for primitive.
 * Support for vertexIndex.
 * 
 * Support for *Binding.
 * 
 * @todo Support BIND_OVERALL, BIND_PER_PRIMITIVE.
 */
void VertexShape::paint(	vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pVertexShape,
							const vgeGL::engine::VertexArrayMethod& method )
{
	// *** BIND_OVERALL ***
	// Nothing to do, because not supported.
#ifdef _DEBUG
	// EDGE FLAG
	if (	(pVertexShape->getEdgeFlagBinding() != vgd::node::BIND_OFF ) &&
			(pVertexShape->getEdgeFlagBinding() != vgd::node::BIND_PER_VERTEX ) )
	{
		vgAssertN( false, "Bindings other than BIND_OFF and BIN_PER_VERTEX are not supported for edgeflag." );
		return;
	}

	// TEX COORD
	vgAssert(	(pVertexShape->getNumTexUnits() > 1 &&
			isGL_ARB_multitexture() && "MultiTexture not currently supported.") ||
			(pVertexShape->getNumTexUnits() <= 1) );

	for(	int32 i=0;
			i < pVertexShape->getNumTexUnits();
			++i )
	{
		if (	(pVertexShape->getTexCoordBinding( i ) != vgd::node::BIND_OFF ) &&
				(pVertexShape->getTexCoordBinding( i ) != vgd::node::BIND_PER_VERTEX ) )
		{
			vgAssertN( false, "Bindings other than BIND_OFF and BIN_PER_VERTEX are not supported for textures coordinates." );
			return;
		}
	}

	// SECONDARY COLOR4
	if (	(pVertexShape->getSecondaryColor4Binding() != vgd::node::BIND_OFF ) &&
			(pVertexShape->getSecondaryColor4Binding() != vgd::node::BIND_PER_VERTEX ) )
	{
		vgAssertN( false, "Bindings other than BIND_OFF and BIN_PER_VERTEX are not supported for secondaryColor4." );
		return;
	}

	// COLOR4
	if (	(pVertexShape->getColor4Binding() != vgd::node::BIND_OFF ) &&
			(pVertexShape->getColor4Binding() != vgd::node::BIND_PER_VERTEX ) )
	{
		vgAssertN( false, "Bindings other than BIND_OFF and BIN_PER_VERTEX are not supported for color4." );
		return;
	}
	
	// NORMAL
	if (	(pVertexShape->getNormalBinding() != vgd::node::BIND_OFF ) &&
			(pVertexShape->getNormalBinding() != vgd::node::BIND_PER_VERTEX ) )
	{
		vgAssertN( false, "Bindings other than BIND_OFF and BIN_PER_VERTEX are not supported for normal." );
		return;
	}
#endif

	// VERTEX-VERTEXINDEX-PRIMITIVE
	vgd::field::EditorRO< vgd::field::MFPrimitive >	primitives( pVertexShape->getFPrimitiveRO() );

	/*if ( primitives->size() > 1 )
	{
		vgLogDebug("primitive count %i for vertex shape %s", primitives->size(), pVertexShape->getName().c_str() );
	}*/

	//int indexPrim = 0;
	for(	vgd::field::MFPrimitive::const_iterator	i	= primitives->begin(),
													ie	= primitives->end();
			i != ie;
			++i/*, ++indexPrim*/)
	{
		const vgd::node::Primitive& primitive(*i);

		// *** BIND_PER_PRIMITIVE ***
		// Nothing to do, because not supported.

		// render a primitive
		paint( pGLEngine, pVertexShape, primitive, method );
	}
}



// submit a primitive of VertexShape
// using VertexArray stored in buffer objects
// @todo VertexArrayMethod => ?
void VertexShape::paint(	vgeGL::engine::Engine * engine, vgd::node::VertexShape * node,
							const vgd::node::Primitive& primitive,
							const vgeGL::engine::VertexArrayMethod& /*method*/ )
{
	typedef vgeGL::rc::VertexShape GLResourceType;

	// RC
	// Gets the resource manager
	vgeGL::engine::Engine::GLManagerType& manager = engine->getGLManager();

	// Gets node dirty flag
	vgd::field::DirtyFlag * nodeDF = node->getDirtyFlag( node->getDFNode() );

	// Gets resource associated to the given node
	::glo::IResource 	* resource			= manager.getAbstract( node );
	GLResourceType		* castedResource	= dynamic_cast< GLResourceType * >(resource);

	// STEP 1
	// Sometimes GLResourceType must be changed for a given node (display list to/from vbo for example).
	// is it the case now ?
	if ( ( castedResource == 0 ) && ( resource != 0 ) )
	{
		// There is a resource, but not with the expected type.
		// Dynamic change of handler ? or node that must be process differently (static, dynamic for VertexShape) ?

		// Removes the resource from the manager
		manager.remove( node );
		resource = 0;
		vgAssertN( (resource == 0) && (castedResource==0), "Internal error." );
	}
	// else if resource != 0 && castedResource != 0 => see step 2
	// else if resource == 0 && castedResource == 0 => see step 2
	// else if resource == 0 && castedResource != 0 => impossible

	// STEP 2
	vgAssertN(	(resource==0 && castedResource==0) ||
				(resource!=0 && castedResource!=0), "Internal error." );

	// Creates resource if needed
	if ( resource == 0 )
	{
		vgAssertN( castedResource == 0, "Internal error." );

		// Creates the resource
		castedResource = new GLResourceType();
		resource = castedResource;

		// Adds the resource to the manager
		manager.add( node, castedResource );
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
		configureRenderingArrays( engine, node, castedResource );
		/*handler->*/renderArrays(	engine, node,
									primitive, // @todo not cute
									castedResource );
		//unconfigureRenderingArrays( engine, node, primitive, castedResource );

		// Checks if synchronize() method have validated the node dirty flag
		// assert( nodeDF->isValid() );	not always validated by synchronize, so don't check
	}
	else
	{
		// No modifications in the node

		// Binds the resource
		//handler->bind( engine, node, castedResource );

		if ( !engine->isGLSLEnabled() ) configureRenderingArrays( engine, node, castedResource );

		/*handler->*/renderArrays(	engine, node,
									primitive, // @todo not cute
									castedResource );
		//unconfigureRenderingArrays( engine, node, primitive, castedResource );
	}
}



// @todo take care of deformable hint modification
void VertexShape::update(	vgeGL::engine::Engine * pGLEngine, vgd::node::VertexShape *pVertexShape,
							vgeGL::rc::VertexShape * rc )
{
	// VAO
//	if ( true /*pGLEngine->isVertexArrayObjectEnabled()*/ ) // @todo
//	{
		updateVAO( rc->vao );
//	}

	// Do nothing if VBO is not enabled
	if ( pGLEngine->isVertexBufferObjectEnabled() == false )	return;


	// Updates all VBO
	const GLenum bufferUsage = convertDeformableHint2GLUsage( pVertexShape );

	// TEXCOORD
	//if ( pGLEngine->isTextureMappingEnabled ) // always update texCoord array(s) even if pGLEngine->isTextureMappingEnabled() == false
	vgd::node::VertexShape::ConstIteratorIndexSet i, iEnd;
	for(	boost::tie( i, iEnd ) = pVertexShape->getTexUnitsIterators();
			i != iEnd;
			++i )
	{
		const uint unit = *i;
		const uint8 texCoordDim	= pVertexShape->getTexCoordDim(unit);
		updateTexCoord( pVertexShape, unit,  texCoordDim, rc );
	}


	// NORMAL
	if ( pVertexShape->getNormalBinding() == vgd::node::BIND_PER_VERTEX )
	{
		vgd::field::EditorRO< vgd::field::MFVec3f > normal;
		normal = pVertexShape->getFNormalRO();
		updateArrayBuffer( rc->normal, normal->size()*sizeof(vgm::Vec3f), normal->ptr(), bufferUsage );
	}


	// VERTEX
	vgd::field::EditorRO< vgd::field::MFVec3f > vertex;
	vertex = pVertexShape->getFVertexRO();
	updateArrayBuffer( rc->vertex, vertex->size()*sizeof(vgm::Vec3f), vertex->ptr(), bufferUsage );


	// VERTEX INDEX
	vgd::field::EditorRO< vgd::field::MFUInt32 > vertexIndex;
	vertexIndex = pVertexShape->getFVertexIndexRO();
	updateArrayBuffer( rc->vertexIndex, vertexIndex->size()*sizeof(uint32), vertexIndex->ptr(), GL_STATIC_DRAW /*bufferUsage adds hints in VertexShape node*/ );

	// @todo multiple instances data
}


void VertexShape::configureRenderingArrays(	vgeGL::engine::Engine * pGLEngine, vgd::node::VertexShape *pVertexShape,
											vgeGL::rc::VertexShape * rc )
{
	// GLSL state
	using vgeGL::engine::GLSLState;
	GLSLState& glslState = pGLEngine->getGLSLState();

	//
	vgd::field::EditorRO< vgd::field::MFVec3f >		normal;
	vgd::field::EditorRO< vgd::field::MFVec3f >		vertex;
	vgd::field::EditorRO< vgd::field::MFUInt32 >	vertexIndex;

	//
	const GLvoid *pArray = 0;

	//
	glo::GLSLProgram * program = pGLEngine->gethCurrentProgram();


	// *** Step 1 : Setup arrays. ***

	if ( true /*pGLEngine->isTextureMappingEnabled()*/ )
	{
		vgd::node::VertexShape::ConstIteratorIndexSet i, iEnd;
		for(	boost::tie( i, iEnd ) = pVertexShape->getTexUnitsIterators();
				i != iEnd;
				++i )
		{
			const uint unit = *i;
			//const vgd::Shp< GLSLState::TexUnitState > current = glslState.textures.getState( unit );

			// Empty texture unit, so do nothing
			//if ( current == 0 ) continue;

			//const vgd::node::Texture *	textureNode	= current->getTextureNode();
			//glo::Texture *				texture		= current->getTexture();
			//const uint8					texCoordDim	= current->getTexCoordDim();

			//
			// @todo hasImage() ? see handler Texture::preSynchronize() : idea boolean value in glo::Texture for "completeness" ?
			// @todo case textureNode and texture, but textureNode with IImage containing no data (texInfo.iimage->pixels() == 0)
			//const bool isTextureComplete	= textureNode && textureNode->hasImage() && texture; // @todo not accurate
			//const bool hasTexCoord			= texCoordDim > 0;

			//const bool isUnitComplete = isTextureComplete && hasTexCoord;

			// TEXTURE COORDINATES
			//if ( isUnitComplete )
			//{
				if ( program )
				{
					vgAssert( program->isInUse() );

					//switch ( textureNode->getUsage().value() )
					//{
						//case vgd::node::Texture::IMAGE:
							configureTexCoord( pGLEngine, pVertexShape, unit, pVertexShape->getTexCoordDim(unit) /* @todo OPTME */, rc, pGLEngine->isVertexBufferObjectEnabled() );
							//break;

						//case vgd::node::Texture::SHADOW:
							// nothing to do, tex coords are generated
							//break;

						//default:
							//vgAssertN( false, "Unknown usage %i", textureNode->getUsage().value() );
					//}
				}
				else
				{
					pGLEngine->activeTexture( unit );
					const uint texCoordDim = pVertexShape->getTexCoordDim(unit);
					//if ( texCoordDim > 0 )		texture->enable();
					glEnable( GL_TEXTURE_2D );
					configureTexCoord( pGLEngine, pVertexShape, unit,  texCoordDim, rc, pGLEngine->isVertexBufferObjectEnabled() );
				}
			//}
			// else nothing to do
		} // end for
	}
	// else nothing to do


/*	const int32 numTexUnits = pGLEngine->isTextureMappingEnabled() ? pVertexShape->getNumTexUnits() : 0;

	if ( numTexUnits >= 1 )
	{
		for(	int32 unit = numTexUnits-1;
				unit >= 0;
				--unit )
		{
			const std::string strUnit = vgd::basic::toString( unit );
*/
// FIXME see Texture2D handler
//	// scaleFactors
//	vgm::Vec3f scaleFactors;
//	pResource->getScaleFactors( scaleFactors[0], scaleFactors[1], scaleFactors[2] );
//	
//	vgm::MatrixR scaleMatrix;
//	scaleMatrix.setScale( scaleFactors );
//	
//	// apply scale to vge.
//	vgm::MatrixR& textureMatrix(
//		pGLEngine->getTextureMatrix().getTop( pNode->getMultiAttributeIndex() )
//			);
//
//	textureMatrix = scaleMatrix * textureMatrix;
//	
//	// apply scale to vgeGL.
//	glMatrixMode( GL_TEXTURE );
//	glLoadMatrixf( reinterpret_cast<const float*>( textureMatrix.getValue() ) );
/*
			vgd::Shp< GLSLState::TexUnitState > texUnitState = glslState.textures.getState( unit );
			if ( texUnitState )
			{
				// Retrieves current texture object from engine
				::glo::Texture * texture;

				if ( texUnitState )
				{
					texture = texUnitState->getTexture();
				}
				else
				{
					texture = 0;
				}

				if ( texture != 0 )
				{
				// ??? not more lazy
				//pVertexShape->getTexCoordBinding( unit ) == vgd::node::BIND_PER_VERTEX 
					if ( program )
					{
						assert( program->isInUse() );

						program->setUniform1i( "texUnit" + strUnit, unit );
					}
					else
					{
						pGLEngine->activeTexture( unit );
						texture->enable();
					}
				}
				else
				{
					vgLogDebug( "There are texture coordinates in this shape, but no texture !!! Skip this texture unit." );
					break;
				}

				//

			} // BIND_PER_VERTEX
		} // for(	int32 unit = numTexUnits-1;
	}
	// else nothing to do.
*/


	// NORMAL
	if ( pVertexShape->getNormalBinding() == vgd::node::BIND_PER_VERTEX )
	{
		if ( pGLEngine->isVertexBufferObjectEnabled() )
		{
			rc->normal.bind();
		}
		else
		{
			pArray = static_cast< const GLvoid* >( pVertexShape->getFNormalRO()->ptr() );
		}

		//glNormalPointer( GL_FLOAT, 0, pArray );
		//glEnableClientState( GL_NORMAL_ARRAY );
		glEnableVertexAttribArray( vgeGL::engine::NORMAL_INDEX );
		glVertexAttribPointer( vgeGL::engine::NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, 0, pArray );
	}
	else
	{
		glDisableVertexAttribArray( vgeGL::engine::NORMAL_INDEX );
	}

	// VERTEX
	if ( pGLEngine->isVertexBufferObjectEnabled() )
	{
		rc->vertex.bind();
	}
	else
	{
		pArray = static_cast< const GLvoid* >( pVertexShape->getFVertexRO()->ptr() );
	}

	//glVertexPointer( 3, GL_FLOAT, 0, pArray );
	//glEnableClientState( GL_VERTEX_ARRAY );
	glEnableVertexAttribArray( vgeGL::engine::VERTEX_INDEX );
	glVertexAttribPointer( vgeGL::engine::VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, 0, pArray );
}



void VertexShape::unconfigureRenderingArrays(	vgeGL::engine::Engine * pGLEngine, vgd::node::VertexShape *pVertexShape, const vgd::node::Primitive& primitive,
												vgeGL::rc::VertexShape * rc )
{
	//
	using vgeGL::engine::GLSLState;
	GLSLState& glslState = pGLEngine->getGLSLState();

	// @todo OPTME remove me
	if ( pGLEngine->isVertexBufferObjectEnabled() )
	{
		rc->vertexIndex.unbind();
	}

	// *** Step 3 : Disable arrays ***

	// TEX COORD
	if ( pGLEngine->isTextureMappingEnabled() )
	{
		vgd::node::VertexShape::ConstIteratorIndexSet i, iEnd;
		for(	boost::tie( i, iEnd ) = pVertexShape->getTexUnitsIterators();
				i != iEnd;
				++i )
		{
			const uint unit = *i;
			vgd::Shp< GLSLState::TexUnitState > texUnitState = glslState.textures.getState( unit );

			if (	texUnitState /*&&
					(pVertexShape->getTexCoordBinding( unit ) != vgd::node::BIND_OFF)*/	)
			{
				configureTexCoord( pGLEngine, pVertexShape, unit, 0, rc, pGLEngine->isVertexBufferObjectEnabled() );
			}
		}
	}



	// @todo Optimizes numTexUnits == 1 case
	/*const uint numTexUnits = pVertexShape->getNumTexUnits();
	if ( numTexUnits >= 1 )
	{
		for(	int32 unit=pVertexShape->getNumTexUnits()-1;
				unit>=0;
				--unit )
		{	
			if ( pVertexShape->getTexCoordBinding( unit ) == vgd::node::BIND_PER_VERTEX )
			{
				// Retrieves current texture object from engine
				::glo::Texture * texture;
				vgd::Shp< GLSLState::TexUnitState > texUnitState = glslState.textures.getState( unit );
				if ( texUnitState )
				{
					texture = texUnitState->getTexture();
				}
				else
				{
					texture = 0;
				}

				if ( texture != 0 )
				{
					if ( !program )
					{
						pGLEngine->activeTexture( unit );
						texture->disable();
					}
					// nothing to do
				}
				//else nothing to do (see arrays setup).
			}
		}
	}*/

	// NORMAL
	if ( pVertexShape->getNormalBinding() == vgd::node::BIND_PER_VERTEX )
	{
		glDisableClientState( GL_NORMAL_ARRAY );
		if ( pGLEngine->isVertexBufferObjectEnabled() && rc->normal.isBound() )
		{
			rc->normal.unbind();
		}
	}

	// VERTEX
	glDisableClientState( GL_VERTEX_ARRAY );
	if ( pGLEngine->isVertexBufferObjectEnabled() && rc->vertex.isBound() )
	{
		rc->vertex.unbind();
	}
}



void VertexShape::renderArrays(	vgeGL::engine::Engine * pGLEngine, vgd::node::VertexShape *pVertexShape, const vgd::node::Primitive& primitive,
								vgeGL::rc::VertexShape * rc )
{
	// *** Step 2 : RENDERING ***
	const GLvoid *pArray = 0;

	rc->vao.bind();

	vgAssert( primitive.getType() != vgd::node::Primitive::NONE );
	const GLenum primitiveType = m_primTypeArray[ primitive.getType() ];

	if ( pGLEngine->isVertexBufferObjectEnabled() )
	{
		//rc->vertexIndex.bind(); // @todo removeme
	}
	else
	{
		pArray = reinterpret_cast< const GLvoid* >( &(*pVertexShape->getFVertexIndexRO())[primitive.getIndex()] );
	}

	const vgd::node::MultipleInstances * multipleInstances = pGLEngine->getGLState().getMultipleInstances();

	if ( multipleInstances )
	{
		// MATRIX
		using vgd::field::EditorRO;
		typedef vgd::node::MultipleInstances::FMatrixType FMatrixType;

		EditorRO< FMatrixType > matrix = multipleInstances->getMatrixRO();

		// Gets the geometrical matrix transformation.
		const vgm::MatrixR backup( pGLEngine->getGeometricalMatrix().getTop() );

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

			// RENDER
			glDrawElements( primitiveType, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
			//glDrawRangeElements( primitiveType, 0, vertex->size()-1, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
		}

		//
		glLoadMatrixf( reinterpret_cast<const float*>( backup.getValue() ) );

		//
		pGLEngine->getGLState().setMultipleInstances( 0 );
	}
	else
	{
		// RENDER
		//glDrawRangeElements( primitiveType, 0, vertex->size()-1, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
		glDrawElements( primitiveType, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
		// or glDrawElements( primitiveType, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
	}

	rc->vao.unbind();
}


// @todo buffer usage GL_STATIC_DRAW must be configurable
void VertexShape::updateTexCoord( vgd::node::VertexShape * vertexShape, const uint unit, const uint texCoordDim, vgeGL::rc::VertexShape * rc )
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



void VertexShape::configureTexCoord( vgeGL::engine::Engine * pGLEngine, vgd::node::VertexShape * vertexShape, const uint unit, const uint texCoordDim, vgeGL::rc::VertexShape * rc, const bool isVertexBufferObjectEnabled )
{
	if (	texCoordDim > 0 &&
			vertexShape->getTexCoordBinding( unit ) == vgd::node::BIND_PER_VERTEX )
	{
		if ( !pGLEngine->isGLSLEnabled() ) glClientActiveTexture( GL_TEXTURE0_ARB + unit );
		//glClientActiveTextureARB( GL_TEXTURE0_ARB + unit );

		const GLvoid *pArray = 0;
		if ( isVertexBufferObjectEnabled )
		{
			rc->texCoord[unit].bind();
		}
		else
		{
			if ( texCoordDim == 2 )
			{
				pArray = static_cast< const GLvoid* >( vertexShape->getFTexCoordRO< vgd::field::MFVec2f >( unit )->ptr() );
			}
			else if ( texCoordDim == 1 )
			{
				pArray = static_cast< const GLvoid* >( vertexShape->getFTexCoordRO< vgd::field::MFFloat >( unit )->ptr() );
			}
			else if ( texCoordDim == 3 )
			{
				pArray = static_cast< const GLvoid* >( vertexShape->getFTexCoordRO< vgd::field::MFVec3f >( unit )->ptr() );
			}
			else if ( texCoordDim == 4 )
			{
				pArray = static_cast< const GLvoid* >( vertexShape->getFTexCoordRO< vgd::field::MFVec4f >( unit )->ptr() );
			}
			else
			{
				// NOT SUPPORTED
				vgAssertN( false, "VertexShape(%s).texCoord%u with dimension equal to %u", vertexShape->getName().c_str(), unit, texCoordDim );
			}
		}
		if ( pGLEngine->isGLSLEnabled() )
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
	// else nothing to do
	
	else
	{
		if ( pGLEngine->isGLSLEnabled() )
		{
			glDisableVertexAttribArray( vgeGL::engine::TEXCOORD_INDEX + unit );
		}
		else
		{
			glClientActiveTexture( GL_TEXTURE0_ARB + unit );
			//glClientActiveTextureARB( GL_TEXTURE0_ARB + unit );
			glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		}
			
		/*if ( isVertexBufferObjectEnabled && rc->texCoord[unit].isBound() )
		{
			rc->texCoord[unit].unbind();
		}*/

	}
}



void VertexShape::drawBoundingBox( vgeGL::engine::Engine *, vgd::node::VertexShape *pVertexShape )
{
	drawBox3f( pVertexShape->getBoundingBox() );
}



void VertexShape::drawXfBoundingBox( vgeGL::engine::Engine *, vgd::node::VertexShape *pVertexShape )
{
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	drawBox3f( pVertexShape->getProjectXfBoundingBox() );

	glPopMatrix();
}


// move to handler/operations.hpp.cpp
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



/**
 * @todo Currently only draw normals on triangles and assert( pVertexShape->getNormalBinding() == vgd::node::BIND_PER_VERTEX );
 */
void VertexShape::drawNormals( vgd::node::VertexShape *pVertexShape, const float normalLength )
{
	vgd::field::EditorRO< vgd::field::MFVec3f >		vertex		= pVertexShape->getFVertexRO();
	vgd::field::EditorRO< vgd::field::MFVec3f >		normal		= pVertexShape->getFNormalRO();
	vgd::field::EditorRO< vgd::field::MFUInt32 >	vertexIndex	= pVertexShape->getFVertexIndexRO();

	vgd::field::EditorRO< vgd::field::MFPrimitive >	primitives( pVertexShape->getFPrimitiveRO() );
	
	if (	(pVertexShape->getNormalBinding() != vgd::node::BIND_PER_VERTEX) ||
			(normal->size() != vertex->size()) )
	{
		// do nothing
		return;
	}

	vgAssert( pVertexShape->getNormalBinding() == vgd::node::BIND_PER_VERTEX );
	vgAssert( normal->size() > 0 );
	vgAssert( normal->size() == vertex->size() );
	
	
	int32 i32IndexPrim=0;	
	for(	vgd::field::MFPrimitive::const_iterator	i	= primitives->begin(),
													ie	= primitives->end();
			i != ie;
			i++, i32IndexPrim++)
	{
		const vgd::node::Primitive& primitive(*i);
	
		// Start rendering the primitive.
		if ( primitive.getType() == vgd::node::Primitive::NONE ) //!= vgd::node::Primitive::TRIANGLES )&&( primitive.getType() != vgd::node::Primitive::QUADS ))
		{
			// Next primitive ?
			continue;
		}
		//assert( primitive.getType() == vgd::node::Primitive::TRIANGLES );
		//GLenum primitiveType = m_primTypeArray[ primitive.getType() ];

		glBegin( GL_LINES );

		const int32 i32Max = primitive.getIndex() + primitive.getNumIndices();

		for( int32 i32I = primitive.getIndex(); i32I<i32Max; i32I++ )
		{
			int32 i32VertexIndex;
			i32VertexIndex = (*vertexIndex)[i32I];

			vgm::Vec3f	normalSource;
			vgm::Vec3f	normalDestination;

			normalSource		= (*vertex)[i32VertexIndex];
			normalDestination	= normalSource + (*normal)[ i32VertexIndex ] * normalLength;

			glVertex3fv( normalSource.getValue() );
			glVertex3fv( normalDestination.getValue() );
		}

		glEnd();
		// Finish rendering the primitive.
	}
}



void VertexShape::drawTriangleOrientation( vgd::node::VertexShape *pVertexShape )
{
	vgd::field::EditorRO< vgd::field::MFVec3f >		vertex			= pVertexShape->getFVertexRO();
	//vgd::field::EditorRO< vgd::field::MFVec3f >	normal			= pVertexShape->getFNormalRO();
	vgd::field::EditorRO< vgd::field::MFUInt32 >	vertexIndex		= pVertexShape->getFVertexIndexRO();

	vgd::field::EditorRO< vgd::field::MFPrimitive >	primitives( pVertexShape->getFPrimitiveRO() );

	//assert( pVertexShape->getNormalBinding() == vgd::node::BIND_PER_VERTEX );
	//assert( normal->size() > 0 );
	
	int32 i32IndexPrim=0;	
	for(	vgd::field::MFPrimitive::const_iterator	i	= primitives->begin(),
													ie	= primitives->end();
		 i != ie;
		 i++, i32IndexPrim++)
	{
		const vgd::node::Primitive& primitive(*i);
	
		// Start rendering the primitive.
		if ( primitive.getType() != vgd::node::Primitive::TRIANGLES )
		{
			// Next primitive ?
			continue;
		}
		//assert( primitive.getType() == vgd::node::Primitive::TRIANGLES );
		//GLenum primitiveType = m_primTypeArray[ primitive.getType() ];
	
		const int32 i32Max = primitive.getIndex() + primitive.getNumIndices();
		
		for( int32 i32I = primitive.getIndex(); i32I<i32Max; i32I++ )
		{
			int32 i32VertexIndexA;
			i32VertexIndexA = (*vertexIndex)[i32I++];

			int32 i32VertexIndexB;
			i32VertexIndexB = (*vertexIndex)[i32I++];
			
			int32 i32VertexIndexC;
			i32VertexIndexC = (*vertexIndex)[i32I];
			
			vgm::Vec3f	vA, vB, vC, vTriangleCenter,
						vMiddle,				// center of [AB] or [BC] or [CA]
						vTmp1, vTmp2, vTmp3;
			
			vA = (*vertex)[i32VertexIndexA];
			vB = (*vertex)[i32VertexIndexB];
			vC = (*vertex)[i32VertexIndexC];
			
			vTriangleCenter = (vA + vB + vC ) / 3.f;
			
			const float		fFactorArrowLength	= 0.6f;

			// triangle center
			glPointSize( 3.f );

			glBegin( GL_POINTS );
			
			glColor3f( 1.f, 1.f, 1.f );

			glVertex3fv( vTriangleCenter.getValue() );
			
			glEnd();
			
			//
			glBegin( GL_LINES );

			// AB
			glColor3f( 1.f, 0.f, 0.f );
			
			vTmp1 = vB + (vTriangleCenter - vB ) * fFactorArrowLength;

			glVertex3fv( vB.getValue() );
			glVertex3fv( vTmp1.getValue() );

			// BC
			glColor3f( 0.f, 1.f, 0.f );
			
			vTmp1 = vC + (vTriangleCenter - vC ) * fFactorArrowLength;

			glVertex3fv( vC.getValue() );
			glVertex3fv( vTmp1.getValue() );
			
			// CA
			glColor3f( 0.f, 0.f, 1.f );
			
			vTmp1 = vA + (vTriangleCenter - vA ) * fFactorArrowLength;

			glVertex3fv( vA.getValue() );
			glVertex3fv( vTmp1.getValue() );

			//			
			glEnd();
		}
	}
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
