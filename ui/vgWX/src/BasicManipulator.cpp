// VGSDK - Copyright (C) 2004, 2006, 2007, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgWX/BasicManipulator.hpp"

#include <vgm/Utilities.hpp>
#include <vgDebug/Global.hpp>

#include "vgWX/event/device/Keyboard.hpp"
#include "vgWX/event/device/Mouse.hpp"



namespace vgWX
{



BEGIN_EVENT_TABLE( BasicManipulator, Canvas )
	EVT_CHAR( BasicManipulator::OnChar )
END_EVENT_TABLE()



BasicManipulator::BasicManipulator(
					wxWindow *parent,
					const wxString& name,
					const wxPoint& pos, const wxSize& size,
					long style,					
					int* gl_attrib,
					const wxWindowID id )
:	BasicViewer( parent, name, pos, size, style, gl_attrib, id ),
	
	m_keyboard		( new vgWX::event::device::Keyboard() ),
	m_mouse			( new vgWX::event::device::Mouse() ),
	
	m_sceneTransform( vgd::node::TransformDragger::create("TRANSFORMDRAGGER_SCENE") )
	
	//m_previousMouseCoord
{
	// Initializes the default lights and frame buffer clearing
	createDefaultLights();
 	createClearFrameBuffer();
	
	// init scene dragger.
	m_sceneTransform->setSurround( getScene() );
		
	getSetup()->addChild( m_sceneTransform );
	
	// Install event handler and event listener.
	PushEventHandler( m_keyboard.get() );
	PushEventHandler( m_mouse.get() );

	addDevice( m_keyboard );
	addDevice( m_mouse );
}



BasicManipulator::BasicManipulator(
					wxWindow *parent,
					Canvas *pSharedCanvas,
					const wxString& name,
					const wxPoint& pos, const wxSize& size,
					long style,					
					int* gl_attrib,
					const wxWindowID id )
:	BasicViewer( parent, pSharedCanvas, name, pos, size, style, gl_attrib, id ),
	
	m_keyboard		( new vgWX::event::device::Keyboard() ),
	m_mouse			( new vgWX::event::device::Mouse() ),
	
	m_sceneTransform(	vgd::node::TransformDragger::create("TRANSFORMDRAGGER_SCENE") )
	
	//m_previousMouseCoord
{
	// Initializes the default lights and frame buffer clearing
	createDefaultLights();
 	createClearFrameBuffer();
	
	// init scene dragger.
	m_sceneTransform->setSurround( getScene() );
		
	getSetup()->addChild( m_sceneTransform );
	
	// Install event handler and event listener.
	PushEventHandler( m_keyboard.get() );
	PushEventHandler( m_mouse.get() );

	addDevice( m_keyboard );
	addDevice( m_mouse );
}



BasicManipulator::~BasicManipulator()
{
	// Deinstall event handlers.
	PopEventHandler();
	PopEventHandler();
	
	removeDevice( m_mouse );
	removeDevice( m_keyboard );
}



vgd::Shp< vgd::node::TransformDragger > BasicManipulator::getSceneTransformation()
{
	return m_sceneTransform;
}



void BasicManipulator::viewAll( const CameraDistanceHints cameraDistance )
{
	// Reset scene transformation.
	getSceneTransformation()->setTransformationToDefaults();

	//
	BasicViewer::viewAll( cameraDistance );
	
	// Sets the center of scene transformation.
	if ( getScene()->isBoundingBoxValid() )
	{
		vgm::Vec3f center( getScene()->getBoundingBox().getCenter() );
		getSceneTransformation()->setCenter( center );
	}
	//else nothing to do
	
	// compute/update bounding box for the whole scene graph.
	Canvas::computeBoundingBox( 0 );

	// FIXME must be automatic
	vgm::MatrixR matrix = getSceneTransformation()->computeMatrixFromFields();
	getSceneTransformation()->setMatrix( matrix );
}



void BasicManipulator::onEvent( vgd::Shp<vgd::event::Event> event )
{
	if ( !enableVGSDK() )
	{
		return;
	}

	BasicViewer::onEvent( event );

	refresh( REFRESH_IF_NEEDED, ASYNCHRONOUS );
}



void BasicManipulator::OnChar( wxKeyEvent& event )
{
	if (	(event.GetKeyCode() == 'b') ||
			(event.GetKeyCode() == 'B')	)
	{
		if ( event.GetKeyCode() == 'b' )
		{
			bench(20);
		}
		else
		{
			bench(100);
		}
		
		// Refresh view.
		Refresh();
	}

	event.Skip();
}



} // namespace vgWX
