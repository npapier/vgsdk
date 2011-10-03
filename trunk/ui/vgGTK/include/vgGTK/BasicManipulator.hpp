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
	namespace event
	{
		namespace device
		{
			struct Keyboard;
			struct Mouse;
			struct Timer;
		}
	}
}

namespace vgSDL
{
	namespace event
	{
		namespace device
		{
			struct Joystick;
		}
	}
}


namespace vgGTK
{



/**
 * @brief	Implements a GTK-based specialization of the vgUI::BasicManipulator.
 */
struct VGGTK_API BasicManipulator : public GenericCanvas< vgUI::BasicManipulator >
{
	/**
	 * @name	Constructors & destructor
	 */
	//@{
	BasicManipulator();

	template< typename SharedCanvasType >
	BasicManipulator( const SharedCanvasType * sharedCanvas )
	:	GenericCanvas< vgUI::BasicManipulator >( sharedCanvas )
	{
		initDevices();
	}

	~BasicManipulator();
	//@}

	void initDevices();		///< Initializes device instances and perform listening connections.
	void uninitDevices();	///< Uninitializes device instances and stop listening connections.
private:

	vgd::Shp< vgGTK::event::device::Keyboard >	m_keyboard;	///< The GTK keyboard device.
	vgd::Shp< vgGTK::event::device::Mouse >		m_mouse;	///< The GTK mouse device.
	vgd::Shp< vgGTK::event::device::Timer >		m_timer;	///< The GTK timer device.
	vgd::Shp< vgSDL::event::device::Joystick >	m_joystick;	///< References the joystick used to control the scene.

};



} // namespace vgGTK



#endif /*_VGGTK_BASICMANIPULATOR_HPP*/
