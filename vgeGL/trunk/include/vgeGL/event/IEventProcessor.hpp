// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_EVENT_IEVENTPROCESSOR_H
#define _VGEGL_EVENT_IEVENTPROCESSOR_H

#include <vgd/Shp.hpp>
#include <vgd/event/Event.hpp>

#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{
	
namespace event
{

/**
 * @brief Interface to process an incoming event.
 */
struct VGEGL_API IEventProcessor
{
	/**
	 * @name Constructor/destructor
	 * 
	 */
	//@{
	
	/**
	 * @brief Default constructor
	 * 
	 * @post isEnabled() == true
	 */
	IEventProcessor();
	
	/**
	 * @brief Destructor
	 */
	virtual ~IEventProcessor();
	
	//@}
	
	
	
	/**
	 * @brief Method call to process the incoming event.
	 * 
	 * @param event		event to process
	 * 
	 * @return true to stop processing (by any following IEventProcessor), false if processing must continue.
	 */
	virtual const bool onEvent( vgd::Shp<vgd::event::Event> event )=0;



	/**
	 * @name Accessors
	 */
	//@{
	
	/**
	 * @brief Tests if this event processor is enabled or not.
	 * 
	 * @return true if enabled, false otherwise.
	 */
	const bool isEnabled() const { return m_isEnabled; }
	
	/**
	 * @brief Sets if this event processor is enabled or not.
	 */
	void setEnabled( const bool isEnabled = true ) { m_isEnabled = isEnabled; }
	
	//@}
	
	
private:

	/**
	 * @brief True if this event processor is enabled, false otherwise.
	 */
	bool m_isEnabled;
};


} // namespace event

} // namespace vgeGL

#endif //#ifndef _VGEGL_EVENT_IEVENTPROCESSOR_H
