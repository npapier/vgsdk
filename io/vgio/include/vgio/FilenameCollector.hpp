// VGSDK - Copyright (C) 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGIO_FILENAMECOLLECTOR_HPP
#define _VGIO_FILENAMECOLLECTOR_HPP

#include <boost/filesystem/path.hpp>
#include <boost/regex.hpp>
#include <list>
#include <string>

#include "vgio/vgio.hpp"



namespace vgio
{



/**
 * @brief Collects the filename of each file in a directory
 *
 * A regular expression could be used to filter collected filenames.
 * 
 * @remarks Directories in path directory are not explored. 
 */
struct VGIO_API FilenameCollector
{
	
	/**
	 * @brief Search property.
	 */
	enum SearchProperty
	{
		REGULAR_FILE = 1, //< Search for regular files
		DIRECTORY_FILE = 2, //< Search for directory files
		RECURSIVE_SEARCH = 4 //< Search in sub directories
	};

	/**
	 * @brief Typedef for list of path
	 */
	typedef std::list< ::boost::filesystem::path >	PathList;

	/**
	 * @brief Typedef for list of string
	 */
	typedef std::list< std::string >				StringList;

	/**
	 * @brief Constructor
	 * 
	 * @param path		the path from where filenames must be collected
	 */
	FilenameCollector( const std::string& path );

	/**
	 * @brief Default constructor
	 * 
	 * @param path		the path from where filenames must be collected
	 */
	FilenameCollector( const ::boost::filesystem::path& path );

	/**
	 * @brief Sets the regular expression used to filter collected filenames
	 *
	 * @param regex		the regular expression
	 */
	void setRegex( const std::string& regex );

	/**
	 * @brief Collects the desired filenames
	 *
	 * @return all collected filenames (same as method getStringFilenames)
	 */
	const StringList& run();
	 
	/**
	 * @brief Gets all collected filenames
	 * 
	 * @return the filenames
	 */
	const PathList& getFilenames() const;

	/**
	 * @brief Gets all collected filenames
	 * 
	 * @return the filenames
	 */
	const StringList& getStringFilenames() const;

	/**
	 * @brief Set search properties
	 * @param properties A combination of SearchProperty
	 */
	void setSearchProperties(const int properties);



private:

	/**
	 * @brief Collects the desired filenames.
	 *
	 * Used internally for recursive search
	 */
	void run(const boost::filesystem::path& path);

	/**
	 * @name Input parameters
	 */
	//@{
	::boost::filesystem::path	m_path;				//< the path from where filenames must be collected
	::boost::regex				m_regex;			//< the boost regular expression to filter collected filenames
	SearchProperty				m_searchProperties; //< the type of search that is being done
	//@}

	/**
	 * @name Output parameters
	 */
	//@{
	PathList					m_filenames;		//< collected filenames
	StringList					m_stringFilenames;	//< collected filenames formatted in the native representation
	//@}
};



} // namespace vgio

#endif //#ifndef _VGIO_FILENAMECOLLECTOR_HPP
