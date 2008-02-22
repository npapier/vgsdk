// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_EVENT_HPP
#define _VGD_EVENT_EVENT_HPP

#include "vgd/vgd.hpp"
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
	 * @remarks The request is processed by the ButtonStateSet. It's a shortcut for getButtonStates().isDonw()
	 */
	bool isButtonDown( const int32 buttonID ) const;



	/**
	 * @brief Implements the accept operation that takes a visitor as an argument (DP Visitor).
	 * 
	 * @param eventVisitor	a reference to a visitor
	 */
	virtual void accept( vgd::event::EventVisitor& eventVisitor )=0;



private:
	/**
	 * @brief	a pointer to the source of the event
	 */
	Source*			m_pSource;
	
	/**
	 * @brief	a button state set
	 */
	ButtonStateSet	m_buttonStates;
};



} // namespace event
	
} // namespace vgd

#endif // _VGD_EVENT_EVENT_HPP
