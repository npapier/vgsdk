// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_ENCRYPT_HPP
#define _VGALG_ACTIONS_ENCRYPT_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgd/Shp.hpp>

#include <vector>

namespace vgAlg
{

namespace actions
{

/**
 * @brief	Encrypt a file with blowfish algorithm.
 *
 * @ingroup g_archCrypto
 */
struct VGALG_API Encrypt : public vgAlg::actions::IAction
{

	Encrypt();

	virtual void execute();

	/**
	 * @brief Set values for encryption.
	 *
	 * @param key		encryption key.
	 *
	 * @param inBuffer	buffer of the file.
	 *
	 * @param outBuffer	buffer of the new encrypted file.
	 */
	void setInitialize( std::string key, std::vector< char > inBuffer, vgd::Shp< std::vector< char > > outBuffer );

private:
	std::string						m_key;
	std::vector< char >				m_inBuffer;
	vgd::Shp< std::vector< char > >	m_outBuffer;

};

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_ENCRYPT_HPP
