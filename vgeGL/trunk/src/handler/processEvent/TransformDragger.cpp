// VGSDK - Copyright (C) 2004, IRCAD.
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
	// FIXME(begin): should go in Dragger
	using namespace vgd::event;
	using vgd::node::TransformDragger;
		
	assert( dynamic_cast< vgd::node::TransformDragger* >(pNode) != 0 );
	vgd::node::TransformDragger *pDragger = static_cast< vgd::node::TransformDragger* >(pNode);
	
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);
	
	// Gets event stored in Engine.
	vgd::Shp< Event > pEvent = getEvent( pEngine );
	assert( pEvent.get() != 0 );

	// Process event

	// Change Dragger.currentState.
	using vgd::field::EditorRO;
	using vgd::node::Dragger;
	
	const ButtonStateSet& bss = pEvent->getButtonStates();
	
	EditorRO< Dragger::FBindingsType > editorBindingsRO(
		pDragger->template getFieldRO<Dragger::FBindingsType>(pDragger->getFBindings()) );

	for (	Dragger::FBindingsType::const_iterator	iBindings		= editorBindingsRO->begin(),
																iEndBindings	= editorBindingsRO->end();
																
			iBindings != iEndBindings;
			++iBindings )
	{
		const Dragger::FBindingsType::value_type& elt = *iBindings;
		
		if ( elt.second == bss )
		{
			pDragger->setCurrentState( elt.first );
			break;
		}
	}

	// FIXME(end): should go in Dragger	
	

	// LOCATION2
	Location2Event	*location2Event = dynamic_cast<Location2Event*>(pEvent.get());

	if ( location2Event != 0 )
	{
		if ( pDragger->getCurrentState() == TransformDragger::ROTATION_XY_ACTIVE )
		{
			// FIXME: Dragger ComputeRotationXY();
			vgm::Vec2f size = location2Event->getSize();
			
			// COMPUTE NEW ROTATION
			vgm::Vec2f		center = size/2.f;
	
			vgm::Rotation	newRot;
			newRot.setValue(	center,
									location2Event->getPreviousLocation(),
									location2Event->getLocation(),
									location2Event->getSize(), 
									0.8f );
	
			// UPDATE TransformDragger.rotation
			pDragger->setRotation(
				pDragger->getRotation() * newRot );
				
			// This must be automatic (virtual computeMatrixFromFields(), setMatrix() and DF ).FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			// UPDATE TrackballDragger.matrix
			vgm::MatrixR matrix = pDragger->computeMatrixFromFields();
			
			pDragger->setMatrix( matrix );
		}
		else if ( pDragger->getCurrentState() == TransformDragger::TRANSLATION_XY_ACTIVE )
		{
			// FIXME: Dragger ComputeTranslationXY();			
			vgm::Vec3f oLeftToRightO;
			vgm::Vec3f oUpToDownO;
			vgm::Vec3f oNearToFarO;
			
			bool bRetVal = ConvertVectorsFromWindowToObject( pGLEngine, pDragger, oLeftToRightO, oUpToDownO, oNearToFarO );
			
			if ( bRetVal )
			{
				vgd::event::Location2Event::LocationDelta	delta = location2Event->getDelta();
				vgd::event::Location2Event::Size				size	= location2Event->getSize();				
				
				vgm::Vec3f translation;
				
				translation =	(delta[0]/size[0]) * oLeftToRightO;
				translation +=	(delta[1]/size[1]) * -oUpToDownO;
				
				pDragger->setTranslation(
					pDragger->getTranslation() + translation
					);
	
				// This must be automatic (virtual computeMatrixFromFields(), setMatrix() and DF ).FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				// UPDATE TransformDragger.matrix
				vgm::MatrixR matrix = pDragger->computeMatrixFromFields();
				
				pDragger->setMatrix( matrix );
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
			
			bool bRetVal = ConvertVectorsFromWindowToObject( pGLEngine, pDragger, oLeftToRightO, oUpToDownO, oNearToFarO );

			if ( bRetVal )
			{			
				vgd::event::Location2Event::LocationDelta	delta = location2Event->getDelta();
				vgd::event::Location2Event::Size				size	= location2Event->getSize();
				
				vgm::Vec3f translation;
				
				translation = oNearToFarO * delta[1]/size[1] / 4.f;
				
				pDragger->setTranslation( 
					pDragger->getTranslation() + translation
					);

				// This must be automatic (virtual computeMatrixFromFields(), setMatrix() and DF ).FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				// UPDATE TransformDragger.matrix
				vgm::MatrixR matrix = pDragger->computeMatrixFromFields();
				
				pDragger->setMatrix( matrix );
			}
			else
			{
				assert( false && "Internal error" );
			}
		}
		else if ( pDragger->getCurrentState() == TransformDragger::ROTATION_Z_ACTIVE )
		{
			// FIXME: Dragger ComputeRotationZ();
			vgd::event::Location2Event::LocationDelta	delta = location2Event->getDelta();
			vgd::event::Location2Event::Size				size	= location2Event->getSize();
			
			vgm::Vec3f	axis(0.f, 0.f, 1.f );
			float			angle;
			
			angle = vgm::Utilities::deg2rad( delta[0]/size[1] * 90.f );

			pDragger->setRotation(
					pDragger->getRotation() * vgm::Rotation( axis, angle )
				);
				
			// This must be automatic (virtual computeMatrixFromFields(), setMatrix() and DF ).FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			// UPDATE TransformDragger.matrix
			vgm::MatrixR matrix = pDragger->computeMatrixFromFields();
			
			pDragger->setMatrix( matrix );
		}
		//else nothing
	}
	
	// MOUSEWHEEL
	MouseWheelEvent	*mouseWheelEvent = dynamic_cast<MouseWheelEvent*>(pEvent.get());
	
	if ( mouseWheelEvent != 0 )
	{
		if ( mouseWheelEvent->getAxis() == MouseWheelEvent::VERTICAL )
		{
			if ( mouseWheelEvent->getDelta() != 0.f )
			{
				// WHEEL
				vgm::Vec3f oLeftToRightO;
				vgm::Vec3f oUpToDownO;
				vgm::Vec3f oNearToFarO;
				
				bool bRetVal = ConvertVectorsFromWindowToObject( pGLEngine, pDragger, oLeftToRightO, oUpToDownO, oNearToFarO );
		
				if ( bRetVal )
				{			
					vgm::Vec3f translation;
					
					translation = oNearToFarO * static_cast<float>(mouseWheelEvent->getDelta())/120.f / 50.f;
					
					pDragger->setTranslation(
						pDragger->getTranslation() + translation
						);
						
					// This must be automatic (virtual computeMatrixFromFields(), setMatrix() and DF ).FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					// UPDATE TransformDragger.matrix
					vgm::MatrixR matrix = pDragger->computeMatrixFromFields();
					
					pDragger->setMatrix( matrix );
				}
				else
				{
					assert( false && "Internal error" );
				}
			}
		}
	}

	pDragger->getDirtyFlag( pDragger->getDFNode() )->validate();
}



void TransformDragger::unapply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
}



void TransformDragger::setToDefaults()
{
}



} // namespace processEvent
	
} // namespace handler

} // namespace vge
