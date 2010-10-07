// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgPhysfs/Blowfish.hpp"



namespace vgPhysfs
{


Blowfish::Blowfish( unsigned char* ucKey, const size_t n )
:	m_blowfish( ucKey, n )
{}


Blowfish::Blowfish( const std::string key )
:	m_blowfish( (unsigned char*)key.c_str(), key.size() )
{}


void Blowfish::encrypt( unsigned char* buf, const size_t n )
{
	m_blowfish.Encrypt( buf, n );
}


void Blowfish::decrypt( unsigned char* buf, const size_t n )
{
	m_blowfish.Decrypt( buf, n );
}


void Blowfish::encrypt( const unsigned char* in, unsigned char* out, const size_t n )
{
	m_blowfish.Encrypt( in, out, n );
}


void Blowfish::decrypt( const unsigned char* in, unsigned char* out, const size_t n )
{
	m_blowfish.Decrypt( in, out, n );
}



} // namespace vgPhysfs
