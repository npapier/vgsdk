// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, Nicolas Papier and Clement Forest
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Clement Forest

#ifndef _VGDEBUG_HELPERS_HPP
#define _VGDEBUG_HELPERS_HPP

#include "vgDebug/vgDebug.hpp"

#include <sbf/debug/GlobalLogger.hpp>
#include <sbf/debug/ILogging.hpp>

namespace sbf { struct Module; }



///@todo Disables some log function in debug
///@todo Completes vgX mapping to vgDebug::get().X()

#define vgLogError( arg1, ... )						sbf::debug::get().logError( (arg1), __VA_ARGS__ )

#define vgLogWarning( arg1, ... )					sbf::debug::get().logWarning( (arg1), __VA_ARGS__ )

#define vgLogStatus( arg1, ... )					sbf::debug::get().logStatus( (arg1), __VA_ARGS__ )

#define vgLogMessage( arg1, ... )					sbf::debug::get().logMessage( (arg1), __VA_ARGS__ )

#ifdef _DEBUG
#define vgLogDebug( arg1, ... )						sbf::debug::get().logDebug( (arg1), __VA_ARGS__ )
#else
#define vgLogDebug( arg1, ... )						sbf::debug::get().logDebug( (arg1), __VA_ARGS__ )
#endif



#define vgAssert( expression )						sbf::debug::get().logAssert( (expression), "", (#expression), __FILE__, __LINE__ )
#define vgAssertN( expression, message, ... )		sbf::debug::get().logAssert( (expression), (message), (#expression), __FILE__, __LINE__, __VA_ARGS__ )



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
