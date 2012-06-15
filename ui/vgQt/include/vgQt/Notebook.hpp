// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_NOTEBOOK_HPP_
#define _VGQT_NOTEBOOK_HPP_

#include "vgQt/graph/Browser.hpp"
#include "vgQt/Properties.hpp"

#include <vgd/Shp.hpp>
#include <QTabWidget>

#include "vgQt/vgQt.hpp"

namespace vgd
{
    namespace node
    {
        struct Group;
    }
}

namespace vgUI
{
    struct BasicManipulator;
}



namespace vgQt
{



/**
 * @brief	Implements a notebook that provides pages to browse a vgSDK graph and
 *		to configure properties of the rendering engine.
 */
struct VGQT_API Notebook : QTabWidget
{
    /**
     * @brief	Constructor
     */
    Notebook(QWidget* parent);

    /**
     * @brief	Assignes the canvas that is used for the rendering.
     *
     * @param	canvas	a reference to a canvas
     */
    void setCanvas( vgUI::BasicManipulator* canvas );


private:

    graph::Browser*		m_graphBrowser;		///< the graph browser widget
    Properties*			m_properties;
};



} // namespace vgQt

#endif //  _VGQT_NOTEBOOK_HPP_
