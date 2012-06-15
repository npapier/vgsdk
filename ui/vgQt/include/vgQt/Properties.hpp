// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_PROPERTIES_HPP_
#define _VGQT_PROPERTIES_HPP_

#include "vgQt/engine/Settings.hpp"

#include <QWidget>

#include "vgQt/vgQt.hpp"

namespace vgUI
{
    struct BasicViewer;
}

namespace vgQt
{

/**
 * @brief Properties for vgsdk rendering.
 */
class VGQT_API Properties : public QWidget
{
public:
    /**
     * @brief	Constructor
     */
    Properties(QWidget* parent);

    /**
     * @brief	Assignes the canvas to configure.
     *
     * @param	canvas	a pointer to a canvas, null if none.
     */
    void setCanvas( vgUI::BasicViewer * canvas );

private:
    engine::Settings*			m_engineSettingsEditor;
};

}

#endif // _VGQT_PROPERTIES_HPP_
