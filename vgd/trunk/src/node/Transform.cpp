// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Transform.hpp"

#include <vgm/Matrix.hpp>



namespace vgd
{

namespace node
{



META_NODE_CPP( Transform );



Transform::Transform( const std::string nodeName ) :
	vgd::node::GeometricalTransformation( nodeName )
{
	// Add field
	addField( new FCenterType(getFCenter()) );
	addField( new FScaleOrientationType(getFScaleOrientation()) );
	addField( new FScaleFactorType(getFScaleFactor()) );
	addField( new FRotationType(getFRotation()) );
	addField( new FTranslationType(getFTranslation()) );

	// Link
	link( getDFNode() );
}



void Transform::setToDefaults( void )
{
	GeometricalTransformation::setToDefaults();

	setCenter				( vgm::Vec3f(0.f, 0.f, 0.f) );
	setScaleOrientation	( vgm::Rotation::getIdentity() );
	setScaleFactor			( vgm::Vec3f(1.f, 1.f, 1.f) );
	setRotation				( vgm::Rotation::getIdentity() );
	setTranslation			( vgm::Vec3f(0.f, 0.f, 0.f) );
}



void Transform::setOptionalsToDefaults()
{
	GeometricalTransformation::setOptionalsToDefaults();
}



const vgm::Vec3f Transform::getCenter( void ) const
{
	return ( getFieldRO<FCenterType>(getFCenter())->getValue() );
}



void Transform::setCenter( const vgm::Vec3f center )
{
	getFieldRW<FCenterType>(getFCenter())->setValue( center );
}



const vgm::Rotation	Transform::getScaleOrientation( void ) const
{
	return ( getFieldRO<FScaleOrientationType>(getFScaleOrientation())->getValue() );
}



void Transform::setScaleOrientation( const vgm::Rotation scaleOrientation )
{
	getFieldRW<FScaleOrientationType>(getFScaleOrientation())->setValue( scaleOrientation );
}



const vgm::Vec3f Transform::getScaleFactor( void ) const
{
	return ( getFieldRO<FScaleFactorType>(getFScaleFactor())->getValue() );
}



void Transform::setScaleFactor( const vgm::Vec3f scaleFactor )
{
	getFieldRW<FScaleFactorType>(getFScaleFactor())->setValue( scaleFactor );
}



const vgm::Rotation	Transform::getRotation( void ) const
{
	return ( getFieldRO<FRotationType>(getFRotation())->getValue() );
}



void Transform::setRotation( const vgm::Rotation rotation )
{
	getFieldRW<FRotationType>(getFRotation())->setValue( rotation );
}



const vgm::Vec3f Transform::getTranslation( void ) const
{
	return ( getFieldRO<FTranslationType>(getFTranslation())->getValue() );
}



void Transform::setTranslation( const vgm::Vec3f translation )
{
	getFieldRW<FTranslationType>(getFTranslation())->setValue( translation );
}



vgm::MatrixR Transform::gethMatrix() const
{
	vgm::MatrixR matrix;
	
	matrix.setTransform(
		getTranslation(),
		getRotation(),
		getScaleFactor(),
		getScaleOrientation(),
		getCenter()
		);
		
	return ( matrix );
}



void Transform::sethMatrix( const vgm::MatrixR& matrix, const vgm::Vec3f& center  )
{
	vgm::Vec3f		translation;
	vgm::Rotation	rotation;
	vgm::Vec3f		scaleFactor;	
	vgm::Rotation	scaleOrientation;

	matrix.getTransform( translation, rotation, scaleFactor, scaleOrientation, center );
	
	setTranslation(		translation );
	setRotation(			rotation );
	setScaleFactor(		scaleFactor );
	setScaleOrientation(	scaleOrientation );
	setCenter(				center );
}



const std::string Transform::getFCenter( void )
{
	return ( "f_center" );
}



const std::string Transform::getFScaleOrientation( void )
{
	return ( "f_scaleOrientation" );
}



const std::string Transform::getFScaleFactor( void )
{
	return ( "f_scaleFactor" );
}



const std::string Transform::getFRotation( void )
{
	return ( "f_rotation" );
}



const std::string Transform::getFTranslation( void )
{
	return ( "f_translation" );
}



} // namespace node

} // namespace vgd
