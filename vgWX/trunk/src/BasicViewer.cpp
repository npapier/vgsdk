// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgWX/BasicViewer.hpp"



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
	return ( m_cameraType );
}



void BasicViewer::viewAll()
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
		vgm::Vec3f		posCam( center + vgm::Vec3f(0.f, 0.f, (0.5f + 1.25f) * max) );						// viewAll( NEAR ); FIXME
	
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
	
	// compute/update bounding box for the whole scene graph.
	Canvas::computeBoundingBox( 0 );
}



vgd::Shp< vgd::node::Group > BasicViewer::getSetup()
{
	return ( m_setup );
}



vgd::Shp< vgd::node::Camera > BasicViewer::getCamera()
{
	return ( m_camera );
}



vgd::Shp< vgd::node::MatrixTransform > BasicViewer::getViewTransformation()
{
	return ( m_viewTransform );
}



vgd::Shp< vgd::node::Group > BasicViewer::getScene()
{
	return ( m_scene );
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
	
	vgm::MatrixR matrix;	

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
	switch ( getCameraType() )
	{
		case CAMERA_PERSPECTIVE:
			matrix.setPerspective(
							45.f,
							static_cast<float>(size[0])/static_cast<float>(size[1]),
							minDepth,
							maxDepth
							);
			break;

		case CAMERA_ORTHOGRAPHIC:
			matrix.setOrtho(
							-width / 2.f,
							width / 2.f,
							
							-height / 2.f,
							height / 2.f,
							
							minDepth,
							maxDepth
							);
			break;

		default:
			assert( false && "Unknwon camera type." );
	}
	
	m_camera->setMatrix( matrix );
	
	m_camera->setViewport(
		vgm::Rectangle2i( 0, 0, size[0], size[1] )
		);
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



} // namespace vgWX
