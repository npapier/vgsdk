// VGSDK - Copyright (C) 2004, 2006, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/handler/basic/Shape.hpp"

#include <vgd/node/Box.hpp>
#include <vgd/node/Quad.hpp>
#include <vgd/node/Shape.hpp>
#include <vgd/node/Sphere.hpp>
#include <vgd/node/TriSet.hpp>
#include <vgd/node/VertexShape.hpp>
#include <vgd/node/WireBox.hpp>
#include <vgd/node/WireQuad.hpp>

#include "vge/engine/Engine.hpp"
#include "vge/service/ComputeBoundingBox.hpp"



namespace vge
{

namespace handler
{

namespace basic
{



META_HANDLER_CPP( Shape );



const Handler::TargetVector Shape::getTargets()	const
{
	TargetVector targets;

	targets.reserve( 7 );
	targets.push_back( vgd::node::Box::getClassIndexStatic() );
	targets.push_back( vgd::node::Quad::getClassIndexStatic() );
	targets.push_back( vgd::node::Sphere::getClassIndexStatic() );
	targets.push_back( vgd::node::TriSet::getClassIndexStatic() );
	targets.push_back( vgd::node::VertexShape::getClassIndexStatic() );
	targets.push_back( vgd::node::WireBox::getClassIndexStatic() );
	targets.push_back( vgd::node::WireQuad::getClassIndexStatic() );

	return targets;
}



void Shape::apply( vge::engine::Engine *pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgd::node::Shape* >(pNode) != 0 );
	vgd::node::Shape *pCastedNode = static_cast< vgd::node::Shape* >(pNode);

	vgm::MatrixR&	current( pEngine->getGeometricalMatrix().getTop() );

	pCastedNode->computeBoundingBox( current );
}



void Shape::unapply( vge::engine::Engine *, vgd::node::Node * )
{
	// Nothing to do.
}



void Shape::setToDefaults()
{}



} // namespace basic
	
} // namespace handler

} // namespace vge
