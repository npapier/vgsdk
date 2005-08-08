// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/ILayers.hpp"

#include <sstream>
#include "vgd/field/TAccessors.hpp"



namespace vgd
{

namespace node
{



ILayers::ILayers( const std::string nodeName ) :
	vgd::node::Kit( nodeName )
{
}



void ILayers::setToDefaults( void )
{
	Kit::setToDefaults();
}



void ILayers::setOptionalsToDefaults()
{
	Kit::setOptionalsToDefaults();
}


	
void ILayers::createLayers( const int32 num )
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
}



const int32	ILayers::getNumLayers() const
{
	int32 i = 0;
	while ( isField( getFIImage(i) ) )
	{
		assert( isField( getFComposeOperator(i) ) );
		
		++i;
	}
	
	return ( i );
}



vgd::field::EditorRO< vgd::node::ILayers::FIImageType > ILayers::getFIImageRO( const int32 index ) const
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );

	return ( getFieldRO< FIImageType >(getFIImage( index )) );
}



vgd::field::EditorRW< vgd::node::ILayers::FIImageType > ILayers::getFIImageRW( const int32 index )
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );
		
	return ( getFieldRW< FIImageType >(getFIImage( index )) );
}



vgd::field::EditorRO< vgd::node::ILayers::FComposeOperatorType > ILayers::getFComposeOperatorRO( const int32 index ) const
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );
		
	return ( getFieldRO< FComposeOperatorType >(getFComposeOperator( index )) );
}



vgd::field::EditorRW< vgd::node::ILayers::FComposeOperatorType > ILayers::getFComposeOperatorRW( const int32 index )
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );
		
	return ( getFieldRW< FComposeOperatorType >(getFComposeOperator( index )) );
}



void ILayers::sethIImage( const int32 index, vgd::Shp< vgd::basic::IImage > iimage )
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );
		
	vgd::field::EditorRW< FIImageType > iimageRW( getFIImageRW( index ) );
	iimageRW->setValue( iimage );
}



vgd::Shp< vgd::basic::IImage > ILayers::gethIImage( const int32 index )
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );
		
	vgd::field::EditorRW< FIImageType > iimageRW( getFIImageRW( index ) );
	
	return ( iimageRW->getValue() );
}



const vgd::Shp< vgd::basic::IImage > ILayers::gethIImage( const int32 index ) const
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );

	vgd::field::EditorRO< FIImageType > iimageRO( getFIImageRO( index ) );
	
	return ( iimageRO->getValue() );
}



const int32 ILayers::gethFirstIImage() const throw()
{
	for(	int32	i	= 0,
					iEnd= getNumLayers();
			i != iEnd;
			++i )
	{
		vgd::Shp< vgd::basic::IImage > image( gethIImage(i) );
		
		if ( image != 0 )
		{
			return i;
		}
	}
	
	return ( -1 );
}
	

	
const vgm::Vec3i ILayers::gethIImageSize3i( const int32 index ) const
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );
		
	vgd::field::EditorRO< FIImageType > iimageRO( getFIImageRO( index ) );

	vgm::Vec3i retVal(
		iimageRO->getValue()->width(),
		iimageRO->getValue()->height(),
		iimageRO->getValue()->depth() );

	return ( retVal );
}



const vgm::Vec3f ILayers::gethIImageSize3f( const int32 index ) const
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );
		
	vgd::field::EditorRO< FIImageType > iimageRO( getFIImageRO( index ) );

	vgm::Vec3f retVal(
		static_cast<float>(iimageRO->getValue()->width()),
		static_cast<float>(iimageRO->getValue()->height()),
		static_cast<float>(iimageRO->getValue()->depth())
		);

	return ( retVal );
}



void ILayers::sethComposeOperator( const int32 index, const ComposeOperatorValueType& composeOperator )
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );
		
	vgd::field::EditorRW< FComposeOperatorType > composeOperatorRW( getFComposeOperatorRW( index ) );

	composeOperatorRW->setValue( composeOperator );
}



const ILayers::ComposeOperatorValueType ILayers::gethComposeOperator( const int32 index ) const
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );

	vgd::field::EditorRO< FComposeOperatorType > composeOperatorRO( getFComposeOperatorRO( index ) );
	
	return ( composeOperatorRO->getValue() );
}



const std::string ILayers::getFIImage( const int32 index )
{
	assert( index >= 0 && "Invalid index." );
	//assert( index < getNumLayers() && "Invalid index." );

	std::stringstream strStream;
	
	strStream << "f_iimage" << index << std::ends;
	
	return ( strStream.str() );
}



const std::string ILayers::getFComposeOperator( const int32 index )
{
	assert( index >= 0 && "Invalid index." );
	//assert( index < getNumLayers() && "Invalid index." );

	std::stringstream strStream;
	
	strStream << "f_composeOperator" << index << std::ends;
	
	return ( strStream.str() );
}



const std::string ILayers::getDFIImage( const int32 index )
{
	assert( index >= 0 && "Invalid index." );
	//assert( index < getNumLayers() && "Invalid index." );

	std::stringstream strStream;
	
	strStream << "df_iimage" << index << std::ends;

	return ( strStream.str() );	
}



} // namespace node

} // namespace vgd
