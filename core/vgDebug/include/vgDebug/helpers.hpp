// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, 2012, Nicolas Papier and Clement Forest
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Clement Forest
// Author Guillaume Brocker

#ifndef _VGDEBUG_HELPERS_HPP
#define _VGDEBUG_HELPERS_HPP

#include "vgDebug/vgDebug.hpp"

#include <sbf/log/GlobalLogger.hpp>
#include <sbf/log/ILogging.hpp>

namespace sbf { namespace pkg { struct Module; } }



///@todo Disables some log function in debug
///@todo Completes vgX mapping to vgDebug::get().X()

#define vgLogError( arg1, ... )						sbf::log::get().logError( (arg1), __VA_ARGS__ )

#define vgLogWarning( arg1, ... )					sbf::log::get().logWarning( (arg1), __VA_ARGS__ )

#define vgLogStatus( arg1, ... )					sbf::log::get().logStatus( (arg1), __VA_ARGS__ )

#define vgLogMessage( arg1, ... )					sbf::log::get().logMessage( (arg1), __VA_ARGS__ )

#ifdef _DEBUG
#define vgLogDebug( arg1, ... )						sbf::log::get().logDebug( (arg1), __VA_ARGS__ )
#else
#define vgLogDebug( arg1, ... )						sbf::log::get().logDebug( (arg1), __VA_ARGS__ )
#endif



#define vgAssert( expression )						sbf::log::get().logAssert( (expression), "", (#expression), __FILE__, __LINE__ )
#define vgAssertN( expression, message, ... )		(void)( (!!(expression)) || (sbf::log::get().logAssert( (expression), (message), (#expression), __FILE__, __LINE__, __VA_ARGS__ ), 0 ) )



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
static void VGDEBUG_API logStandardOutputs( boost::shared_ptr< sbf::pkg::Module > module );


/**
 * @brief Redirect standard output in a log-YYYY-MM-DD-HH-mm-ss.txt file.
 */
static void VGDEBUG_API limitLogFileHistory( const int maxNumber );


/**
 * @brief Log basic info to log file (argument, initial directory, ...
 */
static void VGDEBUG_API logBasicInfo( int argc, char** argv, boost::shared_ptr< sbf::pkg::Module > module );

};

} // namespace vgDebug



#endif //#ifndef _VGDEBUG_HELPERS_HPP
