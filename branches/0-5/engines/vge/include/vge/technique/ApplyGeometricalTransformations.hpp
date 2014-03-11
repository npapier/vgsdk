// VGSDK - Copyright (C) 2010, Nicolas Papier, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Maxime Peresson

#ifndef _VGE_TECHNIQUE_APPLYGEOMETRICALTRANSFORMATIONS_HPP
#define _VGE_TECHNIQUE_APPLYGEOMETRICALTRANSFORMATIONS_HPP

#include "vge/technique/Technique.hpp"



namespace vge
{

namespace technique
{



/**
 * @brief	ApplyGeometricalTransformations Technique.
 * 			Removes all transformation nodes by applying them directly on shapes.
 *
 * @ingroup g_techniques_vge
 * @ingroup g_techniques
 */
struct ApplyGeometricalTransformations : public Technique
{
	VGE_API virtual void apply(	vge::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements );
};



} // namespace technique

} // namespace vge

#endif //#ifndef _VGE_TECHNIQUE_APPLYGEOMETRICALTRANSFORMATIONS_HPP
