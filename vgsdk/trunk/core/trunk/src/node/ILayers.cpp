// VGSDK - Copyright (C) 2004, 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/ILayers.hpp"

#include <limits>
#include <sstream>
#include "vgd/field/TAccessors.hpp"



namespace vgd
{

namespace node
{



ILayers::ILayers( const std::string nodeName ) :
	vgd::node::Kit		( nodeName	),
	m_numLayers			( 0			),
	m_firstImageIndex	( std::numeric_limits<int32>::max() )
{
	// Add field
	addField( new FScaleFactorType(getFScaleFactor()) );
	addField( new FTranslationType(getFTranslation()) );

	// Add dirty flags
	addDirtyFlag( getDFTransformation() );
	
	// Link
	link( getFScaleFactor(),	getDFTransformation() );
	link( getFTranslation(),	getDFTransformation() );

	link( getDFNode() );
}



void ILayers::setToDefaults( void )
{
	Kit::setToDefaults();
	
	setScaleFactor			( vgm::Vec3f(1.f, 1.f, 1.f) );
	setTranslation			( vgm::Vec3f(0.f, 0.f, 0.f) );
}



void ILayers::setOptionalsToDefaults()
{
	Kit::setOptionalsToDefaults();
}


	
const vgm::Vec3f ILayers::getScaleFactor( void ) const
{
	return ( getFieldRO<FScaleFactorType>(getFScaleFactor())->getValue() );
}



void ILayers::setScaleFactor( const vgm::Vec3f scaleFactor )
{
	getFieldRW<FScaleFactorType>(getFScaleFactor())->setValue( scaleFactor );
}



const vgm::Vec3f ILayers::getTranslation( void ) const
{
	return ( getFieldRO<FTranslationType>(getFTranslation())->getValue() );
}



void ILayers::setTranslation( const vgm::Vec3f translation )
{
	getFieldRW<FTranslationType>(getFTranslation())->setValue( translation );
}



void ILayers::createLayers( const int32 num )
{
	assert( num >= 1 );
	
	// Stores the number of layers
	m_numLayers = num;

	const int32 index = 0;

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
	const int32	iMax = index + num;
	
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
	return m_numLayers;

// @todo remove me
//	int32 i = 0;
//	while ( isField( getFIImage(i) ) )
//	{
//		assert( isField( getFComposeOperator(i) ) );
//		
//		++i;
//	}
//
//	return i;
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
	
	// Invalidates first image index cache
	m_firstImageIndex = std::numeric_limits<int32>::max();
		
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



const std::string ILayers::getFScaleFactor( void )
{
	return ( "f_scaleFactor" );
}



const std::string ILayers::getFTranslation( void )
{
	return ( "f_translation" );
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



/**
 * @todo Returns getNumLayers() instead -1
 */
const int32 ILayers::gethFirstIImage() const
{
	// Tests first image index computation cache
	if ( m_firstImageIndex == std::numeric_limits<int32>::max() )
	{
		// First image index cache is invalid => compute it
		for(	int32	i	= 0,
						iEnd= getNumLayers();
				i != iEnd;
				++i )
		{
			vgd::Shp< vgd::basic::IImage > image( gethIImage(i) );
			
			if ( image != 0 )
			{
				// Found
				m_firstImageIndex = i;
				break;
			}
		}
		
		// Tests if not found after the loop
		if ( m_firstImageIndex == std::numeric_limits<int32>::max() )
		{
			// not found
			m_firstImageIndex = -1;
		}
	}
	
	// First image index cache is valid or has been computed
	assert( m_firstImageIndex != std::numeric_limits<int32>::max() );
	
	return m_firstImageIndex;
}



const bool ILayers::isEmpty() const
{
	const bool retVal = (gethFirstIImage() == -1);
	
	return retVal;
}



const vgm::Vec3i ILayers::gethIImageSize3i( const int32 index ) const
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );
		
	vgd::field::EditorRO< FIImageType > iimageRO( getFIImageRO( index ) );
	
	const vgm::Vec3i retVal( iimageRO->getValue()->getSize3i() );
	
	return retVal;
}



const vgm::Vec3f ILayers::gethIImageSize3f( const int32 index ) const
{
	assert( index >= 0 && "Invalid index." );
	assert( index < getNumLayers() && "Invalid index." );
		
	vgd::field::EditorRO< FIImageType > iimageRO( getFIImageRO( index ) );

	vgm::Vec3f retVal( iimageRO->getValue()->getSize3f() );

	return retVal;
}



const uint32 ILayers::gethSliceCount( const ::vgd::basic::SliceType sliceType ) const
{
	uint32 retVal;
	
	const int32 imageIndex( gethFirstIImage() );
	
	if ( imageIndex == -1 )
	{
		retVal = 0;
	}
	else
	{
		switch( sliceType )
		{
			case ::vgd::basic::AXIAL_SLICE:
				retVal = gethIImageSize3i( imageIndex )[2];
				break;
				
			case ::vgd::basic::FRONTAL_SLICE:
				retVal = gethIImageSize3i( imageIndex )[1];
				break;
			
			case ::vgd::basic::SAGITTAL_SLICE:
				retVal = gethIImageSize3i( imageIndex )[0];
				break;
			
			default:
				assert( false && "Unknown type of slice." );
				retVal = 0;
		}
	}
	
	return retVal;
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



const std::string ILayers::getDFTransformation()
{
	return ( "df_transformation" );
}



} // namespace node

} // namespace vgd
