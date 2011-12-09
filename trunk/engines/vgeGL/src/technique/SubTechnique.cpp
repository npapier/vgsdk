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
:	m_isEnabled	( false	),
	m_node		( 0		)
{}

void SubTechnique::reset()
{
	m_isEnabled	= false;
	m_node		= 0;
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


const bool SubTechnique::isRCUpdated( vgeGL::technique::ForwardRendering * technique, vgeGL::engine::Engine * engine, vgd::Shp< glo::IResource > genericRC )
{
	if ( !isEnabled() )
	{
		return true;
	}
	else
	{
		// Gets node dirty flag
		vgd::field::DirtyFlag * nodeDF = getNode()->getDirtyFlag( getNode()->getDFNode() );
		return nodeDF->isValid();
	}
}


vgd::node::Node * SubTechnique::getNode() const
{
	return m_node;
}

void SubTechnique::setNode( vgd::node::Node * node )
{
	m_node = node;
}


} // namespace technique

} // namespace vgeGL
