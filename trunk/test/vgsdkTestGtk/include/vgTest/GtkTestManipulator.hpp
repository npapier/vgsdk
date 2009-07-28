// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGTEST_GTKTESTMANIPULATOR_HPP
#define _VGTEST_GTKTESTMANIPULATOR_HPP

#include <vector>
#include <glibmm/ustring.h>

#include <vgGTK/GenericCanvas.hpp>

#include "vgTest/TestManipulator.hpp"

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


namespace vgTest
{
/**
 * @brief	Implements a BasicManipulator with some content loading features.
 *
 */
	struct GtkTestManipulator : public vgGTK::GenericCanvas< vgTest::TestManipulator >
	{

		/**
		 * @name	Constructors & destructor
		 */
		//@{
		GtkTestManipulator();

		template< typename SharedCanvasType >
		GtkTestManipulator( const SharedCanvasType * sharedCanvas )
		:	GenericCanvas< vgTest::TestManipulator >( sharedCanvas )
		{
			initDevices();
		}

		~GtkTestManipulator();
		//@}

	private:

		vgd::Shp< vgGTK::event::device::Keyboard >	m_keyboard;	///< The GTK keyboard device.
		vgd::Shp< vgGTK::event::device::Mouse >		m_mouse;	///< The GTK mouse device.
		vgd::Shp< vgGTK::event::device::Timer >		m_timer;	///< The GTK timer device.
		vgd::Shp< vgSDL::event::device::Joystick >	m_joystick;	///< References the joystick used to control the scene.

		void initDevices();	///< Initializes device instances and perform listening connections.
	};


} // namespace vgTest

#endif // #ifndef _VGTEST_GTKTESTMANIPULATOR_HPP
