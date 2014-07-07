// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, 2012, 2013, Guillaume Brocker, Nicolas Papier, Bryan Schuller.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier
// Author Bryan Schuller

#include "vgsdkViewerQt/MyCanvas.hpp"

#include <QKeyEvent>

#include <vgeGL/technique/MultiMain.hpp>
#include <vgd/node/Antialiasing.hpp>
#include <vgd/node/Box.hpp>
#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/EngineProperties.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/TessellationLevel.hpp>
#include <vgd/node/TessellationProperties.hpp>
#include <vgeGL/event/RefresherCallback.hpp>
#include <vgeGL/event/TimerEventProcessor.hpp>

#include "vgsdkViewerQt/PythonScript.hpp"

#ifdef MY_WORK
#include "vgsdkViewerQt/my.hpp"
#endif



namespace vgsdkViewerQt
{


MyCanvas::MyCanvas()
{
}


MyCanvas::MyCanvas( const MyCanvas * sharedCanvas )
: vgQt::BasicManipulator( sharedCanvas, 0 )
{
}


void MyCanvas::initialize()
{
	// Scene graph initialization
	createOptionalNodes();

	using vgd::node::ClearFrameBuffer;
	vgd::Shp< ClearFrameBuffer > clear = getOptionalNodeAs< ClearFrameBuffer >( CLEAR_FRAME_BUFFER );
	//clear->setClearColor( vgm::Vec4f(0.1f, 0.f, 0.f, 0.f) );

	// Get the reference of the default technique
	m_viewModeTechniques.resize( VIEW_MODE_COUNT );
	m_viewModeTechniques[ SINGLE_VIEW ]			= getPaintTechnique();
	m_viewModeTechniques[ LEFT_SIDED_VIEWS ]	= createMultiViewSidedTechnique();
	m_viewModeTechniques[ SQUARED_VIEWS ]		= createMultiViewSquaredTechnique();

	// setViewMode( SINGLE_VIEW );

	// STEREO
	//setRequestedGLContextProperties( vgeGL::engine::GLContextProperties(true) );
	//getCamera()->setMode( vgd::node::Camera::QUAD_BUFFER );

	// Configures engine
	setDebugOverlay(true);

#ifdef MY_WORK
	//
	//initializeShadowScene( this );
	initializeUniformsScene( this );
	initializeSharedFieldScene( this );
#endif

	// Default scene
	vgd::Shp< vgd::node::Box > box = vgd::node::Box::create("Default scene");
	getScene()->addChild( box );

	//	Default light configuration
	using vgd::node::Switch;
	vgd::Shp< Switch > lightSwitcher = vgd::dynamic_pointer_cast<Switch>( createOptionalNode(LIGHTS) );

	// LIGHTS node is the first child of the setup group			@todo menu to switch between LIGHTS located on the camera (set in the camera) or located in the scene (set in the scene)
	getSetup()->removeChild( lightSwitcher );
	getSetup()->insertChild( lightSwitcher );

	if ( lightSwitcher )
	{
		lightSwitcher->setWhichChild( 0 );
	}

	viewAll();
	refreshForced();
}


void MyCanvas::keyPressEvent(QKeyEvent * event)
{
	using vgd::node::Switch;

	// L : switch to next light(s) configuration
	vgd::Shp< Switch > lightSwitcher = vgd::dynamic_pointer_cast<Switch>( getOptionalNode(LIGHTS) );
	if ( lightSwitcher != 0 && event->key() == Qt::Key_L )
	{
		int whichChild = lightSwitcher->getWhichChild();
		const int incr = ( event->modifiers() == Qt::ShiftModifier ) ? -1 : 1;

		whichChild += incr;
		const int clampWhichChild = vgm::clamp(whichChild, 0, lightSwitcher->getNumChildren() - 1 );
		if ( clampWhichChild == whichChild )
		{
			destroyOptionalNode( vgQt::BasicManipulator::LIGHTS );
			lightSwitcher = createOptionalNodeAs<Switch>( vgQt::BasicManipulator::LIGHTS );
			getSetup()->removeChild( lightSwitcher );
			getSetup()->insertChild( lightSwitcher );
		}

		lightSwitcher->setWhichChild( clampWhichChild );
		refresh( REFRESH_FORCE, SYNCHRONOUS );
	}

	// F : fps
	if ( event->key() == Qt::Key_F )
	{
		setDebugOverlay( !isDebugOverlay() );
		refresh( REFRESH_FORCE, SYNCHRONOUS );
	}


	// Rendering properties
	using vgd::node::DrawStyle;
	vgd::Shp< DrawStyle > drawStyle = findFirstByType<DrawStyle>();

	using vgd::node::LightModel;
	vgd::Shp< LightModel > lightModel = findFirstByType<LightModel>();

	using vgd::node::EngineProperties;
	vgd::Shp< EngineProperties > engineProperties = findFirstByType<EngineProperties>();

	using vgd::node::TessellationProperties;
	vgd::Shp< TessellationProperties > tessProperties = findFirstByType<TessellationProperties>();

	// W: smooth <=> wireframe
	if ( event->key() == Qt::Key_W )
	{
		if ( drawStyle )
		{
			DrawStyle::ShapeValueType value = DrawStyle::DEFAULT_SHAPE;
			drawStyle->getShape( value );
			value = (value == DrawStyle::DEFAULT_SHAPE) ? DrawStyle::WIREFRAME : DrawStyle::DEFAULT_SHAPE;
			drawStyle->setShape( value );
			refresh( REFRESH_FORCE, SYNCHRONOUS );
		}
	}

	// N: draw normals/tangents
	if ( event->key() == Qt::Key_N )
	{
		if ( drawStyle )
		{
			DrawStyle::NormalLengthValueType nvalue = DrawStyle::DEFAULT_NORMALLENGTH;
			drawStyle->getNormalLength( nvalue );
			nvalue = (nvalue == DrawStyle::DEFAULT_NORMALLENGTH) ? 1.f : DrawStyle::DEFAULT_NORMALLENGTH;
			drawStyle->setNormalLength( nvalue );

			DrawStyle::TangentLengthValueType tvalue = DrawStyle::DEFAULT_TANGENTLENGTH;
			drawStyle->getTangentLength( tvalue );
			tvalue = (tvalue == DrawStyle::DEFAULT_TANGENTLENGTH) ? 1.f : DrawStyle::DEFAULT_TANGENTLENGTH;
			drawStyle->setTangentLength( tvalue );

			refresh( REFRESH_FORCE, SYNCHRONOUS );
		}
	}

	// D: two sided OFF <=> ON
	if ( event->key() == Qt::Key_D )
	{
		if ( lightModel )
		{
			LightModel::TwoSidedValueType value = LightModel::DEFAULT_TWOSIDED;
			/*const bool hasValue = */lightModel->getTwoSided( value );
			value = (value == LightModel::DEFAULT_TWOSIDED) ? true : LightModel::DEFAULT_TWOSIDED;
			lightModel->setTwoSided( value );
			refresh( REFRESH_FORCE, SYNCHRONOUS );
		}
	}

	// B: bumpmapping OFF <=> ON
	if ( event->key() == Qt::Key_B )
	{
		if ( lightModel )
		{
			LightModel::BumpMappingValueType value = LightModel::DEFAULT_BUMPMAPPING;
			value = lightModel->getBumpMapping();
			value = (value == LightModel::DEFAULT_BUMPMAPPING) ? true : LightModel::DEFAULT_BUMPMAPPING;
			lightModel->setBumpMapping( value );
			refresh( REFRESH_FORCE, SYNCHRONOUS );
		}
	}

	// T: tessellation DISABLED <=> PHONG
	if ( event->key() == Qt::Key_T )
	{
		if ( tessProperties )
		{
			TessellationProperties::TessellationValueType value = TessellationProperties::DEFAULT_TESSELLATION;
			/*const bool hasValue = */tessProperties->getTessellation( value );
			value = (value == TessellationProperties::DEFAULT_TESSELLATION) ? TessellationProperties::PHONG : TessellationProperties::DEFAULT_TESSELLATION;
			tessProperties->setTessellation( value );
			refresh( REFRESH_FORCE, SYNCHRONOUS );
		}
	}


	// S: shadow 9U <=> OFF
	if ( event->key() == Qt::Key_S )
	{
		if ( lightModel )
		{
			LightModel::ShadowValueType value = LightModel::DEFAULT_SHADOW;
			lightModel->getShadow( value );
			value = (value == LightModel::DEFAULT_SHADOW) ? LightModel::SHADOW_MAPPING_9U : LightModel::DEFAULT_SHADOW;
			lightModel->setShadow( value );
			refresh( REFRESH_FORCE, SYNCHRONOUS );
		}
	}


	// R: continuous refresh
	if ( event->key() == Qt::Key_R )
	{
		using vgeGL::event::RefresherCallback;

		vgd::Shp< vgeGL::event::RefresherCallback > refresher = getTimerEventProcessor()->find< RefresherCallback >();
		if ( refresher )
		{
			getTimerEventProcessor()->remove( refresher );
		}
		else
		{
			vgd::Shp< RefresherCallback > refresher( new RefresherCallback() );
			getTimerEventProcessor()->add( refresher );
		}
	}
}


const bool MyCanvas::appendToScene( const QString & filename )
{
	// begin: python loading
	QString extension = filename.section(".", -1, -1, QString::SectionSkipEmpty);
	if (extension.compare("py", Qt::CaseSensitive) == 0)
	{
		m_pythonScript.reset( new PythonScript(this, filename.toStdString()) );
		m_filenames.append(filename);
		return true; // @todo get a correct return value, catch loading failure
	}
	// end: python loading
	else
	{
		const bool retVal = load(filename.toStdString());
		if (retVal)
		{
			viewAll();
			refresh(REFRESH_FORCE, SYNCHRONOUS);
			m_filenames.append(filename);
		}
		return retVal;
	}
}


const bool MyCanvas::appendToScene( const QList<QString> & filenames )
{
	bool retVal = true;
	Q_FOREACH(QString filename, filenames)
	{
		// begin: python loading
		QString extension = filename.section(".", -1, -1, QString::SectionSkipEmpty);
		if (extension.compare("py", Qt::CaseSensitive) == 0)
		{
			m_pythonScript.reset( new PythonScript(this, filename.toStdString()) );
			m_filenames.append(filename);
			retVal = true; // @todo get a correct return value, catch loading failure
		}
		// end: python loading
		else
		{
			const bool lRetVal = load(filename.toStdString());
			if (lRetVal)
			{
				viewAll();
				refresh(REFRESH_FORCE, SYNCHRONOUS);
				m_filenames.append(filename);
			}
			else
			{
				retVal = false;
			}
		}
	}
	return retVal;
}


const bool MyCanvas::isEmpty() const
{
	return getScene()->getNumChildren() == 0 && m_pythonScript == 0;
}


const bool MyCanvas::reloadScene()
{
	const QList<QString> filenames = m_filenames;
	clearScene();
	const bool retVal = appendToScene( filenames );
	return retVal;
}


void MyCanvas::setViewMode( const ViewMode mode )
{
	if( mode < VIEW_MODE_COUNT && m_viewModeTechniques[mode] )
	{
		setPaintTechnique( m_viewModeTechniques[mode] );
		refreshForced( ASYNCHRONOUS );
	}
	else
	{
		vgLogDebug( "Error while setting view mode technique." );
	}
}


vgd::Shp< vgeGL::technique::Technique > MyCanvas::createMultiViewSingleTechnique()
{
	// Multi-view rendering technique initialization.
	using vgeGL::technique::MultiMain;

	vgd::Shp< MultiMain >	technique( new MultiMain() );

	vgd::Shp< MultiMain::Window > mainView = technique->addWindow( "main", 0, MultiMain::WindowBorder(false) );
	mainView->setGeometry( vgm::Rectangle2f(0.f, 0.f, 1.f, 1.f) );

	return technique;
}


vgd::Shp< vgeGL::technique::Technique > MyCanvas::createMultiViewSidedTechnique()
{
	// Multi-view rendering technique initialization.
	using vgeGL::technique::MultiMain;

	const float				oneTier		= 1.f / 3.f;
	const float				padding		= 0.011f;
	const float				subWidth	= oneTier - padding - padding;
	const float				subHeight	= oneTier - padding - padding;

	vgd::Shp< MultiMain >	technique( new MultiMain() );

	vgd::Shp< MultiMain::Window > mainView = technique->addWindow( "main", 0, MultiMain::WindowBorder(false) );
	mainView->setGeometry( vgm::Rectangle2f(0.f, 0.f, 1.f, 1.f) );

	vgd::Shp< MultiMain::Window > topView = technique->addWindow( "top", 1,
		MultiMain::WindowBorder(true, vgm::Vec4f(1.f,0.f,0.f,1.f)) );
	const vgm::Rotation rotateTop(vgm::Vec3f(0.f,0.f,-1.f), vgm::Vec3f(0.f,1.f,0.f));
	topView->setGeometry( vgm::Rectangle2f(padding, 0*oneTier+padding, subWidth, subHeight) );
	topView->setConfigurator( vgd::makeShp(new MultiMain::ViewPointConfigurator(getSceneTransformation(), rotateTop)) );

	vgd::Shp< MultiMain::Window > bottomView = technique->addWindow( "bottom", 1,
		MultiMain::WindowBorder(true, vgm::Vec4f(0.f,1.f,0.f,1.f)) );
	const vgm::Rotation rotateBottom(vgm::Vec3f(0.f,0.f,-1.f), vgm::Vec3f(0.f,-1.f,0.f));
	bottomView->setGeometry( vgm::Rectangle2f(padding, 1*oneTier+padding, subWidth, subHeight) );
	bottomView->setConfigurator( vgd::makeShp(new MultiMain::ViewPointConfigurator(getSceneTransformation(), rotateBottom)) );

	vgd::Shp< MultiMain::Window > oppositeView = technique->addWindow( "opposite", 1,
		MultiMain::WindowBorder(true, vgm::Vec4f(0.f,0.f,1.f,1.f)) );
	const vgm::Rotation rotateOpposite(vgm::Vec3f(0.f,0.f,-1.f), vgm::Vec3f(0.f,0.f,1.f));
	oppositeView->setGeometry( vgm::Rectangle2f(padding, 2*oneTier+padding, subWidth, subHeight) );
	oppositeView->setConfigurator( vgd::makeShp(new MultiMain::ViewPointConfigurator(getSceneTransformation(), rotateOpposite)) );

	return technique;
}


vgd::Shp< vgeGL::technique::Technique > MyCanvas::createMultiViewSquaredTechnique()
{
	// Multi-view rendering technique initialization.
	using vgeGL::technique::MultiMain;

	vgd::Shp< MultiMain >	technique( new MultiMain() );

	vgd::Shp< MultiMain::Window > mainView = technique->addWindow( "main", 0,
		MultiMain::WindowBorder(true, vgm::Vec4f(1.f,1.f,1.f,1.f)) );
	mainView->setGeometry( vgm::Rectangle2f(0.5f, 0.5f, 0.5f, 0.5f) );

	vgd::Shp< MultiMain::Window > topView = technique->addWindow( "top", 1,
		MultiMain::WindowBorder(true, vgm::Vec4f(1.f,0.f,0.f,1.f)) );
	const vgm::Rotation rotateTop(vgm::Vec3f(0.f,0.f,-1.f), vgm::Vec3f(0.f,1.f,0.f));
	topView->setGeometry( vgm::Rectangle2f(0.f, 0.f, 0.5f, 0.5f) );
	topView->setConfigurator( vgd::makeShp(new MultiMain::ViewPointConfigurator(getSceneTransformation(), rotateTop)) );

	vgd::Shp< MultiMain::Window > bottomView = technique->addWindow( "bottom", 1,
		MultiMain::WindowBorder(true, vgm::Vec4f(0.f,1.f,0.f,1.f)) );
	const vgm::Rotation rotateBottom(vgm::Vec3f(0.f,0.f,-1.f), vgm::Vec3f(0.f,-1.f,0.f));
	bottomView->setGeometry( vgm::Rectangle2f(0.f, 0.5f, 0.5f, 0.5f) );
	bottomView->setConfigurator( vgd::makeShp(new MultiMain::ViewPointConfigurator(getSceneTransformation(), rotateBottom)) );

	vgd::Shp< MultiMain::Window > oppositeView = technique->addWindow( "opposite", 1,
		MultiMain::WindowBorder(true, vgm::Vec4f(0.f,0.f,1.f,1.f)) );
	const vgm::Rotation rotateOpposite(vgm::Vec3f(0.f,0.f,-1.f), vgm::Vec3f(0.f,0.f,1.f));
	oppositeView->setGeometry( vgm::Rectangle2f(0.5, 0.f, 0.5f, 0.5f) );
	oppositeView->setConfigurator( vgd::makeShp(new MultiMain::ViewPointConfigurator(getSceneTransformation(), rotateOpposite)) );

	return technique;
}


void MyCanvas::clearScene()
{
	m_pythonScript.reset();
	m_filenames.clear();

	resetSceneGraph();
	createOptionalNodes();

	// Default scene
	vgd::Shp< vgd::node::Box > box = vgd::node::Box::create("Default scene");
	getScene()->addChild(box);

	//	Default light configuration
	using vgd::node::Switch;
	vgd::Shp< Switch > lightSwitcher = vgd::dynamic_pointer_cast<Switch>(createOptionalNode(LIGHTS));

	//// LIGHTS node is the first child of the setup group			@todo menu to switch between LIGHTS located on the camera (set in the camera) or located in the scene (set in the scene)
	getSetup()->removeChild(lightSwitcher);
	getSetup()->insertChild(lightSwitcher);

	if (lightSwitcher)
	{
		lightSwitcher->setWhichChild(0);
	}

	// Remove default scene
	getScene()->removeAllChildren();
}


} // namespace vgsdkViewerQt
