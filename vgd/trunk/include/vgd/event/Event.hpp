// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_EVENT_HPP
#define _VGD_EVENT_EVENT_HPP


#include "vgd/vgd.hpp"


namespace vgd
{
	
namespace event
{
	
struct Source;
	
/** 
 * @namespace vgd::event
 * 
 * @brief Bases of the event system.
 *
 * This namespace contains all base classes used for the event subsystem.
 */
 
/**
 * @brief	The generic event class.
 * 
 * This class defines the generic interface for all events.
 */
struct VGD_API Event
{
	/**
	 * @brief	Constructor.
	 * 
	 * @param	source	a pointer to the object that raise the event
	 */
	Event( Source *source );
	
	/**
	 * @brief	Destructor.
	 */
	virtual ~Event();
	
	/**
	 * @brief	Retrieves the source of the event.
	 * 
	 * @return	a pointer to the event source
	 */
	Source* getSource() const;
	
private:
	/**
	 * @brief	a pointer to the source of the event
	 */
	Source *pSource;
};


} // namespace event
	
} // namespace vgd

#endif // _VGD_EVENT_EVENT_HPP
