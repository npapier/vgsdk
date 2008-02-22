// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/basic/FilenameCollector.hpp"

#include <boost/filesystem/operations.hpp>



namespace vgd
{

namespace basic
{



FilenameCollector::FilenameCollector( const std::string& path )
:	m_path	(	path, ::boost::filesystem::no_check	)
{}



FilenameCollector::FilenameCollector( const ::boost::filesystem::path& path )
:	m_path	(	path	)
{}



void FilenameCollector::setRegex( const std::string& regex )
{
	m_regex = regex;
}



const FilenameCollector::StringList& FilenameCollector::run()
{
	namespace fs = boost::filesystem;

	for( fs::directory_iterator i( m_path ); i != fs::directory_iterator(); ++i )
	{
		fs::path current (*i);
		
		if ( !fs::is_directory( current ) )
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
		// else is_directory() == true, nothing to do
	}
	
	return getStringFilenames();
}



const FilenameCollector::PathList& FilenameCollector::getFilenames() const
{
	return m_filenames;
}



const FilenameCollector::StringList& FilenameCollector::getStringFilenames() const
{
	return m_stringFilenames;
}



} // namespace basic

} // namespace vgd
