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
	if ( m_instanceCount == 0 )
	{
		// redirect cerr to cerr.txt file
		m_errFile = new std::ofstream("cerr.txt");
		std::streambuf* errBuf = m_errFile->rdbuf();

		m_cerrBuf = std::cerr.rdbuf();
		std::cerr.rdbuf(errBuf);
		
		// redirect cout to cout.txt file
		m_outFile = new std::ofstream("cout.txt");
		std::streambuf* outBuf = m_outFile->rdbuf();

		m_coutBuf = std::cout.rdbuf();
		std::cout.rdbuf(outBuf);
	}

	++m_instanceCount;

	//
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);	
	
	logDebug("Create a new logger.");

	wxLog::SetActiveTarget(pLogBak);
}



Logging::~Logging()
{
	if ( m_instanceCount == 1 )
	{
		// restores cerr and releases file
		std::cerr.rdbuf(m_cerrBuf);

		delete m_errFile;

		// restore cout and release file
		std::cout.rdbuf(m_coutBuf);

		delete m_outFile;
	}

	--m_instanceCount;
	
	//
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

	wxVLogFatalError( wxConvertMB2WX(szFormat), marker );

	va_end( marker );

	wxLog::SetActiveTarget(pLogBak);
}



void Logging::logError( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	wxVLogError( wxConvertMB2WX(szFormat), marker );

	va_end( marker );

	wxLog::SetActiveTarget(pLogBak);
}



void Logging::logWarning( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	wxVLogWarning( wxConvertMB2WX(szFormat), marker );

	va_end( marker );

	wxLog::SetActiveTarget(pLogBak);
}



void Logging::logMessage( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	wxVLogMessage( wxConvertMB2WX(szFormat), marker );

	va_end( marker );

	wxLog::SetActiveTarget(pLogBak);
}



void Logging::logVerbose( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	wxVLogVerbose( wxConvertMB2WX(szFormat), marker );

	va_end( marker );
	
	wxLog::SetActiveTarget(pLogBak);
}



void Logging::logStatus( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	wxVLogStatus( wxConvertMB2WX(szFormat), marker );

	va_end( marker );

	wxLog::SetActiveTarget(pLogBak);
}



void Logging::logSysError( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	wxVLogSysError( wxConvertMB2WX(szFormat), marker );

	va_end( marker );

	wxLog::SetActiveTarget(pLogBak);
}




void Logging::logDebug( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	wxVLogDebug( wxConvertMB2WX(szFormat), marker );

	va_end( marker );

	wxLog::SetActiveTarget(pLogBak);
}



void Logging::logTrace( const char *szFormat, ... ) const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);
	
	va_list marker;
	va_start( marker, szFormat );

	// wxVLogTrace( wxConvertMB2WX(szFormat), marker ); FIXME modified interface in wx2.5 and superior.
	wxVLogDebug( wxConvertMB2WX(szFormat), marker );

	va_end( marker );

	wxLog::SetActiveTarget(pLogBak);
}



void Logging::flush() const
{
	wxLog *pLogBak = wxLog::SetActiveTarget(m_pLogger);

	m_pLogger->FlushActive();

	wxLog::SetActiveTarget(pLogBak);
}



int Logging::m_instanceCount = 0;



} // namespace vgDebug
