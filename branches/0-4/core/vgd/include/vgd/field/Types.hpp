// VGSDK - Copyright (C) 2004, 2008, Nicolas Papier.
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
 * @name All editing mode
 */
//@{

/**
 * @brief Definition of access modes
 */
// enum AccessMode {
	// NO,	///< no access
	// RW,	///< read-write access
	// RO		///< read-only access
// };

/**
 * @brief Definition of editing modes
 */
enum EditingMode {
	RW		= -1,
	NONE	= 0,
	RO		= 1
};
//const EditingMode RW		= -1;	/*!< read-write access */
//const EditingMode NONE	= 0;	/*!< no access */
//const EditingMode RO		= 1;	/*!< read-only access */

//@}



/**
 * @brief Event type (used by Observer design pattern).
 */
enum Event 
{
	DESTROY, 
	UPDATE 
};	



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_TYPES_HPP
