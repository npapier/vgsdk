// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGALG_ACTIONS_IACTION_HPP
#define _VGALG_ACTIONS_IACTION_HPP


#include "vgAlg/vgAlg.hpp"


namespace vgAlg
{

namespace actions
{

/**
 * @brief	Interface for an action.
 */
struct VGALG_API IAction
{

	IAction(){};

	virtual ~IAction(){};

	/**
	 * @brief	Execute the action.
	 */
	virtual void execute() = 0;

};

} // namespace actions

} // namespace vgAlg

#endif //#ifndef _VGALG_ACTIONS_IACTION_HPP
