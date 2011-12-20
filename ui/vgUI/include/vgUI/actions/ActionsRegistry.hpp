// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGUI_ACTIONS_ACTIONSREGISTRY_HPP
#define _VGUI_ACTIONS_ACTIONSREGISTRY_HPP


#include "vgUI/vgUI.hpp"

#include <list>

#include <vgAlg/actions/HiddenNode.hpp>
#include <vgd/Shp.hpp>
#include <vgUI/actions/IActionUI.hpp>


namespace vgUI
{

namespace actions
{

/**
 * @brief	Reference all actions drawable in a menu.
 */
struct VGUI_API ActionsRegistry
{
	/**
	* @brief	Get the instance of SelectedNode.
	*/
	static vgd::Shp< ActionsRegistry > getActionsRegistry();	
	
	~ActionsRegistry();

	/**
	 * @brief	Get the list of all action referenced.
	 *
	 * @return	the actions map.
	 */
	std::map< int, vgd::Shp< vgUI::actions::IActionUI > > getActionMap() const;

	/**
	 * @brief	Add an action to the current list.
	 *
	 * @param action	the action to add.
	 *
	 * @param action	the key to order action in menu.
	 */
	void addAction( vgd::Shp< vgUI::actions::IActionUI > action, int key);

	/**
	 * @brief	Get an action by its id.
	 *
	 * @return	id	tha action id.
	 */
	vgd::Shp< vgUI::actions::IActionUI > getAction( std::string id );

	/**
	 * @brief	Return the list of hidden node action menu.
	 *
	 * @return	the hidden node actions map.
	 */
	std::map< int, vgd::Shp< vgUI::actions::IActionUI > > getHiddenNodeActionMap();

private:
	
	ActionsRegistry();

	/**
	* @brief	the map of UI action : key / action.
	*			key: order to display action:
	*				1: select node
	*				10-19: edit menu
	*				20-29: transform menu
	*				30-39: visibility
	*				40-~: other
	*/
	std::map< int, vgd::Shp< vgUI::actions::IActionUI > > m_actionMap; ///< the map of UI action (key = order of menu)
	std::map< vgd::Wkp< vgAlg::actions::HiddenNode >, vgd::Shp< vgUI::actions::IActionUI > >	m_hiddenNodeMap; ///< the map of hidden node and its related UI action
};



/**
 * @brief Register an action in ActionsRegistry.
 */
template< typename actionType >
struct RegisterAction
{
	/**
	 * @brief Constructor to register an action.
	 *
	 * @param key	the key to order the action in menu.
	 */	
	RegisterAction( int key )
	{
		// Register the new action in ActionsRegistry.
 		vgd::Shp< actionType > action( new actionType() );
		
		ActionsRegistry::getActionsRegistry()->addAction( action, key );
	}
};


/**
 * @brief Meta helpers.
 */
#define META_ACTION_HPP( actionType )	\
static const vgUI::actions::RegisterAction< actionType > m_registrationInstance;

#define META_ACTION_CPP( actionType, key )	\
const vgUI::actions::RegisterAction< actionType > actionType::m_registrationInstance( key );


} // namespace actions

} // namespace vgUI

#endif //#ifndef _VGUI_ACTIONS_ACTIONSREGISTRY_HPP
