// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_TECHNIQUE_COMPUTEBOUNDINGBOX_HPP
#define _VGE_TECHNIQUE_COMPUTEBOUNDINGBOX_HPP

#include "vge/technique/Technique.hpp"
#include "vge/vge.hpp"



namespace vge
{
	
namespace technique
{



/**
 * @brief Technique to compute/update bounding box.
 */
struct ComputeBoundingBox : public Technique
{
	VGE_API virtual void apply(	vge::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements );
};



} // namespace technique

} // namespace vge

#endif //#ifndef _VGE_TECHNIQUE_COMPUTEBOUNDINGBOX_HPP
