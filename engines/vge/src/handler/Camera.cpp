// VGSDK - Copyright (C) 2004, 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/Camera.hpp"

#include <vgd/node/Camera.hpp>

#include "vge/engine/Engine.hpp"



namespace vge
{

namespace handler
{



void Camera::apply( vge::engine::Engine * engine, vgd::node::Camera * camera )
{
	// Updates engine

	//	CAMERA node
	engine->setCamera( camera );

	//	VIEWPORT field
	const vge::engine::EyeUsagePolicy eyePolicy = engine->getEyeUsagePolicy();
	vgm::Rectangle2i viewportValue;
	camera->gethViewport( viewportValue, engine->getDrawingSurfaceSize()[0], eyePolicy );

	engine->setViewport( viewportValue );

	//
	applyMatrix( engine, camera );
	applyLookAt( engine, camera );

	// Updates engine

	// Computes near and far from the projection matrix.
	const vgm::MatrixR projectionMatrix = camera->getProjection( engine->getEyeUsagePolicy() );
	if ( !projectionMatrix.isIdentity() )
	{
		const double c = projectionMatrix[2][2];
		const double d = projectionMatrix[3][2];

		const double near	= d / (c - 1.0);
		const double far	= d / (1.0 + c);

		engine->setNearFar( vgm::Vec2f(static_cast<float>(near), static_cast<float>(far)) );
	}
	else
	{
		engine->setNearFar( vgm::Vec2f::getInvalid() );
	}
}



void Camera::unapply( vge::engine::Engine *engine, vgd::node::Camera *camera )
{
	//unapplyMatrix( engine, camera );
	//unapplyLookAt( engine, camera );
}



void Camera::applyMatrix( vge::engine::Engine *engine, vgd::node::Camera *camera )
{
	// PROJECTION MATRIX

	const vge::engine::EyeUsagePolicy eyePolicy = engine->getEyeUsagePolicy();
	const vgm::MatrixR matrix = camera->getProjection( eyePolicy );

	// Updates engine
	if ( camera->getComposeTransformation() )
	{
		// Composes and updates engine
		vgm::MatrixR& current( engine->getProjectionMatrix().getTop() );

		current = matrix * current;
	}
	else
	{
		// Updates engine
		engine->getProjectionMatrix().setTop( matrix );
	}
}



void Camera::applyLookAt( vge::engine::Engine *engine, vgd::node::Camera *camera )
{
	// GEOMETRICAL MATRIX

	const vge::engine::EyeUsagePolicy eyePolicy = engine->getEyeUsagePolicy();
	const vgm::MatrixR matrix = camera->getLookAt( eyePolicy );

	// Updates engine
	if ( camera->getComposeTransformation() )
	{
		// Composes and updates engine
		vgm::MatrixR& current( engine->getGeometricalMatrix().getTop() );

		current = matrix * current;
	}
	else
	{
		// Updates engine
		engine->getGeometricalMatrix().setTop( matrix );
	}
}



} // namespace handler

} // namespace vge
