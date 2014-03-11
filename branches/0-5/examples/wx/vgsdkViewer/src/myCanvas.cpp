// VGSDK - Copyright (C) 2004-2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgsdkViewer/myCanvas.hpp"

#if !wxUSE_DRAG_AND_DROP
    #error This sample requires drag and drop support in the library
#endif

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
#include <vgTrian/Loader.hpp>

#include <wx/dnd.h>
#include <wx/log.h>
#include <wx/menu.h>
#include <wx/utils.h>




namespace vgsdkViewer
{



class myCanvas::DnDFile : public wxFileDropTarget
{
public:
    DnDFile( myCanvas* pOwner );

    virtual bool OnDropFiles(	wxCoord x, wxCoord y,
                             	const wxArrayString& filenames);

private:
    myCanvas *m_pOwner;
};



BEGIN_EVENT_TABLE(	myCanvas, vgWX::BasicManipulator	)
	EVT_CHAR	(	myCanvas::OnChar					)
END_EVENT_TABLE()



myCanvas::myCanvas(
					wxWindow *parent,
					const wxString& name,
					const wxPoint& pos, const wxSize& size,
					long style,					
					int* gl_attrib,
					const wxWindowID id ) :

	vgWX::BasicManipulator( parent, name, pos, size, style, gl_attrib, id )
{
	// DnD
	SetDropTarget( new DnDFile( this ) );
	
	//
	enableContextualMenu( true );
}



myCanvas::myCanvas(
					wxWindow *parent,
					Canvas *pSharedCanvas,
					const wxString& name,
					const wxPoint& pos, const wxSize& size,
					long style,					
					int* gl_attrib,
					const wxWindowID id ) :

	vgWX::BasicManipulator( parent, pSharedCanvas, name, pos, size, style, gl_attrib, id )
{
	// DnD
	SetDropTarget( new DnDFile( this ) );
	
	//
	enableContextualMenu( true );
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
	using vgd::node::DrawStyle;
	using vgd::node::LightModel;	
	vgd::Shp< DrawStyle > drawStyle = DrawStyle::create("DRAWSTYLE");
	vgd::Shp< LightModel > lightModel = LightModel::create("LIGHTMODEL");

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

	getSetup()->addChild( drawStyle );
	getSetup()->addChild( lightModel );

	// shape/mesh
	viewAll();

	//
	getGLEngine()->setGLSLEnabled();
}



void myCanvas::OnChar( wxKeyEvent& event )
{
	if ( event.GetKeyCode() == WXK_F5 )
	{
		reloadScene();
		refresh();
	}
	else
	{
		event.Skip();
	}
}



void myCanvas::clearScene()
{
	// Changes the cursor
	::wxBeginBusyCursor();	
	
	m_filenames.Clear();
	getScene()->removeAllChildren();

	// Changes the cursor
	::wxEndBusyCursor();
}



const bool myCanvas::appendToScene( const wxString& pathfilename, const bool mustCallViewAll )
{
	// Changes the cursor
	::wxBeginBusyCursor();
	
	refresh();

	const bool retVal = load( std::string(wxConvertWX2MB(pathfilename)) );
	
	if ( retVal )
	{
		if ( mustCallViewAll ) viewAll();
		
		refresh();
	}

	// Changes the cursor
	::wxEndBusyCursor();
	
	return retVal;
}



const bool myCanvas::appendToScene( wxArrayString pathfilenames, const bool mustCallViewAll )
{
	// Changes the cursor
	::wxBeginBusyCursor();
	
	refresh();
	
	bool retVal = true;

	const size_t nFiles = pathfilenames.GetCount();
	
	for ( size_t n = 0; n < nFiles; ++n ) 
	{
		const std::string pathfilename(wxConvertWX2MB(pathfilenames[n]));

		const bool lRetVal = load( pathfilename );
		
		if ( lRetVal )
		{
			m_filenames.Add( pathfilenames[n] );
			
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
	::wxEndBusyCursor();

	return retVal;
}



const bool myCanvas::reloadScene()
{
	// Changes the cursor
	::wxBeginBusyCursor();
	
	const wxArrayString filenames = m_filenames;
	
	clearScene();

	const bool retVal = appendToScene( filenames, false );

	// Changes the cursor
	::wxEndBusyCursor();
	
	return retVal;
}



const bool myCanvas::load( std::string pathfilename )
{
	// Changes the cursor
	::wxBeginBusyCursor();

	//
	vgd::basic::FilenameExtractor	extractor( pathfilename );
	
	const std::string extension = extractor.getExtension();

	bool bRetVal;
	
	if ( extension.compare( ".trian" ) == 0 )
	{
		bRetVal = loadTrian( pathfilename );
	}
	else if ( extension.compare( ".trian2" ) == 0 )
	{
		bRetVal = loadTrian2( pathfilename );
	}
	else if ( extension.compare( ".DAE" ) == 0 )
	{
		bRetVal = loadCollada( pathfilename );
	}
	else
	{
		bRetVal = false;

		vgDebug::get().logError( "Unknown file extension in %s", pathfilename.c_str() );
	}
	
	if ( bRetVal )
	{
		vgDebug::get().logStatus( "File %s loaded", pathfilename.c_str() );
	}
	else
	{
		vgDebug::get().logError( "Unable to load file %s", pathfilename.c_str() );
	}

	// Changes the cursor
	::wxEndBusyCursor();

	return bRetVal;
}



const bool myCanvas::loadTrian( std::string pathfilename )
{
	// Load .trian
	vgTrian::Loader loader;
	std::pair< bool, vgd::Shp< vgd::node::TriSet > > retVal = loader.loadTrian( pathfilename );

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



const bool myCanvas::loadTrian2( std::string pathfilename )
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



const bool myCanvas::loadCollada( std::string pathfilename )
{
	// Load .DAE
/*	vgCollada::Reader reader;
	const bool retVal = reader.load( pathfilename );*/

	// Setup scene
	// @todo
	//getScene()->addChild( retVal.second );

//	return retVal;
	return false;
}






// ********* DND *********
myCanvas::DnDFile::DnDFile( myCanvas *pOwner )
{ 
	m_pOwner = pOwner; 
}



bool myCanvas::DnDFile::OnDropFiles( wxCoord, wxCoord, const wxArrayString& filenames )
{
	// Changes the cursor
	::wxBeginBusyCursor();

	///@todo Asks if the scene must be cleared ?
	m_pOwner->clearScene();

	const bool retVal = m_pOwner->appendToScene( filenames );

	// Changes the cursor
	::wxEndBusyCursor();

	return retVal;
}



} // namespace vgsdkViewer
