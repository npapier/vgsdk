// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/CoordinateSystem.hpp"

#include <vgd/node/CoordinateSystem.hpp>

#include "vge/engine/Engine.hpp"



namespace vge
{

namespace handler
{



void CoordinateSystem::apply ( vge::engine::Engine * engine, vgd::node::CoordinateSystem * node )
{
	// Retrieves the mask
	const vgd::node::CoordinateSystem::FMaskType::value_type mask( node->getMask() );

	// PROJECTION MATRIX
	if ( mask & vgd::node::CoordinateSystem::PROJECTION_MATRIX_MASK )
	{
		// Retrieves the desired matrix
		const vgd::node::CoordinateSystem::MatrixValueType& matrix = engine->getProjectionMatrix().getTop();

		// Sets the matrix in CoordinateSystem node
		node->setMatrix( vgd::node::CoordinateSystem::PROJECTION, matrix );
	}

	// GEOMETRICAL MATRIX
	if ( mask & vgd::node::CoordinateSystem::GEOMETRICAL_MATRIX_MASK )
	{
		// Retrieves the desired matrix
		const vgd::node::CoordinateSystem::MatrixValueType& matrix = engine->getGeometricalMatrix().getTop();

		// Sets the matrix in CoordinateSystem node
		node->setMatrix( vgd::node::CoordinateSystem::GEOMETRICAL, matrix );
	}

	// VIEWPORT
	if ( mask & vgd::node::CoordinateSystem::VIEWPORT_MASK )
	{
		// Retrives the viewport
		const vgm::Rectangle2i& viewport = engine->getViewport();

		// Sets the viewport in CoordinateSystem node
		node->setViewport( viewport );
	}

	// Validates node
	node->getDirtyFlag(node->getDFNode())->validate();
}



void CoordinateSystem::unapply ( vge::engine::Engine* /*engine*/, vgd::node::CoordinateSystem* /*node*/ )
{
	// Nothing to do
}



} // namespace handler

} // namespace vge
