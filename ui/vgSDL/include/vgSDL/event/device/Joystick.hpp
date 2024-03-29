// VGSDK - Copyright (C) 2008, 2009, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGSDL_EVENT_DEVICE_JOYSTICK_HPP_
#define _VGSDL_EVENT_DEVICE_JOYSTICK_HPP_

#include <cassert>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_joystick.h>

#include <vgd/Shp.hpp>
#include <vgd/Wkp.hpp>
#include <vgd/event/device/Joystick.hpp>

#include "vgSDL/vgSDL.hpp"



namespace vgSDL
{

namespace event
{

namespace device
{



/**
 * @brief	Implements a SDL-based joystick.
 *
 * Due to the architecture of SDL, there can be only one joystick instance
 * per identifier. This implies that you must keep a reference on joysticks
 * you want to receive events from. As soon as the last reference to a
 * joystick get removed, the joystick instance is destroyed will not send
 * any event.
 *
 * @remark	Prior using any method of this class, you must
 * 			have initialized joystick support in SDL
 * 			by passing the @c SDL_INIT_JOYSTICK flag to @c SDL_Init function.
 */
struct VGSDL_API Joystick : public ::vgd::event::device::Joystick
{
	/**
	 * @name	Joystick Querying
	 */
	//@{
	/**
	 * @brief	Retrieves the name of all available joysticks.
	 *
	 * The index of the name entries in the returned sequence can
	 * be used to query a joystick.
	 *
	 * @remark	@c StlStringSequence must comply to the STL Sequence concept and
	 * 			its value type must be @c std::string
	 *
	 * @return	a container of strings containing the name of the available joysticks
	 *
	 * @see		get
	 */
	template< typename StlStringSequence >
	static const StlStringSequence getNames()
	{
		assert( SDL_WasInit(SDL_INIT_JOYSTICK) == SDL_INIT_JOYSTICK && "SDL Joystick system not initialized !");

		const int			joyCount = SDL_NumJoysticks();
		StlStringSequence	result;

		for( int index = 0; index != joyCount; ++index )
		{
			result.insert(result.end(), std::string(SDL_JoystickNameForIndex(index)));
		}

		return result;
	}

	/**
	 * @brief Returns true if the joystick SDL subsytem is initialized.
	 */
	static bool isSubsystemInitialized();

	/**
	 * @brief	Searches for a joystick at the given index.
	 *
	 * @param	index	an index for a joystick
	 *
	 * @return	a shared pointer to a joystick, empty if none
	 */
	static vgd::Shp< Joystick > find( const int index );

	/**
	 * @brief	Retrieves the joystick with the given index, or create
	 * 			one if none exists.
	 *
	 * The index of the name entries of the sequence provided by getNames
	 * corresponds to the joystick index.
	 *
	 * @param	index	an index for a joystick
	 *
	 * @return	a shared pointer to a joystik, empty on error
	 *
	 * @see		getNames, find
	 */
	static vgd::Shp< Joystick > get( const int index );
	//@}


	/**
	 * @name	SDL Event Handling
	 */
	//@{
	static void handleEvent( const SDL_JoyAxisEvent & event );
	static void handleEvent( const SDL_JoyButtonEvent & event );
	static void handleEvent( const SDL_JoyHatEvent & event );
	//@}


	/**
	 * @brief	Destructor
	 */
	~Joystick();


	/**
	 * @name	Property Accessors
	 */
	//@{
	/**
	 * @brief	Retrieves the index of the joystick.
	 *
	 * @return	an integer representing the index
	 */
	const int getIndex() const;

	/**
	 * @brief	Retrieves the name of the joystick
	 *
	 * @return	a string containing the name
	 */
	const std::string getName() const;
	//@}


	/**
	 * @name	State Accessors
	 */
	//@{
	/**
	 * @brief	Retrieves the current value of the given axis, in the range [-1, 1].
	 *
	 * @param	axis	the axis index
	 *
	 * @return	the axis value
	 *
	 * @see		getAxisNumber, getAxisRaw
	 */
	const float getAxis( const int axis ) const;

	/**
	 * @brief	Retrieves the number of axes of the joystick
	 *
	 * @return	the number of axis
	 */
	const int getAxesNumber() const;

	/**
	 * @brief	Retrieves the raw axis value.
	 *
	 * @param	axis	the axis index
	 *
	 * @retrun	the raw axis value
	 *
	 * @see		getAxis, getAxisNumber
	 */
	const short getAxisRaw( const int axis ) const;
	
	/**
	 * @brief	Retreives the state if a given button.
	 * 
	 * @param	button	the name of the button
	 * 
	 * @return	true if the given button is down
	 */
	const bool getButton( const Button button ) const;
	//@}


private:

	/**
	 * @brief	Factory
	 *
	 * This factory is reserved for private use since there can be only
	 * joystick instance per identifier (thanks to the SDL architecture).
	 * 
	 * @return null if creation fail (due to the absence of joystick)
	 * 
	 * @param	index	the index of an attached joystick
	 */
	static vgd::Shp<Joystick > create( const int index );

	/**
	 * @brief	Constructor
	 *
	 * This constructor is reserved for private use since there can be only
	 * joystick instance per identifier (thanks to the SDL architecture).
	 *
	 * @param joystick		the sdl joystick to be attached
	 * @param identifier	the device identifier
	 */
	Joystick( SDL_Joystick* joystick, const uint identifier = 0 );

	typedef std::vector< vgd::Wkp< Joystick >  >	JoyCollection;

	static JoyCollection	m_joyCache;		///< The collection of joystick already in use.
	SDL_Joystick			* m_joystick;	///< The wrapped SDL joystick structure.
};



} // namespace device

} // namespace event

} // namespace vgSDL




#endif /*_VGSDL_EVENT_DEVICE_JOYSTICK_HPP_*/
