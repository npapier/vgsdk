// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgUI/BasicManipulator.hpp"

#include <vgm/Utilities.hpp>
#include <vgd/event/device/Mouse.hpp>
#include <vgd/event/device/Timer.hpp>
#include <vgd/event/MouseWheelEvent.hpp>




namespace vgUI
{



BasicManipulator::BasicManipulator()
:	m_sceneTransform( vgd::node::TransformDragger::create("TRANSFORMDRAGGER_SCENE") )
{
	// init scene dragger.
	m_sceneTransform->setSurround( getScene() );

	getSetup()->addChild( m_sceneTransform );
}



BasicManipulator::BasicManipulator( const vgUI::Canvas * pSharedCanvas )
:	BasicViewer( pSharedCanvas ),
	m_sceneTransform( vgd::node::TransformDragger::create("TRANSFORMDRAGGER_SCENE") )
{
	// init scene dragger.
	m_sceneTransform->setSurround( getScene() );

	getSetup()->addChild( m_sceneTransform );
}



void BasicManipulator::setScene( const vgd::Shp< vgd::node::Group > scene )
{
	BasicViewer::setScene( scene );

	// Set surround field of Dragger
	m_sceneTransform->setSurround( getScene() );
}


vgd::Shp< vgd::node::TransformDragger > BasicManipulator::getSceneTransformation()
{
	return m_sceneTransform;
}



void BasicManipulator::viewAll( const CameraDistanceHints cameraDistance )
{
	// Reset scene transformation.
	getSceneTransformation()->setTransformationToDefaults();

	// FIXME must be automatic
	vgm::MatrixR matrix = getSceneTransformation()->computeMatrixFromFields();
	getSceneTransformation()->setMatrix( matrix );

	//
	BasicViewer::viewAll( cameraDistance );

	// Sets the center of scene transformation.
	const vgm::Box3f& boxOfScene = getScene()->getBoundingBox();

	if ( !boxOfScene.isEmpty() )
	{
		const vgm::Vec3f center( boxOfScene.getCenter() );
		getSceneTransformation()->setCenter( center );
	}
	//else nothing to do

	// Computes/updates bounding box for the whole scene graph.
	Canvas::computeBoundingBox();
}



void BasicManipulator::onEvent( vgd::Shp<vgd::event::Event> event )
{
	if ( !startVGSDK() )
	{
		return;
	}

	BasicViewer::onEvent( event );

	// Applied refresh policy stored in event
	if ( event->isScheduleRefreshForced() )
	{
		refreshForced( SYNCHRONOUS );
	}
	/*else
	{
		refreshIfNeeded( ASYNCHRONOUS );
	}*/
}



} // namespace vgUI

