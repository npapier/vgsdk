//// VGSDK - Copyright (C) 2008, 2010, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_RC_TSYNCANDBINDHELPER_HPP
//#define _VGEGLBASE_RC_TSYNCANDBINDHELPER_HPP
//
//#include <vgd/field/DirtyFlag.hpp>
//#include <vge/rc/TManager.hpp>
//
//#include "vgeGL/engine/Engine.hpp"
//
//
//
//namespace vgeGL
//{
//
//namespace rc
//{
//
///**
// * @brief Helper used in vgeGL::handler::painter::Node::apply(...) in order to simplify the code of this method.
// *
// * @todo Comments
// *
// * Use dirty flag of the node (vgd::Node::getDFNode()).
// * @remarks The handlerType must implements :
// * - void synchronize	( vgeGL::engine::Engine* engine, nodeType* node, GLResourceType* pGLResource );
// */
//template< typename nodeType, typename handlerType, typename GLResourceType >
//void applyUsingSyncAndBind(	vgeGL::engine::Engine * engine, nodeType * node,
//							handlerType * handler )
//{
//	// Gets the resource manager
//	vgeGL::engine::Engine::GLManagerType& manager = engine->getGLManager();
//
//	// Gets node dirty flag
//	vgd::field::DirtyFlag * nodeDF = node->getDirtyFlag( node->getDFNode() );
//
//	// Gets resource associated to the given node
//	::glo::IResource 	* resource			= manager.getAbstract( node );
//	GLResourceType		* castedResource	= dynamic_cast< GLResourceType * >(resource);
//
//	// Sometimes GLResourceType must be changed for a given node (display list to/from vbo for example).
//	// is it the case now ?
//	if ( ( castedResource == 0 ) && ( resource != 0 ) )
//	{
//		// There is a resource, but not with the expected type.
//		// Dynamic change of handler ? or node that must be process differently (static, dynamic for VertexShape) ?
//
//		// Removes the resource from the manager
//		manager.remove( node );
//		resource = 0;
//		assert( (resource == 0) && (castedResource==0) && "Internal error." );
//	}
//	// else if resource != 0 && castedResource != 0 => nothing to do
//	// else if resource == 0 && castedResource == 0 => nothing to do
//	// else if resource == 0 && castedResource != 0 => impossible
//
//	assert(	(resource==0 && castedResource==0) ||
//			(resource!=0 && castedResource!=0) && "Internal error." );
//
//	// Creates resource if needed
//	if ( resource == 0 )
//	{
//		assert( castedResource == 0 && "Internal error." );
//
//		// Creates the resource
//		castedResource = new GLResourceType();
//		resource = castedResource;
//
//		// Adds the resource to the manager
//		manager.add( node, castedResource );
//	}
//	// else nothing to do
//
//	assert(	resource!=0 && castedResource!=0 && "Internal error." );
//
//	// What else ? synchronization and/or binding part of the work
//	if ( nodeDF->isDirty() )
//	{
//		// Node has been invalidated
//
//		// Binds the resource
//		handler->bind( engine, node, castedResource );
//
//		// Updates resource
//		handler->synchronize( engine, node, castedResource );
//
//		// Checks if synchronize() method have validated the node dirty flag
//		// assert( nodeDF->isValid() );	not always validated by synchronize, so don't check
//	}
//	else
//	{
//		// No modifications in the node
//
//		// Binds the resource
//		handler->bind( engine, node, castedResource );
//	}
//}
//
//
//
//} // namespace rc
//
//} // namespace vgeGL
//
//#endif //#ifndef _VGEGLBASE_RC_TSYNCANDBINDHELPER_HPP
//