// VGSDK - Copyright (C) 2009, 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgd/event/DeviceManager.hpp"

#include "vgd/event/Device.hpp"



namespace vgd
{

namespace event
{


DeviceManager::~DeviceManager()
{
	uninitDevices();
}


void DeviceManager::addDevice( vgd::Shp< vgd::event::Device > device )
{
	if ( m_devices.find(device) == m_devices.end() )
	{
		device->attachEventListener( this );
		m_devices.insert( device );
	}
}


const bool DeviceManager::hasDevice( vgd::Shp< vgd::event::Device > device ) const
{
	return m_devices.find(device) != m_devices.end();
}


void DeviceManager::initDevices( const uint devices )
{}


void DeviceManager::removeDevice( vgd::Shp< vgd::event::Device > device )
{
	DeviceContainer::iterator	found = m_devices.find( device );
	
	if ( found != m_devices.end() )
	{
		(*found)->detachEventListener( this );
		m_devices.erase( found );
	}
}


void DeviceManager::uninitDevices()
{
	for( DeviceContainer::iterator i = m_devices.begin(); i != m_devices.end(); ++i )
	{
		(*i)->detachEventListener( this );
	}
	m_devices.clear();
}


} // namespace event

} // namespace vgd
