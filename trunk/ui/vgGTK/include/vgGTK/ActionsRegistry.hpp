// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGGTK_ACTIONSREGISTRY_HPP
#define _VGGTK_ACTIONSREGISTRY_HPP


#include "vgGTK/vgGTK.hpp"

#include <list>

#include <vgAlg/actions/HiddenNode.hpp>
#include <vgd/Shp.hpp>
#include <vgUI/actions/IActionUI.hpp>


namespace vgGTK
{

/**
 * @brief	Reference all actions drawable in a menu.
 */
struct VGGTK_API ActionsRegistry
{
	ActionsRegistry();
	~ActionsRegistry();

	/**
	 * @brief	Get the list of all action referenced.
	 *
	 * @return	the actions list.
	 */
	std::list< vgd::Shp< vgUI::actions::IActionUI > > getActionList() const;

	/**
	 * @brief	Add an action to the current list.
	 *
	 * @param action	the action to add.
	 */
	void addAction( vgd::Shp< vgUI::actions::IActionUI > action);

	/**
	 * @brief	Get an action by its id.
	 *
	 * @return	id	tha action id.
	 */
	vgd::Shp< vgUI::actions::IActionUI > getAction( std::string id );

	/**
	 * @brief	Return the list of hidden node action menu.
	 *
	 * @return	the hidden node actions list.
	 */
	std::list< vgd::Shp< vgUI::actions::IActionUI > > getHiddenNodeActionList();

private:

	std::list< vgd::Shp< vgUI::actions::IActionUI > >	m_actionList; ///< the list of UI action
	std::map< vgd::WeakPtr< vgAlg::actions::HiddenNode >, vgd::Shp< vgUI::actions::IActionUI > >	m_hiddenNodeMap; ///< the list of hidden node UI action
};

} // namespace vgGTK

#endif //#ifndef _VGGTK_ACTIONSREGISTRY_HPP
