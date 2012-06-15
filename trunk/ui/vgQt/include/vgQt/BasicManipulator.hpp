// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_BASICMANIPULATOR_HPP_
#define _VGQT_BASICMANIPULATOR_HPP_

#include <vgUI/BasicManipulator.hpp>
#include "vgQt/Genericcanvas.hpp"

#include "vgQt/event/device/Keyboard.hpp"
#include "vgQt/event/device/Mouse.hpp"
#include "vgQt/event/device/Timer.hpp"

#include "vgQt/vgQt.hpp"

namespace vgQt
{

/**
 * @brief	Implements a Qt-based specialization of the vgUI::BasicManipulator.
 */
class VGQT_API BasicManipulator : public GenericCanvas<vgUI::BasicManipulator>
{
    Q_OBJECT
public:
    /**
     * @name	Constructor & destructor
     */
    explicit BasicManipulator(QWidget *parent = 0);
    ~BasicManipulator();

    void initDevices();		///< Initializes device instances and perform listening connections.
    void uninitDevices();	///< Uninitializes device instances and stop listening connections.

protected:

    bool event( QEvent * event );

Q_SIGNALS:
    void wheel(QWheelEvent * event);
    void clic(QMouseEvent * event);
    void move(QMouseEvent * event);
    void key(QKeyEvent * event);
    void rightClic(QMouseEvent * event, QPoint point, int height);

public Q_SLOTS:
    void onMenuRequested(QPoint);

private:
    vgd::Shp< vgQt::event::device::Keyboard >	m_keyboard;	///< The Qt keyboard device.
    vgd::Shp< vgQt::event::device::Mouse >		m_mouse;	///< The Qt mouse device.
    vgd::Shp< vgQt::event::device::Timer >		m_timer;	///< The Qt timer device.
};

} // namespace vgQt

#endif // _VGQT_BASICMANIPULATOR_HPP_
