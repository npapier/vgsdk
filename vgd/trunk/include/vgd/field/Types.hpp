// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_TYPES_H
#define _VGD_FIELD_TYPES_H

#include "vgd/vgd.hpp"



namespace vgd
{

namespace field
{

/**
 * @brief All editing mode.
 */
typedef enum { 
	NONE,	/*!< no accesses. */
	RO,		/*!< read-only acesses. */
	RW		/*!< read-write acesses. */
} EditingMode;

/**
 * @brief Event type(used by Observer design pattern).
 */
typedef enum { 
		DESTROY, 
		UPDATE 
} Event;	



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_TYPES_H
