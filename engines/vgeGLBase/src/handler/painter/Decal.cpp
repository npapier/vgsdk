//// VGSDK - Copyright (C) 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/handler/painter/Decal.hpp"
//
//#include <vgd/field/DirtyFlag.hpp>
//#include <vgd/node/Decal.hpp>
//#include <vgd/node/Texture2D.hpp>
//#include <vgd/node/VertexShape.hpp>
//#include "vgeGLBase/engine/Engine.hpp"
//#include "vgeGLBase/rc/Texture2D.hpp"
//
//
//
//namespace vgeGLBase
//{
//
//namespace handler
//{
//
//namespace painter
//{
//
//
//
//META_HANDLER_CPP( Decal );
//
//
//
//const vge::handler::Handler::TargetVector Decal::getTargets() const
//{
//	TargetVector targets;
//
//	targets.reserve( 1 );
//	targets.push_back( vgd::node::Decal::getClassIndexStatic() );
//
//	return targets;
//}
//
//
//
//void Decal::apply( vge::engine::Engine* baseEngine, vgd::node::Node * node )
//{
//	assert( dynamic_cast< vgeGLBase::engine::Engine* >(baseEngine) != 0 );
//	vgeGLBase::engine::Engine * engine = static_cast< vgeGLBase::engine::Engine* >(baseEngine);
//
//	assert( dynamic_cast< vgd::node::Decal* >(node) != 0 );
//	vgd::node::Decal * decal = static_cast< vgd::node::Decal* >(node);
//
//	// Updates engine state
//	if ( engine->isGLSLEnabled() )
//	{
//		using vgeGLBase::engine::GLSLState;
//		GLSLState& glslState = engine->getGLSLState();
//
//		// Gets the transformation applied to the shape
//		vgm::MatrixR& current( engine->getGeometricalMatrix().getTop() );
//
//		//
//		vgd::Shp< GLSLState::DecalState > decalState( new GLSLState::DecalState(decal, current) );
//
//		const int multiAttributeIndex = computeMultiAttributeIndex( decal, glslState.decals );
//		glslState.decals.setState( multiAttributeIndex, decalState );
//	}
//
//	// Validates node df
//	node->getDirtyFlag(node->getDFNode())->validate();
//}
//
//
//
//void Decal::unapply( vge::engine::Engine* engine, vgd::node::Node* pNode )
//{}
//
//
//
//void Decal::setToDefaults()
//{}
//
//
//
//void Decal::paint( vgeGLBase::engine::Engine * engine, DecalStateContainer * decals )
//{
//	typedef vgeGLBase::engine::GLSLState::DecalState DecalState;
//
//	// Makes a backup of GLSL activation state
//	using vgeGLBase::engine::Engine;
//	vgd::Shp< Engine::GLSLActivationState > glslActivationState = engine->getGLSLActivationState();
//	engine->sethCurrentProgram();
//
//	const bool isTextureMappingEnabledBAK = engine->setTextureMappingEnabled(true);
//
//	//
//	glDisable( GL_LIGHTING );
//
//	// Depth buffer configuration
//	glDepthMask( GL_FALSE );
//	glDepthFunc( GL_LEQUAL );
//	glEnable( GL_DEPTH_TEST );
//
//	glEnable( GL_POLYGON_OFFSET_FILL );
//	glPolygonOffset( -1.f, -1.f );
//
//	//
//	uint numFound = 0;
//	for( uint i = 0; numFound < decals->getNum(); ++i )
//	{
//		vgd::Shp< DecalState > decalState = decals->getState(i);
//
//		if ( decalState )
//		{
//			++numFound;
//			const vgd::node::Decal *decal = decalState->getNode();
//			if ( decal )
//			{
//				using vgd::node::Texture2D;
//				using vgd::node::VertexShape;
//
//				vgd::Shp< Texture2D >	texture	= decal->getTexture();
//				vgd::Shp< VertexShape >	shape	= decal->getShape();
//
//				if ( !texture )
//				{
//					vgLogDebug("No texture in Decal node named '%s'", decal->getName().c_str() );
//					continue;
//				}
//
//				if ( !shape )
//				{
//					vgLogDebug("No shape in Decal node named '%s'", decal->getName().c_str() );
//					continue;
//				}
//
//				engine->paint( texture );
//
//				// Gets the resource manager
//				vgd::Shp< vgeGLBase::engine::Engine::GLManagerType > rcManager = engine->getGLManager();
//				vgeGLBase::rc::Texture2D * gloTex2D = rcManager->get< vgeGLBase::rc::Texture2D >( texture.get() );
//				gloTex2D->env( GL_TEXTURE_ENV_MODE, GL_REPLACE );
//
//				const vgm::MatrixR& geomMatrix = decalState->getGeometricalMatrix();
//				glMatrixMode( GL_MODELVIEW );
//				glLoadMatrixf( reinterpret_cast<const float*>( geomMatrix.getValue() ) );
//
//				// Properties of Decal node
//				//	Decal.alphaTest
//				if ( decal->getAlphaTest() )
//				{
//					glEnable( GL_ALPHA_TEST );
//					glAlphaFunc( GL_GREATER, 0.f );
//				}
//				else
//				{
//					glDisable( GL_ALPHA_TEST );
//				}
//
//				//	Decal.blending
//				if ( decal->getBlending() )
//				{
//					glEnable( GL_BLEND );
//					glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
//				}
//				else
//				{
//					glDisable( GL_BLEND );
//				}
//
//				//
//				engine->paint( shape );
//			}
//		}
//	}
//
//	//
//	engine->setTextureMappingEnabled(isTextureMappingEnabledBAK);
//
//	// Restores GLSL activation state
//	engine->setGLSLActivationState( glslActivationState );
//}
//
//
//
//} // namespace painter
//
//} // namespace handler
//
//} // namespace vgeGLBase
//