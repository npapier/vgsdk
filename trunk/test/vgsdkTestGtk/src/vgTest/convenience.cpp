// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgsdkTestGtk/vgTest/convenience.hpp"
#include <vgd/Shp.hpp>
#include <vgd/basic/Image.hpp>
#include <sbf/path.hpp>
#include <vgio/FilenameCollector.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <sstream>

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

	std::vector<vgsdkTestGtk::vgTest::Performance> getPerformance(std::vector<int> level, 
											std::vector<vgd::node::VertexShape::DeformableHintValueType> deformableHint, 
											std::vector<vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType> boundingBoxPolicy)
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
