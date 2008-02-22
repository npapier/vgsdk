// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/IDragger.hpp"

#include <limits>
#include "vgd/field/TAccessors.hpp"
#include "vgd/node/Group.hpp"




namespace vgd
{

namespace node
{



IDragger::IDragger( const std::string nodeName ) :
	vgd::node::Kit( nodeName )
{
	// Add field
	addField( new FListenerType(getFListener()) );
	addField( new FSurroundType(getFSurround()) );
	addField( new FCurrentStateType(getFCurrentState()) );

	// Link(s)
	link( getDFNode() );
}



void IDragger::setToDefaults()
{
	Kit::setToDefaults();
	
	// Initialize Kit.root (construct sub scene graph).
	//nothing to do

	// init. fields
	setListener( true );
	//setSurround()
	setCurrentState( IDragger::IDRAGGER_DEFAULT );
}



void IDragger::setOptionalsToDefaults()
{
	Kit::setOptionalsToDefaults();
}



// LISTENER
const IDragger::ListenerValueType IDragger::getListener() const
{
	return ( getFieldRO<FListenerType>(getFListener())->getValue() );
}



void IDragger::setListener( const ListenerValueType value )
{
	getFieldRW<FListenerType>(getFListener())->setValue( value );
}



// SURROUND
const IDragger::SurroundValueType IDragger::getSurround() const
{
	return ( getFieldRO<FSurroundType>(getFSurround())->getValue() );
}



void IDragger::setSurround( const SurroundValueType value )
{
	getFieldRW<FSurroundType>(getFSurround())->setValue( value );
}



// STATE
const IDragger::CurrentStateValueType IDragger::getCurrentState() const
{
	return ( getFieldRO<FCurrentStateType>(getFCurrentState())->getValue() );
}



void IDragger::setCurrentState( const CurrentStateValueType value )
{
	getFieldRW<FCurrentStateType>(getFCurrentState())->setValue( value );
}



const std::string IDragger::getFListener()
{
	return ( "f_listener" );
}



const std::string IDragger::getFSurround()
{
	return ( "f_surround" );
}



const std::string IDragger::getFCurrentState()
{
	return ( "f_currentState" );
}



} // namespace node

} // namespace vgd
