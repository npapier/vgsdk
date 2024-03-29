//// VGSDK - Copyright (C) 2007, 2008, 2009, 2010, 2012, 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/handler/painter/LayerPlan.hpp"
//
//
//#include <vgd/field/DirtyFlag.hpp>
//#include <vgd/node/Quad.hpp>
//#include <vgd/node/LayerPlan.hpp>
//#include <vgd/node/Texture2D.hpp>
//#include <vge/rc/Manager.hpp>
//#include <vge/service/Painter.hpp>
//#include "vgeGLBase/engine/Engine.hpp"
//#include <vgeGLBase/rc/Root.hpp>
////#include "vgeGLBase/rc/TDisplayListHelper.hpp"
//#include "vgeGLBase/rc/Texture2D.hpp"
//#include <vgm/operations.hpp>
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
//META_HANDLER_CPP( LayerPlan );
//
//
//
//const vge::handler::Handler::TargetVector LayerPlan::getTargets() const
//{
//	TargetVector targets;
//
//	targets.reserve( 1 );
//	targets.push_back( vgd::node::LayerPlan::getClassIndexStatic() );
//
//	return targets;
//}
//
//
//
//void LayerPlan::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
//{
//	vgAssert( dynamic_cast< vgeGLBase::engine::Engine* >(pEngine) != 0 );
//	vgeGLBase::engine::Engine *pGLEngine = static_cast< vgeGLBase::engine::Engine* >(pEngine);
//
//	vgAssert( dynamic_cast< vgd::node::LayerPlan* >(pNode) != 0 );
//	vgd::node::LayerPlan *pCastedNode = static_cast< vgd::node::LayerPlan* >(pNode);
//
//	paint( pGLEngine, pCastedNode );
//	// @todo conflict in manager between display list and vge::rc::Root for the same node (the LayerPlan)
//	// vgeGLBase::rc::applyUsingDisplayList< vgd::node::LayerPlan, LayerPlan >( pEngine, pNode, this );
//}
//
//
//
//void LayerPlan::unapply ( vge::engine::Engine* engine, vgd::node::Node* pNode )
//{}
//
//
//
//void LayerPlan::setToDefaults()
//{}
//
//
//
//
//// @todo Uses glsl for LayerPlan
//void LayerPlan::paint( vgeGLBase::engine::Engine *pGLEngine, vgd::node::LayerPlan *layerPlan )
//{
//	if (	(layerPlan->getImage() == 0) ||													// no image
//			(	(layerPlan->getImage() != 0) && layerPlan->getImage()->isEmpty()	)		// empty image
//			)
//	{
//		// Nothing to do
//		return;
//	}
//
//	// Searchs resource
//	vgd::Shp< vgeGLBase::engine::Engine::GLManagerType > rcManager = pGLEngine->getGLManager();
//
//	::glo::IResource 							*resource	= rcManager->getAbstract( layerPlan );
//	vgeGLBase::rc::Root								*rcRoot		= dynamic_cast< vgeGLBase::rc::Root* >(resource);
//
//	using vgd::node::Quad;
//	using vgd::node::Texture2D;
//
//	vgd::Shp< Quad >		quad;
//	vgd::Shp< Texture2D >	texture2D;
//
//	if ( resource )
//	{
//		vgAssert( rcRoot != 0 );
//
//		texture2D	= rcRoot->getRoot()->getChild< Texture2D >(0);
//		quad		= rcRoot->getRoot()->getChild< Quad >(1);
//	}
//	else
//	{
//		vgAssert( rcRoot == 0 );
//
//		// No resource (this is the first evaluation), create it.
//		rcRoot = new vgeGLBase::rc::Root;
//		rcManager->add( layerPlan, rcRoot );
//
//		texture2D = Texture2D::create("rootRC.LayerPlan.texture2D");
//		quad = Quad::create("rootRC.LayerPlan.quad");
//
//		rcRoot->getRoot()->addChild( texture2D );
//		rcRoot->getRoot()->addChild( quad );
//
//		// setup rc
//		texture2D->setWrapS( Texture2D::CLAMP_TO_EDGE );
//		texture2D->setWrapT( Texture2D::CLAMP_TO_EDGE );
//
//		texture2D->setMinFilter( Texture2D::LINEAR );
//		texture2D->setMagFilter( Texture2D::LINEAR );
//
//		quad->initializeTexUnits( 1, vgd::basic::TOP_LEFT, false /* cw */ );
//		const vgm::Vec3f translateToOrigin( 0.5f, 0.5f, 0.f );
//		quad->transform( translateToOrigin );
//	}
//
//	// Dirty flags
//	vgd::field::DirtyFlag	*pDF		= layerPlan->getDirtyFlag( layerPlan->getDFNode() );
//	vgd::field::DirtyFlag	*pDFImage	= layerPlan->getDirtyFlag( layerPlan->getDFImage() );
//
//	// @todo OPTME always computed
//	const vgm::Vec2f	layerPlanPosition	= layerPlan->getPosition();
//	const vgm::Vec2f	layerPlanSize		= layerPlan->getSize();
//
//	vgAssertN( vgm::greaterThanEqual(layerPlanSize[0], 0.f), "%s node with size[0] < 0 : %f", layerPlan->getName().c_str(), layerPlanSize[0] );
//	vgAssertN( vgm::greaterThanEqual(layerPlanSize[1], 0.f), "%s node with size[1] < 0 : %f", layerPlan->getName().c_str(), layerPlanSize[1] );
//
//	vgm::MatrixR current;
//	current.setTranslate( vgm::Vec3f(layerPlanPosition) );
//	current.scale( vgm::Vec3f(layerPlanSize[0], layerPlanSize[1], 1.f) );
//
//	// render overlay
//
//	// Makes a backup of GLSL activation state
//	using vgeGLBase::engine::Engine;
//	vgd::Shp< Engine::GLSLActivationState > glslActivationState = pGLEngine->getGLSLActivationState();
//	pGLEngine->sethCurrentProgram();
//
//	const bool isTextureMappingEnabledBAK = pGLEngine->setTextureMappingEnabled(true);
//
//	pGLEngine->paint( rcRoot->getRoot(), true );
//
//	const vgm::Vec2i drawingSurfaceSize = pGLEngine->getDrawingSurfaceSize();
//	const vgm::Rectangle2i viewport( 0, 0, drawingSurfaceSize[0], drawingSurfaceSize[1] );
//	pGLEngine->begin2DRendering( &viewport, false );
//
//	glMatrixMode( GL_MODELVIEW );
//	glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );
//
//	if ( pDFImage->isDirty() )
//	{
//		const float alphaScale = layerPlan->getAlphaScale();
//
//		if ( alphaScale != 1.f )
//		{
//			glPixelTransferf( GL_ALPHA_SCALE, alphaScale );
//		}
//
//		texture2D->setImage( layerPlan->getImage() );
//	}
//
//	pGLEngine->paint( texture2D, true );
//
//	// Gets the resource manager
//	vgeGLBase::rc::Texture2D * gloTex2D = rcManager->get< vgeGLBase::rc::Texture2D >( texture2D.get() );
//	gloTex2D->env( GL_TEXTURE_ENV_MODE, GL_REPLACE );
//
//	// draw proxy geometry
//	glEnable( GL_ALPHA_TEST );
//	glAlphaFunc( GL_GREATER, 0.f );
//
//	glEnable( GL_BLEND );
//	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
//
//	// alpha/blend
//	pGLEngine->paint( quad, true );
//
//	pGLEngine->end2DRendering( false );
//
//	pGLEngine->paint( rcRoot->getRoot(), false );
//
//	pGLEngine->setTextureMappingEnabled(isTextureMappingEnabledBAK);
//
//	// Restores GLSL activation state
//	pGLEngine->setGLSLActivationState( glslActivationState );
//
//	// Validates node
//	pDF->validate();
//	pDFImage->validate();
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