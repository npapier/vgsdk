// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgUI/actions/IActionUI.hpp"

#include <boost/algorithm/string.hpp>

namespace vgUI
{

namespace actions
{



IActionUI::IActionUI( std::string menuContrib, std::string name, std::string id, Icons icon, std::string accelKey, vgAlg::actions::IAction* action ) :
m_menuContrib( menuContrib ),
m_name( name ),
m_id( id ),
m_icon( icon ),
m_accelKey( accelKey ),
m_action( vgd::makeShp( action ) )
{
}



IActionUI::~IActionUI( )
{
}



const std::string IActionUI::getMenuContrib() const
{
	return m_menuContrib;
}



const std::vector< std::string > IActionUI::getMenuContribList() const
{
	std::vector<std::string> strs;
	boost::split( strs, m_menuContrib, boost::is_any_of("/") );
	return strs;
}



const std::string IActionUI::getName() const
{
	return m_name;
}



const std::string IActionUI::getId() const
{
	return m_id;
}



const Icons IActionUI::getIcon() const
{
	return m_icon;
}



const std::string IActionUI::getAccelKey() const
{
	return m_accelKey;
}



vgAlg::actions::IAction* IActionUI::getAction() const
{
	return m_action.get();
}



} // namespace actions

} // namespace vgUI
