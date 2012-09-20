// VGSDK - Copyright (C) 2010, 2011, 2012, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson
// Author Nicolas Papier

#include "vgUI/node/InsertNode.hpp"
#include "vgGTK/node/InsertNode.hpp"

#include <boost/mpl/for_each.hpp>
#include <gtkmm/menu.h>
#include <vgAlg/actions/SelectedNode.hpp>



namespace vgGTK
{

namespace node
{

namespace
{

struct CreateNodeList
{
	CreateNodeList( InsertNode* insertNode )
	:	m_insertNode( insertNode )
	{
	}

	template< typename NodeType, template< typename NodeType > class ContainerType >
	void operator() ( ContainerType< NodeType > value )
	{
		m_insertNode->addClassName( typeid( NodeType ).name() );
	}

private:
	InsertNode* m_insertNode;
};



struct CreateNode
{
	CreateNode( std::string name, InsertNode* insertNode )
	:	m_name( name ),
		m_insertNode( insertNode )
	{
	}

	template< typename NodeType, template< typename NodeType > class ContainerType >
	void operator() ( ContainerType< NodeType > value )
	{
		if( m_name == typeid( NodeType ).name() )
		{
			m_insertNode->setCreatedNode( NodeType::create("") );
		}
	}

private:
	std::string m_name;
	InsertNode* m_insertNode;
};

}



InsertNode::InsertNode()
{
	m_insertMenu = new Gtk::Menu();
	m_insertMenu->items().clear();

	CreateNodeList createNodeList( this );
	boost::mpl::for_each< vgUI::node::insertNodeShapes >( createNodeList );

	for( uint i = 0; i < vgUI::node::getInsertNodeNames().size(); i++ )
	{
		Gtk::MenuItem	* item = new Gtk::MenuItem( vgUI::node::getInsertNodeNames()[i] );
		item->signal_activate().connect( sigc::bind<0>( sigc::mem_fun(this, &InsertNode::onInsertNode), m_classNames[i] ) );
		m_insertMenu->append( *item );
	}
	m_insertMenu->show_all();
}



InsertNode::~InsertNode()
{
	delete m_insertMenu;
}



void InsertNode::onInsertNode( std::string name )
{
	CreateNode createNode( name, this );
	boost::mpl::for_each< vgUI::node::insertNodeShapes >( createNode );

	vgd::Shp< vgd::node::Node > node = vgAlg::actions::SelectedNode::getSelectedNodeObject()->getSelectedNode();
	vgd::Shp< vgd::node::Group > parentGroup = vgAlg::actions::SelectedNode::getSelectedNodeObject()->getParentSelectedNode();

	if( node )
	{
		if( node->isAKindOf<vgd::node::Group>() )
		{
			vgd::dynamic_pointer_cast< vgd::node::Group >( node )->addChild( m_createdNode );
		}
		else if( parentGroup )
		{
			parentGroup->insertChild( m_createdNode, parentGroup->findChild( node ) );
		}
	}

	vgAlg::actions::SelectedNode::getSelectedNodeObject()->setAction( vgAlg::actions::REFRESH );
}



Gtk::Menu * InsertNode::getMenu()
{
	return m_insertMenu;
}



void InsertNode::setCurrentNode( vgd::Shp< vgd::node::Node > currentNode, vgd::Shp< vgd::node::Group > currentParentNode )
{
	m_currentNode = currentNode;
	m_currentParentNode = currentParentNode; 
}

void InsertNode::setCreatedNode( vgd::Shp< vgd::node::Node > node )
{
	m_createdNode = node;
}



void InsertNode::addClassName( std::string name )
{
	m_classNames.push_back( name );
}



} // namespace node

} // namespace vgGTK
