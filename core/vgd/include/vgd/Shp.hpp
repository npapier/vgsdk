// VGSDK - Copyright (C) 2004-2006, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_SHP_HPP
#define _VGD_SHP_HPP

#include <boost/shared_ptr.hpp>



namespace vgd
{

/**
 * @brief Object ownership shared among multiple pointers.
 * 
 * An enhanced relative of scoped_ptr with reference counted copy semantics.
 * The object pointed to is deleted when the last Shp pointing to it is destroyed or reset.
 *
 * @remarks Written to work with boost version 1.30.2, 1.31.0, 1.32.0 and 1.33.1
 * @sa http://www.boost.org/libs/smart_ptr/shared_ptr.htm
 * 
 * @todo CXX11
 *
 * @ingroup g_shp
 */
template<class T>
struct Shp : public boost::shared_ptr<T>
{
	typedef T element_type;

	Shp(): boost::shared_ptr<T>() {}

	template<class Y>
	explicit Shp(Y * p) : boost::shared_ptr<T>(p)
	{}

	template<class Y, class D> Shp(Y * p, D d): boost::shared_ptr<T>(p,d)
	{}

	// Generated copy constructor, assignment, destructor are fine...
	template<class Y>
	explicit Shp(boost::weak_ptr<Y> const & r): boost::shared_ptr<T>(r)
	{}

	template<class Y>
	Shp(boost::shared_ptr<Y> const & r): boost::shared_ptr<T>(r)
	{}

// 1.54.0
#if SBF_BOOST_VERSION < 1054000
	template<class Y>
	Shp(boost::shared_ptr<Y> const & r, boost::detail::static_cast_tag): boost::shared_ptr<T>(r, boost::detail::static_cast_tag())
	{}

	template<class Y>
	Shp(boost::shared_ptr<Y> const & r, boost::detail::const_cast_tag): boost::shared_ptr<T>(r, boost::detail::const_cast_tag())
	{}

	template<class Y>
	Shp(boost::shared_ptr<Y> const & r, boost::detail::dynamic_cast_tag): boost::shared_ptr<T>(r, boost::detail::dynamic_cast_tag())
	{}

	template<class Y>
	Shp(boost::shared_ptr<Y> const & r, boost::detail::polymorphic_cast_tag): boost::shared_ptr<T>(r, boost::detail::polymorphic_cast_tag())
	{}
#endif

#ifndef BOOST_NO_AUTO_PTR
	template<class Y>
	explicit Shp(std::auto_ptr<Y> & r): boost::shared_ptr<T>(r)
	{}
#endif

//#if !defined(BOOST_MSVC) || (BOOST_MSVC > 1200)
//	template<class Y>
//	boost::shared_ptr & operator=(boost::shared_ptr<Y> const & r) // never throws
//#endif

//#ifndef BOOST_NO_AUTO_PTR
//	template<class Y>
//	Shp & operator=(std::auto_ptr<Y> & r )
//#endif
};



/**
 * @relates Shp
 */
template<class T, class U> inline bool operator==(Shp<T> const & a, Shp<U> const & b)
{
	return boost::operator==(a,b);
}


/**
 * @relates Shp
 */
template<class T, class U> inline bool operator!=(Shp<T> const & a, Shp<U> const & b)
{
	return boost::operator!=(a,b);
}


/**
 * @relates Shp
 */
template<class T, class U> inline bool operator<(Shp<T> const & a, Shp<U> const & b)
{
	return boost::operator<(a,b);
}


/**
 * @relates Shp
 */
template<class T> inline void swap(Shp<T> & a, Shp<T> & b)
{
	std::swap(a,b);
}


/**
 * @relates Shp
 */
template<class T, class U> Shp<T> static_pointer_cast(boost::shared_ptr<U> const & r)
{
#if SBF_BOOST_VERSION < 1054000
    return Shp<T>(r, boost::detail::static_cast_tag());
#else
	return boost::static_pointer_cast<T>(r);
#endif
}


/**
 * @relates Shp
 */
template<class T, class U> Shp<T> const_pointer_cast(boost::shared_ptr<U> const & r)
{
#if SBF_BOOST_VERSION < 1054000
	return Shp<T>(r, boost::detail::const_cast_tag());
#else
	return boost::const_pointer_cast<T>(r);
#endif
}


/**
 * @relates Shp
 */
template<class T, class U> Shp<T> dynamic_pointer_cast(boost::shared_ptr<U> const & r)
{
#if SBF_BOOST_VERSION < 1054000
	return Shp<T>(r, boost::detail::dynamic_cast_tag());
#else
	return boost::dynamic_pointer_cast<T>(r);
#endif
}


#if SBF_BOOST_VERSION >= 1054000
/**
 * @relates Shp
 */
template<class T, class U> Shp<T> reinterpret_pointer_cast(boost::shared_ptr<U> const & r)
{
	return boost::reinterpret_pointer_cast<T>(r);
}
#endif



/**
 * @brief enables boost::mem_fn to recognize Shp
 * 
 * @relates Shp
 */
template<class T> inline T * getPointer(boost::shared_ptr<T> const & p)
{
	return boost::get_pointer(p);
}



/**
 * @brief	Builds a shared pointer from the given pointer
 *
 * @relates Shp
 */
template<class T> Shp<T> makeShp( T * object )
{
	return Shp< T >( object );
}



} // namespace vgd

#endif //#ifndef _VGD_SHP_HPP
