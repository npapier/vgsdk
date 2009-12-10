// VGSDK - Copyright (C) 2004, 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/technique/ComputeBoundingBox.hpp"

#include "vge/pass/ForEach.hpp"
#include "vge/service/ComputeBoundingBox.hpp"



namespace vge
{

namespace technique
{



void ComputeBoundingBox::apply( vge::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements )
{
	vgd::Shp< vge::service::Service > cbb = vge::service::ComputeBoundingBox::create();

	prepareEval( engine, traverseElements );

	evaluatePass( ::vgd::makeShp( new vge::pass::ForEach ), cbb, engine, PassIsolationMask(0) );

	finishEval();
}



} // namespace technique

} // namespace vge
