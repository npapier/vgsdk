// VGSDK - Copyright (C) 2008, Guillaume Brocker, Nicolas Papier, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier
// Author Maxime Peresson

#include "vgsdkTestGtk/vgTest/myCanvas.hpp"

#include <time.h>
#include <vgAlg/actions/Decrypt.hpp>
#include <vgd/basic/FilenameExtractor.hpp>
#include <vgeGL/engine/Engine.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/TriSet.hpp>

#include <vgGTK/event/device/mouse.hpp>
#include <vgGTK/event/device/keyboard.hpp>
#include <vgGTK/event/device/timer.hpp>
#include <vgSDL/event/device/joystick.hpp>

#include <vgObj/Loader.hpp>
#include <vgOpenCOLLADA/importer/Loader.hpp>
#include <vgOpenCOLLADA/convenience.hpp>
#include <vgTrian/Loader.hpp>
#include <vgd/basic/Image.hpp>
#include <vgio/helpers.hpp>

namespace vgsdkTestGtk
{

namespace vgTest
{

myCanvas::myCanvas()
{
	// Initial window size
	set_size_request( 1024, 768 );

	// Configures engine
	getGLEngine()->setGLSLEnabled();

	// Scene graph initialization.
	using vgd::node::LightModel;

	createOptionalNode( LIGHTS );
	createOptionalNode( CLEAR_FRAME_BUFFER );
	createOptionalNode( DRAW_STYLE );

	vgd::Shp< LightModel > lightModel = vgd::dynamic_pointer_cast< LightModel >( createOptionalNode( LIGHT_MODEL ) );
	lightModel->setModel( LightModel::STANDARD_PER_PIXEL );
	lightModel->setViewer( LightModel::AT_EYE );
}

const bool myCanvas::appendToScene( const Glib::ustring & filename, const bool mustCallViewAll )
{
	// Changes the cursor
	//get_root_window()->set_cursor( Gdk::Cursor(Gdk::WATCH) );

	const bool retVal = load( filename );

	if ( retVal )
	{
		if ( mustCallViewAll ) viewAll();

		//refresh( REFRESH_FORCE, SYNCHRONOUS );
		m_filenames.push_back( filename );
	}

	// Changes the cursor
	//get_root_window()->set_cursor();

	return retVal;
}

const bool myCanvas::appendToScene( const Strings & pathfilenames, const bool mustCallViewAll )
{
	// Changes the cursor
	//get_root_window()->set_cursor( Gdk::Cursor(Gdk::WATCH) );

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
	//get_root_window()->set_cursor();

	return retVal;
}

const bool myCanvas::load( const Glib::ustring & pathfilename )
{
	// Changes the cursor
	//get_root_window()->set_cursor( Gdk::Cursor(Gdk::WATCH) );

	// Retrieves the extension of the given filename.
	vgd::basic::FilenameExtractor	extractor( pathfilename.c_str() );
	Glib::ustring					extension = extractor.getExtension();
	bool							bRetVal;

	extension = extension.lowercase();


	// Invokes the right loader, depending on the found extension.
	if ( extension.compare( ".trian" ) == 0 )
	{
		bRetVal = loadTrian( pathfilename );
	}
	else if ( extension.compare( ".trian2" ) == 0 || extension.compare( ".dae" ) == 0
		|| extension.compare( ".crypt" ) == 0 || extension.compare( ".vgarch" ) == 0) //new way using registry
	{
		std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;
		retVal = vgio::load( pathfilename );
		bRetVal = retVal.first;
		if ( retVal.first )
		{
			// Setup scene
			getScene()->addChild( retVal.second );
		}
	}
	else if( extension.compare( ".obj" ) == 0 )
	{
		bRetVal = loadObj( pathfilename );
	}
	else
	{
		bRetVal = false;

		vgLogWarning( "Unknown file extension in %s.", pathfilename.c_str() );
	}


	// Perform post loading actions that depend on the result.
	if ( bRetVal )
	{
		// Shows in the log that the file has been loaded.
		vgLogStatus( "File %s loaded.", pathfilename.c_str() );
	}
	else
	{
		// Shows in the log that something has gone wrong.
		vgLogWarning( "Unable to load file %s.", pathfilename.c_str() );
	}

	// Changes the cursor
	//get_root_window()->set_cursor();

	return bRetVal;
}

const bool myCanvas::loadCollada( const Glib::ustring & pathfilename )
{
/*	// Load .dae
	vgCollada::Reader reader;
	const bool retVal = reader.load( pathfilename.c_str() );

	if ( retVal )
	{
		// Setup scene
		getScene()->addChild( reader.getRoot() );
	}

	return retVal;*/
	return false;
}

// @todo share code with vgio::helpers.cpp
const bool myCanvas::loadOpenCollada( const Glib::ustring & pathfilename, bool crypted )
{
	// Load .dae
	vgOpenCOLLADA::importer::Loader loader;
	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;
	
	try
	{
		if( crypted )
		{
			vgd::Shp< std::vector<char> > inBuffer = vgio::readFile( pathfilename );
			if( inBuffer->empty() )
			{
				return false;
			}

			vgd::Shp< std::vector< char > > outBuffer( new std::vector<char> );

			vgAlg::actions::Decrypt decrypt;
			decrypt.setInitialize( "vgsdkViewerGTK", inBuffer, outBuffer );
			decrypt.execute();

			retVal = loader.load( pathfilename.c_str(), outBuffer );
		}
		else
		{
			retVal = loader.load( pathfilename.c_str() );
		}
	}
	catch(std::runtime_error e)
	{
		return false;
	}

	if ( retVal.first )
	{
		// Setup scene
		getScene()->addChild( retVal.second );
	}

	return retVal.first;
}



const bool myCanvas::loadObj( const Glib::ustring & pathfilename )
{
	// Load .obj
	vgObj::Loader loader;
	std::pair< bool, vgd::Shp< vgd::node::VertexShape > > retVal;

	retVal = loader.loadObj( pathfilename.c_str() );

	if ( !retVal.first )
	{
		return false;
	}

	// Setup scene
	getScene()->addChild( retVal.second );
	//(retVal.second)->computeNormals();

	return true;
}

const bool myCanvas::loadTrian( const Glib::ustring & pathfilename )
{
	// Load .trian
	vgTrian::Loader loader;
	std::pair< bool, vgd::Shp< vgd::node::TriSet > > retVal = loader.loadTrian( std::string(pathfilename.c_str()) );

	if ( !retVal.first )
	{
		return false;
	}

	// Setup scene
	using vgd::node::Material;

	vgd::Shp< Material > material = Material::create("material");
	material->setDiffuse( vgm::Vec3f(204.f/255.f, 51.f/255.f, 51.f/255.f) );
	material->setSpecular( vgm::Vec3f(1.f, 1.f, 1.f) );
	material->setShininess( 1.f );

	getScene()->addChild( material );
	getScene()->addChild( retVal.second );
	(retVal.second)->computeNormals();

	return true;
}

// @todo share code with vgio::helpers.cpp
const bool myCanvas::loadTrian2( const Glib::ustring & pathfilename, bool crypted)
{
	// Load .trian
	vgTrian::Loader loader;
	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;

	try
	{
		if( crypted )
		{
			vgd::Shp< std::vector<char> > inBuffer = vgio::readFile( pathfilename );
			if( inBuffer->empty() )
			{
				return false;
			}

			vgd::Shp< std::vector< char > > outBuffer( new std::vector< char > );

			vgAlg::actions::Decrypt decrypt;
			decrypt.setInitialize( "vgsdkViewerGTK", inBuffer, outBuffer );
			decrypt.execute();

			retVal = loader.load( pathfilename.c_str(), outBuffer );
		}
		else
		{
			retVal = loader.load( pathfilename.c_str() );
		}
	}
	catch(std::runtime_error e)
	{
		return false;
	}

	if ( !retVal.first )
	{
		return false;
	}

	// Setup scene
	getScene()->addChild( retVal.second );

	return true;
}

} // namespace vgTest

} //namespace vgsdkTestGtk

