// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller
// Author Nicolas Papier

#include "vgUI/node/InsertNode.hpp"

#include <boost/assign.hpp>


namespace vgUI
{

namespace node
{


namespace
{
static std::vector< std::string > insertNodeNames = boost::assign::list_of("Antialiasing")
																			("ClipPlane")
																			("CullFace")
																			("DepthOfField")
																			("DirectionalLight")
																			("DrawStyle")
																			("EngineProperties")
																			("Fluid")
																			("FrontFace")
																			("Group")
																			("LightModel")
																			("Material")
																			("MatrixTransform")
																			("Noise")
																			("OutputBuffers")
																			("OutputBufferProperty")
																			("PointLight")
																			("PostProcessing")
																			("Separator")
																			("SpotLight")
																			("Transform");
}


const std::vector< std::string >& getInsertNodeNames()
{
	return insertNodeNames;
}


} // namespace node

} // namespace vgUI
