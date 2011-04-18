// VGSDK - Copyright (C) 2004, 2006, 2009, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/DrawStyle.hpp"

#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vge/service/Painter.hpp>

#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/GLSLState.hpp"
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

	targets.push_back( vgd::node::DrawStyle::getClassIndexStatic() );

	return targets;
}



void DrawStyle::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);

	assert( dynamic_cast< vgd::node::DrawStyle* >(node) != 0 );
	vgd::node::DrawStyle *drawStyle = static_cast< vgd::node::DrawStyle* >(node);

	// *** DRAWSTYLE.shape ***
	using vgd::node::DrawStyle;

	bool isDefined;
	DrawStyle::ShapeValueType shapeValue;

	isDefined = drawStyle->getShape( shapeValue );

	if ( isDefined )
	{
		// Updates GLState
		glEngine->getGLState().setShape( shapeValue );

		// Updates GLSLState
		if ( glEngine->isGLSLEnabled() )
		{
			// Retrieves GLSL state
			using vgeGL::engine::GLSLState;
			GLSLState& state = glEngine->getGLSLState();

			switch ( shapeValue )
			{
				case DrawStyle::NONE:
				case DrawStyle::POINT:
				case DrawStyle::FLAT:
				case DrawStyle::WIREFRAME:
				case DrawStyle::HIDDEN_LINE:
				case DrawStyle::FLAT_HIDDEN_LINE:
					// Updates GLSL state
					state.setEnabled( vgeGL::engine::FLAT_SHADING );
					break;

				case DrawStyle::SMOOTH:
				case DrawStyle::SMOOTH_HIDDEN_LINE:
				case DrawStyle::NEIGHBOUR:
					// Updates GLSL state
					state.setEnabled( vgeGL::engine::FLAT_SHADING, false );
					break;

				default:
					assert( false && "Unknown DrawStyle.shape value." );
			}
		}
	}

	// DRAWSTYLE.normalLength
	vgd::node::DrawStyle::NormalLengthValueType	normalLengthValue;

	isDefined = drawStyle->getNormalLength( normalLengthValue );

	if ( isDefined )
	{
		// Updates GLState
		glEngine->getGLState().setNormalLength( normalLengthValue );
	}

	// DRAWSTYLE.showOrientation
	vgd::node::DrawStyle::ShowOrientationValueType showOrientationValue;

	isDefined = drawStyle->getShowOrientation( showOrientationValue );

	if ( isDefined )
	{
		// Updates GLState
		glEngine->getGLState().setShowOrientation( showOrientationValue );
	}

	// DRAWSTYLE.boundingBox
	vgd::node::DrawStyle::BoundingBoxValueType boundingBoxValue;

	isDefined = drawStyle->getBoundingBox( boundingBoxValue );

	if ( isDefined )
	{
		// Updates GLState
		glEngine->getGLState().setBoundingBox( boundingBoxValue );
	}

	// Validates node
	node->getDirtyFlag( node->getDFNode() )->validate();
}



void DrawStyle::unapply ( vge::engine::Engine* , vgd::node::Node* )
{}



void DrawStyle::setToDefaults()
{}



/**
 * @todo Splits this method into smaller one
 */
void DrawStyle::paintVertexShapeWithShapeProperty(
	vgeGL::engine::Engine *glEngine, vgd::node::VertexShape *pVertexShape,
	vgeGL::handler::painter::VertexShape *pVertexShapeHandler )
{
	using vgd::node::DrawStyle;

	// *** DRAWSTYLE.shape ***
	const DrawStyle::ShapeValueType shapeValue = glEngine->getGLState().getShape();

	switch ( shapeValue )
	{
		case DrawStyle::NONE:
			break;

		case DrawStyle::POINT:
			///@todo FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );

			glPointSize( 4.0 );
			glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );

			pVertexShapeHandler->paintMethodChooser( glEngine, pVertexShape );

			///@todo FIXME OPTME
			glPopAttrib();
			break;

		case DrawStyle::FLAT:
			///@todo FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glShadeModel(GL_FLAT);

			pVertexShapeHandler->paintMethodChooser( glEngine, pVertexShape );
			
			///@todo FIXME OPTME
			glPopAttrib();
			break;
			
		// see below for case SMOOTH:

		case DrawStyle::WIREFRAME:
			///@todo FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );
		
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			
			pVertexShapeHandler->paintMethodChooser( glEngine, pVertexShape );
			
			///@todo FIXME OPTME
			glPopAttrib();
			break;

		case DrawStyle::HIDDEN_LINE:
		{
			///@todo FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );
	
			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			pVertexShapeHandler->paintMethodChooser( glEngine, pVertexShape );

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

			pVertexShapeHandler->paintMethodChooser( glEngine, pVertexShape );

			glDisable(GL_POLYGON_OFFSET_FILL);
			
			///@todo FIXME OPTME
			glPopAttrib();
			break;
		}

		case DrawStyle::FLAT_HIDDEN_LINE:
		{
			///@todo FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );

			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

			glPushAttrib( GL_ALL_ATTRIB_BITS );
			float vMat[4];
			glGetFloatv( GL_COLOR_CLEAR_VALUE, vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS,	vMat );
			
			pVertexShapeHandler->paintMethodChooser( glEngine, pVertexShape );
			
			glPopAttrib();
			
			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glShadeModel( GL_FLAT );
			glEnable( GL_POLYGON_OFFSET_FILL );
			glPolygonOffset( 1.0, 1.0 );

			pVertexShapeHandler->paintMethodChooser( glEngine, pVertexShape );
			
			glDisable(GL_POLYGON_OFFSET_FILL);

			///@todo FIXME OPTME
			glPopAttrib();
			break;
		}

		case DrawStyle::SMOOTH_HIDDEN_LINE:
		{
			///@todo FIXME OPTME
			glPushAttrib( GL_ALL_ATTRIB_BITS );

			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

			glPushAttrib( GL_ALL_ATTRIB_BITS );
			float vMat[4];			
			glGetFloatv( GL_COLOR_CLEAR_VALUE, vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,	vMat );
			glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS,	vMat );
			
			pVertexShapeHandler->paintMethodChooser( glEngine, pVertexShape );
			
			glPopAttrib();
			
			//
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glShadeModel( GL_SMOOTH );
			glEnable( GL_POLYGON_OFFSET_FILL );
			glPolygonOffset( 1.0, 1.0 );

			pVertexShapeHandler->paintMethodChooser( glEngine, pVertexShape );
			
			glDisable(GL_POLYGON_OFFSET_FILL);

			///@todo FIXME OPTME
			glPopAttrib();
			break;
		}

		case DrawStyle::NEIGHBOUR: ///@todo support Neighbour option
		case DrawStyle::SMOOTH:
			///@todo FIXME OPTME
			//glPushAttrib( GL_ALL_ATTRIB_BITS );

			// FIXME move to engine.
			// POLYGON_MODE
#ifdef _DEBUG
/*			GLint polygonMode[2];
			glGetIntegerv( GL_POLYGON_MODE, polygonMode );
			//bool	bRestorePolygonMode;
			if (	(polygonMode[0] != GL_FILL) ||
					(polygonMode[1] != GL_FILL) )
			{
				assert( false && "Unexpected GL_POLYGON_MODE value ! ");
				glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
				//bRestorePolygonMode = true;
			}*/
			//else
			//{ 
			//	bRestorePolygonMode = false;
			//}

			// SHADE_MODEL
/*			GLint shadeModel;
			glGetIntegerv( GL_SHADE_MODEL, &shadeModel );
			
			//bool bRestoreShadeModel;
			if ( shadeModel != GL_SMOOTH )
			{
				assert( false && "Unexpected GL_SHADE_MODEL value ! ");
				//bRestoreShadeModel = true;
				glShadeModel( GL_SMOOTH );
			}*/
			//else
			//{
			//	bRestoreShadeModel = false;
			//}
#endif

			pVertexShapeHandler->paintMethodChooser( glEngine, pVertexShape );

			//
			//if ( bRestoreShadeModel )
			//{
			//	glShadeModel( shadeModel );
			//}
			
			//if ( bRestorePolygonMode )
			//{
			//	glPolygonMode( GL_FRONT,polygonMode[0] );
			//	glPolygonMode( GL_BACK,	polygonMode[1] );
			//}

			///@todo FIXME OPTME
			//glPopAttrib();
			break;

		default:
			assert( false && "Unknown DrawStyle.shape value." );
	}
}



void DrawStyle::paintVertexShapeNormals(	vgeGL::engine::Engine *glEngine, vgd::node::VertexShape *pVertexShape,
											vgeGL::handler::painter::VertexShape *pVertexShapeHandler )
{
	// *** DRAWSTYLE.normalLength ***
	vgd::node::DrawStyle::NormalLengthValueType	value = glEngine->getGLState().getNormalLength();

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
