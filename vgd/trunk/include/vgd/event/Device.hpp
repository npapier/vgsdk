// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_DEVICE_HPP
#define _VGD_EVENT_DEVICE_HPP

#include "vgd/vgd.hpp"
#include "vgd/event/Source.hpp"


namespace vgd
{
	
namespace event
{
	
/**
 * @brief	Defines the interface for event sources that are input devices.
 */
struct VGD_API Device : public Source
{
	/**
	 * @brief	Destructor.
	 */
	~Device();
	
protected:

	/**
	 * @brief	Constructor.
	 * 
	 * @remark	The constructor is defined in the protected scope to prevent
	 * 			from using this class without specialization.
	 */
	Device();
};


} // namespace event

} // namespace vgd


#endif // _VGD_EVENT_DEVICE_HPP
