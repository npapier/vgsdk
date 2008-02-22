// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/processEvent/TransformDragger.hpp"

#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgd/event/Location2Event.hpp>
#include <vgd/event/MouseButtonEvent.hpp>
#include <vgd/event/MouseWheelEvent.hpp>
#include <vgd/node/TransformDragger.hpp>
#include <vge/rc/ButtonStateSet.hpp>
#include <vgm/Utilities.hpp>

#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/technique/ProcessEvent.hpp"



namespace vgeGL
{

namespace handler
{

namespace processEvent
{



META_HANDLER_CPP( TransformDragger );



const vge::handler::Handler::TargetVector TransformDragger::getTargets() const
{
	TargetVector targets;
	
	targets.push_back( vgd::node::TransformDragger::getClassIndexStatic() );
	
	return ( targets );
}



void TransformDragger::apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	using vgd::node::TransformDragger;
		
	assert( dynamic_cast< TransformDragger* >(pNode) != 0 );
	TransformDragger *pDragger = static_cast< TransformDragger* >(pNode);
	
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	//
	Dragger::preApply( pGLEngine, pDragger );
	Dragger::apply();
	Dragger::postApply();
}



void TransformDragger::unapply( vge::engine::Engine *, vgd::node::Node * )
{
}



void TransformDragger::setToDefaults()
{
}



void TransformDragger::apply( const vgd::event::Location2Event *pLocation2Event )
{
	using vgd::node::TransformDragger;
		
	assert( dynamic_cast< TransformDragger* >(m_pDragger) != 0 );
	TransformDragger *pDragger = static_cast< TransformDragger* >(m_pDragger);
		
	if ( pDragger->getCurrentState() == TransformDragger::ROTATION_XY_ACTIVE )
	{
		// FIXME: Dragger computeRotationXY();

		// COMPUTE NEW ROTATION IN WORLD SPACE
		vgm::Vec2f		size		= pLocation2Event->getSize();
		vgm::Vec2f		center	= size/2.f;

		vgm::Rotation	newRotW;
		newRotW.setValue(	center,
							pLocation2Event->getPreviousLocation(),
							pLocation2Event->getLocation(),
							size,
							0.8f );

		// UPDATE THE ROTATION TO BEEING IN OBJECT SPACE
		vgm::MatrixR&	currentGeometrical( m_pGLEngine->getGeometricalMatrix().getTop() );
		vgm::MatrixR	invertedCurrentGeometrical(currentGeometrical);
		invertedCurrentGeometrical.inverse();
		
		vgm::Vec3f	axis;
		float		radians;
		newRotW.getValue( axis, radians );

		invertedCurrentGeometrical.multDirMatrix( axis, axis );
					
		vgm::Rotation newRotO;
		newRotO.setValue( axis, radians );

		// UPDATE TransformDragger.rotation
		pDragger->setRotation(
			pDragger->getRotation() * newRotO );
	}
	else if ( pDragger->getCurrentState() == TransformDragger::TRANSLATION_XY_ACTIVE )
	{
		// FIXME: Dragger ComputeTranslationXY();			
		vgm::Vec3f oLeftToRightO;
		vgm::Vec3f oUpToDownO;
		vgm::Vec3f oNearToFarO;
		
		bool bRetVal = ConvertVectorsFromWindowToObject( m_pGLEngine, pDragger, oLeftToRightO, oUpToDownO, oNearToFarO );
		
		if ( bRetVal )
		{
			vgd::event::Location2Event::LocationDelta	delta = pLocation2Event->getDelta();
			vgd::event::Location2Event::Size			size	= pLocation2Event->getSize();				
			
			vgm::Vec3f translation;
			
			translation =	(delta[0]/size[0]) * oLeftToRightO;
			translation +=	(delta[1]/size[1]) * -oUpToDownO;
			
			pDragger->setTranslation( pDragger->getTranslation() + translation );
		}
		else
		{
			assert( false && "Internal error" );
		}
	}
	else if ( pDragger->getCurrentState() == TransformDragger::TRANSLATION_Z_ACTIVE )
	{
		// FIXME: Dragger ComputeTranslationZ();
		vgm::Vec3f oLeftToRightO;
		vgm::Vec3f oUpToDownO;
		vgm::Vec3f oNearToFarO;
		
		bool bRetVal = ConvertVectorsFromWindowToObject( m_pGLEngine, pDragger, oLeftToRightO, oUpToDownO, oNearToFarO );

		if ( bRetVal )
		{			
			vgd::event::Location2Event::LocationDelta	delta = pLocation2Event->getDelta();
			vgd::event::Location2Event::Size			size	= pLocation2Event->getSize();
			
			vgm::Vec3f translation;
			
			translation = oNearToFarO * delta[1]/size[1] / 4.f;
			
			pDragger->setTranslation( pDragger->getTranslation() + translation );
		}
		else
		{
			assert( false && "Internal error" );
		}
	}
	else if ( pDragger->getCurrentState() == TransformDragger::ROTATION_Z_ACTIVE )
	{
		// FIXME: Dragger ComputeRotationZ();
		vgd::event::Location2Event::LocationDelta	delta = pLocation2Event->getDelta();
		vgd::event::Location2Event::Size			size	= pLocation2Event->getSize();
		
		// COMPUTE NEW ROTATION IN WORLD SPACE			
		vgm::Vec3f	axis(0.f, 0.f, 1.f );
		float		angle;
		
		angle = vgm::Utilities::deg2rad( delta[0]/size[1] * 90.f );
		
		// UPDATE THE ROTATION TO BEEING IN OBJECT SPACE
		vgm::MatrixR&	currentGeometrical( m_pGLEngine->getGeometricalMatrix().getTop() );
		vgm::MatrixR	invertedCurrentGeometrical(currentGeometrical);
		invertedCurrentGeometrical.inverse();

		invertedCurrentGeometrical.multDirMatrix( axis, axis );
		
		//
		pDragger->setRotation( pDragger->getRotation() * vgm::Rotation( axis, angle ) );
	}
	//else nothing
}



void TransformDragger::apply( const vgd::event::MouseWheelEvent *pMouseWheelEvent )
{
	using vgd::event::MouseWheelEvent;
	using vgd::node::TransformDragger;
		
	assert( dynamic_cast< TransformDragger* >(m_pDragger) != 0 );
	TransformDragger *pDragger = static_cast< TransformDragger* >(m_pDragger);
	
	//	
	if ( pMouseWheelEvent->getAxis() == MouseWheelEvent::VERTICAL )
	{
		if ( pMouseWheelEvent->getDelta() != 0.f )
		{
			// WHEEL
			vgm::Vec3f oLeftToRightO;
			vgm::Vec3f oUpToDownO;
			vgm::Vec3f oNearToFarO;
			
			bool bRetVal = ConvertVectorsFromWindowToObject( m_pGLEngine, pDragger, oLeftToRightO, oUpToDownO, oNearToFarO );
	
			if ( bRetVal )
			{			
				vgm::Vec3f translation;
				
				translation = oNearToFarO * static_cast<float>(pMouseWheelEvent->getDelta())/120.f / 50.f;
				
				pDragger->setTranslation( pDragger->getTranslation() + translation );
			}
			else
			{
				assert( false && "Internal error" );
			}
		}
	}
}



} // namespace processEvent
	
} // namespace handler

} // namespace vge
