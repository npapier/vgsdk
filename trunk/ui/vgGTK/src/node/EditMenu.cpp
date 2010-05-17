// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/node/EditMenu.hpp"

#include <gtkmm/stock.h>
#include <gtkmm/window.h>


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
		"      <menuitem action='Cut'/>"
		"      <menuitem action='Copy'/>"
		"      <menuitem action='Paste'/>"
		"      <separator/>"
		"      <menuitem action='Next'/>"
		"      <menuitem action='Previous'/>"
		"      <separator/>"
		"      <menuitem action='Delete'/>"
		"    </popup>"
		"</ui>";
	
	m_actionsNode = vgd::Shp< ActionsNode >( new ActionsNode() );
	m_uiManager->add_ui_from_string( m_uiDefinition );


	//m_actions->add( Gtk::Action::create("Edit", "_Edit") );
	m_actions->add(
			Gtk::Action::create("Cut", Gtk::Stock::CUT),
			sigc::mem_fun(m_actionsNode.get(), &vgGTK::node::ActionsNode::onCutNode) );
	m_actions->add(
			Gtk::Action::create("Copy", Gtk::Stock::COPY),
			sigc::mem_fun(m_actionsNode.get(), &vgGTK::node::ActionsNode::onCopyNode) );
	m_actions->add(
			Gtk::Action::create("Paste", Gtk::Stock::PASTE),
			sigc::mem_fun(m_actionsNode.get(), &vgGTK::node::ActionsNode::onPasteNode) );
	m_actions->add(
			Gtk::Action::create("Next", Gtk::Stock::GO_FORWARD),
			Gtk::AccelKey("<control>Down"),
			sigc::mem_fun(m_actionsNode.get(), &vgGTK::node::ActionsNode::onNextNode) );
	m_actions->add(
			Gtk::Action::create("Previous", Gtk::Stock::GO_BACK),
			Gtk::AccelKey("<control>Up"),
			sigc::mem_fun(m_actionsNode.get(), &vgGTK::node::ActionsNode::onPreviousNode) );
	m_actions->add(
			Gtk::Action::create("Delete", Gtk::Stock::DELETE),
			Gtk::AccelKey("<control>Delete"),
			sigc::mem_fun(m_actionsNode.get(), &vgGTK::node::ActionsNode::onRemoveNode) );


	m_uiManager->insert_action_group( m_actions );
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



} // namespace node

} // namespace vgGTK
