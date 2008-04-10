// VGSDK - Copyright (C) 2004-2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VGD_HPP
#define _VGD_VGD_HPP

/**
 * @defgroup g_vgd vgd (V)ersatile (G)raphical (D)ata
 * 
 * vgd, a shortcut for Versatile Graphical Data, is a collection of classes for describing 3d world.
 *
 * vgd is open source (LGPL).
 */


/**
 * @defgroup g_images Images
 * 
 * @ingroup g_vgd
 */

/**
 * @defgroup g_shp Shp (shared pointer)
 * 
 * @ingroup g_vgd
 */

/**
 * @defgroup g_coordinatesSystem Coordinate Systems
 * 
 * @ingroup g_vgd
 * 
 * Coordinates system :
 * 	- Object coordinates system :
 * 	- Eye coordinates system :
 * 	- Clip coordinates system :
 * 	- Normalized device coordinates :
 * 	- Window coordinates system :
 *		The origin of this coordinates system is the bottom left corner of the window. Width and height are expressed in 
 * 		pixels.
 * 
 * 	- Normalized window coordinates system :
 * 		Width and height are expressed by a float within [0,1].
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
 * @defgroup g_groupNodes Group nodes
 * 
 * @ingroup g_nodes
 */

/**
 * @defgroup g_shapeNodes Shape nodes
 * 
 * @ingroup g_nodes
 */

/**
 * @defgroup g_attributeNodes Attribute nodes
 * 
 * @ingroup g_nodes
 */

/**
 * @defgroup g_singleAttributeNodes Single attribute nodes
 * 
 * @ingroup g_attributeNodes
 * @ingroup g_nodes
 */

/**
 * @defgroup g_multiAttributeNodes Multi attribute nodes
 * 
 * @ingroup g_attributeNodes
 * @ingroup g_nodes
 */

/**
 * @defgroup g_frameBufferNodes Frame Buffer Operations nodes
 * 
 * @ingroup g_nodes
 */

/**
 * @defgroup g_propertiesNodes Properties
 * 
 * @ingroup g_nodes
 */

/**
 * @defgroup g_transformationNodes Transformation nodes
 * 
 * @ingroup g_nodes
 */

/**
 * @defgroup g_coloringAndLightingNodes Coloring and Lighting nodes
 * 
 * @ingroup g_nodes
 */

/**
 * @defgroup g_texturingNodes Texture mapping nodes
 * 
 * @ingroup g_nodes
 */

/**
 * @defgroup g_nodekits Node kits
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
 * @brief (V)ersatile (G)raphical (D)ata
 */

#include <vgBase/Type.hpp>

#ifdef _WIN32

	#ifdef VGD_EXPORTS
	#define VGD_API	__declspec(dllexport)
	#else
	#define VGD_API	__declspec(dllimport)
	#endif

	#define VGD_CLASS_API

#elif defined(__GNUC__) && (__GNUC__>=4) && defined(__USE_DYLIB_VISIBILITY__)

	#ifdef VGD_EXPORTS
	#define VGD_API __attribute__ ((visibility("default")))
	#define VGD_CLASS_API __attribute__ ((visibility("default")))
	#else
	#define VGD_API __attribute__ ((visibility("hidden")))
	#define VGD_CLASS_API __attribute__ ((visibility("hidden")))
	#endif

#else

	#define VGD_API
	#define VGD_CLASS_API

#endif



#endif //#ifndef _VGD_VGD_HPP
