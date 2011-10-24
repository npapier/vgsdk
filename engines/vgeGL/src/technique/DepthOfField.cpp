// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/DepthOfField.hpp"

#include <vgd/node/DepthOfField.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/OutputBufferProperty.hpp>
#include <vgd/node/PostProcessing.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/handler/painter/OutputBuffers.hpp"
#include "vgeGL/rc/DepthOfField.hpp"
#include "vgeGL/technique/ForwardRendering.hpp"


namespace vgeGL
{

namespace technique
{



// SUBTECHNIQUE
SubTechnique::SubTechnique()
: m_isEnabled( false )
{}

void SubTechnique::reset()
{
	m_isEnabled = false;
}


const bool SubTechnique::isEnabled() const
{
	return m_isEnabled;
}

const bool SubTechnique::setEnabled( const bool enabled )
{
	const bool oldState = isEnabled();
	m_isEnabled = enabled;
	return oldState;
}



// DEPTHOFFIELD
namespace
{
	const int blurFactorBufferIndex = 7;
}



DepthOfField::DepthOfField()
: m_dof(0)
{}


void DepthOfField::reset()
{
	SubTechnique::reset();

	m_dof = 0;
}


void DepthOfField::stageCollectInformationsBegin( vgeGL::engine::Engine * engine )
{
	engine->regardIfIsA< vgd::node::DepthOfField >();
}


const bool DepthOfField::collectInformationsCallback( vge::visitor::TraverseElementVector::const_iterator iterator )
{
	if ( iterator->first->isA< vgd::node::DepthOfField >() && iterator->second )
	{
		m_dof = dynamic_cast< vgd::node::DepthOfField * >( iterator->first );
		if ( m_dof->getCameraModel() == vgd::node::DepthOfField::THIN_LENS )
		{
			setEnabled();
		}
		return true;
	}
	else
	{
		return false;
	}
}


vgd::Shp< vgeGL::rc::DepthOfField > DepthOfField::getRC( vgeGL::engine::Engine * engine )
{
	vgeGL::engine::Engine::GLManagerType& rcManager = engine->getGLManager();

	vgd::Shp< vgeGL::rc::DepthOfField > rc = rcManager.getShp< vgeGL::rc::DepthOfField >( m_dof );

	return rc;
}


void DepthOfField::stageInitializeOutputBuffersNodes( vgd::Shp< vgeGL::rc::DepthOfField > rc )
{
	// OutputBufferProperty : COLOR RGBA
	using vgd::node::OutputBufferProperty;
	vgd::Shp< OutputBufferProperty > obufProperty;

	obufProperty = OutputBufferProperty::create("vgsdk:colorRGBA", 0);
	obufProperty->setFormat( OutputBufferProperty::RGBA );
	obufProperty->setType( OutputBufferProperty::INTEGER );
	obufProperty->setCommand( OutputBufferProperty::COLOR );
	rc->colorBuffer = obufProperty;

	// OUTPUT BUFFER PROPERTY : BLUR FACTOR
	//obufProperty = OutputBufferProperty::create("vgsdk:DOF:blurFactor", 1);
	obufProperty = OutputBufferProperty::create("vgsdk:DOF:blurFactor", blurFactorBufferIndex );
	obufProperty->setFormat( OutputBufferProperty::LUMINANCE );
	obufProperty->setType( OutputBufferProperty::FLOAT16 );
	obufProperty->setCommand( OutputBufferProperty::CUSTOM );
	obufProperty->setCustomDeclaration(
	"uniform float d_focus;\n"
	"uniform float d_focusToFar;\n"
	"uniform float d_focusToNear;\n"
	"uniform float far_clamp;\n"
	"uniform float near_clamp;\n"
	"\n"
	"float d_far = d_focus + d_focusToFar;\n"
	"float d_near = d_focus - d_focusToNear;\n"
	"\n"
	"float dof_computeBlurFactor( float distCam )\n"
	"{\n"
	"	float f;\n"
	"\n"
	"	if (distCam < d_focus)\n"
	"	{\n"
	"		// scale distCam value between near blur distance and focal distance to [-1, 0] range\n"
	"		f = (distCam - d_focus)/(d_focus - d_near);\n"
	"\n"
	"		// clamp the near blur to a maximum blurriness\n"
	"		f = clamp( f, near_clamp, 0 );\n"
	"	}\n"
	"	else\n"
	"	{\n"
	"		// scale distCam value between focal distance and far blur distance to [0, 1] range\n"
	"		f = (distCam - d_focus)/(d_far - d_focus);\n"
	"\n"
	"		// clamp the far blur to a maximum blurriness\n"
	"		f = clamp( f, 0, far_clamp );\n"
	"	}\n"
	"\n"
	"	// scale and bias into [0, 1] range\n"
	"	return f;\n"
	"}\n" 
	);

	obufProperty->setCustomCommand(
		"dof_computeBlurFactor( -ecPosition.z )"
	);
	rc->blurFactorBuffer = obufProperty;
}



void DepthOfField::stageInitializePostProcessing( vgd::node::DepthOfField * node, vgd::Shp< vgeGL::rc::DepthOfField > rc )
{
	// POST-PROCESSING
	using vgd::node::Group;
	using vgd::node::PostProcessing;
	using vgeGL::engine::GLSLState;

	vgd::Shp< Group > ppGroup = Group::create( "vgsdk:dof:postProcessing" );

	vgd::Shp< PostProcessing > p;

	p = PostProcessing::create("vgsdk:dof:down");
	p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
	//p->setFilter( PostProcessing::IDENTITY );
	p->setFilter( PostProcessing::DOWN_FILTER4 );
	//p->setOutput( PostProcessing::OUTPUT_TMP0 );
	ppGroup->addChild( p );
//	rc->postProcessing.setState( 0, vgd::makeShp( new GLSLState::PostProcessingState(p.get()) ) );

	p = PostProcessing::create("vgsdk:dof:blurH", 1);
p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
//	p->setInput0( PostProcessing::PREVIOUS0 );
	p->setFilter( PostProcessing::BLUR_HORIZ  );
	ppGroup->addChild( p );
	rc->postProcessing.setState( 1, vgd::makeShp( new GLSLState::PostProcessingState(p.get()) ) );

	p = PostProcessing::create("vgsdk:dof:blurV", 2);
	p->setFilter( PostProcessing::BLUR_VERT );
	ppGroup->addChild( p );
	rc->postProcessing.setState( 2, vgd::makeShp( new GLSLState::PostProcessingState(p.get()) ) );

	p = PostProcessing::create("vgsdk:dof:up", 3);
	p->setFilter( PostProcessing::UP_FILTER4 );
	ppGroup->addChild( p );
//	rc->postProcessing.setState( 3, vgd::makeShp( new GLSLState::PostProcessingState(p.get()) ) );

	p = PostProcessing::create("vgsdk:dof:final", 4);
	p->setInput0( PostProcessing::OUTPUT_BUFFER0 );										// color
	p->setInput1( PostProcessing::INPUT1_OUTPUT_BUFFER0 + blurFactorBufferIndex );		// blurFactor
	p->setInput2( PostProcessing::INPUT2_PREVIOUS0 );									// up4( blurVH( down4(color) ) )
	p->setFilter( PostProcessing::CUSTOM_FILTER );
	p->setCustomFilterDefinition(
	"// contains poisson-distributed positions on the unit circle\n"
	"vec2 poisson[8] = vec2[8](\n"
	"	vec2( 0.0,			0.0),\n"
	"	vec2( 0.527837,		-0.085868),\n"
	"	vec2( -0.040088,	0.536087),\n"
	"	vec2(-0.670445,		-0.179949),\n"
	"	vec2(-0.419418,		-0.616039),\n"
	"	vec2( 0.440453,		-0.639399),\n"
	"	vec2(-0.757088,		0.349334),\n"
	"	vec2( 0.574619,		0.685879)\n"
	");\n"
	"\n"
	"vec4 apply( sampler2D tColor, sampler2D tBlurFactor, sampler2D tBlurredColor, vec2 texCoord, int numberOfTaps )\n"
	"{\n"
	"\n"
	"	vec2 screenRes = textureSize( tColor, 0 );\n"
	"\n"
	"	// pixel size (1/image resolution) of full resolution image\n"
	"	vec2 pixelSizeHigh = 1.0/screenRes;\n"
	"\n"
	"	// pixel size of low resolution image\n"
	"	vec2 pixelSizeLow = pixelSizeHigh;\n"
	"\n"
	"	// maximum CoC radius and diameter in pixels\n"
	"	vec2 vMaxCoC = vec2(5.0, 10.0);\n"							// @todo param
	"\n"
	"	// scale factor for maximum CoC size on low res. image\n"
	"	float radiusScale = 0.4;\n"									// @todo param
	"\n"
	"	float centerDepth		= texture( tBlurFactor, texCoord ).r;	// save its depth\n"
	"\n"
	"	float discRadius		= abs( (centerDepth*0.5+0.5) * vMaxCoC.y - vMaxCoC.x);	// convert depth into blur radius in pixels\n"
	"	float discRadiusLow		= discRadius * radiusScale;						// compute disc radius on low-res image\n"
	"\n"
	"	// Accumulator\n"
	"	vec4 cOut = vec4(0);\n"
	"\n"
	"	for(int t = 0; t < numberOfTaps; t++)\n"
	"	{\n"
	"		// fetch high-res tap\n"
	"		vec2 coordHigh = texCoord + (pixelSizeHigh * poisson[t] * discRadius);\n"
	"		vec4 tapHigh = texture( tColor, coordHigh );\n"
	"\n"
	"		// fetch low-res tap\n"
	"		vec2 coordLow = texCoord + (pixelSizeLow * poisson[t] * discRadiusLow);\n"
	"		vec4 tapLow = texture( tBlurredColor, coordLow );\n"
	"\n"
	"		// fetch blur factor tap\n"
	"		float blurFactor = texture( tBlurFactor, coordHigh ).r;\n"
	"\n"
	"		// put tap blurriness into [0, 1] range\n"
	"		float tapBlur = abs(blurFactor /** 2.0 - 1.0*/);\n"
	"\n"
	"		// mix low- and hi-res taps based on tap blurriness\n"
	"		vec4 tap = mix(tapHigh, tapLow, tapBlur);\n"
	"\n"
	"		// apply leaking reduction: lower weight for taps that are\n"
	"		// closer than the center tap and in focus\n"
	"		tap.a = (blurFactor >= centerDepth) ? 1.0 : abs(blurFactor /** 2.0 - 1.0*/);\n"
	"\n"
	"		// accumulate\n"
	"		cOut.rgb += tap.rgb * tap.a;\n"
	"		cOut.a += tap.a;\n"
	"	}\n"
	"\n"
	"	// normalize and return result\n"
	"	return (cOut/cOut.a);\n"
	"}\n"
	);
	p->setCustomFilterApply(
	"	color = apply( texMap2D[0], texMap2D[1], texMap2D[2], mgl_TexCoord[0].xy, int(param1f0) );\n"
	);
	ppGroup->addChild( p );
	rc->postProcessing.setState( 4, vgd::makeShp( new GLSLState::PostProcessingState(p.get()) ) );

	rc->rootPostProcessing = ppGroup;
}


void DepthOfField::stageUpdatePostProcessingParameters( vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::DepthOfField > rc )
{
	if ( !isEnabled() )	return;

	// Retrieves final post-processing
	using vgd::node::PostProcessing;
	vgd::Shp< PostProcessing > final = rc->rootPostProcessing->getChild< PostProcessing >( 4 );

	const float sampling = static_cast<float>(m_dof->getSampling());
	final->setParam1f0( sampling );
}


void DepthOfField::stageInitializeRC( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine )
{
	if ( isEnabled() )
	{
		// Tests if rc must be created and/or updated ?
		bool callUpdateRC;

		vgd::Shp< glo::IResource > rc = getRC( engine );

		if ( !rc )
		{
			// Creates resource
			rc.reset( new vgeGL::rc::DepthOfField ); // @todo a template parameter of DepthOfField

			// Register node and its resource into manager
			vgeGL::engine::Engine::GLManagerType& rcManager = engine->getGLManager();
			rcManager.add( m_dof, rc );				// @todo getNode/setNode() in SubTechnique

			// RC must be initialized
			callUpdateRC = true;
		}
		else
		{
			// Tests if rc is up to date ?
			const bool isUpdated = isRCUpdated( rc );
			callUpdateRC = !isUpdated;
		}

		// Updates RC ?
		if ( callUpdateRC )
		{
			updateRC( technique, engine, rc );
		}
		// else nothing to do
	}
	// else nothing to do
}



const bool DepthOfField::isRCUpdated( vgd::Shp< glo::IResource > genericRC )
{
	if ( !isEnabled() ) return true;

	// Gets node dirty flag
	vgd::field::DirtyFlag * nodeDF = m_dof->getDirtyFlag( m_dof->getDFNode() );
	return nodeDF->isValid();
}



void DepthOfField::updateRC( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine, vgd::Shp< glo::IResource > genericRC )
{
	if ( !isEnabled() ) return;

	vgd::Shp< vgeGL::rc::DepthOfField > rc = vgd::dynamic_pointer_cast< vgeGL::rc::DepthOfField >( genericRC );
	vgAssert( rc );

	if ( !rc->colorBuffer )
	{
		stageInitializeOutputBuffersNodes( rc );
	}

	if ( !rc->rootPostProcessing )
	{
		stageInitializePostProcessing( m_dof, rc );
	}

	stageUpdatePostProcessingParameters( engine, rc );
}



void DepthOfField::stagePrePaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine )
{
	if ( !isEnabled() ) return;

	vgd::Shp< vgeGL::rc::DepthOfField > rc = vgd::dynamic_pointer_cast< vgeGL::rc::DepthOfField >( getRC(engine) );
	vgAssert( rc );

	stageInitializeOutputBuffers( technique, engine, rc );

	// Sets uniforms

	// focus
	vgAssertN( !engine->getUniformState().isUniform( "d_focus" ), "Uniform named d_focus not found" );
	engine->getUniformState().sethUniform( "d_focus", m_dof->getFocus() );

	// focusToFar
	vgAssertN( !engine->getUniformState().isUniform( "d_focusToFar" ), "Uniform named d_focusToFar not found" );
	engine->getUniformState().sethUniform( "d_focusToFar", m_dof->getFocusToFar() );

	// focusToNear
	vgAssertN( !engine->getUniformState().isUniform( "d_focusToNear" ), "Uniform named d_focusToNear not found" );
	engine->getUniformState().sethUniform( "d_focusToNear", m_dof->getFocusToNear() );

	// farMaximumBlurriness
	vgAssertN( !engine->getUniformState().isUniform( "far_clamp" ), "Uniform named far_clamp not found" );
	engine->getUniformState().sethUniform( "far_clamp", m_dof->getFarMaximumBlurriness() );

	// nearMaximumBlurriness
	vgAssertN( !engine->getUniformState().isUniform( "near_clamp" ), "Uniform named near_clamp not found" );
	engine->getUniformState().sethUniform( "near_clamp", -m_dof->getNearMaximumBlurriness() );
}



void DepthOfField::stageInitializeOutputBuffers( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::DepthOfField > rc )
{
	using vgd::node::OutputBufferProperty;
	using vgeGL::engine::GLSLState;

	if ( !isEnabled() ) return;

	// patches output buffers of engine
	if ( !technique->hasOutputBufferProperties )
	{
		// configures current output buffers of engine
		technique->hasOutputBufferProperties = true;
		technique->m_outputBufferProperties->setState( 0, vgd::makeShp( new GLSLState::OutputBufferPropertyState(rc->colorBuffer.get()) ) );
		technique->m_outputBufferProperties->setState( blurFactorBufferIndex, vgd::makeShp( new GLSLState::OutputBufferPropertyState(rc->blurFactorBuffer.get()) ) );

		engine->setCurrentPrivateOutputBuffers( 0, blurFactorBufferIndex );
	}
	else
	{
		// patches current output buffers of engine
		// i.e. adds blurFactorBuffer
		vgAssert(	technique->m_outputBufferProperties->getState(0) &&
					technique->m_outputBufferProperties->getState(0)->getNode()->getFormat() == OutputBufferProperty::RGBA );
		vgAssert( !technique->m_outputBufferProperties->getState(blurFactorBufferIndex) );
		technique->m_outputBufferProperties->setState( blurFactorBufferIndex, vgd::makeShp( new GLSLState::OutputBufferPropertyState(rc->blurFactorBuffer.get()) ) );

		engine->setCurrentPrivateOutputBuffers( blurFactorBufferIndex );
	}

	if ( !technique->isPostProcessingEnabled )
	{
		technique->isPostProcessingEnabled = true;
	}
}



void DepthOfField::stagePostPaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine )
{
	if ( !isEnabled() ) return;

	vgd::Shp< vgeGL::rc::DepthOfField > rc = vgd::dynamic_pointer_cast< vgeGL::rc::DepthOfField >( getRC(engine) );
	vgAssert( rc );

	const vgd::Shp< vgeGL::rc::FrameBufferObject > finalBuffers = technique->applyPostProcessing( engine, technique->m_textures, &(rc->postProcessing) );
	technique->blit( engine, finalBuffers );
}



} // namespace technique

} // namespace vgeGL
