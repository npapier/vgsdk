// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGUI_HELPERS_HPP
#define _VGUI_HELPERS_HPP

#include <string>
#include <boost/format.hpp>
#include "vgUI/vgUI.hpp"



namespace vgUI
{



/**
 * @brief Non-template version of boost::format
 */
struct VGUI_API Format
{
	Format( const std::string str );

	const std::string str() const;

	Format& operator %( const int param );
	Format& operator %( const float param );
	Format& operator %( const std::string param );

private:
	boost::format m_converter;
};



/**
 * @brief Substitute placeholders in a format string named 'str' with the given arguments.
 *
 * This function could be used to replace Glib::ustring::compose(), but the format string is not the same.
 * "%1" in ustring::compose() must be replaced by "%1%" in vgUI::compose()
 *
 * See boost::format for the complete description of the format string.
 */
template< typename T0 >
const std::string compose( const std::string str, const T0 param0 )
{
	Format format(str);
	format % param0;
	return format.str();
}


template< typename T0, typename T1 >
const std::string compose( const std::string str, const T0 param0, const T1 param1 )
{
	Format format(str);
	format % param0 % param1;
	return format.str();
}


template< typename T0, typename T1, typename T2 >
const std::string compose( const std::string str, const T0 param0, const T1 param1, const T2 param2 )
{
	Format format(str);
	format % param0 % param1 % param2;
	return format.str();
}


template< typename T0, typename T1, typename T2, typename T3 >
const std::string compose( const std::string str, const T0 param0, const T1 param1, const T2 param2, const T3 param3 )
{
	Format format(str);
	format % param0 % param1 % param2 % param3;
	return format.str();
}


template< typename T0, typename T1, typename T2, typename T3, typename T4 >
const std::string compose( const std::string str, const T0 param0, const T1 param1, const T2 param2, const T3 param3, const T4 param4 )
{
	Format format(str);
	format % param0 % param1 % param2 % param3 % param4;
	return format.str();
}



// @todo format()



} // namespace vgUI

#endif // #ifndef _VGUI_HELPERS_HPP
