// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/Outlining.hpp"

#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/Kit.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Shape.hpp>
#include <vge/engine/Engine.hpp>
#include <vge/service/Painter.hpp>



namespace vgeGL
{

namespace technique
{



Outlining::Outlining( const vgm::Vec3f diffuseColor, const float width ) :
	m_diffuseColor	(	diffuseColor	),
	m_width			(	width				)
{
}


	
/**
 * outline algorithm :
 * 
 * glClearStencil(0);
 * glClear(GL_STENCIL_BUFFER_BIT);
 * 
 * // Render the mesh into the stencil buffer.
 * 
 * glEnable(GL_STENCIL_TEST);
 * 
 * glStencilFunc(GL_ALWAYS, 1, -1);
 * glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
 * 
 * RenderMesh();
 * 
 * // Render the thick wireframe version.
 * glStencilFunc(GL_NOTEQUAL, 1, -1);
 * glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
 * 
 * glLineWidth(3);
 * glPolygonMode(GL_FRONT, GL_LINE);
 * RenderMesh();
 */
void Outlining::apply(	vge::engine::Engine *pEngine, vge::visitor::TraverseElementVector* pTraverseElements )
{
	vgd::Shp< vge::service::Service > paint = vge::service::Painter::create();

	prepareEval();
	pEngine->resetEval();

	// First pass : Render the mesh into the stencil buffer (=>fill stencil buffer).
	beginPass();
	glPushAttrib( GL_ALL_ATTRIB_BITS );

	// FIXME add all disregard/regard.
	pEngine->disregardIfIsA< vgd::node::ClearFrameBuffer >();
	
	//
	glClearStencil( 0 );
	glClear( GL_STENCIL_BUFFER_BIT );
	
	glStencilFunc(GL_ALWAYS, 1, -1); // static_cast<GLuint>( ????????????????????????????????????????????????????????????
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	// first pass must change only stencil buffer.
	glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );
	glDepthMask( GL_FALSE );

	// render scene
	vgd::node::Node *pCurrentKit = 0;			// FIXME must be improved for nested Kit.
	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = pTraverseElements->begin(), iEnd = pTraverseElements->end();
			i != iEnd;
			++i )
	{
		if ( (i->first)->isAKindOf< vgd::node::Kit >() )
		{
			if (i->second)
			{
				// preTraverse
				vgd::node::PNodeSet::const_iterator iter;
				iter = getNodes().find( i->first );
				
				if ( iter != getNodes().end() )
				{
					pCurrentKit = i->first;
				}
			}
			else
			{
				// postTraverse
				pCurrentKit = 0;
			}
		}
		else if ( (i->first)->isAKindOf< vgd::node::Shape >()	)
		{
			// 'render in stencil' only if the current node must be outlined in the 2 pass, i.e. current node is inside 
			// getNodes() or is owned by a Kit.
			vgd::node::PNodeSet::const_iterator iter;
			iter = getNodes().find( i->first );
			if (	(iter != getNodes().end()) ||
					(pCurrentKit != 0) )
			{
				//glDepthFunc( GL_EQUAL );
				glEnable( GL_STENCIL_TEST );
				glDisable( GL_DEPTH_TEST );
				pEngine->evaluate( paint, i->first, i->second );
			}
		}
		else
		{
			pEngine->evaluate( paint, i->first, i->second );
		}
	}

	glPopAttrib();
	endPass();
	
	// Second pass : Render the thick wireframe version (use stencil buffer).
	beginPass();
	pEngine->disregardIfIsA< vgd::node::ClearFrameBuffer >();
	glPushAttrib( GL_ALL_ATTRIB_BITS );
	
	pEngine->resetEval();
	
	//	
	glStencilFunc(GL_NOTEQUAL, 1, -1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	vgd::Shp< vgd::node::DrawStyle > drawStyle = vgd::node::DrawStyle::create("drawStyleForOutlining");
	drawStyle->setShape( vgd::node::DrawStyle::WIREFRAME );
	pEngine->evaluate( paint, drawStyle.get(), true );
	
	// sets diffuse color of outline
	vgd::Shp< vgd::node::Material > material = vgd::node::Material::create("materialForOutlining");
	material->setColor( vgd::node::Material::DIFFUSE, getDiffuseColor() );
	pEngine->evaluate( paint, material.get(), true );
	
	pEngine->disregardIfIsA< vgd::node::DrawStyle >();	
	pEngine->disregardIfIsA< vgd::node::Material >();

	// render scene
	for(	i = pTraverseElements->begin(), iEnd = pTraverseElements->end();
			i != iEnd;
			++i )
	{
		if ( (i->first)->isAKindOf< vgd::node::Kit >() )
		{
			if (i->second)
			{
				// preTraverse
				vgd::node::PNodeSet::const_iterator iter;
				iter = getNodes().find( i->first );
				
				if ( iter != getNodes().end() )
				{
					pCurrentKit = i->first;
				}
			}
			else
			{
				// postTraverse
				pCurrentKit = 0;
			}
		}
		else if ( (i->first)->isAKindOf< vgd::node::Shape >() )
		{
			// render outline only, i.e. current node is inside getNodes() or is owned by a Kit.
			vgd::node::PNodeSet::const_iterator iter;
			iter = getNodes().find( i->first );
			if (	(iter != getNodes().end()) ||
					(pCurrentKit != 0) )
			{
				// sets width of outline
				glLineWidth( getWidth() ); // FIXME check max width() and min;
				glDisable( GL_LIGHTING );
				glDisable( GL_DEPTH_TEST );
				glEnable( GL_LINE_SMOOTH );// FIXME should be an option
				
				glEnable( GL_STENCIL_TEST );

				pEngine->evaluate( paint, i->first, i->second );
			}
		}
		else
		{
			pEngine->evaluate( paint, i->first, i->second );
		}
	}
	
	glPopAttrib();
	endPass();
	
	pEngine->regard();
		
	//
	finishEval();
}


//// vgeGL::OutliningTechnique
//
///*
//resetEngine();
//	engine()->resetStateStack();
//	engine()->resetMatrices();
//---
//prepareEval();			collectNodes();
//
//     glClearStencil(0);
//     glClear(GL_STENCIL_BUFFER_BIT);
//
//beginPass( FIRST_PASS, PUSH );
//   
//     // Render the mesh into the stencil buffer.
//     glEnable(GL_STENCIL_TEST);
//
//     glStencilFunc(GL_ALWAYS, 1, -1);
//     glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//
//	for_each();      RenderMesh();
//
//endPass( ###IMPLICIT FIRST_PASS### , POP );
//
//     // Render the thick wireframe version.
//
//     glStencilFunc(GL_NOTEQUAL, 1, -1);
//     glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//
//     glLineWidth(3);
//     glPolygonMode(GL_FRONT, GL_LINE);
//
//beginPass( NEXT_PASS, NONE );
//	
//     RenderMesh();
//     
//endPass( ### IMPLICIT x PASS###, NONE );
//
//finishEval(); regard( ALL );
//---*/




} // namespace technique

} // namespace vgeGL
