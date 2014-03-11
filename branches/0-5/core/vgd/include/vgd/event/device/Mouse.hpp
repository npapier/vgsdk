// VGSDK - Copyright (C) 2004-2006, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_DEVICE_MOUSE_HPP
#define _VGD_EVENT_DEVICE_MOUSE_HPP

#include "vgd/event/Device.hpp"



namespace vgd
{

namespace event
{

namespace device
{

/**
 * @brief	Defines the interface for event sources that are keyboards.
 */
struct VGD_API Mouse : public Device
{
	/**
	 * @brief	Destructor.
	 */
	~Mouse();

protected:

	/**
	 * @brief	Constructor.
	 *
	 * @param identifier	the device identifier
	 *
	 * @remark	The constructor is defined in the protected scope to prevent
	 * 		from using this class without specialization.
	 */
	Mouse( const uint identifier = 0 );
};


} // namespace device

} // namespace event

} // namespace vgd


#endif // _VGD_EVENT_DEVICE_MOUSE_HPP
