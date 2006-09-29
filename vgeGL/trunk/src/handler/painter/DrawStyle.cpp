// VGSDK - Copyright (C) 2004, 2006, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/DrawStyle.hpp"

#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vge/service/Painter.hpp>

#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/handler/painter/VertexShape.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( DrawStyle );



const vge::handler::Handler::TargetVector DrawStyle::getTargets() const
{
	TargetVector targets;
	
	targets.reserve( 1 );
	targets.push_back( vgd::node::DrawStyle::getClassIndexStatic() );

	return ( targets );
}



void DrawStyle::apply ( vge::engine::Engine* , vgd::node::Node *pNode )
{
	// Validate node
	pNode->getDirtyFlag(pNode->getDFNode())->validate();	
}



void DrawStyle::unapply ( vge::engine::Engine* , vgd::node::Node* )
{}



void DrawStyle::setToDefaults()
{}



/**
 * @todo Splits this method into smaller one
 */
void DrawStyle::paintVertexShapeWithShapeProperty(
	vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pVertexShape,
	vgeGL::handler::painter::VertexShape *pVertexShapeHandler )
{
	// *** DRAWSTYLE.shape ***
	vgd::node::DrawStyle::ShapeValueType shapeValue;

	const bool bDefined = pGLEngine->getStateStackTop<
						vgd::node::DrawStyle,
						vgd::node::DrawStyle::ShapeParameterType,
						vgd::node::DrawStyle::ShapeValueType >(	vgd::node::DrawStyle::getFShape(),
																vgd::node::DrawStyle::SHAPE,
																shapeValue );
	assert( bDefined );

	switch ( shapeValue )
	{
		case vgd::node::DrawStyle::NONE:
			break;

		case vgd::node::DrawStyle::POINT:
			///@todo FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );

			glPointSize( 4.0 );
			glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );

			pVertexShapeHandler->paintMethodChooser( pGLEngine, pVertexShape );

			///@todo FIXME OPTME
			glPopAttrib();
			break;

		case vgd::node::DrawStyle::FLAT:
			///@todo FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glShadeModel(GL_FLAT);

			pVertexShapeHandler->paintMethodChooser( pGLEngine, pVertexShape );
			
			///@todo FIXME OPTME
			glPopAttrib();			
			break;
			
		// see below for case SMOOTH:

		case vgd::node::DrawStyle::WIREFRAME:
			///@todo FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );
		
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			
			pVertexShapeHandler->paintMethodChooser( pGLEngine, pVertexShape );
			
			///@todo FIXME OPTME
			glPopAttrib();
			break;

		case vgd::node::DrawStyle::HIDDEN_LINE:
		{
			///@todo FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );
	
			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			pVertexShapeHandler->paintMethodChooser( pGLEngine, pVertexShape );

			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glEnable( GL_POLYGON_OFFSET_FILL );
			glPolygonOffset( 1.0f, 1.0f );
			
			float vMat[4];
			glGetFloatv( GL_COLOR_CLEAR_VALUE, vMat );

			glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS,	vMat );

			pVertexShapeHandler->paintMethodChooser( pGLEngine, pVertexShape );

			glDisable(GL_POLYGON_OFFSET_FILL);
			
			///@todo FIXME OPTME
			glPopAttrib();
			break;
		}

		case vgd::node::DrawStyle::FLAT_HIDDEN_LINE:
		{
			///@todo FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );

			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

			//glPushAttrib( GL_ALL_ATTRIB_BITS );
			float vMat[4];			
			glGetFloatv( GL_COLOR_CLEAR_VALUE, vMat );			
			glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS,	vMat );
			
			pVertexShapeHandler->paintMethodChooser( pGLEngine, pVertexShape );
			
			//glPopAttrib();
			
			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glShadeModel( GL_FLAT );
			glEnable( GL_POLYGON_OFFSET_FILL );
			glPolygonOffset( 1.0, 1.0 );

			pVertexShapeHandler->paintMethodChooser( pGLEngine, pVertexShape );
			
			glDisable(GL_POLYGON_OFFSET_FILL);

			///@todo FIXME OPTME
			glPopAttrib();
			break;
		}

		case vgd::node::DrawStyle::SMOOTH_HIDDEN_LINE:
		{
			///@todo FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );

			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

			//glPushAttrib( GL_ALL_ATTRIB_BITS );
			
			float vMat[4];			
			glGetFloatv( GL_COLOR_CLEAR_VALUE, vMat );			
			glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS,	vMat );
			
			pVertexShapeHandler->paintMethodChooser( pGLEngine, pVertexShape );
			
			//glPopAttrib();
			
			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glShadeModel( GL_SMOOTH );
			glEnable( GL_POLYGON_OFFSET_FILL );
			glPolygonOffset( 1.0, 1.0 );

			pVertexShapeHandler->paintMethodChooser( pGLEngine, pVertexShape );
			
			glDisable(GL_POLYGON_OFFSET_FILL);

			///@todo FIXME OPTME
			glPopAttrib();
			break;
		}

		case vgd::node::DrawStyle::NEIGHBOUR: ///@todo support Neighbour option
		case vgd::node::DrawStyle::SMOOTH:
		
			///@todo FIXME OPTME
			//glPushAttrib( GL_ALL_ATTRIB_BITS );

			// FIXME move to engine.
			// POLYGON_MODE
			GLint polygonMode[2];
			glGetIntegerv( GL_POLYGON_MODE, polygonMode );

			bool	bRestorePolygonMode;
			if (	(polygonMode[0] != GL_FILL) ||
					(polygonMode[1] != GL_FILL) )
			{
				glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
				bRestorePolygonMode = true;
			}
			else
			{ 
				bRestorePolygonMode = false;
			}
			
			// SHADE_MODEL
			GLint shadeModel;
			glGetIntegerv( GL_SHADE_MODEL, &shadeModel );
			
			bool bRestoreShadeModel;
			if ( shadeModel != GL_SMOOTH )
			{
				bRestoreShadeModel = true;
				glShadeModel( GL_SMOOTH );
			}
			else
			{
				bRestoreShadeModel = false;
			}

			pVertexShapeHandler->paintMethodChooser( pGLEngine, pVertexShape );
			
			//
			if ( bRestoreShadeModel )
			{
				glShadeModel( shadeModel );
			}
			
			if ( bRestorePolygonMode )
			{
				glPolygonMode( GL_FRONT,polygonMode[0] );
				glPolygonMode( GL_BACK,	polygonMode[1] );				
			}

			///@todo FIXME OPTME
			//glPopAttrib();
			break;

		default:
			assert( false && "Unknown DrawStyle.shape value." );
	}
}



void DrawStyle::paintVertexShapeNormals(	vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pVertexShape,
											vgeGL::handler::painter::VertexShape *pVertexShapeHandler )
{
	// *** DRAWSTYLE.normalLength ***
	vgd::node::DrawStyle::NormalLengthValueType	value;

	const bool bDefined = pGLEngine->getStateStackTop< 
						vgd::node::DrawStyle, 
						vgd::node::DrawStyle::NormalLengthParameterType,
						vgd::node::DrawStyle::NormalLengthValueType >(	vgd::node::DrawStyle::getFNormalLength(),
																		vgd::node::DrawStyle::NORMAL_LENGTH,
																		value );
	assert( bDefined );

	if ( value != 0.f )
	{
		///@todo FIXME OPTME
		glPushAttrib( GL_ALL_ATTRIB_BITS );

		glDisable( GL_LIGHTING );
		glColor3f( 1.f, 1.f, 1.f );
		// END FIXME

		pVertexShapeHandler->drawNormals( pVertexShape, value );
		
		///@todo FIXME OPTME
		glPopAttrib();
	}
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
