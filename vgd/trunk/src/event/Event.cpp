// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgd/event/Event.hpp"

namespace vgd
{
	
namespace event
{
	
	
Event::Event( Source *source )
: pSource(source)
{}

Event::~Event()
{}

Source* Event::getSource() const
{
	return this->pSource;
}


} // namespace event

} // namespace vgd
