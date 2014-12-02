//// VGSDK - Copyright (C) 2013, 2014, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/handler/painter/Displacement.hpp"
//
//#include <vgd/node/Displacement.hpp>
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
//META_HANDLER_CPP( Displacement );
//
//
//
//const Displacement::TargetVector Displacement::getTargets() const
//{
//	TargetVector targets;
//
//	targets.push_back( vgd::node::Displacement::getClassIndexStatic() );
//
//	return targets;
//}
//
//
//void Displacement::apply( vge::engine::Engine * engine, vgd::node::Node * node )
//{
//	assert( dynamic_cast< vgeGLBase::engine::Engine* >(engine) != 0 );
//	vgeGLBase::engine::Engine *glEngine = static_cast< vgeGLBase::engine::Engine* >(engine);
//
//	assert( dynamic_cast< vgd::node::Displacement* >(node) != 0 );
//	vgd::node::Displacement *displacement = dynamic_cast< vgd::node::Displacement* >(node);
//
//
//	// Retrieves GLSL state
//	using vgeGLBase::engine::GLSLState;
//	GLSLState& glslState = glEngine->getGLSLState();
//
//
//	// Updates GLSL state
//	if ( glslState.isDisabled(vgeGLBase::engine::DISPLACEMENT) )
//	{
//		glslState.setEnabled(vgeGLBase::engine::DISPLACEMENT);
//	}
//
//
//	// COMPOSE MODE
//	const vgd::field::Enum composeMode = displacement->getComposeMode();
//
//	// VERTEX SHADER PART
//	static std::string displacementAlongNormalVS = "position += uDisplacementParameter4f0.x * vec4(normalize(normal),0);\n";
//
//	vgd::node::Displacement::PredefinedDisplacementValueType function;
//	const bool hasDisplacementFunctionVS = displacement->getDisplacementFunctionVS( function );
//
//	if ( hasDisplacementFunctionVS )
//	{
//		switch ( function.value() )
//		{
//			case vgd::node::Displacement::NONE:
//				switch ( composeMode.value() )
//				{
//					case vgd::node::Displacement::REPLACE:
//						glslState.resetShaderStage( GLSLState::VERTEX_POSITION_DISPLACEMENT );
//						break;
//					case vgd::node::Displacement::PREPEND:
//						glslState.prependShaderStage( GLSLState::VERTEX_POSITION_DISPLACEMENT, glslState.getShaderStageDefault(GLSLState::VERTEX_POSITION_DISPLACEMENT) );
//						break;
//					case vgd::node::Displacement::APPEND:
//						glslState.appendShaderStage( GLSLState::VERTEX_POSITION_DISPLACEMENT, glslState.getShaderStageDefault(GLSLState::VERTEX_POSITION_DISPLACEMENT) );
//						break;
//					default:
//						vgAssertN( false, "Unexpected value for Displacement.composeMode" );
//				}
//				break;
//
//			case vgd::node::Displacement::ALONG_NORMAL:
//				switch ( composeMode.value() )
//				{
//					case vgd::node::Displacement::REPLACE:
//						glslState.setShaderStage( GLSLState::VERTEX_POSITION_DISPLACEMENT, displacementAlongNormalVS );
//						break;
//					case vgd::node::Displacement::PREPEND:
//						glslState.prependShaderStage( GLSLState::VERTEX_POSITION_DISPLACEMENT, displacementAlongNormalVS );
//						break;
//					case vgd::node::Displacement::APPEND:
//						glslState.appendShaderStage( GLSLState::VERTEX_POSITION_DISPLACEMENT, displacementAlongNormalVS );
//						break;
//					default:
//						vgAssertN( false, "Unexpected value for Displacement.composeMode" );
//				}
//				break;
//
//			case vgd::node::Displacement::CUSTOM:
//			{
//				//	declarationsVS and displacementVS
//				const std::string& declarationsVSStr = displacement->getDeclarationsVS();
//				const std::string& displacementVSStr = displacement->getDisplacementVS();
//
//				switch ( composeMode.value() )
//				{
//					case vgd::node::Displacement::REPLACE:
//						if ( declarationsVSStr.size() > 0 )	glslState.setShaderStage( GLSLState::VERTEX_DECLARATIONS, declarationsVSStr );
//						if ( displacementVSStr.size() > 0 )	glslState.setShaderStage( GLSLState::VERTEX_POSITION_DISPLACEMENT, displacementVSStr );
//						break;
//					case vgd::node::Displacement::PREPEND:
//						if ( declarationsVSStr.size() > 0 )	glslState.prependShaderStage( GLSLState::VERTEX_DECLARATIONS, declarationsVSStr );
//						if ( displacementVSStr.size() > 0 )	glslState.prependShaderStage( GLSLState::VERTEX_POSITION_DISPLACEMENT, displacementVSStr );
//						break;
//					case vgd::node::Displacement::APPEND:
//						if ( declarationsVSStr.size() > 0 )	glslState.appendShaderStage( GLSLState::VERTEX_DECLARATIONS, declarationsVSStr );
//						if ( displacementVSStr.size() > 0 )	glslState.appendShaderStage( GLSLState::VERTEX_POSITION_DISPLACEMENT, displacementVSStr );
//						break;
//					default:
//						vgAssertN( false, "Unexpected value for Displacement.composeMode" );
//				}
//				break;
//			}
//			break;
//
//			default:
//				vgAssertN( false, "Unknown value for displacement.displacementFunctionVS field %i", function.value() );
//		}
//	}
//	// else do nothing
//
//
//	// TESSELLATION EVALUATION SHADER PART
//	static std::string displacementAlongNormalTES = "position += uDisplacementParameter4f0.y * vec4(normalize(normal),0);\n";
//
//	const bool hasDisplacementFunctionTES = displacement->getDisplacementFunctionTES( function );
//
//	if ( hasDisplacementFunctionTES )
//	{
//		switch ( function.value() )
//		{
//			case vgd::node::Displacement::NONE:
//				switch ( composeMode.value() )
//				{
//					case vgd::node::Displacement::REPLACE:
//						glslState.resetShaderStage( GLSLState::TES_POSITION_DISPLACEMENT );
//						break;
//					case vgd::node::Displacement::PREPEND:
//						glslState.prependShaderStage( GLSLState::TES_POSITION_DISPLACEMENT, glslState.getShaderStageDefault(GLSLState::TES_POSITION_DISPLACEMENT) );
//						break;
//					case vgd::node::Displacement::APPEND:
//						glslState.appendShaderStage( GLSLState::TES_POSITION_DISPLACEMENT, glslState.getShaderStageDefault(GLSLState::TES_POSITION_DISPLACEMENT) );
//						break;
//					default:
//						vgAssertN( false, "Unexpected value for Displacement.composeMode" );
//				}
//				break;
//
//			case vgd::node::Displacement::ALONG_NORMAL:
//				switch ( composeMode.value() )
//				{
//					case vgd::node::Displacement::REPLACE:
//						glslState.setShaderStage( GLSLState::TES_POSITION_DISPLACEMENT, displacementAlongNormalTES );
//						break;
//					case vgd::node::Displacement::PREPEND:
//						glslState.prependShaderStage( GLSLState::TES_POSITION_DISPLACEMENT, displacementAlongNormalTES );
//						break;
//					case vgd::node::Displacement::APPEND:
//						glslState.appendShaderStage( GLSLState::TES_POSITION_DISPLACEMENT, displacementAlongNormalTES );
//						break;
//					default:
//						vgAssertN( false, "Unexpected value for Displacement.composeMode" );
//				}
//				break;
//
//			case vgd::node::Displacement::CUSTOM:
//			{
//				//	declarationsTES and displacementTES
//				const std::string& declarationsTESStr = displacement->getDeclarationsTES();
//				const std::string& displacementTESStr = displacement->getDisplacementTES();
//
//				switch ( composeMode.value() )
//				{
//					case vgd::node::Displacement::REPLACE:
//						if ( declarationsTESStr.size() > 0 )	glslState.setShaderStage( GLSLState::TES_DECLARATIONS, declarationsTESStr );
//						if ( displacementTESStr.size() > 0 )	glslState.setShaderStage( GLSLState::TES_POSITION_DISPLACEMENT, displacementTESStr );
//						break;
//					case vgd::node::Displacement::PREPEND:
//						if ( declarationsTESStr.size() > 0 )	glslState.prependShaderStage( GLSLState::TES_DECLARATIONS, declarationsTESStr );
//						if ( displacementTESStr.size() > 0 )	glslState.prependShaderStage( GLSLState::TES_POSITION_DISPLACEMENT, displacementTESStr );
//						break;
//					case vgd::node::Displacement::APPEND:
//						if ( declarationsTESStr.size() > 0 )	glslState.appendShaderStage( GLSLState::TES_DECLARATIONS, declarationsTESStr );
//						if ( displacementTESStr.size() > 0 )	glslState.appendShaderStage( GLSLState::TES_POSITION_DISPLACEMENT, displacementTESStr );
//						break;
//					default:
//						vgAssertN( false, "Unexpected value for Displacement.composeMode" );
//				}
//				break;
//			}
//			break;
//
//			default:
//				vgAssertN( false, "Unknown value for displacement.displacementFunctionTES field %i", function.value() );
//		}
//	}
//	// else do nothing
//}
//
//
//
//void Displacement::unapply( vge::engine::Engine *, vgd::node::Node * )
//{
//	// nothing to do
//}
//
//
//
//void Displacement::setToDefaults()
//{
//	// nothing to do
//}
//
//
//
//} // namespace basic
//
//} // namespace handler
//
//} // namespace vgeGLBase
//