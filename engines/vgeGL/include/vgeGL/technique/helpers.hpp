// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_HELPERS_HPP
#define _VGEGL_TECHNIQUE_HELPERS_HPP

#include <vgd/Shp.hpp>
#include "vgeGL/vgeGL.hpp"
#include <vgm/Matrix.hpp>


namespace glo { struct FrameBufferObject; }
namespace vgd { namespace basic { struct Image; } }
namespace vgd { namespace node { struct Camera; } }

namespace vgeGL { namespace engine { struct Engine; } }



namespace vgeGL
{

namespace technique
{


// @todo getImage( texture );
vgd::Shp< vgd::basic::Image > getImage( vgd::Shp< glo::FrameBufferObject > fbo, const int index );

vgd::Shp< vgd::node::Camera > setupRenderFromCamera(
		const vgm::Vec3f cameraPositionO, const vgm::Vec3f cameraDirectionO, const vgm::MatrixR cameraModelViewMatrix,
		const std::string cameraName, const vgm::MatrixR cameraProjection, const vgm::Vec2i cameraViewport,
		const vgm::MatrixR& invViewMatrix, const vgm::MatrixR& invTransformDraggerMatrix,
		vgm::MatrixR& cameraLookAt );


} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_HELPERS_HPP
