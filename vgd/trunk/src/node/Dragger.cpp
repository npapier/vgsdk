// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Dragger.hpp"

#include <limits>
#include "vgd/field/TAccessors.hpp"
#include "vgd/node/Group.hpp"
#include "vgd/node/MatrixTransform.hpp"




namespace vgd
{

namespace node
{



Dragger::Dragger( const std::string nodeName ) :
	vgd::node::Kit( nodeName ),
	m_startingPoint(std::numeric_limits<float>::max(), std::numeric_limits<float>::max() )
{
	// Add field
	addField( new FListenerType(getFListener()) );
	addField( new FSurroundType(getFSurround()) );
	addField( new FCurrentStateType(getFCurrentState()) );
	addField( new FBindingsType(getFBindings()) );	

	// Link(s)
	link( getDFNode() );
}



void Dragger::setToDefaults()
{
	Kit::setToDefaults();
	
	// Initialize Kit.root (construct sub scene graph).
	using vgd::node::Group;
	using vgd::node::MatrixTransform;

	vgd::Shp< Group >					pGroup( Group::create("dragger.group") );
	vgd::Shp< MatrixTransform >	pMatrixTransform( MatrixTransform::create("dragger.group.matrixTransform") );

	setRoot( pGroup );
		
	pGroup->addChild( pMatrixTransform );
	
	//
	setListener( true );
	//setSurround()
	setCurrentState( Dragger::DRAGGER_DEFAULT );
	setBindingsToDefaults();
}



void Dragger::setOptionalsToDefaults()
{
	Kit::setOptionalsToDefaults();
}



// LISTENER
const Dragger::ListenerValueType Dragger::getListener() const
{
	return ( getFieldRO<FListenerType>(getFListener())->getValue() );
}



void Dragger::setListener( const ListenerValueType value )
{
	getFieldRW<FListenerType>(getFListener())->setValue( value );
}



// SURROUND
const Dragger::SurroundValueType Dragger::getSurround() const
{
	return ( getFieldRO<FSurroundType>(getFSurround())->getValue() );
}



void Dragger::setSurround( const SurroundValueType value )
{
	getFieldRW<FSurroundType>(getFSurround())->setValue( value );
}



// STATE
const Dragger::CurrentStateValueType Dragger::getCurrentState() const
{
	return ( getFieldRO<FCurrentStateType>(getFCurrentState())->getValue() );
}



void Dragger::setCurrentState( const CurrentStateValueType value )
{
	getFieldRW<FCurrentStateType>(getFCurrentState())->setValue( value );
}



// BINDINGS
bool Dragger::getBindings( const BindingsParameterType param, BindingsValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< BindingsParameterType, BindingsValueType >( this, getFBindings(), param, value )
		);
}



void Dragger::setBindings( const BindingsParameterType param, BindingsValueType value )
{
	vgd::field::setParameterValue< BindingsParameterType, BindingsValueType >( this, getFBindings(), param, value );
}



void Dragger::eraseBindings( const BindingsParameterType param )
{
	vgd::field::eraseParameterValue< BindingsParameterType, BindingsValueType >( this, getFBindings(), param );
}



const std::string Dragger::getFListener()
{
	return ( "f_listener" );
}



const std::string Dragger::getFSurround()
{
	return ( "f_surround" );
}



const std::string Dragger::getFCurrentState()
{
	return ( "f_currentState" );
}



const std::string Dragger::getFBindings()
{
	return ( "f_bindings" );
}



const vgm::Vec2f&	Dragger::getStartingPoint() const
{
	return ( m_startingPoint );
}



void Dragger::setStartingPoint( const vgm::Vec2f& startingPoint )
{
	m_startingPoint = startingPoint;
}



bool Dragger::isStartingPoint() const
{
	return ( m_startingPoint == vgm::Vec2f( std::numeric_limits<float>::max(), std::numeric_limits<float>::max() ) );
}



const vgm::MatrixR& Dragger::getMatrix() const
{
	const vgm::MatrixR& matrix( getMatrixTransform()->getMatrix() );
	
	return ( matrix );
}



void Dragger::setMatrix( const vgm::MatrixR& matrix )
{
	getMatrixTransform()->setMatrix( matrix );
}



vgd::Shp< vgd::node::MatrixTransform > Dragger::getMatrixTransform() const
{
	using vgd::node::MatrixTransform;
	
	vgd::Shp< MatrixTransform > pMatrixTransform = getRoot()->getChild<vgd::node::MatrixTransform>(0);
	
	return ( pMatrixTransform );
}



} // namespace node

} // namespace vgd
