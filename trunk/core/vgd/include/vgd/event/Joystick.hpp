// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_JOYSTICK_HPP_
#define _VGD_EVENT_JOYSTICK_HPP_

#include "vgd/vgd.hpp"
#include "vgd/event/Device.hpp"



namespace vgd
{

namespace event
{



/**
 * @brief	Implements the joystick device.
 */
struct VGD_API Joystick : public Device
{

protected:

	/**
	 * @brief	Constructor
	 *
	 * @remark	The constructor is protected so only specialized classes
	 * 			can be instanciated.
	 */
	Joystick();

};

} // namespace event

} // namespace vgd



#endif /*_VGD_EVENT_JOYSTICK_HPP_*/
