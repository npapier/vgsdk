// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/basic/TransferFunction.hpp"



namespace vgd
{
	
namespace basic
{



TransferFunction::TransferFunction()
 :	m_type( IDENTITY )
 	//m_points
{
}


const TransferFunction::Type TransferFunction::getType() const
{
	return m_type;
}


void TransferFunction::setType( const Type type )
{
	m_type = type;
}


void TransferFunction::insertPoint( const float input, const float output )
{
	m_points[input] = output;
}


const bool TransferFunction::removePoint( const float input )
{
	const bool hasBeenErased = (m_points.erase(input) >= 1);
	
	return hasBeenErased;
}


void TransferFunction::removePoints()
{
	m_points.clear();
}


const uint32 TransferFunction::getNumPoints() const
{
	return m_points.size();
}



} // namespace basic

} // namespace vgd
