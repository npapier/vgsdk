//// VGSDK - Copyright (C) 2009, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_TEXGEN_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_TEXGEN_HPP
//
//#include <vge/handler/painter/MultiAttribute.hpp>
//#include <vgm/Matrix.hpp>
//#include "vgeGL/vgeGL.hpp"
//
//namespace vgd { namespace node { struct TexGen; } }
//
//namespace vgeGL { namespace engine { struct Engine; } }
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
// * @brief Handler for TexGen node.
// */
//struct VGEGLBASE_API TexGen : public vge::handler::painter::MultiAttribute
//{
//	void apply( vgeGL::engine::Engine *, vgd::node::TexGen * );
//
//	void paint( vgeGL::engine::Engine*, vgd::node::TexGen* );
//
//	/**
//	 * @param textureGenModeValue	a symbolic constant specifying a single-valued texture generation parameter GL_OBJECT_LINEAR,
//	 *						GL_EYE_LINEAR, GL_SPHERE_MAP, GL_REFLECTION_MAP, or GL_NORMAL_MAP
//	 * @param planeType			GL_OBJECT PLANE or GL_EYE_PLANE
//	 * @param params				a matrix containing values that specify texture generation parameters
//	 */
//	void paint( const GLenum textureGenModeValue, const GLenum planeType, /*const*/ vgm::MatrixR& params );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_TEXGEN_HPP
//