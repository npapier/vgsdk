// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/VertexShape.hpp"

#include <vgd/node/Box.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/Quad.hpp>
#include <vgd/node/TriSet.hpp>
#include <vgd/node/VertexShape.hpp>

#include "vgeGL/rc/TDisplayListHelper.hpp"
#include "vgeGL/rc/VertexBufferObject.hpp"



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
	
	targets.reserve( 4 );

	targets.push_back( vgd::node::Box::getClassIndexStatic() );
	targets.push_back( vgd::node::Quad::getClassIndexStatic() );
	targets.push_back( vgd::node::TriSet::getClassIndexStatic() );	
	targets.push_back( vgd::node::VertexShape::getClassIndexStatic() );

	return ( targets );
}



/**
 * @todo glPolygonMode( GL_FRONT_AND_BACK, *): is it always correct ? use GL_FRONT, GL_BACK ?
 * @bug 
 */
void VertexShape::apply ( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	assert( dynamic_cast< vgd::node::VertexShape* >(pNode) != 0 );
	vgd::node::VertexShape *pCastedNode = static_cast< vgd::node::VertexShape* >(pNode);
		
	// Select
	// FIXME see Settings.

	/* ImmediateMode */
	//paint( pGLEngine, pCastedNode );

	/* ImmediateMode in DL */
	//paintDisplayList	( pGLEngine, pCastedNode ); 

	/* Vertex Array */
	/* Vertex Array in DL */
	//vgeGL::engine::VertexArrayMethod method;
	vgeGL::engine::VertexArrayDisplayListMethod method;

	/* Vertex Arrays in VBO */
	//paintVBO						( pGLEngine, pCastedNode );
	//paintVBOVertexArray	( pGLEngine, pCastedNode );

	// Render the VertexShape.
	bool														bDefined;

	// FIXME not the good place ?
	// *** DRAWSTYLE.shape ***
	vgd::node::DrawStyle::ShapeValueType			shapeValue;

	bDefined = pGLEngine->getStateStackTop< 
						vgd::node::DrawStyle,
						vgd::node::DrawStyle::ShapeParameterType,
						vgd::node::DrawStyle::ShapeValueType >(
																				vgd::node::DrawStyle::getFShape(),
																				vgd::node::DrawStyle::SHAPE,
																				shapeValue );
	assert( bDefined );
	
	float vMat[4];	
	
	switch ( shapeValue )
	{
		case vgd::node::DrawStyle::NONE:
			break;

		case vgd::node::DrawStyle::POINT:
			// FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );

			glPointSize( 4.0 );
			glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );

			paint( pGLEngine, pCastedNode, method );

			// FIXME OPTME
			glPopAttrib();
			break;

		case vgd::node::DrawStyle::FLAT:
			// FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glShadeModel(GL_FLAT);

			paint( pGLEngine, pCastedNode, method );
			
			// FIXME OPTME
			glPopAttrib();			
			break;
			
		// see below for case SMOOTH:
					
		case vgd::node::DrawStyle::WIREFRAME:
		{	// FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );
		
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			
			// ??? FIXME
//			GLfloat fogColor[] = { 0.1f, 0.1f, 0.1f, 1.0 };
//			
//			glEnable( GL_FOG );
//			glFogi( GL_FOG_MODE, GL_LINEAR );
//			glFogfv( GL_FOG_COLOR, fogColor );
//			glFogf( GL_FOG_DENSITY, 1.0f );
//			glHint( GL_FOG_HINT, GL_DONT_CARE );
//			glFogf(GL_FOG_START, 50.0f);
//			glFogf(GL_FOG_END, 5000.0f);
			
			paint( pGLEngine, pCastedNode, method );
			
			// FIXME OPTME
			glPopAttrib();
		}
			break;
					
		case vgd::node::DrawStyle::HIDDEN_LINE:
			// FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );
	
			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			paint( pGLEngine, pCastedNode, method );			

			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glEnable( GL_POLYGON_OFFSET_FILL );
			glPolygonOffset( 1.0f, 1.0f );

			glGetFloatv( GL_COLOR_CLEAR_VALUE, vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,		vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,		vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS,	vMat );

			paint( pGLEngine, pCastedNode, method );			
			
			glDisable(GL_POLYGON_OFFSET_FILL);
			
			// FIXME OPTME
			glPopAttrib();
			break;

		case vgd::node::DrawStyle::FLAT_HIDDEN_LINE:
		{
			// FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );

			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

			glPushAttrib( GL_ALL_ATTRIB_BITS );
			glGetFloatv( GL_COLOR_CLEAR_VALUE, vMat );			
			glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,		vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,		vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS,	vMat );
			
			paint( pGLEngine, pCastedNode, method );
			
			glPopAttrib();
			
			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glShadeModel( GL_FLAT );
			
			glEnable( GL_POLYGON_OFFSET_FILL );
			glPolygonOffset( 1.0, 1.0 );

			paint( pGLEngine, pCastedNode, method );
			
			glDisable(GL_POLYGON_OFFSET_FILL);

			// FIXME OPTME
			glPopAttrib();			
			break;
		}

		case vgd::node::DrawStyle::SMOOTH_HIDDEN_LINE:
		{
			// FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );

			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

			glPushAttrib( GL_ALL_ATTRIB_BITS );
			glGetFloatv( GL_COLOR_CLEAR_VALUE, vMat );			
			glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,		vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,		vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS,	vMat );
			
			paint( pGLEngine, pCastedNode, method );
			
			glPopAttrib();
			
			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glShadeModel( GL_SMOOTH );
			
			glEnable( GL_POLYGON_OFFSET_FILL );
			glPolygonOffset( 1.0, 1.0 );

			paint( pGLEngine, pCastedNode, method );
			
			glDisable(GL_POLYGON_OFFSET_FILL);

			// FIXME OPTME
			glPopAttrib();			
			break;
		}
					
		case vgd::node::DrawStyle::NEIGHBOUR: // FIXME
		case vgd::node::DrawStyle::SMOOTH:
			// FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );
			
//			GLint polygonMode;
//???		glGetIntegerv( GL_POLYGON_MODE, &polygonMode ???);

//			GLint shadeModel;
//			glGetIntegerv( GL_SHADE_MODEL, &shadeModel );

			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glShadeModel( GL_SMOOTH );

			paint( pGLEngine, pCastedNode, method );
			
			//glShadeModel( shadeModel );

			// FIXME OPTME
			glPopAttrib();			
			break;

		default:
			assert( false && "Unknown DrawStyle.shape value." );
	}


//	// pre
//	GLboolean bLightingState;
//	glGetBooleanv( GL_LIGHTING, &bLightingState );
//
//	glDisable( GL_LIGHTING );

	// FIXME not the good place ?
	// *** DRAWSTYLE.normalLength ***
	//bool														bDefined;
	vgd::node::DrawStyle::NormalLengthValueType	value;

	bDefined = pGLEngine->getStateStackTop< 
						vgd::node::DrawStyle, 
						vgd::node::DrawStyle::NormalLengthParameterType,
						vgd::node::DrawStyle::NormalLengthValueType >(
																								vgd::node::DrawStyle::getFNormalLength(),
																								vgd::node::DrawStyle::NORMAL_LENGTH,
																								value );
	assert( bDefined );
	if ( value != 0.f )
	{
		// FIXME optimize me
		glPushAttrib( GL_ALL_ATTRIB_BITS );
		
		glDisable( GL_LIGHTING );
		glColor3f( 1.f, 1.f, 1.f );
		// END FIXME

		drawNormals( pCastedNode, value );
	
		// FIXME OPTME	
		glPopAttrib();
	}


	// FIXME not the good place ?
	// *** DRAWSTYLE.showOrientation
	//bool														bDefined;
	bool showOrientationValue;

	bDefined = pGLEngine->getStateStackTop< 
						vgd::node::DrawStyle, 
						vgd::node::DrawStyle::ShowOrientationParameterType,
						vgd::node::DrawStyle::ShowOrientationValueType >(
																								vgd::node::DrawStyle::getFShowOrientation(),
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
		// FIXME OPTME	
		glPopAttrib();
	}


	// FIXME not the good place ?
	// *** DRAWSTYLE.boundingBox ***
	//bool														bDefined;
	vgd::node::DrawStyle::BoundingBoxValueType	bbValue;

	bDefined = pGLEngine->getStateStackTop< 
						vgd::node::DrawStyle, 
						vgd::node::DrawStyle::BoundingBoxParameterType,
						vgd::node::DrawStyle::BoundingBoxValueType >(
																								vgd::node::DrawStyle::getFBoundingBox(),
																								vgd::node::DrawStyle::BOUNDING_BOX,
																								bbValue );
	assert( bDefined );

	if ( bDefined )
	{
		// FIXME optimize me
		glPushAttrib( GL_ALL_ATTRIB_BITS );
		glDisable( GL_LIGHTING );
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
		
		// FIXME OPTME	
		glPopAttrib();
	}
	
//	// post
//	if ( bLightingState == GL_TRUE )
//	{
//		glEnable( GL_LIGHTING );
//	}	
}



void VertexShape::unapply ( vge::engine::Engine* engine, vgd::node::Node* pNode )
{
}



void VertexShape::setToDefaults()
{
}






/**
 * @bug Only support normal, vertex, vertexindex, normalindex and primitive(and theirs bindings).
 * @todo support all VertexShape fields.
 * 
 * @todo Support of multiple display list.
 *
 */
//void VertexShape::paint( vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pVertexShape )
//{
//	// *** BIND_OVERALL ***
//
//	// TEX COORDINATES
//	/*if ( getTexCoordinateBinding() == BIND_OVERALL )
//	{
//		assert( getShpTexCoordinates()->getNum() > 0 );
//
//		glTexCoord2fv( getShpTexCoordinates()->getValue().getVec() );
//	}*/
//
//	// normal
//	/*if ( pVertexShape->getNormalBinding() == vgd::node::BIND_OVERALL )
//	{
//		assert( pVertexShape->getFNormalRO()->size() > 0 );
//		
//		glNormal3fv(  pVertexShape->getFNormalRO()->front().getValue() );
//	}*/
//
//	// color
//	/* FIXME if ( pVertexShape->getColorBinding() == BIND_OVERALL )
//	{
//		assert( getShpColors()->getNum() > 0 );
//
//		glColor3fv( getShpColors()->getValue().getVec() );
//	}*/
//
//	// primitive
//	vgd::field::EditorRO< vgd::field::MFPrimitive >	primitives( pVertexShape->getFPrimitiveRO() );
//
//	int32 i32IndexPrim=0;
//	for(	vgd::field::MFPrimitive::const_iterator	i	= primitives->begin(),
//																	ie	= primitives->end();
//		 i != ie;
//		 i++, i32IndexPrim++)
//	{
//		const vgd::node::Primitive& primitive(*i);
//
//		// *** BIND_PER_PRIMITIVE ***
//		
//		/* FIXME // TEX COORDINATES
//		if ( getTexCoordinateBinding() == BIND_PER_PRIMITIVE )
//		{
//			assert( getShpTexCoordinates()->getNum() > 0 );
//
//			if ( getShpTexCoordinateIndices()->getNum() > 0 )
//			{
//				// tex coordinate index table not empty.
//				int32 i32Index = getShpTexCoordinateIndices()->get1Value( i32IndexPrim );
//				
//				glTexCoord2fv( getShpTexCoordinates()->get1Value( i32Index ).getVec() );
//			}
//			else
//			{
//				// tex coordinate index table empty, use i32IndexPrim instead.
//				glTexCoord2fv( getShpTexCoordinates()->get1Value( i32IndexPrim ).getVec() );
//			}
//		}*/
//
//		// normal
//		/*if ( pVertexShape->getNormalBinding() == vgd::node::BIND_PER_PRIMITIVE )
//		{
//			assert( pVertexShape->getFNormalRO()->size() > 0 );
//
//			if ( pVertexShape->getFNormalIndexRO()->size() > 0 )
//			{
//				// normal index table not empty.
//				int32 normalIndex = pVertexShape->getFNormalIndexRO()->operator[]( i32IndexPrim );
//				
//				glNormal3fv( pVertexShape->getFNormalRO()->operator[]( normalIndex ).getValue() );
//			}
//			else
//			{
//				// normal index table empty, use i32IndexPrim instead.
//				glNormal3fv( pVertexShape->getFNormalRO()->operator[]( i32IndexPrim ).getValue() );
//			}
//		}*/
//
//		/* FIXME // color
//		if ( getColorBinding() == BIND_PER_PRIMITIVE )
//		{
//			assert( getShpColors()->getNum() > 0 );
//
//			if ( getShpColorIndices()->getNum() > 0 )
//			{
//				// color index table not empty.
//				int32 i32ColorIndex = getShpColorIndices()->get1Value( i32IndexPrim );
//				
//				glColor3fv( getShpColors()->get1Value( i32ColorIndex ).getVec() );
//			}
//			else
//			{
//				// color index table empty, use i32IndexPrim instead.
//				glColor3fv( getShpColors()->get1Value( i32IndexPrim ).getVec() );
//			}
//		}*/
//
//		// render a primitive
//		paint( pGLEngine, pVertexShape, primitive );
//	}
//}
//
//
//
//void VertexShape::paint(	vgeGL::engine::Engine *engine, vgd::node::VertexShape *pVertexShape,
//											const vgd::node::Primitive& primitive )
//{
//	vgd::field::EditorRO< vgd::field::MFVec3f > vertex			= pVertexShape->getFVertexRO();
//	vgd::field::EditorRO< vgd::field::MFVec3f > normal			= pVertexShape->getFNormalRO();
//
//	vgd::field::EditorRO< vgd::field::MFUInt32 > vertexIndex	= pVertexShape->getFVertexIndexRO();
//	//vgd::field::EditorRO< vgd::field::MFInt32 > normalIndex	= pVertexShape->getFNormalIndexRO();
//
//	// Start rendering the primitive.
//	assert( primitive.getType() != vgd::node::Primitive::NONE );
//	GLenum primitiveType = m_primTypeArray[ primitive.getType() ];
//
//	glBegin( primitiveType );
//
//	const int32 i32Max = primitive.getIndex() + primitive.getNumIndices();
//
//	for( int32 i32I = primitive.getIndex(); i32I<i32Max; i32I++ )
//	{
//		int32 i32VertexIndex;
//		i32VertexIndex = (*vertexIndex)[i32I];
//
//		/* FIXME // TEX COORDINATES
//		//if ( pnodeGeometry->getTexCoordinateBinding() == BIND_OFF ) // already test in void vgsdk::node::CGeometry::draw( SoState& _rState );
//		//else if ( pnodeGeometry->getTexCoordinateBinding() == BIND_OVERALL ) // already test in void vgsdk::node::CGeometry::draw( SoState& _rState );
//		//else if ( pnodeGeometry->getTexCoordinateBinding() == BIND_PER_PRIMITIVE ) already test in void vgsdk::node::CGeometry::draw( SoState& _rState );
//		if ( pnodeGeometry->getTexCoordinateBinding() == vgsdk::node::BIND_PER_VERTEX )
//		{
//			assert( pnodeGeometry->getShpTexCoordinates()->getNum() > 0 );
//
//			if ( pnodeGeometry->getShpTexCoordinateIndices()->getNum() > 0 )
//			{
//				// tex coordinate index table not empty.
//				int32 i32Index = pnodeGeometry->getShpTexCoordinateIndices()->get1Value( i32I );
//
//				pnodeGeometry->getShpTexCoordinates()->get1Value( i32Index ).getVec();
//				
//				glTexCoord2fv( pnodeGeometry->getShpTexCoordinates()->get1Value( i32Index ).getVec() );
//			}
//			else
//			{
//				// tex coordinates index table empty, use edge insteed.
//				glTexCoord2fv( pnodeGeometry->getShpTexCoordinates()->get1Value( i32Edges ).getVec() );
//			}
//		}*/
//
//
//		// normal
//		//if ( pnodeGeometry->getNormalBinding() == BIND_OFF ) // already test in void vgsdk::node::CGeometry::draw( SoState& _rState ); ???
//		// BIND_OVERALL already test.
//		// BIND_PER_PRIMITIVE already.
//		if ( pVertexShape->getNormalBinding() == vgd::node::BIND_PER_VERTEX )
//		{
//			assert( normal->size() > 0 );
//			// normal index table empty, use i32VertexIndex instead.
//			glNormal3fv( (*normal)[ i32VertexIndex ].getValue() );
//		}
//
//		/* FIXME // COLOR
//		if ( pnodeGeometry->getColorBinding() == vgsdk::node::BIND_PER_VERTEX )
//		{
//			assert( pnodeGeometry->getShpColors()->getNum() > 0 );
//
//			if ( pnodeGeometry->getShpColorIndices()->getNum() > 0 )
//			{
//				// color index table not empty.
//				int32 i32Index = pnodeGeometry->getShpColorIndices()->get1Value( i32I );
//
//				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pnodeGeometry->getShpColors()->get1Value( i32Index ).getVec() );
//				//glColor4fv( pnodeGeometry->getShpColors()->get1Value( i32Index ).getVec() );
//			}
//			else
//			{
//				// color index table empty, use edge insteed.
//				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pnodeGeometry->getShpColors()->get1Value( i32Edges ).getVec() );
//
//				//glColor4fv( pnodeGeometry->getShpColors()->get1Value( i32Edges ).getVec() );
//			}
//		}*/
//
//		// vertex
//		glVertex3fv( (*vertex)[i32VertexIndex].getValue() );
//	}
//
//	glEnd();
//	// Finish rendering the primitive.
//}
//
//
//
//void VertexShape::paintDisplayList( vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pVertexShape )
//{
//	// USE DISPLAY LIST
//	vgeGL::rc::applyUsingDisplayList< vgd::node::VertexShape, VertexShape >( pGLEngine, pVertexShape, this );
//}



/**
 * Support for vertex.
 * 
 * Support for normal					with BIND_OFF, BIND_PER_VERTEX.
 * Support for color4					with BIND_OFF, BIND_PER_VERTEX.
 * Support for secondaryColor4		with BIND_OFF, BIND_PER_VERTEX.
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
				gleGetCurrent()->isGL_ARB_multitexture &&
				"MultiTexture not currently supported.")		||
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
	for(	vgd::field::MFPrimitive::const_iterator	i	= primitives->begin(),
																	ie	= primitives->end();
			i != ie;
			i++, i32IndexPrim++)
	{
		const vgd::node::Primitive& primitive(*i);

		// *** BIND_PER_PRIMITIVE ***
		// Nothing to do, because not supported.

		// render a primitive
		paint( pGLEngine, pVertexShape, primitive, method );
	}
	
	primitives.release();
}



void VertexShape::paint(	vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pVertexShape,
									const vgd::node::Primitive& primitive,
									const vgeGL::engine::VertexArrayMethod& method )
{
	vgd::field::EditorRO< vgd::field::MFVec3f >	normal;
	vgd::field::EditorRO< vgd::field::MFVec4f >	color4;
	vgd::field::EditorRO< vgd::field::MFVec4f >	secondaryColor4;
	vgd::field::EditorRO< vgd::field::MFUInt8 >	edgeFlag;

	vgd::field::EditorRO< vgd::field::MFVec3f >	vertex;
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
	int32 numTexUnits = pVertexShape->getNumTexUnits();
	
	if ( numTexUnits >= 1 )
	{
		for(	int32 i = numTexUnits-1;
				i >= 0;
				--i )
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
			
			gleGetCurrent()->glClientActiveTexture( GL_TEXTURE0_ARB + i );
			
			if ( pVertexShape->getTexCoordBinding( i ) == vgd::node::BIND_PER_VERTEX )
			{
				int32 dimTexCoord;
				dimTexCoord	= pVertexShape->getTexCoordDim( i );
				
				switch ( dimTexCoord )
				{
					case 2:
					{
						vgd::field::EditorRO< vgd::field::MFVec2f >	texCoord;
						texCoord	= pVertexShape->getFTexCoordRO< vgd::field::MFVec2f >( i );
						pArray = static_cast< const GLvoid* >( texCoord->begin()->getValue() );
						glTexCoordPointer( 2, GL_FLOAT, 0, pArray );
						glEnableClientState( GL_TEXTURE_COORD_ARRAY );
						break;
					}
					
					case 3:
					{
						vgd::field::EditorRO< vgd::field::MFVec3f >	texCoord;
						texCoord	= pVertexShape->getFTexCoordRO< vgd::field::MFVec3f >( i );
						pArray = static_cast< const GLvoid* >( texCoord->begin()->getValue() );
						glTexCoordPointer( 3, GL_FLOAT, 0, pArray );
						glEnableClientState( GL_TEXTURE_COORD_ARRAY );
						break;
					}
	
					case 1:
					{
						vgd::field::EditorRO< vgd::field::MFFloat >	texCoord;
						texCoord	= pVertexShape->getFTexCoordRO< vgd::field::MFFloat >( i );
						pArray = static_cast< const GLvoid* >( &(*texCoord)[0] );
						glTexCoordPointer( 1, GL_FLOAT, 0, pArray );
						glEnableClientState( GL_TEXTURE_COORD_ARRAY );
						break;
					}
	
					case 4:
					{
						vgd::field::EditorRO< vgd::field::MFVec4f >	texCoord;
						texCoord	= pVertexShape->getFTexCoordRO< vgd::field::MFVec4f >( i );
						pArray = static_cast< const GLvoid* >( texCoord->begin()->getValue() );
						glTexCoordPointer( 4, GL_FLOAT, 0, pArray );
						glEnableClientState( GL_TEXTURE_COORD_ARRAY );
						break;
					}
					
					default:
						assert( false && "Unexpected dimension for texCoord." );
				} // switch
			} // BIND_PER_VERTEX
		} // for
	}
	// else nothing to do.



	// SECONDARY COLOR4
	if ( pVertexShape->getSecondaryColor4Binding() == vgd::node::BIND_PER_VERTEX )
	{
		if ( glext->isGL_EXT_secondary_color )
		{
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
	
	const int32 i32Max = primitive.getIndex() + primitive.getNumIndices();

	vertexIndex	= pVertexShape->getFVertexIndexRO();	
	pArray		= reinterpret_cast< const GLvoid* >( &(*vertexIndex)[primitive.getIndex()] );
	
	glDrawElements( primitiveType, i32Max, GL_UNSIGNED_INT, pArray );



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
		}
	}	
	
	// COLOR4
	if ( pVertexShape->getColor4Binding() == vgd::node::BIND_PER_VERTEX )
	{
		glDisableClientState( GL_COLOR_ARRAY );
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
											const vgeGL::engine::VertexArrayDisplayListMethod& method )
{
	// USE DISPLAY LIST
	vgeGL::rc::applyUsingDisplayList< vgd::node::VertexShape, VertexShape, vgeGL::engine::VertexArrayMethod >( 
		pGLEngine, pVertexShape, this );
}



///**
// * Support for vertex.
// * Support for normals					with BIND_OFF, BIND_PER_VERTEX.
// * Support for texture coordinates	with BIND_OFF.									TODO: BIND_PER_VERTEX
// * 
// * Support for vertexIndex
// * 
// * 
// * @todo Support BIND_OVERALL, BIND_PER_PRIMITIVE.
// * 
// * @todo Support for texture coordinates	with BIND_OFF, BIND_PER_VERTEX and multitexture
// * @todo Other fields (like Color3, color4, texture...).
// */
//void VertexShape::paintVBOVertexArray(	vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pVertexShape,
//																vgeGL::rc::VertexBufferObject* pVBO )
//{
//	// *** BIND_OVERALL ***
//	// Nothing to do, because not supported.
//
//	// TEX COORDINATES
//	assert( pVertexShape->getNumTexUnits() <= 1 && "MultiTexture not currently supported." );
//	
//	//if ( pVertexShape->getNumTexUnits() == 0 )
//	//{
//		// Nothing to do.
//	//}
//	//else 
//	if ( pVertexShape->getNumTexUnits() == 1 )
//	{
//		if (	(pVertexShape->getTexCoordBinding( 0 ) != vgd::node::BIND_OFF ) &&
//				(pVertexShape->getTexCoordBinding( 0 ) != vgd::node::BIND_PER_VERTEX ) )
//		{
//			assert( "Bindings other than BIND_OFF and BIN_PER_VERTEX are not supported for textures coordinates." );
//			return;
//		}
//	}
//
//	// normal
//	if (	(pVertexShape->getNormalBinding() != vgd::node::BIND_OFF ) &&
//			(pVertexShape->getNormalBinding() != vgd::node::BIND_PER_VERTEX ) )
//	{
//		assert( "Bindings other than BIND_OFF and BIN_PER_VERTEX are not supported for normals." );
//		return;
//	}
//
//	// primitive
//	vgd::field::EditorRO< vgd::field::MFPrimitive >	primitives( pVertexShape->getFPrimitiveRO() );
//
//	int32 i32IndexPrim = 0;
//	for(	vgd::field::MFPrimitive::const_iterator	i	= primitives->begin(),
//																	ie	= primitives->end();
//			i != ie;
//			i++, i32IndexPrim++)
//	{
//		const vgd::node::Primitive& primitive(*i);
//
//		// *** BIND_PER_PRIMITIVE ***
//		// Nothing to do, because not supported.
//
//		// render a primitive
//		paintVBOVertexArray( pGLEngine, pVertexShape, primitive, pVBO );
//	}
//}
//
//
//
//#define BUFFER_OFFSET(i) ((char*)NULL + (i))
//
///**
// * @brief Use Vertex, Normal, VertexIndex fields and use vertex arrays or VBO.
// */
//void VertexShape::paintVBOVertexArray(	vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pVertexShape,
//																const vgd::node::Primitive& primitive,
//																vgeGL::rc::VertexBufferObject* pVBO )
//{
//	vgd::field::EditorRW< vgd::field::MFUInt32 >	vertexIndex		= pVertexShape->getFVertexIndexRW();
//
//	vgd::field::EditorRW< vgd::field::MFVec3f >	vertex			= pVertexShape->getFVertexRW();
//	vgd::field::EditorRW< vgd::field::MFVec3f >	normal			= pVertexShape->getFNormalRW();
//
//
//	// VBO initialize if needeed.
//	gle::OpenGLExtensionsGen *glext	= pGLEngine->getContext();
//
//	// bVBOEnabled==true if VBO must be used, false if not.
//	bool bVBOEnabled				(pVBO != 0);
//	
//	// bVBONotInitialized==true if bVBOEnabled==true and VBO not initialized(first use).
//	bool bVBONotInitialized;
//
//	// ????????????????????????????????????????????????????????????????????????
///*	bool	bVBOForEachField	= true;
//	int32	maxId					= 2; // 2 => 3 VBOs (zero-based).*/
//	
//	bool	bVBOForEachField	= false;
//	int32	maxId					= 1; // 1 => 2 VBOs (zero-based).
//	
//	if ( bVBOEnabled )
//	{
//		assert( glext->isGL_ARB_vertex_buffer_object && "GL_ARB_vertex_buffer_object not detected, but try to use VBO !!!" );
//
//		bVBONotInitialized = pVBO->isEmpty();
//		
//		if ( bVBONotInitialized )
//		{
//			pVBO->generate( maxId+1 );
//		}
//		else
//		{
//			assert( pVBO->getNum() == maxId+1 );
//		}
//	}
//	//else nothing
//
//	int32		sizeOfVertexIndex;
//	int32		sizeOfVertex;
//	int32		sizeOfNormal;
//
//	int32		offsetVertexIndex;
//	int32		offsetVertex;
//	int32 	offsetNormal;
//
//	int32		idVertexIndex;
//	int32		idVertex;
//	int32		idNormal;
//
//	int32		nextID		( 0 );
//	int32		nextOffset	( 0 );
//
//	//	
//	GLvoid	*pVertexIndexArray;
//	GLvoid	*pVertexArray;
//	GLvoid 	*pNormalArray;
//	
//	pVertexIndexArray		= reinterpret_cast< GLvoid* >( &(*vertexIndex)[primitive.getIndex()] );
//	pVertexArray			= static_cast< GLvoid* >( vertex->begin()->getValue() );
//	pNormalArray			= static_cast< GLvoid* >( normal->begin()->getValue() );	
//
//	// VERTEX INDEX
//	sizeOfVertexIndex =	vertexIndex->size() * sizeof(uint32);
//
//	idVertexIndex		=	nextID++;
//	offsetVertexIndex	=	0;
//
//	// VERTEX
//	sizeOfVertex		=	vertex->size() * 3 * sizeof(float);
//	idVertex				=	nextID;
//	offsetVertex		=	nextOffset;
//	
//	if ( nextID < maxId )
//	{
//		nextID++;
//	}
//	else
//	{
//		nextOffset		+=	sizeOfVertex;
//	}
//
//	// NORMAL
//	sizeOfNormal	=	normal->size() * 3 * sizeof(float);
//	idNormal			=	nextID;
//	offsetNormal	=	nextOffset;
//	if ( nextID < maxId )
//	{
//		nextID++;
//	}
//	else
//	{
//		nextOffset		+=	sizeOfNormal;
//	}
//
//	//
//	if ( bVBOEnabled && bVBONotInitialized )
//	{
//		// VERTEX INDEX
//		glext->glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, pVBO->get(idVertexIndex) );
//
//		glext->glBufferDataARB(	GL_ELEMENT_ARRAY_BUFFER_ARB,
//										sizeOfVertexIndex, pVertexIndexArray,
//										GL_STATIC_DRAW_ARB );						// FIXME Usage
//
//		//
//		if ( bVBOForEachField )
//		{
//			// VERTEX
//			glext->glBindBufferARB( GL_ARRAY_BUFFER_ARB, pVBO->get(idVertex) );
//	
//			glext->glBufferDataARB(	GL_ARRAY_BUFFER_ARB,
//											sizeOfVertex, pVertexArray,
//											GL_STATIC_DRAW_ARB );						// FIXME Usage
//	
//			// NORMAL
//			glext->glBindBufferARB( GL_ARRAY_BUFFER_ARB, pVBO->get(idNormal) );
//	
//			glext->glBufferDataARB(	GL_ARRAY_BUFFER_ARB,
//											sizeOfNormal, pNormalArray,
//											GL_STATIC_DRAW_ARB );						// FIXME Usage
//		}
//		else
//		{
//			// VERTEX-NORMAL
//			glext->glBindBufferARB( GL_ARRAY_BUFFER_ARB, pVBO->get(idVertex) );
//	
//			glext->glBufferDataARB(	GL_ARRAY_BUFFER_ARB,
//											sizeOfVertex + sizeOfNormal, 0,
//											GL_STATIC_DRAW_ARB );						// FIXME Usage
//
//			// VERTEX
//			glext->glBufferSubDataARB( GL_ARRAY_BUFFER_ARB, offsetVertex,
//												sizeOfVertex, pVertexArray );
//
//			glext->glBufferSubDataARB( GL_ARRAY_BUFFER_ARB, offsetNormal,
//												sizeOfNormal, pNormalArray );
//		}
//	}
//	// else nothing.
//
//	// Start rendering the primitive.
//	if ( bVBOEnabled )
//	{
//		if ( bVBOForEachField )
//		{
//			glext->glBindBufferARB( GL_ARRAY_BUFFER_ARB, pVBO->get(idNormal) );
//			glNormalPointer( GL_FLOAT, 0, BUFFER_OFFSET(offsetNormal) );
//			
//			glext->glBindBufferARB( GL_ARRAY_BUFFER_ARB, pVBO->get(idVertex) );
//			glVertexPointer( 3, GL_FLOAT, 0, BUFFER_OFFSET(offsetVertex) );
//		}
//		else
//		{
//			glext->glBindBufferARB( GL_ARRAY_BUFFER_ARB, pVBO->get(idVertex) );
//			
//			glNormalPointer( GL_FLOAT, 0, BUFFER_OFFSET(offsetNormal) );
//			glVertexPointer( 3, GL_FLOAT, 0, BUFFER_OFFSET(offsetVertex) );
//		}
//	}
//	else
//	{
//		glNormalPointer( GL_FLOAT, 0, pNormalArray );
//		glVertexPointer( 3, GL_FLOAT, 0, pVertexArray );
//	}
//
//	// VERTEX INDEX
//	//
//	//glext->glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, pVBO->get(idVertexIndex) );
//	//		glext->glBufferSubDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0,
//		//										sizeOfVertexIndex,
//		//										pVertexIndexArray );
//		
//	// Enable Arrays
//	//glDisable( GL_LIGHTING ); // ??????????????????????????????????????????????????????????????
//	glEnableClientState( GL_NORMAL_ARRAY );
//	glEnableClientState( GL_VERTEX_ARRAY );
//	
//	// Render
//	assert( primitive.getType() != vgd::node::Primitive::NONE );
//	GLenum primitiveType = m_primTypeArray[ primitive.getType() ];
//	
//	const int32 i32Max = primitive.getIndex() + primitive.getNumIndices();
//	
//	if ( bVBOEnabled )
//	{
//		glext->glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, pVBO->get(idVertexIndex) );
//		
//		glDrawElements( primitiveType, i32Max, GL_UNSIGNED_INT, 0 );
//	}
//	else
//	{
//		glDrawElements( primitiveType, i32Max, GL_UNSIGNED_INT, pVertexIndexArray );
//	}
//
//	// Disable Arrays
//	glDisableClientState(GL_NORMAL_ARRAY);
//	glDisableClientState(GL_VERTEX_ARRAY);
//
//	// Finish rendering the primitive.
//}
//#undef BUFFER_OFFSET



//Rendering commands ArrayElement, DrawArrays, DrawElements,
//    DrawRangeElements, MultiDrawArrays, and MultiDrawElements
//
//	
	//glDrawRangeElements();
	/*void glDrawArrays(
	  GLenum mode,   
	  GLint first,   
	  GLsizei count  
	);*/
		//glDrawArrays( primitiveType, 0, 0 );
		/*glext->glDrawRangeElementsEXT(
			primitiveType,
			0,
			i32Max,
			i32Max,
			
			
			
	GLenum mode,
	GLuint start,
	GLuint end,
	GLsizei count,
	GLenum type,
	const GLvoid *indices
);*/



//void VertexShape::paintVBO ( vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pCastedNode )
//{
//	// VERTEX BUFFER OBJECT
//	vge::rc::Manager& rGLManager = pGLEngine->getGLManager();
//
//	// ****** Render ******
//	vgd::field::DirtyFlag			*pDF;
//	
//	vge::rc::IResource 				*pResource;
//	vgeGL::rc::VertexBufferObject	*pCastedResource;
//
//	// get dirty flag of node
//	pDF = pCastedNode->getDirtyFlag( pCastedNode->getDFNode() );
//
//	// lookup the resource.
//	pResource			= rGLManager.getAbstract( pCastedNode );
//	pCastedResource	= dynamic_cast< vgeGL::rc::VertexBufferObject* >(pResource);
//
//	assert(	(pResource==0 && pCastedResource==0) ||
//				(pResource!=0 && pCastedResource!=0)
//				 );
//
//	// What to do ?
//	if ( pDF->isDirty() )
//	{
//		// Invalidate vertex shape.
//	
//		if ( pCastedResource != 0 )
//		{
//			// Founded an associated resource, recycle it
//			pCastedResource->release();
//		}
//		else
//		{
//			// No resource (this is the first evaluation), create it.
//			pCastedResource = new vgeGL::rc::VertexBufferObject();
//			rGLManager.add( pCastedNode, pCastedResource );
//		}
//		
//		// Initialize VBO and render with it.
//		paintVBOVertexArray( pGLEngine, pCastedNode, pCastedResource );
//		
//		// validate vertex shape.
//		pDF->validate();
//	}
//	else
//	{
//		// No change in vertex shape.
//
//		if ( pCastedResource != 0 )
//		{
//			// Founded an associated resource.
//			
//			// render using VBO
//			paintVBOVertexArray( pGLEngine, pCastedNode, pCastedResource );
//		}
//		else
//		{
//			// No resource, but already validate !!!
//			assert( false && "No resource, but already validate !!!" );
//		}
//	}
//}



void VertexShape::drawBoundingBox( vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pCastedNode )
{
	drawBox3f( pCastedNode->getBoundingBox() );
}



void VertexShape::drawXfBoundingBox( vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pCastedNode )
{
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
	
	drawBox3f( pCastedNode->getProjectXfBoundingBox() );	
	
	glPopMatrix();
}



void VertexShape::drawBox3f( const vgm::Box3f& box )
{
	float			width, height, depth;
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
	vgd::field::EditorRO< vgd::field::MFVec3f >	vertex			= pCastedNode->getFVertexRO();
	vgd::field::EditorRO< vgd::field::MFVec3f >	normal			= pCastedNode->getFNormalRO();
	vgd::field::EditorRO< vgd::field::MFUInt32 >	vertexIndex		= pCastedNode->getFVertexIndexRO();

	vgd::field::EditorRO< vgd::field::MFPrimitive >	primitives( pCastedNode->getFPrimitiveRO() );

	assert( pCastedNode->getNormalBinding() == vgd::node::BIND_PER_VERTEX );
	assert( normal->size() > 0 );
	
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
	vgd::field::EditorRO< vgd::field::MFVec3f >	vertex			= pCastedNode->getFVertexRO();
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



// Be careful, the elements of this enumeration are ordered(see vgd::node::Primitive)
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
