// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_BASIC_TUNITCONTAINER_HPP
#define _VGE_BASIC_TUNITCONTAINER_HPP

#include <vector>
#include <vgd/Shp.hpp>
#include <vge/vge.hpp>



namespace vge
{

namespace basic
{



/**
 * @brief Specialized container to manage a state per unit
 *
 * @todo iterators
 * @todo uses this class in GLSLState for textures and lights
 *
 * @todo resize(m_state)
 */
template< typename UnitState >
struct TUnitContainer
{
	/**
	 * @name Constructors
	 */
	//@{


	/**
	 * @brief Default constructor
	 *
	 * @param size	the number of units
	 */
	TUnitContainer( const uint size )
	:	m_unit(size),
		m_num(0)
	{}


	/**
	 * @brief Copy constructor
	 */
	TUnitContainer( const TUnitContainer& value )
	{
		copy(value);
	}

	/**
	 * @brief Assign operator
	 */
	TUnitContainer& operator =( const TUnitContainer& value )
	{
		if ( this != &value )
		{
			// remove() not needed
			copy( value );
		}
		return (*this);
	}

	//@}



	/**
	 * @brief Clears content
	 *
	 * All the elements in the container are dropped.
	 *
	 * @post getNum() == 0
	 * @post getMax() is left unchanged
	 */
	void clear()
	{
		// Fast for sparse container
		// @todo OPTME for full or almost full container
		for(	uint	i		= 0,
						iEnd	= m_unit.size();
				i != iEnd;
				++i )
		{
			if ( getState(i) )
			{
				setState( i );

				if ( getNum() == 0 )
				{
					break;
				}
			}
		}
		assert( getNum() == 0 );
	}


	/**
	 * @brief Retrieves the desired unit state.
	 *
	 * @param indexUnit		the index of the unit
	 *
	 * @return The unit state for the given unit index or an empty shared pointer.
	 */
	const vgd::Shp< UnitState > getState( const uint indexUnit = 0 ) const
	{
		assert( indexUnit >= 0 && "Invalid unit index." );
		assert( indexUnit < m_unit.size() && "Invalid unit index." );

		return m_unit[indexUnit];
	}


	/**
	 * @brief Retrieves the desired unit state.
	 *
	 * @param indexUnit		the index of the unit
	 *
	 * @return The unit state for the given unit index or an empty shared pointer.
	 */
	vgd::Shp< UnitState > getState( const uint indexUnit = 0 )
	{
		assert( indexUnit >= 0 && "Invalid unit index." );
		assert( indexUnit < m_unit.size() && "Invalid unit index." );

		return m_unit[indexUnit];
	}


	/**
	 * @brief Sets the desired unit state.
	 *
	 * @param indexUnit		the index of the unit
	 * @param state			the state to set
	 *
	 * @return The previous state
	 */
	vgd::Shp< UnitState > setState( const uint indexUnit, vgd::Shp< UnitState > state = vgd::Shp< UnitState >() )
	{
		assert( indexUnit >= 0 && "Invalid unit index." );
		assert( indexUnit < m_unit.size() && "Invalid unit index." );

		// Saves the previous state and sets the new one
		vgd::Shp< UnitState > oldState = m_unit[indexUnit];
		m_unit[indexUnit] = state;

// @todo updates a vector<int> definedUnit
		// Updates count
		if ( oldState )
		{
			m_num += ( state != 0 ) ? 0 : -1;
		}
		else
		{
			m_num += ( state != 0 ) ? 1 : 0;
		}
		assert( m_num >= 0 );
		assert( m_num <= m_unit.size() );

		return oldState;
	}

	/**
	 * @brief Retrieves the number of defined states.
	 *
	 * @return The number of defined states in all units.
	 */
	const uint getNum() const
	{
		return m_num;
	}

	/**
	 * @brief Tests if the number of defined states is equal to zero.
	 *
	 * @return getNum() == 0
	 */
	const bool isEmpty() const
	{
		return getNum() == 0;
	}

	/**
	 * @brief Tests if the number of defined states is not equal to zero.
	 *
	 * @return getNum() > 0
	 */
	const bool isNotEmpty() const
	{
		return getNum() > 0;
	}

	/**
	 * @brief Retrieves the number of state units.
	 *
	 * @return The number of state units
	 */
	const uint getMax() const
	{
		return m_unit.size();
	}


private:

	/**
	 * @brief Code for copy constructor
	 */
	void copy( const TUnitContainer& value )
	{
		m_unit	= value.m_unit;
		m_num	= value.m_num;
	}

	std::vector< vgd::Shp<UnitState> >	m_unit;		///< array storing the state of each unit. This array uses a zero-based index to select the desired unit.
	uint								m_num;		///< the number of defined states in all units
};



} // namespace basic

} // namespace vge

#endif //#ifndef _VGE_BASIC_TUNITCONTAINER_HPP
