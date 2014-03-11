// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgWX/BasicViewer.hpp"

#include <vgd/node/DirectionalLight.hpp>



namespace vgWX
{



//BEGIN_EVENT_TABLE( BasicViewer, Canvas )
//
//END_EVENT_TABLE()



BasicViewer::BasicViewer(
					wxWindow *parent,
					const wxString& name,
					const wxPoint& pos, const wxSize& size,
					long style,					
					int* gl_attrib,
					const wxWindowID id ) :

	Canvas( parent, name, pos, size, style, gl_attrib, id ),

	m_setup(				vgd::node::Group::create("SETUP") ),
	m_camera(				vgd::node::Camera::create("CAMERA") ),
	m_viewTransform(		vgd::node::MatrixTransform::create("VIEW_TRANSFORM") ),
	m_scene(				vgd::node::Group::create("SCENE") ),
	
	m_cameraType( CAMERA_DEFAULT )
{
	getRoot()->addChild( m_setup );
	getRoot()->addChild( m_scene );
	
	// populate setup.
	m_setup->addChild(	m_camera );
	m_setup->addChild(	m_viewTransform );

	//
	m_camera->setComposeTransformation( false );
	m_viewTransform->setComposeTransformation( false );
}



BasicViewer::BasicViewer(
					wxWindow *parent,
					Canvas *pSharedCanvas,
					const wxString& name,
					const wxPoint& pos, const wxSize& size,
					long style,					
					int* gl_attrib,
					const wxWindowID id ) :

	Canvas( parent, pSharedCanvas, name, pos, size, style, gl_attrib, id ),

	m_setup(				vgd::node::Group::create("SETUP") ),
	m_camera(				vgd::node::Camera::create("CAMERA") ),
	m_viewTransform(		vgd::node::MatrixTransform::create("VIEW_TRANSFORM") ),
	m_scene(				vgd::node::Group::create("SCENE") ),
	
	m_cameraType( CAMERA_DEFAULT )
{
	getRoot()->addChild( m_setup );
	getRoot()->addChild( m_scene );
	
	// populate setup.
	m_setup->addChild(	m_camera );
	m_setup->addChild(	m_viewTransform );

	//
	m_camera->setComposeTransformation( false );
	m_viewTransform->setComposeTransformation( false );
}



void BasicViewer::setCameraType( const CameraType typeOfCamera )
{
	m_cameraType = typeOfCamera;
}



const BasicViewer::CameraType BasicViewer::getCameraType() const
{
	return m_cameraType;
}



void BasicViewer::viewAll( const CameraDistanceHints cameraDistance )
{
	if ( !enableVGSDK() )
	{
		return;
	}

	// Compute bounding box and some informations
	vgm::Box3f	box;
	vgm::Vec3f	center;
	float		max;

	computeSceneBoundingBox( box, center, max );
	
	vgm::MatrixR	matrix;
	
	if ( !box.isEmpty() )
	{	
		// Compute the scene position and orientation.
		const float distanceCoeff = compute( cameraDistance );

		vgm::Vec3f		posCam( center + vgm::Vec3f(0.f, 0.f, (0.5f + 1.f + distanceCoeff) * max) );
	
		matrix.setLookAt(
			posCam[0], posCam[1], posCam[2],
			center[0], center[1], center[2],
			0.f, 1.f, 0.f );
	}
	else
	{
		matrix.setIdentity();
	}
	
	// Compute and setup the camera type and frustum.
	vgm::Vec2i	v2iSize( GetSize().GetWidth(), GetSize().GetHeight() );

	if (	(v2iSize[0] != 0) &&
			(v2iSize[1] != 0)	)
	{
		resize( v2iSize );
	}
	//else viewAll() called before window creation => unable to do completely the job.

	// Setup the scene position.
	m_viewTransform->setMatrix( matrix );
}



vgd::Shp< vgd::node::Group > BasicViewer::getSetup()
{
	return m_setup;
}



vgd::Shp< vgd::node::Camera > BasicViewer::getCamera()
{
	return m_camera;
}



vgd::Shp< vgd::node::MatrixTransform > BasicViewer::getViewTransformation()
{
	return m_viewTransform;
}



vgd::Shp< vgd::node::Group > BasicViewer::getScene()
{
	return m_scene;
}



vgd::Shp< vgd::node::ClearFrameBuffer > BasicViewer::createClearFrameBuffer()
{
	if( !m_clearFrameBuffer )
	{
		m_clearFrameBuffer = vgd::node::ClearFrameBuffer::create("CLEAR");
		getSetup()->addChild( m_clearFrameBuffer );
	}
	return m_clearFrameBuffer;
}



void BasicViewer::destroyClearFrameBuffer()
{
	if( m_clearFrameBuffer )
	{
		getSetup()->removeChild( m_clearFrameBuffer );
		m_clearFrameBuffer.reset();
	}
}



vgd::Shp< vgd::node::ClearFrameBuffer > BasicViewer::getClearFrameBuffer() const
{
	return m_clearFrameBuffer;
}



void BasicViewer::createDefaultLights()
{
	if( !m_lights )
	{
		using vgd::node::DirectionalLight;
		using vgd::node::Group;
		
		// Creates and swithes on the directional lights.
		vgd::Shp< DirectionalLight > light1 = DirectionalLight::create("defaultLight1");
		light1->setOn( true );
		light1->setDirection( vgm::Vec3f(0.f, 0.f, -1.f) );
	
		vgd::Shp< DirectionalLight > light2 = DirectionalLight::create("defaultLight2");
		light2->setMultiAttributeIndex( 1 );
		light2->setOn( true );
		light2->setDirection( vgm::Vec3f(0.f, 0.f, 1.f) );
		
		// Creates the group that will contain the lights.
		m_lights = Group::create("LIGHTS");
		m_lights->addChild( light1 );
		m_lights->addChild( light2 );		
		
		// Inserts the default lights before the scene transform.
		const int32	insertIndex = m_setup->findChild( m_viewTransform );
		getSetup()->insertChild( m_lights, insertIndex );
	}	
}



void BasicViewer::destroyDefaultLights()
{
	if( m_lights )
	{
		// Removes the default lights sub-graph and frees the sub-graph 
		getSetup()->removeChild( m_lights );
		m_lights.reset();
	}
}



void BasicViewer::resize( const vgm::Vec2i size )
{
	if (	(size[0] == 0) || (size[1] == 0)	)
	{
		// Degenerated window, nothing to do
		return;
	}

	// Compute bounding box and some informations
	vgm::Box3f	box;
	vgm::Vec3f	center;
	float		max;

	computeSceneBoundingBox( box, center, max );
	
	// Get additionnal informations.
	float width, height, depth;
	
	if ( !box.isEmpty() )
	{
		box.getSize( width, height, depth );
	}
	else
	{
		width = height = depth = 999.f;

		max = 999.f;
	}

	float	minDepth = max / 2048.f; // r = 2048 in r = far/near.
	float	maxDepth = 12.f * max;

	//
	if ( height == 0.f )
	{
		return;
	}

	const float sceneAspectRatio	= width/height;	
	const float windowAspectRatio	= static_cast<float>(size[0])/static_cast<float>(size[1]);

	vgm::MatrixR matrix;
	
	switch ( getCameraType() )
	{
		case CAMERA_PERSPECTIVE:
			matrix.setPerspective(
							90.f,
							windowAspectRatio,
							minDepth,
							maxDepth
							);
			break;

		case CAMERA_ORTHOGRAPHIC:
		{
			if ( windowAspectRatio < sceneAspectRatio )
			{
				matrix.setOrtho(
								-width / 2.f,
								width / 2.f,
								
								-width / 2.f / windowAspectRatio,
								width / 2.f / windowAspectRatio,
								
								minDepth,
								maxDepth
								);
			}
			else
			{
				matrix.setOrtho(
								-height / 2.f * windowAspectRatio,
								height / 2.f * windowAspectRatio,
								
								-height / 2.f,
								height / 2.f,
								
								minDepth,
								maxDepth
								);
			}
			break;
		}
		
//		{
//			if ( width > height )
//			{
//				matrix.setOrtho(
//								-width / 2.f,
//								width / 2.f,
//								
//								-width / 2.f / windowAspectRatio,
//								width / 2.f / windowAspectRatio,
//								
//								minDepth,
//								maxDepth
//								);
//			}
//			else
//			{
//				matrix.setOrtho(
//								-height / 2.f * windowAspectRatio,
//								height / 2.f * windowAspectRatio,
//								
//								-height / 2.f,
//								height / 2.f,
//								
//								minDepth,
//								maxDepth
//								);
//			}
//
//			break;
//		}

		default:
			assert( false && "Unknwon camera type." );
	}
	
	m_camera->setProjection( matrix );
	
	m_camera->setViewport( vgm::Rectangle2i( 0, 0, size[0], size[1] ) );
}



void BasicViewer::computeBoundingBox(	vge::visitor::NodeCollectorExtended<> *pCollectorExt, 
										vgm::Box3f& box, vgm::Vec3f& center,
										float& max )
{
	// compute/update bounding box for the whole scene graph.
	Canvas::computeBoundingBox( pCollectorExt );

	box		= getScene()->getBoundingBox();

	if ( box.isEmpty() )
	{
		center.setValue( 0.f, 0.f, 0.f );
		max = 0;
	}
	else
	{
		center	= box.getCenter();

		float width, height, depth;
		box.getSize( width, height, depth );
		
		max		= width > height ? width : height;
		max		= max > depth ? max : depth;
	}
}



void BasicViewer::computeSceneBoundingBox(	vgm::Box3f& box, vgm::Vec3f& center, float& max )
{
	vge::visitor::NodeCollectorExtended<> collectorExt;
	getScene()->traverse( collectorExt );
	
	computeBoundingBox(	&collectorExt,
						box, center,
						max );
}



const float BasicViewer::compute( const CameraDistanceHints cameraDistance )
{
	float retVal;
	
	switch( cameraDistance )
	{
		case CLOSE:
			retVal = 0.f;
			break;
			
		case CENTER:
			retVal = 0.25f;
			break;
	
		default:
			retVal = 0.f;
			assert( false && "Unexpected CameraDistanceHints." );
	}
	
	return retVal;
}


		
} // namespace vgWX
