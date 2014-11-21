// VGSDK - Copyright (C) 2008, 2009, 2011, 2014 Nicolas Papier, Philippe Sengchanpheng.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier
// Author Philippe Sengchanpheng

#ifndef _VGSDL_BASICMANIPULATOR_HPP
#define _VGSDL_BASICMANIPULATOR_HPP

#include <vgUI/BasicManipulator.hpp>

#include "vgSDL/vgSDL.hpp"
#include "vgSDL/GenericCanvas.hpp"


namespace vgSDL
{


/**
 * @brief	Implements a BasicManipulator with some content loading features.
 *
 */
template < class T >
struct TBasicManipulator : public vgSDL::GenericCanvas< T >
{
	/**
	 * @brief	Constructor
	 */
	TBasicManipulator( const uint devices = Keyboard|Mouse|Timer|Joystick ) 
	{
		initDevices(devices);
	}
	
	/**
	 * @brief	Constructor
	 */
	template< typename SharedCanvasType >
	TBasicManipulator( const SharedCanvasType * sharedCanvas, const uint devices = Keyboard|Mouse|Timer|Joystick )
	:	GenericCanvas< T >( sharedCanvas )
	{
		initDevices(devices);
	}
	
	/**
	 * @brief	Retrive the keyboard device
	 */
	vgd::Shp< vgSDL::event::device::Keyboard >getKeyboard() const
	{
		return findDevice< vgSDL::event::device::Keyboard >();
	}
};


/**
 * @brief	Implements a SDL-based specialization of the vgUI::BasicManipulator.
 */
struct VGSDL_API BasicManipulator : public TBasicManipulator< vgUI::BasicManipulator >
{
	/**
	 * @brief	Constructor
	 */
	BasicManipulator( const uint devices = Keyboard|Mouse|Timer|Joystick );
	
	/**
	 * @brief	Constructor
	 */
	template< typename SharedCanvasType >
	BasicManipulator( const SharedCanvasType * sharedCanvas, const uint devices = Keyboard|Mouse|Timer|Joystick )
	:	TBasicManipulator< vgUI::BasicManipulator >( sharedCanvas, devices )
	{}	
};


} // namespace vgSDL



#endif /*_VGSDL_BASICMANIPULATOR_HPP*/
