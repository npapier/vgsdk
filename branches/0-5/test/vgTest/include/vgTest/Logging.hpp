// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGTEST_LOGGING_HPP
#define _VGTEST_LOGGING_HPP

#include <map>
#include <string>

#include "vgTest/vgTest.hpp"

//Used because addToGtest don't work. Problem posted in gtest mailing-list
#define PutInGtestReport(base) \
	std::map<std::string, std::string> log = base->getLog()->getLog(); \
	for( std::map<std::string, std::string>::iterator ii=log.begin(); ii!=log.end(); ++ii) \
	{ \
		   RecordProperty((*ii).first.c_str(), (*ii).second.c_str()); \
	}

namespace vgTest
{

/**
 * @brief Abstract base class which make link between test application, Gtk and vgsdk.
 */
struct Logging
{
	/**
	 * @brief Default constructor
	 */
	VGTEST_API Logging();


	/**
	 * @brief Add a string to the logging map
	 */
	VGTEST_API void add(std::string key, std::string value);

	/**
	 * @brief Add something to the logging map
	 */
	template <class T>
	void add(std::string key, T value)
	{
		std::ostringstream out;
		out << value;
		
		m_log[key] = out.str();
	}

	/**
	 * @brief Get value from the map
	 */
	VGTEST_API const std::string get(std::string key);

	/**
	 * @brief Remove value from the map
	 */
	VGTEST_API void remove(std::string key);

	/**
	 * @brief Get the log map
	 */
	VGTEST_API const std::map<std::string, std::string>& getLog() const;

	/**
	 * @brief Add the whole map to googletest report
	 */
	VGTEST_API void addToGtest();


private:
	std::map<std::string, std::string> m_log;
};



} // namespace vgTest



#endif // #ifndef _VGTEST_LOGGING_HPP
