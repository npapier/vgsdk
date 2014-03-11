// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller
// Author Nicolas Papier

#ifndef _VGUI_NODE_INSERTNODE_HPP_
#define _VGUI_NODE_INSERTNODE_HPP_

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 40
#include <boost/mpl/vector.hpp>

#include "vgUI/vgUI.hpp"

#include <vgd/node/Antialiasing.hpp>
#include <vgd/node/ClipPlane.hpp>
#include <vgd/node/CullFace.hpp>
#include <vgd/node/DepthOfField.hpp>
#include <vgd/node/DirectionalLight.hpp>
#include <vgd/node/DrawStyle.hpp>
#include <vgd/node/EngineProperties.hpp>
#include <vgd/node/Fluid.hpp>
#include <vgd/node/FrontFace.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/MatrixTransform.hpp>
#include <vgd/node/Noise.hpp>
#include <vgd/node/OutputBuffers.hpp>
#include <vgd/node/OutputBufferProperty.hpp>
#include <vgd/node/PointLight.hpp>
#include <vgd/node/PostProcessing.hpp>
#include <vgd/node/Separator.hpp>
#include <vgd/node/SpotLight.hpp>
#include <vgd/node/Transform.hpp>


namespace vgUI
{

namespace node
{


typedef boost::mpl::vector<	vgd::Shp< vgd::node::Antialiasing >,
                            vgd::Shp< vgd::node::ClipPlane >,
                            vgd::Shp< vgd::node::CullFace >,
                            vgd::Shp< vgd::node::DepthOfField >,
                            vgd::Shp< vgd::node::DirectionalLight >,
                            vgd::Shp< vgd::node::DrawStyle >,
                            vgd::Shp< vgd::node::EngineProperties >,
                            vgd::Shp< vgd::node::Fluid >,
                            vgd::Shp< vgd::node::FrontFace >,
                            vgd::Shp< vgd::node::Group >,
                            vgd::Shp< vgd::node::LightModel >,
                            vgd::Shp< vgd::node::Material >,
                            vgd::Shp< vgd::node::MatrixTransform >,
                            vgd::Shp< vgd::node::Noise >,
                            vgd::Shp< vgd::node::OutputBuffers >,
                            vgd::Shp< vgd::node::OutputBufferProperty >,
                            vgd::Shp< vgd::node::PointLight >,
                            vgd::Shp< vgd::node::PostProcessing >,
                            vgd::Shp< vgd::node::Separator >,
                            vgd::Shp< vgd::node::SpotLight >,
                            vgd::Shp< vgd::node::Transform >
                                > insertNodeShapes;


VGUI_API const std::vector< std::string >& getInsertNodeNames();


} // namespace node

} // namespace vgUI

#endif // _VGUI_NODE_INSERTNODE_HPP_
