// VGSDK - Copyright (C) 2004, 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGEGL_HANDLER_PROCESSEVENT_DRAGGER_HPP
#define _VGEGL_HANDLER_PROCESSEVENT_DRAGGER_HPP

#include <vgd/Shp.hpp>
#include <vgd/event/Event.hpp>
#include <vgd/event/EventVisitor.hpp>
#include <vgm/Vector.hpp>

#include "vgeGL/vgeGL.hpp"

namespace vgd
{
	namespace node
	{
		struct Dragger;
	}
}

namespace vge
{
	namespace engine
	{
		struct Engine;
	}
}



namespace vgeGL
{

	namespace engine
	{
		struct Engine;
	}

namespace handler
{

namespace processEvent
{



/**
 * @brief Abstract class for handlers of Dragger nodes.
 */
struct VGEGL_API Dragger : public vgd::event::EventVisitor
{
	/**
	 * @name Interface of EventVisitor.
	 *
	 * The following methods do nothing and must be overriden by derived Dragger to perform proper actions.
	 */
	//@{
	void apply( const vgd::event::AxisEvent				*pAxisEvent				);
	void apply( const vgd::event::HatEvent				*pHatEvent				);
	void apply( const vgd::event::JoystickButtonEvent	*pJoystickButtonEvent	);
	void apply( const vgd::event::KeyboardButtonEvent	*pKeyboardButtonEvent	);
	void apply( const vgd::event::Location2Event		*pLocation2Event 		);
	void apply( const vgd::event::MouseButtonEvent		*pMouseButtonEvent		);
	void apply( const vgd::event::Motion3Event			*pMotion3Event			);
	void apply( const vgd::event::MouseWheelEvent		*pMouseWheelEvent		);
	void apply( const vgd::event::SizeEvent				*pSizeEvent				);
	void apply( const vgd::event::TimerEvent			*pTimerEvent			);
	//@}



	/**
	 * @brief Converts keyboard arrow key into a vector.
	 *
	 * The vector is unit length and is equal to :
	 * - Vec2f( -1.f, 0.f ) for left arrow.
	 * - Vec2f( 1.f, 0.f ) for right arrow.
	 * - Vec2f( 0.f, 1.f ) for up arrow.
	 * - Vec2f( 0.f, -1.f ) for down arrow.
	 *
	 * @param keyboardButtonEvent	the keyboard button event.
	 * @return the converted vector.
	 */
	vgm::Vec2f convertKeyboardArrowToVec2f( vgd::event::KeyboardButtonEvent *keyboardButtonEvent );

	/**
	 * @brief Output to logDebug() informations contains in event.
	 *
	 * @param event	an event
	 *
	 * @todo process vgd::event::Motion3Event
	 */
	void logDebug( vgd::Shp< vgd::event::Event > event );

	/**
	 * @brief Convert vectors from window space to object space.
	 *
	 * @param pEngine				an engine
	 * @param pDragger			a dragger
	 * @param oLeftToRightO
	 * @param oUpToDownO
	 * @param oNearToFarO
	 *
	 * @todo comments
	 * @todo Add more methods from ktvs/src/view/Abstract.cpp, move to another file/class
	 */
	const bool ConvertVectorsFromWindowToObject(	vgeGL::engine::Engine *pEngine, vgd::node::Dragger *pDragger,
			vgm::Vec3f& oLeftToRightO, vgm::Vec3f& oUpToDownO, vgm::Vec3f& oNearToFarO );

	/**
	 * @brief Must be called by derived handler at the beginning of apply().
	 *
	 * Update m_pGLEngine, m_pDragger, m_pEvent and update Dragger.currentState field.
	 */
	void preApply( vgeGL::engine::Engine *pGLEngine, vgd::node::Dragger *pDragger );

	/**
	 * @brief Must be called by derived handler after preApply() and before postApply()
	 *
	 * This method use the EventVisitor interface to process the incoming event.
	 */
	void apply();

	/**
	 * @brief Must be called by derived handler at the end of apply().
	 *
	 * Update Dragger.setMatrix() if needeed and validate pDragger->DF(node).
	 */
	void postApply();



protected:
	vgeGL::engine::Engine	*m_pGLEngine;
	vgd::node::Dragger		*m_pDragger;

	/**
	 * @brief Returns a reference on the event stored in engine
	 *
	 * @param pEngine		engine that contains the current event
	 *
	 * @return a reference on the current event
	 */
	vgd::Shp< vgd::event::Event > getEvent( vge::engine::Engine *pEngine );

	vgd::Shp< vgd::event::Event > m_pEvent;
};



} // namespace processEvent

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PROCESSEVENT_DRAGGER_HPP
