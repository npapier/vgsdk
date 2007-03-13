// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_REGISTERHANDLER_H
#define _VGE_HANDLER_REGISTERHANDLER_H

#include "vge/vge.hpp"

#include "vge/handler/Handler.hpp"



namespace vge
{

namespace handler
{



/**
 * @brief Register a handler in the handler registry.
 * 
 * @remarks Class to register must have a method VGE_API static vgd::basic::ClassRegistry& classType::getClassRegistry( void );
 */
template< typename handler >
struct RegisterHandler
{
	/**
	 * @todo Improve errors handling.
	 */
	RegisterHandler()
	{
		// Register the new class in ClassRegistry. This instance of handler is managed(deleted) by the registry.
		handler *pHandler = new handler;
		bool retVal;
		retVal = handler::getClassRegistry().add( pHandler );
		assert( retVal );
	}
};



} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_REGISTERHANDLER_H
