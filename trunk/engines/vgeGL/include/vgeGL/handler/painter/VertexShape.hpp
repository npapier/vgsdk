// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_VERTEXSHAPE_HPP
#define _VGEGL_HANDLER_PAINTER_VERTEXSHAPE_HPP

#include <vge/handler/painter/Shape.hpp>

#include "vgeGL/engine/Settings.hpp"
#include "vgeGL/vgeGL.hpp"

namespace vgd
{
	namespace node
	{
		struct Primitive;
		struct VertexShape;
	}
}

namespace vgm
{
	struct Box3f;
}

namespace vgeGL
{

	namespace engine
	{
		struct Engine;
	}

	namespace rc
	{
		struct VertexShape;
	}
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
	
	void unapply( vge::engine::Engine*, vgd::node::Node* );

	void setToDefaults();



	void paintMethodChooser( vgeGL::engine::Engine*, vgd::node::VertexShape* );



//	// IMMEDIATE MODE
//	/**
//	 * @brief Render all primitives in immediate mode.
//	 */
//	void	paint( vgeGL::engine::Engine*, vgd::node::VertexShape* );
//	
//	/**
//	 * @brief Render one primitive in immediate mode.
//	 */
//	void	paint( vgeGL::engine::Engine*, vgd::node::VertexShape*, const vgd::node::Primitive& );



//	// DISPLAY LIST
//	/**
//	 * @brief Render all primitives in display lists (immediate mode encapsulate in a display list).
//	 */
//	void	paintDisplayList( vgeGL::engine::Engine*, vgd::node::VertexShape* );



	// VERTEX ARRAY
	/**
	 * @brief Render all primitives with vertex array.
	 */
	void	paint(	vgeGL::engine::Engine*, vgd::node::VertexShape*, 
					const vgeGL::engine::VertexArrayMethod& );

	void	paint(	vgeGL::engine::Engine*, vgd::node::VertexShape*, const vgd::node::Primitive&, 
					const vgeGL::engine::VertexArrayMethod& );

	void updateTexCoord(	vgd::node::VertexShape * vertexShape, const uint unit, const uint texCoordDim,
							vgeGL::rc::VertexShape * rc );
	void configureTexCoord(	vgd::node::VertexShape * vertexShape, const uint unit, const uint texCoordDim,
							vgeGL::rc::VertexShape * rc, const bool isVertexBufferObjectEnabled );


	// VERTEX ARRAY IN DISPLAY LIST
	/**
	 * @brief Render all primitives in display list (vertex array encapsulate in a display list).
	 */
	void	paint(	vgeGL::engine::Engine*, vgd::node::VertexShape*,
					const vgeGL::engine::VertexArrayDisplayListMethod& );


	//
	void update(	vgeGL::engine::Engine * pGLEngine, vgd::node::VertexShape *pVertexShape,
					vgeGL::rc::VertexShape * rc );
	void submit(	vgeGL::engine::Engine * pGLEngine, vgd::node::VertexShape *pVertexShape, const vgd::node::Primitive& primitive,
					vgeGL::rc::VertexShape * rc );
//	// VERTEX ARRAY IN VBO
//	/**
//	 * @brief Render all primitives with vertex array.
//	 * 
//	 * @param pVBO		zero to use plain VertexArray,
//	 * 					not zero to use VertexBufferObject.
//	 * 
//	 * @remarks If VertexBufferObject is empty (pVBO->isEmpty()), than paintVertexArray() generate and initialize VBO,
//	 * otherwise paintVertexArray() use only VBO contains by VertexBufferObject.
//	 */
//	void	paintVBOVertexArray(	vgeGL::engine::Engine*, vgd::node::VertexShape*, 
//									vgeGL::rc::VertexBufferObject* pVBO = 0);
//
//	/**
//	 * @brief Render one primitive with vertex array.
//	 */
//	void	paintVBOVertexArray(	vgeGL::engine::Engine *pEngine, vgd::node::VertexShape *pVertexShape,
//									const vgd::node::Primitive& primitive, vgeGL::rc::VertexBufferObject* pVBO = 0 );
//
//	/**
//	 * @brief Render all primitives with VBO (Vertex Buffer Object).
//	 */
//	void	paintVBO( vgeGL::engine::Engine*, vgd::node::VertexShape* );



	/**
	 * @name Rendering some basic objects.
	 */
	//@{

	void 	drawBoundingBox		( vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pCastedNode );
	void 	drawXfBoundingBox	( vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pCastedNode );

	void	drawBox3f	( const vgm::Box3f& box );
	void	drawNormals	( vgd::node::VertexShape *pCastedNode, const float normalLength );

	/**
	 * @brief Draw 3 points (one Red, one Green and one Blue) for the first triangle of each primitive in the same order
	 * than the vertex array.
	 * 
	 * @remarks Useful to know if triangles are in CCW or CW
	 */
	void 	drawTriangleOrientation( vgd::node::VertexShape *pCastedNode );
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
