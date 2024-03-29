// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Kit.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



Kit::Kit( const std::string nodeName ) :
	Node( nodeName )
{
	// Add field
	addField( new FRootType(getFRoot()) );

	// Add dirty flags.
	addDirtyFlag(getDFBoundingBox());

	// Link(s)
	link( getDFNode() );
}



void Kit::setToDefaults( void )
{
	Node::setToDefaults();
	
	// IBoundingBox
	reset();
}



void Kit::setOptionalsToDefaults()
{
	Node::setOptionalsToDefaults();
}



// IBoundingBox interface
bool Kit::computeBoundingBox( const vgm::MatrixR& /* transformation */ )
{
	// STEP 1: init. and check matrix transformation.
	bool	bRetVal;
	bool	bInvalidateParents;

	vgd::Shp< vgd::node::Group > pRoot( getRoot() );
	if ( pRoot.get() == 0 )
	{
		// no sub-scene graph in this Kit.
		
		// validate the bounding box (empty one), could already be validate.
		invalidateBoundingBox( false );
		
		return ( false );
	}

	// update transformation
	if ( m_transformation != pRoot->getTransformation() )
	{
		bInvalidateParents	= true;
		bRetVal					= true;

		setTransformation( pRoot->getTransformation() );
	}
	else
	{
		bInvalidateParents	= false;
		bRetVal					= false;
	}

	// STEP 2: update bounding box.
	assert( pRoot->isBoundingBoxValid() && "Unexpected invalid bounding box in root sub scene graph in a kit." );

	if ( m_boundingBox != pRoot->getBoundingBox() )
	{
		bInvalidateParents	= true;
		bRetVal					= true;

		// compute bb
		setBoundingBox( pRoot->getBoundingBox() );
	}
	
	invalidateBoundingBox( false );

	//
	if ( bInvalidateParents )
	{
		invalidateParentsBoundingBoxDirtyFlag();
	}
	
	return ( bRetVal );
}



bool Kit::isBoundingBoxValid() const
{
	return ( getDirtyFlag( getDFBoundingBox() )->isValid() );
}



void Kit::invalidateBoundingBox( bool bInvalidate )
{
	getDirtyFlag( getDFBoundingBox() )->dirty( bInvalidate );
}



// ROOT
const Kit::RootValueType Kit::getRoot() const
{
	return ( getFieldRO<FRootType>(getFRoot())->getValue() );
}



void Kit::setRoot( const RootValueType value )
{
	getFieldRW<FRootType>(getFRoot())->setValue( value );
}



//
const std::string Kit::getFRoot()
{
	return ( "f_root" );
}



const std::string Kit::getDFBoundingBox()
{
	return ( "df_boundingBox" );
}



} // namespace node

} // namespace vgd
