// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGM_VECTOROPERATIONS_HPP
#define _VGM_VECTOROPERATIONS_HPP

#include "vgm/Utilities.hpp"
#include "vgm/Vector.hpp"



namespace vgm
{



/**
 * @brief Creates a new vector with nextPower2()  applied to each of its components.
 *
 * @param input		the input vector
 *
 * @return a new vector, where each component have been computed by applying nextPower2() on component of the input vector.
 *
 * @see nextPower2() function of vgm.
 */
template< typename T, int32 N >
const Vector<T,N> nextPower2( const Vector<T,N> input )
{
	Vector<T,N> output;

	for( int32 i=0; i<N; i++ )
	{
		output[i] = vgm::Utilities::nextPower2( input[i] );
	}

	return output;
}



} // namespace vgm

#endif // #ifndef _VGM_VECTOROPERATIONS_HPP
