// VGSDK - Copyright (C) 2004, 2010, 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_RC_TSYNCHRONIZEHELPER_HPP
#define _VGEGL_RC_TSYNCHRONIZEHELPER_HPP

#include <vgd/field/DirtyFlag.hpp>

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
 * - void synchronize( vgeGL::engine::Engine* engine, nodeType* node, GLResourceType* rc );
 */
template< typename GLResourceType, typename nodeType, typename handlerType >
void applyUsingSynchronize(	vgeGL::engine::Engine*	engine, nodeType* node,
							handlerType*			handler )
{
	// CREATE/RETRIEVE THE RESOURCE

	// get the resource manager
	using vgeGL::engine::Engine;
	vgd::Shp< Engine::GLManagerType > rGLManager = engine->getGLManager();

	// get associated resource
	::glo::IResource 	*pResource			= rGLManager->getAbstract( node );
	GLResourceType		*pCastedResource	= dynamic_cast< GLResourceType* >(pResource);

	/*if ( pResource && ( pCastedResource == 0 ) )
	{
		// There is a resource, but not of the expected type
		// Dynamic change of handler ?
		// or node that must be process differently (static, dynamic for VertexShape).
		rGLManager->remove( node );
		pResource			= 0;
	}*/

#ifdef _DEBUG
	vgAssert(	(pResource==0 && pCastedResource==0) ||
				(pResource!=0 && pCastedResource!=0)	);
#endif

	//bool callSynchronize;

	if ( pCastedResource == 0 )		// No resource
	{
		// Creates the resource
		pCastedResource = new GLResourceType();

		// Registers node and its resource into manager
		rGLManager->add( node, pCastedResource );

		// RC must be initialized
		//callSynchronize = true;
	}
	/*else
	{
		// reuse the resource

		// Updates RC ?
// @todo customization point
		//vgd::field::DirtyFlag * pDFNode = node->getDirtyFlag( node->getDFNode() );
		//callSynchronize = pDFNode->isDirty();
		//callSynchronize = true;
	}*/

	// UPDATE RC ?
	//if ( callSynchronize )
	//{
		handler->synchronize( engine, node, pCastedResource );
	//}
	// else nothing to do
}



} // namespace rc

} // namespace vgeGL

#endif //#ifndef _VGEGL_RC_TSYNCHRONIZEHELPER_HPP
