// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_ENUMREGISTRY_HPP
#define _VGD_NODE_ENUMREGISTRY_HPP

#include <map>
#include <string>
#include "vgd/vgd.hpp"



namespace vgd
{

namespace node
{

struct VGD_API EnumRegistry
{
	/**
	 * @brief Converts to a string an enumeration value
	 *
	 * @param enumValue	the enumeration value to convert
	 *
	 * @return the string representing the enumeration value
	 */
	static const std::string toString( const int enumValue );

private:
	typedef std::map< const int, std::string > ToStringType;	//< typedef for the registry storing association between enum value and enum string
	static ToStringType m_toString;								//< instanciation of the registry

	/**
	 * @brief Initializes the registry
	 */
	static void initialize();
};

} // namespace node

} // namespace vgd

#endif // #ifndef _VGD_NODE_ENUMREGISTRY_HPP
