// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/processEvent/Dragger.hpp"

#include <vgDebug/Global.hpp>
#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgd/event/Location2Event.hpp>
#include <vgd/event/Motion3Event.hpp>
#include <vgd/event/MouseButtonEvent.hpp>
#include <vgd/event/MouseWheelEvent.hpp>
#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/Dragger.hpp>
#include <vgeGL/engine/Engine.hpp>

#include "vgeGL/technique/ProcessEvent.hpp"



namespace vgeGL
{

namespace handler
{

namespace processEvent
{



void Dragger::apply( const vgd::event::KeyboardButtonEvent * )
{
}



void Dragger::apply( const vgd::event::Location2Event * )
{
}



void Dragger::apply( const vgd::event::MouseButtonEvent * )
{
}



void Dragger::apply( const vgd::event::Motion3Event * )
{
}



void Dragger::apply( const vgd::event::MouseWheelEvent * )
{
}



vgm::Vec2f Dragger::convertKeyboardArrowToVec2f( vgd::event::KeyboardButtonEvent *keyboardButtonEvent )
{
	vgm::Vec2f	v2fDelta;

	using vgd::event::ButtonEvent;
	using vgd::event::KeyboardButtonEvent;
	
	if ( keyboardButtonEvent->getState() == ButtonEvent::DOWN )
	{
		// Navigation keys.
		switch ( keyboardButtonEvent->getButtonID() )
		{
			case KeyboardButtonEvent::KEY_LEFT:
				v2fDelta = vgm::Vec2f( -1.f, 0.f );
				break;
				
			case KeyboardButtonEvent::KEY_RIGHT:
				v2fDelta = vgm::Vec2f( 1.f, 0.f );
				break;
				
			case KeyboardButtonEvent::KEY_UP:
				v2fDelta = vgm::Vec2f( 0.f, 1.f );
				break;
				
			case KeyboardButtonEvent::KEY_DOWN:
				v2fDelta = vgm::Vec2f( 0.f, -1.f );
				break;
			
			default:
				v2fDelta = vgm::Vec2f( 0.f, 0.f );
		}
	}
	else
	{
		v2fDelta = vgm::Vec2f( 0.f, 0.f );
	}
	
	return ( v2fDelta );
}



void Dragger::logDebug( vgd::Shp< vgd::event::Event > event )
{
	using vgd::event::KeyboardButtonEvent;
	using vgd::event::MouseButtonEvent;
	using vgd::event::Location2Event;
	using vgd::event::MouseWheelEvent;
	
	vgd::event::KeyboardButtonEvent	*keyboardButtonEvent= dynamic_cast<KeyboardButtonEvent*>(event.get());
	MouseButtonEvent				*mouseButtonEvent	= dynamic_cast<MouseButtonEvent*>(event.get());
	Location2Event					*location2Event		= dynamic_cast<Location2Event*>(event.get());
	MouseWheelEvent					*mouseWheelEvent	= dynamic_cast<MouseWheelEvent*>(event.get());
	
	if( keyboardButtonEvent != 0 )
	{
		vgDebug::get().logDebug(
			"KeyboardButtonEvent (%d,%d)",
			keyboardButtonEvent->getButtonID(),
			keyboardButtonEvent->getState()
		);
	}
	else if( mouseButtonEvent != 0 )
	{
		vgDebug::get().logDebug(
			"MouseButtonEvent (%d,%d)",
			mouseButtonEvent->getButtonID(),
			mouseButtonEvent->getState()
		);
	}
	else if( location2Event != 0 )
	{
		vgDebug::get().logDebug(
			"Location2Event ( previousLocation(%f,%f), location(%f,%f), size(%f,%f)",
			location2Event->getPreviousLocation()[0],
			location2Event->getPreviousLocation()[1],
			location2Event->getLocation()[0],
			location2Event->getLocation()[1],
			location2Event->getSize()[0],
			location2Event->getSize()[1]
		);
	}
	else if( mouseWheelEvent != 0 )
	{
		vgDebug::get().logDebug(
			"MouseWheelEvent (%d,%d)",
			mouseWheelEvent->getAxis(),
			mouseWheelEvent->getDelta()
		);
	}
	else
	{
		vgDebug::get().logDebug("Unknown event");
	}
}



const bool Dragger::ConvertVectorsFromWindowToObject(	vgeGL::engine::Engine *pEngine, vgd::node::Dragger *pDragger,
							vgm::Vec3f& oLeftToRightO, vgm::Vec3f& oUpToDownO, vgm::Vec3f& oNearToFarO )
{
	// MODELVIEW : Gets scene transformation.
	vgm::MatrixR&		matrixTransformScene = pEngine->getGeometricalMatrix().getTop();
	
	vgm::RawMatrixd	transformSceneD;
	matrixTransformScene.getValue( transformSceneD );

	// PROJECTION
	vgm::MatrixR&	matrixProjectionScene = pEngine->getProjectionMatrix().getTop();
	
	vgm::RawMatrixd	transformProjectionD;
	matrixProjectionScene.getValue( transformProjectionD );

	// VIEWPORT
	//vgm::Rectangle2i viewport;
	//pEngine->getViewport( viewport );
	//	GLint viewportGL[4];
	//	viewportGL[0] = viewport.x();	
	//	viewportGL[1] = viewport.y();
	//	viewportGL[2] = viewport.width();
	//	viewportGL[3] = viewport.height();
	// or
	
	GLint viewportGL[4];
	glGetIntegerv( GL_VIEWPORT, viewportGL );
	
	// Compute convertion.

	//
	GLdouble x, y, z;
	GLdouble dZCenterO;
	
	// gluProject function maps object coordinates to window coordinates.
	vgd::Shp< vgd::node::IBoundingBox > pBoundingBox = 
		vgd::dynamic_pointer_cast< vgd::node::IBoundingBox >( pDragger->getSurround() );

	if ( pBoundingBox.get() == 0 )
	{
		assert( false && "dragger.surround contains a reference to an object that don't implement IBoundingBox interface.");
		return ( false );
	}
	
	vgm::Vec3f center = pBoundingBox->getBoundingBox().getCenter();
	
	bool bRetVal;	
	bRetVal = gluProject(
		center[0], center[1], center[2],
		&transformSceneD[0][0],
		&transformProjectionD[0][0],
		viewportGL,
		&x, &y, &dZCenterO ) == GL_TRUE;

	//
	vgm::Vec3d	vec3dUpperLeftCornerO;
	vgm::Vec3d	vec3dUpperRightCornerO;
	vgm::Vec3d	vec3dDownLeftCornerO;

	// The gluUnProject function maps window coordinates to object coordinates.
	bRetVal &= gluUnProject(
		viewportGL[0], viewportGL[1] + viewportGL[3], dZCenterO,
		&transformSceneD[0][0],
		&transformProjectionD[0][0],
		viewportGL,
		&x, &y, &z ) == GL_TRUE;
	vec3dUpperLeftCornerO.setValue( x, y , z );

	bRetVal &= gluUnProject(	
		viewportGL[0] + viewportGL[2], viewportGL[1] + viewportGL[3], dZCenterO,
		&transformSceneD[0][0],
		&transformProjectionD[0][0],
		viewportGL,
		&x, &y, &z ) == GL_TRUE;
	vec3dUpperRightCornerO.setValue( x, y, z );

	bRetVal &= 	gluUnProject(	
		viewportGL[0], viewportGL[1], dZCenterO,
		&transformSceneD[0][0],
		&transformProjectionD[0][0],
		viewportGL,
		&x, &y, &z ) == GL_TRUE;
	vec3dDownLeftCornerO.setValue( x, y, z );

	//
	vgm::Vec3d vec3dUpperLeftCornerFarO;
	vgm::Vec3d vec3dUpperLeftCornerNearO;

	bRetVal &= 	gluUnProject(	
		viewportGL[0] + viewportGL[2]/2.f, viewportGL[1] + viewportGL[3]/2.f, 1.f,
		&transformSceneD[0][0],
		&transformProjectionD[0][0],
		viewportGL,
		&x, &y, &z ) == GL_TRUE;
	vec3dUpperLeftCornerFarO.setValue( x, y, z );

	bRetVal &= 	gluUnProject(	
		viewportGL[0] + viewportGL[2]/2.f, viewportGL[1] + viewportGL[3]/2.f, 0.f,	

		&transformSceneD[0][0],
		&transformProjectionD[0][0],
		viewportGL,
		&x, &y, &z ) == GL_TRUE;
	vec3dUpperLeftCornerNearO.setValue( x, y, z );

	// Final computation
	vgm::Vec3d vec3dLeftToRightO;
	vec3dLeftToRightO	= vec3dUpperRightCornerO	-	vec3dUpperLeftCornerO;
	oLeftToRightO.setValue( 
		static_cast<float>(vec3dLeftToRightO[0]),
		static_cast<float>(vec3dLeftToRightO[1]),
		static_cast<float>(vec3dLeftToRightO[2])	);

	vgm::Vec3d vec3dUpToDownO;
	vec3dUpToDownO		= vec3dDownLeftCornerO		-	vec3dUpperLeftCornerO;
	oUpToDownO.setValue(	
		static_cast<float>(vec3dUpToDownO[0]),
		static_cast<float>(vec3dUpToDownO[1]),
		static_cast<float>(vec3dUpToDownO[2]) );

	vgm::Vec3d vec3dNearToFarO;
	vec3dNearToFarO	= vec3dUpperLeftCornerFarO	-	vec3dUpperLeftCornerNearO;
	oNearToFarO.setValue(
		static_cast<float>(vec3dNearToFarO[0]),
		static_cast<float>(vec3dNearToFarO[1]),
		static_cast<float>(vec3dNearToFarO[2]) );
	
	return ( bRetVal );
}



void Dragger::preApply( vgeGL::engine::Engine *pGLEngine, vgd::node::Dragger *pDragger )
{
	// Update internal attribute (to give access to them from EventVisitor methods).
	m_pGLEngine = pGLEngine;
	m_pDragger	= pDragger;

	// Check dragger.listener field
	if ( !m_pDragger->getListener() )
	{
		// nothing to do
		return;
	}

	// Gets event stored in Engine.
	m_pEvent = getEvent( pGLEngine );
	assert( m_pEvent.get() != 0 );

	// Process event
	// Change Dragger.currentState.
	using vgd::field::EditorRO;
	using vgd::node::Dragger;
	
	const vgd::event::ButtonStateSet& bss = m_pEvent->getButtonStates();
	
	EditorRO< Dragger::FBindingsType > editorBindingsRO(
		pDragger->getFieldRO<Dragger::FBindingsType>(pDragger->getFBindings()) );

	// sets founded to true when button states of incoming event is equal to a binding from bindings field.
	bool founded = false;
	
	for (	Dragger::FBindingsType::const_iterator	iBindings		= editorBindingsRO->begin(),
													iEndBindings	= editorBindingsRO->end();
																
			iBindings != iEndBindings;
			++iBindings )
	{
		const Dragger::FBindingsType::value_type& elt = *iBindings;
		
		if ( elt.second == bss )
		{
				// Update current state if and only if its value has changed.
			if ( pDragger->getCurrentState() != elt.first )
			{
				pDragger->setCurrentState( elt.first );
			}
			
			founded = true;
			break;			
		}
	}
	
	if ( !founded )
	{
		if ( pDragger->getCurrentState() != Dragger::IDRAGGER_DEFAULT )
		{
			pDragger->setCurrentState( Dragger::IDRAGGER_DEFAULT );
		}
	}
}



void Dragger::apply()
{
	if ( m_pDragger->getListener() )
	{
		m_pEvent->accept( *this );
	}
	// else nothing to do, because the dragger.listener field is false.
}


	
void Dragger::postApply()
{
	vgd::field::DirtyFlag *pDF = m_pDragger->getDirtyFlag( m_pDragger->getDFNode() );
	assert( pDF != 0 );
	
	if ( pDF->isDirty() )
	{
		vgm::MatrixR matrix = m_pDragger->computeMatrixFromFields();
		m_pDragger->setMatrix( matrix );
		//pDF->validate(); validation is done only during paint().
	}
	//else nothing to do
}



vgd::Shp< vgd::event::Event > Dragger::getEvent( vge::engine::Engine *pEngine )
{
	using vgeGL::technique::ProcessEvent;
	
	assert( pEngine->isField( ProcessEvent::getFProcessEvent() ) );
	
	vgd::field::EditorRO< ProcessEvent::FProcessEventType > eventInEngine =
		pEngine->getFieldRO< ProcessEvent::FProcessEventType >( ProcessEvent::getFProcessEvent() );

	vgd::Shp< vgd::event::Event > event = eventInEngine->getValue();
	
	return event;
}



} // namespace processEvent
	
} // namespace handler

} // namespace vge
