// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_PROCESSEVENT_H
#define _VGEGL_TECHNIQUE_PROCESSEVENT_H

#include <vgd/event/Event.hpp>
#include <vgd/field/TSingleField.hpp>
#include "vgeGL/vgeGL.hpp"
#include "vgeGL/technique/Technique.hpp"



namespace vgeGL
{
	
namespace technique
{



struct VGEGL_API ProcessEvent : public Technique
{
	/**
	 * @name Accessors to technique parameters.
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



	/**
	 * @brief Traverse scene graph and dispatch/process event.
	 * 
	 * @param pEngine					engine that must be used during evaluation
	 * @param pTraverseElements	node to traverse
	 * @param event					event to dispatch/process
	 */
	void apply( vge::engine::Engine *pEngine, vge::visitor::TraverseElementVector* pTraverseElements,
					vgd::Shp<vgd::event::Event> event );
};



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_PROCESSEVENT_H
