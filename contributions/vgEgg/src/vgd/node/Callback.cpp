// VGSDK - Copyright (C) 2006, 2008, Clement Forest.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

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
	// Add fields
	addField( new FPaintFunctionType(getFPaintFunction()) );
	addField( new FCbbFunctionType(getFCbbFunction()) );

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

	setPaintFunction( 0 );
	setCbbFunction( 0 );
}






// Paint Function

bool Callback::getPaintFunction( PaintFunctionType& value ) const
{
	return ( 
		vgd::field::getParameterValue< FunctionParameterType, PaintFunctionType >( this, getFPaintFunction(), PAINT_FUNCTION, value )
		);
}



void Callback::setPaintFunction(  PaintFunctionType value )
{
	vgd::field::setParameterValue< FunctionParameterType, PaintFunctionType >( this, getFPaintFunction(), PAINT_FUNCTION, value );
}



void Callback::erasePaintFunction()
{
	vgd::field::eraseParameterValue< FunctionParameterType, PaintFunctionType >( this, getFPaintFunction(), PAINT_FUNCTION );
}



const std::string Callback::getFPaintFunction()
{
	return ( "f_paintFunction" );
}



// Bounding Box Computation Function

bool Callback::getCbbFunction( CbbFunctionType& value ) const
{
	return ( 
		vgd::field::getParameterValue< FunctionParameterType, CbbFunctionType >( this, getFCbbFunction(), CBB_FUNCTION, value )
		);
}



void Callback::setCbbFunction(  CbbFunctionType value )
{
	vgd::field::setParameterValue< FunctionParameterType, CbbFunctionType >( this, getFCbbFunction(), CBB_FUNCTION, value );
}



void Callback::eraseCbbFunction()
{
	vgd::field::eraseParameterValue< FunctionParameterType, CbbFunctionType >( this, getFCbbFunction(), CBB_FUNCTION );
}



const std::string Callback::getFCbbFunction()
{
	return ( "f_cbbFunction" );
}



// IBoundingBox computation

bool Callback::computeBoundingBox( const vgm::MatrixR& transformation )
{
	bool			hasCbbFunction = false;
	CbbFunctionType	cbbFunction;
	
	hasCbbFunction = getCbbFunction( cbbFunction );
	if( hasCbbFunction )
	{
		cbbFunction(this);
	}
	else
	{
		m_boundingBox.makeEmpty();
	}

	m_transformation = transformation;
	return true;
}



bool Callback::isBoundingBoxValid() const
{
	return m_boundingBox.isInvalid() == false;
}



void Callback::invalidateBoundingBox( bool bInvalidate )
{
	// Nothing todo.
}




} // namespace node

} // namespace vgd
