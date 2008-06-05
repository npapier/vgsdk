// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGDEBUG_CONVENIENCE_HPP
#define _VGDEBUG_CONVENIENCE_HPP

#include "vgDebug/Global.hpp"

///@todo Disables some log function in debug
///@todo Completes vgX mapping to vgDebug::get().X()

#define vgLogError( arg1 )				vgDebug::get().logError( (arg1) )
#define vgLogError2( arg1, arg2 )		vgDebug::get().logError( (arg1), (arg2) )
#define vgLogWarning( arg1 )			vgDebug::get().logWarning( (arg1) )
#define vgLogWarning2( arg1, arg2 )		vgDebug::get().logWarning( (arg1), (arg2) )
#define vgLogDebug( arg1 )				vgDebug::get().logDebug( (arg1) )
#define vgLogDebug2( arg1, arg2 )		vgDebug::get().logDebug( (arg1), (arg2) )

#endif //#ifndef _VGDEBUG_CONVENIENCE_HPP
