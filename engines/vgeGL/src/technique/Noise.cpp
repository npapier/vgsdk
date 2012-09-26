// VGSDK - Copyright (C) 2011, 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/Noise.hpp"

#include <boost/algorithm/string/replace.hpp>
#include <vgd/basic/Image.hpp>
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
	const vgm::Vec2i size(	drawingSurfaceSize[0] * randomTextureScaleFactors[0],
							drawingSurfaceSize[1] * randomTextureScaleFactors[1] );

	using vgd::basic::Image;
	vgd::Shp< Image > image( new Image(size[0], size[1], 1, Image::LUMINANCE, Image::UINT8) );

	uint8 * iPixel = static_cast< uint8 * >( image->editPixels() );

	for(uint count=0; count< size[0]*size[1]; ++count)
	{
		*iPixel = rand() % 256;
		++iPixel;
	}
	image->editPixelsDone();
	// for debug: image->save("noise.png");

	// 2D texture containing noise image
	if ( !rc->randomTexture )
	{
		using vgd::node::Texture2D;
		vgd::Shp< Texture2D > texture2D = Texture2D::create("vgsdk:noise:randomTexture");

		texture2D->setFilter( Texture2D::MIN_FILTER, Texture2D::NEAREST );
		texture2D->setFilter( Texture2D::MAG_FILTER, Texture2D::NEAREST );

		texture2D->setWrap( Texture2D::WRAP_S, Texture2D::REPEAT );
		texture2D->setWrap( Texture2D::WRAP_T, Texture2D::REPEAT );

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

	vgd::Shp< Group > ppGroup = Group::create( "vgsdk:noise:postProcessing" );

	vgd::Shp< PostProcessing > p;

	p = PostProcessing::create("vgsdk:noise:apply");
	p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
	p->setInput1( PostProcessing::INPUT1_TEXTURE0 );
	p->setTexture0( rc->randomTexture );
	p->setFilter( PostProcessing::CUSTOM_FILTER );

	ppGroup->addChild( p );
	rc->postProcessing.setState( 0, vgd::makeShp( new GLSLState::PostProcessingState(p.get()) ) );

	rc->rootPostProcessing = ppGroup;
}


void Noise::stageUpdatePostProcessingParameters( vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::Noise > rc )
{
	if ( !isEnabled() )	return;

	// Retrieves noise post-processing
	using vgd::node::PostProcessing;
	vgd::Shp< PostProcessing > noisePP = rc->rootPostProcessing->getChild< PostProcessing >( 0 );

	// Sets the custom filter
	const std::string customFilterDefinitionWithNoiseFromTexture =
		"vec4 apply( sampler2D texMap0, sampler2D texMap1, vec2 texCoord, vec2 params )\n"
		"{\n"
		"	float linearFactor		= params.x;\n"
		"	float constantFactor	= params.y;\n"
		"\n"
		"	vec4 color = texture( texMap0, texCoord );\n"
		"	NOISE0\n"
		"	NOISE1\n"
		"	COLOR\n"
		"	return color;\n"
		"}\n"
		"\n\n\n";

	const std::string customFilterDefinitionWithTextureLessNoise =
		"vec4 apply( sampler2D texMap0, vec2 texCoord, vec2 params )\n"
		"{\n"
		"	float linearFactor		= params.x;\n"
		"	float constantFactor	= params.y;\n"
		"\n"
		"	vec4 color = texture( texMap0, texCoord );\n"
		"	NOISE0\n"
		"	NOISE1\n"
		"	COLOR\n"
		"	return color;\n"
		"}\n"
		"\n\n\n";

	std::string customFilterDefinition;
	std::string customFilterApply;
	if ( getNoiseNode()->getUseTextureLessRandom() )
	{
		customFilterDefinition	= vgeGL::engine::GLSLHelpers::get_pnoise_cnoise() + customFilterDefinitionWithTextureLessNoise;
		customFilterApply		= "	color = apply( texMap2D[0], mgl_TexCoord[0].xy, param4f0.xy );\n";
	}
	else
	{
		customFilterDefinition	= customFilterDefinitionWithNoiseFromTexture;
		customFilterApply		= "	color = apply( texMap2D[0], texMap2D[1], mgl_TexCoord[0].xy, param4f0.xy );\n";
	}

	if ( getNoiseNode()->getChannelsSeparated() )
	{
		if ( getNoiseNode()->getUseTextureLessRandom() )
		{
			boost::algorithm::replace_all( customFilterDefinition, "NOISE0",
				"	vec4 noise0 = vec4(	\n"
				"			cnoise( 512 * texCoord + vec2(0,time) ),\n"
				"			cnoise( 512 * texCoord + vec2(time,143) ),\n"
				"			cnoise( 512 * texCoord + vec2(-170,time) ),\n"
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

		boost::algorithm::replace_all( customFilterDefinition, "NOISE1",
			"	vec4 noise1 = noise0;\n" );
	}
//texture( texMap1, texCoord - random.zw) ).x;\n" // @todo test != between 1 noise or 2 noise values
	else
	{
		if ( getNoiseNode()->getUseTextureLessRandom() )
		{
			boost::algorithm::replace_all( customFilterDefinition, "NOISE0",
				"	float noise0 = cnoise( 512 * texCoord + vec2(0,time) );\n"
				"	noise0 = 0.5 * noise0 + 0.5;\n"
				);
		}
		else
		{
			boost::algorithm::replace_all( customFilterDefinition, "NOISE0",
				"	float noise0 = texture( texMap1, texCoord + random.xy ).x;\n" );
		}

		boost::algorithm::replace_all( customFilterDefinition, "NOISE1",
			"	float noise1 = noise0;\n" );
	}

	boost::algorithm::replace_all( customFilterDefinition, "COLOR",
		"//	color = noise0;\n"
		"	color = color * ( vec4(1) + linearFactor * noise0 ) + (constantFactor * noise1);\n" );


	if ( noisePP->getCustomFilterDefinition() != customFilterDefinition )
	{
		noisePP->setCustomFilterDefinition( customFilterDefinition );
	}

	if ( noisePP->getCustomFilterApply() != customFilterApply )
	{
		noisePP->setCustomFilterApply( customFilterApply );
	}

	//
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

	// random texture
	vgd::field::DirtyFlag * dfNode = getNoiseNode()->getDirtyFlag(getNoiseNode()->getDFNode());
	if (	!rc->randomTexture ||
			technique->hasDrawingSurfaceSizeChanged() ||
			dfNode->isDirty() )
	{
		stageInitializeRandomTexture( engine, rc, getNoiseNode() );
		dfNode->validate();
	}

	// post processing nodes
	if ( !rc->rootPostProcessing )
	{
		stageInitializePostProcessing( getNoiseNode(), rc );
	}

	// post processing parameters
	stageUpdatePostProcessingParameters( engine, rc );
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

	const vgd::Shp< vgeGL::rc::FrameBufferObject > finalBuffers = technique->applyPostProcessing( engine, technique->m_textures, &(rc->postProcessing) );
	technique->blit( engine, finalBuffers, technique->m_fbo );
}


vgd::node::Noise * Noise::getNoiseNode() const
{
	return static_cast< vgd::node::Noise * >( getNode() );
}


} // namespace technique

} // namespace vgeGL
