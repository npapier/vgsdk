// VGSDK - Copyright (C) 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_DETAIL_NODE_HPP
#define _VGD_NODE_DETAIL_NODE_HPP

#include "vgd/Shp.hpp"
#include "vgd/basic/ClassRegistry.hpp"
#include "vgd/field/DirtyFlag.hpp"
#include "vgd/field/TAccessors.hpp"
#include "vgd/graph/Graph.hpp"

/**
 * @brief Meta helpers.
 */
#define META_NODE_CPP( nodeType )	vgd::Shp< nodeType > nodeType::create( const std::string nodeName )	\
{																										\
	/* Creates a new node */																			\
	vgd::Shp< nodeType > node( new nodeType(nodeName) );												\
																										\
	/* Adds a vertex (i.e. a node) to boost::graph */ 													\
	graph().addNode( node );																			\
																										\
	/* Sets fields to their default values */															\
	node->setToDefaults();																				\
																										\
	return node;																						\
}																										\
																										\
vgd::Shp< nodeType > nodeType::createWhole( const std::string nodeName )								\
{																										\
	/* Creates a new node */																			\
	vgd::Shp< nodeType > node = nodeType::create(nodeName);												\
																										\
	/* Sets optional fields to their default values */													\
	node->setOptionalsToDefaults();																		\
																										\
	return node;																						\
}																										\
																										\
IMPLEMENT_INDEXABLE_CLASS_CPP( , nodeType );															\
																										\
const vgd::basic::RegisterNode<nodeType> nodeType::m_registrationInstance;

/** 
 * @namespace vgd::node::detail
 * 
 * @brief Used internally by node (and derived) implementation.
 */

#endif //#ifndef _VGD_NODE_DETAIL_NODE_HPP
