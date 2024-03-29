//// VGSDK - Copyright (C) 2004, 2008, 2009, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//// Author Guillaume Brocker
//
//#include "vgeGLBase/handler/processEvent/Dragger.hpp"
//
//#include <GL/glu.h>
//
//#include <vgDebug/helpers.hpp>
//#include <vgd/event/KeyboardButtonEvent.hpp>
//#include <vgd/event/Location2Event.hpp>
//#include <vgd/event/Motion3Event.hpp>
//#include <vgd/event/MouseButtonEvent.hpp>
//#include <vgd/event/MouseWheelEvent.hpp>
//#include <vgd/field/DirtyFlag.hpp>
//#include <vgd/node/Dragger.hpp>
//#include <vgeGLBase/engine/Engine.hpp>
//
//#include "vgeGLBase/event/DefaultEventProcessor.hpp"
//#include "vgeGLBase/technique/ProcessEvent.hpp"
//
//
//
//namespace vgeGLBase
//{
//
//namespace handler
//{
//
//namespace processEvent
//{
//
//
//
//void Dragger::apply( vgd::event::AxisEvent * )
//{
//}
//
//
//
//void Dragger::apply( vgd::event::HatEvent * )
//{
//}
//
//
//
//void Dragger::apply( vgd::event::JoystickButtonEvent * )
//{
//}
//
//
//
//void Dragger::apply( vgd::event::KeyboardButtonEvent * )
//{
//}
//
//
//
//void Dragger::apply( vgd::event::Location2Event * )
//{
//}
//
//
//
//void Dragger::apply( vgd::event::MouseButtonEvent * )
//{
//}
//
//
//
//void Dragger::apply( vgd::event::Motion3Event * )
//{
//}
//
//
//
//void Dragger::apply( vgd::event::MouseWheelEvent * )
//{
//}
//
//
//
//void Dragger::apply( vgd::event::SizeEvent *pSizeEvent )
//{
//}
//
//
//
//void Dragger::apply( vgd::event::TimerEvent *pTimerEvent )
//{
//}
//
//
//
//vgm::Vec2f Dragger::convertKeyboardArrowToVec2f( vgd::event::KeyboardButtonEvent *keyboardButtonEvent )
//{
//	vgm::Vec2f	v2fDelta;
//
//	using vgd::event::ButtonEvent;
//	using vgd::event::KeyboardButtonEvent;
//
//	if ( keyboardButtonEvent->getState() == ButtonEvent::DOWN )
//	{
//		// Navigation keys.
//		switch ( keyboardButtonEvent->getButtonID() )
//		{
//			case KeyboardButtonEvent::KEY_LEFT:
//				v2fDelta = vgm::Vec2f( -1.f, 0.f );
//				break;
//
//			case KeyboardButtonEvent::KEY_RIGHT:
//				v2fDelta = vgm::Vec2f( 1.f, 0.f );
//				break;
//
//			case KeyboardButtonEvent::KEY_UP:
//				v2fDelta = vgm::Vec2f( 0.f, 1.f );
//				break;
//
//			case KeyboardButtonEvent::KEY_DOWN:
//				v2fDelta = vgm::Vec2f( 0.f, -1.f );
//				break;
//
//			default:
//				v2fDelta = vgm::Vec2f( 0.f, 0.f );
//		}
//	}
//	else
//	{
//		v2fDelta = vgm::Vec2f( 0.f, 0.f );
//	}
//
//	return ( v2fDelta );
//}
//
//
//
//void Dragger::logDebug( vgd::Shp< vgd::event::Event > event )
//{
//	using vgd::event::KeyboardButtonEvent;
//	using vgd::event::MouseButtonEvent;
//	using vgd::event::Location2Event;
//	using vgd::event::MouseWheelEvent;
//
//	vgd::event::KeyboardButtonEvent	*keyboardButtonEvent= dynamic_cast<KeyboardButtonEvent*>(event.get());
//	MouseButtonEvent				*mouseButtonEvent	= dynamic_cast<MouseButtonEvent*>(event.get());
//	Location2Event					*location2Event		= dynamic_cast<Location2Event*>(event.get());
//	MouseWheelEvent					*mouseWheelEvent	= dynamic_cast<MouseWheelEvent*>(event.get());
//
//	if( keyboardButtonEvent != 0 )
//	{
//		vgLogDebug(
//			"KeyboardButtonEvent (%d,%d)",
//			keyboardButtonEvent->getButtonID(),
//			keyboardButtonEvent->getState()
//		);
//	}
//	else if( mouseButtonEvent != 0 )
//	{
//		vgLogDebug(
//			"MouseButtonEvent (%d,%d)",
//			mouseButtonEvent->getButtonID(),
//			mouseButtonEvent->getState()
//		);
//	}
//	else if( location2Event != 0 )
//	{
//		vgLogDebug(
//			"Location2Event ( previousLocation(%f,%f), location(%f,%f), size(%f,%f)",
//			location2Event->getPreviousLocation()[0],
//			location2Event->getPreviousLocation()[1],
//			location2Event->getLocation()[0],
//			location2Event->getLocation()[1],
//			location2Event->getSize()[0],
//			location2Event->getSize()[1]
//		);
//	}
//	else if( mouseWheelEvent != 0 )
//	{
//		vgLogDebug(
//			"MouseWheelEvent (%d,%d)",
//			mouseWheelEvent->getAxis(),
//			mouseWheelEvent->getDelta()
//		);
//	}
//	else
//	{
//		vgLogDebug("Unknown event");
//	}
//}
//
//
//
//const bool Dragger::ConvertVectorsFromWindowToObject(	vgeGLBase::engine::Engine *pEngine, vgd::node::Dragger *pDragger,
//														vgm::Vec3f& oLeftToRightO, vgm::Vec3f& oUpToDownO, vgm::Vec3f& oNearToFarO )
//{
//	// MODELVIEW : Gets scene transformation
//	vgm::MatrixR&		matrixTransformScene = pEngine->getGeometricalMatrix().getTop();
//
//	// PROJECTION
//	vgm::MatrixR&	matrixProjectionScene = pEngine->getProjectionMatrix().getTop();
//
//	vgm::RawMatrixd	transformProjectionD;
//	matrixProjectionScene.getValue( transformProjectionD );
//
//	// VIEWPORT
//	const vgm::Rectangle2i viewport = pEngine->getViewport();
//	GLint viewportGL[4];
//	viewportGL[0] = viewport.x();
//	viewportGL[1] = viewport.y();
//	viewportGL[2] = viewport.width();
//	viewportGL[3] = viewport.height();
//
//	// Compute conversion
//
//	//
//	GLdouble x, y, z;
//	GLdouble dZCenterO;
//
//	// gluProject function maps object coordinates to window coordinates.
//	vgm::Vec3f		center;
//	vgm::RawMatrixd	transformSceneD;
//
//	vgd::Shp< vgeGLBase::basic::Hit > hit = getHit( m_pGLEngine );
//	if (	!hit ||											// no hit
//			(/*hit && */hit->modelviewS().isInvalid()) )	// invalid hit
//	{
//		// No hit, so scene bounding box is used
//		using vgd::node::IBoundingBox;
//		vgd::Shp< IBoundingBox > pBoundingBox = vgd::dynamic_pointer_cast< IBoundingBox >( pDragger->getSurround() );
//
//		if ( pBoundingBox.get() == 0 )
//		{
//			vgAssertN( false, "dragger.surround contains a reference to an object that don't implement IBoundingBox interface.");
//			return false;
//		}
//		else if ( pBoundingBox->getBoundingBox().isEmpty() )
//		{
//			return false;
//		}
//
//		// center and transformSceneD
//		center = pBoundingBox->getBoundingBox().getCenter();
//		matrixTransformScene.getValue( transformSceneD );
//	}
//	else
//	{
//		// Hit
//		center = hit->nearestVertexS();
//		hit->modelviewS().getValue( transformSceneD );
//	}
//
//	bool bRetVal;
//	bRetVal = gluProject(
//		center[0], center[1], center[2],
//		&transformSceneD[0][0],
//		&transformProjectionD[0][0],
//		viewportGL,
//		&x, &y, &dZCenterO ) == GL_TRUE;
//
//	// Restore transformSceneD from matrixTransformScene
//	matrixTransformScene.getValue( transformSceneD );
//
//	//
//	vgm::Vec3d	vec3dUpperLeftCornerO;
//	vgm::Vec3d	vec3dUpperRightCornerO;
//	vgm::Vec3d	vec3dDownLeftCornerO;
//
//	// The gluUnProject function maps window coordinates to object coordinates.
//	bRetVal &= gluUnProject(
//		viewportGL[0], viewportGL[1] + viewportGL[3], dZCenterO,
//		&transformSceneD[0][0],
//		&transformProjectionD[0][0],
//		viewportGL,
//		&x, &y, &z ) == GL_TRUE;
//	vec3dUpperLeftCornerO.setValue( x, y , z );
//
//	bRetVal &= gluUnProject(
//		viewportGL[0] + viewportGL[2], viewportGL[1] + viewportGL[3], dZCenterO,
//		&transformSceneD[0][0],
//		&transformProjectionD[0][0],
//		viewportGL,
//		&x, &y, &z ) == GL_TRUE;
//	vec3dUpperRightCornerO.setValue( x, y, z );
//
//	bRetVal &= 	gluUnProject(
//		viewportGL[0], viewportGL[1], dZCenterO,
//		&transformSceneD[0][0],
//		&transformProjectionD[0][0],
//		viewportGL,
//		&x, &y, &z ) == GL_TRUE;
//	vec3dDownLeftCornerO.setValue( x, y, z );
//
//	//
//	vgm::Vec3d vec3dUpperLeftCornerFarO;
//	vgm::Vec3d vec3dUpperLeftCornerNearO;
//
//	bRetVal &= 	gluUnProject(
//		viewportGL[0] + viewportGL[2]/2.f, viewportGL[1] + viewportGL[3]/2.f, 1.f,
//		&transformSceneD[0][0],
//		&transformProjectionD[0][0],
//		viewportGL,
//		&x, &y, &z ) == GL_TRUE;
//	vec3dUpperLeftCornerFarO.setValue( x, y, z );
//
//	bRetVal &= 	gluUnProject(
//		viewportGL[0] + viewportGL[2]/2.f, viewportGL[1] + viewportGL[3]/2.f, 0.f,
//
//		&transformSceneD[0][0],
//		&transformProjectionD[0][0],
//		viewportGL,
//		&x, &y, &z ) == GL_TRUE;
//	vec3dUpperLeftCornerNearO.setValue( x, y, z );
//
//	// Final computation
//	vgm::Vec3d vec3dLeftToRightO;
//	vec3dLeftToRightO	= vec3dUpperRightCornerO	-	vec3dUpperLeftCornerO;
//	oLeftToRightO.setValue(
//		static_cast<float>(vec3dLeftToRightO[0]),
//		static_cast<float>(vec3dLeftToRightO[1]),
//		static_cast<float>(vec3dLeftToRightO[2])	);
//
//	vgm::Vec3d vec3dUpToDownO;
//	vec3dUpToDownO		= vec3dDownLeftCornerO		-	vec3dUpperLeftCornerO;
//	oUpToDownO.setValue(
//		static_cast<float>(vec3dUpToDownO[0]),
//		static_cast<float>(vec3dUpToDownO[1]),
//		static_cast<float>(vec3dUpToDownO[2]) );
//
//	vgm::Vec3d vec3dNearToFarO;
//	vec3dNearToFarO	= vec3dUpperLeftCornerFarO	-	vec3dUpperLeftCornerNearO;
//	oNearToFarO.setValue(
//		static_cast<float>(vec3dNearToFarO[0]),
//		static_cast<float>(vec3dNearToFarO[1]),
//		static_cast<float>(vec3dNearToFarO[2]) );
//
//	return bRetVal;
//}
//
//
//
//void Dragger::preApply( vgeGLBase::engine::Engine *pGLEngine, vgd::node::Dragger *pDragger )
//{
//	// Update internal attribute (to give access to them from EventVisitor methods).
//	m_pGLEngine = pGLEngine;
//	m_pDragger	= pDragger;
//
//	// Check dragger.listener field
//	if ( !m_pDragger->getListener() )
//	{
//		// nothing to do
//		return;
//	}
//
//	// Gets event stored in Engine.
//	m_pEvent = getEvent( pGLEngine );
//	assert( m_pEvent.get() != 0 );
//
//	// Process event
//	// Change Dragger.currentState.
//	using vgd::field::EditorRO;
//	using vgd::node::Dragger;
//
//	const vgd::event::ButtonStateSet& bss = m_pEvent->getButtonStates();
//
//	EditorRO< Dragger::FBindingsType > editorBindingsRO(
//		pDragger->getFieldRO<Dragger::FBindingsType>(pDragger->getFBindings()) );
//
//	// sets founded to true when button states of incoming event is equal to a binding from bindings field.
//	bool founded = false;
//
//	for (	Dragger::FBindingsType::const_iterator	iBindings		= editorBindingsRO->begin(),
//													iEndBindings	= editorBindingsRO->end();
//
//			iBindings != iEndBindings;
//			++iBindings )
//	{
//		const Dragger::FBindingsType::value_type& elt = *iBindings;
//
//		if ( elt.second == bss )
//		{
//				// Update current state if and only if its value has changed.
//			if ( pDragger->getCurrentState() != elt.first )
//			{
//				pDragger->setCurrentState( elt.first );
//			}
//
//			founded = true;
//			break;
//		}
//	}
//
//	if ( !founded )
//	{
//		if ( pDragger->getCurrentState() != Dragger::IDRAGGER_DEFAULT )
//		{
//			pDragger->setCurrentState( Dragger::IDRAGGER_DEFAULT );
//		}
//	}
//}
//
//
//
//void Dragger::apply()
//{
//	if ( m_pDragger->getListener() )
//	{
//		m_pEvent->accept( *this );
//	}
//	// else nothing to do, because the dragger.listener field is false.
//}
//
//
//
//void Dragger::postApply()
//{
//	vgd::field::DirtyFlag *pDF = m_pDragger->getDirtyFlag( m_pDragger->getDFNode() );
//	assert( pDF != 0 );
//
//	if ( pDF->isDirty() )
//	{
//		vgm::MatrixR matrix = m_pDragger->computeMatrixFromFields();
//		m_pDragger->setMatrix( matrix );
//		// pDF->validate();	validation is done only during paint().
//	}
//	//else nothing to do
//}
//
//
//
//vgd::Shp< vgd::event::Event > Dragger::getEvent( vge::engine::Engine *pEngine )
//{
//	using vgeGLBase::technique::ProcessEvent;
//
//	assert( pEngine->isField( ProcessEvent::getFProcessEvent() ) );
//
//	vgd::field::EditorRO< ProcessEvent::FProcessEventType > eventInEngine =
//		pEngine->getFieldRO< ProcessEvent::FProcessEventType >( ProcessEvent::getFProcessEvent() );
//
//	vgd::Shp< vgd::event::Event > event = eventInEngine->getValue();
//
//	return event;
//}
//
//
//
//vgd::Shp< vgeGLBase::basic::Hit > Dragger::getHit( vge::engine::Engine * engine )
//{
//	using vgeGLBase::event::DefaultEventProcessor;
//	typedef DefaultEventProcessor::FHitType FHitType;
//
//	vgd::Shp< vgeGLBase::basic::Hit > hit;
//
//	if ( engine->isField( DefaultEventProcessor::getFHit() ) )
//	{
//		vgd::field::EditorRO< FHitType > hitInEngine = engine->getFieldRO< FHitType >( DefaultEventProcessor::getFHit() );
//		hit = hitInEngine->getValue();
//	}
//	// else nothing to do
//	return hit;
//}
//
//
//
//} // namespace processEvent
//
//} // namespace handler
//
//} // namespace vge
//