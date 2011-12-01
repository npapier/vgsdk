// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/SubTechnique.hpp"



namespace vgeGL
{

namespace technique
{



// SUBTECHNIQUE
SubTechnique::SubTechnique()
: m_isEnabled( false )
{}

void SubTechnique::reset()
{
	m_isEnabled = false;
}


const bool SubTechnique::isEnabled() const
{
	return m_isEnabled;
}

const bool SubTechnique::setEnabled( const bool enabled )
{
	const bool oldState = isEnabled();
	m_isEnabled = enabled;
	return oldState;
}



} // namespace technique

} // namespace vgeGL
