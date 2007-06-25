// VGSDK - Copyright (C) 2004, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_MAIN_HPP
#define _VGEGL_TECHNIQUE_MAIN_HPP

#include "vgeGL/technique/Technique.hpp"



namespace vgeGL
{
	
namespace technique
{



/**
 * @brief The default technique to render opaque and transparent object.
 */
struct VGEGL_CLASS_API Main : public Technique
{
	VGEGL_API void apply( vgeGL::engine::Engine * /*engine*/, vge::visitor::TraverseElementVector * /*traverseElements*/ );
};



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_MAIN_HPP
