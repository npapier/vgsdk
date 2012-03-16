// VGSDK - Copyright (C) 2009, 2012, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson
// Author Guillaume Brocker

#include "vgsdkTestGtk/vgTest/convenience.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>

#include <sstream>
#include <vgd/basic/Image.hpp>
#include <vgd/Shp.hpp>
#include <vgio/FilenameCollector.hpp>


namespace vgsdkTestGtk
{

namespace vgTest
{

bool getCreateReference()
{
	return createReference;
}

void setCreateReference(bool createRef)
{
	createReference = createRef;
}

std::vector<vgsdkTestGtk::vgTest::Performance> getPerformance(const std::vector<int> level, 
										const std::vector<vgd::node::VertexShape::DeformableHintValueType> deformableHint, 
										const std::vector<vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType> boundingBoxPolicy)
{
	std::vector<vgsdkTestGtk::vgTest::Performance> p;

	for( uint i = 0; i < level.size(); i++)
	{
		for( uint j = 0; j< deformableHint.size(); j++)
		{
			for( uint k = 0; k < boundingBoxPolicy.size(); k++)
			{
				p.push_back(Performance(level[i], deformableHint[j], boundingBoxPolicy[k]));
			}
		}
	}
	
	return p;
}

} //namespace vgTest

} //namespace vgsdkTestGtk

