// VGSDK - Copyright (C) 2012, 2013, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_BASICMANIPULATOR_HPP_
#define _VGQT_BASICMANIPULATOR_HPP_

#include <QEvent>

#include <vgUI/BasicManipulator.hpp>

#include "vgQt/vgQt.hpp"
#include "vgQt/GenericCanvas.hpp"
#include "vgQt/event/device/Keyboard.hpp"
#include "vgQt/event/device/Mouse.hpp"
#include "vgQt/event/device/Timer.hpp"

namespace vgQt
{

/**
 * @brief	Implements a Qt-based specialization of the vgUI::BasicManipulator.
 *
 * This class allows to specify a custom base class that has itself to be based on vgUI::BasicManipulator.
 */
template< typename T >
struct TBasicManipulator : public GenericCanvas< T >
{
	/**
     * @brief	Constructor that builds a canvas with its own OpenGL context.
	 *
	 * @param	parent	a pointer to the parent widget (default is null)
	 * @param	devices	a set of flags telling what devices to initialze (default is all)
     */
	explicit TBasicManipulator( 
		QWidget * parent = 0, 
		const uint devices = vgd::event::DeviceManager::Keyboard|vgd::event::DeviceManager::Mouse|vgd::event::DeviceManager::Timer|vgd::event::DeviceManager::Joystick )
	:    GenericCanvas< T >(parent)
	{
		// Configures the focus policy.
		this->setFocusPolicy( (Qt::FocusPolicy) (Qt::TabFocus|Qt::ClickFocus|Qt::WheelFocus) );
		
		// Initializes devices.
		this->initDevices( devices );

		// Initializes the contextual menu.
		this->m_actionsMenu->setCanvas(this);
		this->connect(this, SIGNAL(customContextMenuRequested(QPoint)), this->m_actionsMenu.get(), SLOT(onCanvasMenuRequested(QPoint)));
	}

	/**
	 * @brief	Constructor that builds a canvas with an OpenGL context sharing resources with
	 * 			the given canvas.
	 *
	 * @param	sharedCanvas	a pointer to the canvas for sharing
	 * @param	parent			a pointer to the parent widget (default is null)
	 * @param	devices			a set of flags telling what devices to initialze (default is all)
	 */
	explicit TBasicManipulator( 
		const vgUI::Canvas * sharedCanvas, 
		QWidget * parent = 0, 
		const uint devices = vgd::event::DeviceManager::Keyboard|vgd::event::DeviceManager::Mouse|vgd::event::DeviceManager::Timer|vgd::event::DeviceManager::Joystick )
    :    GenericCanvas< T >( sharedCanvas, parent )
	{
		// Configures the focus policy.
		this->setFocusPolicy( (Qt::FocusPolicy) (Qt::TabFocus|Qt::ClickFocus|Qt::WheelFocus) );
		
		// Initializes devices.
		this->initDevices( devices );

		// Initializes the contextual menu.
		this->m_actionsMenu->setCanvas(this);
		this->connect(this, SIGNAL(customContextMenuRequested(QPoint)), this->m_actionsMenu.get(), SLOT(onCanvasMenuRequested(QPoint)));
	}

protected:

	/**
	 * @brief	Main event handler method overriding QWidget's
	 */
    bool event( QEvent * event )
	{
		switch( event->type() )
		{
		case QEvent::KeyPress:
		case QEvent::KeyRelease:
		case QEvent::MouseButtonPress:
		case QEvent::MouseButtonRelease:
		case QEvent::MouseMove:
		case QEvent::Wheel:
			forwardEventToDevices( event );
			break;

		default:
			break; // Nothing to do.
		}

		return GenericCanvas< T >::event(event);
	}

private:

	/**
	 * @brief	Forward the given event to managed devices.
	 */
	void forwardEventToDevices( QEvent * event )
	{
		for( vgd::event::DeviceManager::DeviceContainer::iterator device = vgd::event::DeviceManager::m_devices.begin(); device != vgd::event::DeviceManager::m_devices.end(); ++device )
		{
			vgd::Shp< vgQt::event::device::IDevice > qtDevice = vgd::dynamic_pointer_cast< vgQt::event::device::IDevice >( *device );

			if( qtDevice )
			{
				qtDevice->onEvent(event);
			}
		}
	}
};


/**
 * @brief	Implements a QT-based specialization of the vgUI::BasicManipulator
 */
struct VGQT_API BasicManipulator : public TBasicManipulator< vgUI::BasicManipulator >
{
	/**
     * @brief	Constructor that builds a canvas with its own OpenGL context.
	 *
	 * @param	parent	a pointer to the parent widget (default is null)
	 * @param	devices	a set of flags telling what devices to initialze (default is all)
     */
	explicit BasicManipulator( QWidget * parent = 0, const uint devices = Keyboard|Mouse|Timer|Joystick );

	/**
	 * @brief	Constructor that builds a canvas with an OpenGL context sharing resources with
	 * 			the given canvas.
	 *
	 * @param	sharedCanvas	a pointer to the canvas for sharing
	 * @param	parent			a pointer to the parent widget (default is null)
	 * @param	devices			a set of flags telling what devices to initialze (default is all)
	 */
	explicit BasicManipulator( const vgUI::Canvas * sharedCanvas, QWidget * parent = 0, const uint devices = Keyboard|Mouse|Timer|Joystick );
};


} // namespace vgQt

#endif // _VGQT_BASICMANIPULATOR_HPP_
