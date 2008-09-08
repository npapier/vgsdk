// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgDebug/StdStreamsToFiles.hpp"

#include <cassert>
#include <iostream>

#include "vgDebug/StreamRedirection.hpp"



namespace vgDebug
{


StdStreamsToFiles::StdStreamsToFiles( const std::string & coutPath, const std::string & cerrPath, const OpenModeType openMode )
:	m_coutPath( coutPath ),
	m_cerrPath( cerrPath )
{
	assert( coutPath != cerrPath );

	std::ios_base::openmode stlOpenMode = std::ios_base::out;
	stlOpenMode |= (openMode == TRUNCATE ? std::ios_base::trunc : std::ios_base::app);

	m_coutFile.open( coutPath.c_str(), stlOpenMode );
	m_cerrFile.open( cerrPath.c_str(), stlOpenMode );

	m_coutRedirection.reset( new StreamRedirection(&std::cout, &m_coutFile) );
	m_cerrRedirection.reset( new StreamRedirection(&std::cerr, &m_cerrFile) );
}



StdStreamsToFiles::~StdStreamsToFiles()
{
	// Well, nothing to do :)
}



const std::string & StdStreamsToFiles::getCoutPath() const
{
	return m_coutPath;
}



const std::string & StdStreamsToFiles::getCerrPath() const
{
	return m_cerrPath;
}



} // namespace vgDebug
