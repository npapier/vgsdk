// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/TransformDragger.hpp"

#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgd/event/MouseButtonEvent.hpp>

#include <vgm/Matrix.hpp>



namespace vgd
{

namespace node
{



META_NODE_CPP( TransformDragger );



TransformDragger::TransformDragger( const std::string nodeName ) :
	vgd::node::Dragger( nodeName )
{
	// Add field
	addField( new FCenterType(getFCenter()) );
	addField( new FRotationType(getFRotation()) );
	addField( new FTranslationType(getFTranslation()) );

	// Link
	link( getDFNode() );
}



void TransformDragger::setToDefaults( void )
{
	Dragger::setToDefaults();
	setCurrentState( TRANSFORMDRAGGER_DEFAULT );

	// Add feedback scene-graph.
	setBoundingBoxFeedback();
}



void TransformDragger::setOptionalsToDefaults()
{
	Dragger::setOptionalsToDefaults();
}



void TransformDragger::setTransformationToDefaults()
{
	setCenter				( vgm::Vec3f(0.f, 0.f, 0.f) );
	setRotation				( vgm::Rotation::getIdentity() );
	setTranslation			( vgm::Vec3f(0.f, 0.f, 0.f) );
}


	
void TransformDragger::setBindingsToDefaults()
{
	// .bindings
	using vgd::event::ButtonStateSet;
	using vgd::event::KeyboardButtonEvent;	
	using vgd::event::MouseButtonEvent;
	
	// rotation_xy*
	ButtonStateSet bssRotationXY;
	setBindings( ROTATION_XY, bssRotationXY );
	
	//
	bssRotationXY.setDown( MouseButtonEvent::MOUSE_BUTTON_1 );
	setBindings( ROTATION_XY_ACTIVE, bssRotationXY );

	// translation_xy*
	ButtonStateSet bssTranslationXY;
	bssTranslationXY.setDown( KeyboardButtonEvent::KEY_CONTROL );
	setBindings( TRANSLATION_XY, bssTranslationXY );
	
	bssTranslationXY.setDown( MouseButtonEvent::MOUSE_BUTTON_1 );
	setBindings( TRANSLATION_XY_ACTIVE, bssTranslationXY );
	
	// translation_z*
	ButtonStateSet bssTranslationZ;
	bssTranslationZ.setDown( KeyboardButtonEvent::KEY_SHIFT );
	setBindings( TRANSLATION_Z, bssTranslationZ );
	
	bssTranslationZ.setDown( MouseButtonEvent::MOUSE_BUTTON_1 );
	setBindings( TRANSLATION_Z_ACTIVE, bssTranslationZ );

	// rotation_z*
	ButtonStateSet bssRotationZ;
	bssRotationZ.setDown( KeyboardButtonEvent::KEY_CONTROL );
	bssRotationZ.setDown( KeyboardButtonEvent::KEY_SHIFT );
	setBindings( ROTATION_Z, bssRotationZ );

	bssRotationZ.setDown( MouseButtonEvent::MOUSE_BUTTON_1 );
	setBindings( ROTATION_Z_ACTIVE, bssRotationZ );
}



void TransformDragger::setBindingsToDefaults2()
{
	// .bindings
	using vgd::event::ButtonStateSet;
	using vgd::event::KeyboardButtonEvent;	
	using vgd::event::MouseButtonEvent;
	
	// rotation_xy*
	ButtonStateSet bssRotationXY;
	setBindings( ROTATION_XY, bssRotationXY );
	
	//
	bssRotationXY.setDown( MouseButtonEvent::MOUSE_BUTTON_1 );
	setBindings( ROTATION_XY_ACTIVE, bssRotationXY );

	// translation_xy*
	ButtonStateSet bssTranslationXY;
	bssTranslationXY.setDown( MouseButtonEvent::MOUSE_BUTTON_2 );
	//setBindings( TRANSLATION_XY, bssTranslationXY );
	setBindings( TRANSLATION_XY_ACTIVE, bssTranslationXY );
	
	// translation_z*
	ButtonStateSet bssTranslationZ;
	bssTranslationZ.setDown( MouseButtonEvent::MOUSE_BUTTON_3 );
	//setBindings( TRANSLATION_Z, bssTranslationZ );
	setBindings( TRANSLATION_Z_ACTIVE, bssTranslationZ );

	// rotation_z*
	ButtonStateSet bssRotationZ;
	bssRotationZ.setDown( MouseButtonEvent::MOUSE_BUTTON_1 );
	bssRotationZ.setDown( MouseButtonEvent::MOUSE_BUTTON_2 );	
	//setBindings( ROTATION_Z, bssRotationZ );
	setBindings( ROTATION_Z_ACTIVE, bssRotationZ );
}



void TransformDragger::setNullFeedback()
{
	setupNullFeedback( 9 );
}



void TransformDragger::setBoundingBoxFeedback()
{
	setupBoundingBoxFeedback( 9 );
}



const vgm::Vec3f TransformDragger::getCenter( void ) const
{
	return ( getFieldRO<FCenterType>(getFCenter())->getValue() );
}



void TransformDragger::setCenter( const vgm::Vec3f center )
{
	getFieldRW<FCenterType>(getFCenter())->setValue( center );
}



const vgm::Rotation	TransformDragger::getRotation( void ) const
{
	return ( getFieldRO<FRotationType>(getFRotation())->getValue() );
}



void TransformDragger::setRotation( const vgm::Rotation rotation )
{
	getFieldRW<FRotationType>(getFRotation())->setValue( rotation );
}



const vgm::Vec3f TransformDragger::getTranslation( void ) const
{
	return ( getFieldRO<FTranslationType>(getFTranslation())->getValue() );
}



void TransformDragger::setTranslation( const vgm::Vec3f translation )
{
	getFieldRW<FTranslationType>(getFTranslation())->setValue( translation );
}



vgm::MatrixR TransformDragger::computeMatrixFromFields() const
{
	vgm::MatrixR matrix;
	
	matrix.setTransform(
		getTranslation(),
		getRotation(),
		vgm::Vec3f(1.f, 1.f, 1.f),
		vgm::Rotation::getIdentity(),
		getCenter()
		);

	return ( matrix );
}



const std::string TransformDragger::getFCenter( void )
{
	return ( "f_center" );
}



const std::string TransformDragger::getFRotation( void )
{
	return ( "f_rotation" );
}



const std::string TransformDragger::getFTranslation( void )
{
	return ( "f_translation" );
}



} // namespace node

} // namespace vgd
