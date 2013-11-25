// VGSDK - Copyright (C) 2008-2013, Nicolas Papier.
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

#include <glc_gtkmm/glc_gtkmm.hpp>

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgUI/Canvas.hpp>

#include <vgd/event/detail/GlobalButtonStateSet.hpp>

#include <vgSDL/event/device/Joystick.hpp>

#include "vgGTK/vgGTK.hpp"
#include "vgGTK/event/device/Keyboard.hpp"
#include "vgGTK/event/device/Mouse.hpp"
#include "vgGTK/event/device/Timer.hpp"
#include "vgGTK/node/ActionsMenu.hpp"


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
struct GenericCanvas : public Gtk::DrawingArea, public BaseCanvasType, public boost::signals::trackable
{

	/**
	 * @brief	Constructor that builds a canvas with its own OpenGL context.
	 */
	GenericCanvas()
	:	m_showMenu( false )
	{
		// vgLogDebug("Creates vgGTK::Canvas.");
		set_events( Gdk::SCROLL_MASK | Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK );
		set_flags( Gtk::CAN_FOCUS );
		grab_focus();

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
		m_showMenu( false )
	{
		// vgLogDebug("Creates vgGTK::Canvas.");
		set_events( Gdk::SCROLL_MASK | Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK );
		set_flags( Gtk::CAN_FOCUS );
		grab_focus();

		//vgAlg::actions::SelectedNode::getSelectedNodeObject()->signal_action_changed.connect( sigc::mem_fun(this, &GenericCanvas::onActionChanged) );
		vgAlg::actions::SelectedNode::getSelectedNodeObject()->signal_action_changed.connect( boost::bind( &GenericCanvas::onActionChanged, this, _1 ) );
	}

	/**
	 * @brief	Destructor
	 */
	virtual ~GenericCanvas()
	{
		BaseCanvasType::shutdownVGSDK();
	}

	/**
	 * @name	Overrides
	 */
	//@{
	void initDevices( const uint devices )
	{
		// Creates device instances so we will receive vgd events.
		if ( devices & Keyboard )
		{
			addDevice( vgd::makeShp(new vgGTK::event::device::Keyboard(this)) );
		}

		if ( devices & Mouse )
		{
			addDevice( vgd::makeShp(new vgGTK::event::device::Mouse(this)) );
		}

		if ( devices & Timer )
		{
			addDevice( vgd::makeShp(new vgGTK::event::device::Timer()) );
		}

		if ( devices & Joystick )
		{
			vgd::Shp< vgSDL::event::device::Joystick >	joystick = vgSDL::event::device::Joystick::get(0);

			// Adds joystick (if present)
			if( joystick )
			{
				addDevice( joystick );
			}
			else
			{
				vgLogWarning( "No joystick found." );
			}
		}
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
			return false;
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

			// Call base class.
			return BaseCanvasType::setFullscreen( wantFullscreen );
		}
	}

	void refreshForced( const vgUI::Canvas::WaitType wait = vgUI::Canvas::ASYNCHRONOUS )
	{
		Glib::RefPtr< Gdk::Window >	window = get_window();
		
		if( window )
		{
			if( !window->is_visible() )
			{
				window->show();
			}

			// Mark the window for painting. This will trigger an asynchronous refresh.
			window->invalidate_region( get_window()->get_visible_region(), false );

			// In the case of a synchronous refresh, we process all updates right now.
			if( wait == SYNCHRONOUS )
			{
				gdk_window_process_all_updates();
			}
		}
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
	glc_drawable_t * createDrawable()
	{
		return glc_gtkmm_drawable_create( this );
	}

	void destroyDrawable( glc_drawable_t * drawable )
	{
		glc_gtkmm_drawable_destroy( drawable );
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


	bool on_focus_in_event( GdkEventFocus * event )
	{
		vgd::event::detail::GlobalButtonStateSet::clear();
		return Gtk::DrawingArea::on_focus_in_event( event );
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


	bool onCursorTimeout()
	{
		hideCursor();
		return false;
	}

};


} // namespace vgGTK

#endif // #ifndef _VGGTK_GENERICCANVAS_HPP

