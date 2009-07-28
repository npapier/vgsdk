// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgTest/convenience.hpp"
#include <vgd/Shp.hpp>
#include <vgd/basic/Image.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <sstream>

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

void moveTo(std::string from, std::string to)
{
	if (boost::filesystem::exists(to))
	{
		boost::filesystem::remove(to);
	}
	boost::filesystem::rename(from, to);
}

int compare(std::string pathRef, std::string pathCap, std::string pathDif)
{
	using vgd::basic::Image;
	vgd::Shp< Image > capturedImage( new Image );
	vgd::Shp< Image > referenceImage( new Image );

	capturedImage->load(pathCap);
	referenceImage->load(pathRef);

	vgd::Shp< Image > differenceImage( new Image( pathCap ));

	assert(capturedImage->format() == Image::RGB && capturedImage->type() == Image::UINT8);

	uint8 *pref = (uint8*)referenceImage->pixels();
	float rref;
	float gref;
	float bref;

	uint8 *p = (uint8*)capturedImage->pixels();
	float r;
	float g;
	float b;

	uint8 *pdif = (uint8*)differenceImage->pixels();
	
	if(referenceImage->computeNumberOfPixels() != capturedImage->computeNumberOfPixels())
	{
		return false;
	}
	
	int identique = 0;
	int different = 0;

	for (uint i = 0; i < referenceImage->computeNumberOfPixels(); i++)
	{
		rref = pref[0];
		gref = pref[1];
		bref = pref[2];

		r = p[0];
		g = p[1];
		b = p[2];

		pdif[0] = static_cast<uint>( std::fabs(rref - r) );
		pdif[1] = static_cast<uint>( std::fabs(gref - g) );
		pdif[2] = static_cast<uint>( std::fabs(bref - b) );

		//pdif[0] = static_cast< uint8 >((rref - r) / 2.f + 127.5f);
		//pdif[1] = static_cast< uint8 >((gref - g) / 2.f + 127.5f);
		//pdif[2] = static_cast< uint8 >((bref - b) / 2.f + 127.5f);

		if(rref != r || gref != g || bref != b)
		{
			different++;
		}
		else
		{
			identique++;
		}

		pref += referenceImage->components();
		p += capturedImage->components();
		pdif += differenceImage->components();
	}
	
	if( boost::filesystem::exists( pathDif ) )
	{
		boost::filesystem::remove( pathDif );
	}
	if( different > 0 )
	{
		differenceImage->save(pathDif);
	}
	
	return different;
}


std::vector<vgTest::Performance> getPerformance(std::vector<int> level, 
										std::vector<vgd::node::VertexShape::DeformableHintValueType> deformableHint, 
										std::vector<vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType> boundingBoxPolicy)
{
	std::vector<vgTest::Performance> p;

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

std::string getImageName(std::string filename)
{
	boost::replace_all(filename, "/", "-");

	return filename + ".png";
}

std::string getDatedImageName(std::string filename)
{
	using namespace boost::posix_time;
	using namespace boost::gregorian;
	
	boost::replace_all(filename, "/", "-");
	boost::replace_all(filename, ".png", "");


	ptime now = second_clock::local_time();
	date d = now.date();
	filename += "_" + to_simple_string(now);

	boost::replace_all(filename, " ", "_");
	boost::replace_all(filename, ":", "");
	return filename + ".png";
}

} //namespace vgTest
