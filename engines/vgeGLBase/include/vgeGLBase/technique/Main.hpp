//// VGSDK - Copyright (C) 2004, 2007, 2009, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_TECHNIQUE_MAIN_HPP
//#define _VGEGLBASE_TECHNIQUE_MAIN_HPP
//
//#include "vgeGLBase/technique/Technique.hpp"
//
//
//
//namespace vgeGLBase
//{
//
//namespace technique
//{
//
//
//
///**
// * @brief The default technique to render opaque and transparent object.
// *
// * @ingroup g_techniques_vgeGL
// * @ingroup g_techniques
// */
//struct VGEGL_CLASS_API Main : public Technique
//{
//	/**
//	 * @brief Evaluates the technique
//	 *
//	 * @param engine			evaluation engine
//	 * @param traverseElements	the "flatten" scene graph to evaluate
//	 */
//	VGEGLBASE_API void apply( vgeGLBase::engine::Engine * engine, vge::visitor::TraverseElementVector * traverseElements );
//
//protected:
//	/**
//	 * @brief Evaluates the opaque pass
//	 *
//	 * @param service	the service used by engine
//	 *
//	 * @return true if the transparency pass must be done, i.e. at least one transparent object has been encountered
//	 */
//	const bool evaluateOpaquePass(	vgd::Shp< vge::service::Service > service,
//									const PassIsolationMask isolationMask = PassIsolationMask(DEFAULT_PASS_ISOLATION_MASK),
//									const bool nestedPass = false );
//
//	/**
//	 * @brief Evaluates the transparent pass
//	 *
//	 * @param service	the service used by engine
//	 */
//	void evaluateTransparentPass(	vgd::Shp< vge::service::Service > service,
//									const PassIsolationMask isolationMask = PassIsolationMask(DEFAULT_PASS_ISOLATION_MASK),
//									const bool nestedPass = false );
//};
//
//
//
//} // namespace technique
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_TECHNIQUE_MAIN_HPP
//