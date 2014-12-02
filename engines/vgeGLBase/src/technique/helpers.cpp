//// VGSDK - Copyright (C) 2011, 2014, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGL/technique/helpers.hpp"
//
//#include <glo/FrameBufferObject.hpp>
//#include <glo/Texture2D.hpp>
//#include <vgd/basic/Image.hpp>
//#include <vgd/node/Camera.hpp>
//#include "vgeGL/basic/helpers.hpp"
//
//
//
//namespace vgeGL
//{
//
//namespace technique
//{
//
//
//// @todo read from (position, size)
//void getImage(	vgd::Shp< glo::Texture2D > texture2D,
//				vgd::Shp< vgd::basic::Image >& image, void *& imageData )
//{
//	const GLint	width			= texture2D->getWidth();
//	const GLint	height			= texture2D->getHeight();
//	const GLint	internalFormat	= texture2D->getInternalFormat();
//
//	vgd::basic::IImage::Format	myFormat;
//	vgd::basic::IImage::Type	myType;
//	const bool convertRetVal = vgeGL::basic::convertGLInternalFormat2My( internalFormat, myFormat, myType );
//	vgAssert( convertRetVal );
//
//	using vgd::basic::Image;
//	const bool matchingImage =	image && imageData &&
//								(image->getSize3i() == vgm::Vec3i( width, height, 1 ))	&&
//								(image->format() == myFormat)							&&
//								(image->type() == myType);
//
//	if ( !matchingImage )
//	{
//		// no image given or not matching (size, format or type)
//		image.reset( new Image( width, height, 1, myFormat, myType ) );
//		imageData = static_cast<uint8*>( image->editPixels() );
//		image->editPixelsDone();
//	}
//	// else use image and imageData
//
//	// Reads back the buffer values
//	glPixelStorei(GL_PACK_ALIGNMENT, 1);
//	glReadPixels(	0, 0,
//					width, height,
//					vgeGL::basic::convertMyFormat2GL(myFormat), vgeGL::basic::convertMyType2GL(myType),
//					imageData );
//}
//
//
//void getImage(	vgd::Shp< glo::FrameBufferObject > fbo, const int index,
//				vgd::Shp< vgd::basic::Image >& image, void *& imageData )
//{
//	fbo->bind();
//	fbo->setReadBuffer( index );
//
//	vgd::Shp< glo::Texture2D > texture2D = fbo->getColorAsTexture2D(index);
//
//	getImage( texture2D, image, imageData );
//
//	fbo->unbind();
//}
//
//
//vgd::Shp< vgd::node::Camera > setupRenderFromCamera(
//		const vgm::Vec3f cameraPositionO, const vgm::Vec3f cameraDirectionO, const vgm::MatrixR cameraModelViewMatrix,
//		const std::string cameraName, const vgm::MatrixR cameraProjection, const vgm::Rectangle2i cameraViewport,
//		const vgm::MatrixR& invViewMatrix, const vgm::MatrixR& invTransformDraggerMatrix,
//		vgm::MatrixR& cameraLookAt )
//{
//	// Creates the new camera
//	vgd::Shp< vgd::node::Camera > newCamera = vgd::node::Camera::create( cameraName );
//
//	// Sets fields
//	vgm::Vec3f position		= cameraPositionO;
//	vgm::Vec3f direction	= cameraDirectionO;
//
//	vgm::MatrixR cameraModelMatrix = cameraModelViewMatrix * invViewMatrix;
//	cameraModelMatrix.multVecMatrix( position, position );
//	cameraModelMatrix[3][0] = cameraModelMatrix[3][1] = cameraModelMatrix[3][2] = 0.f;
//	cameraModelMatrix.multVecMatrix( direction, direction );
//
//	// lookAt field
//	vgm::Vec3f	eye		( position );
//	vgm::Vec3f	center	( position + direction );
//	vgm::Vec3f	up		( 0.f, 1.f, 0.f );
//	if ( direction.dot( up ) > 0.5f ) up.setValue( 1.f, 0.f, 0.f );
//	cameraLookAt.setLookAt( eye, center, up );
//
//	// The transform dragger must be undo.
//// @todo disable TransformDragger
//	newCamera->setLookAt( invTransformDraggerMatrix * cameraLookAt );
//
//	// projection field
//	newCamera->setProjection( cameraProjection );
//
//	// viewport field
//	newCamera->setViewport( cameraViewport );
//
//	// Returns the new camera
//	return newCamera;
//}
//
//
//} // namespace technique
//
//} // namespace vgeGL
//