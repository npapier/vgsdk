// VGSDK - Copyright (C) 2004, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_PROCESSEVENT_HPP
#define _VGEGL_TECHNIQUE_PROCESSEVENT_HPP

#include <vgd/event/Event.hpp>
#include <vgd/field/TSingleField.hpp>

#include "vgeGL/technique/Technique.hpp"



namespace vgeGL
{
	
namespace technique
{



struct VGEGL_API ProcessEvent : public Technique
{
	/**
	 * @name Technique parameters
	 */
	//@{

	/**
	 * @brief Sets the event to dispatch
	 * 
	 * @param event		the incoming event
	 */
	void setEvent( vgd::Shp< vgd::event::Event > event );

	/**
	 * @brief Returns the event to dispatch
	 * 
	 * @return the event
	 */
	vgd::Shp< vgd::event::Event > getEvent() const;
	//@}



	/**
	 * @brief Traverse scene graph and dispatch/process event.
	 * 
	 * @param engine			engine used during evaluation
	 * @param traverseElements	elements to evaluate
	 */
	void apply(	vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements );



	/**
	 * @name Accessors to technique parameters stored in engine
	 */
	//@{
	
	typedef vgd::Shp<vgd::event::Event> ProcessEventValueType;

	/**
	 * @brief Type of the field added in Engine.
	 */
	typedef vgd::field::TSingleField< ProcessEventValueType > FProcessEventType;
	
	/**
	 * @brief Name of the field added in Engine to gain access on the event in handler.
	 */
	static const std::string getFProcessEvent();
	
	//@}



private:
	vgd::Shp<vgd::event::Event> m_event;		///< The event to dispatch for processing
};



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_PROCESSEVENT_HPP
