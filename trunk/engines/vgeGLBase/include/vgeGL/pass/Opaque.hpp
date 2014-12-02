//// VGSDK - Copyright (C) 2007, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_PASS_OPAQUE_HPP
//#define _VGEGLBASE_PASS_OPAQUE_HPP
//
//#include "vgeGL/pass/Pass.hpp"
//
//
//
//namespace vgeGL
//{
//
//namespace pass
//{
//
//
//
///**
// * @brief Opaque pass
// */
//struct Opaque : public ::vgeGL::pass::Pass
//{
//	/**
//	 * @brief Default constructor
//	 */
//	VGEGLBASE_API Opaque();
//
//	VGEGLBASE_API void apply(	vgeGL::technique::Technique * technique, vgeGL::engine::Engine *engine, 
//							vge::visitor::TraverseElementVector* traverseElements,
//							vgd::Shp< vge::service::Service > service );
//
//	/**
//	 * @brief Returns informations about transparency pass
//	 * 
//	 * @return True if a transparent shape has been encoutered during apply(), false otherwise.
//	 */
//	VGEGLBASE_API const bool mustDoTransparencyPass() const;
//
//private:
//
//	/**
//	 * @brief True if a transparent shape has been encoutered during apply(), false otherwise.
//	 * 
//	 * At startup, the transparency pass is disabled. It would be enabled during the opaque pass if at least one
//	 * transparent shape is encountered.
//	 */
//	bool m_mustDoTransparencyPass;
//};
//
//
//
//} // namespace pass
//
//} // namespace vgeGL
//
//#endif //#ifndef _VGEGLBASE_PASS_OPAQUE_HPP
//