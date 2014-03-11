// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_BINDING_HPP
#define _VGD_NODE_BINDING_HPP

#include "vgd/vgd.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Enumeration of all bindings modes.
 * 
 * Binding is used to defined the type of association between attributes and vertices.
 * Attributes could be :
 * \li normals.
 * \li colors or secondary colors.
 * \li textures.
 * \li and so on.
 */
typedef enum {
	BIND_OFF = 0,				/*!< No attribute at all */
	BIND_OVERALL,				/*!< One attribute for the entire shape */
	BIND_PER_PRIMITIVE,		/*!< One attribute per primitive (a sequence of triangles, triangles-strip...) */
	BIND_PER_VERTEX			/*!< One attribute per vertex */
} Binding;



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_BINDING_HPP
