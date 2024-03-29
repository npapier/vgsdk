// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_ENGINE_SETTINGS_HPP
#define _VGEGL_ENGINE_SETTINGS_HPP

#include "vgeGL/vgeGL.hpp"

namespace vgd
{
	namespace node
	{
		struct VertexShape;
	}
}



namespace vgeGL
{
	
namespace engine
{

	struct Engine;

struct ProcessingMethod
{
	//virtual void paint( vgeGL::engine::Engine*, vgd::node::VertexShape* )=0;
};
	
struct VertexProcessingMethod : public ProcessingMethod
{};

struct VertexArrayMethod : public VertexProcessingMethod
{
};

struct VertexArrayDisplayListMethod : public VertexArrayMethod
{
};

//
//
//	/**
//	 * @name ThingToProcess/ProcessingMethod.
//	 */
//	//@{
//	insert(
//	
//	"static_VertexShape", STATIC_VERTEXSHAPE, VertexProcessingMethod.
//	std::string strThingToProcess[] = 
//	
//	"dynamic_VertexShape"
//	typedef enum {
//		
//		STATIC_VERTEXSHAPE		= 0,
//
//		DYNAMIC_VERTEXSHAPE
//
//	} ThingToProcess;
//
//
//	struct ImmediateMode	: public VertexProcessingMethod
//	{};
//	struct DisplayList	: public ImmediateMode
//	{};
//
//	struct VertexArray	: public VertexProcessingMethod
//	{};
//	
//	struct VertexBufferObject : public VertexArray
//	{};
//	
//	//@}
//
//	const VertexProcessingMethod*	getVertexProcessionMethod( )
//	
//	std::auto_ptr< VertexProcessingMethod > 
//	{};
//
//

} // namespace engine

} // namespace vgeGL

#endif //#ifndef _VGEGL_ENGINE_SETTINGS_HPP
