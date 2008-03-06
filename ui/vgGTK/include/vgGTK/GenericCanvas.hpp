// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGGTK_GENERICCANVAS_HPP
#define _VGGTK_GENERICCANVAS_HPP

#include <gtkmm/drawingarea.h>
#include <vgUI/Canvas.hpp>

#include "vgGTK/vgGTK.hpp"

#include <gdk/gdkgl.h>
#include <gtk/gtkgl.h>



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
	{
		setGlCapability( GTK_WIDGET(gobj()) );
	}

	/**
	 * @brief	Constrcutor that builds a canvas with an OpenGL context sharing resources with
	 * 			the given canvas.
	 *
	 * @param	sharedCanvas	a pointer to the canvas for sharing
	 */
	template< typename SharedCanvasType >
	GenericCanvas( const SharedCanvasType * sharedCanvas )
	:	vgUI::Canvas( sharedCanvas )
	{
		GdkGLContext * glContext = gtk_widget_get_gl_context( GTK_WIDGET(sharedCanvas->gobj()) );
		assert( glContext != 0 && "Shared canvas has no OpenGL capability." );

		setGlCapability( GTK_WIDGET(gobj()), glContext );
	}

	/**
	 * @brief	Destructor
	 */
	virtual ~GenericCanvas()
	{}


	/**
	 * @name	Overrides
	 */
	//@{
	const bool setCurrent()
	{
		GdkGLContext	* glContext  = gtk_widget_get_gl_context( GTK_WIDGET(gobj()) );
		GdkGLDrawable	* glDrawable = gtk_widget_get_gl_drawable( GTK_WIDGET(gobj()) );

		const bool retVal = gdk_gl_drawable_gl_begin( glDrawable, glContext );

		// gle must be made current (only if not yet)
		if ( gleGetCurrent() != &m_gleContext )
		{
			gleSetCurrent( &m_gleContext );
		}

		return retVal;
	}

	const bool unsetCurrent()
	{
		GdkGLDrawable	* glDrawable = gtk_widget_get_gl_drawable( GTK_WIDGET(gobj()) );

		gdk_gl_drawable_gl_end( glDrawable );
		return true;
	}

	const bool isCurrent()
	{
		GdkGLContext	* glContext  = gtk_widget_get_gl_context( GTK_WIDGET(gobj()) );

		return (gdk_gl_context_get_current() == glContext);
	}

	void swapBuffer()
	{
		GdkGLDrawable	* glDrawable = gtk_widget_get_gl_drawable( GTK_WIDGET(gobj()) );

		if( gdk_gl_drawable_is_double_buffered(glDrawable) )
		{
			gdk_gl_drawable_swap_buffers(glDrawable);
		}
		else
		{
			glFlush();
		}
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

	//@}
	/**
	 * @name	Gtk::Widget overrides
	 */
	//@{
	bool on_configure_event( GdkEventConfigure * event )
	{
		//
		vgm::Vec2i	v2iSize( event->width, event->height );

		resize( v2iSize );

		// Default processing
		return Gtk::DrawingArea::on_configure_event( event );
	}

	bool on_expose_event( GdkEventExpose * event )
	{
		//
		vgm::Vec2i	v2iSize( event->area.width, event->area.height );

		setCurrent();
		paint( v2iSize, getBoundingBoxUpdate() );

		return Gtk::DrawingArea::on_expose_event( event );
	}

	void on_realize()
	{
		Gtk::DrawingArea::on_realize();

		setCurrent();
		startVGSDK();

	//	get_toplevel()->signal_delete_event().connect( sigc::ptr_fun(&delete_cb) );
	//	get_toplevel()->signal_unmap().connect( sigc::ptr_fun(&unmap_cb) );
	//	get_toplevel()->signal_unmap().connect( sigc::mem_fun(this, &Canvas::topLevelUnmap) );
	}

	void on_unrealize()
	{
	//	setCurrent();
	//	shutdownVGSDK();

		Gtk::DrawingArea::on_unrealize();
	}

	bool on_unmap_event( GdkEventAny * event )
	{
		setCurrent();
		shutdownVGSDK();

		return Gtk::DrawingArea::on_unmap_event( event );
	}
	//@}


private:

	/**
	 * @brief	Sets the OpenGL rendering capability for the given widget.
	 *
	 * @param	widget			a pointer to the widget that will get OpenGL rendering capability
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


};



} // namespace vgGTK



#endif /*_VGGTK_GENERICCANVAS_HPP*/
