// VGSDK - Copyright (C) 2006, Clement Forest.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Callback.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( Callback );



Callback::Callback( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Add field
	addField( new FFunctionType(getFFunction()) );

	// Link(s)
	link( getDFNode() );
}



void Callback::setToDefaults()
{
	SingleAttribute::setToDefaults();
}



void Callback::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();

	setCallback( 0 );
}






// CALLBACK

bool Callback::getCallback( CallbackType& value ) const
{
	return ( 
		vgd::field::getParameterValue< FunctionParameterType, CallbackType >( this, getFFunction(), CALLBACKFUNCTION, value )
		);
}

void Callback::setCallback(  CallbackType value )
{
	vgd::field::setParameterValue< FunctionParameterType, CallbackType >( this, getFFunction(), CALLBACKFUNCTION, value );
}



void Callback::eraseCallback()
{
	vgd::field::eraseParameterValue< FunctionParameterType, CallbackType >( this, getFFunction(), CALLBACKFUNCTION );
}





const std::string Callback::getFFunction()
{
	return ( "f_function" );
}



} // namespace node

} // namespace vgd
