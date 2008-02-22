// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_RC_TDISPLAYLISTHELPER_HPP
#define _VGEGL_RC_TDISPLAYLISTHELPER_HPP

#include <vgd/field/DirtyFlag.hpp>
#include <vge/rc/Manager.hpp>

#include "vgeGL/vgeGL.hpp"
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/Settings.hpp"
#include "vgeGL/rc/DisplayList.hpp"



namespace vgeGL
{
	
namespace rc
{



/**
 * @brief Helper used in vgeGL::handler::NodePainter::apply(...) in order to simplify compiling OpenGL calls 
 * (for a node) in a single display list.
 *
 * @remarks vgeGL::handler::NodePainter must implements void paint( vgeGL::engine::Engine*, nodeType* );
 * 
 * @todo remove this assert(	(pResource==0 && pDisplayList==0) || (pResource!=0 && pDisplayList!=0)  ); for changing 
 * handler at runtime.
 */
template< typename nodeType, typename handlerType >
void applyUsingDisplayList(	vge::engine::Engine* pEngine, vgd::node::Node *pNode,
										handlerType	*pHandler
									 )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	assert( dynamic_cast< nodeType* >(pNode) != 0 );
	nodeType *pCastedNode = static_cast< nodeType* >(pNode);

	vge::rc::Manager& rGLManager = pGLEngine->getGLManager();

	// ****** Render ******
	vgd::field::DirtyFlag	*pDF;
	
	vge::rc::IResource 		*pResource;
	vgeGL::rc::DisplayList	*pDisplayList;

	// get dirty flag of node
	pDF = pCastedNode->getDirtyFlag( pCastedNode->getDFNode() );

	// lookup the resource.
	pResource		= rGLManager.getAbstract( pNode );
	pDisplayList	= dynamic_cast< vgeGL::rc::DisplayList* >(pResource);

	assert(	(pResource==0 && pDisplayList==0) ||
				(pResource!=0 && pDisplayList!=0)
				 );
	
	// What to do ?
	if ( pDF->isDirty() )
	{
		// Invalidate vertex shape.
		if ( pDisplayList != 0 )
		{
			// Founded an associated resource, recycle it
			pDisplayList->release();
		}
		else
		{
			// No resource (this is the first evaluation), create it.
			pDisplayList = new vgeGL::rc::DisplayList();
			rGLManager.add( pNode, pDisplayList );
		}

		// update display lists.
		pDisplayList->begin();
	
		pHandler->paint( pGLEngine, pCastedNode );

		bool bRetVal;
		bRetVal = pDisplayList->next();
		assert( !bRetVal );
		
		// render
		pDisplayList->call();
		
		// validate vertex shape.
		pDF->validate();
	}
	else
	{
		// No change in vertex shape.
		if ( pDisplayList != 0 )
		{
			// Founded an associated resource.
			
			// render
			pDisplayList->call();
		}
		else
		{
			// No resource, but already validate !!!
			assert( false && "No resource, but already validate !!!" );
		}
	}
}



template< typename nodeType, typename handlerType, typename paintParamType >
void applyUsingDisplayList(	vge::engine::Engine* pEngine, vgd::node::Node *pNode,
										handlerType	*pHandler
									 )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	assert( dynamic_cast< nodeType* >(pNode) != 0 );
	nodeType *pCastedNode = static_cast< nodeType* >(pNode);

	vge::rc::Manager& rGLManager = pGLEngine->getGLManager();

	// ****** Render ******
	vgd::field::DirtyFlag	*pDF;
	
	vge::rc::IResource 		*pResource;
	vgeGL::rc::DisplayList	*pDisplayList;

	// get dirty flag of node
	pDF = pCastedNode->getDirtyFlag( pCastedNode->getDFNode() );

	// lookup the resource.
	pResource		= rGLManager.getAbstract( pNode );
	pDisplayList	= dynamic_cast< vgeGL::rc::DisplayList* >(pResource);

	assert(	(pResource==0 && pDisplayList==0) ||
				(pResource!=0 && pDisplayList!=0)
				 );
	
	// What to do ?
	if ( pDF->isDirty() )
	{
		// Invalidate vertex shape.
		if ( pDisplayList != 0 )
		{
			// Founded an associated resource, recycle it
			pDisplayList->release();
		}
		else
		{
			// No resource (this is the first evaluation), create it.
			pDisplayList = new vgeGL::rc::DisplayList();
			rGLManager.add( pNode, pDisplayList );
		}

		// update display lists.
		pDisplayList->begin();

		paintParamType method;
		pHandler->paint( pGLEngine, pCastedNode, method );

		bool bRetVal;
		bRetVal = pDisplayList->next();
		assert( !bRetVal );
		
		// render
		pDisplayList->call();
		
		// validate vertex shape.
		pDF->validate();
	}
	else
	{
		// No change in vertex shape.
		if ( pDisplayList != 0 )
		{
			// Founded an associated resource.
			
			// render
			pDisplayList->call();
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

#endif //#ifndef _VGEGL_RC_TDISPLAYLISTHELPER_HPP
