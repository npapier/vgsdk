// VGSDK - Copyright (C) 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/OutputBufferProperty.hpp"

#include <glo/GLSLProgram.hpp>

#include <vgd/basic/toString.hpp>
#include <vgd/basic/IImage.hpp>
#include <vgd/basic/ImageInfo.hpp>
#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/FrameBuffer.hpp>
#include <vgd/node/OutputBufferProperty.hpp>
#include <vgd/node/Texture2D.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/rc/FrameBufferObject.hpp"
#include "vgeGL/rc/Texture2D.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



namespace
{

const vgd::basic::IImage::Format convertToIImageFormat( const vgd::node::OutputBufferProperty::FormatValueType format )
{
	using vgd::basic::IImage;
	using vgd::node::OutputBufferProperty;

	IImage::Format retVal;

	switch ( format.value() )
	{
		case OutputBufferProperty::RGB:
			retVal = IImage::RGB;
			break;

		case OutputBufferProperty::RGBA:
			retVal = IImage::RGBA;
			break;

		case OutputBufferProperty::LUMINANCE:
			retVal = IImage::LUMINANCE;
			break;

		case OutputBufferProperty::LUMINANCE_ALPHA:
			retVal = IImage::LUMINANCE_ALPHA;
			break;

		case OutputBufferProperty::LUMINANCE_FOR_DEPTH:
			retVal = IImage::LUMINANCE;
			break;

		default:
			vgAssertN( false, "Unexpected value" );
			retVal = IImage::RGBA;
	}
	return retVal;
}



const std::string convertToGLSLFormat( const vgd::node::OutputBufferProperty::FormatValueType format )
{
	using vgd::node::OutputBufferProperty;

	std::string retVal;

	switch ( format.value() )
	{
		case OutputBufferProperty::RGB:
			retVal = "vec3";
			break;

		case OutputBufferProperty::RGBA:
			retVal = "vec4";
			break;

		case OutputBufferProperty::LUMINANCE:
			retVal = "float";
			break;

		case OutputBufferProperty::LUMINANCE_ALPHA:
			retVal = "vec2";
			break;

		case OutputBufferProperty::LUMINANCE_FOR_DEPTH:
			retVal = "float";
			break;

		default:
			vgAssertN( false, "Unexpected value" );
	}

	return retVal;
}



const vgd::basic::IImage::Type convertToIImageType( const vgd::node::OutputBufferProperty::TypeValueType type )
{
	using vgd::basic::IImage;
	using vgd::node::OutputBufferProperty;

	IImage::Type retVal;

	switch ( type.value() )
	{
		case OutputBufferProperty::INTEGER:
			retVal = IImage::UINT8;
			break;

		case OutputBufferProperty::FLOAT16:
		case OutputBufferProperty::FLOAT32:
			retVal = IImage::FLOAT;
			break;

		default:
			vgAssertN( false, "Unexpected value" );
			retVal = IImage::UINT8;
	}
	return retVal;
}


const vgd::node::Texture::InternalFormatValueType convertToInternalFormatValueType(
	const vgd::node::OutputBufferProperty::FormatValueType	format,
	const vgd::node::OutputBufferProperty::TypeValueType	type )
{
	using vgd::node::Texture;
	using vgd::node::OutputBufferProperty;

	Texture::InternalFormatValueType retVal = Texture::AUTOMATIC;

	// RGB
	if ( format == OutputBufferProperty::RGB )
	{
		switch ( type.value() )
		{
			case OutputBufferProperty::INTEGER:
				break;

			case OutputBufferProperty::FLOAT16:
				retVal = Texture::RGB_16F;
				break;

			case OutputBufferProperty::FLOAT32:
				retVal = Texture::RGB_32F;
				break;

			default:
				vgAssertN( false, "Unexpected value" );
		}
	}
	// RGBA
	else if ( format == OutputBufferProperty::RGBA )
	{
		switch ( type.value() )
		{
			case OutputBufferProperty::INTEGER:
				break;

			case OutputBufferProperty::FLOAT16:
				retVal = Texture::RGBA_16F;
				break;

			case OutputBufferProperty::FLOAT32:
				retVal = Texture::RGBA_32F;
				break;

			default:
				vgAssertN( false, "Unexpected value" );
		}
	}
	// LUMINANCE
	else if ( format == OutputBufferProperty::LUMINANCE )
	{
		switch ( type.value() )
		{
			case OutputBufferProperty::INTEGER:
				break;

			case OutputBufferProperty::FLOAT16:
				retVal = Texture::LUMINANCE_16F;
				break;

			case OutputBufferProperty::FLOAT32:
				retVal = Texture::LUMINANCE_32F;
				break;

			default:
				vgAssertN( false, "Unexpected value" );
		}
	}
	// LUMINANCE_ALPHA
	else if ( format == OutputBufferProperty::LUMINANCE_ALPHA )
	{
		switch ( type.value() )
		{
			case OutputBufferProperty::INTEGER:
				break;

			case OutputBufferProperty::FLOAT16:
				retVal = Texture::LUMINANCE_ALPHA_16F;
				break;

			case OutputBufferProperty::FLOAT32:
				retVal = Texture::LUMINANCE_ALPHA_32F;
				break;

			default:
				vgAssertN( false, "Unexpected value" );
		}
	}
	// LUMINANCE_FOR_DEPTH
	else if ( format == OutputBufferProperty::LUMINANCE_FOR_DEPTH )
	{
		switch ( type.value() )
		{
			case OutputBufferProperty::INTEGER:
				retVal = Texture::DEPTH_COMPONENT_32;
				break;

			case OutputBufferProperty::FLOAT16:
				retVal = Texture::LUMINANCE_16F;
				break;

			case OutputBufferProperty::FLOAT32:
				retVal = Texture::LUMINANCE_32F;
				break;

			default:
				vgAssertN( false, "Unexpected value" );
		}
	}
	else
	{
		vgAssertN( false, "Unexpected format" );
	}

	return retVal;
}


const std::string getCommandString( vgd::node::OutputBufferProperty * outputBufferProperty )
{
	std::string retVal;

	using vgd::node::OutputBufferProperty;

	const OutputBufferProperty::CommandValueType command = outputBufferProperty->getCommand();
	switch ( command.value() )
	{
		case OutputBufferProperty::COLOR:
			retVal = "color";
			break;

		case OutputBufferProperty::NORMAL:
			retVal = "normal, 1.0";
			break;

		case OutputBufferProperty::POSITION:
			retVal = "ecPosition.xyz, 1.0";
			break;

		case OutputBufferProperty::DEPTH:
			retVal = "gl_FragCoord.z";
			break;

		case OutputBufferProperty::LINEAR_DEPTH:
// linear depth-buffer (will map near..far to 0..1)
//"	float near	= nearFar[0];\n"
//"	float far	= nearFar[1];\n"
//"	float linearDepth = (2.0 * near)/(far + near - gl_FragCoord.z * (far-near));\n"
			retVal = "(-ecPosition.z-nearFar[0])/(nearFar[1]-nearFar[0])";
			break;

		case OutputBufferProperty::CUSTOM:
			retVal = outputBufferProperty->getCustomCommand();
			break;

		default:
			retVal = "color";
			assert( false && "Unexpected value" );
	}
	return retVal;
}


}



META_HANDLER_CPP( OutputBufferProperty );



const vge::handler::Handler::TargetVector OutputBufferProperty::getTargets() const
{
	TargetVector targets;

	targets.reserve( 1 );
	targets.push_back( vgd::node::OutputBufferProperty::getClassIndexStatic() );

	return targets;
}



void OutputBufferProperty::apply( vge::engine::Engine* baseEngine, vgd::node::Node * node )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(baseEngine) != 0 );
	vgeGL::engine::Engine *engine = static_cast< vgeGL::engine::Engine* >(baseEngine);

	assert( dynamic_cast< vgd::node::OutputBufferProperty* >(node) != 0 );
	vgd::node::OutputBufferProperty *outputBufferProperty = static_cast< vgd::node::OutputBufferProperty* >(node);

	// Updates engine state
	if ( engine->isGLSLEnabled() )
	{
		using vgeGL::engine::GLSLState;
		GLSLState& glslState = engine->getGLSLState();

		vgd::Shp< GLSLState::OutputBufferPropertyState > outputBufferPropertyState( new GLSLState::OutputBufferPropertyState(outputBufferProperty) );

		const int multiAttributeIndex = computeMultiAttributeIndex( outputBufferProperty, glslState.outputBufferProperties );
		glslState.outputBufferProperties.setState( multiAttributeIndex, outputBufferPropertyState );
	}
}



void OutputBufferProperty::unapply( vge::engine::Engine* engine, vgd::node::Node* pNode )
{}



void OutputBufferProperty::setToDefaults()
{}



void OutputBufferProperty::paint(
	vgeGL::engine::Engine * engine,
	OutputBufferPropertyStateContainer * outputBufferProperties,
	std::back_insert_iterator< TextureContainer > backInserter )
{
	typedef vgeGL::engine::GLSLState::OutputBufferPropertyState OutputBufferPropertyState;
	using vgd::node::Texture;

	uint numFound = 0;
	for( uint i = 0; numFound < outputBufferProperties->getNum(); ++i )
	{
		vgd::Shp< OutputBufferPropertyState > outputBufferPropertyState = outputBufferProperties->getState(i);

		if ( outputBufferPropertyState )
		{
			++numFound;
			vgd::node::OutputBufferProperty * outputBufferProperty = outputBufferPropertyState->getNode();
			if ( outputBufferProperty )
			{
				vgd::Shp< vgd::node::Texture2D > texture = createTexture2D( engine, outputBufferProperty );
				backInserter = texture;
				++backInserter;

				// Validates node df
				outputBufferProperty->getDirtyFlag(outputBufferProperty->getDFNode())->validate();
			}
			else
			{
				vgAssertN( false, "Internal error" );
			}
		}
		else
		{
			//vgAssertN( false, "No output buffer property %i", i );
			vgd::Shp< vgd::node::Texture2D > texture;
			backInserter = texture;
			++backInserter;
		}
	}
}



vgd::Shp< vgd::node::Texture2D > OutputBufferProperty::createTexture2D( vgeGL::engine::Engine * engine, vgd::node::OutputBufferProperty * node )
{
	using vgd::node::OutputBufferProperty;
	using vgd::node::Texture;

	//
	const std::string nodeIndexStr = vgd::basic::toString( node->getMultiAttributeIndex() );
	vgd::Shp< vgd::node::Texture2D > texture = vgd::node::Texture2D::create( "attachment" + nodeIndexStr );

	// WRAP, FILTER
// @todo sethDefault();
	texture->setWrap( Texture::WRAP_S, Texture::CLAMP_TO_EDGE );
	texture->setWrap( Texture::WRAP_T, Texture::CLAMP_TO_EDGE );
	texture->setFilter( Texture::MIN_FILTER, Texture::NEAREST );
	texture->setFilter( Texture::MAG_FILTER, Texture::NEAREST );
	//texture->setFilter( Texture::MIN_FILTER, Texture::LINEAR );
	//texture->setFilter( Texture::MAG_FILTER, Texture::LINEAR );

	// IMAGE
	using vgd::basic::ImageInfo;

// @todo should work with ImageInfo(0, 0, 0, ....) see Texture handlers

	// IMAGE WIDTH / IMAGE HEIGHT
	float width		= static_cast< float >( engine->getDrawingSurfaceSize()[0] );
	float height	= static_cast< float >( engine->getDrawingSurfaceSize()[1] );

	const OutputBufferProperty::SizeSemanticValueType	sizeSemantic	= node->getSizeSemantic();
	const vgm::Vec2f									sizeRequested	= node->getSize();

	if ( sizeSemantic == OutputBufferProperty::SCALE_FACTOR )
	{
		width	*= sizeRequested[0];
		height	*= sizeRequested[1];
	}
	else
	{
		vgAssert( sizeSemantic == OutputBufferProperty::PIXEL_SIZE );
		width	= sizeRequested[0];
		height	= sizeRequested[1];
	}

	// Creates image for texture
	vgd::Shp< ImageInfo > image( new ImageInfo( (uint)width, (uint)height, 1 ) );
	texture->setImage( image );

	// IMAGE FORMAT / IMAGE TYPE / TEXTURE INTERNAL FORMAT
	const OutputBufferProperty::FormatValueType	format	= node->getFormat();
	const OutputBufferProperty::TypeValueType	type	= node->getType();

	// IMAGE FORMAT
	image->format()	= convertToIImageFormat( format );

	// IMAGE TYPE
	image->type()	= convertToIImageType( type );

	// TEXTURE INTERNAL FORMAT
	Texture::InternalFormatValueType internalFormat = convertToInternalFormatValueType( format, type );
	texture->setInternalFormat( internalFormat );

	// TEXTURE USAGE
	if ( format != OutputBufferProperty::LUMINANCE_FOR_DEPTH )
	{
		texture->setUsage( Texture::IMAGE );
	}
	else
	{
// @todo Adds DEPTH usage
		image->type() = vgd::basic::IImage::INT32;
		texture->setUsage( Texture::SHADOW );
	}

	return texture;
}



OutputBufferProperty::createsFBORetValType OutputBufferProperty::createsFBO( vgeGL::engine::Engine * engine,
	OutputBufferPropertyStateContainer * outputBufferProperties,
	std::back_insert_iterator< TextureContainer > backInserter,
	const bool addDepth )
{
	// Retrieves manager
	vgeGL::engine::Engine::GLManagerType& rcManager = engine->getGLManager();

	// Creates FBO node and GL rc
	vgd::Shp< vgd::node::FrameBuffer >			framebuffer	= vgd::node::FrameBuffer::create("ForwardRendering.frameBuffer");
	vgd::Shp< vgeGL::rc::FrameBufferObject >	fbo( new vgeGL::rc::FrameBufferObject() );

	createsFBORetValType retVal = std::make_pair( framebuffer, fbo );

	rcManager.add( framebuffer.get(), fbo );

	//
	fbo->generate();
	fbo->bind();

	// Creates texture(s)
	std::vector< vgd::Shp< vgd::node::Texture2D > > textureContainer;
	vgeGL::handler::painter::OutputBufferProperty::paint( engine, outputBufferProperties, std::back_inserter(textureContainer) );

	// For each texture, do attachment
	int firstValidIndex = -1;
	for( uint i=0; i < textureContainer.size(); ++i )
	{
		vgd::Shp< vgd::node::Texture2D > textureNode = textureContainer[i];

		backInserter = textureNode;
		++backInserter;

		if ( textureNode )
		{
			// Attaching images
			engine->paint( textureNode );
			vgd::Shp< vgeGL::rc::Texture2D > texture2D = rcManager.getShp< vgeGL::rc::Texture2D >( textureNode );
			vgAssertN( texture2D, "No texture2D" );

			fbo->attachColor( texture2D, i );
			if ( firstValidIndex == -1 )	firstValidIndex = i;
		}
		// else nothing to do
	}

	vgAssert( firstValidIndex >= 0 );

	if ( addDepth )
	{
		vgd::Shp< vgd::node::OutputBufferProperty > obuf = vgd::node::OutputBufferProperty::create("depth");
		obuf->setFormat( vgd::node::OutputBufferProperty::LUMINANCE_FOR_DEPTH );
		obuf->setType( vgd::node::OutputBufferProperty::INTEGER );
		obuf->setSizeSemantic( outputBufferProperties->getState(firstValidIndex)->getNode()->getSizeSemantic() );
		obuf->setSize( outputBufferProperties->getState(firstValidIndex)->getNode()->getSize() );

		vgd::Shp< vgd::node::Texture2D > depthTextureNode;
		depthTextureNode = vgeGL::handler::painter::OutputBufferProperty::createTexture2D( engine, obuf.get() );

		// Attaching images
		engine->paint( depthTextureNode );
		vgd::Shp< vgeGL::rc::Texture2D > depthTexture = rcManager.getShp< vgeGL::rc::Texture2D >( depthTextureNode );

		fbo->attachDepth( depthTexture );
	}

	// Checks framebuffer completeness at the end of initialization
	std::string fboStatus = fbo->getStatusString();
	if ( fboStatus.size() > 0 )
	{
		vgLogError( "OutputBufferProperty::createsFBO(): %s", fboStatus.c_str() );
		// return retVal;
		// @todo better error management
	}
	// else nothing to do

	fbo->unbind();

	return retVal;
}



const std::string OutputBufferProperty::getFragmentOutputDeclarationStageString(
	vgeGL::engine::Engine * engine,
	OutputBufferPropertyStateContainer * outputBufferProperties )
{
	typedef vgeGL::engine::GLSLState::OutputBufferPropertyState OutputBufferPropertyState;

	std::string retVal("// FragmentOutputDeclarationStage\n");

	if (!outputBufferProperties)
	{
		return retVal;
	}

	uint numFound = 0;
	for( uint i = 0; numFound < outputBufferProperties->getNum(); ++i )
	{
		vgd::Shp< OutputBufferPropertyState > outputBufferPropertyState = outputBufferProperties->getState(i);

		if ( outputBufferPropertyState )
		{
			++numFound;
			vgd::node::OutputBufferProperty * outputBufferProperty = outputBufferPropertyState->getNode();
			if ( outputBufferProperty )
			{
				const std::string formatType	= convertToGLSLFormat( outputBufferProperty->getFormat() );
				const std::string indexStr		= vgd::basic::toString(i);
				// "layout(location = I) out type outputBufferI;" 
				retVal += "layout(location = " + indexStr + ") out " + formatType + " outputBuffer" + indexStr + ";\n";
				const std::string customDeclaration = outputBufferProperty->getCustomDeclaration();
				if ( !customDeclaration.empty() )
				{
					retVal += "\n" + outputBufferProperty->getCustomDeclaration() + "\n";
				}
			}
		}
	}

	retVal += "\n";
	return retVal;
}



const std::string OutputBufferProperty::getFragmentOutputStageString(
	vgeGL::engine::Engine * engine,
	OutputBufferPropertyStateContainer * outputBufferProperties )
{
	typedef vgeGL::engine::GLSLState::OutputBufferPropertyState OutputBufferPropertyState;

	std::string retVal;

	if (!outputBufferProperties)
	{
		return retVal;
	}
	
	uint numFound = 0;
	for( uint i = 0; numFound < outputBufferProperties->getNum(); ++i )
	{
		vgd::Shp< OutputBufferPropertyState > outputBufferPropertyState = outputBufferProperties->getState(i);

		if ( outputBufferPropertyState )
		{
			++numFound;
			vgd::node::OutputBufferProperty * outputBufferProperty = outputBufferPropertyState->getNode();
			if ( outputBufferProperty )
			{
				const std::string formatType = convertToGLSLFormat( outputBufferProperty->getFormat() );
				const std::string commandString = getCommandString( outputBufferProperty );
				//	"	outputBufferI = formatType(command);\n"
				retVal +=
					"	outputBuffer" + vgd::basic::toString(i) + " = " + formatType + "(" + commandString + ");\n";
			}
		}
	}
	return retVal;
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
