// VGSDK - Copyright (C) 2007, 2008, 2011, 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgio/FilenameCollector.hpp"

#include <boost/filesystem/operations.hpp>
#include <vgDebug/helpers.hpp>



namespace vgio
{



FilenameCollector::FilenameCollector( const std::string& path )
:	m_path( path ),
	m_searchProperties(REGULAR_FILE)
{}



FilenameCollector::FilenameCollector( const ::boost::filesystem::path& path )
:	m_path( path ),
	m_searchProperties(REGULAR_FILE)
{}



void FilenameCollector::setRegex( const std::string& regex )
{
	m_regex = regex;
}


const FilenameCollector::StringList& FilenameCollector::run()
{
	m_filenames.clear();
	m_stringFilenames.clear();
	run( m_path );
	return getStringFilenames();
}


void FilenameCollector::run( const boost::filesystem::path& path)
{
	vgAssert( boost::filesystem::exists(path) );

	// Skips processing if the given path is not valid.
	if( !boost::filesystem::exists(path) )
	{
		return;
	}

	namespace fs = boost::filesystem;

	for( fs::directory_iterator i( path ); i != fs::directory_iterator(); ++i )
	{
		fs::path current (*i);
		fs::file_type file_type = fs::status(current).type();
		if ( ( ( file_type == fs::regular_file ) && ( m_searchProperties & REGULAR_FILE ) ) ||
			 ( ( file_type == fs::directory_file ) && ( m_searchProperties & DIRECTORY_FILE ) ) )
		{
			if ( m_regex.empty() )
			{
				m_filenames.push_back( current );
				m_stringFilenames.push_back( current.string() );
			}
			else
			{
				const bool matchingRegex = ::boost::regex_match( current.string(), m_regex );
				
				if ( matchingRegex )
				{
					m_filenames.push_back( current );
					m_stringFilenames.push_back( current.string() );
				}
				// else no matching, nothing to do
			}
		}
		// if search is recursive, search in subdirectories
		if( ( file_type == fs::directory_file ) && ( m_searchProperties & RECURSIVE_SEARCH ) )
		{
			run( current );
		}
	}
}



const FilenameCollector::PathList& FilenameCollector::getFilenames() const
{
	return m_filenames;
}



const FilenameCollector::StringList& FilenameCollector::getStringFilenames() const
{
	return m_stringFilenames;
}

void FilenameCollector::setSearchProperties( const int properties )
{
	m_searchProperties = SearchProperty( properties );
}

} // namespace vgio
