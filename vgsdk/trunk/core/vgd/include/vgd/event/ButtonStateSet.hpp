// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_EVENT_BUTTONSTATESET_HPP
#define _VGD_EVENT_BUTTONSTATESET_HPP

#include <set>
#include "vgd/event/EventVisitor.hpp"
#include "vgd/vgd.hpp"



namespace vgd
{
	
namespace event
{



/**
 * @brief List of buttons in the DOWN state.
 * 
 * Useful to trace the state of all buttons in the system or in at a specific time.
 * 
 * @todo Adds two constructors : the first one that take the single down button, the second one that take the list of down buttons. 
 */
struct VGD_API ButtonStateSet : public EventVisitor
{
	/**
	 * @brief Virtual destructor.
	 */
	virtual ~ButtonStateSet() {}

	/**
	 * @name Visitor DP (see EventVisitor).
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

	void apply( const vgd::event::Location2Event		*pLocation2Event 			);
	void apply( const vgd::event::Motion3Event			*pMotion3Event				);
	void apply( const vgd::event::MouseWheelEvent		*pMouseWheelEvent			);

	//@}



	/**
	 * @name Accessors
	 */
	//@{
	
	/**
	 * @brief Tells if at least one button is down.
	 */
	bool isDown() const;
		
	/**
	 * @brief Tells if a button is down.
	 */
	bool isDown( const int32 idButton ) const;

	/**
	 * @brief Sets the button state to down.
	 */
	void setDown( const int32 idButton );

	/**
	 * @brief Sets the button state to up.
	 */
	void setUp( const int32 idButton );
	
	/**
	 * @brief Sets the state of all buttons to up.
	 */
	void setUp();
	
	/**
	 * @brief Returns the number of buttons that are in the down state.
	 * 
	 * @return number of buttons.
	 */
	uint32 getNumDown() const;

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

#endif //#ifndef _VGD_EVENT_BUTTONSTATESET_HPP
