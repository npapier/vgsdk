// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGDEBUG_STDSTREAMSTOFILES_HPP_
#define _VGDEBUG_STDSTREAMSTOFILES_HPP_

#include <fstream>
#include <memory>
#include <string>

#include "vgDebug/vgDebug.hpp"



namespace vgDebug
{



struct StreamRedirection;



/**
 * @brief	Redirects @c std::cout and @c std::cerr to files (default paths are
 * 			@c cout.txt and @c cerr.txt respectively).
 *
 * The redirection begins as soon as the instance of this class is created. The
 * redirection stops as soon as the instance is destroyed. See sample code below.
 *
 * @code
 * // Sends some text to the standard output and error streams.
 * std::cout << "Message to the standard output stream.\n";
 * std::cerr << "Message to the standard error stream.\n";
 *
 * // Now redirects both std::cout and std::cerr to files.
 * // You should find files named "cout.txt" and "cerr.txt" in the working directory.
 * {
 *      vgDebug::StdStreamsToFiles redirection;
 *
 *      std::cout << "Message goes to cout.txt\n";
 *      std::cerr << "Message goes to cerr.txt\n";
 * }
 *
 * // Sends some text to the standard output and error streams, again.
 * std::cout << "Message to the standard output stream, again.\n";
 * std::cerr << "Message to the standard error stream, again.\n";
 * @endcode
 *
 * @remark	Any existing file will be overwritten.
 *
 * @remark	Redirecting @c std::cout and @c std::cerr to the same file is not supported yet.
 */
struct VGDEBUG_API StdStreamsToFiles
{
	/**
	 * @brief	Constructor
	 *
	 * @param	coutPath	a string containing the path to the file that will log @c std::cout (@c cout.txt by default)
	 * @param	cerrPath	a string containing the path to the file that will log @c std::cerr (@c cerr.txt by default)
	 *
	 * @pre		coutPath != cerrPath
	 */
	StdStreamsToFiles( const std::string & coutPath = "cout.txt", const std::string & cerrPath = "cerr.txt" );

	/**
	 * @brief	Destructor
	 */
	~StdStreamsToFiles();

	/**
	 * @brief	Retrieves the path of the file use to log @c std::cout content.
	 *
	 * @return	a string containing a path
	 */
	const std::string & getCoutPath() const;

	/**
	 * @brief	Retrieves the path of the file use to log @c std::cerr content.
	 *
	 * @return	a string containing a path
	 */
	const std::string & getCerrPath() const;

private:

	const std::string					m_coutPath;
	const std::string					m_cerrPath;
	std::ofstream						m_coutFile;
	std::ofstream						m_cerrFile;
	std::auto_ptr< StreamRedirection >	m_coutRedirection;
	std::auto_ptr< StreamRedirection >	m_cerrRedirection;

};


} // namespace vgDebug



#endif /*_VGDEBUG_STDSTREAMSTOFILES_HPP_*/
