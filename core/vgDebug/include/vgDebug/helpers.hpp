// VGSDK - Copyright (C) 2008, 2009, 2010, Nicolas Papier and Clement Forest
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Clement Forest

#ifndef _VGDEBUG_HELPERS_HPP
#define _VGDEBUG_HELPERS_HPP

#include "vgDebug/Global.hpp"

namespace sbf { struct Module; }



///@todo Disables some log function in debug
///@todo Completes vgX mapping to vgDebug::get().X()

#define vgLogError( arg1 )						vgDebug::get().logError( (arg1) )
#define vgLogError2( arg1, arg2 )				vgDebug::get().logError( (arg1), (arg2) )
#define vgLogError3( arg1, arg2, arg3 )			vgDebug::get().logError( (arg1), (arg2), (arg3) )

#define vgLogWarning( arg1 )					vgDebug::get().logWarning( (arg1) )
#define vgLogWarning2( arg1, arg2 )				vgDebug::get().logWarning( (arg1), (arg2) )
#define vgLogWarning3( arg1, arg2, arg3 )		vgDebug::get().logWarning( (arg1), (arg2), (arg3) )

#define vgLogStatus( arg1 )						vgDebug::get().logStatus( (arg1) )
#define vgLogStatus2( arg1, arg2 )				vgDebug::get().logStatus( (arg1), (arg2) )
#define vgLogStatus3( arg1, arg2, arg3 )		vgDebug::get().logStatus( (arg1), (arg2), (arg3) )

#define vgLogMessage( arg1 )					vgDebug::get().logMessage( (arg1) )
#define vgLogMessage2( arg1, arg2 )				vgDebug::get().logMessage( (arg1), (arg2) )
#define vgLogMessage3( arg1, arg2, arg3 )		vgDebug::get().logMessage( (arg1), (arg2), (arg3) )

#ifdef _DEBUG
#define vgLogDebug( arg1 )						vgDebug::get().logDebug( (arg1) )
#define vgLogDebug2( arg1, arg2 )				vgDebug::get().logDebug( (arg1), (arg2) )
#define vgLogDebug3( arg1, arg2, arg3 )			vgDebug::get().logDebug( (arg1), (arg2), (arg3) )
#define vgLogDebug4( arg1, arg2, arg3, arg4 )	vgDebug::get().logDebug( (arg1), (arg2), (arg3), (arg4) )
#else
#define vgLogDebug( arg1 )						vgDebug::get().logDebug( (arg1) )
#define vgLogDebug2( arg1, arg2 )				vgDebug::get().logDebug( (arg1), (arg2) )
#define vgLogDebug3( arg1, arg2, arg3 )			vgDebug::get().logDebug( (arg1), (arg2), (arg3) )
#define vgLogDebug4( arg1, arg2, arg3, arg4 )	vgDebug::get().logDebug( (arg1), (arg2), (arg3), (arg4) )
#endif



namespace vgDebug
{

/**
 * @brief Methods for logging message.
 */
struct Log
{

/**
 * @brief Redirect standard output in a log-YYYY-MM-DD-HH-mm-ss.txt
 * file located in the var directory of the given module.
 */
static void VGDEBUG_API logStandardOutputs(const sbf::Module& module);


/**
 * @brief Redirect standard output in a log-YYYY-MM-DD-HH-mm-ss.txt file.
 */
static void VGDEBUG_API limitLogFileHistory( const int maxNumber );


/**
 * @brief Log basic info to log file (argument, initial directory, ...
 */
static void VGDEBUG_API logBasicInfo( int argc, char** argv, const sbf::Module& module );

};

} // namespace vgDebug



#endif //#ifndef _VGDEBUG_HELPERS_HPP
