// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Camera.hpp"

#include "vgd/field/TAccessors.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( Camera );



Camera::Camera( const std::string nodeName ) :
	vgd::node::ProjectionTransformation( nodeName )
{
	// Add field
	addField( new FMatrixType(getFMatrix()) );
	addField( new FViewportType(getFViewport()) );
	addField( new FScissorType(getFScissor()) );

	// Links
	link( getDFNode() );
}



void Camera::setToDefaults( void )
{
	ProjectionTransformation::setToDefaults();

	vgm::MatrixR identity;
	identity.setIdentity();
	
	setMatrix( identity );
}



void Camera::setOptionalsToDefaults()
{
	ProjectionTransformation::setOptionalsToDefaults();
	
	setViewport( 	vgm::Rectangle2i( 0, 0, 1600, 1200 ) );
	//setScissor( empty );
}



const vgm::MatrixR& Camera::getMatrix( void ) const
{
	return ( getFieldRO<FMatrixType>(getFMatrix())->getValue() );
}



void Camera::setMatrix( const vgm::MatrixR& projection )
{
	getFieldRW<FMatrixType>(getFMatrix())->setValue( projection );
}



bool Camera::getViewport( vgm::Rectangle2i& value ) const
{
	return ( 
		vgd::field::getParameterValue< ViewportParameterType, ViewportValueType >( this, getFViewport(), VIEWPORT, value )
		);
}



void Camera::setViewport( vgm::Rectangle2i value )
{
	vgd::field::setParameterValue< ViewportParameterType, ViewportValueType >( this, getFViewport(), VIEWPORT, value );
}



void Camera::eraseViewport()
{
	vgd::field::eraseParameterValue< ViewportParameterType, ViewportValueType >( this, getFViewport(), VIEWPORT );
}



bool Camera::getScissor( vgm::Rectangle2i& value ) const
{
	return ( 
		vgd::field::getParameterValue< ScissorParameterType, ScissorValueType >( this, getFScissor(), SCISSOR, value )
		);
}



void Camera::setScissor( vgm::Rectangle2i value )
{
	vgd::field::setParameterValue< ScissorParameterType, ScissorValueType >( this, getFScissor(), SCISSOR, value );
}



void Camera::eraseScissor()
{
	vgd::field::eraseParameterValue< ScissorParameterType, ScissorValueType >( this, getFScissor(), SCISSOR );
}



const std::string Camera::getFMatrix( void )
{
	return ( "f_matrix" );
}



const std::string Camera::getFViewport( void )
{
	return ( "f_viewport" );
}



const std::string Camera::getFScissor( void )
{
	return ( "f_scissor" );
}



} // namespace node

} // namespace vgd
