// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_EVENT_BUTTONSTATESET_H
#define _VGD_EVENT_BUTTONSTATESET_H

#include <set>
#include "vgd/vgd.hpp"

#include "vgd/event/EventVisitor.hpp"

namespace vgd
{
	
namespace event
{

/**
 * @brief List of buttons in the DOWN state.
 * 
 * Useful to trace the state of all buttons in the system or in at a specific time.
 */
struct VGD_API ButtonStateSet : public EventVisitor
{
	/**
	 * @name Visitor DP
	 */
	//@{

	/**
	 * @brief Update internal structure in this class to reflect the button modification from this event.
	 * 
	 * @param pKeyboardButtonEvent
	 * 
	 * @pre pKeyboardButtonEvent != 0
	 */
	void apply( const vgd::event::KeyboardButtonEvent *pKeyboardButtonEvent );

	/**
	 * @brief Update internal structure in this class to reflect the button modification from this event.
	 * 
	 * @param pMouseButtonEvent
	 * 
	 * @pre pMouseButtonEvent != 0
	 */
	void apply( const vgd::event::MouseButtonEvent *pMouseButtonEvent );
	
	//@}



	/**
	 * @name Accessors
	 */
	//@{
	
	/**
	 * @brief Tells if a button is down.
	 */
	bool isDown( const int32 idButton ) const;

	/**
	 * @brief Sets a button down.
	 */
	void setDown( const int32 idButton );

	/**
	 * @brief Sets a button up.
	 */
	void setUp( const int32 idButton );
	
	//@}



	/**
	 * @name Comparison methods.
	 */
	//@{

	/**
	 * @brief Equality comparison.
	 */
	bool			operator ==( const ButtonStateSet& other ) const;

	/**
	 * @brief Difference comparison.
	 */
	bool			operator !=( const ButtonStateSet& other ) const;
	
	//@}
	


protected:
	/**
	 * @brief Typedef for container.
	 */
	typedef std::set< int32 > ButtonIDSet;

	/**
	 * @brief A set to store id of buttons that are DOWN.
	 */
	ButtonIDSet	m_down;
};



} // namespace event

} // namespace vgd

#endif //#ifndef _VGD_EVENT_BUTTONSTATESET_H
