// VGSDK - Copyright (C) 2004-2006, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgd/event/Device.hpp"



namespace vgd
{

namespace event
{



Device::Device( const uint identifier )
:	Source(),
	m_id(identifier)
{}


Device::~Device()
{}



uint Device::getId() const
{
	return m_id;
}



} // namespace event

} // namespace vgd
