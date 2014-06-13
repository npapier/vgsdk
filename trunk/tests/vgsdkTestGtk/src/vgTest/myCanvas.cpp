// VGSDK - Copyright (C) 2008, 2014, Guillaume Brocker, Nicolas Papier, Maxime Peresson.
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
#include <vgd/node/DirectionalLight.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/TriSet.hpp>

#include <vgGTK/event/device/mouse.hpp>
#include <vgGTK/event/device/keyboard.hpp>
#include <vgGTK/event/device/timer.hpp>
#include <vgSDL/event/device/joystick.hpp>

#include <vgObj/Loader.hpp>
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
	//set_size_request( 1024, 768 );
	set_size_request( 640, 480 );

	// Scene graph initialization
	createOptionalNodes();
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


} // namespace vgTest

} //namespace vgsdkTestGtk
