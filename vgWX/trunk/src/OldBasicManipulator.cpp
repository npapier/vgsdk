// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgWX/OldBasicManipulator.hpp"

#include <vgd/visitor/predicate/ByDirtyFlag.hpp>
#include <vgm/Utilities.hpp>
#include <vgDebug/Global.hpp>



namespace vgWX
{



BEGIN_EVENT_TABLE( OldBasicManipulator, Canvas )

   EVT_MOUSE_EVENTS			( OldBasicManipulator::OnMouseEvent	)
	EVT_CHAR    				( OldBasicManipulator::OnChar			)

END_EVENT_TABLE()



OldBasicManipulator::OldBasicManipulator(
					wxWindow *parent,
					const wxString& name,
					const wxPoint& pos, const wxSize& size,
					long style,					
					int* gl_attrib,
					const wxWindowID id ) :

	BasicViewer( parent, name, pos, size, style, gl_attrib, id ),
	
	m_sceneTransform(	vgd::node::Transform::create("SCENE_TRANSFORM") )
	
	//m_previousMouseCoord
{
	getSetup()->addChild( m_sceneTransform );
	
//	// Install event handler and event listener.
//	PushEventHandler( &m_keyboard );
//	PushEventHandler( &m_mouse );
//	
//	m_keyboard.attachEventListener( this );
//	m_mouse.attachEventListener( this );
}



OldBasicManipulator::~OldBasicManipulator()
{
//	// Deinstall event handler and event listener.
//	m_keyboard.detachEventListener( this );
//	m_mouse.detachEventListener( this );
//
//	PopEventHandler();
//	PopEventHandler();
}



vgd::Shp< vgd::node::Transform > OldBasicManipulator::getSceneTransformation()
{
	return ( m_sceneTransform );
}



void OldBasicManipulator::viewAll()
{
	// Reset scene transformation.
	getSceneTransformation()->setToDefaults();

	//
	BasicViewer::viewAll();
	
	// Sets the center of scene transformation.
	vgm::Vec3f center;
	center = getScene()->getBoundingBox().getCenter();
	
	getSceneTransformation()->setCenter( center );
}



void OldBasicManipulator::onEvent( vgd::Shp<vgd::event::Event> event )
{
	BasicViewer::onEvent( event );
	
	//Refresh(); ????????????????????????
	
//	// must schedule a refresh of the window ?
//	std::pair< bool, vgd::Shp< vgd::node::Node > > retVal;
//
//	retVal = vgd::visitor::findFirst(	getRoot(),
//													vgd::visitor::predicate::ByDirtyFlag() );
//
//	if ( retVal.first )
//	{
//		vgDebug::get().logDebug("%s\n", retVal.second->getName().c_str() );
//		Refresh();
//	}
}



void OldBasicManipulator::OnMouseEvent(wxMouseEvent& event)
{
	const float fStepTranslationZ = 50.f;
	
	// STEP 1: window size.

	vgm::Vec2i	v2iSize( GetSize().GetWidth(), GetSize().GetHeight() );
	
	vgm::Vec2f	v2fSize(
		static_cast<float>(v2iSize[0]),
		static_cast<float>(v2iSize[1])
			);
	
	// STEP 2 : mouse coordinates

	// The first time, mouse position must be initialized.
	if ( event.Entering() )
	{
		m_previousMouseCoord.setValue(
			static_cast<float>(event.GetX()),
			static_cast<float>(v2iSize[1] - event.GetY())
			);
			
		return;
	}

	if ( event.Leaving() )
	{
		return;
	}
	
	vgm::Vec2f	deltaMouse;
	float			wheelRotation;

	vgm::Vec2f	currentMouseCoord(
			static_cast<float>(event.GetX()),
			static_cast<float>(v2iSize[1] - event.GetY())
			);

	deltaMouse = currentMouseCoord - m_previousMouseCoord;

	wheelRotation = static_cast< float >( event.GetWheelRotation() );
	
	// STEP 3 : move scene
	if ( event.LeftIsDown() )
	{
		if ( !event.ControlDown() && !event.ShiftDown() )
		{
			// ROTATION
			vgm::Vec2f	center;
			center	= v2fSize/2.f;

			vgm::Rotation rot;
			
			rot.setValue( center,
				m_previousMouseCoord, currentMouseCoord,
				v2fSize,
				0.8f );

			getSceneTransformation()->setRotation( 
					getSceneTransformation()->getRotation() * rot
				);

			Refresh();
		}
		else if ( event.ControlDown() && !event.ShiftDown() )
		{
			// TRANSLATION
			vgm::Vec3f oLeftToRightO;
			vgm::Vec3f oUpToDownO;
			vgm::Vec3f oNearToFarO;
			
			bool bRetVal;
			bRetVal = ConvertVectorsFromWindowToObject( oLeftToRightO, oUpToDownO, oNearToFarO );
			
			if ( bRetVal )
			{
				vgm::Vec3f translation;
				
				translation =	(deltaMouse[0]/v2fSize[0]) * oLeftToRightO;
				translation +=	(deltaMouse[1]/v2fSize[1]) * -oUpToDownO;
				
				getSceneTransformation()->setTranslation(
					getSceneTransformation()->getTranslation() + translation
					);
					
				Refresh();
			}
			else
			{
				// assert( false && "ConvertVectorsFromWindowToObject() returns false" );
			}
		}
		else if ( !event.ControlDown() && event.ShiftDown() )
		{
			// TRANSLATION Z
			vgm::Vec3f oLeftToRightO;
			vgm::Vec3f oUpToDownO;
			vgm::Vec3f oNearToFarO;
			
			bool bRetVal;
			bRetVal = ConvertVectorsFromWindowToObject( oLeftToRightO, oUpToDownO, oNearToFarO );

			if ( bRetVal )
			{			
				vgm::Vec3f translation;
				
				translation = oNearToFarO * deltaMouse[1]/v2fSize[1] / 4.f;
				
				getSceneTransformation()->setTranslation(
					getSceneTransformation()->getTranslation() + translation
					);
					
				Refresh();					
			}
			else
			{
				//assert( false && "ConvertVectorsFromWindowToObject() returns false" );
			}					
		}
		else if ( event.ControlDown() && event.ShiftDown() )
		{
			// ROTATION Z
			vgm::Vec3f	axis(0.f, 0.f, 1.f );
			float			angle;
			angle = vgm::Utilities::deg2rad( deltaMouse[0]/v2fSize[1] * 90.f );

			getSceneTransformation()->setRotation(
					getSceneTransformation()->getRotation() * vgm::Rotation( axis, angle )
				);

			Refresh();				
		}
	}
	
	if ( wheelRotation != 0.f )
	{
		// WHEEL
		vgm::Vec3f oLeftToRightO;
		vgm::Vec3f oUpToDownO;
		vgm::Vec3f oNearToFarO;
		
		bool bRetVal;
		bRetVal = ConvertVectorsFromWindowToObject( oLeftToRightO, oUpToDownO, oNearToFarO );

		if ( bRetVal )
		{			
			vgm::Vec3f translation;
			
			translation = oNearToFarO * wheelRotation/120.f / fStepTranslationZ;
			
			getSceneTransformation()->setTranslation(
				getSceneTransformation()->getTranslation() + translation
				);

			Refresh();
		}
		else
		{
			//assert( false && "ConvertVectorsFromWindowToObject() returns false" );
		}
	}
		
	// Store current mouse position.
	m_previousMouseCoord.setValue(
		static_cast<float>(event.GetX()),
			static_cast<float>(v2iSize[1] - event.GetY())
		);
		
	event.Skip();
}



void OldBasicManipulator::OnChar( wxKeyEvent& event )
{
	float			fAngle				= 1.0f;
	const float	fStepTranslation	= 50.f;
	const float	fStepTranslationZ	= 50.f;
	
	// Navigation keys.
	vgm::Vec2f	v2fDelta( 0.f, 0.f );
	
	if ( event.KeyCode() == WXK_LEFT )
	{
		v2fDelta += vgm::Vec2f( -1.f, 0.f );
	}
	
	if ( event.KeyCode() == WXK_RIGHT )
	{
		v2fDelta += vgm::Vec2f( 1.f, 0.f );
	}
	
	if ( event.KeyCode() == WXK_UP )
	{
		v2fDelta += vgm::Vec2f( 0.f, 1.f );
	}
	
	if ( event.KeyCode() == WXK_DOWN )
	{
		v2fDelta += vgm::Vec2f( 0.f, -1.f );
	}
	
	// VIEW ALL
	if ( event.KeyCode() == 'v' )
	{
		viewAll();
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
		Refresh();
	}
	// MANIPULATION MODE
	else if ( !event.ControlDown() && !event.ShiftDown() )
	{
		// ROTATION
		getSceneTransformation()->setRotation( 
				getSceneTransformation()->getRotation() * 
				vgm::Rotation( vgm::Vec3f(0.f, 1.f, 0.f), vgm::Utilities::deg2rad(fAngle*v2fDelta[0]) )
			);
	
		getSceneTransformation()->setRotation( 
					getSceneTransformation()->getRotation() * 
					vgm::Rotation( vgm::Vec3f(1.f, 0.f, 0.f), vgm::Utilities::deg2rad(-fAngle*v2fDelta[1]) )
				);
	}
	else if ( event.ControlDown() && !event.ShiftDown() )
	{
		// TRANSLATION
		vgm::Vec3f oLeftToRightO;
		vgm::Vec3f oUpToDownO;
		vgm::Vec3f oNearToFarO;
		
		bool bRetVal;
		bRetVal = ConvertVectorsFromWindowToObject( oLeftToRightO, oUpToDownO, oNearToFarO );

		if ( bRetVal )
		{			
			vgm::Vec3f translation;
			
			translation =	(v2fDelta[0]/fStepTranslation) * oLeftToRightO;
			translation +=	(v2fDelta[1]/fStepTranslation) * -oUpToDownO;
			
			getSceneTransformation()->setTranslation(
				getSceneTransformation()->getTranslation() + translation
				);
		}
		else
		{
			// assert( false && "ConvertVectorsFromWindowToObject() returns false" );
		}
	}
	else if ( !event.ControlDown() && event.ShiftDown() )
	{
		// TRANSLATION Z
		vgm::Vec3f oLeftToRightO;
		vgm::Vec3f oUpToDownO;
		vgm::Vec3f oNearToFarO;
				
		bool bRetVal;
		bRetVal = ConvertVectorsFromWindowToObject( oLeftToRightO, oUpToDownO, oNearToFarO );
		if ( bRetVal )
		{			
			vgm::Vec3f translation;
					
			translation = (v2fDelta[1]/fStepTranslationZ) * oNearToFarO;
					
			getSceneTransformation()->setTranslation(
				getSceneTransformation()->getTranslation() + translation
				);
		}
		else
		{
			// assert( false && "ConvertVectorsFromWindowToObject() returns false" );
		}					
	}
	else if ( event.ControlDown() && event.ShiftDown() )
	{
		// ROTATION Z
		vgm::Vec3f	axis(0.f, 0.f, 1.f );
		float			angle;
		angle = vgm::Utilities::deg2rad( v2fDelta[0]/fStepTranslation * 90.f );
	
		getSceneTransformation()->setRotation(
				getSceneTransformation()->getRotation() * vgm::Rotation( axis, angle )
			);
	}

	event.Skip();
	
	// Refresh view.
	Refresh();
}



const bool OldBasicManipulator::ConvertVectorsFromWindowToObject(	vgm::Vec3f& oLeftToRightO,
																					vgm::Vec3f& oUpToDownO,
																					vgm::Vec3f& oNearToFarO )
{
	// MODELVIEW : Gets scene transformation.
	vgm::MatrixR	matrixTransformScene = getScene()->getXfBoundingBox().getTransform();
	
	vgm::RawMatrixd	transformSceneD;
	matrixTransformScene.getValue( transformSceneD );

	// PROJECTION :
	// FIXME work only for simple scene graph (1 camera node).
	vgm::MatrixR	matrixProjectionScene = getCamera()->getMatrix();
	
	vgm::RawMatrixd	transformProjectionD;
	matrixProjectionScene.getValue( transformProjectionD );

	// VIEWPORT
	vgm::Rectangle2i viewport;
	bool bRetVal;
	bRetVal = getCamera()->getViewport( viewport );

	GLint viewportGL[4];
	viewportGL[0] = viewport.x();	
	viewportGL[1] = viewport.y();
	viewportGL[2] = viewport.width();
	viewportGL[3] = viewport.height();
	
	// Compute convertion.

	//
	GLdouble x, y, z;
	GLdouble dZCenterO;
	
	// gluProject function maps object coordinates to window coordinates.
	vgm::Vec3f center;
	center = getScene()->getBoundingBox().getCenter();
	
	bRetVal &= gluProject(
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
	oLeftToRightO.setValue( vec3dLeftToRightO[0], vec3dLeftToRightO[1], vec3dLeftToRightO[2] );

	vgm::Vec3d vec3dUpToDownO;
	vec3dUpToDownO		= vec3dDownLeftCornerO		-	vec3dUpperLeftCornerO;
	oUpToDownO.setValue(	vec3dUpToDownO[0], vec3dUpToDownO[1], vec3dUpToDownO[2] );

	vgm::Vec3d vec3dNearToFarO;
	vec3dNearToFarO	= vec3dUpperLeftCornerFarO	-	vec3dUpperLeftCornerNearO;
	oNearToFarO.setValue( vec3dNearToFarO[0], vec3dNearToFarO[1], vec3dNearToFarO[2] );
	
	return ( bRetVal );
}



} // namespace vgWX
