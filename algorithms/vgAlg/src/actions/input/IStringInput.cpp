// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/input/IStringInput.hpp"

namespace vgAlg
{

namespace actions
{

namespace input
{

void IStringInput::setStringParam( std::string param )
{
	m_stringParam = param;
}

std::string IStringInput::getStringParam()
{
	return m_stringParam;
}

} // namespace input

} // namespace actions

} // namespace vgAlg