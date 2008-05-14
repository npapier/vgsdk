// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier and Stephane Nicolau.

#include "vgd/node/WarpLens.hpp"



namespace vgd
{

namespace node
{



std::pair< vgm::MatrixR, vgm::Rectangle2i > computeWarpLensParams(
	const int width, const int height,
	const float fc1, const float fc2,
	const float cc1, const float cc2,
	const float nearPlane, const float farPlane )
{
	// Computes projection matrix
	const float width1f		= static_cast< float >( width );
	const float height1f	= static_cast< float >( height );

	vgm::MatrixR projection;
	projection.setPerspective(	2.f * static_cast<float>(std::atan( (height1f/2.f)/-fc2 )) * 180.f / static_cast<float>(vgm::M_PI),
								width1f/height1f * fc2/fc1,
								nearPlane, farPlane );

	// Computes viewport
	const vgm::Rectangle2i viewport(
		static_cast<int>(cc1 - width/2.f),
		static_cast<int>(cc2 - height/2.f), width, height );

	// Constructs return value
	const std::pair< vgm::MatrixR, vgm::Rectangle2i > retVal( projection, viewport );

	return retVal;
}



} // namespace node

} // namespace vgd
