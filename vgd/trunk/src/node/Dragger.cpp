// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Dragger.hpp"

#include <limits>
#include "vgd/field/TAccessors.hpp"



namespace vgd
{

namespace node
{

Dragger::Dragger( const std::string nodeName ) :
	vgd::node::MatrixTransform( nodeName ),
	m_startingPoint(std::numeric_limits<float>::max(), std::numeric_limits<float>::max() )
{
	// Add field
	addField( new FActivateType(getFActivate()) );
	addField( new FSurroundType(getFSurround()) );
	addField( new FStateType(getFState()) );

	// Link(s)
	link( getDFNode() );
}



void Dragger::setToDefaults()
{
	MatrixTransform::setToDefaults();

	setActivate( true );
	//setSurround()
	setState( 0 );
}



void Dragger::setOptionalsToDefaults()
{
	MatrixTransform::setOptionalsToDefaults();
}



// ACTIVATE
const Dragger::ActivateValueType Dragger::getActivate() const
{
	return ( getFieldRO<FActivateType>(getFActivate())->getValue() );
}



void Dragger::setActivate( const ActivateValueType value )
{
	getFieldRW<FActivateType>(getFActivate())->setValue( value );
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
const Dragger::StateValueType Dragger::getState() const
{
	return ( getFieldRO<FStateType>(getFState())->getValue() );
}



void Dragger::setState( const StateValueType value )
{
	getFieldRW<FStateType>(getFState())->setValue( value );
}



const std::string Dragger::getFActivate()
{
	return ( "f_activate" );
}



const std::string Dragger::getFSurround()
{
	return ( "f_surround" );
}



const std::string Dragger::getFState()
{
	return ( "f_state" );
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



} // namespace node

} // namespace vgd
