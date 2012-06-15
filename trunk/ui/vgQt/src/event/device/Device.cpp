// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller


#include "vgQt/event/device/Device.hpp"


namespace vgQt
{

namespace event
{

namespace device
{

Device::Device()
{
}

Device::~Device()
{
}

void Device::connect( QWidget *widget )
{
    m_connectedWidget = widget;
}

void Device::disconnect()
{
    m_connectedWidget = 0;
}

} // namespace device
} // namespace event
} // namespace vgQt
