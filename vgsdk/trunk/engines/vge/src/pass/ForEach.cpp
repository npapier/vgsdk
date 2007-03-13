// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/pass/ForEach.hpp"

#include "vge/engine/Engine.hpp"



namespace vge
{

namespace pass
{



void ForEach::apply(	vge::technique::Technique* technique, vge::engine::Engine *engine, 
						vge::visitor::TraverseElementVector* traverseElements,
						vgd::Shp< vge::service::Service > service )
{
	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			i != iEnd;
			++i )
	{
		engine->evaluate( service, i->first, i->second );
	}
}



} // namespace pass

} // namespace vge
