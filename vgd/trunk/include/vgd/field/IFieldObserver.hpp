// VGSDK - Copyright (C) 2004, 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_IFIELDOBSERVER_HPP
#define _VGD_FIELD_IFIELDOBSERVER_HPP

#include "vgd/vgd.hpp"

#include "vgd/field/Types.hpp"



namespace vgd
{

namespace field
{
	struct	AbstractField;

/**
 * @brief Interface for field observer in \b DP \b Observer
 */
struct VGD_API IFieldObserver
{
	/**
	 * @brief Virtual destructor
	 */
	virtual ~IFieldObserver() {}

	/**
	 * @brief Receive a notification from a field (the subject in DP Observer).
	 * 
	 * @remarks Implements the Observer updating interface.
	 *
	 * @param	rField	shared pointer on the field that send the update.
	 * @param	event	give more useful informations of this update message.
	 */
	virtual void updateField( const AbstractField& rField, const Event event )=0;
};



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_IFIELDOBSERVER_HPP
