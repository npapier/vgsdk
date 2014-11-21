// VGSDK - Copyright (C) 2012, 2013, 2014, Guillaume Brocker, Nicolas Papier, Philippe Sengchanpheng
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier
// Author Philippe Sengchanpheng

#ifndef _VGSDL_GENERICCANVAS_HPP_
#define _VGSDL_GENERICCANVAS_HPP_

#include <sdl.h>

#include <glc_sdl/glc_sdl.hpp>

#include <vgd/Shp.hpp>

#include "vgSDL/event/device/Joystick.hpp"
#include "vgSDL/event/device/Keyboard.hpp"
#include "vgSDL/event/device/Mouse.hpp"
#include "vgSDL/event/device/Timer.hpp"

namespace vgSDL
{

/*namespace
{

	void drawWarningMessage(Cairo::RefPtr<Cairo::Context> cr, GdkEventExpose * event)
	{
		// clear
		cr->save();
		cr->set_operator(Cairo::OPERATOR_CLEAR);
		cr->paint();
		cr->restore();

		// draw text
		const float centerY = static_cast<float>(event->area.height) / 2.f;

		cr->save();
		cr->select_font_face("serif", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_BOLD);
		cr->set_font_size(32.f);
		cr->set_source_rgb(1.f, 1.f, 1.f);

		const std::string text1("Unable to draw scene.");
		cr->move_to(5.f, centerY - 32.f);
		cr->show_text(text1);

		const std::string text2("Please check the requirements for the graphics card and its driver.");
		cr->move_to(5.f, centerY);
		cr->show_text(text2);

		cr->restore();
	}

}*/

/**
 * @brief	Implements a generic rendering canvas based on SDL_Surface with its own openGL context.
 *
 * It is meant to specialize into vgSDL::Canvas, vgSDL::BasicViewer or vgSDL::BasicManipulator.
 *
 * @todo contextual menu ?
 * @todo const bool setFullscreen( const bool wantFullscreen = true )
 * @todo cursor (hide, timeout)
 */
template< typename CanvasT >
struct GenericCanvas : public CanvasT
{
	void initSDL()
	{
		if (SDL_WasInit(SDL_INIT_VIDEO) == 0)
		{
			if (SDL_Init(SDL_INIT_VIDEO) != 0)
			{
				vgLogDebug("Unable to initialize SDL : %s\n", SDL_GetError());
				return;
			}
		}

		//Set up screen 
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		m_screen = SDL_SetVideoMode(800, 600, 16, SDL_OPENGL);
		if (!m_screen)
		{
			vgLogDebug("Unable to set video mode: %s\n", SDL_GetError());
			return;
		}
	}

    /**
     * @brief	Constructor that builds a canvas with its own OpenGL context.
	 *
	 */
	explicit GenericCanvas()
	{
		initSDL();
	}


	/**
	 * @brief	Constructor that builds a canvas with an OpenGL context sharing resources with
	 * 			the given canvas.
	 *
	 * @param	sharedCanvas	a pointer to the canvas for sharing
	 */
	GenericCanvas( const vgUI::Canvas * sharedCanvas)
		: CanvasT( sharedCanvas )
    {
		initSDL();
		vgAssertN(false, "Sharing canvas not yet implemented");
    }

    ~GenericCanvas()
    {
		if ( m_screen )	SDL_FreeSurface(m_screen);
        CanvasT::shutdownVGSDK();
    }

	void mainLoop()
	{
		bool haveToLoop = true;
		SDL_Event event;
		while ( haveToLoop )
		{
			// @todo SDL_WaitEvent
			const int result = SDL_PollEvent(&event);
			if (result == 0)
				continue;

			switch (event.type)
			{
				case SDL_VIDEORESIZE:
				{
					SDL_ResizeEvent *r = &(event.resize);
					const vgm::Vec2i v2iSize(r->w, r->h);
					if (CanvasT::startVGSDK())
					{
						CanvasT::resize(v2iSize);
						unsetCurrent();
					}
					break;
				}

				case SDL_VIDEOEXPOSE:
				{
					SDL_ExposeEvent *e = &(event.expose);
					const vgm::Vec2i v2iSize(m_screen->w, m_screen->h);

					if (CanvasT::startVGSDK())
					{
						CanvasT::paint(v2iSize, CanvasT::getBoundingBoxUpdate());
						unsetCurrent();
					}
					break;
				}

				case SDL_KEYDOWN:
				case SDL_KEYUP:
					event::device::Keyboard::handleEvent(event);
					break;

				case SDL_MOUSEMOTION:
					event::device::Mouse::handleEvent(event.motion);
					refreshForced(SYNCHRONOUS);
					break;

				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
					event::device::Mouse::handleEvent(event.button);
					break;

				//@todo mousebuttonup/down



				case SDL_QUIT:
					haveToLoop = false;
					break;
			}
		}
	}


	void initDevices( const uint devices )
	{
		// Creates device instances so we will receive vgd events.
		if ( devices & vgd::event::DeviceManager::Keyboard )
		{
			addDevice( vgSDL::event::device::Keyboard::get(0) );
		}

		if ( devices & vgd::event::DeviceManager::Mouse )
		{
			addDevice( vgSDL::event::device::Mouse::get(0) );
		}

	//	@todo doesn't work on sdl 1 because there's no current openGL context (another thread)
	/*	if ( devices & vgd::event::DeviceManager::Timer )
		{
			addDevice( vgd::makeShp(new vgSDL::event::device::Timer()) );
		}
	
	*/ 
		if ( devices & vgd::event::DeviceManager::Joystick )
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


	void refreshForced( const vgUI::Canvas::WaitType wait = vgUI::Canvas::ASYNCHRONOUS )
	{
		if (wait == vgUI::Canvas::SYNCHRONOUS)
		{
			if (startVGSDK())
			{
				const vgm::Vec2i v2iSize(m_screen->w, m_screen->h);
				CanvasT::paint(v2iSize, CanvasT::getBoundingBoxUpdate());
				unsetCurrent();
			}
			/* @todo for each startVGSDK()
			else
			{
				Glib::RefPtr<Gdk::Window> window = get_window();
				if (window)
				{
					Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
					drawWarningMessage(cr, event);
				}
			}*/
		}
		else
		{
			SDL_UpdateRect(m_screen, 0, 0, 0, 0);
		}
	}


	/*bool on_focus_in_event(GdkEventFocus * event)
	{
		vgd::event::detail::GlobalButtonStateSet::clear();
		return Gtk::DrawingArea::on_focus_in_event(event);
	}*/

protected:

	SDL_Surface * 	m_screen;

	/**
	* @name	vgUI::Canvas specialization
	*/
	//@{
	glc_drawable_t * createDrawable()
	{
		return glc_sdl_drawable_create(0);
	}

	void destroyDrawable(glc_drawable_t * drawable)
	{
		glc_sdl_drawable_destroy(drawable);
	}
	//@}
};


} // namespace vgSDL

#endif // _VGSDL_GENERICCANVAS_HPP_
