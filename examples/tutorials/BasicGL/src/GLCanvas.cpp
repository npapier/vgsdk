// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "basicGL/GLCanvas.hpp"

#if !wxUSE_GLCANVAS
#error Please set wxUSE_GLCANVAS to 1 in setup.h.
#endif



namespace basicGL
{



BEGIN_EVENT_TABLE( GLCanvas, wxGLCanvas )
	EVT_PAINT				( GLCanvas::OnPaint )
	EVT_SIZE					( GLCanvas::OnSize )
   EVT_ERASE_BACKGROUND	( GLCanvas::OnEraseBackground )
END_EVENT_TABLE()



GLCanvas::GLCanvas(	wxWindow *parent, wxWindowID id, const wxPoint& pos,
							const wxSize& size, long style, const wxString& name, 
							int* gl_attrib ) :
	wxGLCanvas(parent, id, pos, size, style, name, gl_attrib)
{
}



void GLCanvas::OnPaint( /*const*/ wxPaintEvent& event )
{
	// This is a dummy, to avoid an endless succession of paint messages.
	// OnPaint handlers must always create a wxPaintDC.
	::wxPaintDC dc(this);

	// Gets the size of the canvas.
	wxSize size = GetSize();

	// OpenGL context is made current. OpenGL must be used only after calling this method !!!
	SetCurrent();

	// Initialize the projection matrix using the size of the canvas.
	// This could be done preferably in OnSize method
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -size.GetWidth()/2.f, size.GetWidth()/2.f, -size.GetHeight()/2.f, size.GetHeight()/2.f, -2.f, 2.f );
	
	// Initialize the viewport using the size of the canvas.
	glViewport( 0, 0, size.GetWidth(), size.GetHeight() );
	
	// Initialize the modelview matrix with identity.
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	// Clear the color buffer and the depth buffer.
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
	// Draw one triangle.
	glBegin( GL_TRIANGLES );
	
	glColor3f( 1.f, 0.f, 0.f );
	glVertex3f( -size.GetWidth()/2.f, -size.GetHeight()/2.f, 1.f );
	
	glColor3f( 0.f, 1.f, 0.f );	
	glVertex3f( size.GetWidth()/2.f, -size.GetHeight()/2.f, 1.f );
	
	glColor3f( 0.f, 0.f, 1.f );	
	glVertex3f( size.GetWidth()/2.f, size.GetHeight()/2.f, 1.f );
	
	glEnd();

	// Swap the color buffer.
	SwapBuffers();
}



void GLCanvas::OnSize( /*const*/ wxSizeEvent& event )
{
    // this is also necessary to update the context on some platforms
   ::wxGLCanvas::OnSize( event );
/*    
    // set GL viewport (not called by wxGLCanvas::OnSize on all platforms...)
    int w, h;
    GetClientSize(&w, &h);
#ifndef __WXMOTIF__
    if (GetContext())
#endif
    {
        SetCurrent();
        glViewport(0, 0, (GLint) w, (GLint) h);
    }
*/   	
}



void GLCanvas::OnEraseBackground( wxEraseEvent& event )
{
    /* Do nothing, to avoid flashing on MSW */
}



} // namespace basicGL
