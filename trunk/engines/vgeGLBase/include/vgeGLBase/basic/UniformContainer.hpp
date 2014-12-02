//// VGSDK - Copyright (C) 2010, 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_BASIC_UNIFORMCONTAINER_HPP
//#define _VGEGLBASE_BASIC_UNIFORMCONTAINER_HPP
//
//#include <vgd/basic/UniformContainer.hpp>
//#include "vgeGLBase/vgeGLBase.hpp"
//
//namespace vgeGLBase { namespace engine { struct Engine; } }
//
//
//
//namespace vgeGLBase
//{
//
//namespace basic
//{
//
//
//
//struct VGEGLBASE_API UniformContainer : public vgd::basic::UniformContainer
//{
//	/**
//	 * @brief Generates GLSL declaration for all uniforms in this container
//	 */
//	const std::string generateDeclarations();
//
//	/**
//	 * @brief Sends all uniform variables to OpenGL
//	 */
//	void apply( vgeGLBase::engine::Engine * engine );
//};
//
//
//
//} // namespace basic
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_BASIC_UNIFORMCONTAINER_HPP
//