// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGOPENASSETIMPORT_HELPERS_HPP
#define _VGOPENASSETIMPORT_HELPERS_HPP

#include "vgOpenAssetImport/vgOpenAssetImport.hpp"
#include <vgd/Shp.hpp>

struct aiMesh;
struct aiMaterial;
struct aiScene;
namespace vgd { namespace node { struct Material; struct VertexShape; } }


namespace vgOpenAssetImport
{


VGOPENASSETIMPORT_API vgd::Shp< aiMesh > createAiMesh( vgd::node::VertexShape * vertexShape );

VGOPENASSETIMPORT_API void fillAiMesh( vgd::node::VertexShape * vertexShape, aiMesh * mesh );
VGOPENASSETIMPORT_API void fillAiMaterial( vgd::node::Material * material, aiMaterial * aimaterial );

VGOPENASSETIMPORT_API aiScene * createAiScene( vgd::node::VertexShape * vertexShape );


} // namespace vgOpenAssetImport


#endif // _VGOPENASSETIMPORT_HELPERS_HPP
