// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGDEBUG_LOGGING_HPP
#define _VGDEBUG_LOGGING_HPP

#include <iostream>
#include <fstream>

#include "vgDebug/vgDebug.hpp"

#include "vgDebug/ILogging.hpp"
class wxLog;



namespace vgDebug
{



/**
 * @brief Implements logging interface(to cerr) with wxWidgets.
 */
struct VGDEBUG_API Logging : public ILogging
{
	/**
	 * @name Constructor/Destructor
	 */
	//@{

	/**
	 * @brief Constructor
	 */
	Logging();
	
	/**
	 * @brief Destructor
	 */
	~Logging();

	//@}
	
	
	
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



private:
	/**
	 * @brief Keep a reference to the wxLogger mapped by this class.
	 */
	wxLog *m_pLogger;

	static int m_instanceCount;

	std::ofstream*	m_errFile;
	std::streambuf*	m_cerrBuf;

	std::ofstream*	m_outFile;
	std::streambuf*	m_coutBuf;
};



} // namespace vgDebug

#endif // #ifndef _VGDEBUG_LOGGING_HPP
