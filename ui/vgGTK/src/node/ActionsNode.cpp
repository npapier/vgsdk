// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/node/ActionsNode.hpp"

#include <vgAlg/node/TriSet.hpp>
#include <vgAlg/node/VertexShape.hpp>
#include <vgDebug/convenience.hpp>
#include <vgd/node/TriSet.hpp>
#include <vge/technique/ApplyGeometricalTransformations.hpp>
#include <vgeGL/engine/Engine.hpp>
#include <vgGTK/node/SelectedNode.hpp>
#include <vgOpenCOLLADA/exporter/SceneExporter.hpp>



namespace vgGTK
{

namespace node
{

ActionsNode::ActionsNode() 
{
}



ActionsNode::~ActionsNode()
{
}



void ActionsNode::setCanvas( vgUI::Canvas * canvas )
{
	m_canvas = canvas;
}



void ActionsNode::onGetNodeInTree()
{
	vgd::Shp< vgd::node::Node > node = vgGTK::node::SelectedNode::getSelectedNodeObject()->getSelectedNode();
	vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
	
	//During refresh, selection may change, so we reselect current node.
	vgGTK::node::SelectedNode::getSelectedNodeObject()->setSelectedNode( node );
	vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( SELECT );
	vgDebug::get().logStatus( "Node %s selected.", node->getName().c_str() );
}



void ActionsNode::onExpandSubTree()
{
	vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( EXPAND );
}



void ActionsNode::onRemoveNode()
{
	vgd::Shp< vgd::node::Node > node = vgGTK::node::SelectedNode::getSelectedNodeObject()->getSelectedNode();
	
	if( node )
	{
		vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( SELECT );
		vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( REMOVE );
		vgDebug::get().logStatus( "Node %s removed.", node->getName().c_str() );
	}
}



void ActionsNode::onHideNode()
{
	vgd::Shp< vgd::node::Node > node = vgGTK::node::SelectedNode::getSelectedNodeObject()->getSelectedNode();

	if( isAlreadyHidden( node ) )
	{
		return; //node is already hidden.
	}

	vgd::Shp< vgd::node::VertexShape > vertexShape = vgd::dynamic_pointer_cast< vgd::node::VertexShape >( node );

	vgd::Shp < HiddenNode > hidden = vgd::makeShp( new HiddenNode(vertexShape) );
	vgGTK::node::SelectedNode::getSelectedNodeObject()->getHiddenNodeList()->push_back( hidden );
	hidden->hide();

	vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );

	vgDebug::get().logStatus( "Node %s hidden.", node->getName().c_str() );
}



void ActionsNode::onShowNode( vgd::Shp < HiddenNode > hidden )
{
	hidden->restorePrimitives();

	vgGTK::node::SelectedNode::getSelectedNodeObject()->getHiddenNodeList()->remove(hidden);
	vgDebug::get().logStatus( "Node %s restored.", hidden->getNode()->getName().c_str() );
	hidden.reset();

	vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
}



void ActionsNode::onShowAllHiddenNode()
{
	vgd::Shp < HiddenNode > hidden;
	vgd::Shp< std::list< vgd::Shp < HiddenNode > > > hiddenNodes = vgGTK::node::SelectedNode::getSelectedNodeObject()->getHiddenNodeList();	
	std::list< vgd::Shp < HiddenNode > >::iterator it = hiddenNodes->begin();
	for( it; it !=  hiddenNodes->end(); )
	{
		hidden = (*it);
		it++;
		onShowNode( hidden );
	}
}



void ActionsNode::onHideAll()
{
	vgd::Shp< vgd::node::Node > node = vgGTK::node::SelectedNode::getSelectedNodeObject()->getSelectedNode();

	vgd::visitor::predicate::ByKindOfType<vgd::node::VertexShape> predicate;
	vgd::Shp< vgd::node::NodeList > result;
	result = vgd::visitor::find( m_canvas->getRoot(), predicate );

	std::list< vgd::Shp < vgd::node::Node > >::iterator it = result->begin();
	for( it; it !=  result->end(); it++ )
	{
		vgGTK::node::SelectedNode::getSelectedNodeObject()->setSelectedNode( (*it) );
		onHideNode();
	}

	vgGTK::node::SelectedNode::getSelectedNodeObject()->setSelectedNode( node );
}



void ActionsNode::onHideAllExceptSelected()
{
	vgd::Shp< vgd::node::Node > node = vgGTK::node::SelectedNode::getSelectedNodeObject()->getSelectedNode();

	vgd::visitor::predicate::ByKindOfType<vgd::node::VertexShape> predicate;
	vgd::Shp< vgd::node::NodeList > result;
	result = vgd::visitor::find( m_canvas->getRoot(), predicate );

	std::list< vgd::Shp < vgd::node::Node > >::iterator it = result->begin();
	for( it; it !=  result->end(); it++ )
	{
		if ( node != (*it) )
		{
			vgGTK::node::SelectedNode::getSelectedNodeObject()->setSelectedNode( (*it) );
			onHideNode();
		}
	}

	vgGTK::node::SelectedNode::getSelectedNodeObject()->setSelectedNode( node );
}



void ActionsNode::onExportNode()
{
	vgd::Shp< vgd::node::Node > node = vgGTK::node::SelectedNode::getSelectedNodeObject()->getSelectedNode();
	vgGTK::node::SelectedNode::getSelectedNodeObject()->setSelectedNode( node );
	vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( EXPORT );
	vgDebug::get().logStatus( "Node %s exported.", node->getName().c_str() );
}



void ActionsNode::onSetToDefault()
{
	vgd::Shp< vgd::node::Node > node = vgGTK::node::SelectedNode::getSelectedNodeObject()->getSelectedNode();

	node->setToDefaults();

	vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
}



void ActionsNode::onSetOptionalToDefault()
{
	vgd::Shp< vgd::node::Node > node = vgGTK::node::SelectedNode::getSelectedNodeObject()->getSelectedNode();

	node->setOptionalsToDefaults();

	vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
}



void ActionsNode::onInvertTriangleOrientation()
{
	vgd::Shp< vgd::node::Node > node = vgGTK::node::SelectedNode::getSelectedNodeObject()->getSelectedNode();
	
	if( node->isA<vgd::node::VertexShape>() )
	{
		vgAlg::node::invertPrimitiveOrientation( vgd::dynamic_pointer_cast< vgd::node::VertexShape >( node ) );
	}
	else if( node->isA<vgd::node::TriSet>() )
	{
		vgAlg::node::invertTriangleOrientation( vgd::dynamic_pointer_cast< vgd::node::TriSet >( node ) );
	}

	vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
}



void ActionsNode::onInvertNormalOrientation()
{
	vgd::Shp< vgd::node::Node > node = vgGTK::node::SelectedNode::getSelectedNodeObject()->getSelectedNode();

	vgAlg::node::invertNormalOrientation( vgd::dynamic_pointer_cast< vgd::node::VertexShape >( node ) );

	vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
}



void ActionsNode::onApplyGeometricalTransformation()
{
	using vge::visitor::NodeCollectorExtended;
	vge::technique::ApplyGeometricalTransformations technique;
	vgeGL::engine::Engine* engine = new vgeGL::engine::Engine();
	NodeCollectorExtended<> collector( true, false, NodeCollectorExtended<>::IGNORE_KIT );
	m_canvas->getRoot()->traverse( collector );
	technique.apply( engine, collector.getTraverseElements() );

	vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
}



void ActionsNode::onPreviousNode()
{
	vgd::Shp< vgd::node::Node > node = vgGTK::node::SelectedNode::getSelectedNodeObject()->getSelectedNode();
	vgd::Shp< vgd::node::Group > parentGroup = vgGTK::node::SelectedNode::getSelectedNodeObject()->getParentSelectedNode();

	if( node && parentGroup )
	{
		int index = parentGroup->findChild( node );

		if ( index > 0 )
		{
			vgd::Shp< vgd::node::Node > prevNode = parentGroup->getAbstractChild( index - 1 );

			parentGroup->replaceChild( node, index - 1 );
			parentGroup->replaceChild( prevNode, index );

			vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( MOVE_PREVIOUS );

			//vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );

			////during refresh, selection change, we have to reselect it.
			//vgGTK::node::SelectedNode::getSelectedNodeObject()->setSelectedNode( node );
			//vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( SELECT );


		}
	}	
}



void ActionsNode::onNextNode()
{
	vgd::Shp< vgd::node::Node > node = vgGTK::node::SelectedNode::getSelectedNodeObject()->getSelectedNode();
	vgd::Shp< vgd::node::Group > parentGroup = vgGTK::node::SelectedNode::getSelectedNodeObject()->getParentSelectedNode();

	if( node && parentGroup )
	{
		int index = parentGroup->findChild( node );

		if ( index < parentGroup->size() -1 )
		{
			vgd::Shp< vgd::node::Node > nextNode = parentGroup->getAbstractChild( index + 1 );
			parentGroup->replaceChild( node, index + 1 );
			parentGroup->replaceChild( nextNode, index );

			vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( MOVE_NEXT );

			//vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );

			//during refresh, selection change, we have to reselect it.
			//vgGTK::node::SelectedNode::getSelectedNodeObject()->setSelectedNode( node );
			//vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( SELECT );
		}
	}
}



void ActionsNode::onCutNode()
{
	vgd::Shp< vgd::node::Node > node = vgGTK::node::SelectedNode::getSelectedNodeObject()->getSelectedNode();
	vgd::Shp< vgd::node::Group > parentGroup = vgGTK::node::SelectedNode::getSelectedNodeObject()->getParentSelectedNode();

	if( node && parentGroup )
	{
		vgGTK::node::SelectedNode::getSelectedNodeObject()->setClipboardedNode( node );
		parentGroup->removeChild( node );
		vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
	}
}



void ActionsNode::onCopyNode()
{
	vgd::Shp< vgd::node::Node > node = vgGTK::node::SelectedNode::getSelectedNodeObject()->getSelectedNode();
	vgd::Shp< vgd::node::Group > parentGroup = vgGTK::node::SelectedNode::getSelectedNodeObject()->getParentSelectedNode();

	if( node && parentGroup )
	{
		vgGTK::node::SelectedNode::getSelectedNodeObject()->setClipboardedNode( node );
	}
}



void ActionsNode::onPasteNode()
{
	vgd::Shp< vgd::node::Node > node = vgGTK::node::SelectedNode::getSelectedNodeObject()->getSelectedNode();
	vgd::Shp< vgd::node::Group > parentGroup = vgGTK::node::SelectedNode::getSelectedNodeObject()->getParentSelectedNode();

	vgd::Shp< vgd::node::Node > clipboardedNode = vgGTK::node::SelectedNode::getSelectedNodeObject()->getClipboardedNode();
	if( clipboardedNode )
	{
		if( node )
		{
			if( node->isAKindOf<vgd::node::Group>() )
			{
				vgd::dynamic_pointer_cast< vgd::node::Group >( node )->addChild( clipboardedNode );
			}
			else if( parentGroup )
			{
				parentGroup->insertChild( clipboardedNode, parentGroup->findChild( node ) );
			}
		}

		vgGTK::node::SelectedNode::getSelectedNodeObject()->setAction( REFRESH );
	}
}


bool ActionsNode::isAlreadyHidden( vgd::Shp< vgd::node::Node > node )
{
	bool retVal = false;
	
	vgd::Shp < HiddenNode > hidden;
	vgd::Shp< std::list< vgd::Shp < HiddenNode > > > hiddenNodes = vgGTK::node::SelectedNode::getSelectedNodeObject()->getHiddenNodeList();	
	std::list< vgd::Shp < HiddenNode > >::iterator it = hiddenNodes->begin();
	for( it; it !=  hiddenNodes->end(); it++)
	{
		hidden = (*it);

		if( hidden->getNode() == node )
		{
			return true;
		}
	}

	return retVal;
}



int ActionsNode::getDisplayedNodeNumber()
{
	int counter = 0;

	vgd::visitor::predicate::ByKindOfType<vgd::node::VertexShape> predicate;
	vgd::Shp< vgd::node::NodeList > result;
	result = vgd::visitor::find( m_canvas->getRoot(), predicate );

	std::list< vgd::Shp < vgd::node::Node > >::iterator iter = result->begin();
	for( iter; iter !=  result->end(); iter++ )
	{
		if( !isAlreadyHidden( (*iter) ) )
		{
			counter++;
		}
	}

	return counter;
}



void ActionsNode::setCurrentNode( vgd::Shp< vgd::node::Node > node, vgd::Shp< vgd::node::Group > parentNode )
{
	m_currentNode = node;
	m_currentParentNode = parentNode;
}



} // namespace node

} // namespace vgGTK
