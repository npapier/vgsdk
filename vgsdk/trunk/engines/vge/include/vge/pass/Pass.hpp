// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_PASS_PASS_HPP
#define _VGE_PASS_PASS_HPP

#include "vge/vge.hpp"
#include "vge/visitor/NodeCollectorExtended.hpp"

namespace vgd { template<class T> struct Shp; }

namespace vge
{
	namespace engine { struct Engine; }

	namespace service { struct Service; }

	namespace technique { struct Technique; }
}



namespace vge
{

/**
 * @namespace vge::pass
 * 
 * @brief Provides a framework to describe a single pass of a technique evaluation strategy.
 */
namespace pass
{

/**
 * @brief Pass describes a single pass of a technique evaluation strategy.
 */
struct Pass
{
	/**
	 * @brief Virtual destructor
	 */
	VGE_API virtual ~Pass();

	/**
	 * @brief Applies the pass to the traverse elements with the engine
	 * 
	 * @param technique			technique owning this pass and from where this pass is called
	 * @param engine			engine used during evaluation
	 * @param traverseElements	elements to evaluate
	 * @param service			service to evaluate
	 */
	VGE_API virtual void apply(	vge::technique::Technique * technique, vge::engine::Engine *engine, 
								vge::visitor::TraverseElementVector* traverseElements,
								vgd::Shp< vge::service::Service > service ) = 0;
};



} // namespace pass

} // namespace vge

#endif //#ifndef _VGE_PASS_PASS_HPP
