// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_EVENT_DEVICE_KEYBOARD_HPP_
#define _VGQT_EVENT_DEVICE_KEYBOARD_HPP_

#include <vgd/event/device/Keyboard.hpp>

#include "vgQt/vgQt.hpp"
#include "vgQt/event/device/IDevice.hpp"


namespace vgQt
{

namespace event
{

namespace device
{

/**
 * @brief	Implements a keyboard event device for Qt widgets.
 *
 * @remark	This device will not handle the \c tab key since it can involve inconsistancy in the global
 *			button state set due to the lost of the focus.
 */
struct VGQT_API Keyboard : public vgd::event::device::Keyboard, public IDevice
{
    /**
     * @brief	Handles the givent Qt event in order to eventually translate it into a vgSDK keyboard event.
     *
     * @remark	Will skip \c tab key events to avoid inconsistancy problems due to the lost of the focus.
     */
    void onEvent( QEvent * event );
};

} // namespace device
} // namespace event
} // namespace vgQt


#endif // _VGQT_EVENT_DEVICE_KEYBOARD_HPP_
