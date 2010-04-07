// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_REGISTERNODE_HPP
#define _VGD_BASIC_REGISTERNODE_HPP

#include "vgd/vgd.hpp"



namespace vgd
{
	
namespace basic
{



/**
 * @brief Register a node in a ClassRegistry.
 * 
 * @remarks Class to register must have a method VGD_API static vgd::basic::ClassRegistry& classType::getClassRegistry( void );
 * 
 * @todo Improve errors handling.
 */
template< typename classType >
struct RegisterNode
{
	/**
	 * @brief Constructor to register a node.
	 */	
	RegisterNode()
	{
		// Register the new node in ClassRegistry. This instance of node is managed(deleted) by the registry.
 		vgd::Shp< classType > shpClass(	classType::createWhole() );

		const bool retVal = classType::getClassRegistry().template add<classType>( shpClass );
		assert( retVal );
	}
	
	/**
	 * 
	 * @brief Specialized constructor to register a multi attribute node.
	 * 
	 * @param index		multi attribute index of the node to register.
	 */	
	RegisterNode( const int8 index )
	{
		// Register the new node in ClassRegistry. This instance of node is managed(deleted) by the registry.
		vgd::Shp< classType > shpClass(	classType::createWhole()	);
		shpClass->setMultiAttributeIndex( index );

		const bool retVal = classType::getClassRegistry().template add<classType>( shpClass );
		assert( retVal );
	}
};



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_REGISTERNODE_HPP
