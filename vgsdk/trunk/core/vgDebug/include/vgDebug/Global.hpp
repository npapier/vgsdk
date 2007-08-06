// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGDEBUG_GLOBAL_HPP
#define _VGDEBUG_GLOBAL_HPP

#include "vgDebug/vgDebug.hpp"

#include "vgDebug/Logging.hpp"



namespace vgDebug
{



/**
 * @brief Access to the global debug logger.
 */
VGDEBUG_API ILogging& get();



struct Global
{
	/**
	 * @brief Access to the global debug logger.
	 */
	static ILogging& get();



private:

	static Logging		m_globalLogger;
};



} // namespace vgDebug

#endif //#ifndef _VGDEBUG_GLOBAL_HPP
