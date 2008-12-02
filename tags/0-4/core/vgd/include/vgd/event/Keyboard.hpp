// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_KEYBOARD_HPP
#define _VGD_EVENT_KEYBOARD_HPP

#include "vgd/event/Device.hpp"
#include "vgd/vgd.hpp"



namespace vgd
{
	
namespace event
{
	

	
/**
 * @brief	Defines the interface for event sources that are keyboards.
 */
struct VGD_API Keyboard : public Device
{
	/**
	 * @brief	Destructor.
	 */
	~Keyboard();
	
protected:

	/**
	 * @brief	Constructor.
	 * 
	 * @remark	The constructor is defined in the protected scope to prevent
	 * 			from using this class without specialization.
	 */
	Keyboard();
};



} // namespace event

} // namespace vgd


#endif // _VGD_EVENT_KEYBOARD_HPP
