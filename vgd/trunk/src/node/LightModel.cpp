// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/LightModel.hpp"

#include "vgd/field/TAccessors.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( LightModel );



LightModel::LightModel( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Add field
	addField( new FModelType(getFModel()) );
	addField( new FAmbientType(getFAmbient()) );
	addField( new FViewerType(getFViewer()) );
	addField( new FTwoSidedType(getFTwoSided()) );

	// Link(s)
	link( getDFNode() );
}



void LightModel::setToDefaults( void )
{
	SingleAttribute::setToDefaults();
}



void LightModel::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();

	setModel(		DEFAULT_MODEL );
	setAmbient(		vgm::Vec4f( 0.2f, 0.2f, 0.2f, 1.0f ) );
	setViewer(		DEFAULT_VIEWER );
	setTwoSided(	false );
}



// MODEL
bool LightModel::getModel( ModelValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< ModelParameterType, ModelValueType >( this, getFModel(), MODEL, value )
		);
}



void LightModel::setModel( ModelValueType value )
{
	vgd::field::setParameterValue< ModelParameterType, ModelValueType >( this, getFModel(), MODEL, value );
}



void LightModel::eraseModel()
{
	vgd::field::eraseParameterValue< ModelParameterType, ModelValueType >( this, getFModel(), MODEL );
}



// AMBIENT
bool LightModel::getAmbient( AmbientValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< AmbientParameterType, AmbientValueType >( this, getFAmbient(), AMBIENT, value )
		);
}



void LightModel::setAmbient( AmbientValueType value )
{
	vgd::field::setParameterValue< AmbientParameterType, AmbientValueType >( this, getFAmbient(), AMBIENT, value );
}



void LightModel::eraseAmbient()
{
	vgd::field::eraseParameterValue< AmbientParameterType, AmbientValueType >( this, getFAmbient(), AMBIENT );
}



// VIEWER
bool LightModel::getViewer( ViewerValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< ViewerParameterType, ViewerValueType >( this, getFViewer(), VIEWER, value )
		);
}



void LightModel::setViewer( ViewerValueType value )
{
	vgd::field::setParameterValue< ViewerParameterType, ViewerValueType >( this, getFViewer(), VIEWER, value );
}



void LightModel::eraseViewer()
{
	vgd::field::eraseParameterValue< ViewerParameterType, ViewerValueType >( this, getFViewer(), VIEWER );
}



// TWO_SIDED
bool LightModel::getTwoSided( TwoSidedValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< TwoSidedParameterType, TwoSidedValueType >( this, getFTwoSided(), TWO_SIDED, value )
		);
}



void LightModel::setTwoSided( TwoSidedValueType value )
{
	vgd::field::setParameterValue< TwoSidedParameterType, TwoSidedValueType >( this, getFTwoSided(), TWO_SIDED, value );
}



void LightModel::eraseTwoSided()
{
	vgd::field::eraseParameterValue< TwoSidedParameterType, TwoSidedValueType >( this, getFTwoSided(), TWO_SIDED );
}



const std::string LightModel::getFModel( void )
{
	return ( "f_model" );
}



const std::string LightModel::getFAmbient( void )
{
	return ( "f_ambient" );
}



const std::string LightModel::getFViewer( void )
{
	return ( "f_viewer" );
}



const std::string LightModel::getFTwoSided( void )
{
	return ( "f_twoSided" );
}



} // namespace node

} // namespace vgd
