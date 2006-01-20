// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_TECHNIQUE_COMPUTEBOUNDINGBOX_H
#define _VGE_TECHNIQUE_COMPUTEBOUNDINGBOX_H

#include "vge/vge.hpp"
#include "vge/technique/Technique.hpp"



namespace vge
{
	
namespace technique
{



/**
 * @brief Technique to compute/update bounding box.
 */
struct VGE_API ComputeBoundingBox : public Technique
{
	virtual void apply( vge::engine::Engine *pEngine, vge::visitor::TraverseElementVector* pTraverseElements );
};



} // namespace technique

} // namespace vge

#endif //#ifndef _VGE_TECHNIQUE_COMPUTEBOUNDINGBOX_H
