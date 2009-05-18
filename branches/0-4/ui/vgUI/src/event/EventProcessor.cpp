// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgUI/event/EventProcessor.hpp"

#include "vgUI/Canvas.hpp"



namespace vgUI
{

namespace event
{



EventProcessor::EventProcessor( ::vgUI::Canvas *canvas )
:	::vgeGL::event::EventProcessor(canvas)
{}



::vgUI::Canvas * EventProcessor::getCanvas() const
{
	::vgUI::Canvas * canvas = dynamic_cast< ::vgUI::Canvas * >( getSceneManager() );
	assert( canvas != 0 );

	return canvas;
}



} // namespace event

} // namespace vgui
