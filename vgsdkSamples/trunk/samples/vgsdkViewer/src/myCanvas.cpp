// VGSDK - Copyright (C) 2004, Nicolas Papier.
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
#include <vgd/node/Material.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/TransformSeparator.hpp>
#include <vgd/visitor/Find.hpp>
#include <vgeGL/technique/RayCasting.hpp>

#include <vgDebug/Global.hpp>
#include <vgTrian/Loader.hpp>

#include <wx/menu.h>
#include <wx/log.h>



namespace vgsdkViewer
{



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
	using namespace vgd::node;
	
	// SETUP
	vgd::Shp< ClearFrameBuffer > clearFrameBuffer = ClearFrameBuffer::create("clearFrameBuffer");
	
	// create and swith on a directional light.
	vgd::Shp< DirectionalLight > light1 = DirectionalLight::create("light1");
	light1->setOn( true );
	light1->setDirection( vgm::Vec3f(0.f, 0.f, -1.f) );

	vgd::Shp< DirectionalLight > light2 = DirectionalLight::create("light2");
	light2->setMultiAttributeIndex( 1 );
	light2->setOn( true );
	light2->setDirection( vgm::Vec3f(0.f, 0.f, 1.f) );
	
	// DRAWSTYLE
	vgd::Shp< DrawStyle > drawStyle = DrawStyle::create("DRAWSTYLE");
	vgd::Shp< LightModel > lightModel = LightModel::create("LIGHTMODEL");	

	// add clearFrameBuffer and light to the setup node.
	getSetup()->addChild( clearFrameBuffer );
	getSetup()->insertChild( light1, 2 );
	getSetup()->insertChild( light2, 2 );
	getSetup()->addChild( drawStyle );
	getSetup()->addChild( lightModel );
	
	// shape/mesh.

	viewAll();
}



void myCanvas::OnChar( wxKeyEvent& event )
{
	if ( event.KeyCode() == WXK_F5 )
	{
		reload();
		Refresh();
	}
	else if ( event.KeyCode() == 'g' )
	{
		writeGraphviz( false );
		vgDebug::get().logStatus( "Write scene graph.dot." );
	}
	else
	{
		event.Skip();
	}
}



wxMenu *myCanvas::createContextualMenu( const int32 xMouse, const int32 yMouse )
{
	SetCurrent();
		
	//
	wxMenu *ctxMenu;
	ctxMenu = Canvas::createContextualMenu( xMouse, yMouse );
	
	//
	//bool isDefined;
	//wxMenu *subMenu;

	// RayCasting
	// collector
	getNodeCollector().reset();
	getRoot()->traverse( getNodeCollector() );

	vgeGL::technique::RayCasting raycasting;
	getEngine()->resetEval();	
	raycasting.apply(	getEngine().get(), getNodeCollector().getTraverseElements(),
							xMouse, yMouse );

	if ( raycasting.getHitsSize() > 0 )
	{
		vgd::node::Node *pNode( raycasting.getNearestHitNode() );
		
		if ( pNode != 0 )
		{
			ctxMenu->Prepend( wxID_LOWEST-1, pNode->getName().c_str() );
		}
	}
	
	return ( ctxMenu );
}



/*void myCanvas::paint( const vgm::Vec2i size, const bool bUpdateBoundingBox )
{
	BasicManipulator::paint( size, bUpdateBoundingBox );
}*/



bool myCanvas::load( std::string pathfilename )
{
	vgd::basic::FilenameExtractor extractor( pathfilename );
	std::string							extension;
	
	extension	= extractor.getExtension();

	if ( extension.compare( ".trian" ) == 0 )
	{
		loadTrian( pathfilename );
		vgDebug::get().logStatus( "%s loaded.", pathfilename.c_str() );
	}
	else if ( extension.compare( ".trian2" ) == 0 )
	{
		loadTrian2( pathfilename );
		vgDebug::get().logStatus( "%s loaded.", pathfilename.c_str() );
	}
	else
	{
		vgDebug::get().logStatus( "Empty scene." );
	}

	return ( true );
}



bool myCanvas::loadTrian( std::string pathfilename )
{
	// Load .trian
	vgTrian::Loader loader;
	std::pair< bool, vgd::Shp< vgd::node::VertexShape > > retVal;

	retVal = loader.loadTrian( pathfilename.c_str() );
	
	if ( !retVal.first )
	{
		return false;
	}
	
	// Setup scene
	getScene()->addChild( retVal.second );
	(retVal.second)->computeNormals();
	
	return ( true );
}



bool myCanvas::loadTrian2( std::string pathfilename )
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
	
	return ( true );
}



void myCanvas::reload()
{
	getScene()->removeAllChildren();
	
	for(	uint32 i=0;
			i < m_filenames.size();
			++i
		)
	{
		// load
		load( m_filenames[i].c_str() );
	}
	
	Refresh();
}






// ********* DND *********
DnDFile::DnDFile( myCanvas *pOwner )
{ 
	m_pOwner = pOwner; 
}
    


bool DnDFile::OnDropFiles( wxCoord, wxCoord, const wxArrayString& filenames )
{
	size_t nFiles = filenames.GetCount();
	
	if ( nFiles > 0 )
	{
		m_pOwner->m_filenames.resize(0);
		m_pOwner->m_filenames.reserve(nFiles);
		
		for ( size_t n = 0; n < nFiles; n++ ) 
		{
			std::string str(filenames[n].c_str());
			m_pOwner->m_filenames.push_back( str );
		}
		
		m_pOwner->reload();
		
		m_pOwner->viewAll();
	
		return ( true );
	}
	else
	{
		return ( false );
	}
}


} // namespace vgsdkViewer
