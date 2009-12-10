// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGD_EVENT_DEVICELISTENER_HPP_
#define _VGD_EVENT_DEVICELISTENER_HPP_

#include <set>

#include "vgd/Shp.hpp"
#include "vgd/event/Listener.hpp"

namespace vgd
{
	namespace event
	{
		struct Device;
		struct Event;
	}
}



namespace vgd
{

namespace event
{



/**
 * @brief	Implements a listener that manages a collection of devices it is attached to.
 *
 * The DeviceListener will attach it-self to specified devices and detaches from devices being removed. It also
 * detaches it-self upon detruction.
 *
 * @remark	Although the DeviceListener will not attached to a device that is passed twice, you must ensure to not
 *		pass two Device instances wrapping the same real device, or may result in unpredicted behaviours.
 */
struct VGD_API DeviceListener : public Listener
{
	/**
	 * @brief	Destructor
	 */
	~DeviceListener();

	/**
	 * @name	Device Management
	 */
	//@{
	/**
	 * @brief	Adds the given device.
	 *
	 * The listener will automatically connect to the device  in order to receive events from it.
	 */
	void addDevice( vgd::Shp< vgd::event::Device > device );
	
	/**
	 * @brief	Looks for the first device that matches the given type.
	 *
	 * @return	A shared pointer to the found device, or empty if none.
	 */
	template< typename DeviceType >
	vgd::Shp< DeviceType > findDevice() const
	{
		vgd::Shp< DeviceType >	result;

		for( DeviceContainer::const_iterator i = m_devices.begin(); i != m_devices.end(); ++i )
		{
			result = vgd::dynamic_pointer_cast< DeviceType >( *i );

			if( result )
			{
				break;
			}
		}
		
		return result;
	}
	
	/**
	 * @brief	Tells if the listener is connected to the given device.
	 */
	const bool hasDevice( vgd::Shp< vgd::event::Device > device ) const;
	
	/**
	 * @brief	Removes the given device.
	 *
	 * The listener will automatically disconnect from the device and will not receive any more event from it.
	 */
	void removeDevice( vgd::Shp< vgd::event::Device > device );
	//@}

private:

	typedef std::set< vgd::Shp< vgd::event::Device > >	DeviceContainer;

	DeviceContainer	m_devices;	///< Holds all devices the listener is connected to.
};



} // namespace event

} // namespace vgd



#endif // _VGD_EVENT_DEVICELISTENER_HPP_
