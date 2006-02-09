// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/basic/TransferFunction.hpp"

#include <cmath>
#include <vgm/Utilities.hpp>



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


void TransferFunction::getLookupTable( int32& inputBegin, int32& inputEnd, std::vector< int32 >& lut )
{
	assert( getNumPoints() >= 2 );

	assert( lut.size() == 0 );
	
	PointsContainer::const_iterator iterCurrent = m_points.begin();
	PointsContainer::const_iterator iterEnd		= m_points.end();

	inputBegin	= static_cast<int32>( std::floor(iterCurrent->first) );
	inputEnd	= static_cast<int32>( std::floor(m_points.rbegin()->first) );

	assert( inputBegin <= inputEnd );

	lut.reserve( inputEnd - inputBegin + 1 );

	switch ( m_type )
	{
		case IDENTITY:
		{
			int32 inputCurrent = inputBegin;
			
			while ( inputCurrent <= inputEnd )
			{
				lut.push_back( static_cast<int32>(inputCurrent) );
				
				++inputCurrent;
			}
			break;
		}
		
		case TABLE:
		{
			float input0	= iterCurrent->first;
			float output0	= iterCurrent->second;
			
			lut.push_back( static_cast<int32>(output0) );
			int32 inputCurrent = static_cast<int32>(input0) + 1;

			++iterCurrent;
			
			while ( iterCurrent != iterEnd )
			{
				const float input1	= iterCurrent->first;
				const float output1	= iterCurrent->second;

				float a, b;
				vgm::Utilities::linearInterpolation( input0, output0, input1, output1, a, b );

				while ( inputCurrent <= input1 )
				{
					const float output = vgm::Utilities::linearInterpolation( a, b, static_cast<float>(inputCurrent) );
					
					lut.push_back( static_cast<int32>(output) );
					
					++inputCurrent;
				}
				
				input0	= input1;
				output0	= output1;
				
				++iterCurrent;
			}
			
			break;
		}

		default:
		
			assert( false && "Unexpected transfer function type." );
	}
}


} // namespace basic

} // namespace vgd
