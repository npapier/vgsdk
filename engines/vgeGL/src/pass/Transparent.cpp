// VGSDK - Copyright (C) 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/pass/Transparent.hpp"

#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgd/node/Kit.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Shape.hpp>
#include <vgeGL/engine/Engine.hpp>
#include <vgm/operations.hpp>



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
			using vgd::node::Material;

			Material *material( engine->getStateStackTop<Material>() );
			assert( material != 0 && "Internal error" );

			const float opacity = material->getTransparency(); // @todo getTransparency() => getOpacity()
			const float opaqueDelta = fabs( opacity - 1.f );

			if ( opaqueDelta > vgm::Epsilon<float>::value() )
			{
				// Incoming shape is not opaque
				if ( opacity > vgm::Epsilon<float>::value() )
				{
					// Incoming shape is transparent (but not totally), it must be rendered
					engine->evaluate( service, i->first, i->second );
				}
				// else incoming shape is totally transparent, nothing to render
			}
			// else nothing to do for opaque object.
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
