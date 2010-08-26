// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/node/EditMenu.hpp"

#include <boost/bind.hpp>
#include <boost/signals.hpp>

#include <gtkmm/stock.h>
#include <gtkmm/window.h>
#include <gtkmm/icontheme.h>

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>
#include <vgAlg/actions/input/IParentInput.hpp>
#include <vgAlg/actions/SelectedNode.hpp>
#include <vgGTK/actions/Icons.hpp>
#include <vgUI/actions/IActionUI.hpp>


namespace vgGTK
{

namespace node
{

EditMenu::EditMenu()
:	m_actions( Gtk::ActionGroup::create() ),
	m_uiManager( Gtk::UIManager::create() )
{
	// Initializes the user interface manager.
	m_uiDefinition =
		"<ui>"
		"	<popup name='Edit'>"
		"      <menuitem action='CutNode'/>"
		"      <menuitem action='CopyNode'/>"
		"      <menuitem action='PasteNode'/>"
		"      <separator/>"
		"      <menuitem action='NextNode'/>"
		"      <menuitem action='PreviousNode'/>"
		"      <separator/>"
		"      <menuitem action='RemoveNode'/>"
		"      <separator/>"
		"      <menuitem action='EncryptFile'/>"
		"    </popup>"
		"</ui>";
	
	m_uiManager->add_ui_from_string( m_uiDefinition );

	vgd::Shp< vgUI::actions::ActionsRegistry > actionsRegistry = vgUI::actions::ActionsRegistry::getActionsRegistry();

	m_actionList.push_back( actionsRegistry->getAction( "CutNode" ) );
	m_actionList.push_back( actionsRegistry->getAction( "CopyNode" ) );
	m_actionList.push_back( actionsRegistry->getAction( "PasteNode" ) );
	m_actionList.push_back( actionsRegistry->getAction( "NextNode" ) );
	m_actionList.push_back( actionsRegistry->getAction( "PreviousNode" ) );
	m_actionList.push_back( actionsRegistry->getAction( "RemoveNode" ) );
	m_actionList.push_back( actionsRegistry->getAction( "EncryptFile" ) );

	std::list< vgd::Shp< vgUI::actions::IActionUI > >::iterator it = m_actionList.begin();

	for( it; it != m_actionList.end(); it++ )
	{
		Gtk::StockID stock = vgGTK::actions::getIcon( (*it)->getIcon() );
		m_actions->add(
				Gtk::Action::create( (*it)->getId(), stock, (*it)->getName(), (*it)->getName() ),
				Gtk::AccelKey( (*it)->getAccelKey() ),
				sigc::mem_fun( (*it)->getAction(), &vgAlg::actions::IAction::execute ) );
	}

	m_uiManager->insert_action_group( m_actions );

	//modify action when selection changed.
	vgAlg::actions::SelectedNode::getSelectedNodeObject()->signal_selection_changed.connect( boost::bind( &EditMenu::onSelectionChanged, this ) );
}



EditMenu::~EditMenu()
{
}



Gtk::Menu * EditMenu::getMenu()
{
	return dynamic_cast< Gtk::Menu * >( m_uiManager->get_widget("/Edit") );
}



Glib::RefPtr< Gtk::UIManager > EditMenu::getUIManager()
{
	return m_uiManager;
}



void EditMenu::onSelectionChanged()
{
	vgAlg::actions::input::INodeInput*		nodeInput;
	vgAlg::actions::input::IParentInput*	parentInput;
	
	std::list< vgd::Shp< vgUI::actions::IActionUI > >::iterator it = m_actionList.begin();
	
	for( it; it != m_actionList.end(); it++ )
	{
		vgAlg::actions::IAction* action = (*it)->getAction(); 
		if( nodeInput = dynamic_cast< vgAlg::actions::input::INodeInput* >( action ) )
		{
			nodeInput->setNode( vgAlg::actions::SelectedNode::getSelectedNodeObject()->getSelectedNode() );
		}
		if( parentInput = dynamic_cast< vgAlg::actions::input::IParentInput* >( action ) )
		{
			parentInput->setParent( vgAlg::actions::SelectedNode::getSelectedNodeObject()->getParentSelectedNode() );
		}
	}
}



} // namespace node

} // namespace vgGTK
