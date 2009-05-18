// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/CoordinateSystem.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( CoordinateSystem );



CoordinateSystem::CoordinateSystem( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Add fields
	addField( new FMaskType(getFMask()) );
	addField( new FMatrixType(getFMatrix()) );
	addField( new FViewportType(getFViewport()) );

	// Link(s)
	link( getFMask(), getDFNode() );
	//link( getDFNode() );	
}



void CoordinateSystem::setToDefaults()
{
	SingleAttribute::setToDefaults();

	setMask( DEFAULT_MASK );
}



void CoordinateSystem::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



// MASK
int8 CoordinateSystem::getMask() const
{
	return ( getFieldRO<FMaskType>(getFMask())->getValue() );
}



void CoordinateSystem::setMask( const int8 mask )
{
	getFieldRW<FMaskType>(getFMask())->setValue( mask );
}



// MATRIX
bool CoordinateSystem::getMatrix( const MatrixParameterType param, MatrixValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< MatrixParameterType, MatrixValueType >( this, getFMatrix(), param, value )
		);
}



void CoordinateSystem::setMatrix( const MatrixParameterType param, MatrixValueType value )
{
	vgd::field::setParameterValue< MatrixParameterType, MatrixValueType >( this, getFMatrix(), param, value );
}



void CoordinateSystem::eraseMatrix( const MatrixParameterType param )
{
	vgd::field::eraseParameterValue< MatrixParameterType, MatrixValueType >( this, getFMatrix(), param );
}



// VIEWPORT
bool CoordinateSystem::getViewport( vgm::Rectangle2i& value ) const
{
	return ( 
		vgd::field::getParameterValue< ViewportParameterType, ViewportValueType >( this, getFViewport(), VIEWPORT, value )
		);
}



void CoordinateSystem::setViewport( vgm::Rectangle2i value )
{
	vgd::field::setParameterValue< ViewportParameterType, ViewportValueType >( this, getFViewport(), VIEWPORT, value );
}



void CoordinateSystem::eraseViewport()
{
	vgd::field::eraseParameterValue< ViewportParameterType, ViewportValueType >( this, getFViewport(), VIEWPORT );
}



const std::string CoordinateSystem::getFMask( void )
{
	return "f_mask";
}



const std::string CoordinateSystem::getFMatrix()
{
	return "f_matrix";
}



const std::string CoordinateSystem::getFViewport( void )
{
	return "f_viewport";
}



} // namespace node

} // namespace vgd
