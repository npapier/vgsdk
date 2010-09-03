// VGSDK - Copyright (C) 2010, Clement Forest.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Clement Forest

#ifndef _VGDEBUG_STREAMTEE_HPP_
#define _VGDEBUG_STREAMTEE_HPP_

#include <ostream>
#include "vgDebug/vgDebug.hpp"



namespace vgDebug
{



/**
 * @brief	Tee two output stream to another output stream or file.
 *
 * The redirection takes place as soon as the redirector instance is created
 * and it stops as soon as the redirector instance is destroyed. See sample code
 * below.
 *
 * @warning This constructor creates a stream buffer which is never destroyed
 *
 * @code
 * // Sends some text simultaneously to the standard output and error streams.
 * std::cout << "Message to the standard output stream.\n";
 * std::cerr << "Message to the standard error stream.\n";
 *
 * // Tee std::cout to a file.
 * // You should find a file named "log.txt" in the working directory.
 * {
 *     std::ofstream				logFile("log.txt");
 *     vgDebug::StreamTee	redirection( &std::cout, &logFile );
 *
 *     std::cout << "Message to the log file.\n";
 *
 *     // Overrides the previous redirection to a file named "anotherlog.txt".
 *     {
 *         std::ofstream				anotherLogFile("anotherlog.txt");
 *         vgDebug::StreamTee	redirection( &std::cout, &anotherLogFile );
 *
 *         std::cout << "Message to another log file.\n";
 *     }
 *
 *     std::cout << "Message to the log file again.\n";
 * }
 *
 * // Tee std::cerr to a string buffer and shows the content of that
 * // buffer in std::cout.
 * {
 *     std::ostringstream			buffer;
 *     vgDebug::StreamTee	redirection( &std::cerr, &buffer );
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
struct VGDEBUG_API StreamTee
{
	/**
	 * @brief	Constructor
	 * 
	 * StreamTee(a,b) is equivalent to StreamTee(a,a,b)
	 *
	 * @param	tee		a pointer to the output stream that will become the tee
	 * @param	first	a pointer to the first output stream to be teed
	 * @param	second	a pointer to the second output stream to be teed
	 */
	StreamTee( std::ostream * tee, std::ostream * first, std::ostream * second=0 );

	/**
	 * @brief	Destructor
	 *
	 * The associated buffed m_teeBuf is never destroyed. This is
	 * because rdbuf might have been called and that the buffer could
	 * still be in use somewhere
	 */
	~StreamTee();

	/**
	 * @brief	Retrieves the outupt stream the redirection comes from.
	 *
	 * @return	a pointer to an output stream
	 */
	std::ostream * tee();

	/**
	 * @brief	Retrieves the output stream the redirection goes to.
	 *
	 * @return	a pointer to an output stream
	 */
	std::ostream * first();

	/**
	 * @brief	Retrieves the output stream the redirection goes to.
	 *
	 * @return	a pointer to an output stream
	 */
	std::ostream * second();


private:

	std::ostream	* m_tee;
	std::ostream	* m_first;
	std::ostream	* m_second;
	std::streambuf	* m_oldFromStreambuf;
};



} // namespace vgDebug



#endif /*_VGDEBUG_STREAMTEE_HPP_*/
