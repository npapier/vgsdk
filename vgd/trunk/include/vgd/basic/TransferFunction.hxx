// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include <cmath>
#include <vgm/Utilities.hpp>


namespace vgd
{

namespace basic
{


template< typename T >
void TransferFunction::getLookupTable( T& inputBegin, T& inputEnd, std::vector< T >& lut )
{
	assert( getNumPoints() >= 2 );

	assert( lut.size() == 0 );
	
	PointsContainer::const_iterator iterCurrent = m_points.begin();
	PointsContainer::const_iterator iterEnd		= m_points.end();

	inputBegin	= static_cast<T>( std::floor(iterCurrent->first) );
	inputEnd	= static_cast<T>( std::floor(m_points.rbegin()->first) );

	assert( inputBegin <= inputEnd );

	lut.reserve( inputEnd - inputBegin + static_cast<T>(1) );

	switch ( m_type )
	{
		case IDENTITY:
		{
			T inputCurrent = inputBegin;
			
			while ( inputCurrent <= inputEnd )
			{
				lut.push_back( static_cast<T>(inputCurrent) );
				
				++inputCurrent;
			}
			break;
		}
		
		case TABLE:
		{
			float input0	= iterCurrent->first;
			float output0	= iterCurrent->second;
			
			lut.push_back( static_cast<T>(output0) );
			T inputCurrent = static_cast<T>(input0) + static_cast<T>(1);

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
					
					lut.push_back( static_cast<T>(output) );
					
					++inputCurrent;
				}
				
				input0	= input1;
				output0	= output1;
				
				++iterCurrent;
			}
			
			break;
		}

		case DISCRETE:
		{
			float input0	= iterCurrent->first;
			float output0	= iterCurrent->second;

			T inputCurrent = static_cast<T>(input0) + static_cast<T>(1);
			++iterCurrent;
			
			while ( iterCurrent != iterEnd )
			{
				const T output = static_cast<T>(output0);
			
				lut.push_back( static_cast<T>(output) );
				
				const float input1	= iterCurrent->first;
				const float output1	= iterCurrent->second;

				while ( inputCurrent < input1 )
				{
					lut.push_back( output );
					++inputCurrent;
				}
				
				input0	= input1;
				output0	= output1;
				
				++iterCurrent;
			}
			
			lut.push_back( static_cast<T>(output0) );
			
			break;
		}

		default:
			assert( false && "Unexpected transfer function type." );
	}
}


} // namespace basic

} // namespace vgd
