// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Depth.hpp"

#include "vgd/field/TAccessors.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( Depth );



Depth::Depth( const std::string nodeName ) :
	vgd::node::SingleAttribute( nodeName )
{
	// Add field
	addField( new FFunctionType(getFFunction()) );
	addField( new FMaskType(getFMask()) );

	// Link(s)
	link( getDFNode() );
}



void Depth::setToDefaults()
{
	SingleAttribute::setToDefaults();
}



void Depth::setOptionalsToDefaults()
{
	SingleAttribute::setOptionalsToDefaults();

	setFunction( FUNCTION_DEFAULT );
	setMask( MASK_DEFAULT );
}






// FUNCTION
bool Depth::getFunction( FunctionValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< FunctionParameterType, FunctionValueType >( this, getFFunction(), FUNCTION, value )
		);
}



void Depth::setFunction( FunctionValueType value )
{
	vgd::field::setParameterValue< FunctionParameterType, FunctionValueType >( this, getFFunction(), FUNCTION, value );
}



void Depth::eraseFunction()
{
	vgd::field::eraseParameterValue< FunctionParameterType, FunctionValueType >( this, getFFunction(), FUNCTION );
}



// MASK
bool Depth::getMask( MaskValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< MaskParameterType, MaskValueType >( this, getFMask(), MASK, value )
		);
}



void Depth::setMask( MaskValueType value )
{
	vgd::field::setParameterValue< MaskParameterType, MaskValueType >( this, getFMask(), MASK, value );
}



void Depth::eraseMask()
{
	vgd::field::eraseParameterValue< MaskParameterType, MaskValueType >( this, getFMask(), MASK );
}



const std::string Depth::getFFunction()
{
	return ( "f_function" );
}



const std::string Depth::getFMask()
{
	return ( "f_mask" );
}



} // namespace node

} // namespace vgd
