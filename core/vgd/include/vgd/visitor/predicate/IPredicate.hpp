// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_PREDICATE_IPREDICATE_HPP
#define _VGD_VISITOR_PREDICATE_IPREDICATE_HPP

#include <functional>
#include "vgd/vgd.hpp"

namespace vgd
{

template<class T> struct Shp;

namespace node { struct Node; }

}



namespace vgd
{

namespace visitor
{

namespace predicate
{



/**
 * @brief Predicate abstract class.
 */
struct VGD_API IPredicate : public std::unary_function< const bool, const vgd::Shp< vgd::node::Node > >
{
	virtual const bool operator () ( const vgd::Shp< vgd::node::Node > node ) const=0;

	virtual const vgd::Shp< IPredicate > clone() const=0;
};



} // namespace predicate

} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_PREDICATE_IPREDICATE_HPP
