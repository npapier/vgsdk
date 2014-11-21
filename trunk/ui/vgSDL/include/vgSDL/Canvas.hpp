// VGSDK - Copyright (C) 2012, 2014, Guillaume Brocker, Philippe Sengchanpheng
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Philippe Sengchanpheng

#ifndef _VGSDL_CANVAS_HPP_
#define _VGSDL_CANVAS_HPP_

#include <vgUI/Canvas.hpp>
#include "vgSDL/GenericCanvas.hpp"

#include "vgSDL/vgSDL.hpp"

namespace vgSDL
{

/**
 * @brief	Implements a SDL-based specialization of vgUI::Canvas.
 */
class VGSDL_API Canvas : public GenericCanvas<vgUI::Canvas>
{

public:

    /**
     * @brief	Constructor that builds a canvas with its own OpenGL context.
     */
	explicit Canvas();

	/**
     * @brief	Constructor that builds a canvas with an OpenGL context sharing resources with
	 * 			the given canvas.
	 *
	 * @param	sharedCanvas	a pointer to the canvas for sharing
     */
	explicit Canvas(vgUI::Canvas * sharedCanvas);
};

} // namespace vgQt

#endif // _VGSDL_CANVAS_HPP_
