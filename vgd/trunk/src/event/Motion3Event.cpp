// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/event/Motion3Event.hpp"



namespace vgd
{

namespace event
{
	
	
Motion3Event::Motion3Event(	Source * source, const ButtonStateSet& buttonStates, const Translation& translation, 
										const Rotation& rotation, const Size& size )
: Event( source, buttonStates ),
  m_translation( translation ),
  m_rotation( rotation ),
  m_size( size )
{}


Motion3Event::~Motion3Event()
{}


const Motion3Event::Translation& Motion3Event::getTranslation() const
{
	return m_translation;
}


const Motion3Event::Rotation& Motion3Event::getRotation() const
{
	return m_rotation;
}


const Motion3Event::Size& Motion3Event::getSize() const
{
	return m_size;
}


} // namespace event

} // namespace vgd
