// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker


#ifndef _VGD_EVENT_MOUSE_HPP
#define _VGD_EVENT_MOUSE_HPP


#include "vgd/vgd.hpp"
#include "vgd/event/Device.hpp"


namespace vgd
{
	
namespace event
{
	
	
/**
 * @brief	Defines the interface for event sources that are keyboards.
 */
struct VGD_API Mouse : public Device
{
public:
	/**
	 * @brief	Destructor.
	 */
	~Mouse();
	
protected:

	/**
	 * @brief	Constructor.
	 * 
	 * @remark	The constructor is defined in the protected scope to prevent
	 * 			from using this class without specialization.
	 */
	Mouse();
};


} // namespace event

} // namespace vgd


#endif // _VGD_EVENT_MOUSE_HPP
