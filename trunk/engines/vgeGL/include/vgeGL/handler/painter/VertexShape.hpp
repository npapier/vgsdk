// VGSDK - Copyright (C) 2004-2006, 2012, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_VERTEXSHAPE_HPP
#define _VGEGL_HANDLER_PAINTER_VERTEXSHAPE_HPP

#include <glo/ArrayBuffer.hpp>
#include <vge/handler/painter/Shape.hpp>
#include <vgd/node/VertexShape.hpp>
#include <vgm/Vector.hpp>

#include "vgeGL/engine/Settings.hpp"
#include "vgeGL/vgeGL.hpp"

namespace glo { struct GLSLProgram; }

namespace vgd
{
	namespace node { struct Primitive; struct VertexShape; }
}

namespace vgm { struct Box3f; }

namespace vgeGL
{
	namespace engine { struct Engine; }

	namespace rc { struct VertexShape; }
}



namespace vgeGL
{

namespace handler
{

namespace painter
{



/**
 * @brief Send render command for vertex shape.
 * 
 * @todo Complete Immediate Mode.
 */
struct VGEGL_API VertexShape : public vge::handler::painter::Shape
{
	META_HANDLER_HPP( VertexShape );

	const TargetVector getTargets()	const;

	void apply( vge::engine::Engine*, vgd::node::Node* );

	void setSamplers( vgeGL::engine::Engine * pGLEngine, glo::GLSLProgram * program );

	void unapply( vge::engine::Engine*, vgd::node::Node* );

	void setToDefaults();



	void paint(	vgeGL::engine::Engine*, vgd::node::VertexShape* );


	//
	void update(	vgeGL::engine::Engine * pGLEngine, vgd::node::VertexShape *pVertexShape,
					vgeGL::rc::VertexShape * rc );

	void configureRenderingArrays(		vgeGL::engine::Engine * pGLEngine, vgd::node::VertexShape *pVertexShape,
										vgeGL::rc::VertexShape * rc );

	void unconfigureRenderingArrays(	vgeGL::engine::Engine * pGLEngine, vgd::node::VertexShape *pVertexShape, const vgd::node::Primitive& primitive,
										vgeGL::rc::VertexShape * rc );

	void renderArrays(	vgeGL::engine::Engine * pGLEngine, vgd::node::VertexShape *pVertexShape, vgeGL::rc::VertexShape * rc );

	/**
	 * @name Rendering some basic objects.
	 */
	//@{

	void 	drawBoundingBox		( vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pCastedNode );
	void 	drawXfBoundingBox	( vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pCastedNode );

	void	drawBox3f	( const vgm::Box3f& box );
	void	drawVectorsFromVertices(	vgd::node::VertexShape *vertexShape,
										vgd::field::EditorRO< vgd::field::MFVec3f >& vectorsField, const float vectorsLength,
										std::vector< vgm::Vec3f >& vectors, glo::ArrayBuffer& buffer	);

	/**
	 * @brief Draw 3 points (one Red, one Green and one Blue) for the first triangle of each primitive in the same order
	 * than the vertex array.
	 * 
	 * @remarks Useful to know if triangles are in CCW or CW
	 */
	void 	drawTriangleOrientation( vgd::node::VertexShape *pVertexShape, vgeGL::rc::VertexShape * rc );
	//@}

protected:
	/**
	 * @brief Be careful, the elements of this enumeration are ordered(see vgd::node::Primitive)
	 */
	static GLenum m_primTypeArray[];
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_VERTEXSHAPE_HPP
