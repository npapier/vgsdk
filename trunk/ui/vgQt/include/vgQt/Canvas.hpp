// VGSDK - Copyright (C) 2012, 2013, Guillaume Brocker, Bryan Schuller
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
     * @brief	Constructor that builds a canvas with its own OpenGL context.
	 *
	 * @param	a pointer to the parent widget (default is null)
     */
    explicit Canvas( QWidget * parent = 0 );

	/**
     * @brief	Constructor that builds a canvas with an OpenGL context sharing resources with
	 * 			the given canvas.
	 *
	 * @param	sharedCanvas	a pointer to the canvas for sharing
	 * @param	parent			a pointer to the parent widget (default is null)
     */
    explicit Canvas( vgUI::Canvas * sharedCanvas, QWidget * parent = 0 );
};

} // namespace vgQt

#endif // _VGQT_CANVAS_HPP_
