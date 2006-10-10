// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/VertexShape.hpp"

#include <glo/GLSLShader.hpp>
#include <glo/Texture.hpp>
// @todo Move Box stuff to Box handler (FIXME)
#include <vgd/node/Box.hpp>
// @todo Move DrawStyle stuff to drawStyle handler (FIXME)
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/Quad.hpp>
#include <vgd/node/Sphere.hpp>
#include <vgd/node/Texture.hpp>
#include <vgd/node/TriSet.hpp>
#include <vgd/node/VertexShape.hpp>
#include <vgm/Box.hpp>

#include "vgeGL/handler/painter/DrawStyle.hpp"
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

	return ( targets );
}



/**
 * @todo glPolygonMode( GL_FRONT_AND_BACK, *): is it always correct ? use GL_FRONT, GL_BACK ?
 */
void VertexShape::apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	assert( dynamic_cast< vgd::node::VertexShape* >(pNode) != 0 );
	vgd::node::VertexShape *pCastedNode = static_cast< vgd::node::VertexShape* >(pNode);

	// Render the VertexShape
	::vgeGL::handler::painter::DrawStyle::paintVertexShapeWithShapeProperty( pGLEngine, pCastedNode, this );
	::vgeGL::handler::painter::DrawStyle::paintVertexShapeNormals( pGLEngine, pCastedNode, this );	

//	// pre
//	GLboolean bLightingState;
//	glGetBooleanv( GL_LIGHTING, &bLightingState );
//
//	glDisable( GL_LIGHTING );

	// FIXME not the good place ?
	// *** DRAWSTYLE.showOrientation
	//bool	bDefined;
	bool	showOrientationValue;

	bool	bDefined = pGLEngine->getStateStackTop< 
						vgd::node::DrawStyle, 
						vgd::node::DrawStyle::ShowOrientationParameterType,
						vgd::node::DrawStyle::ShowOrientationValueType >(	vgd::node::DrawStyle::getFShowOrientation(),
																			vgd::node::DrawStyle::SHOW_ORIENTATION,
																			showOrientationValue );
	assert( bDefined );
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
		drawTriangleOrientation( pCastedNode );

		//glDisable(GL_POLYGON_OFFSET_FILL);
		///@todo FIXME OPTME	
		glPopAttrib();
	}


	// FIXME not the good place ?
	// *** DRAWSTYLE.boundingBox ***
	//bool										bDefined;
	vgd::node::DrawStyle::BoundingBoxValueType	bbValue;

	bDefined = pGLEngine->getStateStackTop< 
						vgd::node::DrawStyle, 
						vgd::node::DrawStyle::BoundingBoxParameterType,
						vgd::node::DrawStyle::BoundingBoxValueType >(	vgd::node::DrawStyle::getFBoundingBox(),
																		vgd::node::DrawStyle::BOUNDING_BOX,
																		bbValue );
	assert( bDefined );

	if ( bbValue != vgd::node::DrawStyle::NONE )
	{
		// FIXME optimize me
		glPushAttrib( GL_ALL_ATTRIB_BITS );
		
		glo::GLSLShader::useFixedPaths();

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
				drawBoundingBox( pGLEngine, pCastedNode );
				break;
	
			case vgd::node::DrawStyle::AA_OBJECT_SPACE:
				glColor3f( 1.f, 0.f, 0.f );
				drawXfBoundingBox( pGLEngine, pCastedNode );
				break;

			case vgd::node::DrawStyle::OBJECT_AND_AA_OBJECT_SPACE:
				glColor3f( 0.f, 0.f, 1.f );			
				drawBoundingBox( pGLEngine, pCastedNode );
				glColor3f( 1.f, 0.f, 0.f );				
				drawXfBoundingBox( pGLEngine, pCastedNode );
				break;

			default:
				assert( false && "Unknown DrawStyle.boundingBox value." );
		}
		
		///@todo FIXME OPTME	
		glPopAttrib();
	}
	
//	// post
//	if ( bLightingState == GL_TRUE )
//	{
//		glEnable( GL_LIGHTING );
//	}	

	// Validate node
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
	const vgd::node::VertexShape::DeformableHintValueType deformableHint = vertexShape->getDeformableHint();

	/* ImmediateMode */
	//paint( pGLEngine, pCastedNode );

	/* ImmediateMode in DL */
	//paintDisplayList	( pGLEngine, pCastedNode ); 

	/* Vertex Array */
	/* Vertex Array in DL */
	if ( deformableHint == vgd::node::VertexShape::STATIC )
	{
		paint(engine, vertexShape, vgeGL::engine::VertexArrayDisplayListMethod() );
	}
	else
	{
		assert( 	(deformableHint == vgd::node::VertexShape::DYNAMIC) ||
					(deformableHint == vgd::node::VertexShape::STREAM)	);

		paint(engine, vertexShape, vgeGL::engine::VertexArrayMethod() );
	}
	
	/* Vertex Arrays in VBO */
	//paintVBO				( pGLEngine, pCastedNode );
	//paintVBOVertexArray	( pGLEngine, pCastedNode );
}



/**
 * Support for vertex.
 * 
 * Support for normal					with BIND_OFF, BIND_PER_VERTEX.
 * Support for color4					with BIND_OFF, BIND_PER_VERTEX.
 * Support for secondaryColor4			with BIND_OFF, BIND_PER_VERTEX.
 * Support for texCoord					with BIND_OFF, BIND_PER_VERTEX.
 * Support for edgeFlag					with BIND_OFF, BIND_PER_VERTEX.
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
			gleGetCurrent()->isGL_ARB_multitexture && "MultiTexture not currently supported.") ||
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

	int32 i32IndexPrim = 0;
	for(	vgd::field::MFPrimitive::const_iterator	i	=	primitives->begin(),
															ie	= primitives->end();
			i != ie;
			++i, ++i32IndexPrim)
	{
		const vgd::node::Primitive& primitive(*i);

		// *** BIND_PER_PRIMITIVE ***
		// Nothing to do, because not supported.

		// render a primitive
		paint( pGLEngine, pVertexShape, primitive, method );
	}
	
	primitives.release();
}



void VertexShape::paint(	vgeGL::engine::Engine *, vgd::node::VertexShape *pVertexShape,
							const vgd::node::Primitive& primitive,
							const vgeGL::engine::VertexArrayMethod& /*method*/ )
{
	vgd::field::EditorRO< vgd::field::MFVec3f >		normal;
	vgd::field::EditorRO< vgd::field::MFVec4f >		color4;
	vgd::field::EditorRO< vgd::field::MFVec4f >		secondaryColor4;
	vgd::field::EditorRO< vgd::field::MFUInt8 >		edgeFlag;

	vgd::field::EditorRO< vgd::field::MFVec3f >		vertex;
	vgd::field::EditorRO< vgd::field::MFUInt32 >	vertexIndex;

	// extensions.
	gle::OpenGLExtensionsGen *glext = gleGetCurrent();

	//
	const GLvoid	*pArray;



	// *** Step 1 : Setup arrays. ***

	// EDGE FLAG
	if ( pVertexShape->getEdgeFlagBinding() == vgd::node::BIND_PER_VERTEX )
	{
		edgeFlag = pVertexShape->getFEdgeFlagRO();

		pArray = static_cast< const GLvoid* >( &((*edgeFlag)[0]) );

		glEdgeFlagPointer( 0, pArray );
		glEnableClientState( GL_EDGE_FLAG_ARRAY );
	}

	// TEX COORD
	const int32 numTexUnits = pVertexShape->getNumTexUnits();

	if ( numTexUnits >= 1 )
	{
		for(	int32 unit = numTexUnits-1;
				unit >= 0;
				--unit )
		{
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

			if ( pVertexShape->getTexCoordBinding( unit ) == vgd::node::BIND_PER_VERTEX )
			{
/*				// TODO: could only search vgd::node::Texture2D, not abstract node....
				// gets the texture node and ressource															FIXME : not always correct.
				vgd::node::Texture *pTexture = pGLEngine->template getStateStackTop<vgd::node::Texture>( unit );
				assert( pTexture != 0 && "Internal error." );
				glo::Texture *pTextureGLO = pGLEngine->getGLManager().template get< glo::Texture >( pTexture );
				assert( pTextureGLO != 0 && "Internal error." );

				glo::Texture::active( unit );
				pTextureGLO->enable();*/

				//
				gleGetCurrent()->glClientActiveTexture( GL_TEXTURE0_ARB + unit );				
				int32 dimTexCoord = pVertexShape->getTexCoordDim( unit );
				
				switch ( dimTexCoord )
				{
					case 2:
					{
						vgd::field::EditorRO< vgd::field::MFVec2f >	texCoord;
						texCoord	= pVertexShape->getFTexCoordRO< vgd::field::MFVec2f >( unit );
						pArray = static_cast< const GLvoid* >( texCoord->begin()->getValue() );
						glTexCoordPointer( 2, GL_FLOAT, 0, pArray );
						glEnableClientState( GL_TEXTURE_COORD_ARRAY );
						break;
					}
					
					case 3:
					{
						vgd::field::EditorRO< vgd::field::MFVec3f >	texCoord;
						texCoord	= pVertexShape->getFTexCoordRO< vgd::field::MFVec3f >( unit );
						pArray = static_cast< const GLvoid* >( texCoord->begin()->getValue() );
						glTexCoordPointer( 3, GL_FLOAT, 0, pArray );
						glEnableClientState( GL_TEXTURE_COORD_ARRAY );
						break;
					}
	
					case 1:
					{
						vgd::field::EditorRO< vgd::field::MFFloat >	texCoord;
						texCoord	= pVertexShape->getFTexCoordRO< vgd::field::MFFloat >( unit );
						pArray = static_cast< const GLvoid* >( &(*texCoord)[0] );
						glTexCoordPointer( 1, GL_FLOAT, 0, pArray );
						glEnableClientState( GL_TEXTURE_COORD_ARRAY );
						break;
					}
	
					case 4:
					{
						vgd::field::EditorRO< vgd::field::MFVec4f >	texCoord;
						texCoord	= pVertexShape->getFTexCoordRO< vgd::field::MFVec4f >( unit );
						pArray = static_cast< const GLvoid* >( texCoord->begin()->getValue() );
						glTexCoordPointer( 4, GL_FLOAT, 0, pArray );
						glEnableClientState( GL_TEXTURE_COORD_ARRAY );
						break;
					}
					
					default:
						assert( false && "Unexpected dimension for texCoord." );
				} // switch
			} // BIND_PER_VERTEX
		} // for(	int32 unit = numTexUnits-1;
	}
	// else nothing to do.



	// SECONDARY COLOR4
	if ( pVertexShape->getSecondaryColor4Binding() == vgd::node::BIND_PER_VERTEX )
	{
		if ( glext->isGL_EXT_secondary_color )
		{
			glEnable( GL_COLOR_MATERIAL );

			secondaryColor4 = pVertexShape->getFSecondaryColor4RO();
			
			pArray = static_cast< const GLvoid* >( secondaryColor4->begin()->getValue() );
			
			glext->glSecondaryColorPointerEXT( 4, GL_FLOAT, 0, pArray );
			
			glEnableClientState( GL_SECONDARY_COLOR_ARRAY );
		}
		else
		{
			vgDebug::get().logError( "GL_EXT_secondary_color not supported" );
		}
	}

	// COLOR4
	if ( pVertexShape->getColor4Binding() == vgd::node::BIND_PER_VERTEX )
	{
		glEnable( GL_COLOR_MATERIAL );

		color4 = pVertexShape->getFColor4RO();
		
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
	GLenum primitiveType = m_primTypeArray[ primitive.getType() ];

	vertexIndex	= pVertexShape->getFVertexIndexRO();
	pArray		= reinterpret_cast< const GLvoid* >( &(*vertexIndex)[primitive.getIndex()] );
	
	gleGetCurrent()->glDrawRangeElements( primitiveType, 0, vertexIndex->size()-1, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );
	// or glDrawElements( primitiveType, primitive.getNumIndices(), GL_UNSIGNED_INT, pArray );



	// *** Step 3 : Disable arrays ***

	// EDGE FLAG
	if ( pVertexShape->getEdgeFlagBinding() == vgd::node::BIND_PER_VERTEX )
	{
		glDisableClientState( GL_EDGE_FLAG_ARRAY );
	}

	// TEX COORD
	if ( pVertexShape->getNumTexUnits() == 1 )
	{
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	}
	else
	{
		for(	int32 i=pVertexShape->getNumTexUnits()-1;
				i>=0;
				--i )
		{	
			if ( pVertexShape->getTexCoordBinding( i ) == vgd::node::BIND_PER_VERTEX )
			{
				gleGetCurrent()->glClientActiveTexture( GL_TEXTURE0_ARB + i );

				glDisableClientState( GL_TEXTURE_COORD_ARRAY );
			}
		}
	}
	
	// SECONDARY COLOR4
	if ( pVertexShape->getSecondaryColor4Binding() == vgd::node::BIND_PER_VERTEX )
	{
		if ( glext->isGL_EXT_secondary_color )
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



void VertexShape::paint(	vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pVertexShape,
							const vgeGL::engine::VertexArrayDisplayListMethod& /*method*/ )
{
	// USE DISPLAY LIST
	vgeGL::rc::applyUsingDisplayList< vgd::node::VertexShape, VertexShape, vgeGL::engine::VertexArrayMethod >( 
		pGLEngine, pVertexShape, this );
}



void VertexShape::drawBoundingBox( vgeGL::engine::Engine *, vgd::node::VertexShape *pCastedNode )
{
	drawBox3f( pCastedNode->getBoundingBox() );
}



void VertexShape::drawXfBoundingBox( vgeGL::engine::Engine *, vgd::node::VertexShape *pCastedNode )
{
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
	
	drawBox3f( pCastedNode->getProjectXfBoundingBox() );	
	
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
 * @todo Currently only draw normals on triangles and assert( pCastedNode->getNormalBinding() == vgd::node::BIND_PER_VERTEX );
 */
void VertexShape::drawNormals( vgd::node::VertexShape *pCastedNode, const float normalLength )
{
	vgd::field::EditorRO< vgd::field::MFVec3f >		vertex		= pCastedNode->getFVertexRO();
	vgd::field::EditorRO< vgd::field::MFVec3f >		normal		= pCastedNode->getFNormalRO();
	vgd::field::EditorRO< vgd::field::MFUInt32 >	vertexIndex	= pCastedNode->getFVertexIndexRO();

	vgd::field::EditorRO< vgd::field::MFPrimitive >	primitives( pCastedNode->getFPrimitiveRO() );
	
	if (	(pCastedNode->getNormalBinding() != vgd::node::BIND_PER_VERTEX) ||
			(normal->size() != vertex->size()) )
	{
		// do nothing
		return;
	}

	assert( pCastedNode->getNormalBinding() == vgd::node::BIND_PER_VERTEX );
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
		if ( primitive.getType() != vgd::node::Primitive::TRIANGLES )
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



void VertexShape::drawTriangleOrientation( vgd::node::VertexShape *pCastedNode )
{
	vgd::field::EditorRO< vgd::field::MFVec3f >		vertex			= pCastedNode->getFVertexRO();
	//vgd::field::EditorRO< vgd::field::MFVec3f >	normal			= pCastedNode->getFNormalRO();
	vgd::field::EditorRO< vgd::field::MFUInt32 >	vertexIndex		= pCastedNode->getFVertexIndexRO();

	vgd::field::EditorRO< vgd::field::MFPrimitive >	primitives( pCastedNode->getFPrimitiveRO() );

	//assert( pCastedNode->getNormalBinding() == vgd::node::BIND_PER_VERTEX );
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
