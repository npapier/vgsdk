// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Fluid.hpp"

#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>

#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/Fluid.hpp>
#include <vgd/node/Grid.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Program.hpp>
#include <vgd/node/Separator.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vge/rc/Manager.hpp>
#include <vge/service/Painter.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/GLSLState.hpp"
#include "vgeGL/rc/Texture2D.hpp"
#include "vgeGL/rc/Fluid.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( Fluid );



const vge::handler::Handler::TargetVector Fluid::getTargets() const
{
	TargetVector targets;

	targets.reserve( 1 );
	targets.push_back( vgd::node::Fluid::getClassIndexStatic() );

	return targets;
}



void Fluid::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	assert( dynamic_cast< vgd::node::Fluid* >(pNode) != 0 );
	vgd::node::Fluid *pCastedNode = static_cast< vgd::node::Fluid* >(pNode);

	paint( pGLEngine, pCastedNode );
}



void Fluid::unapply ( vge::engine::Engine* engine, vgd::node::Node* pNode )
{}



void Fluid::setToDefaults()
{}



void Fluid::paint( vgeGL::engine::Engine * engine, vgd::node::Fluid * fluid )
{
	using vgd::node::Texture;

	vgeGL::engine::Engine::GLManagerType& rcManager = engine->getGLManager();
	vgd::Shp< vgeGL::rc::Fluid > fluidRC = rcManager.getShp< vgeGL::rc::Fluid >( fluid );

	if ( fluidRC )
	{
		using vgeGL::engine::GLSLState;

		// Saves texture mapping state
		const bool isTextureMappingEnabledBak	= engine->setTextureMappingEnabled(true);
		const bool isTexture2DRegarded = engine->isRegardedIfIsA< vgd::node::Texture2D >();
		engine->regardIfIsA< vgd::node::Texture2D >();

		//
/*		std::stringstream ssBegin;
		ssBegin << "BEGIN: fluid rendering";
		glStringMarkerGREMEDY( 0, ssBegin.str().c_str() );*/

		//
		engine->paint( fluidRC->separator, true );

		
//		engine->resetMatrices();

		GLSLState& glslState = engine->getGLSLState();

		glslState.setShaderStage( GLSLState::VERTEX_DECLARATIONS, "out float fluidHeight;\n" );

		const std::string ecPosition_gl_Position_displacementMapping =
		"	vec4 sceneVertex = texture( texMap2D[0], (gl_TextureMatrix[0] * mgl_MultiTexCoord0).xy);\n"
		"	if ( sceneVertex.z == 0 )\n"
//		"	if ( (sceneVertex.x == 0) && (sceneVertex.y == 0) && (sceneVertex.z == 0) )\n"
		"	{\n"
		"		ecPosition = vec4(0, 0, 0, -1);\n"
		"		gl_Position = vec4(0, 0, 0, -1);\n"
		"	}\n"
		"	else\n"
		"	{\n"
		"		ecPosition	= gl_ModelViewMatrix * sceneVertex;\n"
		"		gl_Position = gl_ModelViewProjectionMatrix * sceneVertex;\n"
		"	}\n"
		"\n";
		glslState.setShaderStage( GLSLState::VERTEX_GL_POSITION_COMPUTATION, ecPosition_gl_Position_displacementMapping );

		glslState.setShaderStage( GLSLState::VERTEX_ECPOSITION_COMPUTATION, "" );

		glslState.setShaderStage( GLSLState::VERTEX_ECNORMAL_COMPUTATION,
		"	vec4 normal = texture( texMap2D[1], (gl_TextureMatrix[0] * mgl_MultiTexCoord0).xy );\n"
		"	ecNormal = gl_NormalMatrix * normal.xyz;\n" );

		glslState.setShaderStage( GLSLState::FRAGMENT_DECLARATIONS, "in float fluidHeight;\n" );

		std::string fragmentOutputStr = 
		"	if ( fluidHeight <= OPACITY )\n"
		"	{\n"
		"		discard;\n"
		"	}\n"
		/*"	else\n"
		"	{\n"
		"		const float p = OPACITY;\n"
		"		float alpha;\n"
		"		if ( fluidHeight >= p )\n"
		"		{\n"
		"			alpha = 1.0;\n"
		"		}\n"
		"		else\n"
		"		{\n"
		"			alpha = fluidHeight/p;\n"
		"		}\n"
		"		gl_FragData[0] = vec4(color.rgb, alpha);\n"*/
		"		gl_FragData[0] = color;\n"
		//"	}\n"
		"\n";

		const std::string opacityStr = boost::lexical_cast<std::string>( fluid->getOpacity() );
		boost::algorithm::replace_all( fragmentOutputStr, "OPACITY", opacityStr );
		glslState.setShaderStage( GLSLState::FRAGMENT_OUTPUT, fragmentOutputStr );

		// fluid position map
		vgd::Shp< vgd::node::Texture2D > fluidPositionMap = fluidRC->heightMaps[4];
		if ( fluidPositionMap->getMultiAttributeIndex() != 0 ) fluidPositionMap->setMultiAttributeIndex( 0 );
		//fluidPositionMap->setVertexFunction( displacementMapping );

// @todo discard fragment if fluidHeight < threshold
//		fluidPositionMap->setFilter( Texture::MIN_FILTER, Texture::LINEAR );
//		fluidPositionMap->setFilter( Texture::MAG_FILTER, Texture::LINEAR );
		engine->paint( fluidPositionMap );
//		fluidPositionMap->setFilter( Texture::MIN_FILTER, Texture::NEAREST );
//		fluidPositionMap->setFilter( Texture::MAG_FILTER, Texture::NEAREST );

		// fluid normal map
		vgd::Shp< vgd::node::Texture2D > fluidNormalMap = fluidRC->heightMaps[5];
		if ( fluidNormalMap->getMultiAttributeIndex() != 1 ) fluidNormalMap->setMultiAttributeIndex( 1 );
//		fluidNormalMap->setFilter( Texture::MIN_FILTER, Texture::LINEAR );
//		fluidNormalMap->setFilter( Texture::MAG_FILTER, Texture::LINEAR );
		engine->paint( fluidNormalMap );
//		fluidNormalMap->setFilter( Texture::MIN_FILTER, Texture::NEAREST );
//		fluidNormalMap->setFilter( Texture::MAG_FILTER, Texture::NEAREST );

		// fluid height map
		vgd::Shp< vgd::node::Texture2D > fluidHeightMap = fluidRC->heightMaps[1];
		if ( fluidHeightMap->getMultiAttributeIndex() != 2 )
		{
			fluidHeightMap->setMultiAttributeIndex( 2 );
			fluidHeightMap->setVertexFunction(
				"	fluidHeight = texture( texMap2D[2], mgl_TexCoord[0].xy ).x;\n" );
		}

// @todo done in FRAGMENT_OUTPUT but could be better done here => fluidHeightMap->setFragmentFunction( "	color = vec4( color.rgb, fluidHeight );\n" );
// @todo optme
//		fluidHeightMap->setFilter( Texture::MIN_FILTER, Texture::LINEAR );
//		fluidHeightMap->setFilter( Texture::MAG_FILTER, Texture::LINEAR );
		engine->paint( fluidHeightMap );
//		fluidHeightMap->setFilter( Texture::MIN_FILTER, Texture::NEAREST );
//		fluidHeightMap->setFilter( Texture::MAG_FILTER, Texture::NEAREST );

		engine->paint( fluidRC->grid );

		engine->paint( fluidRC->separator, false );

		//
		/*std::stringstream ssEnd;
		ssEnd << "END: fluid rendering";
		glStringMarkerGREMEDY( 0, ssEnd.str().c_str() );*/

		// Restores texture mapping state
		engine->setTextureMappingEnabled( isTextureMappingEnabledBak );
		if ( isTexture2DRegarded )
		{
			engine->regardIfIsA< vgd::node::Texture2D >(); // @todo refardIfIsA<>( bool enabled = true );
		}
		else
		{
			engine->disregardIfIsA< vgd::node::Texture2D >();
		}
	}
	// else nothing to do
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
