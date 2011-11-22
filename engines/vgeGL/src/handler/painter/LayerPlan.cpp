// VGSDK - Copyright (C) 2007, 2008, 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/LayerPlan.hpp"


#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/Quad.hpp>
#include <vgd/node/LayerPlan.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vge/rc/Manager.hpp>
#include <vge/service/Painter.hpp>
#include "vgeGL/engine/Engine.hpp"
#include <vgeGL/rc/Root.hpp>
//#include "vgeGL/rc/TDisplayListHelper.hpp"
#include "vgeGL/rc/Texture2D.hpp"



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
	// @todo conflict in manager between display list and vge::rc::Root for the same node (the LayerPlan)
	// vgeGL::rc::applyUsingDisplayList< vgd::node::LayerPlan, LayerPlan >( pEngine, pNode, this );
}



void LayerPlan::unapply ( vge::engine::Engine* engine, vgd::node::Node* pNode )
{}



void LayerPlan::setToDefaults()
{}




// @todo Uses glsl for LayerPlan
void LayerPlan::paint( vgeGL::engine::Engine *pGLEngine, vgd::node::LayerPlan *layerPlan )
{
	if (	(layerPlan->getImage() == 0) ||													// no image
			(	(layerPlan->getImage() != 0) && layerPlan->getImage()->isEmpty()	)		// empty image
			)
	{
		// Nothing to do
		return;
	}

	// Searchs resource
	vgeGL::engine::Engine::GLManagerType&		rcManager	= pGLEngine->getGLManager();

	::glo::IResource 							*resource	= rcManager.getAbstract( layerPlan );
	vgeGL::rc::Root								*rcRoot		= dynamic_cast< vgeGL::rc::Root* >(resource);

	using vgd::node::Quad;
	using vgd::node::Texture2D;

	vgd::Shp< Quad >		quad;
	vgd::Shp< Texture2D >	texture2D;

	if ( resource )
	{
		assert( rcRoot != 0 );

		texture2D	= rcRoot->getRoot()->getChild< Texture2D >(0);
		quad		= rcRoot->getRoot()->getChild< Quad >(1);
	}
	else
	{
		assert( rcRoot == 0 );

		// No resource (this is the first evaluation), create it.
		rcRoot = new vgeGL::rc::Root;
		rcManager.add( layerPlan, rcRoot );

		texture2D = Texture2D::create("rootRC.LayerPlan.texture2D");
		quad = Quad::create("rootRC.LayerPlan.quad");

		rcRoot->getRoot()->addChild( texture2D );
		rcRoot->getRoot()->addChild( quad );

		// setup rc
		texture2D->setWrap( Texture2D::WRAP_S, Texture2D::CLAMP_TO_EDGE );
		texture2D->setWrap( Texture2D::WRAP_T, Texture2D::CLAMP_TO_EDGE );

		texture2D->setFilter( Texture2D::MIN_FILTER, Texture2D::LINEAR );
		texture2D->setFilter( Texture2D::MAG_FILTER, Texture2D::LINEAR );

		quad->initializeTexUnits( 1, vgd::basic::TOP_LEFT, false /* cw */ );
		const vgm::Vec3f translateToOrigin( 0.5f, 0.5f, 0.f );
		quad->transform( translateToOrigin );
	}

	// Dirty flags
	vgd::field::DirtyFlag	*pDF		= layerPlan->getDirtyFlag( layerPlan->getDFNode() );
	vgd::field::DirtyFlag	*pDFImage	= layerPlan->getDirtyFlag( layerPlan->getDFImage() );

	// @todo OPTME always computed
	const vgm::Vec2f	layerPlanPosition	= layerPlan->getPosition();
	const vgm::Vec2f	layerPlanSize		= layerPlan->getSize();

	assert( layerPlanSize[0] + vgm::Epsilon<float>().value() > 0.f );
	assert( layerPlanSize[0] - vgm::Epsilon<float>().value() <= 1.f );
	assert( layerPlanSize[1] + vgm::Epsilon<float>().value() > 0.f );
	assert( layerPlanSize[1] - vgm::Epsilon<float>().value() <= 1.f );

	vgm::MatrixR current;
	current.setTranslate( vgm::Vec3f(layerPlanPosition) );
	current.scale( vgm::Vec3f(layerPlanSize[0], layerPlanSize[1], 1.f) );

	// render overlay

	// Makes a backup of GLSL activation state
	using vgeGL::engine::Engine;
	vgd::Shp< Engine::GLSLActivationState > glslActivationState = pGLEngine->getGLSLActivationState();
	pGLEngine->sethCurrentProgram();

	const bool isTextureMappingEnabledBAK = pGLEngine->setTextureMappingEnabled(true);

	pGLEngine->paint( rcRoot->getRoot(), true );

	const vgm::Vec2i drawingSurfaceSize = pGLEngine->getDrawingSurfaceSize();
	const vgm::Rectangle2i viewport( 0, 0, drawingSurfaceSize[0], drawingSurfaceSize[1] );
	pGLEngine->begin2DRendering( &viewport, false );

	glMatrixMode( GL_MODELVIEW );
	glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );

	if ( pDFImage->isDirty() )
	{
		const float alphaScale = layerPlan->getAlphaScale();

		if ( alphaScale != 1.f )
		{
			glPixelTransferf( GL_ALPHA_SCALE, alphaScale );
		}

		texture2D->setImage( layerPlan->getImage() );
	}

	pGLEngine->paint( texture2D, true );

	// Gets the resource manager
	vgeGL::rc::Texture2D * gloTex2D = rcManager.get< vgeGL::rc::Texture2D >( texture2D.get() );
	gloTex2D->env( GL_TEXTURE_ENV_MODE, GL_REPLACE );

	// draw proxy geometry
	glEnable( GL_ALPHA_TEST );
	glAlphaFunc( GL_GREATER, 0.f );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// alpha/blend
	pGLEngine->paint( quad, true );

	pGLEngine->end2DRendering( false );

	pGLEngine->paint( rcRoot->getRoot(), false );

	pGLEngine->setTextureMappingEnabled(isTextureMappingEnabledBAK);

	// Restores GLSL activation state
	pGLEngine->setGLSLActivationState( glslActivationState );

	// Validates node
	pDF->validate();
	pDFImage->validate();
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
