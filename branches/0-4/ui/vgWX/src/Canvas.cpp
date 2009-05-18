// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgWX/Canvas.hpp"

#if !wxUSE_GLCANVAS
#error Please set wxUSE_GLCANVAS to 1 in setup.h.
#endif

#include <vgDebug/Global.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#include <vgd/node/TriSet.hpp>
#include <vgd/visitor/FindFirstHelper.hpp>
#include <vgd/visitor/predicate/ByDirtyFlag.hpp>
#include <vgeGL/engine/Engine.hpp>

#include "vgWX/detail/ContextualMenu.hpp"



namespace vgWX
{



BEGIN_EVENT_TABLE( Canvas, wxGLCanvas )

	EVT_PAINT				( Canvas::OnPaint					)
	EVT_SIZE				( Canvas::OnSize					)
	EVT_ERASE_BACKGROUND	( Canvas::OnEraseBackground			)
   
	EVT_RIGHT_UP			( Canvas::OnRightUp					)
	EVT_MENU_RANGE			( wxID_HIGHEST + 1024, wxID_HIGHEST + 2048, Canvas::OnCtxMenu )
	
	EVT_IDLE				( Canvas::OnIdle					)

	//EVT_ENTER_WINDOW		( Canvas::OnEnterWindow )
	//EVT_KILL_FOCUS			( Canvas::OnKillFocus	)
	//EVT_SET_FOCUS			( Canvas::OnSetFocus	)

END_EVENT_TABLE()



void Canvas::setGleLogSystem( const GleLogSystem logger )
{
	m_gleLogSystem = logger;
}



const Canvas::GleLogSystem Canvas::getGleLogSystem()
{
	return m_gleLogSystem;
}



Canvas::Canvas(	wxWindow *parent,
				const wxString& name,
				const wxPoint& pos, const wxSize& size,
				long style,					
				int* gl_attrib,
				const wxWindowID id )
:	wxGLCanvas( parent, id, pos, size, style, name, 
				(gl_attrib != 0) ? gl_attrib : m_vgsdk_attrib ),
	vgeGL::engine::SceneManager( vgd::Shp< vgeGL::engine::Engine >( new vgeGL::engine::Engine() ) ),

	//m_canvasCount
	m_sharedCanvas				(	0						),	
	//m_vgsdk_attrib

	// m_gleLogSystem
	// m_gleLogFile
	m_gleContext				(	getGleOutputStream()	),

	m_bLocalInitializedVGSDK	(	false					),

	m_isContextualMenuEnabled	(	false					)
{
	assert( getCanvasCount() == 0 && "This is not the first canvas." );
	++m_canvasCount;
}



Canvas::Canvas(	wxWindow *parent,
				Canvas *pSharedCanvas,
				const wxString& name,
				const wxPoint& pos, const wxSize& size,
				long style,
				int* gl_attrib,
				const wxWindowID id )
:	wxGLCanvas( parent, pSharedCanvas, id, pos, size, style, name,
				(gl_attrib != 0) ? gl_attrib : m_vgsdk_attrib ),
	vgeGL::engine::SceneManager( vgd::Shp< vgeGL::engine::Engine >( new vgeGL::engine::Engine() ) ),

	//m_canvasCount
	m_sharedCanvas				(	pSharedCanvas			),	
	//m_vgsdk_attrib

	// m_gleLogSystem
	// m_gleLogFile
	m_gleContext				(	getGleOutputStream()	),

	m_bLocalInitializedVGSDK	(	false					),

	m_isContextualMenuEnabled	(	false					)
{
	assert( getCanvasCount() >= 1 && "This is the first canvas." );
	++m_canvasCount;
}



Canvas::~Canvas()
{
	assert( m_canvasCount > 0 );
	
	--m_canvasCount;

	if ( m_canvasCount == 0 )
	{
		// Last canvas is about to be destroy
		
		// Try to destroy OpenGL objects
		if ( enableVGSDK() )
		{
			getGLEngine()->getGLManager().clear();
			getGLEngine()->getGLSLManager().clear();
		}
		else
		{
			assert( false && "OpenGL context could not be made current. So OpenGL objects could not be released properly." );
			getGLEngine()->getGLManager().clear();
			getGLEngine()->getGLSLManager().clear();
		}

		// Global initialization of vgsdk must be redone for each "first canvas"
		m_bGlobalInitializedVGSDK = false;
	}
	//else don't destroy OpenGL objects, because they could be shared between OpenGL contexts.
}



void Canvas::enableContextualMenu( const bool bEnable )
{
	m_isContextualMenuEnabled = bEnable;
}



const bool Canvas::isContextualMenuEnabled() const
{
	return m_isContextualMenuEnabled;
}



wxMenu *Canvas::createContextualMenu() const
{
	// Retrieves information from raycasting
	const vgeGL::technique::RayCasting& rayCasting = getRayCastingTechnique();
	vgd::node::Node * node = rayCasting.getNearestHitNode();

	// Contextual menu creation
	wxMenu *ctxMenu = detail::createContextualMenu( this );

	if ( node != 0 )
	{
		wxMenu *subCtxMenu = detail::createContextualMenu( this, node->shpFromThis() );
	
		if ( subCtxMenu->GetMenuItemCount() >  0 )
		{
			ctxMenu->AppendSeparator();
			
			std::string menuName = "Algorithms and io on triset : ";
			menuName += node->getName();

			ctxMenu->Append( detail::wxID_CTX_ALGORITHMS_AND_IO, wxConvertMB2WX(menuName.c_str()), subCtxMenu );
		}
		else
		{
			delete subCtxMenu;
		}
	}

	return ctxMenu;
}



void Canvas::refresh( const RefreshType type, const WaitType wait )
{
	vgm::Vec2i	v2iSize( GetSize().GetWidth(), GetSize().GetHeight() );
	
	if ( type == REFRESH_IF_NEEDED )
	{
		// must schedule a refresh of the window ?
		std::pair< bool, vgd::Shp< vgd::node::Node > > retVal;
		retVal = vgd::visitor::findFirst( getRoot(), vgd::visitor::predicate::ByDirtyFlag() );

		if ( retVal.first )
		{
			// refresh must be done.

			// useful for debugging wrong dirty flags
			// vgDebug::get().logDebug("%s\n", retVal.second->getName().c_str() );

			if ( wait == ASYNCHRONOUS )
			{
				Refresh();
			}
			else
			{
				paint( v2iSize, getBoundingBoxUpdate() );
			}
		}
		// else refresh not needed
	}
	else
	{
		if ( wait == ASYNCHRONOUS )
		{
			Refresh();
		}
		else
		{
			paint( v2iSize, getBoundingBoxUpdate() );					// @todo don't work anytime (see OnPaint()).
		}
	}
}



void Canvas::paint( const vgm::Vec2i size, const bool bUpdateBoundingBox )
{
	//
	if ( !enableVGSDK() )
	{
		return;
	}
	
	// Call method initialize if needed (same code in OnSize()).
	if ( !m_bCallInitialize )
	{
		// First rendering, call initialize().
		gleGetCurrent()->reportGLErrors();
		
		initialize();
		
		gleGetCurrent()->reportGLErrors();

		//
		m_bCallInitialize = true;
	}

	while( getNumberOfFrames() > 0 )
	{
		gleGetCurrent()->reportGLErrors();
	
		::vgeGL::engine::SceneManager::paint( size, getBoundingBoxUpdate() );

		gleGetCurrent()->reportGLErrors();
	
		// Swap
		SwapBuffers();
		
		setNumberOfFrames( getNumberOfFrames()-1 );
	}
	
	// Reset the number of frame to render next time to 1.
	setNumberOfFrames( 1 );
}



const bool Canvas::onIdle()
{
	return false;
}



bool Canvas::Destroy()
{
	// Enables vgsdk
	const bool retVal = enableVGSDK();
	assert( retVal && "enableVGSDK() fails." );

	// Cleans the scene graph
	setRoot( vgd::node::Group::create("empty") );

	getGLEngine()->getGLManager().clear();
	getGLEngine()->getGLSLManager().clear();

	return wxGLCanvas::Destroy();
}



void Canvas::OnPaint( /*const*/ wxPaintEvent& /*event*/ )
{
	// This is a dummy, to avoid an endless succession of paint messages.
	// OnPaint handlers must always create a wxPaintDC.
	::wxPaintDC dc(this);

	//
	vgm::Vec2i	v2iSize( GetSize().GetWidth(), GetSize().GetHeight() );
	paint( v2iSize, getBoundingBoxUpdate() );
}



void Canvas::OnSize( /*const*/ wxSizeEvent& event )
{
	//this is also necessary to update the context on some platforms
	::wxGLCanvas::OnSize( event );

	//
	if ( !enableVGSDK() )
	{
		return;
	}
	
	// Call method initialize if needed (same code in OnSize()).
	if ( !m_bCallInitialize )
	{
		// First rendering, call initialize().
		gleGetCurrent()->reportGLErrors();
		
		initialize();
		
		gleGetCurrent()->reportGLErrors();

		//
		m_bCallInitialize = true;
	}
	
	//
	vgm::Vec2i	v2iSize( GetSize().GetWidth(), GetSize().GetHeight() );

	gleGetCurrent()->reportGLErrors();
			
	resize( v2iSize );

	gleGetCurrent()->reportGLErrors();	
}



void Canvas::OnEraseBackground( wxEraseEvent& /*event*/ )
{
    /* Do nothing, to avoid flashing on MSW */
}



void Canvas::OnRightUp( wxMouseEvent& event )
{
	assert( event.RightUp() );

	using vgd::event::detail::GlobalButtonStateSet;

	if (	isContextualMenuEnabled() &&
			GlobalButtonStateSet::get().isDown() == false	)
	{
		// Cast a ray
		/*vgd::node::Node *nodeUnderMouse =*/castRay( event.GetX(), event.GetY() );

		wxMenu *ctxMenu = createContextualMenu();

		PopupMenu( ctxMenu, event.GetX(), event.GetY() );
		
		delete ctxMenu;
	}
}



void Canvas::OnCtxMenu( wxCommandEvent& event )
{
	// Retrieves information from raycasting
	const vgeGL::technique::RayCasting& rayCasting = getRayCastingTechnique();
	vgd::node::Node * node = rayCasting.getNearestHitNode();

	// Processes event	
	detail::processContextualMenuEvent( this, event );
	
	if ( node != 0 )
	{	
		detail::processContextualMenuEvent(	this, event, node->shpFromThis() );
	}

	//
	refresh();
}



void Canvas::OnIdle( wxIdleEvent& event )
{
	const bool requestMoreIdleEvent = onIdle();
	event.RequestMore( requestMoreIdleEvent );
}



//void Canvas::OnEnterWindow( wxMouseEvent& event )
//{
//	//SetFocus();
//		
//	event.Skip();
//}



//void Canvas::OnKillFocus( wxFocusEvent& event )
//{
//	/*if ( HasCapture() )
//	{
//		ReleaseMouse();
//	}*/
//		
//	event.Skip();
//}



//void Canvas::OnSetFocus( wxFocusEvent& event )
//{
////	if ( HasCapture() == false )
////	{
////		CaptureMouse();
////	}
//		
//	event.Skip();
//}



const uint32 Canvas::getCanvasCount() const
{
	return m_canvasCount;
}



Canvas *Canvas::getSharedCanvas() const
{
	return m_sharedCanvas;
}



bool Canvas::enableVGSDK()
{
	// If parent window is hidden, OpenGL context could not be set current and an assert fails in SetCurrent() call.
	if ( !GetParent()->IsShown() )
	{
		return false;
	}

	// Activates OpenGL context
	SetCurrent();

	// Tests if the OpenGL context is current	
	if ( !isGLContextCurrent() )
	{
		return false;
	}

	// Initializes VGSDK if needed
	// @todo remove that
	if ( !m_bGlobalInitializedVGSDK )
	{
		// init. of OpenGL context already done and the OpenGL context is already current too.
		m_bGlobalInitializedVGSDK = true;
	}

	if ( !m_bLocalInitializedVGSDK )
	{
		// Initializes gle and sets it current
		m_gleContext.clear();

		m_gleContext.initialize();

		gleSetCurrent( &m_gleContext );

		// Initializes vgeGL
		getGLEngine()->reset();

		// FIXME
		///@todo Remove setToDefaults().
		getGLEngine()->setToDefaults();

		// Theses two lines must go in setToDefaults()
		//vgd::Shp< vge::service::Service > paint = vge::service::Painter::create();
		//m_engine->evaluateTopStateWithoutTrace( paint, true /*isPreTraverse*/ ); //FIXME BUG BECAUSE SEPARATOR is evaluated pre and not post...
		//m_engine->evaluateTopStateWithoutTrace( paint, false /*isPreTraverse*/ ); //FIXME BUG BECAUSE SEPARATOR is evaluated pre and not post...

		//
		m_bLocalInitializedVGSDK = true;

		// Checks OpenGL requirements for vgsdk
		if ( m_gleContext.isGL_VERSION_1_5 == false )
		{
			vgDebug::get().logDebug("You don't have the basic requirements for vgsdk, i.e. at least OpenGL version 1.5.");
			vgDebug::get().logError("You don't have the basic requirements for vgsdk, i.e. at least OpenGL version 1.5.");
		}
		else if ( m_gleContext.isGL_VERSION_2_0 == false )
		{
			vgDebug::get().logDebug("You don't have the full requirements for vgsdk, i.e. at least OpenGL version 2.0.");
			vgDebug::get().logWarning("You don't have the full requirements for vgsdk, i.e. at least OpenGL version 2.0.");
		}
	}

	// gle must be made current (only if not yet)
	if ( gleGetCurrent() != &m_gleContext )
	{
		gleSetCurrent( &m_gleContext );
	}

	return true;
}



uint32 Canvas::m_canvasCount = 0;



int	Canvas::m_vgsdk_attrib[] = {
			WX_GL_RGBA,
			WX_GL_DOUBLEBUFFER,
			WX_GL_DEPTH_SIZE, 24,
			WX_GL_STENCIL_SIZE, 8,
			0 };



Canvas::GleLogSystem Canvas::m_gleLogSystem = GLE_FILE_IN_VAR;



std::ofstream Canvas::m_gleLogFile;



std::ostream* Canvas::getGleOutputStream()
{
	const GleLogSystem currentGleLogSystem = getGleLogSystem();

	if ( currentGleLogSystem == GLE_FILE )
	{
		// Opens gle.txt if not already done
		if ( m_gleLogFile.is_open() == false )
		{
			m_gleLogFile.open("gle.txt");
		}

		return &m_gleLogFile;
	}
	else if ( currentGleLogSystem == GLE_FILE_IN_VAR )
	{
		// Opens gle.txt if not already done
		if ( m_gleLogFile.is_open() == false )
		{
			m_gleLogFile.open("../var/gle.txt");
		}

		return &m_gleLogFile;
	}
	else if ( currentGleLogSystem == GLE_COUT )
	{
		return &std::cout;
	}
	else
	{
		assert( false && "vgWX::Canvas: Unsupported gle log system." );
		return &std::cout;
	}
}



bool Canvas::m_bGlobalInitializedVGSDK = false;



} // namespace vgWX
