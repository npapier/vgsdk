// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_ENUMREGISTRY_HPP
#define _VGD_NODE_ENUMREGISTRY_HPP

#include <map>
#include <string>
#include "vgd/vgd.hpp"

namespace vgd { template<class T> struct Shp; }
namespace vgd { namespace field { struct Enum; } }



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

	/**
	 * @brief Converts the given enumeration value to the real enumeration type.
	 *
	 * @param enumValue	the enumeration value to convert
	 *
	 * @return the desired enum type
	 */
	static const vgd::Shp< vgd::field::Enum > toEnum( const int enumValue );

private:
	typedef std::map< const int, std::string > ToStringType;	//< typedef for the registry storing association between enum value and enum string
	static ToStringType m_toString;								//< instanciation of the registry

	typedef std::map< const int, vgd::Shp< vgd::field::Enum > > ToEnumType;	//< typedef for the registry storing association between enum value and the real enum type
	static ToEnumType m_toEnum;												//< instanciation of the registry

	/**
	 * @brief Initializes the registry
	 */
	static void initialize();
};

} // namespace node

} // namespace vgd

#endif // #ifndef _VGD_NODE_ENUMREGISTRY_HPP
