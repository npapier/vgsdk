// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_POSTPROCESSING_HPP
#define _VGEGL_TECHNIQUE_POSTPROCESSING_HPP

#include <vgd/node/PostProcessing.hpp>

namespace vgd { namespace node { struct Texture2D; } }

namespace vgeGL
{

namespace technique
{



vgd::Shp< vgd::node::Texture2D > getInputTexture( const vgd::node::PostProcessing::Input0ValueType input,
	std::vector< vgd::Shp< vgd::node::Texture2D > >* outputBufferTexture,
	std::vector< vgd::Shp< vgd::node::Texture2D > >* tmpBuffers );

vgd::Shp< vgd::node::Texture2D > getOutputTexture( const vgd::node::PostProcessing::OutputValueType output,
	std::vector< vgd::Shp< vgd::node::Texture2D > >* outputBufferTexture,
	std::vector< vgd::Shp< vgd::node::Texture2D > >* tmpBuffers );


const std::string getPostProcessingDeclarations();

const std::string getPostProcessingVertexProgram();

const std::string getPostProcessingFragmentProgram();



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_POSTPROCESSING_HPP
