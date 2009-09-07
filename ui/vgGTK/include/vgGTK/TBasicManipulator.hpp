// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier
// Author Maxime Peresson

#ifndef _VGGTK_TBASICMANIPULATOR_HPP
#define _VGGTK_TBASICMANIPULATOR_HPP

#include <vector>
#include <glibmm/ustring.h>
#include <vgGTK/GenericCanvas.hpp>

#include <vgd/basic/FilenameExtractor.hpp>

#include <vgd/node/LightModel.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/TriSet.hpp>

#include <vgGTK/event/device/mouse.hpp>
#include <vgGTK/event/device/keyboard.hpp>
#include <vgGTK/event/device/timer.hpp>
#include <vgSDL/event/device/joystick.hpp>

#include <vgeGL/engine/Engine.hpp>
#include <vgObj/Loader.hpp>
#include <vgTrian/Loader.hpp>
#include <vgd/basic/Image.hpp>
#include <time.h>

namespace vgGTK
{

/**
 * @brief	Defines devices flags
 */
enum Devices
{
	Keyboard	= 1<<0,
	Mouse		= 1<<1,
	Timer		= 1<<2,
	Joystick	= 1<<3,
};

/**
 * @brief	Implements a BasicManipulator with some content loading features.
 *
 */
template < class T >
struct TBasicManipulator : public vgGTK::GenericCanvas< T >
{

	/**
	 * @name	Constructors & destructor
	 */
	//@{
	TBasicManipulator(const uint devices = Keyboard | Mouse | Timer | Joystick) 
	:	m_devices( devices )
	{
		initDevices();
	}


	template< typename SharedCanvasType >
	TBasicManipulator( const SharedCanvasType * sharedCanvas , const uint devices = Keyboard | Mouse | Timer | Joystick)
	:	GenericCanvas< T >( sharedCanvas ),
		m_devices( devices )
	{
		initDevices();
	}

	~TBasicManipulator()
	{
		// Disconnects GTK devices to the widget so they no more receive GTK events
		// Removes devices
		if ( m_devices & Keyboard )
		{
			m_keyboard->disconnect();
			removeDevice( m_keyboard );
		}

		if ( m_devices & Mouse )
		{
			m_mouse->disconnect();
			removeDevice( m_mouse );
		}

		if ( m_devices & Timer )
		{
			m_timer->disconnect();
			removeDevice( m_timer );
		}

		if ( m_devices & Joystick )
		{
			// Removes joystick (if present)
			if ( m_joystick )
			{
				removeDevice( m_joystick );
			}
		}
	}
	//@}

	vgd::Shp< vgGTK::event::device::Keyboard >	getKeyboard() ///< Get the keyboard
	{
		return m_keyboard;
	}

private:

	vgd::Shp< vgGTK::event::device::Keyboard >	m_keyboard;	///< The GTK keyboard device.
	vgd::Shp< vgGTK::event::device::Mouse >		m_mouse;	///< The GTK mouse device.
	vgd::Shp< vgGTK::event::device::Timer >		m_timer;	///< The GTK timer device.
	vgd::Shp< vgSDL::event::device::Joystick >	m_joystick;	///< References the joystick used to control the scene.

	unsigned int								m_devices;

	void initDevices()	///< Initializes device instances and perform listening connections.
	{
		assert( m_keyboard == 0 && m_mouse == 0 && m_timer == 0 && m_joystick == 0 );

		// Creates device instances.
		// Connects GTK devices to the widget so they receive GTK events.
		// Adds devices so we receive vgd events.
		if ( m_devices & Keyboard )
		{
			m_keyboard.reset( new vgGTK::event::device::Keyboard() );
			m_keyboard->connect( this );
			addDevice( m_keyboard );
		}

		if ( m_devices & Mouse )
		{
			m_mouse.reset( new vgGTK::event::device::Mouse() );
			m_mouse->connect( this );
			addDevice( m_mouse );
		}

		if ( m_devices & Timer )
		{
			m_timer.reset( new vgGTK::event::device::Timer() );
			m_timer->connect( this );
			addDevice( m_timer );
		}

		if ( m_devices & Joystick )
		{
			m_joystick = vgSDL::event::device::Joystick::get(0);

			// Adds joystick (if present)
			if( m_joystick )
			{
				addDevice( m_joystick );
			}
			else
			{
				vgLogWarning( "No joystick found." );
			}
		}
	}
};


} // namespace vgGTK

#endif // #ifndef _VGGTK_TBASICMANIPULATOR_HPP
