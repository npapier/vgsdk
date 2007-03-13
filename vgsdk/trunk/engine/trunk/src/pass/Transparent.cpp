// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/pass/Transparent.hpp"

#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgd/node/Kit.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Shape.hpp>
#include <vgeGL/engine/Engine.hpp>



namespace vgeGL
{

namespace pass
{



void Transparent::apply(	vgeGL::technique::Technique * /*technique*/, vgeGL::engine::Engine *engine, 
							vge::visitor::TraverseElementVector* traverseElements,
							vgd::Shp< vge::service::Service > service )
{
	engine->resetMatrices();
	
	engine->pushStateStack();			
	glPushAttrib( GL_ALL_ATTRIB_BITS );	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glDepthMask(GL_FALSE);	
			
	engine->disregardIfIsA< vgd::node::ClearFrameBuffer >();
	engine->disregardIfIsAKindOf< vgd::node::Kit >(); ///< Nothing to do for nodekit in transparent pass. FIXME ?

	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			i != iEnd;
			++i )
	{
		if ( (i->first)->isAKindOf< vgd::node::Shape >() )
		{
			vgd::node::Material *pMaterial( engine->getStateStackTop<vgd::node::Material>() );
			assert( pMaterial != 0 );

			if ( pMaterial->getTransparency() < 1.f )
			{
				// object is transparent, draw it.
				engine->evaluate( service, i->first, i->second );
			}
			// nothing to do for opaque object.
		}
		else
		{
			engine->evaluate( service, i->first, i->second );
		}
	}

	engine->regardIfIsAKindOf< vgd::node::Kit >();		
	engine->regardIfIsA< vgd::node::ClearFrameBuffer >();

	glPopAttrib();
	engine->popStateStack();
}



} // namespace pass

} // namespace vgeGL
