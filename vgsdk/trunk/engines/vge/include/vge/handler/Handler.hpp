// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_HANDLER_H
#define _VGE_HANDLER_HANDLER_H

#include "vge/vge.hpp"

#include <vector>

#include "vge/handler/HandlerRegistry.hpp"
#include "vge/handler/RegisterHandler.hpp"
#include "vge/service/Service.hpp"

namespace vgd
{
	namespace node
	{
		struct Node;
	}
}

namespace vge
{
	namespace engine
	{
		struct Engine;
	}
}


/** 
 * @namespace vge::handler
 * 
 * @brief Handlers implements services to evaluate node.
 */



namespace vge
{
	
namespace handler
{



/**
 * @brief Meta helper.
 */
#define META_HANDLER_HPP( handlerType )	private:\
 \
static const vge::handler::RegisterHandler< handlerType >	registrationInstance; \
public:



/**
 * @brief Meta helper.
 */
#define META_HANDLER_CPP( handlerType ) const vge::handler::RegisterHandler< handlerType >	handlerType::registrationInstance;



/**
 * @brief Abstract base class for handlers.
 */
struct VGE_API Handler
{
	/**
	 * @brief Typedef for vector of target.
	 */
	typedef std::vector< int32 >	TargetVector;

	/**
	 * @name Registry.
	 */
	//@{

	/**
	 * @brief Returns the handler registry (i.e. the registered handlers table).
	 */
	static HandlerRegistry&						getClassRegistry( void );

	//@}

	virtual const vge::service::List			getServices()	const=0;
	virtual const TargetVector					getTargets()	const=0;
	
	virtual void	apply		( vge::engine::Engine*, vgd::node::Node* )=0;
	virtual void	unapply	( vge::engine::Engine*, vgd::node::Node* )=0;

	/**
	 * @brief Sets all OpenGL states used by this node to their defaults values (see the documentation of the node
	 * associated to this handlers).
	 * This is very useful for Attribute nodes (because attribute nodes change OpenGL state, this is not generally the 
	 * case for Shape nodes).
	 * 
	 * @remarks Be careful about states that could be initialized, by more than one handlers, with differents values 
	 * (like all \c GeometricalTransformation).
	 * 
	 * @todo Must go in vgeGL.
	 */
	virtual void	setToDefaults()=0;
};



} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_HANDLER_H
