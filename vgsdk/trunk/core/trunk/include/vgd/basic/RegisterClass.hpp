// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_REGISTERCLASS_HPP
#define _VGD_BASIC_REGISTERCLASS_HPP

#include "vgd/vgd.hpp"

#include "vgd/Shp.hpp"



namespace vgd
{
	
namespace basic
{



/**
 * @brief Register a class in a ClassRegistry.
 * 
 * @remarks Class to register must have a method VGD_API static vgd::basic::ClassRegistry& classType::getClassRegistry( void );
 */
template< typename classType >
struct RegisterClass
{
	/**
	 * @todo Improve errors handling.
	 */	
	RegisterClass()
	{
		// Register the new class in ClassRegistry. This instance of class is managed(deleted) by the registry.
		vgd::Shp< classType > shpClass(	new classType );

		bool retVal;
		retVal = classType::getClassRegistry().add( shpClass );
		assert( retVal );
	}
};



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_REGISTERCLASS_HPP
