// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgsdkTestGtk/vgTest/Performance.hpp"

namespace vgsdkTestGtk
{

namespace vgTest
{

Performance::Performance()
:	m_level( 1 ),
	m_deformableHint( vgd::node::VertexShape::DEFAULT_DEFORMABLEHINT ),
	m_boundingBox( vgd::node::VertexShape::DEFAULT_BOUNDINGBOXUPDATEPOLICY )
{
}

Performance::Performance(const int l, const vgd::node::VertexShape::DeformableHintValueType d, const vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType b)
:	m_level( l ),
	m_deformableHint( d ),
	m_boundingBox( b )
{
}

const int Performance::getLevel() const
{
	return m_level;
}

const vgd::node::VertexShape::DeformableHintValueType Performance::getDeformableHint() const
{
	return m_deformableHint;
}

const vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType Performance::getBoundingBox() const
{
	return m_boundingBox;
}

const std::string	Performance::getDeformableHintToString() const
{
	if ( m_deformableHint == vgd::node::VertexShape::STATIC )
	{
		return "STATIC";
	}
	else if ( m_deformableHint == vgd::node::VertexShape::DYNAMIC )
	{
		return "DYNAMIC";
	}
	else if ( m_deformableHint == vgd::node::VertexShape::STREAM )
	{
		return "STREAM";
	}
	else
	{
		return "DEFAULT";
	}
}

const std::string	Performance::getBoundingBoxToString() const
{
	if ( m_boundingBox == vgd::node::VertexShape::AUTOMATIC )
	{
		return "AUTOMATIC";
	}
	else if ( m_boundingBox == vgd::node::VertexShape::ONCE )
	{
		return "ONCE";
	}
	else
	{
		return "DEFAULT";
	}
}

} //namespace vgTest

} //namespace vgsdkTestGtk

