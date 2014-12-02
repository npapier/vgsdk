//// VGSDK - Copyright (C) 2011, 2014, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_TECHNIQUE_HELPERS_HPP
//#define _VGEGLBASE_TECHNIQUE_HELPERS_HPP
//
//#include <vgd/Shp.hpp>
//#include "vgeGLBase/vgeGLBase.hpp"
//#include <vgm/Matrix.hpp>
//
//
//namespace glo { struct FrameBufferObject; struct Texture2D; }
//namespace vgd { namespace basic { struct Image; } }
//namespace vgd { namespace node { struct Camera; } }
//
//namespace vgeGLBase { namespace engine { struct Engine; } }
//
//
//
//namespace vgeGLBase
//{
//
//namespace technique
//{
//
//
///**
// * @brief Copies texture pixels into image/imageData.
// *
// * @param texture	texture from which to read pixels
// * @param image		if texture and image have matching size, format and type, then texture pixels are copying into the image. Otherwise a new image is created to copy texture pixels.
// * @param imageData	value returned by image->editPixels(). Useful to avoid calling this method (lock on openil !!!).
// */
//void getImage(	vgd::Shp< glo::Texture2D > texture,
//				vgd::Shp< vgd::basic::Image >& image, void *& imageData );
//
///**
// * @brief Copies texture pixels from given framebuffer into image/imageData.
// *
// * @param framebuffer	framebuffer from which to read pixels
// * @param index			a zero-based index used to select to color buffer in the given framebuffer
// * @param image			if texture and image have matching size, format and type, then texture pixels are copying into the image. Otherwise a new image is created to copy texture pixels.
// * @param imageData	value returned by image->editPixels(). Useful to avoid calling this method (lock on openil !!!).
// */
//void getImage( vgd::Shp< glo::FrameBufferObject > fbo, const int index, vgd::Shp< vgd::basic::Image >& image, void *& imageData );
//
//
//vgd::Shp< vgd::node::Camera > setupRenderFromCamera(
//		const vgm::Vec3f cameraPositionO, const vgm::Vec3f cameraDirectionO, const vgm::MatrixR cameraModelViewMatrix,
//		const std::string cameraName, const vgm::MatrixR cameraProjection, const vgm::Rectangle2i cameraViewport,
//		const vgm::MatrixR& invViewMatrix, const vgm::MatrixR& invTransformDraggerMatrix,
//		vgm::MatrixR& cameraLookAt );
//
//
//} // namespace technique
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_TECHNIQUE_HELPERS_HPP
//