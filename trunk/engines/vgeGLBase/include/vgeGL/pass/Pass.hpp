//// VGSDK - Copyright (C) 2007, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_PASS_PASS_HPP
//#define _VGEGLBASE_PASS_PASS_HPP
//
//#include <vge/pass/Pass.hpp>
//
//#include "vgeGL/vgeGL.hpp"
//
//
//
//namespace vgeGL
//{
//
//namespace engine { 	struct Engine; 	}
//
//namespace technique { struct Technique; }
//
///**
// * @namespace vgeGL::pass
// * 
// * @brief Provides a framework to describe a single pass of a technique evaluation strategy.
// */
//namespace pass
//{
//
//
//
///**
// * @brief Pass describes a single pass of a technique evaluation strategy.
// */
//struct Pass : public ::vge::pass::Pass
//{
//	/**
//	 * @brief Applies the pass to the traverse elements with the engine
//	 * 
//	 * @param technique			technique owning this pass and from where this pass is called
//	 * @param engine			engine used during evaluation
//	 * @param traverseElements	elements to evaluate
//	 * @param service			service to evaluate
//	 */
//	VGEGLBASE_API virtual void apply(	vgeGL::technique::Technique * technique, vgeGL::engine::Engine *engine, 
//									vge::visitor::TraverseElementVector* traverseElements,
//									vgd::Shp< vge::service::Service > service ) = 0;
//private:
//	virtual void apply(	vge::technique::Technique * technique, vge::engine::Engine *engine, 
//						vge::visitor::TraverseElementVector* traverseElements,
//						vgd::Shp< vge::service::Service > service );
//};
//
//
//
//} // namespace pass
//
//} // namespace vgeGL
//
//#endif //#ifndef _VGEGLBASE_PASS_PASS_HPP
//