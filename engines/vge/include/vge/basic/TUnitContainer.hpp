// VGSDK - Copyright (C) 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_BASIC_TUNITCONTAINER_HPP
#define _VGE_BASIC_TUNITCONTAINER_HPP

#include <vector>
#include <vgd/field/DirtyFlag.hpp>
#include <vgd/Shp.hpp>
#include <vgDebug/helpers.hpp>



namespace vge
{

namespace basic
{



/**
 * @brief Specialized container containing a state per unit
 *
 * This container is conceptually similar to std::vector with unit similar to vector index and state similar to vector value.
 *
 * @todo iterators
 */
template< typename UnitState >
struct TUnitContainer : public vgd::field::DirtyFlag
{
	/**
	 * @name Constructors
	 */
	//@{


	/**
	 * @brief Default constructor
	 *
	 * @param size			the number of units
	 */
	TUnitContainer( const uint size = 0 )
	:	DirtyFlag(""),
		m_unit		( size		),
		m_num		( 0			)
	{}

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
		dirty();

		const int size = m_unit.size();
		m_unit.clear();
		m_unit.resize( size );

		m_num = 0;
	}


	/**
	 * @brief Tests existence of the desired unit in the container
	 *
	 * @return true if the unit exists, otherwise returns false
	 */
	const bool hasState( const uint indexUnit = 0 ) const
	{
		return indexUnit < m_unit.size();
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
		expandSize( indexUnit );

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
		expandSize( indexUnit );

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
		expandSize( indexUnit );

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
		vgAssert( m_num >= 0 );
		vgAssert( m_num <= m_unit.size() );

		// Updates dirty flags
		dirty();

		// Returns old value
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
	 *
	 * @todo deprecated
	 */
	const uint getMax() const
	{
		return size();
	}

	/**
	 * @brief Retrieves the number of state units.
	 *
	 * @return The number of state units
	 */
	const uint size() const
	{
		return m_unit.size();
	}


private:

	void expandSize( const uint indexUnit ) const
	{
		if ( indexUnit >= m_unit.size() )
		{
			// Expand the container
			const_cast<TUnitContainer*>(this)->m_unit.resize( indexUnit + 2 );
		}
	}

	typedef std::vector< vgd::Shp<UnitState> > ContainerType;
	ContainerType	m_unit;			///< array storing the state of each unit. This array uses a zero-based index to select the desired unit.
	uint			m_num;			///< the number of defined states in all units
};



} // namespace basic

} // namespace vge

#endif //#ifndef _VGE_BASIC_TUNITCONTAINER_HPP
