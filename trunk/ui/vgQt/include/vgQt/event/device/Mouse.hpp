// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_EVENT_DEVICE_MOUSE_HPP_
#define _VGQT_EVENT_DEVICE_MOUSE_HPP_

#include <vgd/event/device/Mouse.hpp>
#include <vgd/event/Location2.hpp>

#include "vgQt/vgQt.hpp"
#include "vgQt/event/device/IDevice.hpp"


class QWidget;
class QEvent;
class QMouseEvent;
class QWheelEvent;


namespace vgQt
{

namespace event
{

namespace device
{

/**
 * @brief	Implements a mouse event device for Qt widgets.
 *
 */
struct VGQT_API Mouse : public vgd::event::device::Mouse, public IDevice
{
    /**
     * @brief	Constructor
     *
	 * @param	widget		a pointer to the widget where the mouse events will occur
     * @param	identifier	the optionnal device identifier
     */
    Mouse( const QWidget * widget, const uint identifier = 0 );

     /**
     * @brief	Handles the givent Qt event in order to eventually translate it into a vgSDK mouse event.
     */
	void onEvent( QEvent * event );

	const ::vgd::event::Location2::Location getPreviousLocation() { return m_previousLocation; }

private:

	const QWidget						* m_widget;			///< Points to the widget where the mouse event occur.
	::vgd::event::Location2::Location	m_previousLocation;	///< Holds the previous mouse location.

	/**
	 * @name	Helpers
	 */
	//@{
	void onButtonEvent( QMouseEvent * );	///< Handles mouse button press and release events.
	void onMoveEvent( QMouseEvent * );		///< Handles mouse motion events.
	void onWheelEvent( QWheelEvent * );		///< Handles mouse wheel scroll events.
	//@}

};

} // namespace device
} // namespace event
} // namespace vgQt


#endif // _VGQT_EVENT_DEVICE_MOUSE_HPP_
