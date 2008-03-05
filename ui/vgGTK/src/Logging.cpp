// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgGTK/Logging.hpp"

#include <glib.h>
#include <stdarg.h>
#include <stdio.h>



namespace vgGTK
{



void Logging::logFatalError( const char *szFormat, ... ) const
{
	va_list marker;
	va_start( marker, szFormat );

	g_logv( G_LOG_DOMAIN, (GLogLevelFlags) (G_LOG_LEVEL_ERROR|G_LOG_FLAG_FATAL), szFormat, marker );

	va_end( marker );
}



void Logging::logError( const char *szFormat, ... ) const
{
	va_list marker;
	va_start( marker, szFormat );

	g_logv( G_LOG_DOMAIN, G_LOG_LEVEL_ERROR, szFormat, marker );

	va_end( marker );
}



void Logging::logWarning( const char *szFormat, ... ) const
{
	va_list marker;
	va_start( marker, szFormat );

	g_logv( G_LOG_DOMAIN, G_LOG_LEVEL_WARNING, szFormat, marker );

	va_end( marker );
}



void Logging::logMessage( const char *szFormat, ... ) const
{
	va_list marker;
	va_start( marker, szFormat );

	g_logv( G_LOG_DOMAIN, G_LOG_LEVEL_MESSAGE, szFormat, marker );

	va_end( marker );
}



void Logging::logVerbose( const char *szFormat, ... ) const
{
	va_list marker;
	va_start( marker, szFormat );

	g_logv( G_LOG_DOMAIN, G_LOG_LEVEL_INFO, szFormat, marker );

	va_end( marker );
}



void Logging::logStatus( const char *szFormat, ... ) const
{
	va_list marker;
	va_start( marker, szFormat );

	g_logv( G_LOG_DOMAIN, G_LOG_LEVEL_INFO, szFormat, marker );

	va_end( marker );
}



void Logging::logSysError( const char *szFormat, ... ) const
{
	va_list marker;
	va_start( marker, szFormat );

	g_logv( G_LOG_DOMAIN, G_LOG_LEVEL_ERROR, szFormat, marker );

	va_end( marker );
}



void Logging::logDebug( const char *szFormat, ... ) const
{
	va_list marker;
	va_start( marker, szFormat );

	g_logv( G_LOG_DOMAIN, G_LOG_LEVEL_DEBUG, szFormat, marker );

	va_end( marker );
}



void Logging::logTrace( const char *szFormat, ... ) const
{
	va_list marker;
	va_start( marker, szFormat );

	g_logv( G_LOG_DOMAIN, G_LOG_LEVEL_DEBUG, szFormat, marker );

	va_end( marker );
}



void Logging::flush() const
{
	// Nothing to do here.
}



} // namespace vgGTK
