// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgDebug/StreamRedirection.hpp"



namespace vgDebug
{



StreamRedirection::StreamRedirection( std::ostream * from, std::ostream * to )
:	m_from( from ),
	m_to( to ),
	m_oldFromStreambuf( from->rdbuf() )
{
	m_from->rdbuf( m_to->rdbuf() );
}



StreamRedirection::~StreamRedirection()
{
	m_from->rdbuf( m_oldFromStreambuf );
}



std::ostream * StreamRedirection::from()
{
	return m_from;
}



std::ostream * StreamRedirection::to()
{
	return m_to;
}



} // namespace vgDebug
