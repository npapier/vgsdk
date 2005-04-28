// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include <wx/defs.h>
#include <wx/log.h>

#include "vgDebug/Logging.hpp"



namespace vgDebug
{



Logging::Logging() :
	m_pLogger( new wxLogGui ) //wxLogChain(...) new wxLogGui() new wxLogStderr()
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);	
	
	logDebug("Create a new logger.");

	wxLog::SetActiveTarget(pLogBak);
}



Logging::~Logging()
{
	logDebug("Destroy a logger.");
	
	// Destroy logger.
	if ( m_pLogger != 0 )
	{
		wxLog *pLogBak = wxLog::SetActiveTarget(NULL);
		
		delete m_pLogger;

		if ( pLogBak != m_pLogger )
		{
			wxLog::SetActiveTarget( pLogBak );
		}
	}
}



void Logging::logFatalError( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	wxVLogFatalError( szFormat, marker );

	va_end( marker );

	wxLog::SetActiveTarget(pLogBak);
}



void Logging::logError( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	wxVLogError( szFormat, marker );

	va_end( marker );

	wxLog::SetActiveTarget(pLogBak);
}



void Logging::logWarning( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	wxVLogWarning( szFormat, marker );

	va_end( marker );

	wxLog::SetActiveTarget(pLogBak);
}



void Logging::logMessage( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	wxVLogMessage( szFormat, marker );

	va_end( marker );

	wxLog::SetActiveTarget(pLogBak);
}



void Logging::logVerbose( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	wxVLogVerbose( szFormat, marker );

	va_end( marker );
	
	wxLog::SetActiveTarget(pLogBak);
}



void Logging::logStatus( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	wxVLogStatus( szFormat, marker );

	va_end( marker );

	wxLog::SetActiveTarget(pLogBak);
}



void Logging::logSysError( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	wxVLogSysError( szFormat, marker );

	va_end( marker );

	wxLog::SetActiveTarget(pLogBak);
}




void Logging::logDebug( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	wxVLogDebug( szFormat, marker );

	va_end( marker );

	wxLog::SetActiveTarget(pLogBak);
}



void Logging::logTrace( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	// wxVLogTrace( szFormat, marker ); FIXME modified interface in wx2.5 and superior.
	wxVLogDebug( szFormat, marker );

	va_end( marker );

	wxLog::SetActiveTarget(pLogBak);
}



void Logging::flush() const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);

	m_pLogger->FlushActive();

	wxLog::SetActiveTarget(pLogBak);
}



} // namespace vgDebug
