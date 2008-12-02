// VGSDK - Copyright (C) 2004, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGDEBUG_LOGGING_HPP
#define _VGDEBUG_LOGGING_HPP

#include "vgDebug/ILogging.hpp"



namespace vgDebug
{



/**
 * @brief Implements logging interface based on standard outputs.
 */
struct VGDEBUG_API Logging : public ILogging
{
	/**
	 * @name Logging facilities methods
	 */
	//@{
	void logFatalError	( const char *szFormat, ... ) const;
	void logError		( const char *szFormat, ... ) const;
	void logWarning		( const char *szFormat, ... ) const;
	void logMessage		( const char *szFormat, ... ) const;

	void logVerbose		( const char *szFormat, ... ) const;
	void logStatus		( const char *szFormat, ... ) const;

	void logSysError	( const char *szFormat, ... ) const;

	void logDebug		( const char *szFormat, ... ) const;
	void logTrace		( const char *szFormat, ... ) const;

	void flush			() const;
	//@}
};



} // namespace vgDebug

#endif // #ifndef _VGDEBUG_LOGGING_HPP
