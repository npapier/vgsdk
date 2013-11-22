// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/GeoMorph.hpp"

#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/GeoMorph.hpp>
#include <vgd/node/VertexShape.hpp>
#include <vge/service/Painter.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/handler/painter/VertexShape.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( GeoMorph );



const vge::handler::Handler::TargetVector GeoMorph::getTargets() const
{
	vge::handler::Handler::TargetVector targets;

	targets.push_back( vgd::node::GeoMorph::getClassIndexStatic() );

	return targets;
}



void GeoMorph::apply( vge::engine::Engine * baseEngine, vgd::node::Node * node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(baseEngine) != 0 );
	vgeGL::engine::Engine *engine = static_cast< vgeGL::engine::Engine* >(baseEngine);

	assert( dynamic_cast< vgd::node::GeoMorph* >(node) != 0 );
	vgd::node::GeoMorph *geoMorph = static_cast< vgd::node::GeoMorph* >(node);

	// Updates engine.geoMorph
	using vgd::node::GeoMorph;
	GeoMorph::MethodValueType method = geoMorph->getMethod();

	if ( method == GeoMorph::NORMALIZED )
	{
		// Enables geo morphing in engine. Handlers have to take care of that (see VertexShape handler).
		engine->setGeoMorph( geoMorph );

		engine->setDrawCallsEnabled(false);

		// Updates engine glsl state
		if ( engine->isGLSLEnabled() )
		{
			//
			using vgeGL::engine::GLSLState;

			engine->getGLSLStateStack().push();
			GLSLState& glslState = engine->getGLSLState();

			// Ask to generate new shaders
			glslState.setEnabled( vgeGL::engine::GEOMORPH );

			// Customize shaders
			//	uniform
			const std::string uniformDecl =	"// geomorph\n"
											"uniform vec2 geoMorphWeights;\n\n";
			glslState.setShaderStage( GLSLState::UNIFORM_DECLARATIONS, uniformDecl );

			engine->getUniformState().addUniform( "geoMorphWeights", geoMorph->getWeights() );

			// Geomorphing computation in vertex shader
			const std::string glPositionAndEcPositionComputation =
				"	vec4 position2 = mgl_Vertex1;\n"
				"	position = (1-geoMorphWeights[0]) * position2 + geoMorphWeights[0] * position;\n\n";
			glslState.setShaderStage( GLSLState::VERTEX_POSITION_COMPUTATION, glPositionAndEcPositionComputation );

			// @todo normals and tangents, texCoord ?
		}
		//else nothing to do. GeoMorphing is not supported without GLSL
	}
	else if ( method == GeoMorph::SKIP )
	{
		engine->setDrawCallsEnabled(false);
	}
	else
	{
		vgAssert( method == GeoMorph::DISABLED );
		// nothing to do
	}
}



void GeoMorph::unapply( vge::engine::Engine * baseEngine, vgd::node::Node * node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(baseEngine) != 0 );
	vgeGL::engine::Engine *engine = static_cast< vgeGL::engine::Engine* >(baseEngine);

	assert( dynamic_cast< vgd::node::GeoMorph* >(node) != 0 );
	vgd::node::GeoMorph *geoMorph = static_cast< vgd::node::GeoMorph* >(node);

	// Updates engine
	engine->setGeoMorph( 0 );	// restore vertexShape painter normal behavior
	engine->setDrawCallsEnabled( true ); // @todo restore previous value (before modification in apply())

	using vgd::node::GeoMorph;
	GeoMorph::MethodValueType method = geoMorph->getMethod();

	if ( (method == GeoMorph::NORMALIZED) && engine->isGLSLEnabled() )
	{
		// Render the geoMorph
		using vgd::field::MFVertexShapePtr;
		vgd::field::EditorRW< MFVertexShapePtr > meshes = geoMorph->get__meshes__RW();	// @todo move meshes in a rc::GeoMorph.meshes
		const uint meshesSize = meshes->size();

		if ( meshesSize < 2 )
		{
			vgLogDebug( "GeoMorph(%s) have to be apply to at least 2 meshes", geoMorph->getName().c_str() );
			meshes->clear();
		}
		else
		{
			if ( meshesSize > 2 ) vgLogDebug( "GeoMorph(%s) have to be apply to exactly 2 meshes.", geoMorph->getName().c_str() );

			// Retrieves all meshes
			vgd::node::VertexShape * mesh0 = (*meshes)[0];
			vgd::node::VertexShape * mesh1 = (*meshes)[1];

			// Clean and release
			meshes->clear();
			meshes.release();

			// Paint GeoMorph
			vgeGL::handler::painter::VertexShape vsHandler;
			vsHandler.geoMorph2 = mesh1;
			vsHandler.apply( engine, mesh0 );
		}

		// Restores state
		engine->getUniformState().removeUniform( "geoMorphWeights" );
		engine->getGLSLStateStack().pop();
	}

	node->getDirtyFlag(node->getDFNode())->validate();
}



void GeoMorph::setToDefaults()
{
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
