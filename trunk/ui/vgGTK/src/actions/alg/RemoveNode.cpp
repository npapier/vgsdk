// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/actions/alg/RemoveNode.hpp"

#include <gtkmm/messagedialog.h>

#include <vgAlg/actions/RemoveNode.hpp>


namespace vgGTK
{

namespace actions
{

namespace alg
{


RemoveNode::RemoveNode()
{

}



RemoveNode::~RemoveNode()
{

}



void RemoveNode::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();
	vgd::Shp< vgd::node::Group > parent = m_parent.lock();	
	
	// Asks the user to confirm the node removal.
	const Glib::ustring	nodeName = node->getName();
	Gtk::MessageDialog	messageDialog("<big><b>Do you really want to remove the node <i>" + nodeName + "</i> ?</b></big>\n\nThis can break then rendering or may even cause the program to crash.", true, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_YES_NO );
	
	if( messageDialog.run() == Gtk::RESPONSE_YES )
	{
		::vgAlg::actions::RemoveNode removeNode;

		removeNode.setNode( node );
		removeNode.setParent( parent );
		removeNode.execute();
	}
}


} // namespace alg

} // namespace actions

} // namespace vgGTK
