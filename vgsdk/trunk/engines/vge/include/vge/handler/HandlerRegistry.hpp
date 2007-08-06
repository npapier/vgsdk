// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_HANDLERREGISTRY_HPP
#define _VGE_HANDLER_HANDLERREGISTRY_HPP

#include "vge/vge.hpp"

#include <set>
#include <utility>
#include <vgd/Shp.hpp>



namespace vge
{

namespace handler
{

struct Handler;

/**
 * @brief Repository for registered handlers.
 * 
 */
struct VGE_API HandlerRegistry
{
	/**
	 * @name Typedefs.
	 */
	//@{
	
	/**
	 * @brief Set of all registred handlers.
	 */
	typedef std::set< vgd::Shp<Handler> >			HandlersSet;

	//@}
	
	
	
	/**
	 * @brief Register a new handler.
	 *
	 * @param pHandler		pointer on handler.
	 * 
	 * @return true if node is successfully registered, false otherwise(already registered).
	 * 
	 * @remarks pHandler is deleted by the HandlerRegistry.
	 */
	bool				add( Handler *pHandler );

	/**
	 * @brief Gets all registered handlers.
	 * 
	 * @return A string with all registered handlers name separated by space.
	 */
	std::string		get() const;

	/**
	 * @brief Returns the number of registered handlers.
	 *
	 * @return number of registered handlers.
	 */
	uint32			getNumRegistered() const;
	
	/**
	 * @brief Gets a pair with a begin and end iterator on the handlers map.
	 */
	std::pair< HandlersSet::iterator, HandlersSet::iterator > getIterators();



private:

	/**
	 * @brief Container for registry.
	 */
	HandlersSet		m_handlers;
};



} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_HANDLERREGISTRY_HPP
