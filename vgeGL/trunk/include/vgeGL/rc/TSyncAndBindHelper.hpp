// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_RC_TSYNCANDBINDHELPER_H
#define _VGEGL_RC_TSYNCANDBINDHELPER_H

#include <vgd/field/DirtyFlag.hpp>
#include <vge/rc/Manager.hpp>

#include "vgeGL/vgeGL.hpp"
#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{
	
namespace rc
{

/**
 * @brief Helper used in vgeGL::handler::painter::Node::apply(...) in order to simplify the code of this method.
 * Use dirty flag of the node (vgd::Node::getDFNode()).
 *
 * @remarks The handlerType must implements :
 * - void synchronize	( vgeGL::engine::Engine* pGLEngine, nodeType* pNode, GLResourceType* pGLResource );
 * - void bind				( vgeGL::engine::Engine* pGLEngine, nodeType* pNode, GLResourceType* pGLResource );
 */
template< typename nodeType, typename handlerType, typename GLResourceType >
void applyUsingSyncAndBind(	vgeGL::engine::Engine*	pGLEngine, nodeType* pNode,
										handlerType*				pHandler
									 )
{
	// get the resource manager
	vge::rc::Manager&			rGLManager	= pGLEngine->getGLManager();

	// get dirty flag of node
	vgd::field::DirtyFlag*	pDFNode		= pNode->getDirtyFlag( pNode->getDFNode() );

	// get associated resource
	vge::rc::IResource 		*pResource;
	GLResourceType				*pCastedResource;

	// lookup the resource.
	pResource			= rGLManager.getAbstract( pNode );
	pCastedResource	= dynamic_cast< GLResourceType* >(pResource);
	
	if (	( pCastedResource == 0 ) &&
			( pResource != 0) )
	{
		// There is a resource, but not of the expected type.
		// Dynamic change of handler ?
		// or node that must be process differently (static, dynamic for VertexShape).
		rGLManager.remove( pNode );

		pResource			= 0;
	}

	assert(	(pResource==0 && pCastedResource==0) ||
				(pResource!=0 && pCastedResource!=0)
				 );

	// What to do ?
	if ( pDFNode->isDirty() )
	{
		// Node is invalidated.
		if ( pCastedResource == 0 )
		{
			// No resource (this is the first evaluation), create it.
			pCastedResource = new GLResourceType();
			rGLManager.add( pNode, pCastedResource );
		}
		// else have founded an associated resource, recycle it in synchronize().

		// update resource.
		pHandler->synchronize( pGLEngine, pNode, pCastedResource );
		pHandler->bind( pGLEngine, pNode, pCastedResource );
		
		// validate.
		pDFNode->validate();
	}
	else
	{
		// No change in node.
		if ( pCastedResource != 0 )
		{
			// Founded an associated resource and use it.
			pHandler->bind( pGLEngine, pNode, pCastedResource );
		}
		else
		{
			// No resource, but already validate !!!
			assert( false && "No resource, but already validate !!!" );
		}
	}
}



} // namespace rc

} // namespace vgeGL

#endif //#ifndef _VGEGL_RC_TSYNCANDBINDHELPER_H
