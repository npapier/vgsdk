// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_BASICVIEWER_HPP_
#define _VGQT_BASICVIEWER_HPP_

#include <vgUI/BasicViewer.hpp>
#include "vgQt/Genericcanvas.hpp"

#include "vgQt/vgQt.hpp"

namespace vgQt
{
/**
 * @brief	Implements a Qt-based specialization of vgUI::BasicViewer.
 */
class VGQT_API BasicViewer : public GenericCanvas<vgUI::BasicViewer>
{
    Q_OBJECT
public:
    /**
     * @name	Constructor
     */
    explicit BasicViewer(QWidget *parent = 0);

};

} // namespace vgQt

#endif // _VGQT_BASICVIEWER_HPP_
