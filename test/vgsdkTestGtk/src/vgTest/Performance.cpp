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
	{
		m_level = 1;
		m_deformableHint = vgd::node::VertexShape::DEFAULT_DEFORMABLE_HINT;
		m_boundingBox = vgd::node::VertexShape::DEFAULT_BOUNDINGBOX_UPDATE_POLICY;
	}

	Performance::Performance(int l, vgd::node::VertexShape::DeformableHintValueType d, vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType b)
	{
		m_level = l;
		m_deformableHint = d;
		m_boundingBox = b;
	}

	int Performance::getLevel()
	{
		return m_level;
	}

	vgd::node::VertexShape::DeformableHintValueType Performance::getDeformableHint()
	{
		return m_deformableHint;
	}

	vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType Performance::getBoundingBox()
	{
		return m_boundingBox;
	}

	std::string	Performance::getDeformableHintToString()
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

	std::string	Performance::getBoundingBoxToString()
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
