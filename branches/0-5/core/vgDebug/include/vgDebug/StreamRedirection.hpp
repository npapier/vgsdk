// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGDEBUG_STREAMREDIRECTION_HPP_
#define _VGDEBUG_STREAMREDIRECTION_HPP_

#include <ostream>
#include "vgDebug/vgDebug.hpp"



namespace vgDebug
{



/**
 * @brief	Redirects a given output stream to another output stream or file.
 *
 * The redirection takes place as soon as the redirector instance is created
 * and it stops as soon as the redirector instance is destroyed. See sample code
 * below.
 *
 * @code
 * // Sends some text to the standard output and error streams.
 * std::cout << "Message to the standard output stream.\n";
 * std::cerr << "Message to the standard error stream.\n";
 *
 * // Redirects std::cout to a file.
 * // You should find a file named "log.txt" in the working directory.
 * {
 *     std::ofstream				logFile("log.txt");
 *     vgDebug::StreamRedirection	redirection( &std::cout, &logFile );
 *
 *     std::cout << "Message to the log file.\n";
 *
 *     // Overrides the previous redirection to a file named "anotherlog.txt".
 *     {
 *         std::ofstream				anotherLogFile("anotherlog.txt");
 *         vgDebug::StreamRedirection	redirection( &std::cout, &anotherLogFile );
 *
 *         std::cout << "Message to another log file.\n";
 *     }
 *
 *     std::cout << "Message to the log file again.\n";
 * }
 *
 * // Redirects std::cerr to a string buffer and shows the content of that
 * // buffer in std::cout.
 * {
 *     std::ostringstream			buffer;
 *     vgDebug::StreamRedirection	redirection( &std::cerr, &buffer );
 *
 *     std::cerr << "Error message to a string buffer.\n";
 *     std::cout << "From memory : " << buffer.str();
 * }
 *
 * // Sends some text to the standard output and error streams, again.
 * std::cout << "Message to the standard output stream, again.\n";
 * std::cerr << "Message to the standard error stream, again.\n";
 * @endcode
 */
struct VGDEBUG_API StreamRedirection
{
	/**
	 * @brief	Constructor
	 *
	 * @param	from	a pointer to the output stream to redirect from
	 * @param	to		a pointer to the output stream to redirect to
	 */
	StreamRedirection( std::ostream * from, std::ostream * to );

	/**
	 * @brief	Destructor
	 */
	~StreamRedirection();

	/**
	 * @brief	Retrieves the outupt stream the redirection comes from.
	 *
	 * @return	a pointer to an output stream
	 */
	std::ostream * from();

	/**
	 * @brief	Retrieves the output stream the redirection goes to.
	 *
	 * @return	a pointer to an output stream
	 */
	std::ostream * to();


private:

	std::ostream	* m_from;
	std::ostream	* m_to;
	std::streambuf	* m_oldFromStreambuf;

};



} // namespace vgDebug



#endif /*_VGDEBUG_STREAMREDIRECTION_HPP_*/
