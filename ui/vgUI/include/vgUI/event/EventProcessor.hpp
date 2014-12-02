// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGUI_EVENT_EVENTPROCESSOR_HPP
#define _VGUI_EVENT_EVENTPROCESSOR_HPP

#include <vgeGLBase/event/EventProcessor.hpp>
#include "vgUI/vgUI.hpp"

namespace vgUI
{

struct Canvas;

}



namespace vgUI
{

namespace event
{

/**
 * @brief Event processor with a reference on a canvas.
 */
struct VGUI_API EventProcessor : public ::vgeGLBase::event::EventProcessor
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
	EventProcessor( ::vgUI::Canvas *canvas );
	//@}



protected:

	/**
	 * @brief Returns a reference on the linked canvas.
	 * 
	 * @return a reference on the linked canvas.
	 */
	::vgUI::Canvas *getCanvas() const;
};


} // namespace event

} // namespace vgUI

#endif //#ifndef _VGUI_EVENT_EVENTPROCESSOR_HPP
