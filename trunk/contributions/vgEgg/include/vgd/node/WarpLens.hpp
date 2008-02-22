// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier and Stephane Nicolau.

#ifndef _VGD_NODE_WARPLENS_HPP
#define _VGD_NODE_WARPLENS_HPP

#include <utility>
#include <vgm/Matrix.hpp>
#include <vgm/Rectangle.hpp>

#include "vgd/vgd.hpp"


namespace vgd
{

namespace node
{

/**
 * @brief Computes parameters for Camera node from camera intrinsic parameters.
 *
 * @param width		width of view in pixels
 * @param height		height of view in pixels
 * @param fc1		focal of the camera in the x and y direction 
 * @param fc2		focal of the camera in the x and y direction 
 * @param cc1		coordinates of the lens center (in pixels) in the pixel frame
 * @param cc2		coordinates of the lens center (in pixels) in the pixel frame
 * @param nearPlane	the distance from the camera to the near plane
 * @param farPlane	the distance from the camera to the far plane
 *
 * @return a pair with a matrix and a rectangle to apply to camera node (field \c matrix for the matrix and field \c viewport for the rectangle).
 */
VGD_API std::pair< vgm::MatrixR, vgm::Rectangle2i > computeWarpLensParams(
	const int width, const int height,
	const float fc1, const float fc2,
	const float cc1, const float cc2,
	const float nearPlane = 0.1f, const float farPlane = 2000.f );



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_WARPLENS_HPP
