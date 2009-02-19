// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_EVENT_DEVICE_TIMER_HPP_
#define _VGD_EVENT_DEVICE_TIMER_HPP_

#include "vgd/event/Device.hpp"



namespace vgd
{

namespace event
{

namespace device
{


/**
 * @brief	Implements the timer device.
 */
struct VGD_API Timer : public Device
{

protected:

	/**
	 * @brief	Constructor
	 *
	 * @param identifier	the device identifier
	 *
	 * @remark	The constructor is protected so only specialized classes can be instanciated.
	 */
	Timer( const uint identifier = 0 );
};

} // namespace device

} // namespace event

} // namespace vgd



#endif // #ifndef _VGD_EVENT_DEVICE_TIMER_HPP_
