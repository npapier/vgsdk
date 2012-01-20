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


} // namespace vgTest

} //namespace vgsdkTestGtk
