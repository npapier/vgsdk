// VGSDK - Copyright (C) 2007, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/pass/Opaque.hpp"

#include <vgd/node/Material.hpp>
#include <vgd/node/Shape.hpp>
#include <vgeGL/engine/Engine.hpp>
#include <vgm/operations.hpp>



namespace vgeGL
{

namespace pass
{



Opaque::Opaque()
: 	m_mustDoTransparencyPass( false )
{}



void Opaque::apply(	vgeGL::technique::Technique * technique, vgeGL::engine::Engine *engine, 
					vge::visitor::TraverseElementVector* traverseElements,
					vgd::Shp< vge::service::Service > service )
{
	// @todo
//	engine->resetMatrices();

	engine->push();
	/*getGLSLStateStack().push();
	engine->getGLStateStack().push();
	engine->pushStateStack();
	glPushAttrib( GL_ALL_ATTRIB_BITS );*/
	//

	vge::visitor::TraverseElementVector::const_iterator i, iEnd;

	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			i != iEnd;
			++i )
	{
		if ( (i->first)->isAKindOf< vgd::node::Shape >() )
		{
			const float opacityDiff = fabs( engine->getGLState().getOpacity() - 1.f );

			if ( opacityDiff < vgm::Epsilon<float>::value() )
			{
				// object is opaque, draw it.
				engine->evaluate( service, i->first, i->second );
			}
			else
			{
				m_mustDoTransparencyPass = true;
			}
		}
		else
		{
			engine->evaluate( service, i->first, i->second );
		}
	}

	// @todo
	engine->pop();
	/*glPopAttrib();
	engine->popStateStack();
	engine->getGLStateStack().pop();
	engine->getGLSLStateStack().pop();*/
	//
}



const bool Opaque::mustDoTransparencyPass() const
{
	return m_mustDoTransparencyPass;
}



} // namespace pass

} // namespace vgeGL
