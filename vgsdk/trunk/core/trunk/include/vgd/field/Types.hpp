// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_TYPES_HPP
#define _VGD_FIELD_TYPES_HPP



namespace vgd
{

namespace field
{

/**
 * @brief All editing mode.
 */
enum EditingMode 
{ 
	NONE,	/*!< no accesses. */
	RO,		/*!< read-only acesses. */
	RW		/*!< read-write acesses. */
};

/**
 * @brief Event type(used by Observer design pattern).
 */
enum Event 
{
	DESTROY, 
	UPDATE 
};	



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_TYPES_HPP
