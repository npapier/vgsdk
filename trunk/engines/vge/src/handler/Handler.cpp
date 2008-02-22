// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/Handler.hpp"



namespace vge
{

namespace handler
{



HandlerRegistry& Handler::getClassRegistry( void )
{
	static HandlerRegistry handlerRegistry;

	return ( handlerRegistry );
}


	
} // namespace handler

} // namespace vge
