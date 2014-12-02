//// VGSDK - Copyright (C) 2004, 2008, 2009, 2010, 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_RC_TDISPLAYLISTHELPER_HPP
//#define _VGEGLBASE_RC_TDISPLAYLISTHELPER_HPP
//
//#include <vgd/field/DirtyFlag.hpp>
//
//#include "vgeGL/engine/Engine.hpp"
//#include "vgeGL/engine/Settings.hpp"
//#include "vgeGL/rc/DisplayList.hpp"
//
//
//
//namespace vgeGL
//{
//
//namespace rc
//{
//
//
//
///**
// * @brief Helper used in vgeGL::handler::NodePainter::apply(...) in order to simplify compiling OpenGL calls 
// * (for a node) in a single display list.
// *
// * @remarks vgeGL::handler::NodePainter must implements void paint( vgeGL::engine::Engine*, nodeType* );
// * 
// * @todo remove this assert(	(pResource==0 && pDisplayList==0) || (pResource!=0 && pDisplayList!=0)  ); for changing 
// * handler at runtime.
// */
//template< typename nodeType, typename handlerType >
//void applyUsingDisplayList(	vge::engine::Engine* pEngine, vgd::node::Node *pNode,
//							handlerType	*pHandler )
//{
//	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
//	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);
//
//	assert( dynamic_cast< nodeType* >(pNode) != 0 );
//	nodeType *pCastedNode = static_cast< nodeType* >(pNode);
//
//	vgd::Shp< vgeGL::engine::Engine::GLManagerType > rGLManager = pGLEngine->getGLManager();
//
//	// ****** Render ******
//	// get dirty flag of node
//	vgd::field::DirtyFlag	*pDF			= pCastedNode->getDirtyFlag( pCastedNode->getDFNode() );
//
//	// lookup the resource.
//	::glo::IResource 		*pResource		= rGLManager->getAbstract( pNode );
//	::glo::DisplayList		*pDisplayList	= dynamic_cast< ::glo::DisplayList* >(pResource);
//
//	// @todo relax
//	assert(	(pResource==0 && pDisplayList==0) ||
//			(pResource!=0 && pDisplayList!=0)		// (pResource!=0 && (pDisplayList!=0||==0) ) => rc type could be changed for a node (display list <=> vbo)
//				 );
//
//	// What to do ?
//	// USING DISPLAY LIST
//	if ( pGLEngine->isDisplayListEnabled() )
//	{
//		if ( pDF->isDirty() )
//		{
//			// Node has been modified
//			if ( pDisplayList != 0 )
//			{
//				// Found an associated resource, recycle it
//				pDisplayList->release();
//			}
//			else
//			{
//				// No resource (this is the first evaluation), creates a new one.
//				pDisplayList = new ::glo::DisplayList();
//				rGLManager->add( pNode, pDisplayList );
//			}
//
//			// Updates display lists.
//			pDisplayList->begin();
//
//			pHandler->paint( pGLEngine, pCastedNode );
//
//			bool bRetVal = pDisplayList->next();
//			assert( !bRetVal );
//
//			// render
//			pDisplayList->call();
//
//			// Validates node.
//			pDF->validate();
//		}
//		else
//		{
//			// No change in node.
//			if ( pDisplayList != 0 )
//			{
//				// Found an associated resource.
//
//				// render
//				pDisplayList->call();
//			}
//			else
//			{
//				// No resource, but already validate !!!
//				assert( false && "No resource, but already validate !!!" );
//			}
//		}
//	}
//	// WITHOUT USING DISPLAY LIST
//	else
//	{
//		pHandler->paint( pGLEngine, pCastedNode );
//	}
//}
//
//
//
//template< typename nodeType, typename handlerType, typename paintParamType >
//void applyUsingDisplayList(	vge::engine::Engine* pEngine, vgd::node::Node *pNode,
//							handlerType	*pHandler )
//{
//	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
//	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);
//
//	assert( dynamic_cast< nodeType* >(pNode) != 0 );
//	nodeType *pCastedNode = static_cast< nodeType* >(pNode);
//
//	vgd::Shp< vgeGL::engine::Engine::GLManagerType > rGLManager = pGLEngine->getGLManager();
//
//	// ****** Render ******
//	// get dirty flag of node
//	vgd::field::DirtyFlag	*pDF			= pCastedNode->getDirtyFlag( pCastedNode->getDFNode() );
//
//	// lookup the resource.
//	::glo::IResource 		*pResource		= rGLManager->getAbstract( pNode );
//	::glo::DisplayList		*pDisplayList	= dynamic_cast< ::glo::DisplayList* >(pResource);
//
//	assert(	(pResource==0 && pDisplayList==0) ||
//			(pResource!=0 && pDisplayList!=0)	 );
//	
//	// What to do ?
//	// USING DISPLAY LIST
//	if ( pGLEngine->isDisplayListEnabled() )
//	{
//		if ( pDF->isDirty() )
//		{
//			// Invalidate vertex shape.
//			if ( pDisplayList != 0 )
//			{
//				// Founded an associated resource, recycle it
//				pDisplayList->release();
//			}
//			else
//			{
//				// No resource (this is the first evaluation), create it.
//				pDisplayList = new ::glo::DisplayList();
//				rGLManager->add( pNode, pDisplayList );
//			}
//
//			// update display lists.
//			pDisplayList->begin();
//
//			paintParamType method;
//			pHandler->paint( pGLEngine, pCastedNode, method );
//
//			bool bRetVal = pDisplayList->next();
//			assert( !bRetVal );
//
//			// render
//			pDisplayList->call();
//			
//			// Validates vertex shape.
//			pDF->validate();
//		}
//		else
//		{
//			// No change in vertex shape.
//			if ( pDisplayList != 0 )
//			{
//				// Founded an associated resource.
//				
//				// render
//				pDisplayList->call();
//			}
//			else
//			{
//				// No resource, but already validate !!!
//				assert( false && "No resource, but already validate !!!" );
//			}
//		}
//	}
//	// WITHOUT USING DISPLAY LIST
//	else
//	{
//		paintParamType method;
//		pHandler->paint( pGLEngine, pCastedNode, method );
//	}
//}
//
//
//
//} // namespace rc
//
//} // namespace vgeGL
//
//#endif //#ifndef _VGEGLBASE_RC_TDISPLAYLISTHELPER_HPP
//