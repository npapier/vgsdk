// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/helpers.hpp"

#include <vgd/node/Camera.hpp>



namespace vgeGL
{

namespace technique
{


vgd::Shp< vgd::node::Camera > setupRenderFromCamera(
		const vgm::Vec3f cameraPositionO, const vgm::Vec3f cameraDirectionO, const vgm::MatrixR cameraModelViewMatrix,
		const std::string cameraName, const vgm::MatrixR cameraProjection, const vgm::Vec2i cameraViewport,
		const vgm::MatrixR& invViewMatrix, const vgm::MatrixR& invTransformDraggerMatrix,
		vgm::MatrixR& cameraLookAt )
{
	// Creates the new camera
	vgd::Shp< vgd::node::Camera > newCamera = vgd::node::Camera::create( cameraName );

	// Sets fields
	vgm::Vec3f position		= cameraPositionO;
	vgm::Vec3f direction	= cameraDirectionO;

	vgm::MatrixR cameraModelMatrix = cameraModelViewMatrix * invViewMatrix;
	cameraModelMatrix.multVecMatrix( position, position );
	cameraModelMatrix[3][0] = cameraModelMatrix[3][1] = cameraModelMatrix[3][2] = 0.f;
	cameraModelMatrix.multVecMatrix( direction, direction );

	// lookAt field
	vgm::Vec3f	eye		( position );
	vgm::Vec3f	center	( position + direction );
	vgm::Vec3f	up		( 0.f, 1.f, 0.f );
	if ( direction.dot( up ) > 0.5f ) up.setValue( 1.f, 0.f, 0.f );
	cameraLookAt.setLookAt( eye, center, up );

	// The transform dragger must be undo.
// @todo disable TransformDragger
	newCamera->setLookAt( invTransformDraggerMatrix * cameraLookAt );

	// projection field
	newCamera->setProjection( cameraProjection );

	// viewport field
	const vgm::Rectangle2i viewport( 0, 0, cameraViewport[0], cameraViewport[1] );
	newCamera->setViewport( viewport );

	// Returns the new camera
	return newCamera;
}


} // namespace technique

} // namespace vgeGL
