// VGSDK - Copyright (C) 2008, 2012, Clément Forest, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Clément Forest

#ifndef _VGQT_LOGGING_HPP
#define _VGQT_LOGGING_HPP

#include <sbf/log/ILogging.hpp>

#include "vgQt/vgQt.hpp"



namespace vgQt
{

/**
 * @brief Implements a logging facility based on Qt message logs.
 */
struct VGQT_API Logging : public sbf::log::ILogging
{
	/**
	 * @name Overrides
	 */
	//@{
	void logFatalError	( const char *szFormat, ... ) const;
	void logError		( const char *szFormat, ... ) const;
	void logWarning		( const char *szFormat, ... ) const;
	void logMessage		( const char *szFormat, ... ) const;

	void logVerbose		( const char *szFormat, ... ) const;
	void logStatus		( const char *szFormat, ... ) const;

	void logSysError	( const char *szFormat, ... ) const;

	void logDebug		( const char *szFormat, ...				) const;
	void logDebug		( const char *szFormat, va_list args	) const;
	void logTrace		( const char *szFormat, ... ) const;

	void flush			() const;
	//@}
};



} // namespace vgQT

#endif // #ifndef _VGQT_LOGGING_HPP
