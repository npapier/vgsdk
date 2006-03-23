// VGSDK - Copyright (C) 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_ENABLESHPFROMTHIS_HPP
#define _VGD_ENABLESHPFROMTHIS_HPP

#include <boost/enable_shared_from_this.hpp>



namespace vgd
{

template<class T> struct Shp;

/**
 * @brief Retrives an Shp from an object.
 * 
 * It is used as a base class that allows a Shp to the current object to be obtained from within a member function.
 * 
 * @remarks Written to work with boost version 1.33.1
 * @sa http://boost.org/libs/smart_ptr/enable_shared_from_this.html
 * 
 * @ingroup g_shp
 */
template<class T>
struct EnableShpFromThis : public boost::enable_shared_from_this<T>
{
	Shp<T> ShpFromThis()
	{
		return boost::enable_shared_from_this<T>::shared_from_this();
	}

	Shp<T const> ShpFromThis() const
	{
		return boost::enable_shared_from_this<T>::shared_from_this();
	}
};



} // namespace vgd

#endif //#ifndef _VGD_ENABLESHPFROMTHIS_HPP
