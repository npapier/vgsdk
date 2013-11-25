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
	engine->setGeoMorph( 0 );				// restore vertexShape painter normal behavior
	engine->setDrawCallsEnabled( true );	// @todo restore previous value (before modification in apply())

	using vgd::node::GeoMorph;
	GeoMorph::MethodValueType method = geoMorph->getMethod();

	if ( (method == GeoMorph::NORMALIZED) && engine->isGLSLEnabled() ) // GeoMorphing is not supported without GLSL
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

			// Paint GeoMorph using a private vertex shape handler
			vgeGL::handler::painter::VertexShape vsHandler;
			vsHandler.geoMorph2 = mesh1;

			// Updates engine glsl state
			using vgeGL::engine::GLSLState;

			engine->getGLSLStateStack().push();
			GLSLState& glslState = engine->getGLSLState();

			// Ask to generate new shaders
			glslState.setEnabled( vgeGL::engine::GEOMORPH );

			// Customize shaders
			//	uniform
			const std::string uniformDecl =	"// add by geomorph\n"
											"uniform vec2 geoMorphWeights;\n\n";
			glslState.setShaderStage( GLSLState::UNIFORM_DECLARATIONS, uniformDecl );

			engine->getUniformState().addUniform( "geoMorphWeights", geoMorph->getWeights() );

			// Geomorphing computation in vertex shader
			static const std::string templateMethodStr =	"// add by geomorph\n"
															"	vec4 Value1 = mgl_Source1;\n"
															"	Value = (1-geoMorphWeights[0]) * Value + geoMorphWeights[0] * Value1;\n";

			// vertex
			std::string positionComputation = boost::algorithm::replace_all_copy( templateMethodStr, "Value", "position" );
			boost::algorithm::replace_all( positionComputation, "mgl_Source1", "mgl_Vertex1" );
			glslState.setShaderStage( GLSLState::VERTEX_POSITION_COMPUTATION, positionComputation );

			// normal
			std::string normalComputation;
			if ( mesh0->getNormalBinding() == vgd::node::BIND_PER_VERTEX )
			{
				normalComputation = boost::algorithm::replace_all_copy( templateMethodStr, "Value", "normal" );
				boost::algorithm::replace_all( normalComputation, "vec4", "vec3" );
				boost::algorithm::replace_all( normalComputation, "mgl_Source1", "mgl_Normal1" );
			}

			// tangent
			std::string tangentComputation;
			if ( mesh0->getTangentBinding() == vgd::node::BIND_PER_VERTEX )
			{
				tangentComputation = boost::algorithm::replace_all_copy( templateMethodStr, "Value", "tangent" );
				boost::algorithm::replace_all( tangentComputation, "vec4", "vec3" );
				boost::algorithm::replace_all( tangentComputation, "mgl_Source1", "mgl_Tangent1" );
			}

			glslState.setShaderStage( GLSLState::VERTEX_NORMAL_COMPUTATION, normalComputation + "\n" + tangentComputation );

			// @todo texCoord ? and texture

			// do the rendering
			vsHandler.apply( engine, mesh0 );

			// Restores state
			engine->getUniformState().removeUniform( "geoMorphWeights" );
			engine->getGLSLStateStack().pop();
		}
	}

	node->getDirtyFlag(node->getDFNode())->validate();
}



void GeoMorph::setToDefaults()
{
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
