// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/basic/FilenameExtractor.hpp"



namespace vgd
{

namespace basic
{



FilenameExtractor::FilenameExtractor( std::string pathFilename ) :
	m_pathFilename( pathFilename )
{
	for(	std::string::size_type index = m_pathFilename.find('\\');
			index != std::string::npos;
			index = m_pathFilename.find('\\') )
	{
		m_pathFilename[index] = '/';
	}
}



std::string FilenameExtractor::getExtension() const
{
	std::string::size_type	index;
	std::string				extension;
	
	index	= m_pathFilename.rfind('.');
	
	if ( index != std::string::npos )
	{
		extension	= m_pathFilename.substr( index, m_pathFilename.size() - index );
	}

	return ( extension );
}



std::string FilenameExtractor::getFilename() const
{
	std::string::size_type	index;
	std::string				filename;
	
	index 	= m_pathFilename.rfind('/');
	
	if ( index != std::string::npos )
	{
		filename = m_pathFilename.substr( index+1, m_pathFilename.size() - (index+1) );
	}

	return ( filename );
}



std::string FilenameExtractor::getFilenameWithoutExtension() const
{
	std::string extension;
	
	std::string				filename	= getFilename();
	std::string::size_type	index		= filename.rfind('.');
		
	if ( index != std::string::npos )
	{
		if ( index > 0 )
		{
			extension	= filename.substr( 0, index );
		}
	}

	return ( extension );
}



std::string FilenameExtractor::getPath() const
{
	std::string::size_type	index;
	std::string					path;
	
	index 	= m_pathFilename.rfind('/');
	
	if ( index != std::string::npos )
	{
		path		= m_pathFilename.substr( 0, index );
	}

	return ( path );
}



std::string FilenameExtractor::getPathFilename() const
{
	return ( m_pathFilename );
}


} // namespace basic

} // namespace vgd
