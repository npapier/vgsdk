//// VGSDK - Copyright (C) 2004, 2008, 2011, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/handler/painter/DirectionalLight.hpp"
//
//#include <vgd/node/DirectionalLight.hpp>
//#include "vgeGLBase/engine/Engine.hpp"
//#include "vgeGLBase/engine/GLSLState.hpp"
//#include "vgeGLBase/rc/TDisplayListHelper.hpp"
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
//	assert( dynamic_cast< vgeGLBase::engine::Engine* >(engine) != 0 );
//	vgeGLBase::engine::Engine *glEngine = static_cast< vgeGLBase::engine::Engine* >(engine);
//
//	assert( dynamic_cast< vgd::node::DirectionalLight* >(node) != 0 );
//	vgd::node::DirectionalLight *directionalLight = static_cast< vgd::node::DirectionalLight* >(node);
//
//	//
//	updateGLSLState( glEngine, directionalLight, glEngine->getGLSLState() );
//
//	//
//	vgeGLBase::rc::applyUsingDisplayList<vgd::node::DirectionalLight, DirectionalLight>( engine, node, this );
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
//void DirectionalLight::updateGLSLState( vgeGLBase::engine::Engine * engine, vgd::node::DirectionalLight * light, vgeGLBase::engine::GLSLState& glslState )
//{
//	using vgeGLBase::engine::GLSLState;
//	typedef vgeGLBase::engine::LightState LightState;
//
//	// Updates GLSL state
//	glslState.setEnabled( vgeGLBase::engine::DIRECTIONAL_LIGHT );
//
//	/* @todo
//	if ( !glslState.isEnabled( vgeGLBase::engine::DIRECTIONAL_LIGHT_CASTING_SHADOW ) )
//	{
//		const bool castShadow = light->getCastShadow();
//		if ( castShadow )	glslState.setEnabled( vgeGLBase::engine::DIRECTIONAL_LIGHT_CASTING_SHADOW );
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
//		lightState.reset( new LightState(vgeGLBase::engine::DIRECTIONAL_LIGHT) );
//		glslState.lights.setState( unit, lightState );
//	}
//	else
//	{
//		// type
//		lightState->setLightType( vgeGLBase::engine::DIRECTIONAL_LIGHT );
//		glslState.lights.dirty();
//	}
//
//	updateUnitState( engine, light, lightState );
//}
//
//
//void DirectionalLight::updateUnitState( vgeGLBase::engine::Engine * engine, vgd::node::DirectionalLight * light, vgd::Shp< vgeGLBase::engine::LightState > lightState )
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
//void DirectionalLight::paint( vgeGLBase::engine::Engine *pGLEngine, vgd::node::DirectionalLight *pDirectionalLight )
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
//} // namespace vgeGLBase
//