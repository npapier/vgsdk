// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/technique/ComputeBoundingBox.hpp"

#include "vge/engine/Engine.hpp"
#include "vge/service/ComputeBoundingBox.hpp"



namespace vge
{

namespace technique
{



void ComputeBoundingBox::apply(	vge::engine::Engine *pEngine, vge::visitor::TraverseElementVector* pTraverseElements )
{
	vgd::Shp< vge::service::Service > cbb = vge::service::ComputeBoundingBox::create();

	prepareEval();
	
	pEngine->resetEval();

	beginPass();

	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = pTraverseElements->begin(), iEnd = pTraverseElements->end();
			i != iEnd;
			++i )
	{
		pEngine->evaluate( cbb, i->first, i->second );
	}
	
	endPass();

	finishEval();
}



} // namespace technique

} // namespace vge
