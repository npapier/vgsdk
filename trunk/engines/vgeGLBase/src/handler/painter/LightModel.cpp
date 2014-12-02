//// VGSDK - Copyright (C) 2004, 2006, 2008, 2009, 2010, 2011, 2012, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/handler/painter/LightModel.hpp"
//
//#include <vgd/field/DirtyFlag.hpp>
//#include <vgd/node/LightModel.hpp>
//
//#include <vge/rc/Manager.hpp>
//#include <vge/service/Painter.hpp>
//
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
//META_HANDLER_CPP( LightModel );
//
//
//
//const vge::handler::Handler::TargetVector LightModel::getTargets() const
//{
//	TargetVector targets;
//
//	targets.push_back( vgd::node::LightModel::getClassIndexStatic() );
//
//	return targets;
//}
//
//
//
//void LightModel::apply( vge::engine::Engine * engine, vgd::node::Node * node )
//{
//	assert( dynamic_cast< vgeGLBase::engine::Engine* >(engine) != 0 );
//	vgeGLBase::engine::Engine *glEngine = static_cast< vgeGLBase::engine::Engine* >(engine);
//
//	assert( dynamic_cast< vgd::node::LightModel* >(node) != 0 );
//	vgd::node::LightModel *lightModel = static_cast< vgd::node::LightModel* >(node);
//
//	// Retrieves GLSL state
//	using vgeGLBase::engine::GLSLState;
//	GLSLState& state = glEngine->getGLSLState();
//
//	bool isDefined;
//
//	// MODEL
//	if ( glEngine->isLightingEnabled() )
//	{
//		vgd::node::LightModel::ModelValueType modelValue;
//		isDefined = lightModel->getModel( modelValue );
//
//		if ( isDefined )
//		{
//// @todo STANDARD_PER_VERTEX
//			if ( modelValue == vgd::node::LightModel::STANDARD_PER_VERTEX )
//			{
//				vgLogDebug( "LightModel::STANDARD_PER_VERTEX is temporarily disabled. Reverts to standard per pixel lighting." );
//				modelValue = vgd::node::LightModel::STANDARD_PER_PIXEL;
//			}
//// end todo
//			// Updates GLSLState
//			// LIGHTING
//			state.setLightingEnabled( modelValue != vgd::node::LightModel::LIGHTING_OFF );
//
//			// PER_PIXEL_LIGHTING
//			state.setPerPixelLightingEnabled( modelValue == vgd::node::LightModel::STANDARD_PER_PIXEL );
//		}
//
//		// LOCAL_VIEWER
//		vgd::node::LightModel::ViewerValueType viewerValue;
//		isDefined = lightModel->getViewer( viewerValue );
//
//		if ( isDefined )
//		{
//			// Updates GLSLState
//			state.setEnabled( vgeGLBase::engine::LOCAL_VIEWER, viewerValue == vgd::node::LightModel::AT_EYE );
//		}
//
//		// TWO_SIDED_LIGHTING
//		vgd::node::LightModel::TwoSidedValueType twoSidedValue;
//		isDefined = lightModel->getTwoSided( twoSidedValue );
//
//		if ( isDefined )
//		{
//			// Updates GLSLState
//			state.setTwoSidedLightingEnabled( twoSidedValue );
//		}
//	}
//	else
//	{
//		// NO LIGHTING
//		state.setLightingEnabled( false );
//	}
//
//	// SHADOW
//	if ( glEngine->isTextureMappingEnabled() && glEngine->isShadowEnabled() )
//	{
//		vgd::node::LightModel::ShadowValueType shadow;
//		isDefined = lightModel->getShadow( shadow );
//
//		if ( isDefined )
//		{
//			// Updates GLSLState
//			// SHADOW
//			state.setShadowType( shadow );
//
//			// SAMPLING SIZE
//			vgd::node::LightModel::SamplingSizeValueType samplingSize = lightModel->getSamplingSize();
//			glEngine->getBuiltinUniformState().sethUniform( "u_samplingSize", samplingSize );
//
//			// SHADOW QUALITY ?
//
//			// SHADOW MAP TYPE
//			vgd::node::LightModel::ShadowMapTypeValueType shadowMapType = lightModel->getShadowMapType();
//			state.setShadowMapType( shadowMapType );
//
//			// ILLUMINATION IN SHADOW
//			vgd::node::LightModel::IlluminationInShadowValueType illuminationInShadow = lightModel->getIlluminationInShadow();
//			glEngine->getBuiltinUniformState().sethUniform( "u_illuminationInShadow", illuminationInShadow );
//		}
//	}
//	else
//	{
//		state.setShadowType( vgd::node::LightModel::SHADOW_OFF );
//	}
//
//	// POSTPROCESSING
//	if ( lightModel->getIgnorePostProcessing() )
//	{
//		state.setEnabled( vgeGLBase::engine::IGNORE_POST_PROCESSING );
//	}
//
//	// BumpMapping
//	state.setBumpMappingEnabled( lightModel->getBumpMapping() );
//
//	//
//	vgeGLBase::rc::applyUsingDisplayList< vgd::node::LightModel, LightModel >( engine, node, this );
//}
//
//
//
//void LightModel::unapply ( vge::engine::Engine* , vgd::node::Node*  )
//{}
//
//
//
//void LightModel::setToDefaults()
//{
//	const vgm::Vec4f defaultAmbientValue( 0.2f, 0.2f, 0.2f, 0.0f );
//	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, defaultAmbientValue.getValue() );
//}
//
//
//
//void LightModel::paint( vgeGLBase::engine::Engine * engine, vgd::node::LightModel *node )
//{
//	bool bDefined;
//
//	// MODEL
//	vgd::node::LightModel::ModelValueType	modelValue;
//
//	bDefined = node->getModel( modelValue );
//
//	if ( bDefined )
//	{
//		switch ( modelValue.value() )
//		{
//			case vgd::node::LightModel::LIGHTING_OFF:
//				glDisable( GL_LIGHTING );
//				break;
//
//			case vgd::node::LightModel::STANDARD_PER_VERTEX:
//				glEnable( GL_LIGHTING );
//				break;
//
//			case vgd::node::LightModel::STANDARD_PER_PIXEL:
//				glEnable( GL_LIGHTING );
//				if ( !engine->isGLSLEnabled() )
//				{
//					// Fallback to standard per vertex
//					vgLogDebug("LightModel::STANDARD_PER_PIXEL is only available when GLSL is enabled. Reverts to standard per vertex lighting.");
//				}
//				// else nothing to do
//				break;
//
//			default:
//				vgAssertN( false, "Unknown LightModel.model value." );
//		}
//	}
//
//	// AMBIENT
//	vgm::Vec4f	ambientValue;
//	bDefined = node->getAmbient( ambientValue );
//	
//	if ( bDefined )
//	{
//		glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambientValue.getValue() );
//	}
//	
//	// VIEWER
//	vgd::node::LightModel::ViewerValueType	viewerValue;
//	bDefined = node->getViewer( viewerValue );
//	
//	if ( bDefined )
//	{
//		if ( viewerValue == vgd::node::LightModel::AT_INFINITY )
//		{
//			glLightModelf( GL_LIGHT_MODEL_LOCAL_VIEWER, 0.f );
//		}
//		else
//		{
//			assert( viewerValue == vgd::node::LightModel::AT_EYE );
//			glLightModelf( GL_LIGHT_MODEL_LOCAL_VIEWER, 1.f );
//		}
//	}
//
//	// TWOSIDED
//	vgd::node::LightModel::TwoSidedValueType	twosidedValue;
//	bDefined = node->getTwoSided( twosidedValue );
//
//	if ( bDefined )
//	{
//		if ( twosidedValue )
//		{
//			glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );
//			glEnable( GL_VERTEX_PROGRAM_TWO_SIDE );
//		}
//		else
//		{
//			glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
//			glDisable( GL_VERTEX_PROGRAM_TWO_SIDE );
//		}
//	}
//
//	// Validates node
//	node->getDirtyFlag(node->getDFNode())->validate();
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