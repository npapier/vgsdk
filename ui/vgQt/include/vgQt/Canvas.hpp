// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_CANVAS_HPP_
#define _VGQT_CANVAS_HPP_

#include <vgUI/Canvas.hpp>
#include "vgQt/GenericCanvas.hpp"

#include "vgQt/vgQt.hpp"

namespace vgQt
{

/**
 * @brief	Implements a Qt-based specialization of vgUI::Canvas.
 */
class VGQT_API Canvas : public GenericCanvas<vgUI::Canvas>
{
    Q_OBJECT

public:
    /**
     * @name	Constructor
     */
    explicit Canvas(QWidget *parent = 0);

};

} // namespace vgQt

#endif // _VGQT_CANVAS_HPP_
