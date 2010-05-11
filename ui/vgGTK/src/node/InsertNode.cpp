// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/node/InsertNode.hpp"

#include <boost/assign.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>

#include <gtkmm/menu.h>

#include <vgd/node/ClipPlane.hpp>
#include <vgd/node/CullFace.hpp>
#include <vgd/node/DirectionalLight.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/FrontFace.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/PointLight.hpp>
#include <vgd/node/PostProcessing.hpp>
#include <vgd/node/SpotLight.hpp>
#include <vgd/node/Sphere.hpp>


#include <vgGTK/node/SelectedNode.hpp>

namespace vgGTK
{

namespace node
{

	typedef boost::mpl::vector<	vgd::Shp< vgd::node::ClipPlane >, 
								vgd::Shp< vgd::node::CullFace >,
								vgd::Shp< vgd::node::DirectionalLight >,
								vgd::Shp< vgd::node::DrawStyle >,
								vgd::Shp< vgd::node::FrontFace >,
								vgd::Shp< vgd::node::Group >,
								vgd::Shp< vgd::node::LightModel >,
								vgd::Shp< vgd::node::Material >,
								vgd::Shp< vgd::node::PointLight >,
								vgd::Shp< vgd::node::PostProcessing >,
								vgd::Shp< vgd::node::SpotLight >
									> shapes;

	static std::vector< std::string > names = boost::assign::list_of("ClipPlane")
																	("CullFace")
																	("DirectionalLight")
																	("DrawStyle")
																	("FrontFace")
																	("Group")
																	("LightModel")
																	("Material")
																	("PointLight")
																	("PostProcessing")
																	("SpotLight");

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



InsertNode::InsertNode()
{
	m_insertMenu = new Gtk::Menu();
	m_insertMenu->items().clear();

	CreateNodeList createNodeList( this );
	boost::mpl::for_each< shapes >( createNodeList );

	for( uint i = 0; i < names.size(); i++ )
	{
		Gtk::MenuItem	* item = new Gtk::MenuItem( names[i] );
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
	boost::mpl::for_each< shapes >( createNode );

	vgd::Shp< vgd::node::Node > node = m_currentNode.lock();
	vgd::Shp< vgd::node::Group > parentGroup = m_currentParentNode.lock();

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

	vgGTK::node::SelectedNode::getSelectedNode()->setAction( REFRESH );
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
