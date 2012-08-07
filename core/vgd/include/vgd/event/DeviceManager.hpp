// VGSDK - Copyright (C) 2009, 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGD_EVENT_DEVICEMANAGER_HPP_
#define _VGD_EVENT_DEVICEMANAGER_HPP_

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
 * @brief	Implements a device manager that is also listening to the devices it owns.
 *
 * The manager will attach it-self to specified devices and detaches from devices being removed. It also
 * detaches it-self upon detruction.
 *
 * @remark	Although the manager will not attached to a device that is passed twice, you must ensure to not
 *		pass two Device instances wrapping the same real device, or may result in unpredicted behaviours.
 */
struct VGD_API DeviceManager : public Listener
{
	/**
	 * @brief	Defines devices flags
	 */
	enum Devices
	{
		Keyboard	= 1<<0,
		Mouse		= 1<<1,
		Timer		= 1<<2,
		Joystick	= 1<<3,
	};

	/**
	 * @brief	Destructor
	 */
	virtual ~DeviceManager();

	/**
	 * @name	Devices management
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
	 * @brief	Initializes all default devices.
	 *
	 * The default implementation does nothing, so sub-classes may override this method in order to specialze the default behaviour.
	 *
	 * @param	devices	a set of flags to specify what devices to create (default is all)
	 *
	 * @remark	This method must not be called twice until uninitDevices method has been called.
	 */
	virtual void initDevices( const uint devices = Keyboard|Mouse|Timer|Joystick);
	
	/**
	 * @brief	Removes the given device.
	 *
	 * The listener will automatically disconnect from the device and will not receive any more event from it.
	 */
	void removeDevice( vgd::Shp< vgd::event::Device > device );

	/**
	 * @brief	Unitializes all devices.
	 */
	virtual void uninitDevices();
	//@}

protected:

	typedef std::set< vgd::Shp< vgd::event::Device > >	DeviceContainer;

	DeviceContainer	m_devices;	///< Holds all devices the listener is connected to.
};



} // namespace event

} // namespace vgd



#endif // _VGD_EVENT_DEVICEMANAGER_HPP_
