// VGSDK - Copyright (C) 2008, 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGGTK_GENERICCANVAS_HPP
#define _VGGTK_GENERICCANVAS_HPP

#include <gtkmm/drawingarea.h>
#include <gtkmm/window.h>
#include <vgDebug/convenience.hpp>
#include <vgUI/Canvas.hpp>

#include "vgGTK/vgGTK.hpp"
#include "vgGTK/event/SignalHandler.hpp"
#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#ifdef WIN32
	#define	USE_GLC
	#undef	USE_GTKGLEXT

	//#include <glc/glc.hpp>
	#include <glc_gtkmm/glc_gtkmm.hpp>
#else
	#undef	USE_GLC
	#define	USE_GTKGLEXT

struct glc_t;

	#include <gdk/gdkgl.h>
	#include <gtk/gtkgl.h>
#endif



namespace vgGTK
{



/**
 * @brief	Implements a generic rendering canvas based on Gtk::DrawingArea.
 *
 * It is meant to specialize vgUI::Canvas, vgUI::BasicViewer or vgUI::BasicManipulator.
 *
 * @todo	Check if querying for gtk and gdk contexts is time consuming.
 * @todo	Implement/debug vgSDK finalization.
 */
template< typename BaseCanvasType >
struct GenericCanvas : public Gtk::DrawingArea, public BaseCanvasType, public event::SignalHandler
{

	/**
	 * @brief	Constructor that builds a canvas with it own OpenGL context.
	 */
	GenericCanvas()
//#ifdef USE_GLC
	:	m_glc( 0 )
//#endif
	{
		// vgLogDebug("Creates vgGTK::Canvas.");
		set_events( Gdk::SCROLL_MASK | Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK );
		set_flags( Gtk::CAN_FOCUS );
		grab_focus();

#ifdef USE_GTKGLEXT
		setGlCapability( GTK_WIDGET(gobj()) );
//#else
#endif
		store( signal_focus_in_event().connect( ::sigc::mem_fun(this, &GenericCanvas::onFocusEvent) )	);
	}

	/**
	 * @brief	Constructor that builds a canvas with an OpenGL context sharing resources with
	 * 		the given canvas.
	 *
	 * @param	sharedCanvas	a pointer to the canvas for sharing
	 */
	template< typename SharedCanvasType >
	GenericCanvas( const SharedCanvasType * sharedCanvas )
	:	vgUI::Canvas( sharedCanvas ),
//#ifdef USE_GLC
		m_glc( 0 )
//#endif
	{
		// vgLogDebug("Creates vgGTK::Canvas.");
		set_events( Gdk::SCROLL_MASK | Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK );
		set_flags( Gtk::CAN_FOCUS );
		grab_focus();
		
#ifdef USE_GTKGLEXT
		GdkGLContext * glContext = gtk_widget_get_gl_context( GTK_WIDGET(sharedCanvas->gobj()) );
		assert( glContext != 0 && "Shared canvas has no OpenGL capability." );

		setGlCapability( GTK_WIDGET(gobj()), glContext );
#else
		// @todo sharing
		assert( false && "Sharing not yet implemented !!!" );
#endif
		store( signal_focus_in_event().connect( ::sigc::mem_fun(this, &GenericCanvas::onFocusEvent) )	);
	}

	/**
	 * @brief	Destructor
	 */
	virtual ~GenericCanvas();


	/**
	 * @name	Overrides
	 */
	//@{
	const bool setCurrent()
	{
		//vgLogDebug("vgGTK::Canvas::setCurrent");

#ifdef USE_GTKGLEXT
		GdkGLContext	* glContext  = gtk_widget_get_gl_context( GTK_WIDGET(gobj()) );
		GdkGLDrawable	* glDrawable = gtk_widget_get_gl_drawable( GTK_WIDGET(gobj()) );

		const bool retVal = gdk_gl_drawable_gl_begin( glDrawable, glContext );
#else

		const bool retVal = (m_glc != 0) ? glc_set_current( m_glc ) : false;
		if ( retVal == false )
		{
			vgLogDebug("glc_set_current returns false");
		}

#endif
		// gle must be made current
		if ( retVal )
		{
			// glc context has been made current. gle must be current too.
			if ( gleGetCurrent() != &BaseCanvasType::getGleContext() )
			{
				gleSetCurrent( &BaseCanvasType::getGleContext() );
			}
			//else nothing to do (already current)
		}
		else
		{
			// gle must be not current.
			gleSetCurrent( 0 );
		}

		return retVal;
	}


	const bool unsetCurrent()
	{
		//vgLogDebug("vgGTK::Canvas::unsetCurrent");

#ifdef USE_GTKGLEXT
		GdkGLDrawable	* glDrawable = gtk_widget_get_gl_drawable( GTK_WIDGET(gobj()) );

		gdk_gl_drawable_gl_end( glDrawable );

		const bool retVal = true;
#else

		const bool retVal = (m_glc != 0) ? glc_unset_current( m_glc ) : false;
		gleSetCurrent( 0 );

		// To be able to modify/recompile GLSL shaders in gDEBugger.
		//const bool retVal = true;
#endif
		return retVal;
	}


	const bool isCurrent()
	{
		//vgLogDebug("vgGTK::Canvas::isCurrent");

#ifdef USE_GTKGLEXT
		GdkGLContext	* glContext  = gtk_widget_get_gl_context( GTK_WIDGET(gobj()) );

		return (gdk_gl_context_get_current() == glContext);
#else
/*		assert(		(m_glc == 0) ||
					((m_glc != 0) && (glc_is_current(m_glc) == (gleGetCurrent()==&BaseCanvasType::getGleContext()))) );
*/
		return (m_glc != 0) ? glc_is_current( m_glc ) : false;
#endif
	}


	void swapBuffer()
	{
		//vgLogDebug("vgGTK::Canvas::swapBuffer");

#ifdef USE_GTKGLEXT
		GdkGLDrawable	* glDrawable = gtk_widget_get_gl_drawable( GTK_WIDGET(gobj()) );

		if( gdk_gl_drawable_is_double_buffered(glDrawable) )
		{
			gdk_gl_drawable_swap_buffers(glDrawable);
		}
		else
		{
			glFlush();
		}
#else
		if ( m_glc != 0 )
		{
			glc_swap( m_glc );
		}
		else
		{
			vgLogDebug("vgGTK::Canvas::swapBuffer called without a glc context.");
		}
#endif
	}



	/**
	 * @pre top level window must be a Gtk::Window.
	 */
	const bool setFullscreen( const bool wantFullscreen = true )
	{
		// Retrieves the top level window.
		Gtk::Container	* container				= get_toplevel();
		Gtk::Window		* topLevel				= dynamic_cast< Gtk::Window * >( container );

		assert( topLevel != 0 );


		// Stops refreshs.
		topLevel->get_window()->freeze_updates();


		// Configures the layout.
		if( wantFullscreen )
		{
			//
			topLevel->get_child()->hide_all();

			// We want to see the canvas. So we walk from the canvas to the top level window
			// and show each.
			for( Gtk::Widget * widget = this; widget != topLevel; widget = widget->get_parent() )
			{
				widget->show();
			}

			//
			topLevel->set_decorated(false);
			topLevel->fullscreen();
			topLevel->set_keep_above(true);
		}
		else
		{
			topLevel->set_keep_above(false);
			topLevel->unfullscreen();
			topLevel->set_decorated(true);

			topLevel->get_child()->show_all();	
		}

		// Refresh the window again.
		topLevel->get_window()->thaw_updates();

		// Updates the current state.
		return glc_drawable_set_fullscreen( m_glc, wantFullscreen ) != 0;
	}

	const bool isFullscreen()
	{
		return glc_drawable_is_fullscreen( m_glc ) != 0;
	}
	//@}


protected:

	/**
	 * @name	vgUI::Canvas overrides
	 */
	//@{

	void doRefresh()
	{
		Glib::RefPtr< Gdk::Window >	window = get_window();
		
		if( window )
		{
			window->invalidate_region( get_window()->get_visible_region(), false );
			gdk_window_process_all_updates();
		}
	}


	void sendRefresh()
	{
		Glib::RefPtr< Gdk::Window >	window = get_window();
		
		if( window )
		{
			window->invalidate_region( get_window()->get_visible_region(), false );
		}
	}


	const bool startOpenGLContext()
	{
		// Tests if glc context is already created
		if ( m_glc == 0 )
		{
#ifdef USE_GLC
			// glc context is not already created, creates a new one

			// First creates the drawable from the canvas
			glc_drawable_t * drawable	= glc_gtkmm_drawable_create( this );
			if ( drawable == 0 )
			{
				vgLogWarning("Unable to create the drawable.");
				return false;
			}

			// Next, creates the glc context
			m_glc						= glc_create( drawable );
			if ( m_glc == 0 )
			{
				vgLogWarning("Unable to create the glc context.");
				return false;
			}

			vgLogMessage("glc context successfully created.");

			// Next, mades the glc context current
			const bool isGLCCurrent = glc_set_current( m_glc );
			assert( isGLCCurrent && "Unable to set glc context current. This is not expected !!!" );

			vgLogMessage("glc context made current.");
#else
			setCurrent();

			if ( isCurrent() )
			{
				m_glc = reinterpret_cast<glc_t*>(1);
			}
			else
			{
				vgLogMessage("Unable to set OpenGL context current using gtkglext.");
				return false;
			}
#endif
			// Finally, initializes gle and sets it current
			vgLogMessage("Start gle initialization...");
			BaseCanvasType::getGleContext().clear();
			BaseCanvasType::getGleContext().initialize();
			vgLogMessage("gle initialization successfully completed.");

			gleSetCurrent( &BaseCanvasType::getGleContext() );

			assert( isCurrent() && "Internal error." );

			return true;
		}
		else
		{
			// glc context is already created
			const bool retVal = setCurrent();

			return retVal;
		}
	}


	const bool shutdownOpenGLContext()
	{
		if ( m_glc != 0 )
		{
#ifdef USE_GLC
			// Deletes glc context
			glc_destroy( m_glc );
			m_glc = 0;
			vgLogDebug("glc context deleted.");
#else
			m_glc = 0;
#endif
			// Cleans gle context
			BaseCanvasType::getGleContext().clear();
			vgLogDebug("gle context cleaned.");

			return true;
		}
		else
		{
			return false;
		}
	}

	//@}



	/**
	 * @name	Gtk::Widget overrides
	 */
	//@{
	bool on_button_press_event( GdkEventButton * event )
	{
		grab_focus();
	
		return Gtk::DrawingArea::on_button_press_event( event );
	}
	
	
	bool on_configure_event( GdkEventConfigure * event )
	{
		//vgLogDebug("vgGTK::Canvas::on_configure_event");

		// vgsdk resize
		const vgm::Vec2i v2iSize( event->width, event->height );

		if ( BaseCanvasType::startVGSDK() )
		{
			BaseCanvasType::resize( v2iSize );
			unsetCurrent();
		}

		// Default gtk processing
		return Gtk::DrawingArea::on_configure_event( event );
	}


	bool on_expose_event( GdkEventExpose * event )
	{
		//vgLogDebug("vgGTK::Canvas::on_expose_event()");
		
		// vgsdk paint
		const vgm::Vec2i v2iSize( get_width(), get_height() );

		if ( BaseCanvasType::startVGSDK() )
		{
			BaseCanvasType::paint( v2iSize, BaseCanvasType::getBoundingBoxUpdate() );
			unsetCurrent();
		}

		// Default gtk processing
		return Gtk::DrawingArea::on_expose_event( event );
	}


	/*void on_realize()
	{
		vgLogDebug("vgGTK::Canvas::on_realize:begin");

		// Default gtk processing
		Gtk::DrawingArea::on_realize();

		vgLogDebug("vgGTK::Canvas::on_realize:end");
	}*/

	//@}


private:

#ifdef USE_GTKGLEXT
	/**
	 * @brief	Sets the OpenGL rendering capability for the given widget.
	 *
	 * @param	widget		a pointer to the widget that will get OpenGL rendering capability
	 * @param	sharedContext	a pointer to a Gdk rendering context to use for sharing OpenGL objects, null if no sharing is desired
	 *
	 * @return	true on success or false otherwise
	 */
	static const bool setGlCapability( GtkWidget * widget, GdkGLContext * sharedContext = 0 )
	{
		GdkGLConfig * glconfig = 0;

		// Tries to create a double-buffered OpenGL configuration
		glconfig = gdk_gl_config_new_by_mode( (GdkGLConfigMode) (GDK_GL_MODE_RGB|GDK_GL_MODE_DEPTH|GDK_GL_MODE_DOUBLE) );
		if( glconfig == 0 )
		{
			g_print( "Cannot find the double-buffered visual.\nTrying single-buffered visual." );

			// Try single-buffered configuration
			glconfig = gdk_gl_config_new_by_mode( (GdkGLConfigMode) (GDK_GL_MODE_RGB|GDK_GL_MODE_DEPTH) );
			if( glconfig == 0 )
			{
				g_print( "No appropriate OpenGL-capable visual found.\n" );
				return false;
			}
		}


		// Enables OpenGL rendering on this widget
		bool ok;

		ok = gtk_widget_set_gl_capability( widget, glconfig, sharedContext, true, GDK_GL_RGBA_TYPE );
		if( ! ok )
		{
			g_print( "Unable to set gl capability to widget." );
			return false;
		}

		return true;
	}
#endif
//#else
	glc_t			*m_glc;
//#endif
	bool onFocusEvent( GdkEventFocus * event )
	{
		vgd::event::detail::GlobalButtonStateSet::clear();
		return false;
	}

};


template< typename BaseCanvasType >
GenericCanvas< BaseCanvasType >::~GenericCanvas()
{
	// vgLogDebug("Deletes vgGTK::Canvas.");

	BaseCanvasType::shutdownVGSDK();
}



} // namespace vgGTK

#endif // #ifndef _VGGTK_GENERICCANVAS_HPP
