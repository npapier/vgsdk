// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGDEBUG_ILOGGING_H
#define _VGDEBUG_ILOGGING_H

#include "vgDebug/vgDebug.hpp"



namespace vgDebug
{

/**
 * @brief Defines interface for logging facilities.
 */
struct VGDEBUG_API ILogging
{
	/**
	 * @brief Virtual destructor.
	 */
	virtual ~ILogging();
	
	/**
	 * @name Logging facilities methods.
	 */
	//@{
	virtual void logFatalError	( const char *szFormat, ... ) const=0;
	virtual void logError		( const char *szFormat, ... ) const=0;
	virtual void logWarning		( const char *szFormat, ... ) const=0;
	virtual void logMessage		( const char *szFormat, ... ) const=0;

	virtual void logVerbose		( const char *szFormat, ... ) const=0;
	virtual void logStatus		( const char *szFormat, ... ) const=0;

	virtual void logSysError	( const char *szFormat, ... ) const=0;

	virtual void logDebug		( const char *szFormat, ... ) const=0;
	virtual void logTrace		( const char *szFormat, ... ) const=0;

	virtual void flush			() const=0;
	//@}
};



} // namespace vgDebug

#endif // #ifndef _VGDEBUG_ILOGGING_H
