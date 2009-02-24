// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/event/TimerCallback.hpp"

//#include "vgd/basic/TimeDuration.hpp"
#include "vgd/event/TimerEvent.hpp"



namespace vgd
{

namespace event
{



TimerCallback::TimerCallback()
//: m_node
{
}



TimerCallback::TimerCallback( vgd::Shp< vgd::node::Node > node )
: m_node( node )
{
}



TimerCallback::~TimerCallback()
{
}



vgd::Shp< vgd::node::Node > TimerCallback::getNode()
{
	return m_node;
}



} // namespace event

} // namespace vgd
