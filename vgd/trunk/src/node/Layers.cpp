// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Layers.hpp"

#include <sstream>

#include "vgd/field/TAccessors.hpp"
#include "vgd/node/Quad.hpp"
#include "vgd/node/Switch.hpp"
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
	
	// texture2D
	vgd::Shp< vgd::node::Texture2D > pTex;
	
	for(	int32 i = index;
			i < iMax;
			++i )
	{
		pTex = vgd::node::Texture2D::create( "layers.subgraph.tex" );
	
		pTex->setWrap( vgd::node::Texture2D::WRAP_S, vgd::node::Texture2D::ONCE );
		pTex->setWrap( vgd::node::Texture2D::WRAP_T, vgd::node::Texture2D::ONCE );
	
		pTex->setFilter( vgd::node::Texture2D::MIN_FILTER, vgd::node::Texture2D::NEAREST );
		pTex->setFilter( vgd::node::Texture2D::MAG_FILTER, vgd::node::Texture2D::NEAREST );
		
		getSwitch()->addChild( pTex );
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
