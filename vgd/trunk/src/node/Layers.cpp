// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Layers.hpp"

#include <sstream>

#include "vgd/field/TAccessors.hpp"
#include "vgd/node/Quad.hpp"
#include "vgd/node/Switch.hpp"
#include "vgd/node/Texture1D.hpp"
#include "vgd/node/Texture2D.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( Layers );



Layers::Layers( const std::string nodeName ) :
	vgd::node::ILayers( nodeName )
{
}



void Layers::setToDefaults( void )
{
	ILayers::setToDefaults();
	
	// partial creation of the sub scene graph
	
	// switch
	vgd::Shp< vgd::node::Switch > pSwitch ( vgd::node::Switch::create("layers.subgraph.switch") );
	
	// Proxy geometry : QUAD
	vgd::Shp< vgd::node::Quad > quad( vgd::node::Quad::create("layers.subgraph.quad") );
  
	quad->initializeGeometry( 1.f, 1.f );
	quad->initializeTexUnits( 1 );
	
	pSwitch->addChild( quad );
	
	setRoot( pSwitch );
}



void Layers::setOptionalsToDefaults()
{
	ILayers::setOptionalsToDefaults();
}


	
void Layers::createLayers( const int32 num )
{
	ILayers::createLayers( num );
	
	const int32	index = 0;
	int32			iMax = index + num;

	// Finish the creation of the sub scene graph.
	
	// texture
	vgd::Shp< vgd::node::Texture2D > pTex;
	vgd::Shp< vgd::node::Texture1D > pColorTable;
	
	for(	int32 i = index;
			i < iMax;
			++i )
	{
		// texture2D
		pTex = vgd::node::Texture2D::create( "layers.subgraph.tex2D" );
	
		pTex->setWrap( vgd::node::Texture2D::WRAP_S, vgd::node::Texture2D::ONCE );
		pTex->setWrap( vgd::node::Texture2D::WRAP_T, vgd::node::Texture2D::ONCE );
	
		pTex->setFilter( vgd::node::Texture2D::MIN_FILTER, vgd::node::Texture2D::NEAREST );
		pTex->setFilter( vgd::node::Texture2D::MAG_FILTER, vgd::node::Texture2D::NEAREST );
		
		getSwitch()->addChild( pTex );
		
		// texture1D
		pColorTable = vgd::node::Texture1D::create( "layers.subgraph.tex1D" );
		pColorTable->setMultiAttributeIndex( 1 );
	
		pColorTable->setWrap( vgd::node::Texture1D::WRAP_S, vgd::node::Texture1D::ONCE );
		pColorTable->setWrap( vgd::node::Texture1D::WRAP_T, vgd::node::Texture1D::ONCE );
	
		pColorTable->setFilter( vgd::node::Texture1D::MIN_FILTER, vgd::node::Texture1D::NEAREST );
		pColorTable->setFilter( vgd::node::Texture1D::MAG_FILTER, vgd::node::Texture1D::NEAREST );
		
		getSwitch()->addChild( pColorTable );		
	}
}



void Layers::resetGeometry()
{
	getQuad()->initializeGeometry( 1.f, 1.f );
}



void Layers::transform( const vgm::MatrixR& matrix, const bool normalize )
{
	getQuad()->transform( matrix, normalize );
}



void Layers::transform( const vgm::Vec3f translation )
{
	getQuad()->transform( translation );
}



// IBoundingBox interface
bool Layers::computeBoundingBox( const vgm::MatrixR& transformation )
{
	// STEP 1: compute quad bounding box.
	bool	bRetVal;
	bool	bInvalidateParents;
	
	vgd::Shp< vgd::node::Quad > pQuad( getQuad() );
	pQuad->computeBoundingBox( transformation );
	
	// STEP 2: update transformation
	if ( m_transformation != pQuad->getTransformation() )
	{
		bInvalidateParents	= true;
		bRetVal					= true;

		setTransformation( pQuad->getTransformation() );
	}
	else
	{
		bInvalidateParents	= false;
		bRetVal					= false;
	}

	// STEP 3: update bounding box.
	if ( m_boundingBox != pQuad->getBoundingBox() )
	{
		bInvalidateParents	= true;
		bRetVal					= true;

		// compute bb
		setBoundingBox( pQuad->getBoundingBox() );
	}
	
	invalidateBoundingBox( false );

	//
	if ( bInvalidateParents )
	{
		invalidateParentsBoundingBoxDirtyFlag();
	}
	
	return ( bRetVal );
}



vgd::Shp< vgd::node::Switch> Layers::getSwitch()
{
	vgd::Shp< vgd::node::Switch > pSwitch = vgd::dynamic_pointer_cast< vgd::node::Switch >( getRoot() );
	
	return ( pSwitch );
}



vgd::Shp< vgd::node::Quad > Layers::getQuad()
{
	return ( getRoot()->getChild< vgd::node::Quad >(0) );
}


	
} // namespace node

} // namespace vgd
