// VGSDK - Copyright (C) 2010, 2014, Clement Forest.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Clement Forest

#include "vgDebug/StreamTee.hpp"

#include <cstdio>
#include <streambuf>

namespace
{
// Class found on http://wordaligned.org/articles/cpp-streambufs
class teebuf: public std::streambuf
{
public:
    // Construct a streambuf which tees output to both input
    // streambufs.
    teebuf(std::streambuf * sb1, std::streambuf * sb2)
        : sb1(sb1)
        , sb2(sb2)
    {
    }
private:
    // This tee buffer has no buffer. So every character "overflows"
    // and can be put directly into the teed buffers.
    virtual int overflow(int c)
    {
        if (c == EOF)
        {
            return !EOF;
        }
        else
        {
            int const r1 = sb1->sputc(c);
            int const r2 = sb2->sputc(c);
            return r1 == EOF || r2 == EOF ? EOF : c;
        }
    }
    
    // Sync both teed buffers.
    virtual int sync()
    {
        int const r1 = sb1->pubsync();
        int const r2 = sb2->pubsync();
        return r1 == 0 || r2 == 0 ? 0 : -1;
    }   
private:
    std::streambuf * sb1;
    std::streambuf * sb2;
};


}

namespace vgDebug
{



StreamTee::StreamTee( std::ostream * tee, std::ostream * first, std::ostream * second )
:	m_tee( tee ),
	m_first( second?first:tee ),
	m_second( second?second:first ),
	m_oldFromStreambuf( tee->rdbuf() )
{
	if(m_first->rdbuf()&&m_second->rdbuf())
	{
		m_tee->rdbuf( new teebuf( m_first->rdbuf(), m_second->rdbuf() ) );
	}
	else if( m_second->rdbuf() )
	{
		m_tee->rdbuf( m_second->rdbuf() );
	}
	else if( m_first->rdbuf() )
	{
		m_tee->rdbuf( m_first->rdbuf() );
	}
}



StreamTee::~StreamTee()
{
	m_tee->rdbuf( m_oldFromStreambuf );
}



std::ostream * StreamTee::tee()
{
	return m_tee;
}



std::ostream * StreamTee::first()
{
	return m_first;
}



std::ostream * StreamTee::second()
{
	return m_second;
}



} // namespace vgDebug
