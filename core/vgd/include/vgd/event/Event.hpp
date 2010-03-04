// VGSDK - Copyright (C) 2004-2006, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_EVENT_HPP
#define _VGD_EVENT_EVENT_HPP

#include "vgd/event/ButtonStateSet.hpp"



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
	 * @param	source			a pointer to the object that raise the event
	 * @param	buttonStates	a reference to the button state set
	 */
	Event( Source *source, const ButtonStateSet& buttonStates );
	
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
	
	/**
	 * @brief	Retrieves the button states.
	 * 
	 * @return	a reference to the button states
	 */
	const ButtonStateSet& getButtonStates() const;

	/**
	 * @brief	Test if a button is down.
	 * 
	 * @param buttonID	a button identifier
	 * 
	 * @remarks The request is processed by the ButtonStateSet. It's a shortcut for getButtonStates().isDown()
	 */
	bool isButtonDown( const int32 buttonID ) const;



	/**
	 * @brief Implements the accept operation that takes a visitor as an argument (DP Visitor).
	 * 
	 * @param eventVisitor	a reference to a visitor
	 */
	virtual void accept( vgd::event::EventVisitor& eventVisitor )=0;



	/**
	 * @name Refresh policy
	 */
	//@{

	/**
	 * @brief Forces the refresh of the canvas.
	 *
	 * @param doIt		true to force the repaint of the canvas even if no changes have been made in the scene graph.
	 *
	 * @remarks The canvas is an event listener. So when it receives an event (see BasicManipulator::onEvent()), vgUI::Canvas::refreshForced() is called if the event is marked to schedule a refresh.
	 */
	void scheduleRefreshForced( const bool doIt = true );

	/**
	 * @brief Returns if the refresh of the canvas is desired.
	 *
	 * @return true if the refresh of the canvas is desired, false otherwise.
	 */
	const bool isScheduleRefreshForced() const;
	//@}


private:

	Source*			m_pSource;					///< a pointer to the source of the event

	ButtonStateSet	m_buttonStates;				///< a button state set

	bool			m_scheduleRefreshForced;	///< true to force the refresh of the canvas. See scheduleRefreshForced()/isScheduleRefreshForced().
};



} // namespace event
	
} // namespace vgd

#endif // _VGD_EVENT_EVENT_HPP
