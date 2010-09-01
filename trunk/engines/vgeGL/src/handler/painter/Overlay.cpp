// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Overlay.hpp"

#include <vgDebug/convenience.hpp>
#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/Overlay.hpp>
#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( Overlay );



const vge::handler::Handler::TargetVector Overlay::getTargets() const
{
	TargetVector targets;

	targets.reserve( 1 );
	targets.push_back( vgd::node::Overlay::getClassIndexStatic() );

	return targets;
}



void Overlay::apply( vge::engine::Engine* baseEngine, vgd::node::Node * node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(baseEngine) != 0 );
	vgeGL::engine::Engine *engine = static_cast< vgeGL::engine::Engine* >(baseEngine);

	assert( dynamic_cast< vgd::node::Overlay* >(node) != 0 );
	vgd::node::Overlay *overlay = static_cast< vgd::node::Overlay* >(node);

	// Updates engine state
	if ( engine->isGLSLEnabled() )
	{
		using vgeGL::engine::GLSLState;
		GLSLState& glslState = engine->getGLSLState();

		vgd::Shp< GLSLState::OverlayState > overlayState( new GLSLState::OverlayState(overlay) );

		const int multiAttributeIndex = computeMultiAttributeIndex( overlay, glslState.overlays );
		glslState.overlays.setState( multiAttributeIndex, overlayState );
	}

	// Validates node df
	node->getDirtyFlag(node->getDFNode())->validate();
}



void Overlay::unapply( vge::engine::Engine* engine, vgd::node::Node* pNode )
{}



void Overlay::setToDefaults()
{}



// @todo Uses glsl for Overlay
void Overlay::paint( vgeGL::engine::Engine * engine, vgd::Shp< OverlayStateContainer > overlays )
{
	typedef vgeGL::engine::GLSLState::OverlayState OverlayState;

	uint numFound = 0;
	for( uint i = 0; numFound < overlays->getNum(); ++i )
	{
		vgd::Shp< OverlayState > overlayState = overlays->getState(i);

		if ( overlayState )
		{
			++numFound;
			vgd::node::Overlay *overlay = overlayState->getNode();
			if ( overlay )
			{
				LayerPlan::paint( engine, overlay );
			}
		}
	}
}



} // namespace painter

} // namespace handler

} // namespace vgeGL

