// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/BasicManipulator.hpp"
#include <QEvent>

namespace vgQt
{

BasicManipulator::BasicManipulator(QWidget *parent) :
    GenericCanvas<vgUI::BasicManipulator>(parent)
{
    initDevices();
    m_actionsMenu->setCanvas(this);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onMenuRequested(QPoint)));
    connect(this, SIGNAL(rightClic(QMouseEvent *, QPoint, int)), m_actionsMenu.get(), SLOT(onBoutonPressEvent(QMouseEvent *, QPoint, int)));
}

BasicManipulator::~BasicManipulator()
{
    uninitDevices();
}

void BasicManipulator::initDevices()
{
    vgAssert( m_keyboard == 0 && m_mouse == 0 && m_timer == 0);

    // Creates device instances.
    m_keyboard.reset( new vgQt::event::device::Keyboard() );
    m_mouse.reset( new vgQt::event::device::Mouse() );
    m_timer.reset( new vgQt::event::device::Timer() );

    // Connects devices to the widget so they receive Qt events.
    m_keyboard->connect( this );
    m_mouse->connect( this );
    m_timer->connect( this );

    // Adds devices so we receive vgd events.
    addDevice( m_keyboard );
    addDevice( m_mouse );
    addDevice( m_timer );

    /*
    // Adds joystick (if present)
    if( m_joystick )
    {
        addDevice( m_joystick );
    }
    else
    {
        vgLogWarning( "No joystick found." );
    }
    */
}

void BasicManipulator::uninitDevices()
{
    // Disconnects devices to the widget so they no more receive Qt events
    m_keyboard->disconnect();
    // m_mouse->disconnect();
    m_timer->disconnect();

    // Removes devices
    removeDevice( m_keyboard );
    removeDevice( m_mouse );
    removeDevice( m_timer );

    /*
    // Removes joystick (if present)
    if ( m_joystick )
    {
        removeDevice( m_joystick );
    }
    */

    m_keyboard.reset();
    m_mouse.reset();
    m_timer.reset();
    // m_joystick.reset();

}

bool BasicManipulator::event(QEvent * event)
{
    if (event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent=static_cast<QWheelEvent*>(event);
        Q_EMIT wheel(wheelEvent);
    }
    else if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease)
    {
        setFocus();
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        Q_EMIT clic(mouseEvent);
        Q_EMIT rightClic(mouseEvent, mapToGlobal(mouseEvent->pos()), height());
    }
    else if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        Q_EMIT move(mouseEvent);
    }
    else if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        Q_EMIT key(keyEvent);
    }
    return GenericCanvas::event(event);
}

void BasicManipulator::onMenuRequested(QPoint point)
{
    m_actionsMenu->setCanvas(this);
    m_actionsMenu->showPopup( mapToGlobal(point), vgQt::node::CANVAS );
}

} // namespace vgQt
