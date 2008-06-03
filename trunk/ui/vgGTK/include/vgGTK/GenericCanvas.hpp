// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGGTK_GENERICCANVAS_HPP
#define _VGGTK_GENERICCANVAS_HPP

#include <gtkmm/drawingarea.h>
#include <vgDebug/Global.hpp>
#include <vgUI/Canvas.hpp>

#include "vgGTK/vgGTK.hpp"

#ifdef WIN32
	#define	USE_GLC
	#undef	USE_GTKGLEXT

	//#include <glc/glc.hpp>
	#include <glc_gtkmm/glc_gtkmm.hpp>
#else
	#undef	USE_GLC
	#define	USE_GTKGLEXT

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
struct GenericCanvas : public Gtk::DrawingArea, public BaseCanvasType
{

	/**
	 * @brief	Constructor that builds a canvas with it own OpenGL context.
	 */
	GenericCanvas()
	:	m_glc( 0 )
	{
		vgDebug::get().logDebug("Creates vgGTK::Canvas.");

#ifdef USE_GTKGLEXT
		setGlCapability( GTK_WIDGET(gobj()) );
#else
#endif
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
		m_glc( 0 )
	{
		vgDebug::get().logDebug("Creates vgGTK::Canvas.");
#ifdef USE_GTKGLEXT
		GdkGLContext * glContext = gtk_widget_get_gl_context( GTK_WIDGET(sharedCanvas->gobj()) );
		assert( glContext != 0 && "Shared canvas has no OpenGL capability." );

		setGlCapability( GTK_WIDGET(gobj()), glContext );
#else
		// @todo sharing
		assert( false && "Sharing not yet implemented !!!" );
#endif
	}

	/**
	 * @brief	Destructor
	 */
	virtual ~GenericCanvas()
	{
		vgDebug::get().logDebug("Deletes vgGTK::Canvas.");

		shutdownVGSDK();
	}


	/**
	 * @name	Overrides
	 */
	//@{
	const bool setCurrent()
	{
		//vgDebug::get().logDebug("vgGTK::Canvas::setCurrent");

#ifdef USE_GTKGLEXT
		GdkGLContext	* glContext  = gtk_widget_get_gl_context( GTK_WIDGET(gobj()) );
		GdkGLDrawable	* glDrawable = gtk_widget_get_gl_drawable( GTK_WIDGET(gobj()) );

		const bool retVal = gdk_gl_drawable_gl_begin( glDrawable, glContext );
#else
		const bool retVal = (m_glc != 0) ? glc_set_current( m_glc ) : false;
#endif
		// gle must be made current
		if ( retVal )
		{
			// glc context has been made current. gle must be current too.
			if ( gleGetCurrent() != &m_gleContext )
			{
				gleSetCurrent( &m_gleContext );
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
		//vgDebug::get().logDebug("vgGTK::Canvas::unsetCurrent");

#ifdef USE_GTKGLEXT
		GdkGLDrawable	* glDrawable = gtk_widget_get_gl_drawable( GTK_WIDGET(gobj()) );

		gdk_gl_drawable_gl_end( glDrawable );

		const bool retVal = true;
#else
		const bool retVal = (m_glc != 0) ? glc_unset_current( m_glc ) : false;

		gleSetCurrent( 0 );
#endif
		return retVal;
	}


	const bool isCurrent()
	{
		//vgDebug::get().logDebug("vgGTK::Canvas::isCurrent");

#ifdef USE_GTKGLEXT
		GdkGLContext	* glContext  = gtk_widget_get_gl_context( GTK_WIDGET(gobj()) );

		return (gdk_gl_context_get_current() == glContext);
#else
		assert(		(m_glc == 0) ||
					((m_glc != 0) && (glc_is_current(m_glc) == (gleGetCurrent()==&m_gleContext))) );

		return (m_glc != 0) ? glc_is_current( m_glc ) : false;
#endif
	}


	void swapBuffer()
	{
		//vgDebug::get().logDebug("vgGTK::Canvas::swapBuffer");

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
			vgDebug::get().logDebug("vgGTK::Canvas::swapBuffer called without a glc context.");
		}
#endif
	}
	//@}


protected:

	/**
	 * @name	vgUI::Canvas overrides
	 */
	//@{

	void doRefresh()
	{
		get_window()->invalidate_region( get_window()->get_visible_region(), false );
		gdk_window_process_all_updates();
	}


	void sendRefresh()
	{
		get_window()->invalidate_region( get_window()->get_visible_region(), false );
	}


	const bool startOpenGLContext()
	{
		// Tests if glc context is already created
		if ( m_glc == 0 )
		{
			// glc context is not already created, creates a new one

			// First creates the drawable from the canvas
			glc_drawable_t * drawable	= glc_gtkmm_drawable_create( this );
			if ( drawable == 0 )
			{
				vgDebug::get().logWarning("Unable to create the drawable.");
				return false;
			}

			// Next, creates the glc context
			m_glc						= glc_create( drawable );
			if ( m_glc == 0 )
			{
				vgDebug::get().logWarning("Unable to create the glc context.");
				return false;
			}

			vgDebug::get().logMessage("glc context successfully created.");

			// Next, mades the glc context current
			const bool isGLCCurrent = glc_set_current( m_glc );
			assert( isGLCCurrent && "Unable to set glc context current. This is not expected !!!" );

			vgDebug::get().logMessage("glc context made current.");

			// Finally, initializes gle and sets it current
			vgDebug::get().logMessage("Start gle initialization...");
			m_gleContext.clear();
			m_gleContext.initialize();
			vgDebug::get().logMessage("gle initialization successfully completed.");

			gleSetCurrent( &m_gleContext );

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
			// Deletes glc context
			glc_destroy( m_glc );
			m_glc = 0;
			vgDebug::get().logDebug("glc context deleted.");

			// Cleans gle context
			m_gleContext.clear();
			vgDebug::get().logDebug("gle context cleaned.");

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
	bool on_configure_event( GdkEventConfigure * event )
	{
		//vgDebug::get().logDebug("vgGTK::Canvas::on_configure_event");
		
		// vgsdk resize
		const vgm::Vec2i v2iSize( event->width, event->height );

		if ( startVGSDK() )
		{
			resize( v2iSize );
		}

		//unsetCurrent();

		// Default gtk processing
		return Gtk::DrawingArea::on_configure_event( event );
	}


	bool on_expose_event( GdkEventExpose * event )
	{
		//vgDebug::get().logDebug("vgGTK::Canvas::on_expose_event()");
		
		// vgsdk paint
		const vgm::Vec2i v2iSize( get_width(), get_height() );

		if ( startVGSDK() )
		{
			paint( v2iSize, getBoundingBoxUpdate() );
		}

		//unsetCurrent();

		// Default gtk processing
		return Gtk::DrawingArea::on_expose_event( event );
	}


	/*void on_realize()
	{
		vgDebug::get().logDebug("vgGTK::Canvas::on_realize:begin");

		// Default gtk processing
		Gtk::DrawingArea::on_realize();

		vgDebug::get().logDebug("vgGTK::Canvas::on_realize:end");
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
#else
	glc_t			*m_glc;
#endif

};



} // namespace vgGTK



#endif // #ifndef _VGGTK_GENERICCANVAS_HPP