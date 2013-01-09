// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/DepthOfField.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



vgd::Shp< DepthOfField > DepthOfField::create( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< DepthOfField > node( new DepthOfField(nodeName) );

	/* Adds a vertex (i.e. a node) to boost::graph */
	graph().addNode( node );

	/* Sets fields to their default values */
	node->setToDefaults();

	return node;
}



vgd::Shp< DepthOfField > DepthOfField::create( const std::string nodeName, const uint8 index )
{
	/* Creates a new node */
	vgd::Shp< DepthOfField > node = DepthOfField::create(nodeName);

	/* Sets index of multi-attributes */
	node->setMultiAttributeIndex(index);

	return node;
}



vgd::Shp< DepthOfField > DepthOfField::createWhole( const std::string nodeName )
{
	/* Creates a new node */
	vgd::Shp< DepthOfField > node = DepthOfField::create(nodeName);

	/* Sets optional fields to their default values */
	node->setOptionalsToDefaults();

	return node;
}



DepthOfField::DepthOfField( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Adds field(s)
	addField( new FFocusToFarType(getFFocusToFar()) );
	addField( new FFarMaximumBlurrinessType(getFFarMaximumBlurriness()) );
	addField( new FFocusType(getFFocus()) );
	addField( new FSamplingType(getFSampling()) );
	addField( new FFocusToNearType(getFFocusToNear()) );
	addField( new FNearMaximumBlurrinessType(getFNearMaximumBlurriness()) );
	addField( new FCameraModelType(getFCameraModel()) );

	// Sets link(s)

	link( getDFNode() );
}



void DepthOfField::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
	setFocusToFar( (1.f) );
	setFarMaximumBlurriness( (0.5f) );
	setFocus( (0.f) );
	setSampling( (8) );
	setFocusToNear( (1.f) );
	setNearMaximumBlurriness( (0.5f) );
	setCameraModel( (THIN_LENS) );
}



void DepthOfField::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();
}



// FocusToFar

const DepthOfField::FocusToFarValueType DepthOfField::DEFAULT_FOCUSTOFAR = (1.f);



const DepthOfField::FocusToFarValueType DepthOfField::getFocusToFar() const
{
	return getFieldRO<FFocusToFarType>(getFFocusToFar())->getValue();
}



void DepthOfField::setFocusToFar( const FocusToFarValueType value )
{
	getFieldRW<FFocusToFarType>(getFFocusToFar())->setValue( value );
}



// FarMaximumBlurriness

const DepthOfField::FarMaximumBlurrinessValueType DepthOfField::DEFAULT_FARMAXIMUMBLURRINESS = (0.5f);



const DepthOfField::FarMaximumBlurrinessValueType DepthOfField::getFarMaximumBlurriness() const
{
	return getFieldRO<FFarMaximumBlurrinessType>(getFFarMaximumBlurriness())->getValue();
}



void DepthOfField::setFarMaximumBlurriness( const FarMaximumBlurrinessValueType value )
{
	getFieldRW<FFarMaximumBlurrinessType>(getFFarMaximumBlurriness())->setValue( value );
}



// Focus

const DepthOfField::FocusValueType DepthOfField::DEFAULT_FOCUS = (0.f);



const DepthOfField::FocusValueType DepthOfField::getFocus() const
{
	return getFieldRO<FFocusType>(getFFocus())->getValue();
}



void DepthOfField::setFocus( const FocusValueType value )
{
	getFieldRW<FFocusType>(getFFocus())->setValue( value );
}



// Sampling

const DepthOfField::SamplingValueType DepthOfField::DEFAULT_SAMPLING = (8);



const DepthOfField::SamplingValueType DepthOfField::getSampling() const
{
	return getFieldRO<FSamplingType>(getFSampling())->getValue();
}



void DepthOfField::setSampling( const SamplingValueType value )
{
	getFieldRW<FSamplingType>(getFSampling())->setValue( value );
}



// FocusToNear

const DepthOfField::FocusToNearValueType DepthOfField::DEFAULT_FOCUSTONEAR = (1.f);



const DepthOfField::FocusToNearValueType DepthOfField::getFocusToNear() const
{
	return getFieldRO<FFocusToNearType>(getFFocusToNear())->getValue();
}



void DepthOfField::setFocusToNear( const FocusToNearValueType value )
{
	getFieldRW<FFocusToNearType>(getFFocusToNear())->setValue( value );
}



// NearMaximumBlurriness

const DepthOfField::NearMaximumBlurrinessValueType DepthOfField::DEFAULT_NEARMAXIMUMBLURRINESS = (0.5f);



const DepthOfField::NearMaximumBlurrinessValueType DepthOfField::getNearMaximumBlurriness() const
{
	return getFieldRO<FNearMaximumBlurrinessType>(getFNearMaximumBlurriness())->getValue();
}



void DepthOfField::setNearMaximumBlurriness( const NearMaximumBlurrinessValueType value )
{
	getFieldRW<FNearMaximumBlurrinessType>(getFNearMaximumBlurriness())->setValue( value );
}



// CameraModel

const DepthOfField::CameraModelValueType DepthOfField::getCameraModel() const
{
	return getFieldRO<FCameraModelType>(getFCameraModel())->getValue();
}



void DepthOfField::setCameraModel( const CameraModelValueType value )
{
	getFieldRW<FCameraModelType>(getFCameraModel())->setValue( value );
}



// Field name accessor(s)
const std::string DepthOfField::getFFocusToFar( void )
{
	return "f_focusToFar";
}



const std::string DepthOfField::getFFarMaximumBlurriness( void )
{
	return "f_farMaximumBlurriness";
}



const std::string DepthOfField::getFFocus( void )
{
	return "f_focus";
}



const std::string DepthOfField::getFSampling( void )
{
	return "f_sampling";
}



const std::string DepthOfField::getFFocusToNear( void )
{
	return "f_focusToNear";
}



const std::string DepthOfField::getFNearMaximumBlurriness( void )
{
	return "f_nearMaximumBlurriness";
}



const std::string DepthOfField::getFCameraModel( void )
{
	return "f_cameraModel";
}



IMPLEMENT_INDEXABLE_CLASS_CPP( , DepthOfField );



const vgd::basic::RegisterNode<DepthOfField> DepthOfField::m_registrationInstance;



} // namespace node

} // namespace vgd

