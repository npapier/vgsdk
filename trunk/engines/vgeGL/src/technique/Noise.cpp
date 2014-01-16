// VGSDK - Copyright (C) 2011, 2012, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/Noise.hpp"

#include <boost/algorithm/string/replace.hpp>
#include <vgd/basic/Image.hpp>
#include <vgd/basic/TimeDuration.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/Noise.hpp>
#include <vgd/node/OutputBufferProperty.hpp>
#include <vgd/node/PostProcessing.hpp>
#include <vgd/node/Texture2D.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/ShaderGenerator.hpp"
#include "vgeGL/handler/painter/OutputBuffers.hpp"
#include "vgeGL/rc/Noise.hpp"
#include "vgeGL/technique/ForwardRendering.hpp"



namespace vgeGL
{

namespace technique
{



void Noise::stageCollectInformationsBegin( vgeGL::engine::Engine * engine )
{
	engine->regardIfIsA< vgd::node::Noise >();
}


const bool Noise::collectInformationsCallback( vge::visitor::TraverseElementVector::const_iterator iterator )
{
	if ( iterator->first->isA< vgd::node::Noise >() && iterator->second )
	{
		setNode( iterator->first );
		if ( getNoiseNode()->getNoiseModel() == vgd::node::Noise::PHOTON )
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


void Noise::stageInitializeOutputBuffersNodes( vgd::Shp< vgeGL::rc::Noise > rc )
{
	// OutputBufferProperty : COLOR RGBA
	using vgd::node::OutputBufferProperty;
	vgd::Shp< OutputBufferProperty > obufProperty;

	obufProperty = OutputBufferProperty::create("vgsdk:colorRGBA", 0);
	obufProperty->setFormat( OutputBufferProperty::RGBA );
	obufProperty->setType( OutputBufferProperty::INTEGER );
	obufProperty->setCommand( OutputBufferProperty::COLOR );
	rc->colorBuffer = obufProperty;
}


void Noise::stageInitializeRandomTexture( vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::Noise > rc, vgd::node::Noise * noise )
{
	// noise image
	const vgm::Vec2f randomTextureScaleFactors	( noise->getRandomTextureScaleFactors() );
	const vgm::Vec2f drawingSurfaceSize			( engine->getDrawingSurfaceSize() );
	const vgm::Vec2i size(	static_cast< int >(drawingSurfaceSize[0] * randomTextureScaleFactors[0]),
							static_cast< int >(drawingSurfaceSize[1] * randomTextureScaleFactors[1]) );

	const float randomPow = noise->getFactors()[3];

	using vgd::basic::Image;
	vgd::Shp< Image > image( new Image(size[0], size[1], 1, Image::LUMINANCE, Image::UINT8) );

	uint8 * iPixel = static_cast< uint8 * >( image->editPixels() );
	const uint endCount = size[0]*size[1];
	for(uint count=0; count< endCount; ++count)
	{
		// random is in [-1, 1]
		const float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.f - 1.f;
		const float randomSign = (random >= 0.f) ? 1.f : -1.f;
		const float powRandom = randomSign * pow( abs(random), randomPow );
		*iPixel = static_cast<uint8>( powRandom * 256.f / 2.f + 128.f );
		++iPixel;
	}
	image->editPixelsDone();

	// 2D texture containing noise image
	if ( !rc->randomTexture )
	{
		using vgd::node::Texture2D;
		vgd::Shp< Texture2D > texture2D = Texture2D::create("vgsdk:noise:randomTexture");

		texture2D->setMinFilter( Texture2D::NEAREST );
		texture2D->setMagFilter( Texture2D::NEAREST );

		texture2D->setWrapS( Texture2D::REPEAT );
		texture2D->setWrapT( Texture2D::REPEAT );

		rc->randomTexture = texture2D;
	}

	rc->randomTexture->setImage( image );
}


void Noise::stageInitializePostProcessing( vgd::node::Noise * node, vgd::Shp< vgeGL::rc::Noise > rc )
{
	// POST-PROCESSING
	using vgd::node::Group;
	using vgd::node::PostProcessing;
	using vgeGL::engine::GLSLState;

	// Creates post processing nodes and pipeline
	if ( !rc->rootPostProcessing )
	{
		vgd::Shp< Group > ppGroup = Group::create( "vgsdk:noise:postProcessing" );

		vgd::Shp< PostProcessing > p = PostProcessing::create("vgsdk:noise:apply");
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		p->setInput1( PostProcessing::INPUT1_TEXTURE0 );
		p->setTexture0( rc->randomTexture );
		p->setFilter( PostProcessing::CUSTOM_FILTER );

		ppGroup->addChild( p );

		rc->postProcessing.setState( 0, vgd::makeShp( new GLSLState::PostProcessingState(p.get()) ) );
		rc->rootPostProcessing = ppGroup;
	}

	// Retrieves noise post-processing
	vgd::Shp< PostProcessing > noisePP = rc->rootPostProcessing->getChild< PostProcessing >( 0 );

	// Sets the custom filter
	const std::string sharedCode = 
		"{\n"
		"	float constantFactor	= params.x;\n"
		"	float modulateFactor	= params.y;\n"
		"	float powFactor			= params.z;\n"
		"	float noisePowFactor	= params.w;\n"
		"\n"
		"	vec4 color = texture( texMap0, texCoord );\n"
		"	NOISE0\n"
		//"	NOISEPOW\n"
		"	noise0 = noise0 * 2 - 1;\n"
		"	NOISE1\n"
		"	COLOR\n"
		"	return color;\n"
		"}\n"
		"\n\n\n";

	const std::string customFilterDefinitionWithNoiseFromTexture =
		"vec4 apply( sampler2D texMap0, sampler2D texMap1, vec2 texCoord, vec4 params )\n" +
		sharedCode;

	const std::string customFilterDefinitionWithTextureLessNoise =
		"vec4 apply( sampler2D texMap0, vec2 texCoord, vec4 params )\n"
		+ sharedCode;

	std::string customFilterDefinition;
	std::string customFilterApply;
	if ( getNoiseNode()->getUseTextureLessRandom() )
	{
		customFilterDefinition	= vgeGL::engine::GLSLHelpers::get_pnoise_cnoise() + customFilterDefinitionWithTextureLessNoise;
		customFilterApply		= "	color = apply( texMap2D[0], mgl_TexCoord[0].xy, param4f0 );\n";
	}
	else
	{
		customFilterDefinition	= customFilterDefinitionWithNoiseFromTexture;
		customFilterApply		= "	color = apply( texMap2D[0], texMap2D[1], mgl_TexCoord[0].xy, param4f0 );\n";
	}

	if ( getNoiseNode()->getChannelsSeparated() )
	{
		if ( getNoiseNode()->getUseTextureLessRandom() )
		{
			boost::algorithm::replace_all( customFilterDefinition, "NOISE0",
				"	vec4 noise0 = vec4(	\n"
				"			cnoise( 512 * texCoord + vec2(0, time) ),\n"
				"			cnoise( 512 * texCoord + vec2(time, 143) ),\n"
				"			cnoise( 512 * texCoord + vec2(-170, time) ),\n"
				"			0.f );\n"
				"	noise0 = 0.5 * noise0 + vec4(0.5);\n"
				);
		}
		else
		{
			boost::algorithm::replace_all( customFilterDefinition, "NOISE0",
				"	vec4 noise0 = vec4(	texture( texMap1, texCoord + vec2(random) ).x,\n"
				"						texture( texMap1, texCoord + vec2(1.0 - random) ).x,\n"
				"						texture( texMap1, texCoord + vec2(random + 0.5) ).x,\n"
				"						0.f );\n" );
		}

		// NOISE0POW
		//boost::algorithm::replace_all( customFilterDefinition, "NOISEPOW",
		//	"	noise0 = pow( noise0, vec4(noisePowFactor, noisePowFactor, noisePowFactor, noisePowFactor) );\n" );

		// NOISE1
		boost::algorithm::replace_all( customFilterDefinition, "NOISE1",
			"	vec4 noise1 = noise0;\n" );
	}
	else
	{
		if ( getNoiseNode()->getUseTextureLessRandom() )
		{
			boost::algorithm::replace_all( customFilterDefinition, "NOISE0",
				"	float noise0 = cnoise( 512 * texCoord + vec2(0, time) );\n"
				"	noise0 = 0.5 * noise0 + 0.5;\n"
				);
		}
		else
		{
			boost::algorithm::replace_all( customFilterDefinition, "NOISE0",
				"	float noise0 = texture( texMap1, texCoord + random.xy ).x;\n" );
		}

		// NOISE0POW
		//boost::algorithm::replace_all( customFilterDefinition, "NOISEPOW",
		//	"	noise0 = pow( noise0, noisePowFactor );\n" );

		// NOISE1
		boost::algorithm::replace_all( customFilterDefinition, "NOISE1",
			"	float noise1 = noise0;\n" );
	}

	boost::algorithm::replace_all( customFilterDefinition, "COLOR",
		"	float luminance = colorToMonochrome(color);\n"
		"	float rluminance = 1-luminance;\n"
		"	//	color = color * ( vec4(1) + linearFactor * noise0 ) + (constantFactor * noise1);\n"
		"	color = (noise0 * constantFactor) + color + (noise1* modulateFactor * pow(rluminance, powFactor));\n" );

	if ( noisePP->getCustomFilterDefinition() != customFilterDefinition )
	{
		noisePP->setCustomFilterDefinition( customFilterDefinition );
	}

	if ( noisePP->getCustomFilterApply() != customFilterApply )
	{
		noisePP->setCustomFilterApply( customFilterApply );
	}
}


void Noise::stageUpdatePostProcessingParameters( vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::Noise > rc )
{
	if ( !isEnabled() )	return;

	//
	using vgd::node::PostProcessing;
	vgd::Shp< PostProcessing > noisePP = rc->rootPostProcessing->getChild< PostProcessing >( 0 );
	const vgm::Vec4f factors( getNoiseNode()->getFactors() );
	noisePP->setParam4f0( factors );
}

void Noise::stageInitializeRC( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine )
{
	templateStageInitializeRC<vgeGL::rc::Noise>( technique, engine );
}


const bool Noise::isRCUpdated( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine, vgd::Shp< glo::IResource > genericRC )
{
	if ( !isEnabled() )
	{
		return true;
	}
	else
	{
		// Gets node dirty flag
		vgd::field::DirtyFlag * nodeDF = getNode()->getDirtyFlag( getNode()->getDFNode() );

		bool isRCUpdated =	nodeDF->isValid() &&
							!technique->hasDrawingSurfaceSizeChanged();
		return isRCUpdated;
	}
}


void Noise::updateRC( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine, vgd::Shp< glo::IResource > genericRC )
{
	if ( !isEnabled() ) return;

	vgd::Shp< vgeGL::rc::Noise > rc = vgd::dynamic_pointer_cast< vgeGL::rc::Noise >( genericRC );
	vgAssert( rc );

	// color buffer
	if ( !rc->colorBuffer )
	{
		stageInitializeOutputBuffersNodes( rc );
	}

	vgd::field::DirtyFlag * dfNode = getNoiseNode()->getDirtyFlag(getNoiseNode()->getDFNode());
	// random texture
	if (	!rc->randomTexture ||
			technique->hasDrawingSurfaceSizeChanged() ||
			dfNode->isDirty() )
	{
		stageInitializeRandomTexture( engine, rc, getNoiseNode() );
	}

	// post processing nodes
	if (	!rc->rootPostProcessing ||
			dfNode->isDirty() )
	{
		stageInitializePostProcessing( getNoiseNode(), rc );
	}

	// post processing parameters
	if ( dfNode->isDirty() )
	{
		stageUpdatePostProcessingParameters( engine, rc );
	}

	dfNode->validate();
}


void Noise::stagePrePaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine )
{
	if ( !isEnabled() ) return;

	vgd::Shp< vgeGL::rc::Noise > rc = getRC< vgeGL::rc::Noise >(engine);
	vgAssert( rc );

	stageInitializeOutputBuffers( technique, engine, rc );
}


void Noise::stageInitializeOutputBuffers( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::Noise > rc )
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

		engine->setCurrentPrivateOutputBuffers( 0 );
	}

	if ( !technique->isPostProcessingEnabled )
	{
		technique->isPostProcessingEnabled = true;
	}
}


void Noise::stagePostPaint( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine )
{
	if ( !isEnabled() ) return;

	vgd::Shp< vgeGL::rc::Noise > rc = getRC< vgeGL::rc::Noise >(engine);
	vgAssert( rc );

	// Sets uniforms
	//	Test if random values have to be updated
	float noiseFrequency;
	const bool hasFrequency = getNoiseNode()->getFrequency( noiseFrequency );

	if (	!hasFrequency ||
			rc->lastRandomUniformUpdate.isInvalid() ||
			rc->lastRandomUniformUpdate.getElapsedTime().ms() >= static_cast<uint64>(1000.f / noiseFrequency)	)
	{
		rc->lastUsedRandomValue = vgm::Vec4f(
			static_cast<float>(rand()) / 32767.f,
			static_cast<float>(rand()) / 32767.f,
			static_cast<float>(rand()) / 32767.f,
			static_cast<float>(rand()) / 32767.f );

		rc->lastUsedTimeValue = engine->getElapsedTime().ms();

		rc->lastRandomUniformUpdate.restart();
	}

	engine->getBuiltinUniformState().sethUniform( "random", rc->lastUsedRandomValue );
	engine->getBuiltinUniformState().sethUniform( "time", static_cast<int>(rc->lastUsedTimeValue) );

	// Apply post-processing
	const vgd::Shp< vgeGL::rc::FrameBufferObject > finalBuffers = technique->applyPostProcessing( engine, technique->m_textures, &(rc->postProcessing) );

	// Blit
	technique->blit( engine, finalBuffers, technique->m_fbo );
}


vgd::node::Noise * Noise::getNoiseNode() const
{
	return static_cast< vgd::node::Noise * >( getNode() );
}


} // namespace technique

} // namespace vgeGL
