// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_PASS_FOREACH_HPP
#define _VGE_PASS_FOREACH_HPP

#include "vge/pass/Pass.hpp"



namespace vge
{

namespace pass
{



/**
 * @brief A simple evaluation of each traverse elements.
 */
struct ForEach : public Pass
{
	VGE_API virtual void apply(	vge::technique::Technique * technique, vge::engine::Engine *engine, 
								vge::visitor::TraverseElementVector* traverseElements,
								vgd::Shp< vge::service::Service > service );
};



} // namespace pass

} // namespace vge

#endif //#ifndef _VGE_PASS_FOREACH_HPP
