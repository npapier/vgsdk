// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/State.hpp"


namespace vgUI
{

namespace actions
{



State::State()
{
}



int State::getNumberOfNode()
{
	return m_numberOfNode;
}



void State::setNumberOfNode( int number )
{
	m_numberOfNode = number;
}



int State::getNumberOfDisplayedNode()
{
	return m_numberOfDisplayedNode;
}



void State::setNumberOfDisplayedNode( int number )
{
	m_numberOfDisplayedNode = number;
}



bool State::isRoot()
{
	return m_isRoot;
}



void State::isRoot( bool b )
{
	m_isRoot = b;
}



vgd::Shp< vgd::node::Node > State::getSelectedNode()
{
	return m_selectedNode;
}



void State::setSelectedNode( vgd::Shp< vgd::node::Node > node )
{
	m_selectedNode = node;
}



bool State::hasAClipboardedNode()
{
	return m_hasAClipboardedNode;
}



void State::hasAClipboardedNode( bool b )
{
	m_hasAClipboardedNode = b;
}



LOCATION State::getLocation()
{
	return m_location;
}



void State::setLocation( LOCATION location )
{
	m_location = location;
}



vgd::Shp< vgd::node::Group > State::getParent()
{
	return m_parentNode;
}



void State::setParent( vgd::Shp< vgd::node::Group > parent )
{
	m_parentNode = parent;
}



bool State::isShape()
{
	return m_isShape;
}



void State::isShape( bool b )
{
	m_isShape = b;
}



bool State::isGroup()
{
	return m_isGroup;
}



void State::isGroup( bool b )
{
	m_isGroup = b;
}



bool State::isHidden()
{
	return m_isHidden;
}



void State::isHidden( bool b )
{
	m_isHidden = b;
}




int State::getNumberOfHiddenNode()
{
	return m_numberOfHiddenNode;
}



void State::setNumberOfHiddenNode( int number )
{
	m_numberOfHiddenNode = number;
}



} // namespace actions

} // namespace vgUI
