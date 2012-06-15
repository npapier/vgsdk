// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_EVENT_SIGNALHANDLER_HPP_
#define _VGQT_EVENT_SIGNALHANDLER_HPP_

#include <QWidget>
#include <QObject>

#include "vgQt/vgQt.hpp"

namespace vgQt
{

namespace event
{

namespace device
{

struct VGQT_API Device : public QObject
{
public:
    Device();
    virtual ~Device();
    void connect( QWidget *widget );
    void disconnect();

protected:
    QWidget	* m_connectedWidget;	///< A pointer to the widget the device is connected to.
};

} // namespace device
} // namespace event
} // namespace vgQt

#endif _VGQT_EVENT_SIGNALHANDLER_HPP_
