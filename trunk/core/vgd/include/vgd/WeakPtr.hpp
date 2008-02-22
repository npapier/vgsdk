// VGSDK - Copyright (C) 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_WEAKPTR_HPP
#define _VGD_WEAKPTR_HPP

#include <boost/weak_ptr.hpp>



namespace vgd
{

/**
 * @brief Non-owning observers of an object owned by Shp.
 * 
 * @remarks Written to work with boost version 1.33.1
 * @sa http://boost.org/libs/smart_ptr/weak_ptr.htm
 * 
 * @ingroup g_shp
 */
template<class T> struct WeakPtr : public boost::weak_ptr<T>
{
	typedef T element_type;

	WeakPtr(): boost::weak_ptr<T>() // never throws in 1.30+
	{}

	// Generated copy constructor, assignment, destructor are fine.

	template<class Y>
	WeakPtr(boost::weak_ptr<Y> const & r): boost::weak_ptr<T>(r) // never throws
	{}

	template<class Y>
	WeakPtr(boost::shared_ptr<Y> const & r): boost::weak_ptr<T>(r) // never throws
	{}

//#if !defined(BOOST_MSVC) || (BOOST_MSVC > 1200)
//    template<class Y>
//    weak_ptr & operator=(weak_ptr<Y> const & r) // never throws
//
//    template<class Y>
//    weak_ptr & operator=(shared_ptr<Y> const & r) // never throws
//#endif
};


/**
 * @relates WeakPtr
 */
template<class T, class U> inline bool operator<(WeakPtr<T> const & a, WeakPtr<U> const & b)
{
	return boost::operator<(a,b);
}


/**
 * @relates WeakPtr
 */
template<class T> void swap(WeakPtr<T> & a, WeakPtr<T> & b)
{
	boost::swap(a,b);
}



} // namespace vgd

#endif //#ifndef _VGD_WEAKPTR_HPP
