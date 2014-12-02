//// VGSDK - Copyright (C) 2004-2006, 2012, 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_VERTEXSHAPE_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_VERTEXSHAPE_HPP
//
//#include <glo/ArrayBuffer.hpp>
//#include <vge/handler/painter/Shape.hpp>
//#include <vgd/node/VertexShape.hpp>
//#include <vgm/Vector.hpp>
//
//#include "vgeGL/engine/Settings.hpp"
//#include "vgeGL/vgeGL.hpp"
//
//namespace glo { struct GLSLProgram; }
//
//namespace vgd
//{
//	namespace node { struct Primitive; struct VertexShape; }
//}
//
//namespace vgm { struct Box3f; }
//
//namespace vgeGL
//{
//	namespace engine { struct Engine; }
//
//	namespace rc { struct VertexShape; }
//}
//
//
//
//namespace vgeGL
//{
//
//namespace handler
//{
//
//namespace painter
//{
//
//
//
///**
// * @brief Send render command for vertex shape.
// * 
// * @todo Remove immediate mode.
// */
//struct VGEGLBASE_API VertexShape : public vge::handler::painter::Shape
//{
//	META_HANDLER_HPP( VertexShape );
//
//	VertexShape() : geoMorph2(0)
//	{}
//
//	const TargetVector getTargets()	const;
//
//	// *)disable tessellation/bumpmapping if not supported for this shape
//	// *2)update glslState.textures[].texCoordDim from vertexShape->texCoordDim
//	// generate GLSL program if needed
//	// setCurrentProgram()
//	// setSamplers()
//	// apply uniformState
//	// renders the VertexShape
//	// renders additional properties of VertexShape
//	// TODO restore value modified in *2) ?
//	// restore value modified in *)
//	void apply( vge::engine::Engine*, vgd::node::Node* );
//	void unapply( vge::engine::Engine*, vgd::node::Node* );
//	void setToDefaults();
//
//	void setSamplers( vgeGL::engine::Engine * pGLEngine, glo::GLSLProgram * program );
//
//	// create rc
//	// 	update, configure, render
//	// or
//	// 	render
//	void paint( vgeGL::engine::Engine*, vgd::node::VertexShape* );
//
//
//	// creates opengl buffer and upload data
//	void update(	vgeGL::engine::Engine * engine, vgd::node::VertexShape * vertexShape, vgeGL::rc::VertexShape * rc );
//
//	// glEnableVertexAttribArray, glVertexAttribPointer
//	//	or
//	// glDisableVertexAttribArray
//	void configureRenderingArrays( vgeGL::engine::Engine * engine, vgd::node::VertexShape * vertexShape, vgeGL::rc::VertexShape * rc );
//
//	// @todo doc
//	// @todo NORMAL1_INDEX,
//	// @todo TANGENT1_INDEX,
//	void configureRenderingArraysForGeoMorph( vgeGL::engine::Engine * engine, vgd::node::VertexShape * vertexShape, vgeGL::rc::VertexShape * rc );
//	void unconfigureRenderingArraysForGeoMorph( vgeGL::engine::Engine * engine, vgd::node::VertexShape * vertexShape, vgeGL::rc::VertexShape * rc );
//
//	// return if GLSL program is not linked
//	// geomorph work
//	// @todo doc
//	void renderArrays(	vgeGL::engine::Engine * pGLEngine, vgd::node::VertexShape *pVertexShape, vgeGL::rc::VertexShape * rc );
//
//
//	/**
//	 * @name GeoMorph node related data
//	 */
//	//@{
//	vgd::node::VertexShape		*geoMorph2;				///< if and only if geoMorph2 is not null, then rendering have to use this shape to initialize m_vertex1, ...
//	//@}
//
//
//	/**
//	 * @name Rendering some basic objects.
//	 */
//	//@{
//
//	void 	drawBoundingBox		( vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pCastedNode );
//	void 	drawXfBoundingBox	( vgeGL::engine::Engine *pGLEngine, vgd::node::VertexShape *pCastedNode );
//
//	void	drawBox3f	( const vgm::Box3f& box );
//	void	drawVectorsFromVertices(	vgd::node::VertexShape *vertexShape,
//										vgd::field::EditorRO< vgd::field::MFVec3f >& vectorsField, const float vectorsLength,
//										std::vector< vgm::Vec3f >& vectors, glo::ArrayBuffer& buffer	);
//
//	/**
//	 * @brief Draw 3 points (one Red, one Green and one Blue) for the first triangle of each primitive in the same order
//	 * than the vertex array.
//	 * 
//	 * @remarks Useful to know if triangles are in CCW or CW
//	 */
//	void 	drawTriangleOrientation( vgd::node::VertexShape *pVertexShape, vgeGL::rc::VertexShape * rc );
//	//@}
//
//protected:
//	/**
//	 * @brief Be careful, the elements of this enumeration are ordered(see vgd::node::Primitive)
//	 */
//	static GLenum m_primTypeArray[];
//};
//
//
//
//} // namespace painter
//
//} // namespace handler
//
//} // namespace vgeGL
//
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_VERTEXSHAPE_HPP
//