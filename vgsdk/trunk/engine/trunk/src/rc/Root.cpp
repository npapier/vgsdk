// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/rc/Root.hpp"



namespace vge
{

namespace rc
{



Root::Root()
:	m_root( vgd::node::Separator::create("vge::rc::Root") )
{}



const vgd::Shp< vgd::node::Separator > Root::getRoot() const
{
	return m_root;
}



vgd::Shp< vgd::node::Separator > Root::getRoot()
{
	return m_root;
}



} // namespace rc

} // namespace vge
