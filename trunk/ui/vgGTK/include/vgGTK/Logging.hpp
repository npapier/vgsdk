// VGSDK - Copyright (C) 2008, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGGTK_LOGGING_HPP
#define _VGGTK_LOGGING_HPP

#include <sbf/debug/ILogging.hpp>

#include "vgGTK/vgGTK.hpp"



namespace vgGTK
{

/**
 * @brief Implements a logging facility based on GLib message logs.
 */
	struct VGGTK_API Logging : public sbf::debug::ILogging
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



} // namespace vgGTK

#endif // #ifndef _VGGTK_LOGGING_HPP
