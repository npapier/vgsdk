// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_PASS_TRANSPARENT_HPP
#define _VGEGL_PASS_TRANSPARENT_HPP

#include "vgeGL/pass/Pass.hpp"



namespace vgeGL
{

namespace pass
{



/**
 * @brief Transparent pass
 */
struct Transparent : public ::vgeGL::pass::Pass
{
	VGEGL_API void apply(	vgeGL::technique::Technique * technique, vgeGL::engine::Engine *engine, 
							vge::visitor::TraverseElementVector* traverseElements,
							vgd::Shp< vge::service::Service > service );
};



} // namespace pass

} // namespace vgeGL

#endif //#ifndef _VGEGL_PASS_TRANSPARENT_HPP
