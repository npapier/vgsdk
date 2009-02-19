// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_DEVICE_JOYSTICK_HPP_
#define _VGD_EVENT_DEVICE_JOYSTICK_HPP_

#include "vgd/event/Device.hpp"



namespace vgd
{

namespace event
{

namespace device
{



/**
 * @brief	Implements the joystick device.
 */
struct VGD_API Joystick : public Device
{

	/**
	 * @brief	Defines joystick button identifers.
	 */
	typedef enum
	{
		BUTTON_1 = 1024,BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5,
		BUTTON_6,  BUTTON_7,  BUTTON_8,  BUTTON_9,  BUTTON_10,
		BUTTON_11, BUTTON_12, BUTTON_13, BUTTON_14, BUTTON_15,
		BUTTON_16, BUTTON_17, BUTTON_18, BUTTON_19, BUTTON_20,
		BUTTON_21, BUTTON_22, BUTTON_23, BUTTON_24, BUTTON_25,
		BUTTON_26, BUTTON_27, BUTTON_28, BUTTON_29, BUTTON_30,
		BUTTON_31, BUTTON_32
	} Button;


protected:

	/**
	 * @brief	Constructor
	 *
	 * @param identifier	the device identifier
	 *
	 * @remark	The constructor is protected so only specialized classescan be instanciated.
	 */
	Joystick( const uint identifier = 0 );

};



} // namespace device

} // namespace event

} // namespace vgd



#endif /*_VGD_EVENT_DEVICE_JOYSTICK_HPP_*/
