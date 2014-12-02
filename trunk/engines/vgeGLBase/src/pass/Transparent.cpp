// VGSDK - Copyright (C) 2007, 2008, 2009, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/pass/Transparent.hpp"

#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgd/node/CullFace.hpp>
#include <vgd/node/Kit.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/IShape.hpp>
#include <vgeGL/engine/Engine.hpp>
#include "vgeGL/engine/GLSLState.hpp"
#include <vgm/operations.hpp>



namespace vgeGL
{

namespace pass
{



void Transparent::apply(	vgeGL::technique::Technique * /*technique*/, vgeGL::engine::Engine *engine, 
							vge::visitor::TraverseElementVector* traverseElements,
							vgd::Shp< vge::service::Service > service )
{
	// Configures blending
	glEnable( GL_BLEND );
	//glBlendFunc( GL_SRC_ALPHA, GL_ONE );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// Configures culling
	engine->disregardIfIsA< vgd::node::CullFace >();
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );

	engine->disregardIfIsAKindOf< vgd::node::Kit >(); ///< Nothing to do for nodekit in transparent pass. @todo FIXME ?

	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			i != iEnd;
			++i )
	{
		if ( (i->first)->isAKindOf< vgd::node::IShape >() )
		{
			using vgd::node::Material;

			const float opacity = engine->getGLState().getOpacity();

			if ( vgm::notEquals( opacity, 1.f ) )
			{
				// Incoming shape is not opaque
				if ( vgm::notEquals( opacity, 0.f ) )
				{
					// Incoming shape is transparent (but not totally), it must be rendered
					// glPushAttrib( GL_ALL_ATTRIB_BITS );

					engine->evaluate( service, *i );

					// glPopAttrib();
				}
				// else incoming shape is totally transparent, nothing to render
			}
			// else nothing to do for opaque object.
		}
		else
		{
			engine->evaluate( service, *i );
		}
	}

	// Restores culling
	glDisable( GL_CULL_FACE );

	// Restores  blending
	glDisable( GL_BLEND );
}



} // namespace pass

} // namespace vgeGL
