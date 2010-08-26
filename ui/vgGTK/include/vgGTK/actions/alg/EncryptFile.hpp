// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_ACTIONS_ALG_ENCRYPTFILE_HPP_
#define _VGGTK_ACTIONS_ALG_ENCRYPTFILE_HPP_

#include "vgGTK/vgGTK.hpp"

#include <vgAlg/actions/IAction.hpp>

namespace vgGTK
{

namespace actions
{

namespace alg
{


/**
 * @brief Encrpyt a file.
 */
	struct VGGTK_API EncryptFile : public vgAlg::actions::IAction
{
	EncryptFile();

	~EncryptFile();

	virtual void execute();


private:


};


} // namespace alg

} // namespace actions

} // namespace vgGTK

#endif /*_VGGTK_ACTIONS_ALG_ENCRYPTFILE_HPP_*/

