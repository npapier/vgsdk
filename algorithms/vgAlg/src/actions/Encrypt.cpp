// VGSDK - Copyright (C) 2010, 2014, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson
// Author Guillaume Brocker


#include <vgAlg/actions/Encrypt.hpp>

#include <vgPhysfs/Blowfish.hpp>


namespace vgAlg
{

namespace actions
{



Encrypt::Encrypt()
{

}



void Encrypt::execute()
{
	//Initialization
	vgPhysfs::Blowfish oBlowFish( m_key );

	//Encryption
	oBlowFish.encrypt( (unsigned char*)&(*m_inBuffer)[0], (unsigned char*)&(*m_outBuffer)[0], m_inBuffer->size() );
}



void Encrypt::setInitialize( const std::string key, vgd::Shp< std::vector<char> > inBuffer, vgd::Shp< std::vector<char> > outBuffer )
{
	m_key		= key;
	m_inBuffer	= inBuffer;
	m_outBuffer	= outBuffer;

	const int length_read = ( ( m_inBuffer->size() + 7 ) &~7 ); //length must be a multiple of 8
	m_inBuffer->resize( length_read );
	m_outBuffer->resize( length_read );
}



} // namespace actions

} // namespace vgAlg
