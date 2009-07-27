// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgTest/Base.hpp"

namespace vgTest
{

Base::Base()
:	m_quit ( false )
{
}

void Base::setQuit(bool b)
{
	m_quit = b;
}

} // namespace vgTest
