// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker


#include "vgd/event/Location2Event.hpp"


namespace vgd
{
namespace event
{
	
	
Location2Event::Location2Event( Source * source, const Location& location )
: Event( source ),
  m_location( location )
{}


Location2Event::~Location2Event()
{}


const Location2Event::Location& Location2Event::getLocation() const
{
	return this->m_location;
}


} // namespace event

} // namespace vgd
