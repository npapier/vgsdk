// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/engine/StereoscopicSettings.hpp"

#include <boost/filesystem/operations.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <sbf/path.hpp>

#include <vgDebug/convenience.hpp>
#include <vgd/node/Camera.hpp>

#include "vge/engine/SceneManager.hpp"



namespace
{
	const std::string SETTINGS_FILENAME = "stereoscopic-settings.ini";
}



namespace vge
{

namespace engine
{



StereoscopicSettings::StereoscopicSettings()
//:	m_eyeSeparation( 0.f )
{
	load();
}



void StereoscopicSettings::apply( vge::engine::SceneManager & sm ) const
{
	// Skips when no camera node has been found.
	using vgd::node::Camera;
	vgd::Shp< Camera > camera = sm.findFirstByType< Camera >();

	if( !camera )
	{
		return;
	}
	else
	{
		apply( camera );
	}
}



void StereoscopicSettings::apply( vgd::Shp< vgd::node::Camera > camera ) const
{
	// Apply stereoscopic paramaters to scene graph
	camera->setMode( vgd::node::Camera::QUAD_BUFFER );
	camera->setEyeSeparation( m_eyeSeparation );
}



void StereoscopicSettings::load()
{
	namespace bfs = boost::filesystem;
	namespace bpt = boost::property_tree;

	// Gets the path of the settings file.
	// Loads for 'var' if exists, otherwise from 'share'.
	const bfs::path varPath = sbf::path::get(sbf::path::Var) / SETTINGS_FILENAME;
	const bfs::path sharePath = sbf::path::get(sbf::path::Share) / SETTINGS_FILENAME;

	const bfs::path path = bfs::exists( varPath ) ? varPath : sharePath;

	try
	{
		// Loads the settings.
		boost::property_tree::ptree settings;
		bpt::ini_parser::read_ini( path.string(), settings );

		// EYE SEPARATION
		float eyeSeparation = settings.get< float >( "eyeSeparation" );
		if ( eyeSeparation >= 0.f )
		{
			m_eyeSeparation = eyeSeparation;
		}
		else
		{
			vgLogError2( "Invalid eye separation in file %s", path.string().c_str() );
			m_eyeSeparation = 0.f;
		}
	}
	catch( bpt::ini_parser::ini_parser_error & )
	{
		vgLogError2( "Error while reading file %s", path.string().c_str() );
	}
}



void StereoscopicSettings::save()
{
	namespace bfs = boost::filesystem;
	namespace bpt = boost::property_tree;

	// Gets the path of the settings file.
	const bfs::path path = sbf::path::getSafe(sbf::path::Var) / SETTINGS_FILENAME;

	try
	{
		// Creates the settings ptree.
		boost::property_tree::ptree settings;

		// EYE SEPARATION
		if ( m_eyeSeparation >= 0.f )
		{
			settings.put( "eyeSeparation", m_eyeSeparation );
		}
		else
		{
			settings.put( "eyeSeparation", 0.f );
			vgLogError2( "Invalid eye separation %f. Uses zero.", m_eyeSeparation );
		}

		// Saves the settings
		bpt::ini_parser::write_ini( path.string(), settings );
	}
	catch( bpt::ini_parser::ini_parser_error & )
	{
		vgLogError2( "Error while writing file %s", path.string().c_str() );
	}
}




} // namespace engine

} // namespace vge
