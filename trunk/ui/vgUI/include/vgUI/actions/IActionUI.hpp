// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGUI_ACTIONS_IACTIONUI_HPP
#define _VGUI_ACTIONS_IACTIONUI_HPP


#include "vgUI/vgUI.hpp"

#include <vgAlg/actions/IAction.hpp>
#include <vgUI/actions/State.hpp>
#include <vgUI/actions/Icons.hpp>

#include <string>
#include <vector>

namespace vgUI
{

namespace actions
{

/**
 * @brief	Interface for all UI Action.
 *			An UI Action contain all attribut to create a menuitem.
 */
struct VGUI_API IActionUI
{
	IActionUI( std::string menuContrib, std::string name, std::string id, Icons icon, std::string accelKey, vgAlg::actions::IAction* action );

	virtual ~IActionUI();

	/**
	 * @brief	Apply filter to check if the menuitem need to be displayed.
	 *
	 * @param filter	The filter with all information about current state.
	 */
	virtual const bool isValide( State state ) = 0 ;

	const std::string					getMenuContrib() const;
	const std::vector< std::string >	getMenuContribList() const;
	const std::string					getName() const;
	const std::string					getId() const;
	const Icons							getIcon() const;
	const std::string					getAccelKey() const;
	vgAlg::actions::IAction*			getAction() const;


protected:

	std::string	m_menuContrib;						///< The path for the menu separated by "/". Exemple: "rootMenu/submenu/menuitemName".
	std::string m_name;								///< The displayed name of the menuitem.
	std::string m_id;								///< An id for the menuitem. (must be unique but not verified)
	Icons m_icon;									///< Icon image for the menuitem.
	std::string m_accelKey;							///< The acceleration key to execute the action of the menuitem (Gtk format).
	vgd::Shp< vgAlg::actions::IAction > m_action;	///< the action to be called.


};

} // namespace actions

} // namespace vgUI

#endif //#ifndef _VGUI_ACTIONS_IACTIONUI_HPP
