// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/basic/UniformContainer.hpp"



namespace vge
{

namespace basic
{



//UniformContainer::UniformContainer()
//{}



void UniformContainer::clear()
{
	m_container.clear();
}



const bool UniformContainer::removeUniform( const std::string& name )
{
	uint numRemovedElement = m_container.erase( name );
	return numRemovedElement == 1;
}



const bool UniformContainer::isUniform( const std::string& name ) const
{
	return m_container.count(name) == 1;
}



const uint UniformContainer::getSize() const
{
	return m_container.size();
}



std::pair< UniformContainer::ConstIteratorType, UniformContainer::ConstIteratorType > UniformContainer::getIterators() const
{
	return std::make_pair( m_container.begin(), m_container.end() );
}



} // namespace basic

} // namespace vge
