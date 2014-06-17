// VGSDK - Copyright (C) 2012, 2013, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_GENERICCANVAS_HPP_
#define _VGQT_GENERICCANVAS_HPP_

#include <QWidget>

#include <glc_qt/glc_qt.hpp>

#include <vgd/Shp.hpp>

#include "vgQt/node/ActionsMenu.hpp"
#include "vgQt/event/device/Keyboard.hpp"
#include "vgQt/event/device/Mouse.hpp"
#include "vgQt/event/device/Timer.hpp"

namespace vgQt
{

/**
 * @brief	Implements a generic rendering canvas based on QWidget with its own openGL context.
 *
 * It is meant to specialize vgQt::Canvas, vgQt::BasicViewer or vgQt::BasicManipulator.
 *
 */
template< typename CanvasT >
struct GenericCanvas : public QWidget, public CanvasT
{

public:

    /**
     * @brief	Constructor that builds a canvas with its own OpenGL context.
	 *
	 * @param	parent	a pointer to the parent widget (default is null)
     */
	explicit GenericCanvas( QWidget * parent = 0 )
    : QWidget(parent),
      m_actionsMenu( new vgQt::node::ActionsMenu( this, vgQt::node::CANVAS))
    {
        setAttribute(Qt::WA_PaintOnScreen);
        setAttribute(Qt::WA_NoSystemBackground);
        setAutoFillBackground(true); // for compatibility

        setContextMenuPolicy(Qt::CustomContextMenu);

		setMouseTracking(true);
    }

	/**
	 * @brief	Constructor that builds a canvas with an OpenGL context sharing resources with
	 * 			the given canvas.
	 *
	 * @param	sharedCanvas	a pointer to the canvas for sharing
	 * @param	parent			a pointer to the parent widget (default is null)
	 */
	GenericCanvas( const vgUI::Canvas * sharedCanvas, QWidget * parent = 0 )
    : QWidget(parent),
	  CanvasT( sharedCanvas ),
      m_actionsMenu( new vgQt::node::ActionsMenu( this, vgQt::node::CANVAS))
    {
        setAttribute(Qt::WA_PaintOnScreen);
        setAttribute(Qt::WA_NoSystemBackground);
        setAutoFillBackground(true); // for compatibility

        setContextMenuPolicy(Qt::CustomContextMenu);

		setMouseTracking(true);
    }

    ~GenericCanvas()
    {
        CanvasT::shutdownVGSDK();
    }

	void initDevices( const uint devices )
	{
		// Creates device instances so we will receive vgd events.
		if ( devices & vgd::event::DeviceManager::Keyboard )
		{
			addDevice( vgd::makeShp(new vgQt::event::device::Keyboard()) );
		}

		if ( devices & vgd::event::DeviceManager::Mouse )
		{
			addDevice( vgd::makeShp(new vgQt::event::device::Mouse(this)) );
		}

		if ( devices & vgd::event::DeviceManager::Timer )
		{
			addDevice( vgd::makeShp(new vgQt::event::device::Timer()) );
		}

		//if ( devices & vgd::event::DeviceManager::Joystick )
		//{
		//	vgd::Shp< vgSDL::event::device::Joystick >	joystick = vgSDL::event::device::Joystick::get(0);
		//
		//	// Adds joystick (if present)
		//	if( joystick )
		//	{
		//		addDevice( joystick );
		//	}
		//	else
		//	{
		//		vgLogWarning( "No joystick found." );
		//	}
		//}
	}


	void refreshForced( const vgUI::Canvas::WaitType wait = vgUI::Canvas::ASYNCHRONOUS )
	{
		if( wait == vgUI::Canvas::SYNCHRONOUS )
		{
			if ( startVGSDK() )
			{
				const vgm::Vec2i v2iSize( width(), height() );
				CanvasT::paint( v2iSize, CanvasT::getBoundingBoxUpdate() );
				unsetCurrent();
			}
		}
		else
		{
			update();
		}
	}


    QPaintEngine * paintEngine () const
    {
        return 0;
    }

    void paintEvent(QPaintEvent* event)
    {
        Q_UNUSED(event);
        const vgm::Vec2i v2iSize( width(), height() );

        if ( CanvasT::startVGSDK() )
        {
            CanvasT::paint( v2iSize, CanvasT::getBoundingBoxUpdate() );
            unsetCurrent();
        }
    }

    void resizeEvent(QResizeEvent* event)
    {
        Q_UNUSED(event);
        const vgm::Vec2i v2iSize( width(), height() );

        if ( CanvasT::startVGSDK() )
        {
            CanvasT::resize( v2iSize );
            unsetCurrent();
        }
    }

protected:

    vgd::Shp< vgQt::node::ActionsMenu > 	m_actionsMenu;

	/**
	 * @name	vgUI::Canvas specialization
	 */
	//@{
	glc_drawable_t * createDrawable()
	{
		return glc_qt_drawable_create( this );
	}

	void destroyDrawable( glc_drawable_t * drawable )
	{
		glc_qt_drawable_destroy( drawable );
	}
	//@}
};


} // namespace vgQt

#endif // _VGQT_GENERICCANVAS_HPP_
