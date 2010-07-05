// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_INPUT_ISTRINGINPUT_HPP
#define _VGALG_ACTIONS_INPUT_ISTRINGINPUT_HPP


#include "vgAlg/vgAlg.hpp"

#include <vgd/node/Node.hpp>
#include <vgd/Shp.hpp>

namespace vgAlg
{

namespace actions
{

namespace input
{

/**
 * @brief	Interface to add a string parame getter/setter to an action.
 */
struct VGALG_API IStringInput
{
	void setStringParam( std::string param );

	std::string getStringParam();


protected:
	std::string m_stringParam;
};

} // namespace input

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_INPUT_ISTRINGINPUT_HPP
