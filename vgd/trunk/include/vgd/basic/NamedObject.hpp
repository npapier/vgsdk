// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BSC_NAMEDOBJECT_HPP
#define _VGD_BSC_NAMEDOBJECT_HPP

#include "vgd/vgd.hpp"

#include <string>



namespace vgd
{

namespace basic
{

/**
 * @brief Object with a name.
 * 
 * Each instance of this class has a name.
 * 
 * @remarks \b Assignable and not \b DefaultConstructible.
 */
struct VGD_API NamedObject
{
	/**
	 * @name Constructor.
	 */
	//@{
	
	/**
	 * @brief Default constructor.
	 */
	NamedObject( const std::string strName ) :
		m_strFlagName(strName)
	{}
	//@}

	/**
	 * @name Accessors.
	 */
	//@{

	/**
	 * @brief Sets the name.
	 */
	void				name( const std::string strName )
	{ 
		m_strFlagName = strName; 
	}

	/**
	 * @brief Returns name of this instance.
	 */
	const std::string&	name( void ) const
	{
		return ( m_strFlagName );
	}

private:

	/**
	 * @name Private data.
	 */
	//@{
	/**
	 * @brief The name.
	 */
	std::string m_strFlagName;
	//@}
};



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BSC_NAMEDOBJECT_HPP
