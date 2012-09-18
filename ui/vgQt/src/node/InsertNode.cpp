// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include <boost/assign.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>

#include <vgd/node/ClipPlane.hpp>
#include <vgd/node/CullFace.hpp>
#include <vgd/node/DepthOfField.hpp>
#include <vgd/node/DirectionalLight.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/EngineProperties.hpp>
#include <vgd/node/Fluid.hpp>
#include <vgd/node/FrontFace.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/MatrixTransform.hpp>
#include <vgd/node/Noise.hpp>
#include <vgd/node/OutputBuffers.hpp>
#include <vgd/node/OutputBufferProperty.hpp>
#include <vgd/node/PointLight.hpp>
#include <vgd/node/PostProcessing.hpp>
#include <vgd/node/Separator.hpp>
#include <vgd/node/SpotLight.hpp>
#include <vgd/node/Transform.hpp>

#include <vgAlg/actions/SelectedNode.hpp>

#include "vgQt/node/Action.hpp"
#include "vgQt/node/InsertNode.hpp"

namespace vgQt
{

namespace node
{

typedef boost::mpl::vector<	vgd::Shp< vgd::node::ClipPlane >,
                            vgd::Shp< vgd::node::CullFace >,
                            vgd::Shp< vgd::node::DepthOfField >,
                            vgd::Shp< vgd::node::DirectionalLight >,
                            vgd::Shp< vgd::node::DrawStyle >,
                            vgd::Shp< vgd::node::EngineProperties >,
                            vgd::Shp< vgd::node::Fluid >,
                            vgd::Shp< vgd::node::FrontFace >,
                            vgd::Shp< vgd::node::Group >,
                            vgd::Shp< vgd::node::LightModel >,
                            vgd::Shp< vgd::node::Material >,
                            vgd::Shp< vgd::node::MatrixTransform >,
                            vgd::Shp< vgd::node::Noise >,
                            vgd::Shp< vgd::node::OutputBuffers >,
                            vgd::Shp< vgd::node::OutputBufferProperty >,
                            vgd::Shp< vgd::node::PointLight >,
                            vgd::Shp< vgd::node::PostProcessing >,
                            vgd::Shp< vgd::node::Separator >,
                            vgd::Shp< vgd::node::SpotLight >,
                            vgd::Shp< vgd::node::Transform >
                                > shapes;

static std::vector< std::string > names = boost::assign::list_of("ClipPlane")
                                                                ("CullFace")
                                                                ("DepthOfField")
                                                                ("DirectionalLight")
                                                                ("DrawStyle")
                                                                ("EngineProperties")
                                                                ("Fluid")
                                                                ("FrontFace")
                                                                ("Group")
                                                                ("LightModel")
                                                                ("Material")
                                                                ("MatrixTransform")
                                                                ("Noise")
                                                                ("OutputBuffers")
                                                                ("OutputBufferProperty")
                                                                ("PointLight")
                                                                ("PostProcessing")
                                                                ("Separator")
                                                                ("SpotLight")
                                                                ("Transform");

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

InsertNode::InsertNode(QWidget* parent)
    : QMenu("Insert Node", parent)
{
    CreateNodeList createNodeList( this );
    boost::mpl::for_each< shapes >( createNodeList );
    for( uint i = 0; i < names.size(); i++ )
    {
        Action *action = new Action(names[i], m_classNames[i], this);
        connect(action, SIGNAL(triggered(std::string)), this, SLOT(onInsertNode(std::string)));
        addAction(action);
    }
}

InsertNode::~InsertNode()
{

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

void InsertNode::onInsertNode( std::string name )
{
    CreateNode createNode( name, this );
    boost::mpl::for_each< shapes >( createNode );
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

} // node

} // vgQt
