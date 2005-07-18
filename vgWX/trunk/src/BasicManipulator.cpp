// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgWX/BasicManipulator.hpp"

#include <vgd/visitor/predicate/ByDirtyFlag.hpp>
#include <vgm/Utilities.hpp>
#include <vgDebug/Global.hpp>



namespace vgWX
{



BEGIN_EVENT_TABLE( BasicManipulator, Canvas )

//   EVT_MOUSE_EVENTS			( BasicManipulator::OnMouseEvent	)
	EVT_CHAR    				( BasicManipulator::OnChar			)

END_EVENT_TABLE()



BasicManipulator::BasicManipulator(
					wxWindow *parent,
					const wxString& name,
					const wxPoint& pos, const wxSize& size,
					long style,					
					int* gl_attrib,
					const wxWindowID id ) :

	BasicViewer( parent, name, pos, size, style, gl_attrib, id ),
	
	m_sceneTransform(	vgd::node::TransformDragger::create("TRANSFORMDRAGGER_SCENE") )
	
	//m_previousMouseCoord
{
	// init scene dragger.
	m_sceneTransform->setSurround( getScene() );
		
	getSetup()->addChild( m_sceneTransform );
	
	// Install event handler and event listener.
	PushEventHandler( &m_keyboard );
	PushEventHandler( &m_mouse );
	
	m_keyboard.attachEventListener( this );
	m_mouse.attachEventListener( this );
}



BasicManipulator::BasicManipulator(
					wxWindow *parent,
					Canvas *pSharedCanvas,
					const wxString& name,
					const wxPoint& pos, const wxSize& size,
					long style,					
					int* gl_attrib,
					const wxWindowID id ) :

	BasicViewer( parent, pSharedCanvas, name, pos, size, style, gl_attrib, id ),
	
	m_sceneTransform(	vgd::node::TransformDragger::create("TRANSFORMDRAGGER_SCENE") )
	
	//m_previousMouseCoord
{
	// init scene dragger.
	m_sceneTransform->setSurround( getScene() );
		
	getSetup()->addChild( m_sceneTransform );
	
	// Install event handler and event listener.
	PushEventHandler( &m_keyboard );
	PushEventHandler( &m_mouse );
	
	m_keyboard.attachEventListener( this );
	m_mouse.attachEventListener( this );
}



BasicManipulator::~BasicManipulator()
{
	// Deinstall event handler and event listener.
	m_keyboard.detachEventListener( this );
	m_mouse.detachEventListener( this );

	PopEventHandler();
	PopEventHandler();
}



vgd::Shp< vgd::node::TransformDragger > BasicManipulator::getSceneTransformation()
{
	return ( m_sceneTransform );
}



void BasicManipulator::viewAll()
{
	// Reset scene transformation.
	getSceneTransformation()->setTransformationToDefaults();

	//
	BasicViewer::viewAll();
	
	// Sets the center of scene transformation.
	vgm::Vec3f center;
	center = getScene()->getBoundingBox().getCenter();
	
	getSceneTransformation()->setCenter( center );
}



void BasicManipulator::onEvent( vgd::Shp<vgd::event::Event> event )
{
	if ( !enableVGSDK() )
	{
		return;
	}

	BasicViewer::onEvent( event );
	
	//Refresh(); ????????????????????????
	
	// must schedule a refresh of the window ?
	std::pair< bool, vgd::Shp< vgd::node::Node > > retVal;

	retVal = vgd::visitor::findFirst(	getRoot(),
													vgd::visitor::predicate::ByDirtyFlag() );

	if ( retVal.first )
	{
		vgDebug::get().logDebug("%s\n", retVal.second->getName().c_str() );
		Refresh();
	}
}



void BasicManipulator::OnChar( wxKeyEvent& event )
{
	// VIEW ALL
	if ( event.KeyCode() == 'v' )
	{
		viewAll();
	
		// Refresh view.
		Refresh();
	}
	else if (	(event.KeyCode() == 'b') ||
					(event.KeyCode() == 'B')
				)
	{
		if ( event.KeyCode() == 'b' )
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
