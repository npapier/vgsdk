// VGSDK - Copyright (C) 2012, 2013, 2014, Guillaume Brocker, Nicolas Papier, Philippe Sengchanpheng
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier
// Author Philippe Sengchanpheng

#ifndef _VGSDL_GENERICCANVAS_HPP_
#define _VGSDL_GENERICCANVAS_HPP_

#include <SDL.h>

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
#ifdef __OPENGLES2__
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#else
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
#endif



		// Create an application window with the following settings:
		m_window = SDL_CreateWindow(
			"An SDL2 window with OpenGL",	// window title
			SDL_WINDOWPOS_UNDEFINED,		// initial x position
			SDL_WINDOWPOS_UNDEFINED,		// initial y position
			640,							// width, in pixels
			480,							// height, in pixels
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
#ifdef __OPENGLES2__
#else
			//| SDL_GL_CONTEXT_DEBUG_FLAG
#endif

			);

		// Check that the window was successfully made
		if (!m_window)
		{
			vgLogDebug("Unable to create window: %s\n", SDL_GetError());
			return;
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE);
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
		CanvasT::shutdownVGSDK();
		if (m_window)	SDL_DestroyWindow(m_window);
    }

	void mainLoop()
	{
		// Simulate a resize event
		if (CanvasT::startVGSDK())
		{		
			int width, height;
			SDL_GetWindowSize(m_window, &width, &height);
			const vgm::Vec2i v2iSize(width, height);
			CanvasT::resize(v2iSize);
			unsetCurrent();
		}

		// Main loop
		bool haveToLoop = true;
		
		while ( haveToLoop )
		{
			haveToLoop = step();
		}
	}


	bool step()
	{
		bool haveToLoop = true;

		SDL_Event event;
		// @todo SDL_WaitEvent
		const int result = SDL_PollEvent(&event);
		if (result == 0)
			continue;

		if (event.type == SDL_WINDOWEVENT)
		{
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_SHOWN:
			{
				SDL_Log("Window %d shown", event.window.windowID);

				int width, height;
				SDL_GetWindowSize(m_window, &width, &height);
				const vgm::Vec2i v2iSize(width, height);

				if (CanvasT::startVGSDK())
				{
					CanvasT::paint(v2iSize, CanvasT::getBoundingBoxUpdate());
					unsetCurrent();
				}
				break;
			}
			case SDL_WINDOWEVENT_HIDDEN:
				SDL_Log("Window %d hidden", event.window.windowID);
				break;
			case SDL_WINDOWEVENT_EXPOSED:
			{
				int width, height;
				SDL_GetWindowSize(m_window, &width, &height);
				const vgm::Vec2i v2iSize(width, height);

				if (CanvasT::startVGSDK())
				{
					CanvasT::paint(v2iSize, CanvasT::getBoundingBoxUpdate());
					unsetCurrent();
				}
				break;
			}
			case SDL_WINDOWEVENT_MOVED:
				SDL_Log("Window %d moved to %d,%d",
					event.window.windowID, event.window.data1,
					event.window.data2);
				break;
			case SDL_WINDOWEVENT_RESIZED:
			{
				SDL_Log("Window %d resized to %dx%d",
					event.window.windowID, event.window.data1,
					event.window.data2);
				const vgm::Vec2i v2iSize(event.window.data1, event.window.data2);
				if (CanvasT::startVGSDK())
				{
					CanvasT::resize(v2iSize);
					unsetCurrent();
				}
				break;
			}
			case SDL_WINDOWEVENT_MINIMIZED:
				SDL_Log("Window %d minimized", event.window.windowID);
				break;
			case SDL_WINDOWEVENT_MAXIMIZED:
				SDL_Log("Window %d maximized", event.window.windowID);
				break;
			case SDL_WINDOWEVENT_RESTORED:
				SDL_Log("Window %d restored", event.window.windowID);
				break;
			case SDL_WINDOWEVENT_ENTER:
				SDL_Log("Mouse entered window %d",
					event.window.windowID);
				break;
			case SDL_WINDOWEVENT_LEAVE:
				SDL_Log("Mouse left window %d", event.window.windowID);
				break;
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				SDL_Log("Window %d gained keyboard focus",
					event.window.windowID);
				break;
			case SDL_WINDOWEVENT_FOCUS_LOST:
				SDL_Log("Window %d lost keyboard focus",
					event.window.windowID);
				break;
			case SDL_WINDOWEVENT_CLOSE:
				SDL_Log("Window %d closed", event.window.windowID);
				break;
			default:
				SDL_Log("Window %d got unknown event %d",
					event.window.windowID, event.window.event);
				break;
			}
		}

		switch (event.type)
		{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			//case SDL_TEXTINPUT:
			event::device::Keyboard::handleEvent(event);
			break;

		case SDL_MOUSEMOTION:
			event::device::Mouse::handleEvent(event.motion);
			break;

		case SDL_MOUSEWHEEL:
			event::device::Mouse::handleEvent(event.wheel);
			break;

		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			event::device::Mouse::handleEvent(event.button);
			break;

		case SDL_QUIT:
			haveToLoop = false;
			break;
		}

		return haveToLoop;
	}

	void initDevices( const uint devices )
	{
		// Creates device instances so we will receive vgd events.
		if ( devices & vgd::event::DeviceManager::Keyboard )
		{
			addDevice( vgSDL::event::device::Keyboard::get() );
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
				int width, height;
				SDL_GetWindowSize(m_window, &width, &height);
				const vgm::Vec2i v2iSize(width, height);
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
			int width, height;
			SDL_GetWindowSize(m_window, &width, &height);
			SDL_Rect rect = { 0, 0, width, height };
			SDL_UpdateWindowSurfaceRects(m_window, &rect, 1);
		}
	}


	/*bool on_focus_in_event(GdkEventFocus * event)
	{
		vgd::event::detail::GlobalButtonStateSet::clear();
		return Gtk::DrawingArea::on_focus_in_event(event);
	}*/

protected:

	SDL_Window * 	m_window;
	SDL_Renderer*	m_renderer;

	/**
	* @name	vgUI::Canvas specialization
	*/
	//@{
	glc_drawable_t * createDrawable()
	{
		return glc_sdl_drawable_create(m_window);
	}

	void destroyDrawable(glc_drawable_t * drawable)
	{
		glc_sdl_drawable_destroy(drawable);
	}
	//@}
};


} // namespace vgSDL

#endif // _VGSDL_GENERICCANVAS_HPP_
