// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_FILENAMECOLLECTOR_HPP
#define _VGD_BASIC_FILENAMECOLLECTOR_HPP

#include <boost/filesystem/path.hpp>
#include <boost/regex.hpp>
#include <list>
#include <string>

#include "vgd/vgd.hpp"



namespace vgd
{

namespace basic
{



/**
 * @brief Collects the filename of each file in a directory
 *
 * A regular expression could be used to filter collected filenames.
 * 
 * @remarks Directories in path directory are not explored. 
 * 
 * @todo Moves to vgIO ?
 */
struct VGD_API FilenameCollector
{
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



private:

	/**
	 * @name Input parameters
	 */
	//@{
	::boost::filesystem::path	m_path;				//< the path from where filenames must be collected
	::boost::regex				m_regex;			//< the boost regular expression to filter collected filenames
	//@}

	/**
	 * @name Output parameters
	 */
	//@{
	PathList					m_filenames;		//< collected filenames
	StringList					m_stringFilenames;	//< collected filenames formatted in the native representation
	//@}
};



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_FILENAMECOLLECTOR_HPP
