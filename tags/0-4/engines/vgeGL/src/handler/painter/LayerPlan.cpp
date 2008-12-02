// VGSDK - Copyright (C) 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/LayerPlan.hpp"

#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/Quad.hpp>
#include <vgd/node/LayerPlan.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vge/rc/Manager.hpp>
#include <vge/rc/Root.hpp>
#include <vge/service/Painter.hpp>

#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( LayerPlan );



const vge::handler::Handler::TargetVector LayerPlan::getTargets() const
{
	TargetVector targets;

	targets.reserve( 1 );
	targets.push_back( vgd::node::LayerPlan::getClassIndexStatic() );

	return targets;
}



void LayerPlan::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	assert( dynamic_cast< vgd::node::LayerPlan* >(pNode) != 0 );
	vgd::node::LayerPlan *pCastedNode = static_cast< vgd::node::LayerPlan* >(pNode);

	paint( pGLEngine, pCastedNode );
	//vgeGL::rc::applyUsingDisplayList< vgd::node::LayerPlan, LayerPlan >( pEngine, pNode, this );
}



void LayerPlan::unapply ( vge::engine::Engine* engine, vgd::node::Node* pNode )
{}



void LayerPlan::setToDefaults()
{}



void LayerPlan::paint( vgeGL::engine::Engine *pGLEngine, vgd::node::LayerPlan *layerPlan )
{
	if (	(layerPlan->getIImage() == 0) ||													// no image
			(	(layerPlan->getIImage() != 0) && layerPlan->getIImage()->isEmpty()	)			// empty image
			)
	{
		// Nothing to do
		return;
	}

	// Searchs resource
	vge::rc::Manager&		rcManager	= pGLEngine->getGLManager();

	vge::rc::IResource 		*resource	= rcManager.getAbstract( layerPlan );
	vge::rc::Root			*rcRoot		= dynamic_cast< vge::rc::Root* >(resource);

	using vgd::node::Quad;
	using vgd::node::Texture2D;

	vgd::Shp< Quad >		quad;
	vgd::Shp< Texture2D >	texture2D;

	if ( resource == 0 )
	{
		assert( rcRoot == 0 );

		// No resource (this is the first evaluation), create it.
		rcRoot = new vge::rc::Root;
		rcManager.add( layerPlan, rcRoot );

		quad = Quad::create("rootRC.LayerPlan.quad");
		texture2D = Texture2D::create("rootRC.LayerPlan.texture2D");

		rcRoot->getRoot()->addChild( texture2D );
		rcRoot->getRoot()->addChild( quad );

		// setup rc
		quad->initializeTexUnits( 1, vgd::basic::TOP_LEFT, false /* cw */ );
		const vgm::Vec3f translateToOrigin( 0.5f, 0.5f, 0.f );
		quad->transform( translateToOrigin );

		texture2D->setWrap( Texture2D::WRAP_S, Texture2D::CLAMP_TO_EDGE );
		texture2D->setWrap( Texture2D::WRAP_T, Texture2D::CLAMP_TO_EDGE );

		texture2D->setFilter( Texture2D::MIN_FILTER, Texture2D::LINEAR );
		texture2D->setFilter( Texture2D::MAG_FILTER, Texture2D::LINEAR );

		texture2D->setFunction( Texture2D::FUN_REPLACE );
	}
	else
	{
		assert( rcRoot != 0 );

		texture2D	= rcRoot->getRoot()->getChild< Texture2D >(0);
		quad		= rcRoot->getRoot()->getChild< Quad >(1);
	}

	// Dirty flags
	vgd::field::DirtyFlag	*pDF		= layerPlan->getDirtyFlag( layerPlan->getDFNode() );
	vgd::field::DirtyFlag	*pDFIImage	= layerPlan->getDirtyFlag( layerPlan->getDFIImage() );

//	if ( pDF->isDirty() )
//	{
//		// At least one field has been modified
//		// @todo OPTME
//	}

	// @todo OPTME always computed
	const vgm::Vec2f	layerPlanPosition	= layerPlan->getPosition();
	const vgm::Vec2f	layerPlanSize		= layerPlan->getSize();

//	assert( layerPlanSize[0] > 0.f ); // @todo FIXME floating point error (vgm::opearator equals( float, float );
//	assert( layerPlanSize[0] <= 1.f );

	vgm::MatrixR current;

	const vgm::Vec3f translation( layerPlanPosition );
	current.setTranslate( translation );

	const vgm::Vec3f scaleFactors( layerPlanSize[0], layerPlanSize[1], 1.f );
	current.scale( scaleFactors );

	// render overlay
	vgd::Shp< vge::service::Service > paintService = vge::service::Painter::create();

	pGLEngine->evaluate( paintService, rcRoot->getRoot().get(), true );

	pGLEngine->begin2DRendering();

	glMatrixMode( GL_MODELVIEW );
	glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );

	const vgm::Vec2i drawingSurfaceSize = pGLEngine->getDrawingSurfaceSize();
	glViewport( 0, 0, drawingSurfaceSize[0], drawingSurfaceSize[1] );

	// Makes a backup of GLSL activation state
	using vgeGL::engine::Engine;
	vgd::Shp< Engine::GLSLActivationState > glslActivationState = pGLEngine->getGLSLActivationState();

	//
	pGLEngine->sethCurrentProgram();

	if ( pDFIImage->isDirty() )
	{
		const float alphaScale = layerPlan->getAlphaScale();

		if ( alphaScale != 1.f )
		{
			glPixelTransferf( GL_ALPHA_SCALE, alphaScale );
		}

		texture2D->setIImage( layerPlan->getIImage() );
	}

	pGLEngine->evaluate( paintService, texture2D.get(), true );

	// draw proxy geometry
	glEnable( GL_ALPHA_TEST );
	glAlphaFunc( GL_GREATER, 0.f );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// alpha/blend
	pGLEngine->evaluate( paintService, quad.get(), true );

	pGLEngine->end2DRendering();

	pGLEngine->evaluate( paintService, rcRoot->getRoot().get(), false );

	// Restores GLSL activation state
	pGLEngine->setGLSLActivationState( glslActivationState );

	// Validates node
	pDF->validate();
	pDFIImage->validate();
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
