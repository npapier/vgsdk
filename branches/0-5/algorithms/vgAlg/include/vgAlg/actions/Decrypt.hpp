// VGSDK - Copyright (C) 2010, Maxime Peresson, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson
// Author Nicolas Papier

#ifndef _VGALG_ACTIONS_DECRYPT_HPP
#define _VGALG_ACTIONS_DECRYPT_HPP

#include <vgAlg/actions/IAction.hpp>
#include <vgd/Shp.hpp>

#include <vector>



namespace vgAlg
{

namespace actions
{

/**
 * @brief	Decrypt a file with blowfish algorithm.
 *
 * @ingroup g_archCrypto
 */
struct VGALG_API Decrypt : public vgAlg::actions::IAction
{
	Decrypt();

	virtual void execute();

	/**
	 * @brief Set values for encryption.
	 *
	 * @param key		encryption key.
	 *
	 * @param inBuffer	buffer of the crypted file.
	 *
	 * @param outBuffer	buffer for the new decrypted file.
	 */
	void setInitialize( const std::string key, vgd::Shp< std::vector<char> > inBuffer, vgd::Shp< std::vector<char> > outBuffer );

private:
	std::string						m_key;
	vgd::Shp< std::vector<char>	>	m_inBuffer;
	vgd::Shp< std::vector<char> >	m_outBuffer;

};



} // namespace actions

} // namespace vgAlg

#endif // _VGALG_ACTIONS_DECRYPT_HPP
