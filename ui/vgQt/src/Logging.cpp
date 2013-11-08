// VGSDK - Copyright (C) 2008, 2012, 2013, Clément Forest, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Clément Forest

#include "vgQt/Logging.hpp"

#include <QDebug>
#include <QtDebug>
#include <QtGlobal>
#include <stdarg.h>
#include <stdio.h>



namespace
{

void qtLog( QtMsgType type, const char *szFormat, va_list args )
{
	QString result;
	result.vsprintf( szFormat, args );

	QDebug( type ) << result;
}

}


namespace vgQt
{



void Logging::logFatalError( const char *szFormat, ... ) const
{
	va_list args;
	va_start( args, szFormat );

	qtLog( QtFatalMsg, szFormat, args );

	va_end( args );
}



void Logging::logError( const char *szFormat, ... ) const
{
	va_list args;
	va_start( args, szFormat );

	qtLog( QtDebugMsg, szFormat, args );

	va_end( args );
}



void Logging::logWarning( const char *szFormat, ... ) const
{
	va_list args;
	va_start( args, szFormat );

	qtLog( QtWarningMsg, szFormat, args );

	va_end( args );
}



void Logging::logMessage( const char *szFormat, ... ) const
{
	va_list args;
	va_start( args, szFormat );

	qtLog( QtWarningMsg, szFormat, args );

	va_end( args );
}



void Logging::logVerbose( const char *szFormat, ... ) const
{
	va_list args;
	va_start( args, szFormat );

	qtLog( QtDebugMsg, szFormat, args );

	va_end( args );
}



void Logging::logStatus( const char *szFormat, ... ) const
{
	va_list args;
	va_start( args, szFormat );

	qtLog( QtDebugMsg, szFormat, args );

	va_end( args );
}



void Logging::logSysError( const char *szFormat, ... ) const
{
	va_list args;
	va_start( args, szFormat );

	qtLog( QtCriticalMsg, szFormat, args );

	va_end( args );
}



void Logging::logDebug( const char *szFormat, ... ) const
{
	va_list args;
	va_start( args, szFormat );

	logDebug( szFormat, args );

	va_end( args );
}



void Logging::logDebug( const char *szFormat, va_list args ) const
{
	qtLog( QtDebugMsg, szFormat, args );
}



void Logging::logTrace( const char *szFormat, ... ) const
{
	va_list args;
	va_start( args, szFormat );

	qtLog( QtDebugMsg, szFormat, args );

	va_end( args );
}



void Logging::flush() const
{
	// Nothing to do here.
}



} // namespace vgQt
