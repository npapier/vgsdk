// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/PostProcessing.hpp"



namespace vgeGL
{

namespace technique
{



vgd::Shp< vgd::node::Texture2D > getInputTexture( const vgd::node::PostProcessing::Input0ValueType input,
	std::vector< vgd::Shp< vgd::node::Texture2D > >* outputBufferTexture,
	std::vector< vgd::Shp< vgd::node::Texture2D > >* tmpBuffers )
{
	using vgd::node::PostProcessing;

	vgd::Shp< vgd::node::Texture2D > retVal;

	//
	const int	inputValue = input.value();
	int			outputBufferIndex	= -1;
	int			tmpBufferIndex		= -1;

	// OUTPUT_BUFFER
	if (	(PostProcessing::OUTPUT_BUFFER0 <= inputValue) &&
			(inputValue <= PostProcessing::OUTPUT_BUFFER7)	)
	{
		outputBufferIndex = inputValue - PostProcessing::OUTPUT_BUFFER0;
	}
	else if (	(PostProcessing::INPUT1_OUTPUT_BUFFER0 <= inputValue) &&
				(inputValue <= PostProcessing::INPUT1_OUTPUT_BUFFER7)	)
	{
		outputBufferIndex = inputValue - PostProcessing::INPUT1_OUTPUT_BUFFER0;
	}
	else if (	(PostProcessing::INPUT2_OUTPUT_BUFFER0 <= inputValue) &&
				(inputValue <= PostProcessing::INPUT2_OUTPUT_BUFFER7)	)
	{
		outputBufferIndex = inputValue - PostProcessing::INPUT2_OUTPUT_BUFFER0;
	}
	// PREVIOUS
	else if (	(PostProcessing::PREVIOUS0 == inputValue) ||
				(PostProcessing::INPUT1_PREVIOUS0 == inputValue) ||
				(PostProcessing::INPUT2_PREVIOUS0 == inputValue)	)
	{
		tmpBufferIndex = 0;
	}
	// NONE
	else if (	(PostProcessing::NONE == inputValue) ||
				(PostProcessing::INPUT1_NONE == inputValue) ||
				(PostProcessing::INPUT2_NONE == inputValue)	)
	{
		// @todo returns black texture
	}
	else
	{
		vgAssertN( false, "Unexpected value" );
	}

	// Computes the returned texture node
	if ( outputBufferIndex >= 0 )
	{
		if ( outputBufferIndex < static_cast< int >(outputBufferTexture->size()) )
		{
			retVal = (*outputBufferTexture)[outputBufferIndex];
		}
		else
		{
			vgAssertN( false, "Out of range OUTPUT_BUFFER%i", outputBufferIndex );
		}
	}
	else if ( tmpBufferIndex >= 0 )
	{
		if ( tmpBufferIndex < static_cast< int >(tmpBuffers->size()) )
		{
			retVal = (*tmpBuffers)[tmpBufferIndex];
		}
		else
		{
			vgAssertN( false, "Out of range PREVIOUS%i", tmpBufferIndex );
		}
	}

	return retVal;
}


vgd::Shp< vgd::node::Texture2D > getOutputTexture( const vgd::node::PostProcessing::OutputValueType output,
	std::vector< vgd::Shp< vgd::node::Texture2D > >* outputBufferTexture,
	std::vector< vgd::Shp< vgd::node::Texture2D > >* tmpBuffers )
{
	using vgd::node::PostProcessing;

	vgd::Shp< vgd::node::Texture2D > retVal;

	//
	const int	outputValue = output.value();
	int			outputBufferIndex	= -1;
	int			tmpBufferIndex		= -1;

	// OUTPOUT_OUTPUT_BUFFER
	if (	(PostProcessing::OUTPUT_OUTPUT_BUFFER0 <= outputValue) &&
			(outputValue <= PostProcessing::OUTPUT_OUTPUT_BUFFER7)	)
	{
		outputBufferIndex = outputValue - PostProcessing::OUTPUT_OUTPUT_BUFFER0;
	}
	// TMP
	else if ( PostProcessing::OUTPUT_TMP0 )
	{
		tmpBufferIndex = 0;
	}
	else
	{
		vgAssertN( false, "Unexpected value" );
	}

	// Computes the returned texture node
	if ( outputBufferIndex >= 0 )
	{
		if ( outputBufferIndex < static_cast< int >(outputBufferTexture->size()) )
		{
			retVal = (*outputBufferTexture)[outputBufferIndex];
		}
		else
		{
			vgAssertN( false, "Out of range OUTPUT_OUTPUT_BUFFER%i", outputBufferIndex );
		}
	}
	else if ( tmpBufferIndex >= 0 )
	{
		if ( tmpBufferIndex < static_cast< int >(tmpBuffers->size()) )
		{
			retVal = (*tmpBuffers)[tmpBufferIndex];
		}
		else
		{
			vgAssertN( false, "Out of range OUTPUT_TMP%i", tmpBufferIndex );
		}
	}

	return retVal;
}


const std::string getPostProcessingDeclarations()
{
	const std::string tmp =
		"// UNIFORM for PostProcessing\n"
		"uniform float param1f0;\n"
		"uniform float param1f1;\n"
		"uniform vec4 param4f0;\n"
		"uniform vec4 param4f1;\n"
		"uniform mat4 param4x4f0;\n"
		"\n";

	return tmp;
}


const std::string getPostProcessingVertexProgram()
{
	const std::string tmp =
	"void main( void )\n"
	"{\n"
	"	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
	"\n"
	"INLINE_FTEXGEN\n"
	"}\n";

	return tmp;
}


const std::string getPostProcessingFragmentProgram()
{
	const std::string tmp =
	"void main( void )\n"
	"{\n"
	"	vec4 color = vec4(0);\n"
	"	INLINE_POST_PROCESSING"
	"	gl_FragColor = color;\n"
	"}\n";

	return tmp;
}


} // namespace technique

} // namespace vgeGL
