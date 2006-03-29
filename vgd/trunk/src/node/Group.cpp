// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Group.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( Group );



Group::Group( const std::string nodeName ) :
	Node(nodeName)
{
	// Add dirty flags.
	addDirtyFlag(getDFChildren());
	addDirtyFlag(getDFChildrenSelection());
	
	addDirtyFlag(getDFBoundingBox());
	
	// Links.
	//link( getFChildren(),				getDFBoundingBox() );
	//link( getFChildrenSelection(),	getDFBoundingBox() );

	//
	link( getDFNode() );
}



void Group::setToDefaults( void )
{
	Node::setToDefaults();

	// IBoundingBox
	reset();
	
	Group::updateGraph();
}



void Group::setOptionalsToDefaults()
{
	Node::setOptionalsToDefaults();
}



void Group::addChild( vgd::Shp<vgd::node::Node> node )
{
	graph().addEdge( this, node.get() );

	getDirtyFlag(getDFChildren())->dirty();
	getDirtyFlag(getDFBoundingBox())->dirty();
	getDirtyFlag(getDFNode())->dirty();
	
	updateGraph();	
}



void Group::insertChild	( vgd::Shp<Node> node, const int32 newChildIndex )
{
	assert(	(newChildIndex>=0 && newChildIndex<=getNumChildren()) && "Wrong index." );

	if ( newChildIndex == getNumChildren() )
	{
		graph().addEdge( this, node.get() );
	}
	else
	{
		graph().addEdge( this, node.get(), newChildIndex );
	}
	
	getDirtyFlag(getDFChildren())->dirty();
	getDirtyFlag(getDFBoundingBox())->dirty();
	getDirtyFlag(getDFNode())->dirty();
	
	updateGraph();	
}



void Group::replaceChild( vgd::Shp<Node> newChild, const int32 index )
{
	assert( checkChildIndex(index) && "index is out of range." );

	removeChild( index );
	insertChild( newChild, index );

//	graph().removeEdge( this, index,
//		false // no repacking
//		);
//
//	graph().addEdge( this, newChild.get(), index );
	
	getDirtyFlag(getDFChildren())->dirty();
	getDirtyFlag(getDFBoundingBox())->dirty();
	getDirtyFlag(getDFNode())->dirty();
	
	updateGraph();	
}



void Group::replaceChild( vgd::Shp<Node> oldChild, vgd::Shp<Node> newChild )
{
	int32 index = findChild( oldChild );
	
	if ( index < getNumChildren() )
	{
		// Found oldChild.
		replaceChild( newChild, index );
	}
	//else oldChild not found.
}



void Group::removeChild( const int32 childIndex )
{
	assert( checkChildIndex(childIndex) && "index is out of range." );

	graph().removeEdge( this, childIndex,
		true // repacking
		);
		
	getDirtyFlag(getDFChildren())->dirty();
	getDirtyFlag(getDFBoundingBox())->dirty();
	getDirtyFlag(getDFNode())->dirty();
	
	updateGraph();	
}



bool Group::removeChild( vgd::Shp<Node> childToRemove )
{
	int32 index = findChild( childToRemove );

	assert( index >= 0 && "vgd::Group::removeChild(): Unexpected value returned by findChild()." );
	
	if ( index < getNumChildren() )
	{
		// Found childToRemove.
		removeChild( index );
		return ( true );
	}
	else
	{
		// childToRemove not found.	
		return ( false );
	}
}



void Group::removeAllChildren( void )
{
	graph().removeEdges( this );
	
	getDirtyFlag(getDFChildren())->dirty();
	getDirtyFlag(getDFBoundingBox())->dirty();
	getDirtyFlag(getDFNode())->dirty();
	
	updateGraph();	
}



bool Group::containsChild( const vgd::Shp<Node> node ) const
{
	return ( graph().containsChild( this, node.get() ) );
}



int32 Group::findChild( const vgd::Shp<Node> node ) const
{
	return ( graph().findChild( this, node.get() ) );
}



vgd::Shp<vgd::node::Node> Group::getAbstractChild( const int32 index )
{
	assert( checkChildIndex(index) && "index is out of range." );

	return ( graph().getChild( this, index ) );
}



void Group::getChildren( NodeList& children) const
{
	graph().getChildren( this, children );
}



int32 Group::getNumChildren( void ) const
{
	return ( graph().getNumChildren( this ) );
}



void Group::getEnabledChildren( NodeList& children, const bool bGetEnabled ) const
{
	graph().getEnabledChildren( this, children, bGetEnabled );
}



void Group::updateGraph( void )
{
	getDirtyFlag(getDFChildren())->validate();
	getDirtyFlag(getDFChildrenSelection())->validate();
	getDirtyFlag(getDFNode())->validate();
}



/**
 * Bounding box dirty flag is validate when calling this method.
 * 
 * It could be invalidate by child (of VertexShape type) when using vge::service::ComputeBoundingBox service.
 * It is invalidate when RW access to fields named \c children or \c childrenSelection.
 * 
 * Parents nodes are invalidated when this node is invalid.
 */
bool Group::computeBoundingBox( const vgm::MatrixR& transformation /* not used */)
{
	// STEP 1: init.
	bool	bRetVal;
	bool	bInvalidateParents;
	
	bInvalidateParents	= false;
	bRetVal				= false;
	
	// update transformation
	// nothing to do.
	
	// STEP 2: update bounding box.
	vgd::field::DirtyFlag *pDirtyFlag = getDirtyFlag( getDFBoundingBox() );
	assert( pDirtyFlag != 0 );
	
	if ( pDirtyFlag->isDirty() )
	{
		bInvalidateParents	= true;
		bRetVal				= true;
		
		// compute bb		
		
		// update bounding box
		m_boundingBox.makeEmpty();
		
		NodeList	children;
		getEnabledChildren( children, true );

		for(	NodeList::iterator i = children.begin(),
				iend = children.end();
				
				i != iend;
				
				++i )
		{
			vgd::Shp< vgd::node::IBoundingBox > ibb( vgd::dynamic_pointer_cast< vgd::node::IBoundingBox >( *i ) );
				
			if ( ibb.get() == 0 )
			{
				continue;
			}

			if ( ibb->isBoundingBoxValid() )
			{
				vgm::Box3f box;
				
				box = ibb->getProjectXfBoundingBox();
				
				if ( !box.isEmpty() )
				{
					m_boundingBox.extendBy( box );
				}
			}
			else
			{
				assert( false && "Invalid child bounding box." );
			}
		}
	
		pDirtyFlag->validate();
	}
	
	if ( bInvalidateParents )
	{
		invalidateParentsBoundingBoxDirtyFlag();
	}
	
	return ( bRetVal );
}



bool Group::isBoundingBoxValid() const
{
	return ( getDirtyFlag( getDFBoundingBox() )->isValid() );
}



void Group::invalidateBoundingBox( bool bInvalidate )
{
	getDirtyFlag( getDFBoundingBox() )->dirty( bInvalidate );
}



void Group::writeGraphviz( std::ostream& out ) const
{
	graph().writeGraphviz( this, out );
}



const std::string Group::getDFChildren( void )
{
	return ( "df_children" );
}



const std::string Group::getDFChildrenSelection( void )
{
	return ( "df_childrenSelection" );
}


const std::string Group::getDFBoundingBox( void )
{
	return ( "df_boundingBox" );
}



bool Group::checkChildIndex( const int32 index ) const
{
	return (	(index>=0) &&
				(index<getNumChildren())	);
}



} // namespace node

} // namespace vgd
