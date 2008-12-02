// VGSDK - Copyright (C) 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_SCOPEDPTR_HPP
#define _VGD_SCOPEDPTR_HPP

#include <boost/scoped_ptr.hpp>



namespace vgd
{


/**
 * @brief Simple sole ownership of single objects. Noncopyable.
 * 
 * ScopedPtr mimics a built-in pointer except that it guarantees deletion
 * of the object pointed to, either on destruction of the scoped_ptr or via
 * an explicit reset(). ScopedPtr is a simple solution for simple needs;
 * Use Shp or std::auto_ptr if your needs are more complex.
 * 
 * @remarks Written to work with boost version 1.33.1
 * @sa http://boost.org/libs/smart_ptr/scoped_ptr.htm
 * 
 * @ingroup g_shp
 */
template<class T>
struct ScopedPtr : public boost::scoped_ptr<T>
{
private:
	// noncopyable
	ScopedPtr(ScopedPtr const &);
	ScopedPtr & operator=(ScopedPtr const &);

public:
	typedef T element_type;

	explicit ScopedPtr(T * p = 0): boost::scoped_ptr<T>(p) // never throws
	{}

#ifndef BOOST_NO_AUTO_PTR

	explicit ScopedPtr(std::auto_ptr<T> p): boost::scoped_ptr<T>(p) // never throws
	{}

#endif

};

/**
 * @relates ScopedPtr
 */
template<class T> inline void swap(ScopedPtr<T> & a, ScopedPtr<T> & b) // never throws
{
	boost::swap(a,b);
}

/**
 * @brief getPointer(p) is a generic way to say p.get()
 * 
 * @relates ScopedPtr
 */
template<class T> inline T * getPointer(ScopedPtr<T> const & p)
{
	boost::get_pointer(p);
}



} // namespace vgd

#endif //#ifndef _VGD_SCOPEDPTR_HPP
