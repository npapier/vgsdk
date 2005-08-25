// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/event/Location2.hpp"


namespace vgd
{

namespace event
{
	
	
Location2::Location2(	const Location& location, const Size& size )
: m_location( location ),
  m_size( size )
{}


Location2::~Location2()
{}


const Location2::Location& Location2::getLocation() const
{
	return this->m_location;
}


const Location2::Size& Location2::getSize() const
{
	return this->m_size;
}


} // namespace event

} // namespace vgd
