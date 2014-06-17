// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_EVENT_DEVICE_IDEVICE_HPP_
#define _VGQT_EVENT_DEVICE_IDEVICE_HPP_

#include "vgQt/vgQt.hpp"

class QEvent;

namespace vgQt
{

namespace event
{

namespace device
{


/**
 * @brief	Defines the interface for Qt specific devices.
 */
struct VGQT_API IDevice
{
	/**
	 * @brief	Handles the givent Qt event in order to eventually translate it into a vgSDK event.
	 */
	virtual void onEvent( QEvent* ) = 0;
};


} // namespace device
} // namespace event
} // namespace vgQt

#endif // _VGQT_EVENT_DEVICE_IDEVICE_HPP_
