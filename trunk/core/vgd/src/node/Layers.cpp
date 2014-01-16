// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Layers.hpp"

#include <sstream>

#include "vgd/node/Quad.hpp"
#include "vgd/node/Switch.hpp"
#include "vgd/node/Texture1D.hpp"
#include "vgd/node/Texture2D.hpp"
#include "vgd/node/TextureMatrixTransform.hpp"
#include "vgd/node/detail/Node.hpp"



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
  
	pSwitch->addChild( quad );
	setRoot( pSwitch );
	
	//
	getQuad()->initializeGeometry( 1.f, 1.f );
	
	getQuad()->initializeTexUnits(); //1, origin, ccw
}



void Layers::setOptionalsToDefaults()
{
	ILayers::setOptionalsToDefaults();
}


	
void Layers::createLayers( const int32 num )
{
	ILayers::createLayers( num );
	
	const int32	index = 0;
	int32		iMax = index + num;

	// Finish the creation of the sub scene graph.
	
	// texture transformation
	using vgd::node::TextureMatrixTransform;
	
	vgd::Shp< TextureMatrixTransform >	pTexMatrixTransform;
	pTexMatrixTransform = TextureMatrixTransform::create("layers.subgraph.texMatrixTransform");
	getSwitch()->addChild( pTexMatrixTransform );
	
	// texture
	using vgd::node::Texture1D;
	using vgd::node::Texture2D;
	
	vgd::Shp< Texture2D >				pTex;
	vgd::Shp< Texture1D >				pColorTable;
	
	for(	int32 i = index;
			i < iMax;
			++i )
	{
		// texture2D
		pTex = Texture2D::create( "layers.subgraph.tex2D" );
	
		pTex->setWrapS( Texture2D::ONCE );
		pTex->setWrapT( Texture2D::ONCE );

		pTex->setMinFilter( Texture2D::NEAREST );
		pTex->setMagFilter( Texture2D::NEAREST );

		getSwitch()->addChild( pTex );
		
		// texture1D
		pColorTable = Texture1D::create( "layers.subgraph.tex1D" );
		pColorTable->setMultiAttributeIndex( 1 );
	
		pColorTable->setWrapS( Texture1D::ONCE );
		pColorTable->setWrapT( Texture1D::ONCE );
	
		pColorTable->setMinFilter( Texture1D::NEAREST );
		pColorTable->setMagFilter( Texture1D::NEAREST );

		getSwitch()->addChild( pColorTable );
	}
}



void Layers::resetGeometry()
{
	getQuad()->initializeGeometry( 1.f, 1.f );
}



void Layers::resetTextureCoordinates( const vgd::basic::Corner origin, const bool ccw )
{
	getQuad()->resetTextureCoordinates(1, origin, ccw);
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
		bRetVal				= true;

		setTransformation( pQuad->getTransformation() );
	}
	else
	{
		bInvalidateParents	= false;
		bRetVal				= false;
	}

	// STEP 3: update bounding box.
	if ( m_boundingBox != pQuad->getBoundingBox() )
	{
		bInvalidateParents	= true;
		bRetVal				= true;

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



vgm::MatrixR Layers::gethMatrix() const
{
	vgm::Vec3f translation = -getTranslation();
	
	assert( translation[2] == 0.f );
	
	vgm::Vec3f scaleFactor = getScaleFactor();
	scaleFactor[0] = 1.f/scaleFactor[0];
	scaleFactor[1] = 1.f/scaleFactor[1];
	assert( scaleFactor[2] == 1.f );

	vgm::MatrixR matrix;
	matrix.setTranslate( translation );
	matrix.scale( scaleFactor );
	
	return ( matrix );
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
