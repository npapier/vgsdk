// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VGD_H
#define _VGD_VGD_H

/**
 * @defgroup g_vgd Virtuals Graphical Data
 * 
 * Virtuals Graphical Data is a collection of classes for describing 3d world.
 *
 * vgD is open source (LGPL).
 */


/**
 * @defgroup g_images Images
 * 
 * @ingroup g_vgd
 */

/**
 * @defgroup g_nodes Nodes
 * 
 * @ingroup g_vgd
 */

/**
 * @defgroup g_abstractNodes Abstract nodes
 * 
 * @ingroup g_nodes
 */
 
/**
 * @defgroup g_groupNodes Group nodes.
 * 
 * @ingroup g_nodes
 */

/**
 * @defgroup g_shapeNodes Shape nodes.
 * 
 * @ingroup g_nodes
 */

/**
 * @defgroup g_attributeNodes Attribute nodes.
 * 
 * @ingroup g_nodes
 */

/**
 * @defgroup g_singleAttributeNodes Single attribute nodes.
 * 
 * @ingroup g_attributeNodes
 * @ingroup g_nodes
 */

/**
 * @defgroup g_multiAttributeNodes Multi attribute nodes.
 * 
 * @ingroup g_attributeNodes
 * @ingroup g_nodes
 */

/**
 * @defgroup g_frameBufferNodes Frame Buffer Operations nodes.
 * 
 * @ingroup g_nodes
 */

/**
 * @defgroup g_propertiesNodes Properties
 * 
 * @ingroup g_nodes
 */

/**
 * @defgroup g_transformationNodes Transformation nodes.
 * 
 * @ingroup g_nodes
 */

/**
 * @defgroup g_coloringAndLightingNodes Coloring and Lighting nodes.
 * 
 * @ingroup g_nodes
 */

/**
 * @defgroup g_texturingNodes Texture mapping nodes.
 * 
 * @ingroup g_nodes
 */

/**
 * @defgroup g_nodekits Node kits.
 * 
 * @ingroup g_nodes
 */

// Shape :Primitives
// Coordinate Transformation
// 
// Clipping
// Rasterization
// Pixel Operations
// Texture Mapping
// Fog
// 
// Evaluators
// Selection and Feedback
// Modes and Execution
// State Queries and debug

// Polygon Tessellation
// Controlling Rendering

/** 
 * @namespace vgd
 * 
 * @brief Virtuals Graphical Data
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

   #ifdef VGD_EXPORTS
   #define VGD_API	__declspec(dllexport)
   #else
   #define VGD_API	__declspec(dllimport)
   #endif

#else

    #define VGD_API

#endif



#endif //#ifndef _VGD_VGD_H
