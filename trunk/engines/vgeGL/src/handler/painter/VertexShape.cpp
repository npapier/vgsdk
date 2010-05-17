// VGSDK - Copyright (C) 2004-2006, 2008, 2009, 2010, Nicolas Papier.
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
#include <vgd/node/Quad.hpp>
#include <vgd/node/MultipleInstances.hpp>
#include <vgd/node/Sphere.hpp>
#include <vgd/node/Texture.hpp>
#include <vgd/node/TriSet.hpp>
#include <vgd/node/VertexShape.hpp>

#include <vgDebug/convenience.hpp>
#include <vgDebug/StdStreamsToFiles.hpp>
#include <vgm/Box.hpp>

#include "vgeGL/engine/GLSLState.hpp"
#include "vgeGL/engine/FragmentShaderGenerator.hpp"
#include "vgeGL/engine/GeometryShaderGenerator.hpp"
#include "vgeGL/engine/ProgramGenerator.hpp"
#include "vgeGL/engine/VertexShaderGenerator.hpp"

#include "vgeGL/handler/painter/DrawStyle.hpp"

#include "vgeGL/rc/GLSLProgram.hpp"
#include "vgeGL/rc/TDisplayListHelper.hpp"



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

	targets.reserve( 5 );

	targets.push_back( vgd::node::Box::getClassIndexStatic() );
	targets.push_back( vgd::node::Quad::getClassIndexStatic() );
	targets.push_back( vgd::node::Sphere::getClassIndexStatic() );
	targets.push_back( vgd::node::TriSet::getClassIndexStatic() );
	targets.push_back( vgd::node::VertexShape::getClassIndexStatic() );

	return targets;
}



/**
 * @todo glPolygonMode( GL_FRONT_AND_BACK, *): is it always correct ? use GL_FRONT, GL_BACK ?
 */
void VertexShape::apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	assert( dynamic_cast< vgd::node::VertexShape* >(pNode) != 0 );
	vgd::node::VertexShape *pVertexShape = static_cast< vgd::node::VertexShape* >(pNode);

//	glPushAttrib( GL_ALL_ATTRIB_BITS );

	// GLSL STATE UPDATE
	using vgeGL::engine::GLSLState;
	GLSLState& glslState = pGLEngine->getGLSLState();

	// Updates GLSL state with vertex shape info
	glslState.setEnabled( GLSLState::COLOR4_BIND_PER_VERTEX, pVertexShape->getColor4Binding() == vgd::node::BIND_PER_VERTEX );

// @todo OPTME
	//setTexCoordDim for texUnitState of glslState => useful for pg->generate();
	//pGLEngine->getGLSLStateStack().push();
	if ( pGLEngine->isTextureMappingEnabled() )
	{
		vgd::node::VertexShape::ConstIteratorIndexSet i, iEnd;
		for(	boost::tie( i, iEnd ) = pVertexShape->getTexUnitsIterators();
				i != iEnd;
				++i )
		{
			const uint unit = *i;

			vgd::Shp< GLSLState::TexUnitState > texUnitState = glslState.getTexture( unit );

			if (	(pVertexShape->getTexCoordBinding( unit ) != vgd::node::BIND_OFF) && 
					texUnitState	)
			{
				const int32 dimTexCoord = pVertexShape->getTexCoordDim( unit );
				texUnitState->setTexCoordDim( static_cast< uint8 >(dimTexCoord) );
			}
			//else
			//{
				//texUnitState->setTexCoordDim( 0 );
				//vgLogDebug3(	"VertexShape(%s).texCoord%i is not empty, but there is no texture",
				//				pVertexShape->getName().c_str(), unit );
			//}
		}
	}

	// GLSL
	if ( pGLEngine->isGLSLEnabled() ) // pGLEngine->gethCurrentProgram()
	{
		//
		vgd::Shp< vgeGL::engine::ProgramGenerator > pg = pGLEngine->getGLSLProgramGenerator();

		using glo::GLSLProgram;
		GLSLProgram * program = 0;

		//
		if ( true /*program == 0 pg->isDirty() */) // @todo OPTME: don't regenerate always shaders
		{
			// GENERATION
			pg->generate( pGLEngine );

			/*if ( pGLEngine->isTextureMappingEnabled() )
			{
				vgd::node::VertexShape::ConstIteratorIndexSet i, iEnd;
				for(	boost::tie( i, iEnd ) = pVertexShape->getTexUnitsIterators();
						i != iEnd;
						++i )
				{
					const uint unit = *i;

					if ( pVertexShape->getTexCoordBinding( unit ) != vgd::node::BIND_OFF )
					{
						vgd::Shp< GLSLState::TexUnitState > texUnitState = glslState.getTexture( unit );
						if ( texUnitState )
						{
							texUnitState->setTexCoordDim( static_cast< uint8 >(0) );
						}
					}
				}
			}*/
			//pGLEngine->getGLSLStateStack().pop();

			// CACHE
			const std::string	fullCode	= pg->getCode();
			const std::string&	vs			= pg->getVertexShaderGenerator()->getCode();
			const std::string&	fs			= pg->getFragmentShaderGenerator()->getCode();

			program = pGLEngine->getGLSLManager().get< GLSLProgram >( fullCode );

			if ( program == 0 )
			{
#ifdef _DEBUG
				static bool firstTime = true;

				vgDebug::StdStreamsToFiles redirection(	"GLSL.cout.txt", "GLSL.cerr.txt", firstTime ? vgDebug::StdStreamsToFiles::TRUNCATE : vgDebug::StdStreamsToFiles::APPEND );

				if ( firstTime ) firstTime = false;

				std::cout << "Generates shaders\n" << std::endl;
				std::cout << "Vertex shader\n" << std::endl << vs << std::endl;
				std::cout << "Fragment shader\n" << std::endl << fs << std::endl;
				std::cout << "\n\n\n";
#endif

				// Not found in cache. Creates a new one
				program = new glo::GLSLProgram;
#ifdef _DEBUG
				vgLogDebug("Creates a new GLSL program.");
				vgLogDebug2("GLSL managed program count : %i", pGLEngine->getGLSLManager().getNum());
#endif
				pGLEngine->getGLSLManager().add( fullCode, program );

				// Compiles and links
				const bool compileVSRetVal = program->addShader( vs.c_str(),pg->getVertexShaderGenerator()->getShaderType(), false );
				const bool compileFSRetVal = program->addShader( fs.c_str(), pg->getFragmentShaderGenerator()->getShaderType(), false );
				const bool linkRetVal = program->link();

#ifdef _DEBUG
				if ( !compileVSRetVal )
				{
					vgLogDebug("VERTEX shader compilation fails");
				}
				else
				{
					vgLogDebug("VERTEX shader compilation succeeded");
				}

				if ( !compileFSRetVal )
				{
					vgLogDebug("FRAGMENT shader compilation fails !");
				}
				else
				{
					vgLogDebug("FRAGMENT shader compilation succeeded");
				}

				if ( !linkRetVal )
				{
					vgLogDebug("Program link fails !");
				}
				else
				{
					vgLogDebug("Program link succeeded");
				}
#endif
				//assert( compileVSRetVal );
				//assert( compileFSRetVal );
				//assert( linkRetVal );
			}
/*#ifdef _DEBUG
			else
			{
				vgLogDebug("Uses GLSL program found in cache.");
			}
#endif*/
		}

		pGLEngine->sethCurrentProgram( program );
// @todo OPTME
		if ( pGLEngine->getUniformState().getSize() > 0 )
		{
			pGLEngine->getUniformState().apply( pGLEngine );
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

	// Makes a backup of GLSL activation state
	using vgeGL::engine::Engine;
	// @todo not always
	vgd::Shp< Engine::GLSLActivationState > glslActivationState = pGLEngine->getGLSLActivationState();
	pGLEngine->sethCurrentProgram();

	::vgeGL::handler::painter::DrawStyle::paintVertexShapeNormals( pGLEngine, pVertexShape, this );

	// @todo not the good place ?
	// *** DRAWSTYLE.showOrientation
	const bool showOrientationValue = pGLEngine->getGLState().getShowOrientation();

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


	// @todo not the good place ?
	// *** DRAWSTYLE.boundingBox ***
	vgd::node::DrawStyle::BoundingBoxValueType	bbValue = pGLEngine->getGLState().getBoundingBox();

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
				assert( false && "Unknown DrawStyle.boundingBox value." );
		}
		
		///@todo FIXME OPTME	
		glPopAttrib();
	}

	if ( pGLEngine->isTextureMappingEnabled() )
	{
		vgd::node::VertexShape::ConstIteratorIndexSet i, iEnd;
		for(	boost::tie( i, iEnd ) = pVertexShape->getTexUnitsIterators();
				i != iEnd;
				++i )
		{
			const uint unit = *i;

			vgd::Shp< GLSLState::TexUnitState > texUnitState = glslState.getTexture( unit );
	
			if (	(pVertexShape->getTexCoordBinding( unit ) != vgd::node::BIND_OFF) &&
					texUnitState	)
			{
				texUnitState->setTexCoordDim( 0 );
			}
		}
	}
//	glPopAttrib();

	// Restores GLSL activation state
	pGLEngine->setGLSLActivationState( glslActivationState );

	// Validates node
	pNode->getDirtyFlag(pNode->getDFNode())->validate();
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
//glPushClientAttrib( GL_CLIENT_ALL_ATTRIB_BITS );
	const vgd::node::VertexShape::DeformableHintValueType deformableHint = vertexShape->getDeformableHint();

	/* ImmediateMode */
	//paint( pGLEngine, pVertexShape );

	/* ImmediateMode in DL */
	//paintDisplayList	( pGLEngine, pVertexShape ); 

	/* Vertex Array */
	/* Vertex Array in DL */
	if ( deformableHint == vgd::node::VertexShape::STATIC )
	{
		paint(engine, vertexShape, vgeGL::engine::VertexArrayMethod() );
// @todo Reenabled display list usage or uses VAO
//		paint(engine, vertexShape, vgeGL::engine::VertexArrayDisplayListMethod() ); @todo don't work on Radeon
	}
	else
	{
		assert( 	(deformableHint == vgd::node::VertexShape::DYNAMIC) ||
					(deformableHint == vgd::node::VertexShape::STREAM)	);

		paint(engine, vertexShape, vgeGL::engine::VertexArrayMethod() );
	}
	
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
 * Support for secondaryColor4			with BIND_OFF, BIND_PER_VERTEX.
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

	// EDGE FLAG
	if (	(pVertexShape->getEdgeFlagBinding() != vgd::node::BIND_OFF ) &&
			(pVertexShape->getEdgeFlagBinding() != vgd::node::BIND_PER_VERTEX ) )
	{
		assert( "Bindings other than BIND_OFF and BIN_PER_VERTEX are not supported for edgeflag." );
		return;
	}

	// TEX COORD
	assert(	(pVertexShape->getNumTexUnits() > 1 &&
			isGL_ARB_multitexture() && "MultiTexture not currently supported.") ||
			(pVertexShape->getNumTexUnits() <= 1) );

	for(	int32 i=0;
			i < pVertexShape->getNumTexUnits();
			++i )
	{
		if (	(pVertexShape->getTexCoordBinding( i ) != vgd::node::BIND_OFF ) &&
				(pVertexShape->getTexCoordBinding( i ) != vgd::node::BIND_PER_VERTEX ) )
		{
			assert( "Bindings other than BIND_OFF and BIN_PER_VERTEX are not supported for textures coordinates." );
			return;
		}
	}

	// SECONDARY COLOR4
	if (	(pVertexShape->getSecondaryColor4Binding() != vgd::node::BIND_OFF ) &&
			(pVertexShape->getSecondaryColor4Binding() != vgd::node::BIND_PER_VERTEX ) )
	{
		assert( "Bindings other than BIND_OFF and BIN_PER_VERTEX are not supported for secondaryColor4." );
		return;
	}

	// COLOR4
	if (	(pVertexShape->getColor4Binding() != vgd::node::BIND_OFF ) &&
			(pVertexShape->getColor4Binding() != vgd::node::BIND_PER_VERTEX ) )
	{
		assert( "Bindings other than BIND_OFF and BIN_PER_VERTEX are not supported for color4." );
		return;
	}
	
	// NORMAL
	if (	(pVertexShape->getNormalBinding() != vgd::node::BIND_OFF ) &&
			(pVertexShape->getNormalBinding() != vgd::node::BIND_PER_VERTEX ) )
	{
		assert( "Bindings other than BIND_OFF and BIN_PER_VERTEX are not supported for normal." );
		return;
	}

	// VERTEX-VERTEXINDEX-PRIMITIVE
	vgd::field::EditorRO< vgd::field::MFPrimitive >	primitives( pVertexShape->getFPrimitiveRO() );

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
	
	primitives.release();
}



void VertexShape::paint(	vgeGL::engine::Engine * pGLEngine, vgd::node::VertexShape *pVertexShape,
							const vgd::node::Primitive& primitive,
							const vgeGL::engine::VertexArrayMethod& /*method*/ )
{
	//
	using vgeGL::engine::GLSLState;
	GLSLState& glslState = pGLEngine->getGLSLState();

	//
	vgd::field::EditorRO< vgd::field::MFVec3f >		normal;
	vgd::field::EditorRO< vgd::field::MFVec4f >		color4;
	vgd::field::EditorRO< vgd::field::MFVec4f >		secondaryColor4;
	vgd::field::EditorRO< vgd::field::MFUInt8 >		edgeFlag;

	vgd::field::EditorRO< vgd::field::MFVec3f >		vertex;
	vgd::field::EditorRO< vgd::field::MFUInt32 >	vertexIndex;

	//
	const GLvoid	*pArray;

	//
	glo::GLSLProgram * program = pGLEngine->gethCurrentProgram();

	// *** Step 1 : Setup arrays. ***

	// EDGE FLAG
	if ( pVertexShape->getEdgeFlagBinding() == vgd::node::BIND_PER_VERTEX )
	{
		edgeFlag = pVertexShape->getFEdgeFlagRO();

		pArray = static_cast< const GLvoid* >( &((*edgeFlag)[0]) );

		glEdgeFlagPointer( 0, pArray );
		glEnableClientState( GL_EDGE_FLAG_ARRAY );
	}

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
	uint		i		= 0;
	const uint	iEnd	= pGLEngine->isTextureMappingEnabled() ? glslState.getMaxTexture() : 0;

	for( uint foundTexture = 0; i != iEnd; ++i )
	{
		const vgd::Shp< GLSLState::TexUnitState > current = glslState.getTexture( i );

		// Empty texture unit, so do nothing
		if ( current == 0 )	continue;

		const uint&					unit	= i;
		const std::string			strUnit = vgd::basic::toString( unit );

		const vgd::node::Texture *	textureNode	= current->getTextureNode();
		glo::Texture *				texture		= current->getTexture();
		const uint8					texCoordDim	= current->getTexCoordDim();
		const vgd::node::TexGen *	texGen		= current->getTexGenNode();

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
				assert( program->isInUse() );

				const vgd::node::Texture::UsageValueType usage = textureNode->getUsage();

				if ( usage == vgd::node::Texture::SHADOW )
				{
					if ( glslState.isShadowSamplerUsageEnabled() )
					{
						program->setUniform1i( "texMap2DShadow[" + glslState.getPrivate( unit ) + "]", unit );
					}
					else
					{
						program->setUniform1i( "texMap2D[" + strUnit + "]", unit );
					}
				}
				else if ( usage == vgd::node::Texture::IMAGE )
				{
					program->setUniform1i( "texMap2D[" + strUnit + "]", unit );
					configureTexCoord( pVertexShape, unit, pVertexShape->getTexCoordDim(unit) /* @todo OPTME */ );
				}
				else
				{
					assert( false );
				}
			}
			else
			{
				pGLEngine->activeTexture( unit );
				const uint texCoordDim = pVertexShape->getTexCoordDim(unit);
				if ( texCoordDim > 0 )
				{
					texture->enable();
				}
				configureTexCoord( pVertexShape, unit,  texCoordDim );
			}
		}

		//
		++foundTexture;
		if ( foundTexture == glslState.getNumTexture() )
		{
			break;
		}
	}


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
			vgd::Shp< GLSLState::TexUnitState > texUnitState = glslState.getTexture( unit );
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


	// SECONDARY COLOR4
	if ( pVertexShape->getSecondaryColor4Binding() == vgd::node::BIND_PER_VERTEX )
	{
		if ( isGL_EXT_secondary_color() )
		{
			glEnable( GL_COLOR_MATERIAL );

			secondaryColor4 = pVertexShape->getFSecondaryColor4RO();
			
			pArray = static_cast< const GLvoid* >( secondaryColor4->begin()->getValue() );
			
			glSecondaryColorPointerEXT( 4, GL_FLOAT, 0, pArray );
			
			glEnableClientState( GL_SECONDARY_COLOR_ARRAY );
		}
		else
		{
			vgLogWarning( "GL_EXT_secondary_color not supported" );
		}
	}

	// COLOR4
	if ( pVertexShape->getColor4Binding() == vgd::node::BIND_PER_VERTEX )
	{
		glEnable( GL_COLOR_MATERIAL );

		color4 = pVertexShape->getFColor4RO();

		// @todo Improves this test and do the same for all fields
		assert( color4->size() > 0 && "Color4Binding is BIND_PER_VERTEX, but no Color4 field has no data." );

		pArray = static_cast< const GLvoid* >( color4->begin()->getValue() );

		glColorPointer( 4, GL_FLOAT, 0, pArray );

		glEnableClientState( GL_COLOR_ARRAY );
	}

	// NORMAL
	if ( pVertexShape->getNormalBinding() == vgd::node::BIND_PER_VERTEX )
	{
		normal = pVertexShape->getFNormalRO();
		
		pArray = static_cast< const GLvoid* >( normal->begin()->getValue() );
		
		glNormalPointer( GL_FLOAT, 0, pArray );
		
		glEnableClientState( GL_NORMAL_ARRAY );
	}

	// VERTEX
	vertex = pVertexShape->getFVertexRO();

	pArray = static_cast< const GLvoid* >( vertex->begin()->getValue() );

	glVertexPointer( 3, GL_FLOAT, 0, pArray );
	glEnableClientState( GL_VERTEX_ARRAY );


	// *** Step 2 : RENDERING ***
	assert( primitive.getType() != vgd::node::Primitive::NONE );
	const GLenum primitiveType = m_primTypeArray[ primitive.getType() ];

	vertexIndex	= pVertexShape->getFVertexIndexRO();
	pArray		= reinterpret_cast< const GLvoid* >( &(*vertexIndex)[primitive.getIndex()] );

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
		}

		//
		glLoadMatrixf( reinterpret_cast<const float*>( backup.getValue() ) );

		//
		pGLEngine->getGLState().setMultipleInstances( 0 );
	}
	else
	{
		// RENDER
		//glDrawRangeElements( primitiveType, 0, vertexIndex->size()-1, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
		glDrawElements( primitiveType, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
		// or glDrawElements( primitiveType, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
	}

	// *** Step 3 : Disable arrays ***

	// EDGE FLAG
	if ( pVertexShape->getEdgeFlagBinding() == vgd::node::BIND_PER_VERTEX )
	{
		glDisableClientState( GL_EDGE_FLAG_ARRAY );
	}

	// TEX COORD
	// nothing to do

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
				vgd::Shp< GLSLState::TexUnitState > texUnitState = glslState.getTexture( unit );
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

	// SECONDARY COLOR4
	if ( pVertexShape->getSecondaryColor4Binding() == vgd::node::BIND_PER_VERTEX )
	{
		if ( isGL_EXT_secondary_color() )
		{		
			glDisableClientState( GL_SECONDARY_COLOR_ARRAY );
			
			glDisable( GL_COLOR_MATERIAL );
		}
	}	

	// COLOR4
	if ( pVertexShape->getColor4Binding() == vgd::node::BIND_PER_VERTEX )
	{
		glDisableClientState( GL_COLOR_ARRAY );
		
		glDisable( GL_COLOR_MATERIAL );
	}

	// NORMAL
	if ( pVertexShape->getNormalBinding() == vgd::node::BIND_PER_VERTEX )
	{
		glDisableClientState( GL_NORMAL_ARRAY );
	}

	// VERTEX
	glDisableClientState( GL_VERTEX_ARRAY );
}



void VertexShape::configureTexCoord( vgd::node::VertexShape * vertexShape, const uint unit, const uint texCoordDim )
{
	if (	texCoordDim > 0 &&
			vertexShape->getTexCoordBinding( unit ) == vgd::node::BIND_PER_VERTEX )
	{
		glClientActiveTexture( GL_TEXTURE0_ARB + unit );

		const GLvoid *pArray;
		switch ( texCoordDim )
		{
			case 2:
			{
				vgd::field::EditorRO< vgd::field::MFVec2f >	texCoord;
				texCoord = vertexShape->getFTexCoordRO< vgd::field::MFVec2f >( unit );
				pArray = static_cast< const GLvoid* >( texCoord->begin()->getValue() );
				glTexCoordPointer( 2, GL_FLOAT, 0, pArray );
				glEnableClientState( GL_TEXTURE_COORD_ARRAY );
				break;
			}

			case 3:
			{
				vgd::field::EditorRO< vgd::field::MFVec3f >	texCoord;
				texCoord = vertexShape->getFTexCoordRO< vgd::field::MFVec3f >( unit );
				pArray = static_cast< const GLvoid* >( texCoord->begin()->getValue() );
				glTexCoordPointer( 3, GL_FLOAT, 0, pArray );
				glEnableClientState( GL_TEXTURE_COORD_ARRAY );
				break;
			}

			case 1:
			{
				vgd::field::EditorRO< vgd::field::MFFloat >	texCoord;
				texCoord = vertexShape->getFTexCoordRO< vgd::field::MFFloat >( unit );
				pArray = static_cast< const GLvoid* >( &(*texCoord)[0] );
				glTexCoordPointer( 1, GL_FLOAT, 0, pArray );
				glEnableClientState( GL_TEXTURE_COORD_ARRAY );
				break;
			}

			case 4:
			{
				vgd::field::EditorRO< vgd::field::MFVec4f >	texCoord;
				texCoord = vertexShape->getFTexCoordRO< vgd::field::MFVec4f >( unit );
				pArray = static_cast< const GLvoid* >( texCoord->begin()->getValue() );
				glTexCoordPointer( 4, GL_FLOAT, 0, pArray );
				glEnableClientState( GL_TEXTURE_COORD_ARRAY );
				break;
			}

			default:
				// NOT SUPPORTED
				vgLogDebug4("VertexShape(%s).texCoord%u with dimension equal to %u", vertexShape->getName().c_str(), unit, texCoordDim );
				assert( false && "Unexpected dimension for texCoord." );
		} // switch
	}
	else
	{
		glClientActiveTexture( GL_TEXTURE0_ARB + unit );
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	}
}



void VertexShape::paint(	vgeGL::engine::Engine *engine, vgd::node::VertexShape *vertexShape,
							const vgeGL::engine::VertexArrayDisplayListMethod& /*method*/ )
{
	// USE DISPLAY LIST
	vgeGL::rc::applyUsingDisplayList< vgd::node::VertexShape, VertexShape, vgeGL::engine::VertexArrayMethod >( 
		engine, vertexShape, this );
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

	assert( pVertexShape->getNormalBinding() == vgd::node::BIND_PER_VERTEX );
	assert( normal->size() > 0 );
	assert( normal->size() == vertex->size() );
	
	
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
