// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgUI/BasicViewer.hpp"

#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgd/node/DirectionalLight.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/visitor/FindFirst.hpp>
#include <vgd/visitor/predicate/ByName.hpp>
#include <vgm/operations.hpp>



namespace vgUI
{



BasicViewer::BasicViewer() :

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



BasicViewer::BasicViewer( Canvas * sharedCanvas ) :

	Canvas( sharedCanvas ),

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
	if ( !startVGSDK() )
	{
		return;
	}

	// Initializes VIEWTRANSFORM
	m_viewTransform->setMatrix( vgm::MatrixR::getIdentity() );

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

		const vgm::Vec3f		posCam( center + vgm::Vec3f(0.f, 0.f, (0.5f + 1.f + distanceCoeff) * max) );

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
	const vgm::Vec2i v2iSize = getEngine()->getDrawingSurfaceSize();

	resize( v2iSize );

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



const vgd::Shp< vgd::node::Group > BasicViewer::getScene() const
{
	return m_scene;
}



vgd::Shp< vgd::node::Node > BasicViewer::createOptionalNode( const OptionalNodeType type )
{
	// Retrieves any existing node of the given type.
	vgd::Shp< vgd::node::Node > existingNode = getOptionalNode( type );
	
	
	// If no node for the given type exists, then we will create one.
	if( ! existingNode )
	{
		switch( type )
		{
		case CLEAR_FRAME_BUFFER:
			existingNode = vgd::node::ClearFrameBuffer::create("CLEAR");
			getSetup()->addChild( existingNode );
			break;
			
		case LIGHTS:
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
				vgd::Shp< Group > lights = Group::create("LIGHTS");
				lights->addChild( light1 );
				lights->addChild( light2 );
	
				// Inserts the default lights before the scene transform.
				const int32	insertIndex = m_setup->findChild( m_viewTransform );
				getSetup()->insertChild( lights, insertIndex );
				
				existingNode = lights;
			}
			break;
	
		case DRAW_STYLE:
			existingNode = vgd::node::DrawStyle::create("DRAW_STYLE");
			getSetup()->addChild( existingNode );
			break;
	
		case LIGHT_MODEL:
			existingNode = vgd::node::LightModel::create("LIGHT_MODEL");
			getSetup()->addChild( existingNode );
			break;
	
		default:
			assert( false && "Optional node type not supported" );
		}
	}
	
	
	// Job's done.
	return existingNode;
}



void BasicViewer::destroyOptionalNode( const OptionalNodeType type )
{
	vgd::Shp< vgd::node::Node > optionNode = getOptionalNode( type );
	
	if( optionNode )
	{
		getSetup()->removeChild( optionNode );
	}
}



vgd::Shp< vgd::node::Node > BasicViewer::getOptionalNode( const OptionalNodeType type )
{
	// Retrieves the optional node name.
	std::string	optionalNodeName;
	
	switch( type )
	{
	case CLEAR_FRAME_BUFFER:
		optionalNodeName = "CLEAR";
		break;
		
	case LIGHTS:
		optionalNodeName = "LIGHTS";
		break;
		
	case DRAW_STYLE:
		optionalNodeName = "DRAW_STYLE";
		break;
		
	case LIGHT_MODEL:
		optionalNodeName = "LIGHT_MODEL";
		break;
		
	default:
		assert( false && "Optional node type not supported" );
	}
	
	
	// Searchs for the node in the setup.
	return vgd::visitor::findFirst( getSetup(), vgd::visitor::predicate::ByName(optionalNodeName) ).second;	
}



void BasicViewer::resize( const vgm::Vec2i size )
{
	// Tests if window is degenerated
	if (	(size[0] == 0) || (size[1] == 0)	)
	{
		// Degenerated window, nothing to do
		return;
	}

	// Calls resize() provided by Canvas
	::vgUI::Canvas::resize( size );

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
							45.f,
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

	m_camera->setMatrix( matrix );

	m_camera->setViewport( vgm::Rectangle2i( 0, 0, size[0], size[1] ) );
}



void BasicViewer::computeBoundingBox(	vge::visitor::NodeCollectorExtended<> *pCollectorExt,
										vgm::Box3f& box, vgm::Vec3f& center,
										float& max )
{
	// compute/update bounding box for the whole scene graph.
	Canvas::computeBoundingBox( pCollectorExt );

	box	= getScene()->getBoundingBox();

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

		max = vgm::max( width, height, depth );
	}
}



void BasicViewer::computeSceneBoundingBox(	vgm::Box3f& box, vgm::Vec3f& center, float& max )
{
	computeBoundingBox(	0,
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



} // namespace vgUI
