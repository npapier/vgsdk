// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGDEBUG_CONVENIENCE_HPP
#define _VGDEBUG_CONVENIENCE_HPP

#include "vgDebug/Global.hpp"

///@todo Disables some log function in debug
///@todo Completes vgX mapping to vgDebug::get().X()

#define vgLogError( text )		vgDebug::get().logError( (text) )
#define vgLogWarning( text )	vgDebug::get().logWarning( (text) )
#define vgLogDebug( text )		vgDebug::get().logDebug( (text) )

#endif //#ifndef _VGDEBUG_CONVENIENCE_HPP
