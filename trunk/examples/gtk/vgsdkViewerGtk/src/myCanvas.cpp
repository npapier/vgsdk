// VGSDK - Copyright (C) 2008, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgsdkViewerGtk/myCanvas.hpp"

#include <vgd/basic/FilenameExtractor.hpp>
#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgd/node/DirectionalLight.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/TriSet.hpp>
#include <vgd/visitor/Find.hpp>
#include <vgeGL/engine/Engine.hpp>
#include <vgeGL/technique/RayCasting.hpp>
//#include <vgCollada/Reader.hpp>
#include <vgDebug/Global.hpp>
#include <vgObj/Loader.hpp>
#include <vgTrian/Loader.hpp>



namespace vgsdkViewerGtk
{



myCanvas::myCanvas()
{
	set_size_request( 1024, 768 );

	createDefaultLights();
 	createClearFrameBuffer();
}



void myCanvas::initialize()
{
	// SETUP

	/* no more needed
	using vgd::node::ClearFrameBuffer;
	vgd::Shp< ClearFrameBuffer > clearFrameBuffer = ClearFrameBuffer::create("clearFrameBuffer");

	// Creates and swithes on a directional light.
	using vgd::node::DirectionalLight;
	vgd::Shp< DirectionalLight > light1 = DirectionalLight::create("light1");
	light1->setOn( true );
	light1->setDirection( vgm::Vec3f(0.f, 0.f, -1.f) );

	vgd::Shp< DirectionalLight > light2 = DirectionalLight::create("light2");
	light2->setMultiAttributeIndex( 1 );
	light2->setOn( true );
	light2->setDirection( vgm::Vec3f(0.f, 0.f, 1.f) );
	*/

	// DRAWSTYLE & LIGHTMODEL
//	using vgd::node::DrawStyle;
//	using vgd::node::LightModel;
//	vgd::Shp< DrawStyle > drawStyle = DrawStyle::create("DRAWSTYLE");
//	vgd::Shp< LightModel > lightModel = LightModel::create("LIGHTMODEL");

	/* no more needed
	// Adds clearFrameBuffer and lights to the setup node.
	getSetup()->insertChild( clearFrameBuffer );

	// lights don't move this the scene
	getSetup()->insertChild( light1, 2 );
	getSetup()->insertChild( light2, 2 );

	// lights are moving with the scene
	//getSetup()->addChild( light1 );
	//getSetup()->addChild( light2 );
	*/

//	getSetup()->addChild( drawStyle );
//	getSetup()->addChild( lightModel );

	getSceneTransformation()->setBindingsToDefaults2();

	// shape/mesh
	//viewAll();
}



void myCanvas::clearScene()
{
	// Changes the cursor
// @todo	::wxBeginBusyCursor();

	m_filenames.clear();
	getScene()->removeAllChildren();
	vgDebug::get().logStatus( "Scene cleared." );

	// Changes the cursor
// @todo	::wxEndBusyCursor();
}



const bool myCanvas::appendToScene( const Glib::ustring & filename, const bool mustCallViewAll )
{
	// Changes the cursor
// @todo	::wxBeginBusyCursor();

	const bool retVal = load( filename );

	if ( retVal )
	{
		if ( mustCallViewAll ) viewAll();

		refresh( REFRESH_FORCE, SYNCHRONOUS );
		m_filenames.push_back( filename );
	}

	// Changes the cursor
// @todo	::wxEndBusyCursor();

	return retVal;
}



const bool myCanvas::appendToScene( const Strings & pathfilenames, const bool mustCallViewAll )
{
	// Changes the cursor
// @todo	::wxBeginBusyCursor();

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
// @todo	::wxEndBusyCursor();

	return retVal;
}



const bool myCanvas::isEmpty() const
{
	return getScene()->getNumChildren() == 0;
}



const bool myCanvas::reloadScene()
{
	// Changes the cursor
// @todo	::wxBeginBusyCursor();

	const Strings filenames = m_filenames;

	clearScene();

	const bool retVal = appendToScene( filenames, false );

	// Changes the cursor
// @todo	::wxEndBusyCursor();

	return retVal;

}



const bool myCanvas::load( const Glib::ustring & pathfilename )
{
	// Changes the cursor
// @todo	::wxBeginBusyCursor();

	//


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
	else if ( extension.compare( ".trian2" ) == 0 )
	{
		bRetVal = loadTrian2( pathfilename );
	}
	else if ( extension.compare( ".dae" ) == 0 )
	{
		bRetVal = loadCollada( pathfilename );
	}
	else if( extension.compare( ".obj" ) == 0 )
	{
		bRetVal = loadObj( pathfilename );
	}
	else
	{
		bRetVal = false;

		vgDebug::get().logWarning( "Unknown file extension in %s.", pathfilename.c_str() );
	}


	// Perform post loading actions that depend on the result.
	if ( bRetVal )
	{
		// Shows in the log that the file has been loaded.
		vgDebug::get().logStatus( "File %s loaded.", pathfilename.c_str() );
	}
	else
	{
		// Shows in the log that something has gone wrong.
		vgDebug::get().logWarning( "Unable to load file %s.", pathfilename.c_str() );
	}

	// Changes the cursor
// @todo	::wxEndBusyCursor();

	return bRetVal;
}



const bool myCanvas::loadCollada( const Glib::ustring & pathfilename )
{
	// Load .DAE
/*	vgCollada::Reader reader;
	const bool retVal = reader.load( pathfilename.c_str() );*/

	// Setup scene
	// @todo
	//getScene()->addChild( retVal.second );

//	return retVal;
	return false;
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

	return ( true );
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
	material->setColor( Material::DIFFUSE, vgm::Vec3f(204.f/255.f, 51.f/255.f, 51.f/255.f) );
	material->setColor( Material::SPECULAR, vgm::Vec3f(1.f, 1.f, 1.f) );
	material->setShininess( 1.f );

	getScene()->addChild( material );
	getScene()->addChild( retVal.second );
	(retVal.second)->computeNormals();

	return true;
}



const bool myCanvas::loadTrian2( const Glib::ustring & pathfilename )
{
	// Load .trian
	vgTrian::Loader loader;
	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;

	retVal = loader.loadTrian2( pathfilename.c_str() );

	if ( !retVal.first )
	{
		return false;
	}

	// Setup scene
	getScene()->addChild( retVal.second );

	return true;
}



} // namespace vgsdkViewerGtk
