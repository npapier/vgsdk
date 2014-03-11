// VGSDK - Copyright (C) 2004-2006, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_DEVICE_HPP
#define _VGD_EVENT_DEVICE_HPP

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
	 * @brief	Destructor
	 */
	virtual ~Device();

	/**
	 * @brief Retrieves the device identifier
	 * 
	 * Device identifiers are not global unique identifier, but a zero-based index of device of the same type.
	 *
	 * @return	the device identifier
	 */
	uint getId() const;

protected:

	/**
	 * @brief	Constructor.
	 *
	 * @param identifier	the device identifier
	 *
	 * @remark	The constructor is defined in the protected scope to prevent
	 * 			from using this class without specialization.
	 */
	Device( const uint identifier = 0 );

private:
	uint m_id; ///< The device identifier
};


} // namespace event

} // namespace vgd


#endif // _VGD_EVENT_DEVICE_HPP
