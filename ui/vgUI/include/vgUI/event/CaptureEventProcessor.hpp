// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGUI_EVENT_CAPTUREEVENTPROCESSOR_HPP
#define _VGUI_EVENT_CAPTUREEVENTPROCESSOR_HPP

#include "vgUI/event/EventProcessor.hpp"



namespace vgUI
{

namespace event
{

/**
 * @brief Event processor to enable capture hotkeys.
 */
struct VGUI_API CaptureEventProcessor : public EventProcessor
{
	/**
	 * @name Constructor
	 */
	//@{
	
	/**
	 * @brief Constructor
	 * 
	 * @param canvas	a reference on the canvas where this processor would be inserted
	 * 
	 * @pre canvas != 0
	 */
	CaptureEventProcessor( ::vgUI::Canvas *canvas );
	//@}


	/**
	 * @brief Method called to process an incoming event.
	 */
	const bool onEvent( vgd::Shp< vgd::event::Event > event );
};


} // namespace event

} // namespace vgUI

#endif //#ifndef _VGUI_EVENT_CAPTUREEVENTPROCESSOR_HPP
