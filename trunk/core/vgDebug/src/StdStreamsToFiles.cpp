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


StdStreamsToFiles::StdStreamsToFiles( const std::string & coutPath, const std::string & cerrPath )
:	m_coutPath( coutPath ),
	m_cerrPath( cerrPath ),
	m_coutFile( coutPath.c_str() ),
	m_cerrFile( cerrPath.c_str() )
{
	assert( coutPath != cerrPath );

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
