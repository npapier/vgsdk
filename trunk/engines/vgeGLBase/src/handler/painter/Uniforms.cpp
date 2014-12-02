//// VGSDK - Copyright (C) 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/handler/painter/Uniforms.hpp"
//
//#include <iterator>
//#include <vgd/node/Uniforms.hpp>
//#include <vge/service/Painter.hpp>
//#include "vgeGLBase/engine/Engine.hpp"
//#include "vgeGLBase/engine/GLSLState.hpp"
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
//namespace
//{
//
//void setUniformStateFromField( vgd::node::Uniforms *uniformsNode, const std::string& fieldname, vgeGLBase::engine::Engine::UniformState& uniformState )
//{
//	const std::type_info& typeinfo = uniformsNode->getFieldType( fieldname );
//
//	using vgd::field::EditorRO;
//	using vgd::field::TSingleField;
//
//	if ( typeinfo == typeid(TSingleField<int>) )
//	{
//		const int& value = uniformsNode->getUniform<int>(fieldname);
//		uniformState.sethUniform( fieldname, value );
//	}
//	else if ( typeinfo == typeid(TSingleField<float>) )
//	{
//		const float& value = uniformsNode->getUniform<float>(fieldname);
//		uniformState.sethUniform( fieldname, value );
//	}
//	else if ( typeinfo == typeid(TSingleField<vgm::Vec2f>) )
//	{
//		const vgm::Vec2f& value = uniformsNode->getUniform<vgm::Vec2f>(fieldname);
//		uniformState.sethUniform( fieldname, value );
//	}
//	else if ( typeinfo == typeid(TSingleField<vgm::Vec3f>) )
//	{
//		const vgm::Vec3f& value = uniformsNode->getUniform<vgm::Vec3f>(fieldname);
//		uniformState.sethUniform( fieldname, value );
//	}
//	else if ( typeinfo == typeid(TSingleField<vgm::Vec4f>) )
//	{
//		const vgm::Vec4f& value = uniformsNode->getUniform<vgm::Vec4f>(fieldname);
//		uniformState.sethUniform( fieldname, value );
//	}
//	else if ( typeinfo == typeid(TSingleField<vgm::MatrixR>) )
//	{
//		const vgm::MatrixR& value = uniformsNode->getUniform<vgm::MatrixR>(fieldname);
//		uniformState.sethUniform( fieldname, value );
//	}
//	else
//	{
//		vgAssertN(false, "Unexpected type");
//	}
//}
//
//}
//
//
//
//META_HANDLER_CPP( Uniforms );
//
//
//
//const Uniforms::TargetVector Uniforms::getTargets() const
//{
//	TargetVector targets;
//
//	targets.push_back( vgd::node::Uniforms::getClassIndexStatic() );
//
//	return targets;
//}
//
//
//void Uniforms::apply( vge::engine::Engine * engine, vgd::node::Node * node )
//{
//	assert( dynamic_cast< vgeGLBase::engine::Engine* >(engine) != 0 );
//	vgeGLBase::engine::Engine *glEngine = static_cast< vgeGLBase::engine::Engine* >(engine);
//
//	assert( dynamic_cast< vgd::node::Uniforms* >(node) != 0 );
//	vgd::node::Uniforms *uniforms = dynamic_cast< vgd::node::Uniforms* >(node);
//
//
//	// Retrieves GLSL state and state of uniforms
//	using vgeGLBase::engine::GLSLState;
//	GLSLState& glslState = glEngine->getGLSLState();
//
//	typedef vgeGLBase::engine::Engine::UniformState UniformState;
//	UniformState& uniformState = glEngine->getUniformState();
//
//
//	// COMPOSEMODE field
//	if ( uniforms->getComposeMode() == vgd::node::Uniforms::REPLACE )
//	{
//		uniformState.clear();
//	}
//	else
//	{
//		vgAssertN( uniforms->getComposeMode() == vgd::node::Uniforms::APPEND, "Unexpected value for composeMode field for node named '%s'. Expected APPEND.", node->getName().c_str() );
//		// nothing to do
//	}
//
//	// Retrieves all field names
//	typedef std::vector< std::string > StringContainer;
//	StringContainer fieldNames;
//	uniforms->getFieldNames( fieldNames );
//
//	// For each field, do
//	for(	StringContainer::const_iterator	i		= fieldNames.begin(),
//											iEnd	= fieldNames.end();
//			i != iEnd;
//			++i )
//	{
//		const std::string fieldname = *i;
//		if ( uniforms->isUniform(fieldname) )
//		{
//			// fieldname contains an uniform variable
//			setUniformStateFromField( uniforms, fieldname, uniformState );
//		}
//	}
//
//	// Updates USER_DEFINED_UNIFORM_DECLARATIONS
//	const std::string uniformsDeclarations = uniformState.generateDeclarations();
//	glslState.setShaderStage( GLSLState::USER_DEFINED_UNIFORM_DECLARATIONS, uniformsDeclarations );
//}
//
//
//
//void Uniforms::unapply( vge::engine::Engine *, vgd::node::Node * )
//{
//	// nothing to do
//}
//
//
//
//void Uniforms::setToDefaults()
//{
//	// nothing to do
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