// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Trackball.hpp"


namespace vgd
{

namespace node
{



META_NODE_CPP( Trackball );



Trackball::Trackball( const std::string nodeName ) :
	vgd::node::Dragger( nodeName )
{
	// Add field
	addField( new FCenterType(getFCenter()) );
	addField( new FRotationType(getFRotation()) );

	// Link
	link( getDFNode() );	
}



void Trackball::setToDefaults()
{
	Dragger::setToDefaults();
	
	setCenter				( vgm::Vec3f(0.f, 0.f, 0.f) );
	setRotation				( vgm::Rotation::getIdentity() );		
}



void Trackball::setOptionalsToDefaults()
{
	Dragger::setOptionalsToDefaults();
}



// CENTER
const vgm::Vec3f Trackball::getCenter() const
{
	return ( getFieldRO<FCenterType>(getFCenter())->getValue() );
}



void Trackball::setCenter( const vgm::Vec3f center )
{
	getFieldRW<FCenterType>(getFCenter())->setValue( center );
}



// ROTATION
const vgm::Rotation	Trackball::getRotation() const
{
	return ( getFieldRO<FRotationType>(getFRotation())->getValue() );
}



void Trackball::setRotation( const vgm::Rotation rotation )
{
	getFieldRW<FRotationType>(getFRotation())->setValue( rotation );
}



vgm::MatrixR Trackball::computeMatrixFromFields() const
{
	vgm::MatrixR matrix;
	
	matrix.setTranslate( getCenter() );
	matrix.rotate( getRotation() );
	matrix.translate( -getCenter() );
	
	return ( matrix );
}



const std::string Trackball::getFCenter()
{
	return ( "f_center" );
}



const std::string Trackball::getFRotation()
{
	return ( "f_rotation" );
}



} // namespace node

} // namespace vgd
