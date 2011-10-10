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
//:	m_isEnabled
//:	m_eyeSeparation
//:	m_imageShift
: m_isRightEyeEnabled(true)
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
	// Apply stereoscopic parameters to scene graph

	// isEnabled
	if ( isEnabled() )
	{
		camera->setMode( vgd::node::Camera::QUAD_BUFFER );
	}
	else
	{
		camera->setMode( vgd::node::Camera::MONOSCOPIC );
	}

	// Eye separation
	camera->setEyeSeparation( getEyeSeparation() );

	// Image shift
	camera->setImageShift( getImageShift() );

	// Right eye enabled
	camera->setRightEye( isRightEyeEnabled() );
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

		// IS ENABLED
		bool isEnabled = settings.get< bool >( "isEnabled", true );
		setEnabled( isEnabled );

		// EYE SEPARATION
		float eyeSeparation = settings.get< float >( "eyeSeparation", 0.f );
		if ( isEyeSeparationValid(eyeSeparation) )
		{
			setEyeSeparation( eyeSeparation );
		}
		else
		{
			vgLogDebug2( "Invalid eye separation in file %s. Uses zero.", path.string().c_str() );
			setEyeSeparation( 0.f );
		}

		// IMAGE SHIFT
		float imageShift = settings.get< float >( "imageShift", 0.f );
		if ( isImageShiftValid(imageShift) )
		{
			setImageShift( imageShift );
		}
		else
		{
			vgLogDebug2( "Invalid image shift in file %s. Uses zero.", path.string().c_str() );
			setImageShift( 0.f );
		}

		// RIGHT EYE
		// only useful for debugging, so not serialized
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

		// IS ENABLED
		settings.put( "isEnabled", m_isEnabled );

		// EYE SEPARATION
		if ( isEyeSeparationValid(m_eyeSeparation) )
		{
			settings.put( "eyeSeparation", m_eyeSeparation );
		}
		else
		{
			settings.put( "eyeSeparation", 0.f );
			vgLogDebug2( "Invalid eye separation %f. Uses zero.", m_eyeSeparation );
		}

		// IMAGE SHIFT
		if ( isImageShiftValid(m_imageShift) )
		{
			settings.put( "imageShift", m_imageShift );
		}
		else
		{
			settings.put( "imageShift", 0.f );
			vgLogDebug2( "Invalid image shift %f. Uses zero.", m_imageShift );
		}

		// RIGHT EYE
		// only useful for debugging, so not serialized

		// Saves the settings
		bpt::ini_parser::write_ini( path.string(), settings );
	}
	catch( bpt::ini_parser::ini_parser_error & )
	{
		vgLogError2( "Error while writing file %s", path.string().c_str() );
	}
}


const bool StereoscopicSettings::isEnabled() const
{
	return m_isEnabled;
}

void StereoscopicSettings::setEnabled( const bool enabled )
{
	m_isEnabled = enabled;
}


const float StereoscopicSettings::getEyeSeparation() const
{
	return m_eyeSeparation;
}

void StereoscopicSettings::setEyeSeparation( const float eyeSeparation )
{
	m_eyeSeparation = eyeSeparation;
}



const float StereoscopicSettings::getImageShift() const
{
	return m_imageShift;
}

void StereoscopicSettings::setImageShift( const float imageShift)
{
	m_imageShift = imageShift;
}



const bool StereoscopicSettings::isRightEyeEnabled() const
{
	return m_isRightEyeEnabled;
}

void StereoscopicSettings::setRightEyeEnabled( const bool enabled )
{
	m_isRightEyeEnabled = enabled;
}



const bool StereoscopicSettings::isEyeSeparationValid( const float eyeSeparation )
{
	//const bool retVal =	(eyeSeparation >= 0);
	//return retVal;

	return true;
}



const bool StereoscopicSettings::isImageShiftValid( const float imageShift )
{
	const bool retVal =	(imageShift >= -100.f) &&
						(imageShift <= 100.f);
	return retVal;
}



} // namespace engine

} // namespace vge
