// VGSDK - Copyright (C) 2004, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgDebug/Logging.hpp"

#include <stdio.h>
#include <stdarg.h>



namespace vgDebug
{



void Logging::logFatalError( const char *szFormat, ... ) const
{
	va_list marker;
	va_start( marker, szFormat );

	fprintf( stderr, "Fatal Error. " );
	fprintf( stderr, szFormat, marker );
	fprintf( stderr, "\n" );

	va_end( marker );
}



void Logging::logError( const char *szFormat, ... ) const
{
	va_list marker;
	va_start( marker, szFormat );

	fprintf( stderr, "Error. " );
	fprintf( stderr, szFormat, marker );
	fprintf( stderr, "\n" );

	va_end( marker );
}



void Logging::logWarning( const char *szFormat, ... ) const
{
	va_list marker;
	va_start( marker, szFormat );

	fprintf( stderr, "Warning. " );
	fprintf( stderr, szFormat, marker );
	fprintf( stderr, "\n" );

	va_end( marker );
}



void Logging::logMessage( const char *szFormat, ... ) const
{
	va_list marker;
	va_start( marker, szFormat );

	fprintf( stdout, szFormat, marker );
	fprintf( stdout, "\n" );

	va_end( marker );
}



void Logging::logVerbose( const char *szFormat, ... ) const
{

#ifdef _DEBUG
	va_list marker;
	va_start( marker, szFormat );

	fprintf( stdout, szFormat, marker );
	fprintf( stdout, "\n" );

	va_end( marker );
#endif

}



void Logging::logStatus( const char *szFormat, ... ) const
{
	va_list marker;
	va_start( marker, szFormat );

	fprintf( stdout, szFormat, marker );
	fprintf( stdout, "\n" );

	va_end( marker );
}



void Logging::logSysError( const char *szFormat, ... ) const
{
	va_list marker;
	va_start( marker, szFormat );

	fprintf( stderr, "Sys Error. " );
	fprintf( stderr, szFormat, marker );
	fprintf( stderr, "\n" );

	va_end( marker );
}




void Logging::logDebug( const char *szFormat, ... ) const
{

#ifdef _DEBUG
	va_list marker;
	va_start( marker, szFormat );

	fprintf( stderr, "Debug. " );
	fprintf( stderr, szFormat, marker );
	fprintf( stderr, "\n" );

	va_end( marker );
#endif

}



void Logging::logTrace( const char *szFormat, ... ) const
{

#ifdef _DEBUG
	va_list marker;
	va_start( marker, szFormat );

	fprintf( stderr, "Trace. " );
	fprintf( stderr, szFormat, marker );
	fprintf( stderr, "\n" );

	va_end( marker );
#endif

}



void Logging::flush() const
{
	fflush( stdout );
	fflush( stderr );
}



} // namespace vgDebug
