// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/ActionsRegistry.hpp"

#include <vgAlg/actions/SelectedNode.hpp>


#include <vgUI/actions/ShowNode.hpp>

namespace vgUI
{

namespace actions
{

vgd::Shp< ActionsRegistry > ActionsRegistry::getActionsRegistry()
{
	static vgd::Shp< ActionsRegistry > actionsRegistry;

	if( !actionsRegistry )
	{
		actionsRegistry.reset( new ActionsRegistry() );
	}
	
	return actionsRegistry;
}

ActionsRegistry::ActionsRegistry( )
{
}



ActionsRegistry::~ActionsRegistry( )
{
	m_actionMap.clear();
	m_hiddenNodeMap.clear();
}



std::map< int, vgd::Shp< vgUI::actions::IActionUI > > ActionsRegistry::getActionMap() const
{
	return m_actionMap;
}



void ActionsRegistry::addAction( vgd::Shp< vgUI::actions::IActionUI > action, int key)
{
	assert( m_actionMap.find(key) == m_actionMap.end() && "ActionUI key already used." );

	m_actionMap[ key ] = action;
}



vgd::Shp< vgUI::actions::IActionUI > ActionsRegistry::getAction( std::string id )
{
	vgd::Shp< vgUI::actions::IActionUI > retVal;
	std::map< int, vgd::Shp< vgUI::actions::IActionUI > >::iterator it = m_actionMap.begin();
	for( it; it != m_actionMap.end(); it++ )
	{
		if( it->second->getId() == id )
		{
			retVal = it->second;
			return retVal;
		}
	}
	
	return retVal;
}



std::map< int, vgd::Shp< vgUI::actions::IActionUI > > ActionsRegistry::getHiddenNodeActionMap()
{
	std::map< int, vgd::Shp< vgUI::actions::IActionUI > > hiddenNodeActionMap;

	vgd::Shp< std::list< vgd::Shp< vgAlg::actions::HiddenNode > > > hiddenNodes = vgAlg::actions::SelectedNode::getSelectedNodeObject()->getHiddenNodeList();

	std::list< vgd::Shp < vgAlg::actions::HiddenNode > >::iterator it = hiddenNodes->begin();
	int i = 0;
	for( it; it != hiddenNodes->end(); it++ )
	{
		if( m_hiddenNodeMap.count( (*it) ) == 0 )
		{
			vgd::Shp< vgUI::actions::IActionUI > action = vgd::makeShp( new vgUI::actions::ShowNode( (*it) ) );
			hiddenNodeActionMap[ i ] = action;
			m_hiddenNodeMap[ (*it) ] = action;
			i++;
		}
	}

	return hiddenNodeActionMap;
}

} // namespace actions

} // namespace vgUI
