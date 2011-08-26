// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGGTK_GENERICCANVAS_HPP
#define _VGGTK_GENERICCANVAS_HPP

#include <boost/bind.hpp>
#include <boost/signal.hpp>

#include <gdk/gdkkeysyms.h>
#include <gdkmm/cursor.h>
#include <glibmm/main.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/window.h>

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgDebug/convenience.hpp>
#include <vgUI/Canvas.hpp>

#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#include "vgGTK/vgGTK.hpp"

#include <vgGTK/event/SignalHandler.hpp>
#include <vgGTK/node/ActionsMenu.hpp>

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



namespace
{

void drawWarningMessage( Cairo::RefPtr<Cairo::Context> cr, GdkEventExpose * event )
{
	// clear
	cr->save();
	cr->set_operator( Cairo::OPERATOR_CLEAR );
	cr->paint();
	cr->restore();

	// draw text
	const float centerY = static_cast<float>(event->area.height) / 2.f;

	cr->save();
	cr->select_font_face( "serif", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_BOLD );
	cr->set_font_size( 32.f );
	cr->set_source_rgb( 1.f, 1.f, 1.f );

	const std::string text1( "Unable to draw scene." );
	cr->move_to( 5.f, centerY - 32.f );
	cr->show_text( text1 );

	const std::string text2( "Please check the requirements for the graphics card and its driver." );
	cr->move_to( 5.f, centerY );
	cr->show_text( text2 );

	cr->restore();
}

}



/**
 * @brief	Implements a generic rendering canvas based on Gtk::DrawingArea.
 *
 * It is meant to specialize vgUI::Canvas, vgUI::BasicViewer or vgUI::BasicManipulator.
 *
 * @todo	Check if querying for gtk and gdk contexts is time consuming.
 * @todo	Implement/debug vgSDK finalization.
 */
template< typename BaseCanvasType >
struct GenericCanvas : public Gtk::DrawingArea, public BaseCanvasType, public event::SignalHandler, public boost::signals::trackable
{

	/**
	 * @brief	Constructor that builds a canvas with it own OpenGL context.
	 */
	GenericCanvas()
//#ifdef USE_GLC
	:	m_glc( 0 ),
		m_showMenu( false )
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

		//vgAlg::actions::SelectedNode::getSelectedNodeObject()->signal_action_changed.connect( sigc::mem_fun(this, &GenericCanvas::onActionChanged) );
		vgAlg::actions::SelectedNode::getSelectedNodeObject()->signal_action_changed.connect( boost::bind( &GenericCanvas::onActionChanged, this, _1 ) );
	}

	/**
	 * @brief	Constructor that builds a canvas with an OpenGL context sharing resources with
	 * 			the given canvas.
	 *
	 * @param	sharedCanvas	a pointer to the canvas for sharing
	 */
	GenericCanvas( const vgUI::Canvas * sharedCanvas )
	:	BaseCanvasType( sharedCanvas ),
//#ifdef USE_GLC
		m_glc( 0 ),
		m_showMenu( false )
//#endif
	{
		// vgLogDebug("Creates vgGTK::Canvas.");
		set_events( Gdk::SCROLL_MASK | Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK );
		set_flags( Gtk::CAN_FOCUS );
		grab_focus();

#ifdef USE_GTKGLEXT
		GdkGLContext * glContext = gtk_widget_get_gl_context( GTK_WIDGET(sharedCanvas->gobj()) );
		vgAssertN( glContext != 0, "Shared canvas has no OpenGL capability." );

		setGlCapability( GTK_WIDGET(gobj()), glContext );
#else
#endif
		store( signal_focus_in_event().connect( ::sigc::mem_fun(this, &GenericCanvas::onFocusEvent) )	);

		//vgAlg::actions::SelectedNode::getSelectedNodeObject()->signal_action_changed.connect( sigc::mem_fun(this, &GenericCanvas::onActionChanged) );
		vgAlg::actions::SelectedNode::getSelectedNodeObject()->signal_action_changed.connect( boost::bind( &GenericCanvas::onActionChanged, this, _1 ) );
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

//#define USE_GDEBUGGER
	const bool unsetCurrent()
	{
		//vgLogDebug("vgGTK::Canvas::unsetCurrent");

#ifdef USE_GTKGLEXT
		GdkGLDrawable	* glDrawable = gtk_widget_get_gl_drawable( GTK_WIDGET(gobj()) );

		gdk_gl_drawable_gl_end( glDrawable );

		const bool retVal = true;
#else

	#ifdef USE_GDEBUGGER
		// code path to be able to modify/recompile GLSL shaders in gDEBugger.
		const bool retVal = true;
		gleSetCurrent( 0 );
	#else
		// normal code path
		const bool retVal = (m_glc != 0) ? glc_unset_current( m_glc ) : false;
		gleSetCurrent( 0 );
	#endif
#endif
		return retVal;
	}


	const bool isCurrent() const
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
		if ( wantFullscreen == isFullscreen() )
		{
			// Nothing to do
			return true;
		}

		// Retrieves the top level window.
		Gtk::Window	* topLevel	= dynamic_cast< Gtk::Window * >( get_toplevel() );
		
		if( !topLevel )
		{
			vgLogDebug("vgGTK::Canvas::setFullscreen called without a Gtk::Window as toplevel.");
		}
		else
		{
			// Stops refreshs.
			//topLevel->get_window()->freeze_updates();


			// Configures the layout.
			if( wantFullscreen )
			{
				// Desctivated !
				// Each application is responsible to manage widget visibility in order to provide a proper full-screen mode.
				//
				//topLevel->get_child()->hide_all();
				//
				//// We want to see the canvas. So we walk from the canvas to the top level window
				//// and show each.
				//for( Gtk::Widget * widget = this; widget != topLevel; widget = widget->get_parent() )
				//{
				//	widget->show();
				//}

				topLevel->set_decorated(false);
				topLevel->fullscreen();
				topLevel->set_keep_above(true);
			}
			else
			{
				topLevel->set_keep_above(false);
				topLevel->unfullscreen();
				topLevel->set_decorated(true);

				// Desactivated !
				// Each application is responsible to manage widget visibility in order to provide a proper full-screen mode.
				//
				//topLevel->get_child()->show_all();
			}

			// Refresh the window again.
			//topLevel->get_window()->thaw_updates();
		}

#ifdef USE_GTKGLEXT
		return false;
#else
		// Updates the current state.
		if ( m_glc )
		{
			return glc_drawable_set_fullscreen( m_glc, wantFullscreen ) != 0;
		}
		else
		{
			return false;
		}
#endif
	}

	const bool isFullscreen()
	{
#ifdef USE_GTKGLEXT
		return false;
#else
		if ( m_glc )
		{
			return glc_drawable_is_fullscreen( m_glc ) != 0;
		}
		else
		{
			return false;
		}
#endif
	}
	//@}

	/**
	* @brief enable/disable popup menu
	*
	* @param show	true to enable menu, false otherwise.
	*/
	void setShowMenu( const bool show )
	{
		if( m_showMenu != show)
		{
			m_showMenu = show;
			if( m_showMenu )
			{
				m_actionsMenu = vgd::makeShp( new vgGTK::node::ActionsMenu( vgGTK::node::CANVAS ) );
				m_actionsMenu->setCanvas( this );
				m_actionNodeConnection = signal_button_press_event().connect( ::sigc::mem_fun(m_actionsMenu.get(), &vgGTK::node::ActionsMenu::onBoutonPressEvent) );
			}
			else
			{
				m_actionNodeConnection.disconnect();
			}
		}
	}

	const bool getShowMenu() const
	{
		return m_showMenu;
	}

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

			// Sets the desired propetry for the context
			const vgeGL::engine::GLContextProperties& requestedProperties = m_requestedGLContextProperties;
			drawable->stereo = requestedProperties.enableQuadBufferStereo();

			// Next, creates the glc context (shared or not)
			m_glc = glc_create_shared( drawable, m_sharedCanvas ? dynamic_cast< const GenericCanvas * >(m_sharedCanvas)->m_glc : 0 );

			if ( m_glc == 0 )
			{
				glc_gtkmm_drawable_destroy( drawable );
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

			// Analyses current OpenGL context
			GLboolean glbool;
			glGetBooleanv( GL_STEREO, &glbool );
			if ( glbool )
			{
				vgLogMessage("OpenGL context with stereo support");
				m_currentGLContextProperties = vgeGL::engine::GLContextProperties(true);
			}
			else
			{
				m_currentGLContextProperties = vgeGL::engine::GLContextProperties(false);
				vgLogMessage("OpenGL context without stereo support");
			}
			m_hasCurrentGLContextProperties = true;

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
			// Cleans gle context
			BaseCanvasType::getGleContext().clear();
			gleSetCurrent(0);
			vgLogDebug("gle context cleaned.");

#ifdef USE_GLC
			// Deletes glc context
			glc_destroy( m_glc );
			m_glc = 0;
			vgLogDebug("glc context deleted.");
#else
			m_glc = 0;
#endif

			return true;
		}
		else
		{
			return false;
		}
	}

	const bool hasAnOpenGLContext() const { return m_glc != 0; }
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
		else
		{
			Glib::RefPtr<Gdk::Window> window = get_window();
			if ( window )
			{
				Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
				drawWarningMessage( cr, event);
			}
		}

		// Default gtk processing
		return Gtk::DrawingArea::on_expose_event( event );
	}


// Applications should manage that.
/*	bool on_key_release_event( GdkEventKey * event )
	{
		if( event->keyval == GDK_Escape && isFullscreen() )
		{
			setFullscreen( false );
		}

		return Gtk::DrawingArea::on_key_release_event( event );
	}*/


	bool on_motion_notify_event( GdkEventMotion * event )
	{
		// Resets the canvas cursor and starts the timeout for cursor hidding.
		get_window()->set_cursor();
		m_cursorTimeout.disconnect();
		m_cursorTimeout = Glib::signal_timeout().connect_seconds( sigc::mem_fun(this, &GenericCanvas< BaseCanvasType >::onCursorTimeout), 3 );

		return Gtk::DrawingArea::on_motion_notify_event( event );
	}


	void on_realize()
	{
		Gtk::DrawingArea::on_realize();
		hideCursor();
	}


	void on_unrealize()
	{
		BaseCanvasType::shutdownVGSDK();

		// Default gtk processing
		Gtk::DrawingArea::on_unrealize();
	}

	//@}

	void onActionChanged( vgAlg::actions::ActionOnNode action )
	{
		switch( action )
		{
			case vgAlg::actions::REFRESH:
				refreshForced();
				break;
		}
	}


private:

	vgd::Shp< vgGTK::node::ActionsMenu > m_actionsMenu;	///< The popup menu.

	sigc::connection	m_cursorTimeout;		///< The connect to the timeout signal used to hide the cursor.

	sigc::connection	m_actionNodeConnection; ///< The connect to the popup menu mouse event.
	bool				m_showMenu;

	/**
	 * @brief	Hides the cursor.
	 */
	void hideCursor()
	{
		// Change this for the new Gdk::BLANK_CURSOR type when switching to a newer gdkmm.
		static const Gdk::Cursor	blankCursor( Gdk::Pixmap::create(get_window(), 1, 1, 1), Gdk::Pixmap::create(get_window(), 1, 1, 1), Gdk::Color(), Gdk::Color(), 0, 0 );

		Gtk::Window	* toplevel	= dynamic_cast< Gtk::Window * >( get_toplevel() );

		if( toplevel && toplevel->property_is_active() )
		{
			get_window()->set_cursor( blankCursor );
		}
		else
		{
			get_window()->set_cursor();
		}
	}

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

	bool onCursorTimeout()
	{
		hideCursor();
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

