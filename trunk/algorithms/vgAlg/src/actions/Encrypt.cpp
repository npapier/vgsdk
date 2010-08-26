// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include <vgAlg/actions/Encrypt.hpp>

#include <vgPhysicFS/BlowFish.hpp>


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
	vgPhysicFS::CBlowFish oBlowFish( (unsigned char*)m_key.c_str(), m_key.size() );

	//Encryption
	oBlowFish.Encrypt( (unsigned char*)&m_inBuffer[0], (unsigned char*)&(*m_outBuffer)[0], m_inBuffer.size() );
}



void Encrypt::setInitialize( std::string key, std::vector< char > inBuffer, vgd::Shp< std::vector< char > > outBuffer )
{
	m_key = key;
	m_inBuffer = inBuffer;
	m_outBuffer = outBuffer;

	int length_read = ( ( m_inBuffer.size() + 7 ) &~7 ); //lenght must be a multiple of 8
	m_inBuffer.resize( length_read );
	m_outBuffer->resize( length_read );
}



} // namespace actions

} // namespace vgAlg
