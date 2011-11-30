// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgsdkViewerGtk/myCanvas.hpp"

#include <gdk/gdkkeysyms.h>
#include <gdkmm/cursor.h>

//#include <vgCollada/Reader.hpp>
#include <vgAlg/actions/Decrypt.hpp>
#include <vgd/basic/FilenameExtractor.hpp>
#include <vgd/basic/Image.hpp>
#include <vgd/node/Camera.hpp>
#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/MultiSwitch.hpp>
#include <vgd/node/TriSet.hpp>
#include <vgd/node/Quad.hpp>
#include <vgd/node/Sphere.hpp>
#include <vgd/node/Transform.hpp>
#include <vgeGL/engine/Engine.hpp>
#include <vgeGL/technique/MultiMain.hpp>
#include <vgDebug/helpers.hpp>
#include <vge/engine/UserSettings.hpp>
#include <vgGTK/engine/UserSettingsDialog.hpp>
#include <vgGTK/node/ColladaSettingsDialog.hpp>
#include <vgio/helpers.hpp>
#include <vgObj/Loader.hpp>
#include <vgTrian/Loader.hpp>
#include <vgOpenCOLLADA/importer/Loader.hpp>
#include <vgOpenCOLLADA/convenience.hpp>

#include "vgsdkViewerGtk/actions.hpp"




namespace
{

void onRenderSettingsSignalChanged( vgsdkViewerGtk::myCanvas * canvas )
{
	vgd::Shp< vgGTK::engine::UserSettingsDialog >	renderSettings	= canvas->getRenderSettingsDialog();

	// Applies the render settings
	renderSettings->get()->apply( *canvas );

	// Refreshs the canvas
	canvas->refreshForced();
}

}



namespace vgsdkViewerGtk
{



myCanvas::myCanvas()
{
	// Initial window size
	set_size_request( 1024, 768 );
	//set_size_request( 512, 512 );


	// Scene graph initialization.
	createOptionalNode( LIGHTS );
	createOptionalNode( CLEAR_FRAME_BUFFER );
	createOptionalNode( DRAW_STYLE );

	using vgd::node::LightModel;
	vgd::Shp< LightModel > lightModel = vgd::dynamic_pointer_cast< LightModel >( createOptionalNode( LIGHT_MODEL ) );
	lightModel->setModel( LightModel::STANDARD_PER_PIXEL );
	lightModel->setViewer( LightModel::AT_EYE );


	// SHADOW configuration

	/*lightModel->setShadowFiltering( LightModel::LINEAR );
	lightModel->setShadow( LightModel::SHADOW_MAPPING_9U );
	lightModel->setShadowMapSize( LightModel::MEDIUM );
	lightModel->setShadowMapType( LightModel::INT32 );
	lightModel->setIlluminationInShadow( 0.4f );*/

	// END SHADOW configuration

	// Get the reference of the default technique
	m_viewModeTechniques.resize( VIEW_MODE_COUNT );
	m_viewModeTechniques[ SINGLE_VIEW ]			= getPaintTechnique(); //createMultiViewSingleTechnique();
	m_viewModeTechniques[ LEFT_SIDED_VIEWS ]	= createMultiViewSidedTechnique();
	m_viewModeTechniques[ SQUARED_VIEWS ]		= createMultiViewSquaredTechnique();

	setViewMode( SINGLE_VIEW );

	// Installs key handler
	add_events(Gdk::KEY_PRESS_MASK );
	signal_key_press_event().connect( ::sigc::mem_fun(this, &myCanvas::onKeyPressed) );

	// Default light configuration
	using vgd::node::Switch;
	vgd::Shp< Switch > lightSwitcher = vgd::dynamic_pointer_cast<Switch>( getOptionalNode(LIGHTS) );

	if ( lightSwitcher )
	{
		lightSwitcher->setWhichChild( 0 );
	}

	// Configures engine
	// getGLEngine()->setDisplayListEnabled( true );
	// setDebugOverlay(true);

	setShowMenu(true);
}



bool myCanvas::onKeyPressed( GdkEventKey * event )
{
	using vgd::node::Switch;

	// L : switch to next light(s) configuration
	vgd::Shp< Switch > lightSwitcher = vgd::dynamic_pointer_cast<Switch>( getOptionalNode(LIGHTS) );
	if ( lightSwitcher != 0 && event->keyval == 'l' )
	{
		int whichChild = lightSwitcher->getWhichChild();
		if ( whichChild == lightSwitcher->getNumChildren() - 1 )
		{
			whichChild = 0;
		}
		else
		{
			++whichChild;
		}
		lightSwitcher->setWhichChild( whichChild );
	}

	// F : fps
	if ( event->keyval == 'f' )
	{
		setDebugOverlay( !isDebugOverlay() );
	}

#ifdef MY_WORK
	processKeyPressed( this, event );
#endif

	return false;
}



void myCanvas::initialize()
{
	// Configures the rendering.
	vgd::Shp< vgGTK::engine::UserSettingsDialog > renderSettingsDialog = getRenderSettingsDialog();

	// SETUP

	// SCENE
#ifdef MY_WORK
	initializeShadowScene( this );
#endif

	//
	viewAll();
}



void myCanvas::setViewMode( const ViewMode mode )
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



void myCanvas::clearScene()
{
	// Changes the cursor
	get_root_window()->set_cursor( Gdk::Cursor(Gdk::WATCH) );

	m_filenames.clear();
// @todo
//	resetSceneGraph();
	getScene()->removeAllChildren();
	vgLogStatus( "Scene cleared." );

	// Changes the cursor
	get_root_window()->set_cursor();
}



const bool myCanvas::appendToScene( const Glib::ustring & filename, const bool mustCallViewAll )
{
	// Changes the cursor
	get_root_window()->set_cursor( Gdk::Cursor(Gdk::WATCH) );

	const bool retVal = load( filename );

	if ( retVal )
	{
		if ( mustCallViewAll ) viewAll();

		refresh( REFRESH_FORCE, SYNCHRONOUS );
		m_filenames.push_back( filename );
	}

	// Changes the cursor
	get_root_window()->set_cursor();

	return retVal;
}



const bool myCanvas::appendToScene( const Strings & pathfilenames, const bool mustCallViewAll )
{
	// Changes the cursor
	get_root_window()->set_cursor( Gdk::Cursor(Gdk::WATCH) );

	refresh();

	bool retVal = true;

	Strings::const_iterator	i;
	for ( i = pathfilenames.begin(); i != pathfilenames.end(); ++i )
	{
		const bool lRetVal = load( *i );

		if ( lRetVal )
		{
			m_filenames.push_back( *i );

			if ( mustCallViewAll )
			{
				viewAll();
			}

			refresh( REFRESH_FORCE, SYNCHRONOUS );
		}
		else
		{
			retVal = false;
		}
	}

	// Changes the cursor
	get_root_window()->set_cursor();

	return retVal;
}



const bool myCanvas::isEmpty() const
{
	return getScene()->getNumChildren() == 0;
}



const bool myCanvas::reloadScene()
{
	// Changes the cursor
	get_root_window()->set_cursor( Gdk::Cursor(Gdk::WATCH) );

	const Strings filenames = m_filenames;

	clearScene();

	const bool retVal = appendToScene( filenames, false );

	// Changes the cursor
	get_root_window()->set_cursor();

	return retVal;
}



vgd::Shp< vgGTK::engine::UserSettingsDialog > myCanvas::getRenderSettingsDialog()
{
	if ( !m_renderSettingsDialog )
	{
		// Creates dialog
		Gtk::Window * toplevel = dynamic_cast< Gtk::Window * >( get_toplevel() );
		m_renderSettingsDialog.reset( new vgGTK::engine::UserSettingsDialog(toplevel) );

		// Initializes the render settings level
		m_renderSettingsDialog->get()->setLevel( 2 );
		m_renderSettingsDialog->getGUI().refreshLevel();
		// Applies the render settings
		m_renderSettingsDialog->get()->apply( *this );

		// Connects to signals
		m_renderSettingsDialog->getGUI().signalChanged().connect( sigc::bind(sigc::ptr_fun(&onRenderSettingsSignalChanged), this) ); // do refresh
	}

	return m_renderSettingsDialog;
}



const bool myCanvas::load( const Glib::ustring & pathfilename )
{
//
	// Load .trian
	vgTrian::Loader loader;
//
	// Changes the cursor
	get_root_window()->set_cursor( Gdk::Cursor(Gdk::WATCH) );

	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;

	retVal = vgio::load( pathfilename );

	if ( retVal.first )
	{
		// Setup scene
		getScene()->addChild( retVal.second );

		// Shows in the log that the file has been loaded.
		vgLogStatus( "File %s loaded.", pathfilename.c_str() );
	}
	else
	{
		// Shows in the log that something has gone wrong.
		vgLogWarning( "Unable to load file %s.", pathfilename.c_str() );
	}

	// Changes the cursor
	get_root_window()->set_cursor();

	return retVal.first;
}


//
//const bool myCanvas::loadCollada( const Glib::ustring & pathfilename )
//{
///*	// Load .dae
//	vgCollada::Reader reader;
//	const bool retVal = reader.load( pathfilename.c_str() );
//
//	if ( retVal )
//	{
//		// Setup scene
//		getScene()->addChild( reader.getRoot() );
//	}
//
//	return retVal;*/
//	return false;
//}
//
//const bool myCanvas::loadOpenCollada( const Glib::ustring & pathfilename, bool crypted )
//{
//	// Load .dae
//	vgGTK::node::ColladaSettingsDialog dialog;
//	dialog.show_all();
//
//	vgOpenCOLLADA::Settings  settings;
//	if( dialog.run() == Gtk::RESPONSE_OK )
//	{
//		settings = dialog.getSettings();
//	}
//	else
//	{
//		return false;
//	}
//	dialog.hide_all();
//
//	vgOpenCOLLADA::importer::Loader loader( settings );
//	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;
//	
//	try
//	{
//		if( crypted )
//		{
//			std::ifstream inFile;
//			inFile.open( pathfilename.c_str(), std::ifstream::in | std::ifstream::binary );
//			bool b = inFile.good();
//			inFile.seekg (0, std::ios::end);
//			int length = inFile.tellg();
//			inFile.seekg (0, std::ios::beg);
//
//			std::vector< char > inBuffer;
//			inBuffer.resize( length );
//			inFile.read( &inBuffer[0], length );
//			
//			vgd::Shp< std::vector< char > > outBuffer( new std::vector< char > );
//
//			vgAlg::actions::Decrypt decrypt;
//			decrypt.setInitialize( "vgsdkViewerGTK", inBuffer, outBuffer );
//			decrypt.execute();
//
//			retVal = loader.load( pathfilename.c_str(), outBuffer );
//		}
//		else
//		{
//			retVal = loader.load( pathfilename.c_str() );
//		}
//	}
//	catch(std::runtime_error e)
//	{
//		return false;
//	}
//
//	if ( retVal.first )
//	{
//		// Setup scene
//		getScene()->addChild( retVal.second );
//	}
//
//	return retVal.first;
//}
//
//
//const bool myCanvas::loadObj( const Glib::ustring & pathfilename )
//{
//	// Load .obj
//	vgObj::Loader loader;
//	std::pair< bool, vgd::Shp< vgd::node::VertexShape > > retVal;
//
//	retVal = loader.loadObj( pathfilename.c_str() );
//
//	if ( !retVal.first )
//	{
//		return false;
//	}
//
//	// Setup scene
//	using vgd::node::Material;
//
//	vgd::Shp< Material > material = Material::create("material");
//	material->setDiffuse( vgm::Vec3f(204.f/255.f, 251.f/255.f, 51.f/255.f) );
//	material->setSpecular( vgm::Vec3f(1.f, 1.f, 1.f) );
//	material->setShininess( 1.f );
//
//	getScene()->addChild( material );
//	getScene()->addChild( retVal.second );
//	//(retVal.second)->computeNormals();
//
//	return true;
//}
//
//
//
//const bool myCanvas::loadTrian( const Glib::ustring & pathfilename )
//{
//	// Load .trian
//	vgTrian::Loader loader;
//	std::pair< bool, vgd::Shp< vgd::node::TriSet > > retVal = loader.loadTrian( std::string(pathfilename.c_str()) );
//
//	if ( !retVal.first )
//	{
//		return false;
//	}
//
//	// Setup scene
//	using vgd::node::Material;
//
//	vgd::Shp< Material > material = Material::create("material");
//	material->setDiffuse( vgm::Vec3f(204.f/255.f, 51.f/255.f, 51.f/255.f) );
//	material->setSpecular( vgm::Vec3f(1.f, 1.f, 1.f) );
//	material->setShininess( 1.f );
//
//	getScene()->addChild( material );
//	getScene()->addChild( retVal.second );
//	(retVal.second)->computeNormals();
//
//	return true;
//}
//
//
//
//const bool myCanvas::loadTrian2( const Glib::ustring & pathfilename, bool crypted )
//{
//	// Load .trian
//	vgTrian::Loader loader;
//	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;
//
//	try
//	{
//		if( crypted )
//		{
//			std::ifstream inFile;
//			inFile.open( pathfilename.c_str(), std::ifstream::in | std::ifstream::binary );
//			bool b = inFile.good();
//			inFile.seekg (0, std::ios::end);
//			int length = inFile.tellg();
//			inFile.seekg (0, std::ios::beg);
//
//			std::vector< char > inBuffer;
//			inBuffer.resize( length );
//			inFile.read( &inBuffer[0], length );
//			
//			vgd::Shp< std::vector< char > > outBuffer( new std::vector< char > );
//
//			vgAlg::actions::Decrypt decrypt;
//			decrypt.setInitialize( "vgsdkViewerGTK", inBuffer, outBuffer );
//			decrypt.execute();
//
//			retVal = loader.load( pathfilename.c_str(), outBuffer );
//		}
//		else
//		{
//			retVal = loader.load( pathfilename.c_str() );
//		}
//	}
//	catch(std::runtime_error e)
//	{
//		return false;
//	}
//
//	if ( !retVal.first )
//	{
//		return false;
//	}
//
//	// Setup scene
//	getScene()->addChild( retVal.second );
//
//	return true;
//}
//


vgd::Shp< vgeGL::technique::Technique > myCanvas::createMultiViewSingleTechnique()
{
	// Multi-view rendering technique initialization.
	using vgeGL::technique::MultiMain;

	vgd::Shp< MultiMain >	technique( new MultiMain() );

	vgd::Shp< MultiMain::Window > mainView = technique->addWindow( "main", 0, MultiMain::WindowBorder(false) );
	mainView->setGeometry( vgm::Rectangle2f(0.f, 0.f, 1.f, 1.f) );

	return technique;
}


vgd::Shp< vgeGL::technique::Technique > myCanvas::createMultiViewSidedTechnique()
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



vgd::Shp< vgeGL::technique::Technique > myCanvas::createMultiViewSquaredTechnique()
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



} // namespace vgsdkViewerGtk

