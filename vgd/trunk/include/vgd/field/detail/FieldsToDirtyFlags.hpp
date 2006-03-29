// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_DETAIL_FIELDSTODIRTYFLAGS_HPP
#define _VGD_FIELD_DETAIL_FIELDSTODIRTYFLAGS_HPP

#include "vgd/vgd.hpp"

#include <set>
#include <utility>

#include "vgd/field/DirtyFlag.hpp"



namespace vgd
{
	
namespace field
{

namespace detail
{

/**
 * @brief Store all links between fields and DirtyFlags.
 *
 * @remarks \b Assignable and \b DefaultConstructible.
 * 
 * Field and DirtyFlags are specified by name.
 * 
 * @remarks Used in \c FieldManager to propagate the invalidation of a field to all related DirtyFlag.
 *
 * @todo Constructor with initialization from an iterator and a size.
 */
struct FieldsToDirtyFlags
{
	/**
	 * @name Several typedefs.
	 */
	//@{

	/**
	 * @brief Set of dirty flag names.
	 */
	typedef std::set< std::string > SetDirtyFlagNames;
	//@}



	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	FieldsToDirtyFlags( void );
	//@}



	/**
	 * @name Accessors for adding/deleting links.
	 * 
	 * @todo remove( const std::string strDirtyFlagName );
	 */
	//@{

	/**
	 * @brief Add a link between a field and a dirty flag.
	 * 
	 * @param strFieldName		: name of field.
	 * @param strDirtyFlagName	: name of dirty flag.
	 * 
	 * @return true if link is successfully added, false otherwise.
	 */
	bool add( const std::string strFieldName, const std::string strDirtyFlagName );

	/**
	 * @brief Remove a link between a field and a dirty flag.
	 * 
	 * @param strFieldName		: name of field.
	 * @param strDirtyFlagName	: name of dirty flag.
	 * 
	 * @return true if link is successfully removed, false if it does'nt exist.
	 */
	bool remove( const std::string strFieldName, const std::string strDirtyFlagName );
		
	/**
	 * @brief Remove all links for a field.
	 * 
	 * @param strFieldName		: name of field.
	 * 
	 * @return true if all links are successfully removed, false if the field does'nt exist.
	 */
	bool removeField( const std::string strFieldName );
	//@}


	
	/**
	 * @name Accessors.
	 */
	//@{
	
	/**
	 * @brief Returns iterator on dirty flag names set link to the field.
	 * 
	 * @param strFieldName		: name of field.
	 * 
	 * @return a pair with a begin iterator(the first element of the pair) and 
	 * the end iterator(the second element of the pair).
	 */
	std::pair< SetDirtyFlagNames::iterator, SetDirtyFlagNames::iterator >
		getIterators( const std::string strFieldName );

	/**
	 * @brief Returns number of fields 
	 * 
	 * that are linked to dirty flag(s).
	 */
	int32		getNumFields( void ) const;
	
	/**
	 * @brief Returns number of dirty flags linked to a field.
	 * 
	 * @param strFieldName : name of the field.
	 */
	int32		getNumLinkedDirtyFlags( const std::string strFieldName );
	
private:
	
	/**
	 * @brief Returns the set of dirty flag names that is linked to a field.
	 * 
	 * @param strFieldName : name of the field.
	 * 
	 * @return References to the set of dirty flag names.
	 * 
	 * @remarks If the field named strFieldName is not link to any dirty flags,
	 * an empty link is created automatically.
	 */
	SetDirtyFlagNames&			get( const std::string strFieldName );
	//@}



	/**
	 * @name Data.
	 */
	//@{

	/**
	 * @brief Container of links between field and dirty flag(s).
	 * 
	 * string				: name of field.
	 * SetDirtyFlagNames	: set of dirty flag names.
	 */
	typedef std::map< std::string, SetDirtyFlagNames > MapLinks;

	MapLinks			m_links;
	
	//@}
};



} // namespace detail

} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_DETAIL_FIELDSTODIRTYFLAGS_HPP
