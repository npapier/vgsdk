// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgWX/Canvas.hpp"

#include <wx/menu.h>

#if !wxUSE_GLCANVAS
#error Please set wxUSE_GLCANVAS to 1 in setup.h.
#endif

#include <vgDebug/Global.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/visitor/predicate/ByDirtyFlag.hpp>



namespace vgWX
{

// FIXME ???
std::ofstream Canvas::m_gleLog("gle.txt");



BEGIN_EVENT_TABLE( Canvas, wxGLCanvas )

	EVT_PAINT				( Canvas::OnPaint					)
	EVT_SIZE				( Canvas::OnSize					)
	EVT_ERASE_BACKGROUND	( Canvas::OnEraseBackground			)
   
	EVT_MOUSE_EVENTS		( Canvas::OnMouseEvent	)
	EVT_MENU_RANGE			( wxID_HIGHEST + 1024, wxID_HIGHEST + 2048, Canvas::OnCtxMenu )

	//EVT_ENTER_WINDOW		( Canvas::OnEnterWindow )
	//EVT_KILL_FOCUS		( Canvas::OnKillFocus	)
	//EVT_SET_FOCUS			( Canvas::OnSetFocus	)
END_EVENT_TABLE()



Canvas::Canvas(	wxWindow *parent,
				const wxString& name,
				const wxPoint& pos, const wxSize& size,
				long style,					
				int* gl_attrib,
				const wxWindowID id ) :
					
	wxGLCanvas( parent, id, pos, size, style, name, 
				(gl_attrib != 0) ? gl_attrib : m_vgsdk_attrib ),
	vgeGL::engine::SceneManager( vgd::Shp< vgeGL::engine::Engine >( new vgeGL::engine::Engine() ) ),

	//m_canvasCount
	//m_vgsdk_attrib

	//m_gleLog
	m_gleContext				(	&m_gleLog	),

	m_bLocalInitializedVGSDK	(	false		),

	m_isContextualMenuEnabled	(	false		)
{
	// Initialize the vgeGL::engine::Engine() if possible...
	// because on linux, OpenGL context could not be made current any times...
	getGLEngine()->reset();

	//
	assert( getCanvasCount() == 0 && "This is not the first canvas." );
	++m_canvasCount;
}



Canvas::Canvas(	wxWindow *parent,
				Canvas *pSharedCanvas,
				const wxString& name,
				const wxPoint& pos, const wxSize& size,
				long style,
				int* gl_attrib,
				const wxWindowID id ) :
				
	wxGLCanvas( parent, pSharedCanvas, id, pos, size, style, name,
				(gl_attrib != 0) ? gl_attrib : m_vgsdk_attrib ),
	vgeGL::engine::SceneManager( vgd::Shp< vgeGL::engine::Engine >( new vgeGL::engine::Engine() ) ),

	//m_vgsdk_attrib

	//m_gleLog
	m_gleContext				(	&m_gleLog	),

	m_bLocalInitializedVGSDK	(	false		),

	m_isContextualMenuEnabled	(	false		)
{
	// Initialize the vgeGL::engine::Engine() if possible...
	// because on linux, OpenGL context could not be made current any times...
	getGLEngine()->reset();
	
	//
	assert( getCanvasCount() >= 1 && "This is the first canvas." );
	++m_canvasCount;
}



Canvas::~Canvas()
{
	assert( m_canvasCount > 0 );
	
	--m_canvasCount;

	if ( m_canvasCount == 0 )
	{
		// Last canvas is about to be destroy => destroy OpenGL objects.
		if ( enableVGSDK() )
		{
			getGLEngine()->getGLManager().clear();
		}
		else
		{
			assert( false && "OpenGL context could not be made current. So OpenGL objects could not be released properly." );
		}
	}
	//else Don't destroy OpenGL objects, because they could be shared between OpenGL contexts.
}



void Canvas::enableContextualMenu( const bool bEnable )
{
	m_isContextualMenuEnabled = bEnable;
}



bool Canvas::isContextualMenuEnabled() const
{
	return ( m_isContextualMenuEnabled );
}



wxMenu *Canvas::createContextualMenu( const int32 xMouse, const int32 yMouse )
{
	using namespace vgd::node;
	
	wxMenu *ctxMenu = new wxMenu;

	//
	bool isDefined;
	wxMenu *subMenu;

	// DrawStyle
	subMenu = new wxMenu;

	vgd::Shp< DrawStyle > drawStyle( findFirstByType< DrawStyle >() );
		
	// drawStyle.shape

	subMenu->Append( wxID_CTX_DRAWSTYLE_NONE, _T("None"), _T("None"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_POINT, _T("Point"), _T("Point"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_FLAT, _T("Flat"), _T("Flat"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_SMOOTH, _T("Smooth"), _T("Smooth"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_WIREFRAME, _T("Wireframe"), _T("Wireframe"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_HIDDEN_LINE, _T("Hidden line"), _T("Hidden line"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_FLAT_HIDDEN_LINE, _T("Flat hidden line"), _T("Flat hidden line"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_SMOOTH_HIDDEN_LINE, _T("Smooth hidden line"), _T("Smooth hidden line"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_NEIGHBOUR, _T("Neighbour"), _T("Neighbour"), wxITEM_CHECK );

	if ( drawStyle.get() != 0 )
	{
		DrawStyle::ShapeValueType	shapeValue;
		
		isDefined = drawStyle->getShape( shapeValue );
		
		if ( isDefined )
		{
			subMenu->Check( wxID_CTX_DRAWSTYLE_NONE + shapeValue - DrawStyle::NONE, true );
		}
	}

	// drawStyle.normalLength
	subMenu->AppendSeparator();
	
	subMenu->Append( wxID_CTX_DRAWSTYLE_NORMALLENGTHNEGATIV, _T("-x"), _T("-x"), wxITEM_CHECK );	
	subMenu->Append( wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS8, _T("-8"), _T("-8"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS4, _T("-4"), _T("-4"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_NORMALLENGTH0, _T("0"), _T("0"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_NORMALLENGTH4, _T("4"), _T("4"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_NORMALLENGTH8, _T("8"), _T("8"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_NORMALLENGTHPOSITIV, _T("+x"), _T("+x"), wxITEM_CHECK );
	
	if ( drawStyle.get() != 0 )
	{
		DrawStyle::NormalLengthValueType	normalLengthValue;
		
		isDefined = drawStyle->getNormalLength( normalLengthValue );
		
		if ( isDefined )
		{
			if ( normalLengthValue < -8 )
			{
				subMenu->Check( wxID_CTX_DRAWSTYLE_NORMALLENGTHNEGATIV, true );
			}
			else if ( normalLengthValue == -8 )
			{
				subMenu->Check( wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS8, true );
			}
			else if ( normalLengthValue == -4 )
			{
				subMenu->Check( wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS4, true );
			}
			else if ( normalLengthValue == 0 )
			{
				subMenu->Check( wxID_CTX_DRAWSTYLE_NORMALLENGTH0, true );
			}
			else if ( normalLengthValue == 4 )
			{
				subMenu->Check( wxID_CTX_DRAWSTYLE_NORMALLENGTH4, true );
			}
			else if ( normalLengthValue == 8 )
			{
				subMenu->Check( wxID_CTX_DRAWSTYLE_NORMALLENGTH8, true );
			}
			else if ( normalLengthValue > 8 )
			{
				subMenu->Check( wxID_CTX_DRAWSTYLE_NORMALLENGTHPOSITIV, true );
			}			
		}
	}

	// drawStyle.showOrientation
	subMenu->AppendSeparator();
	
	subMenu->Append( wxID_CTX_DRAWSTYLE_SHOWORIENTATION, _T("Show orientation"), _T("Show orientation"), wxITEM_CHECK );

	if ( drawStyle.get() != 0 )
	{
		DrawStyle::ShowOrientationValueType	showOrientationValue;
		
		isDefined = drawStyle->getShowOrientation( showOrientationValue );
		
		if ( isDefined )
		{
			subMenu->Check( wxID_CTX_DRAWSTYLE_SHOWORIENTATION, true );
		}
	}

	// drawStyle.boundingBox
	subMenu->AppendSeparator();
	
	subMenu->Append( wxID_CTX_DRAWSTYLE_NO_BOUNDING_BOX, _T("No bounding box"), _T("No bounding box"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_OBJECT_SPACE, _T("Object space bounding box"), 
		_T("Object space bounding box"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_AA_OBJECT_SPACE, _T("Axis aligned object space bounding box"), 
		_T("Axis aligned object space bounding box"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_DRAWSTYLE_OBJECT_AND_AA_OBJECT_SPACE, _T("Object and axis aligned object space bounding box"),
		_T("Object and axis aligned object space bounding box"), wxITEM_CHECK );

	if ( drawStyle.get() != 0 )
	{
		DrawStyle::BoundingBoxValueType bbValue;
		
		isDefined = drawStyle->getBoundingBox( bbValue );
		
		if ( isDefined )
		{
			subMenu->Check( wxID_CTX_DRAWSTYLE_NO_BOUNDING_BOX + bbValue - DrawStyle::NO_BOUNDING_BOX, true );
		}
	}
	
	//
	ctxMenu->Append( wxID_CTX_DRAWSTYLE, _T("Drawing style"), subMenu );	


	// LightModel
	ctxMenu->AppendSeparator();
	
	subMenu = new wxMenu;
	
	vgd::Shp< LightModel > lightModel ( findFirstByType< LightModel >() );

	// lightModel.model
	subMenu->Append( wxID_CTX_LIGHTMODEL_MODEL_LIGHTING_OFF, _T("Lighting off"), _T("Lighting off"), wxITEM_CHECK );
	subMenu->Append( wxID_CTX_LIGHTMODEL_MODEL_STANDARD_PER_VERTEX, _T("Standard per vertex"), _T("Standard per vertex"), 
		wxITEM_CHECK );
	subMenu->Append( wxID_CTX_LIGHTMODEL_MODEL_STANDARD_PER_PIXEL, _T("Standard per pixel"), _T("Standard per vertex")
		, wxITEM_CHECK );
		
	if ( lightModel.get() != 0 )
	{
		LightModel::ModelValueType modelValue;
		
		isDefined = lightModel->getModel( modelValue );
		
		if ( isDefined )
		{
			switch ( modelValue )
			{
				case LightModel::LIGHTING_OFF:
					subMenu->Check( wxID_CTX_LIGHTMODEL_MODEL_LIGHTING_OFF, true );
					break;
		
				case LightModel::STANDARD_PER_VERTEX:
					subMenu->Check( wxID_CTX_LIGHTMODEL_MODEL_STANDARD_PER_VERTEX, true );
					break;
		
				case LightModel::STANDARD_PER_PIXEL:
					subMenu->Check( wxID_CTX_LIGHTMODEL_MODEL_STANDARD_PER_PIXEL, true );
					break;
					
				default:
					assert( false && "Unknown LightModel.model value." );
			}
		}
	}		
	
	// lightModel.viewer	
	subMenu->AppendSeparator();
	subMenu->Append(wxID_CTX_LIGHTMODEL_VIEWER, _T("Local viewer"), _T("Local viewer"), wxITEM_CHECK );

	if ( lightModel.get() != 0 )
	{
		LightModel::ViewerValueType viewerValue;
		isDefined = lightModel->getViewer( viewerValue );
		
		if ( isDefined )
		{
			ctxMenu->Check( wxID_CTX_LIGHTMODEL_VIEWER, viewerValue == LightModel::AT_EYE );
		}
	}
	
	// lightModel.twoSided
	subMenu->AppendSeparator();
	subMenu->Append(wxID_CTX_LIGHTMODEL_TWOSIDED, _T("Two sided"), _T("Two sided"), wxITEM_CHECK );
	
	if ( lightModel.get() != 0 )
	{
		LightModel::TwoSidedValueType twosidedValue;
		isDefined = lightModel->getTwoSided( twosidedValue );
		
		if ( isDefined )
		{
			ctxMenu->Check( wxID_CTX_LIGHTMODEL_TWOSIDED, twosidedValue );
		}
	}

	//	
	ctxMenu->Append( wxID_CTX_LIGHTMODEL_MODEL, _T("Lighting model"), subMenu );	

	return ( ctxMenu );
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
			paint( v2iSize, getBoundingBoxUpdate() );				
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

	//	
	vgm::Vec2i	v2iSize( GetSize().GetWidth(), GetSize().GetHeight() );

	while( getNumberOfFrames() > 0 )
	{
		gleGetCurrent()->reportGLErrors();
	
		::vgeGL::engine::SceneManager::paint( v2iSize, getBoundingBoxUpdate() );

		gleGetCurrent()->reportGLErrors();
	
		// Swap
		SwapBuffers();
		
		setNumberOfFrames( getNumberOfFrames()-1 );
	}
	
	// Reset the number of frame to render next time to 1.
	setNumberOfFrames( 1 );
}



void Canvas::OnPaint( /*const*/ wxPaintEvent& event )
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



void Canvas::OnEraseBackground( wxEraseEvent& event )
{
    /* Do nothing, to avoid flashing on MSW */
}



void Canvas::OnMouseEvent( wxMouseEvent& event )
{
	if ( isContextualMenuEnabled() && event.RightUp() )
	{
		wxMenu *ctxMenu = createContextualMenu( event.GetX(), event.GetY() );
		
		PopupMenu( ctxMenu, event.GetX(), event.GetY() );
		
		delete ctxMenu;
	}
}



void Canvas::OnCtxMenu( wxCommandEvent& event )
{
	using namespace vgd::node;
	
	switch ( event.GetId() )
	{
		// DrawStyle
		case wxID_CTX_DRAWSTYLE_NONE:
		case wxID_CTX_DRAWSTYLE_POINT:
		case wxID_CTX_DRAWSTYLE_FLAT:
		case wxID_CTX_DRAWSTYLE_SMOOTH:
		case wxID_CTX_DRAWSTYLE_WIREFRAME:
		case wxID_CTX_DRAWSTYLE_HIDDEN_LINE:
		case wxID_CTX_DRAWSTYLE_FLAT_HIDDEN_LINE:
		case wxID_CTX_DRAWSTYLE_SMOOTH_HIDDEN_LINE:
		case wxID_CTX_DRAWSTYLE_NEIGHBOUR:
		{
			vgd::Shp< DrawStyle >		drawStyle( findFirstByType< DrawStyle >() );
			
			if ( drawStyle.get() != 0 )
			{
				int32 value;
				value  = event.GetId() - wxID_CTX_DRAWSTYLE_NONE + DrawStyle::NONE;
	
				drawStyle->setShape( static_cast< DrawStyle::ShapeValueType >(value) );
			}
			break;
		}
		
		case wxID_CTX_DRAWSTYLE_NORMALLENGTHNEGATIV:
		case wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS8:
		case wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS4:
		case wxID_CTX_DRAWSTYLE_NORMALLENGTH0:
		case wxID_CTX_DRAWSTYLE_NORMALLENGTH4:
		case wxID_CTX_DRAWSTYLE_NORMALLENGTH8:
		case wxID_CTX_DRAWSTYLE_NORMALLENGTHPOSITIV:
		{
			vgd::Shp< DrawStyle >		drawStyle( findFirstByType< DrawStyle >() );
			
			if ( drawStyle.get() != 0 )
			{
				switch ( event.GetId() )
				{
					case wxID_CTX_DRAWSTYLE_NORMALLENGTHNEGATIV:
						drawStyle->setNormalLength( -15 );
						break;
					case wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS8:
						drawStyle->setNormalLength( -8 );
						break;
					case wxID_CTX_DRAWSTYLE_NORMALLENGTHMINUS4:
						drawStyle->setNormalLength( -4 );
						break;					
					case wxID_CTX_DRAWSTYLE_NORMALLENGTH0:
						drawStyle->setNormalLength( 0 );
						break;
					case wxID_CTX_DRAWSTYLE_NORMALLENGTH4:
						drawStyle->setNormalLength( 4 );
						break;					
					case wxID_CTX_DRAWSTYLE_NORMALLENGTH8:
						drawStyle->setNormalLength( 8 );
						break;					
					case wxID_CTX_DRAWSTYLE_NORMALLENGTHPOSITIV:
						drawStyle->setNormalLength( 15 );
						break;
					default:
						assert( false && "Unknown case" );
				}
			}
			break;
		}
		
		case wxID_CTX_DRAWSTYLE_SHOWORIENTATION:
		{
			vgd::Shp< DrawStyle >		drawStyle( findFirstByType< DrawStyle >() );
			
			if ( drawStyle.get() != 0 )
			{
				DrawStyle::ShowOrientationValueType value;
				bool isDefined = drawStyle->getShowOrientation( value );
				
				if ( isDefined )
				{
					drawStyle->setShowOrientation( !value );
				}
				else
				{
					drawStyle->setShowOrientation( true );
				}
			}
			break;
		}
		
		case wxID_CTX_DRAWSTYLE_NO_BOUNDING_BOX:
		case wxID_CTX_DRAWSTYLE_OBJECT_SPACE:
		case wxID_CTX_DRAWSTYLE_AA_OBJECT_SPACE:
		case wxID_CTX_DRAWSTYLE_OBJECT_AND_AA_OBJECT_SPACE:
		{
			vgd::Shp< DrawStyle >		drawStyle( findFirstByType< DrawStyle >() );
			
			if ( drawStyle.get() != 0 )
			{
				int32 value;
				value  = event.GetId() - wxID_CTX_DRAWSTYLE_NO_BOUNDING_BOX + DrawStyle::NO_BOUNDING_BOX;
	
				drawStyle->setBoundingBox( static_cast< DrawStyle::BoundingBoxValueType >(value) );
			}
			break;
		}


		// LightModel
		
		//
		case wxID_CTX_LIGHTMODEL_MODEL_LIGHTING_OFF:
		{
			vgd::Shp< LightModel >		lightModel( findFirstByType< LightModel >() );
			
			if ( lightModel.get() != 0 )
			{
				lightModel->setModel( LightModel::LIGHTING_OFF );
			}
			break;
		}

		case wxID_CTX_LIGHTMODEL_MODEL_STANDARD_PER_VERTEX:
		{
			vgd::Shp< LightModel >		lightModel( findFirstByType< LightModel >() );
			
			if ( lightModel.get() != 0 )
			{
				lightModel->setModel( LightModel::STANDARD_PER_VERTEX );
			}
			break;
		}		
		
		case wxID_CTX_LIGHTMODEL_MODEL_STANDARD_PER_PIXEL:				
		{
			vgd::Shp< LightModel >		lightModel( findFirstByType< LightModel >() );
			
			if ( lightModel.get() != 0 )
			{
				lightModel->setModel( LightModel::STANDARD_PER_PIXEL );
			}
			break;
		}
		
		//
		case wxID_CTX_LIGHTMODEL_VIEWER:
		{
			vgd::Shp< LightModel >		lightModel( findFirstByType< LightModel >() );
			
			if ( lightModel.get() != 0 )
			{
				LightModel::ViewerValueType value;
				bool isDefined = lightModel->getViewer( value );
				
				if ( isDefined )
				{
					if ( value == LightModel::AT_INFINITY )
					{
						lightModel->setViewer( LightModel::AT_EYE );
					}
					else
					{
						lightModel->setViewer( LightModel::AT_INFINITY );
					}
				}
				else
				{
					lightModel->setViewer( LightModel::AT_EYE );
				}
			}
			break;
		}

		//
		case wxID_CTX_LIGHTMODEL_TWOSIDED:
		{
			vgd::Shp< LightModel >		lightModel( findFirstByType< LightModel >() );
			
			if ( lightModel.get() != 0 )
			{
				bool value;
				bool isDefined = lightModel->getTwoSided( value );
				
				if ( isDefined )
				{
					lightModel->setTwoSided( !value );
				}
				else
				{
					lightModel->setTwoSided( true );
				}
			}

			break;
		}
	
		// default:
		// nothing to do
	}
	
	Refresh();	
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



uint32 Canvas::getCanvasCount() const
{
	return ( m_canvasCount );
}



bool Canvas::enableVGSDK()
{
	// Activate OpenGL context.
	SetCurrent();

	// Test if OpenGL context is current	
	if ( !isGLContextCurrent() )
	{
		return ( false );
	}

	// Initialize VGSDK if needed.
	if ( !m_bGlobalInitializedVGSDK )
	{
		// init. of OpenGL context already done and the OpenGL context is already current too.
	
		// init. gle
		m_gleContext.initialize();

		gleSetCurrent( &m_gleContext );
		
		m_bGlobalInitializedVGSDK = true;
	}
	
	if ( !m_bLocalInitializedVGSDK )
	{
		// init. vgeGL	
		getGLEngine()->reset();
	
		// FIXME
		getGLEngine()->setToDefaults(); //???????????????????????????????????????????????????????????????????? check if opengl is current.

		// Theses two lines must go in setToDefaults()
		//vgd::Shp< vge::service::Service > paint = vge::service::Painter::create();
		//m_engine->evaluateTopStateWithoutTrace( paint, true /*isPreTraverse*/ ); //FIXME BUG BECAUSE SEPARATOR is evaluated pre and not post...
		//m_engine->evaluateTopStateWithoutTrace( paint, false /*isPreTraverse*/ ); //FIXME BUG BECAUSE SEPARATOR is evaluated pre and not post...
		
		//
		m_bLocalInitializedVGSDK = true;
	}

	return ( true );
}



uint32 Canvas::m_canvasCount = 0;


int	Canvas::m_vgsdk_attrib[] = {
			WX_GL_RGBA,
			WX_GL_DOUBLEBUFFER,
			WX_GL_DEPTH_SIZE, 24,
			WX_GL_STENCIL_SIZE, 8,
			0 };


bool	Canvas::m_bGlobalInitializedVGSDK = false;


} // namespace vgWX
