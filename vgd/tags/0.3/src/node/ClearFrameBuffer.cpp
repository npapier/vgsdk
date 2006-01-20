// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/ClearFrameBuffer.hpp"

#include <string>

#include "vgd/field/TAccessors.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( ClearFrameBuffer );



ClearFrameBuffer::ClearFrameBuffer( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Add field
	addField( new FClearMaskType(getFClearMask()) );

	addField( new FClearType(getFClear()) );

	// Links
	link( getDFNode() );
}



void ClearFrameBuffer::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	
	setClearMask( COLOR_BUFFER_BIT | DEPTH_BUFFER_BIT );
}



void ClearFrameBuffer::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
	
	setClear( COLOR, vgm::Vec4f( 0.f, 0.f, 0.f, 0.f ) );
	setClear( ACCUM, vgm::Vec4f( 0.f, 0.f, 0.f, 0.f ) );
}



// CLEAR MASK
int8 ClearFrameBuffer::getClearMask() const
{
	return ( getFieldRO<FClearMaskType>(getFClearMask())->getValue() );
}



void ClearFrameBuffer::setClearMask( const int8 mask )
{
	getFieldRW<FClearMaskType>(getFClearMask())->setValue( mask );
}



// CLEAR
bool ClearFrameBuffer::getClear( const ClearParameterType param, ClearValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< ClearParameterType, ClearValueType >( this, getFClear(), param, value )
		);
}



void ClearFrameBuffer::setClear( const ClearParameterType param, ClearValueType value )
{
	vgd::field::setParameterValue< ClearParameterType, ClearValueType >( this, getFClear(), param, value );
}


void ClearFrameBuffer::eraseClear( const ClearParameterType param )
{
	vgd::field::eraseParameterValue< ClearParameterType, ClearValueType >( this, getFClear(), param );
}



const std::string ClearFrameBuffer::getFClearMask( void )
{
	return ( "f_clearMask" );
}



const std::string ClearFrameBuffer::getFClear( void )
{
	return ( "f_clear" );
}



} // namespace node

} // namespace vgd
