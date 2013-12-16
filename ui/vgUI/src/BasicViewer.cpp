// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, 2009, 2010, 2012, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgUI/BasicViewer.hpp"

#include <vgd/node/Antialiasing.hpp>
#include <vgd/node/Camera.hpp>
#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgd/node/DirectionalLight.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/EngineProperties.hpp>
#include <vgd/node/MatrixTransform.hpp>
#include <vgd/node/MultiSwitch.hpp>
#include <vgd/node/PointLight.hpp>
#include <vgd/node/Program.hpp>
#include <vgd/node/SpotLight.hpp>
#include <vgd/node/Switch.hpp>
#include <vgd/node/TransformSeparator.hpp>
#include <vgd/visitor/helpers.hpp>
#include <vgio/helpers.hpp>
#include <vgm/operations.hpp>



namespace vgUI
{



BasicViewer::BasicViewer()
:	m_cameraType( CAMERA_DEFAULT )
{
	// Resets the scene graph
	privateResetSceneGraph();
}



BasicViewer::BasicViewer( const vgUI::Canvas * sharedCanvas )
:	vgUI::Canvas( sharedCanvas ),
	m_cameraType( CAMERA_DEFAULT )
{
	// Resets the scene graph
	privateResetSceneGraph();
}



void BasicViewer::resetSceneGraph()
{
	Canvas::resetSceneGraph();
	privateResetSceneGraph();
}



void BasicViewer::privateResetSceneGraph()
{
	// Initializes SETUP nodes
	m_setup					= vgd::node::Group::create(			"SETUP"						);
	m_scene					= vgd::node::Group::create(			"SCENE"						);

	m_overlayContainer		= vgd::node::MultiSwitch::create(	"OVERLAY_CONTAINER"			);

	m_camera			= vgd::node::Camera::create(			"CAMERA"				);
	m_camera->setComposeTransformation( false );

	// Constructs scene graph
	getRoot()->addChild( m_setup );
	getRoot()->addChild( m_scene );
	getRoot()->addChild( m_overlayContainer );
	getRoot()->addChild( m_debugOverlayContainer );

	// Populates SETUP
	getSetup()->addChild( m_camera );

	//
	vgm::MatrixR matrix;
	matrix.setOrtho( -1.f, 1.f, -1.f, 1.f, 0.01f, 2.f );
	m_camera->setProjection( matrix );
}



void BasicViewer::setCameraType( const CameraType typeOfCamera )
{
	m_cameraType = typeOfCamera;
	configureCamera();
	refresh();
}



const BasicViewer::CameraType BasicViewer::getCameraType() const
{
	return m_cameraType;
}


void BasicViewer::configureCamera()
{
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
	float	maxDepth = 4.f * max;

	//
	if ( height == 0.f )
	{
		return;
	}

	const vgm::Vec2i	drawingSize			= getEngine()->getDrawingSurfaceSize();
	const float			sceneAspectRatio	= width/height;
	const float			windowAspectRatio	= static_cast<float>(drawingSize[0])/static_cast<float>(drawingSize[1]);

	vgm::MatrixR matrix;

	switch ( getCameraType() )
	{
		case CAMERA_PERSPECTIVE:
			matrix.setPerspective(
							m_camera->getFovy(),
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
	m_camera->setAspect( windowAspectRatio );
	m_camera->setZNear( minDepth );
	m_camera->setZFar( maxDepth );

	m_camera->setViewport( vgm::Rectangle2i( 0, 0, drawingSize[0], drawingSize[1] ) );
}


void BasicViewer::viewAll( const CameraDistanceHints cameraDistance )
{
	// Initializes VIEWTRANSFORM
	m_camera->setLookAt( vgm::MatrixR::getIdentity() );

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
	if ( hasVGSDK() )
	{
		const vgm::Vec2i v2iSize = getEngine()->getDrawingSurfaceSize();

		resize( v2iSize );
	}

	// Setup the scene position.
	m_camera->setLookAt( matrix );
}



vgd::Shp< vgd::node::Group > BasicViewer::getSetup()
{
	return m_setup;
}

const vgd::Shp< vgd::node::Group > BasicViewer::getSetup() const
{
	return m_setup;
}


vgd::Shp< vgd::node::Camera > BasicViewer::getCamera()
{
	return m_camera;
}

const vgd::Shp< vgd::node::Camera > BasicViewer::getCamera() const
{
	return m_camera;
}


vgd::Shp< vgd::node::Group > BasicViewer::getScene()
{
	return m_scene;
}

const vgd::Shp< vgd::node::Group > BasicViewer::getScene() const
{
	return m_scene;
}

void BasicViewer::setScene( const vgd::Shp< vgd::node::Group > newScene )
{
	// Inserts the new scene group at the same place as the previous one.
	getRoot()->replaceChild( m_scene, newScene );
	m_scene = newScene;
}


vgd::Shp< vgd::node::MultiSwitch > BasicViewer::getOverlayContainer()
{
	return m_overlayContainer;
}


const vgd::Shp< vgd::node::MultiSwitch > BasicViewer::getOverlayContainer() const
{
	return m_overlayContainer;
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
		case ANTIALIASING:
		{
			existingNode = vgd::node::Antialiasing::create("ANTIALIASING");
			getSetup()->addChild( existingNode );
		}
		break;

		case CLEAR_FRAME_BUFFER:
		{
			vgd::Shp< vgd::node::ClearFrameBuffer > clearFrameBuffer = vgd::node::ClearFrameBuffer::create("CLEAR_FRAME_BUFFER");
			existingNode = clearFrameBuffer;
			getSetup()->addChild( existingNode );
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

		case ENGINE_PROPERTIES:
			existingNode = vgd::node::EngineProperties::create("ENGINE_PROPERTIES");
			getSetup()->addChild( existingNode );
			break;


		case LIGHTS:
		{
			//
			vgm::MatrixR matrixBak = m_camera->getLookAt();
			m_camera->setLookAt( vgm::MatrixR::getIdentity() );
			vgm::Box3f	box;
			vgm::Vec3f	boxCenter;
			float		boxMax;
			computeSceneBoundingBox( box, boxCenter, boxMax );
			if ( box.isEmpty() )	break;

			m_camera->setLookAt( matrixBak );
			vgm::Vec3f boxMin	= box.getMin(); 
			vgm::Vec3f boxSize	= box.getSize();

			//
			const vgm::Vec3f positionSpot1( boxCenter + vgm::Vec3f(0.f, 0.f, boxSize[2])*3.f );
			const vgm::Vec3f positionSpot2( boxCenter + vgm::Vec3f(-boxSize[0]/4.f, 0.f, boxSize[2])*3.f );
			const vgm::Vec3f positionSpot3( boxCenter + vgm::Vec3f(boxSize[0]/4.f, 0.f, boxSize[2])*3.f );

			using vgd::node::Group;

			using vgd::node::MatrixTransform;
			using vgd::node::TransformSeparator;

			// CREATES LIGHTS
			// Creates and switches on the directional lights.
			using vgd::node::DirectionalLight;
			vgd::Shp< DirectionalLight > light1 = DirectionalLight::create("defaultLight1");
			light1->setOn( true );
			light1->setDirection( vgm::Vec3f(0.f, 0.f, -1.f) );

			// Creates and switches on the spot light.

			using vgd::node::SpotLight;
			vgd::Shp< SpotLight > spotLight1 = SpotLight::create("spotLight1");
			spotLight1->setOn( true );
			spotLight1->setPosition( positionSpot1 );
			spotLight1->setDirection( boxCenter - positionSpot1 );
			spotLight1->setCutOffAngle( 45.f );
			//spotLight1->setDropOffRate( 0.5f );
			spotLight1->setCastShadow( true );

			vgd::Shp< SpotLight > spotLight2 = SpotLight::create("spotLight2");
			spotLight2->setOn( true );
			spotLight2->setPosition( positionSpot2 );
			spotLight2->setDirection( vgm::Vec3f(0,0,-1) );
			spotLight2->setCutOffAngle( 20.f );
			spotLight2->setCastShadow( true );

			vgd::Shp< SpotLight > spotLight3 = SpotLight::create("spotLight3", 1);
			spotLight3->setOn( true );
			spotLight3->setPosition( positionSpot3 );
			spotLight3->setDirection( vgm::Vec3f(0,0,-1) );
			spotLight3->setCutOffAngle( 20.f );
			spotLight3->setCastShadow( true );

			// Creates and switches on the point light.
			using vgd::node::PointLight;
			vgd::Shp< PointLight > pointLight1 = PointLight::create("pointLight1");
			pointLight1->setOn( true );
			pointLight1->setPosition( vgm::Vec3f(0.f, 0.f, 1000.f) );

			// CREATES LIGHTS SCENE GRAPH
			// Creates the group that will contain the directional lights.
			vgd::Shp< Group > directionalLights = Group::create("DIRECTIONAL_LIGHT");
			directionalLights->addChild( light1 );

			// Creates the group that will contain the spot light.
			vgd::Shp< TransformSeparator > spotLight = TransformSeparator::create("SPOT_LIGHT");
			vgd::Shp< MatrixTransform > matrixTransform = MatrixTransform::create("SPOT_MOVE");
			spotLight->addChild( matrixTransform );
			spotLight->addChild( spotLight1 );

			// Creates the group that will contain the spot light.
			vgd::Shp< Group > spotLights = Group::create("SPOT_LIGHTS");
			spotLights->addChild( spotLight2 );
			spotLights->addChild( spotLight3 );

			// Creates the group that will contain the point light.
			vgd::Shp< Group > pointLights = Group::create("POINT_LIGHT");
			pointLights->addChild( pointLight1 );

			// Creates the group containing all lights
			using vgd::node::Switch;
			vgd::Shp< Switch > lightSwitcher = Switch::create("LIGHTS");
			lightSwitcher->setWhichChild(0);
			lightSwitcher->addChild( directionalLights );
			lightSwitcher->addChild( spotLight );
			lightSwitcher->addChild( pointLights );
			lightSwitcher->addChild( spotLights );

			// Inserts the default lights before LightModel node.
			using vgd::node::LightModel;
			vgd::Shp< LightModel > lightModel = getOptionalNodeAs< LightModel >( LIGHT_MODEL );
			if ( lightModel )
			{
				const int insertIndex = m_setup->findChild( lightModel );
				getSetup()->insertChild( lightSwitcher, insertIndex );
			}
			else
			{
				getSetup()->addChild( lightSwitcher );
			}
			existingNode = lightSwitcher;
			break;
		}

		case UNDERLAY_CONTAINER:
			existingNode = vgd::node::MultiSwitch::create("UNDERLAY_CONTAINER");
			getSetup()->addChild( existingNode );
			break;

		case PROGRAM:
			existingNode = vgd::node::Program::createWhole("PROGRAM");
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
	return implGetOptionalNode( type );
}



const vgd::Shp< vgd::node::Node > BasicViewer::getOptionalNode( const OptionalNodeType type ) const
{
	return implGetOptionalNode( type );
}



const vgd::Shp< vgd::node::Node > BasicViewer::implGetOptionalNode( const OptionalNodeType type ) const
{
	// Retrieves the optional node name.
	std::string	optionalNodeName;
	
	switch( type )
	{
		case ANTIALIASING:
			optionalNodeName = "ANTIALIASING";
			break;

		case CLEAR_FRAME_BUFFER:
			optionalNodeName = "CLEAR_FRAME_BUFFER";
			break;

		case DRAW_STYLE:
			optionalNodeName = "DRAW_STYLE";
			break;

		case LIGHT_MODEL:
			optionalNodeName = "LIGHT_MODEL";
			break;

		case ENGINE_PROPERTIES:
			optionalNodeName = "ENGINE_PROPERTIES";
			break;

		case LIGHTS:
			optionalNodeName = "LIGHTS";
			break;

		case UNDERLAY_CONTAINER:
			optionalNodeName = "UNDERLAY_CONTAINER";
			break;

		case PROGRAM:
			optionalNodeName = "PROGRAM";
			break;

		default:
			assert( false && "Optional node type not supported" );
	}

	// Searches for the node in the setup.
	return vgd::visitor::findFirstByName< vgd::node::Node >( getSetup(), optionalNodeName );
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

	// Configures the camera.
	configureCamera();
	}


const bool BasicViewer::load( const std::string filePath )
{
	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;

	retVal = vgio::load( filePath );

	if ( retVal.first )
	{
		// Setup scene
		getScene()->addChild( retVal.second );

		// Shows in the log that the file has been loaded.
		vgLogStatus( "File %s loaded.", filePath.c_str() );
	}
	else
	{
		// Shows in the log that something has gone wrong.
		vgLogWarning( "Unable to load file %s.", filePath.c_str() );
	}

	return retVal.first;
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

		const vgm::Vec3f size = box.getSize();

		max = vgm::max( size[0], size[1], size[2] );
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
