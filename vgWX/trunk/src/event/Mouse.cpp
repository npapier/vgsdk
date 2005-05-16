// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgWX/event/Mouse.hpp"

#include <limits>
#include <vgd/Shp.hpp>
#include <vgd/event/Location2Event.hpp>
#include <vgd/event/MouseButtonEvent.hpp>
#include <vgd/event/MouseWheelEvent.hpp>

#include <wx/window.h>

#include "vgWX/event/Helpers.hpp"



namespace vgWX
{
	
namespace event
{
	
BEGIN_EVENT_TABLE(Mouse, wxEvtHandler)
	EVT_LEFT_DCLICK	(Mouse::onLeftDoubleClick	)
	EVT_LEFT_DOWN		(Mouse::onLeftDown			)
	EVT_LEFT_UP			(Mouse::onLeftUp				)
	EVT_MIDDLE_DCLICK	(Mouse::onMiddleDoubleClick)
	EVT_MIDDLE_DOWN	(Mouse::onMiddleDown			)
	EVT_MIDDLE_UP		(Mouse::onMiddleUp			)
	EVT_RIGHT_DCLICK	(Mouse::onRightDoubleClick	)
	EVT_RIGHT_DOWN		(Mouse::onRightDown			)
	EVT_RIGHT_UP		(Mouse::onRightUp				)
	EVT_MOTION			(Mouse::onMotion				)
	EVT_MOUSEWHEEL		(Mouse::onWheel				)
END_EVENT_TABLE()
	
	
Mouse::Mouse() :
	m_previousMousePosition( std::numeric_limits<float>::max(), std::numeric_limits<float>::max() )
{
}


void Mouse::onLeftDoubleClick( wxMouseEvent& event )
{
	// Update global button states
	updateModifiersOfGlobalButtonStates( event );
	//vgd::event::detail::GlobalButtonStateSet::update( vgd::event::MouseButtonEvent::MOUSE_BUTTON_1, false );
		
	vgd::event::MouseButtonEvent *mouseButtonEvent;
	
	mouseButtonEvent = new vgd::event::MouseButtonEvent(
		this,
		vgd::event::detail::GlobalButtonStateSet::get(),
		vgd::event::MouseButtonEvent::MOUSE_BUTTON_1,
		vgd::event::MouseButtonEvent::DCLICK );
	this->fireEvent(vgd::Shp<vgd::event::Event>(mouseButtonEvent));

	event.Skip();
}


void Mouse::onLeftDown( wxMouseEvent& event )
{
	// Update global button states
	updateModifiersOfGlobalButtonStates( event );
	//vgd::event::detail::GlobalButtonStateSet::update( vgd::event::MouseButtonEvent::MOUSE_BUTTON_1, true );
		
	vgd::event::MouseButtonEvent *mouseButtonEvent;
	
	mouseButtonEvent = new vgd::event::MouseButtonEvent(
		this,
		vgd::event::detail::GlobalButtonStateSet::get(),
		vgd::event::MouseButtonEvent::MOUSE_BUTTON_1,
		vgd::event::MouseButtonEvent::DOWN );
	this->fireEvent(vgd::Shp<vgd::event::Event>(mouseButtonEvent));

	event.Skip();
}
 

void Mouse::onLeftUp( wxMouseEvent& event )
{
	// Update global button states
	updateModifiersOfGlobalButtonStates( event );
	//vgd::event::detail::GlobalButtonStateSet::update( vgd::event::MouseButtonEvent::MOUSE_BUTTON_1, false );
		
	vgd::event::MouseButtonEvent *mouseButtonEvent;
	
	mouseButtonEvent = new vgd::event::MouseButtonEvent(
		this,
		vgd::event::detail::GlobalButtonStateSet::get(),
		vgd::event::MouseButtonEvent::MOUSE_BUTTON_1,
		vgd::event::MouseButtonEvent::UP );
	this->fireEvent(vgd::Shp<vgd::event::Event>(mouseButtonEvent));

	event.Skip();	
}


void Mouse::onMiddleDoubleClick( wxMouseEvent& event )
{
	// Update global button states
	updateModifiersOfGlobalButtonStates( event );
	//vgd::event::detail::GlobalButtonStateSet::update( vgd::event::MouseButtonEvent::MOUSE_BUTTON_2, false );
		
	vgd::event::MouseButtonEvent *mouseButtonEvent;
	
	mouseButtonEvent = new vgd::event::MouseButtonEvent(
		this,
		vgd::event::detail::GlobalButtonStateSet::get(),
		vgd::event::MouseButtonEvent::MOUSE_BUTTON_2,
		vgd::event::MouseButtonEvent::DCLICK );
	this->fireEvent(vgd::Shp<vgd::event::Event>(mouseButtonEvent));

	event.Skip();	
}


void Mouse::onMiddleDown( wxMouseEvent& event )
{
	// Update global button states
	updateModifiersOfGlobalButtonStates( event );
	//vgd::event::detail::GlobalButtonStateSet::update( vgd::event::MouseButtonEvent::MOUSE_BUTTON_2, true );
		
	vgd::event::MouseButtonEvent *mouseButtonEvent;
	
	mouseButtonEvent = new vgd::event::MouseButtonEvent(
		this,
		vgd::event::detail::GlobalButtonStateSet::get(),
		vgd::event::MouseButtonEvent::MOUSE_BUTTON_2,
		vgd::event::MouseButtonEvent::DOWN );
	this->fireEvent(vgd::Shp<vgd::event::Event>(mouseButtonEvent));

	event.Skip();
}


void Mouse::onMiddleUp( wxMouseEvent& event )
{
	// Update global button states
	updateModifiersOfGlobalButtonStates( event );
	//vgd::event::detail::GlobalButtonStateSet::update( vgd::event::MouseButtonEvent::MOUSE_BUTTON_2, false );
		
	vgd::event::MouseButtonEvent *mouseButtonEvent;
	
	mouseButtonEvent = new vgd::event::MouseButtonEvent(
		this,
		vgd::event::detail::GlobalButtonStateSet::get(),
		vgd::event::MouseButtonEvent::MOUSE_BUTTON_2,
		vgd::event::MouseButtonEvent::UP );
	this->fireEvent(vgd::Shp<vgd::event::Event>(mouseButtonEvent));

	event.Skip();
}


void Mouse::onRightDoubleClick( wxMouseEvent& event )
{
	// Update global button states
	updateModifiersOfGlobalButtonStates( event );
	//vgd::event::detail::GlobalButtonStateSet::update( vgd::event::MouseButtonEvent::MOUSE_BUTTON_3, false );
		
	vgd::event::MouseButtonEvent *mouseButtonEvent;
	
	mouseButtonEvent = new vgd::event::MouseButtonEvent(
		this,
		vgd::event::detail::GlobalButtonStateSet::get(),
		vgd::event::MouseButtonEvent::MOUSE_BUTTON_3,
		vgd::event::MouseButtonEvent::DCLICK );
	this->fireEvent(vgd::Shp<vgd::event::Event>(mouseButtonEvent));

	event.Skip();	
}


void Mouse::onRightDown( wxMouseEvent& event )
{
	// Update global button states
	updateModifiersOfGlobalButtonStates( event );
	//vgd::event::detail::GlobalButtonStateSet::update( vgd::event::MouseButtonEvent::MOUSE_BUTTON_3, true );
		
	vgd::event::MouseButtonEvent *mouseButtonEvent;
	
	mouseButtonEvent = new vgd::event::MouseButtonEvent(
		this,
		vgd::event::detail::GlobalButtonStateSet::get(),
		vgd::event::MouseButtonEvent::MOUSE_BUTTON_3,
		vgd::event::MouseButtonEvent::DOWN );
	this->fireEvent(vgd::Shp<vgd::event::Event>(mouseButtonEvent));

	event.Skip();	
}
 

void Mouse::onRightUp( wxMouseEvent& event )
{
	// Update global button states
	updateModifiersOfGlobalButtonStates( event );
	//vgd::event::detail::GlobalButtonStateSet::update( vgd::event::MouseButtonEvent::MOUSE_BUTTON_3, false );
		
	vgd::event::MouseButtonEvent *mouseButtonEvent;
	
	mouseButtonEvent = new vgd::event::MouseButtonEvent(
		this,
		vgd::event::detail::GlobalButtonStateSet::get(),
		vgd::event::MouseButtonEvent::MOUSE_BUTTON_3,
		vgd::event::MouseButtonEvent::UP );
	this->fireEvent(vgd::Shp<vgd::event::Event>(mouseButtonEvent));

	event.Skip();
}


void Mouse::onMotion( wxMouseEvent& event )
{
	// Update global button states
	updateModifiersOfGlobalButtonStates( event );
		
	// Size
	wxWindow *pWindow = dynamic_cast<wxWindow*>(event.GetEventObject());
	assert( pWindow != 0 );

	vgd::event::Location2Event::Size	size;
	size[0]	= static_cast<float>(pWindow->GetClientSize().GetWidth());
	size[1]	= static_cast<float>(pWindow->GetClientSize().GetHeight());

	// Location
	vgd::event::Location2Event::Location	location;
	location[0] = static_cast<float>(event.GetX());
	location[1] = size[1] - static_cast<float>(event.GetY());
	
	this->fireEvent(
		vgd::Shp<vgd::event::Event>(
			new vgd::event::Location2Event(this, 
				vgd::event::detail::GlobalButtonStateSet::get(),
				location, m_previousMousePosition, size )
		)
	);
	
	// Update previous location
	m_previousMousePosition = location;

	event.Skip();
}


void Mouse::onWheel( wxMouseEvent& event )
{
	// Update global button states
	updateModifiersOfGlobalButtonStates( event );
		
	this->fireEvent(
		vgd::Shp<vgd::event::Event>(
			new vgd::event::MouseWheelEvent(
				this,
				vgd::event::detail::GlobalButtonStateSet::get(),
				vgd::event::MouseWheelEvent::VERTICAL,
				event.GetWheelRotation()
			)
		)
	);

	event.Skip();	
}


} // namespace event

} // namespace vgWX
