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
	vgd::node::Kit( nodeName )
{
}



void Layers::setToDefaults( void )
{
	Kit::setToDefaults();
}



void Layers::setOptionalsToDefaults()
{
	Kit::setOptionalsToDefaults();
}


	
void Layers::createLayers( const int32 num, const float width, const float height )
{
	const int32 index = 0;
	
	assert( num >= 1 );

#ifdef _DEBUG
	for(	int32 i = index;
			i < index + num;
			++i)
	{
		assert( !isField( getFIImage(i) ) );
		assert( !isField( getFComposeOperator(i) ) );
	}
#endif

	// Add fields.
	int32	iMax = index + num;
	
	for(	int32 i = index;
			i < iMax;
			++i )
	{
		addField( new FIImageType(getFIImage(i)) );
		addField( new FComposeOperatorType(getFComposeOperator(i)) );
	}
	
	// Add dirty flags.
	for(	int32 i = index;
			i < iMax;
			++i )
	{
		addDirtyFlag( getDFIImage( i ) );
	}	
	
	// Links.
	for(	int32 i = index;
			i < iMax;
			++i )
	{
		link( getFIImage(i), getDFIImage( i ) );
		
		link( getFIImage(i), getDFNode() );
		link( getFComposeOperator(i), getDFNode() );
	}
	
	// Defaults value.
	for(	int32 i = index;
			i < iMax;
			++i )
	{
		sethComposeOperator( index, ComposeOperatorValueType() );
	}
	
	// Create sub scene graph.
	
	// switch
	vgd::Shp< vgd::node::Switch > pSwitch;
	pSwitch = vgd::node::Switch::create("layers.subgraph.switch");
	
	addChild( pSwitch );

	// Proxy geometry : QUAD
	vgd::Shp< vgd::node::Quad > quad( vgd::node::Quad::create("layers.subgraph.quad") );

	quad->initializeGeometry( width, height);
	quad->initializeTexUnits( 1 );
	
	pSwitch->addChild( quad );

	// texture2D
	vgd::Shp< vgd::node::Texture2D > pTex;
	
	for(	int32 i = index;
			i < iMax;
			++i )
	{
		pTex = vgd::node::Texture2D::create( "layers.subgraph.tex" );
	
		pTex->setWrap( vgd::node::Texture2D::WRAP_S, vgd::node::Texture2D::ONCE );
		pTex->setWrap( vgd::node::Texture2D::WRAP_T, vgd::node::Texture2D::ONCE );
	
		pTex->setFilter( vgd::node::Texture2D::MIN_FILTER, vgd::node::Texture2D::LINEAR );
		pTex->setFilter( vgd::node::Texture2D::MAG_FILTER, vgd::node::Texture2D::LINEAR );
		
		pSwitch->addChild( pTex );
	}
}



const int32	Layers::getNumLayers() const
{
	int32 i = 0;
	while ( isField( getFIImage(i) ) )
	{
		assert( isField( getFComposeOperator(i) ) );
		
		++i;
	}
	
	return ( i );
}



vgd::field::EditorRO< vgd::node::Layers::FIImageType > Layers::getFIImageRO( const int32 index ) const
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );

	return ( getFieldRO< FIImageType >(getFIImage( index )) );
}



vgd::field::EditorRW< vgd::node::Layers::FIImageType > Layers::getFIImageRW( const int32 index )
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );
		
	return ( getFieldRW< FIImageType >(getFIImage( index )) );
}



vgd::field::EditorRO< vgd::node::Layers::FComposeOperatorType > Layers::getFComposeOperatorRO( const int32 index ) const
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );
		
	return ( getFieldRO< FComposeOperatorType >(getFComposeOperator( index )) );
}



vgd::field::EditorRW< vgd::node::Layers::FComposeOperatorType > Layers::getFComposeOperatorRW( const int32 index )
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );
		
	return ( getFieldRW< FComposeOperatorType >(getFComposeOperator( index )) );
}



void Layers::sethIImage( const int32 index, vgd::Shp< vgd::basic::IImage > iimage )
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );
		
	vgd::field::EditorRW< FIImageType > iimageRW( getFIImageRW( index ) );
	iimageRW->setValue( iimage );
}



vgd::Shp< vgd::basic::IImage > Layers::gethIImage( const int32 index )
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );
		
	vgd::field::EditorRW< FIImageType > iimageRW( getFIImageRW( index ) );
	
	return ( iimageRW->getValue() );
}



void Layers::sethComposeOperator( const int32 index, const ComposeOperatorValueType& composeOperator )
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );
		
	vgd::field::EditorRW< FComposeOperatorType > composeOperatorRW( getFComposeOperatorRW( index ) );

	composeOperatorRW->setValue( composeOperator );
}



const Layers::ComposeOperatorValueType	Layers::gethComposeOperator( const int32 index )
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );

	vgd::field::EditorRO< FComposeOperatorType > composeOperatorRO( getFComposeOperatorRO( index ) );
	
	return ( composeOperatorRO->getValue() );
}



void Layers::setAlpha( vgd::Shp< vgd::basic::IImage > image, const float alpha )
{
	assert( image->format() == vgd::basic::IImage::RGBA );
	
	assert( alpha >= 0.f );
	assert( alpha <= 1.f );


	uint8	ui8Alpha;
	ui8Alpha	= static_cast< uint8 >( alpha * 255.f );

	// scan image
	uint8*		iPixel = image->editPixels();
	for(	uint8	*iEnd = iPixel + image->width()*image->height()*4;
			iPixel != iEnd;
			iPixel++ )
	{
		iPixel += 3;
		(*iPixel) = ui8Alpha;
	}
	image->editPixelsDone();
}



void Layers::setAlphaIfNotBlack( vgd::Shp< vgd::basic::IImage > image, const float alpha )
{
	assert( image->format() == vgd::basic::IImage::RGBA );
		
	assert( alpha >= 0.f );
	assert( alpha <= 1.f );

	uint8	ui8Alpha;
	ui8Alpha	= static_cast< uint8 >( alpha * 255.f );

	// scan image
	uint8*		iPixel = image->editPixels();
	for(	uint8	*iEnd = iPixel + image->width()*image->height()*4;
			iPixel != iEnd;
			iPixel++ )
	{
		if (	(iPixel[0] == 0) &&
				(iPixel[1] == 0) &&
				(iPixel[2] == 0) )
		{
			iPixel		+=	3;								
			(*iPixel)	=	0;
		}
		else
		{
			iPixel		+=	3;
			(*iPixel)	=	ui8Alpha;
		}	
	}
	image->editPixelsDone();
}



const std::string Layers::getFIImage( const int32 index )
{
	assert( index >= 0 && "Invalid index." );
	//assert( index < getNumLayers() && "Invalid index." );

	std::stringstream strStream;
	
	strStream << "f_iimage" << index << std::ends;
	
	return ( strStream.str() );
}



const std::string Layers::getFComposeOperator( const int32 index )
{
	assert( index >= 0 && "Invalid index." );
	//assert( index < getNumLayers() && "Invalid index." );

	std::stringstream strStream;
	
	strStream << "f_composeOperator" << index << std::ends;
	
	return ( strStream.str() );
}



const std::string Layers::getDFIImage( const int32 index )
{
	assert( index >= 0 && "Invalid index." );
	//assert( index < getNumLayers() && "Invalid index." );

	std::stringstream strStream;
	
	strStream << "df_iimage" << index << std::ends;

	return ( strStream.str() );	
}



} // namespace node

} // namespace vgd
