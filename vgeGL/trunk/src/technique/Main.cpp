// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/Main.hpp"

#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgd/node/Kit.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Shape.hpp>
#include <vge/engine/Engine.hpp>
#include <vge/service/Painter.hpp>



namespace vgeGL
{

namespace technique
{



void Main::apply(	vge::engine::Engine *pEngine, vge::visitor::TraverseElementVector* pTraverseElements )
{
	vgd::Shp< vge::service::Service > paint = vge::service::Painter::create();

	prepareEval();
	//pEngine->resetEval();

	// First pass : draw opaque shape.
	beginPass();
	glPushAttrib( GL_ALL_ATTRIB_BITS );

	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = pTraverseElements->begin(), iEnd = pTraverseElements->end();
			i != iEnd;
			++i )
	{
		if ( (i->first)->isAKindOf< vgd::node::Shape >() )
		{
			vgd::node::Material *pMaterial( pEngine->getStateStackTop<vgd::node::Material>() );
			assert( pMaterial != 0 );

			if ( pMaterial->getTransparency() == 1.f )
			{
				// object is opaque, draw it.
				pEngine->evaluate( paint, i->first, i->second );
			}
			// nothing to do for transparent object.
		}
		else
		{
			pEngine->evaluate( paint, i->first, i->second );
		}
	}

	glPopAttrib();
	endPass();



	// Second pass : draw transparent shape.
	beginPass();
	pEngine->disregardIfIsA< vgd::node::ClearFrameBuffer >();
	glPushAttrib( GL_ALL_ATTRIB_BITS );
	
	pEngine->resetEval();
	
	for(	i = pTraverseElements->begin(), iEnd = pTraverseElements->end();
			i != iEnd;
			++i )
	{
		if ( (i->first)->isAKindOf< vgd::node::Kit >() )
		{
			// nothing to do for nodekit in transparent pass. FIXME ??????????????????????????????????????????????????
		}
		else if ( (i->first)->isAKindOf< vgd::node::Shape >() )
		{
			vgd::node::Material *pMaterial( pEngine->getStateStackTop<vgd::node::Material>() );
			assert( pMaterial != 0 );

			if ( pMaterial->getTransparency() < 1.f )
			{
				// object is transparent, draw it.
				glPushAttrib( GL_ALL_ATTRIB_BITS );					
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA,GL_ONE);
				glDepthMask(GL_FALSE);	
				pEngine->evaluate( paint, i->first, i->second );
				glPopAttrib();
			}
			// nothing to do for opaque object.
		}
		else
		{
			pEngine->evaluate( paint, i->first, i->second );
		}
	}
	
	glPopAttrib();
	pEngine->regardIfIsA< vgd::node::ClearFrameBuffer >();
	endPass();
	
	//
	finishEval();
}


//
//
//
//
///*
//BeginFirstPass(); reset*();
//EndFirstPass();
//For an active technique, this method is invoked after the traversal of the scene graph. The changes made in "preparePass()" should be undone here
//
//
//
//	engine();
//	nodes();
//	
//	vge::engine::Engine&										m_engine;
//	vge::visitor::NodeCollectorExtended<Visitors>&	m_collector
//	
//
//
//MainTechnique()
//{
//	reset();
//	
//	CollectNodes();
//
//	Begin();
//	
//	BeginFirstPass();
//	for_each();
//	EndFirstPass(); disregard();
//
//	BeginNextPass( push true); resetState(); resetMatrix();
//	for_each();
//	EndNextPass();
//	
//	End(); regard();



} // namespace technique

} // namespace vgeGL
