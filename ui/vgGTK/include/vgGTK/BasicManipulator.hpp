// VGSDK - Copyright (C) 2008, 2009, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGGTK_BASICMANIPULATOR_HPP
#define _VGGTK_BASICMANIPULATOR_HPP

#include <vgUI/BasicManipulator.hpp>

#include "vgGTK/vgGTK.hpp"
#include "vgGTK/GenericCanvas.hpp"


namespace vgGTK
{


/**
 * @brief	Implements a BasicManipulator with some content loading features.
 *
 */
template < class T >
struct TBasicManipulator : public vgGTK::GenericCanvas< T >
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
	vgd::Shp< vgGTK::event::device::Keyboard >getKeyboard() const
	{
		return findDevice< vgGTK::event::device::Keyboard >();
	}
};


/**
 * @brief	Implements a GTK-based specialization of the vgUI::BasicManipulator.
 */
struct VGGTK_API BasicManipulator : public TBasicManipulator< vgUI::BasicManipulator >
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


} // namespace vgGTK



#endif /*_VGGTK_BASICMANIPULATOR_HPP*/
