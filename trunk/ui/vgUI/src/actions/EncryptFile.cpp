// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifdef __USE_VGALG__

#include "vgUI/actions/EncryptFile.hpp"

#include <vgAlg/actions/Encrypt.hpp>


namespace vgUI
{

namespace actions
{


EncryptFile::EncryptFile( ) :
IActionUI( "Edit/EncryptFile", "Encrypt File", "EncryptFile", DEFAULT, "", new vgAlg::actions::Encrypt() )
{
}



const bool EncryptFile::isValide( State state )
{
	return true;
}



} // namespace actions

} // namespace vgUI

#endif // #ifdef __USE_VGALG__
