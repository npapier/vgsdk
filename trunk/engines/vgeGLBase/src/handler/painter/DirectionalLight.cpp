//// VGSDK - Copyright (C) 2004, 2008, 2011, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGL/handler/painter/DirectionalLight.hpp"
//
//#include <vgd/node/DirectionalLight.hpp>
//#include "vgeGL/engine/Engine.hpp"
//#include "vgeGL/engine/GLSLState.hpp"
//#include "vgeGL/rc/TDisplayListHelper.hpp"
//
//
//
//namespace vgeGL
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
//META_HANDLER_CPP( DirectionalLight );
//
//
//
//const vge::handler::Handler::TargetVector DirectionalLight::getTargets() const
//{
//	vge::handler::Handler::TargetVector targets;
//
//	targets.push_back( vgd::node::DirectionalLight::getClassIndexStatic() );
//
//	return targets;
//}
//
//
//
//void DirectionalLight::apply( vge::engine::Engine * engine, vgd::node::Node * node )
//{
//	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
//	vgeGL::engine::Engine *glEngine = static_cast< vgeGL::engine::Engine* >(engine);
//
//	assert( dynamic_cast< vgd::node::DirectionalLight* >(node) != 0 );
//	vgd::node::DirectionalLight *directionalLight = static_cast< vgd::node::DirectionalLight* >(node);
//
//	//
//	updateGLSLState( glEngine, directionalLight, glEngine->getGLSLState() );
//
//	//
//	vgeGL::rc::applyUsingDisplayList<vgd::node::DirectionalLight, DirectionalLight>( engine, node, this );
//}
//
//
//
//void DirectionalLight::unapply ( vge::engine::Engine*, vgd::node::Node* )
//{}
//
//
//
//void DirectionalLight::setToDefaults()
//{
//	Light::setToDefaults();
//}
//
//
//
//void DirectionalLight::updateGLSLState( vgeGL::engine::Engine * engine, vgd::node::DirectionalLight * light, vgeGL::engine::GLSLState& glslState )
//{
//	using vgeGL::engine::GLSLState;
//	typedef vgeGL::engine::LightState LightState;
//
//	// Updates GLSL state
//	glslState.setEnabled( vgeGL::engine::DIRECTIONAL_LIGHT );
//
//	/* @todo
//	if ( !glslState.isEnabled( vgeGL::engine::DIRECTIONAL_LIGHT_CASTING_SHADOW ) )
//	{
//		const bool castShadow = light->getCastShadow();
//		if ( castShadow )	glslState.setEnabled( vgeGL::engine::DIRECTIONAL_LIGHT_CASTING_SHADOW );
//	}
//	*/
//
//	// Light state
//	const uint unit = light->getMultiAttributeIndex();
//
//	vgd::Shp< LightState > lightState = glslState.lights.getState( unit );
//
//	if ( !lightState )
//	{
//		// Creates a new unit state
//		// type
//		lightState.reset( new LightState(vgeGL::engine::DIRECTIONAL_LIGHT) );
//		glslState.lights.setState( unit, lightState );
//	}
//	else
//	{
//		// type
//		lightState->setLightType( vgeGL::engine::DIRECTIONAL_LIGHT );
//		glslState.lights.dirty();
//	}
//
//	updateUnitState( engine, light, lightState );
//}
//
//
//void DirectionalLight::updateUnitState( vgeGL::engine::Engine * engine, vgd::node::DirectionalLight * light, vgd::Shp< vgeGL::engine::LightState > lightState )
//{
//	Light::updateUnitState( engine, light, lightState );
//
//	// Updates unit state
//	// DIRECTION field
//	vgd::node::DirectionalLight::DirectionValueType direction;
//	bool bDefined = light->getDirection( direction );
//	if ( bDefined )		lightState->setDirection( direction );
//}
//
//
//void DirectionalLight::paint( vgeGL::engine::Engine *pGLEngine, vgd::node::DirectionalLight *pDirectionalLight )
//{
//	// render Light fields.
//	Light::paint( pGLEngine, pDirectionalLight );
//
//	// render DirectionalLight fields.
//	GLenum lightIndex;
//	bool bDefined;
//	vgm::Vec3f direction;
//
//	lightIndex	= GL_LIGHT0 + pDirectionalLight->getMultiAttributeIndex();
//
//	bDefined	= pDirectionalLight->getDirection( direction );
//
//	if ( bDefined )
//	{
//		// use direction field
//		vgm::Vec4f positionGL(
//				-direction[0], -direction[1], -direction[2],	// direction of light
//				0.f 											// directional light
//				);
//
//		// direction of light is set by GL_POSITION for directional light
//		glLightfv( lightIndex, GL_POSITION, positionGL.getValue() );
//	}
//
//	// Validates node
//	pDirectionalLight->getDirtyFlag(pDirectionalLight->getDFNode())->validate();
//}
//
//
//
//} // namespace painter
//
//} // namespace handler
//
//} // namespace vgeGL
//