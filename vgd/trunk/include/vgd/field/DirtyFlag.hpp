// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_DIRTYFLAG_H
#define _VGD_FIELD_DIRTYFLAG_H

#include "vgd/vgd.hpp"

#include <map>

#include "vgd/basic/NamedObject.hpp"



namespace vgd
{

namespace field
{



/**
 * @brief Basic class for management of validation/invalidation of an object.
 *
 * This is very useful for validate/invalidate of bounding box, neighbour, rendering compilation and so on.
 * 
 * @remarks \b Assignable but not \b DefaultConstructible.
 * 
 * @remarks Used by FieldManager.
 */
struct VGD_API DirtyFlag : public vgd::basic::NamedObject
{
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 *
	 * @param strFlagName	: name of this flag.
	 * @param bIsDirty		: initial state of this flag.
	 */
	DirtyFlag( const std::string& strFlagName, const bool bIsDirty = true );

	/**
	 * @brief Destructor.
	 */
	~DirtyFlag( void );
	//@}



	/**
	 * @name Accessors.
	 */
	//@{

	/**
	 * @brief Test this flag.
	 *
	 * @return true if this flag is dirty, false otherwise.
	 */
	const bool	isDirty	( void ) const;

	/**
	 * @brief Test this flag.
	 *
	 * @return true if this flag is valid, false otherwise.
	 */
	const bool	isValid	( void ) const;

	/**
	 * @brief Set this flag to dirty or valid.
	 * 
	 * @param setToDirty	: true if this flag must be set to dirty, false for validating it.
	 */
	void			dirty	( const bool setToDirty = true );

	/**
	 * @brief Set this flag to valid or dirty.
	 * 
	 * @param setToValid	: true if this flag must be set to valid, false for invalidating(dirty) it.
	 */
	void		validate( const bool setToValid = true );
	//@}

private:

	/** 
	 * @name Private data.
	 */
	//@{
	bool m_bIsDirty;
	//@}
};

/**
 * @brief Typedef for the dirty flag container.
 * 
 * key of map		: name of DirtyFlag.
 * value of map	: DirtyFlag.
 */
typedef std::map< std::string, DirtyFlag >		MapDirtyFlag;



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_DIRTYFLAG_H
